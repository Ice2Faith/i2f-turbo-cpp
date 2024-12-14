#include <iostream>
/*
PCM播放器的实现
在SDL中播放的是PCM数据

基本流程：
打开音频设备
设置音频参数
传递数据
播放音频
关闭设备

基本原则是：
声卡主动要数据，而不是自己推送数据过去
因此，需要回调函数
需要数据量的多少是由音频参数决定的

音频函数：
SDL_OpenAudio/SDL_CloseAudio()
SDL_PauseAudio
SDL_MixAudio 混音，实际上是做加法

*/
#include <Sdl.h>
#define __STDC_CONSTANT_MACROS
extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>
#include<libavcodec/avcodec.h>
#include<libswscale/swscale.h>
}
#define BLOCK_SIZE 4096000
Uint8 * audioBuf = NULL;
int bufLen;
Uint8* audioPos;
bool allOver = false;
bool hasNoData = false;
void readAudioDataCallBack(void *userdata, Uint8 * stream,int len)
{
	if (bufLen == 0)
	{
		return;
	}
	SDL_memset(stream, 0, len);
	len = (len < bufLen) ? len : bufLen;
	SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME);

	audioPos += len;
	bufLen -= len;
	if (hasNoData && bufLen == 0)
	{
		allOver = true;
	}
}

int getAudioPcmData(char * filename, char * savefile);
int decode_write_frame(char * savefile,
	AVCodecContext * context, 
	AVFrame * frame, int * frameCount, AVPacket * pkt);
void savePcmDataToFile(AVFrame * frame, char * saveName, int isLast);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("参数：文件名\n");
		system("pause");
		return -1;
	}
	if (getAudioPcmData(argv[1], "_tmp.pcm") < 0)
	{
		printf("get pcm data failure\n");
		return -1;
	}

	if (SDL_Init(SDL_INIT_AUDIO))
	{
		SDL_Log("SDL init failure");
		return -1;
	}

	char * filename = "_tmp.pcm";

	FILE * fpPcm = fopen(filename,"rb");
	if (!fpPcm)
	{
		SDL_Log("open pcm file failure");
		goto __EXIT;
	}

	audioBuf = (Uint8*)malloc(BLOCK_SIZE);
	if (!audioBuf)
	{
		SDL_Log("allocate audio buff failure");
		goto __CLOSEFILE;
	}

	//参数设置
	SDL_AudioSpec spec;
	spec.freq = 44100;
	spec.channels = 2;
	spec.format = AUDIO_S16SYS;
	spec.silence = 0;
	spec.callback = readAudioDataCallBack;
	spec.userdata = NULL;//回调的返回值指针
	if (SDL_OpenAudio(&spec, NULL))
	{
		SDL_Log("open audio device failure");
		goto __CLOSEFILE;
	}

	SDL_PauseAudio(0);//开始播放

	do
	{
		//从PCM文件读取数据到缓冲区
		bufLen=fread(audioBuf, 1, BLOCK_SIZE, fpPcm);
		audioPos = audioBuf;
		while (audioPos < (audioBuf + bufLen))
		{
			SDL_Delay(1);
		}
	} while (bufLen!=0);
	hasNoData = true;

	//等待播放结束
	while (!allOver)
	{
		SDL_Delay(30);
	}
	SDL_CloseAudio();
__CLOSEFILE:
	if (audioBuf)
	{
		free(audioBuf);
	}
	fclose(fpPcm);
	remove(filename);

__EXIT:
	SDL_Quit(); 
	return 0;
}


int getAudioPcmData(char * filename, char * savefile)
{
	//设置日志级别和注册库
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();

	AVFormatContext * fmtCxt = NULL;
	if (avformat_open_input(&fmtCxt, filename, NULL, NULL) < 0)
	{
		printf("couldn't open source file\n");
		return -1;
	}

	if (avformat_find_stream_info(fmtCxt, NULL) < 0)
	{
		printf("couldn't find any stream info\n");
		return -1;
	}

	av_dump_format(fmtCxt, 0, filename, 0);

	int streamIndex;
	AVStream * stream;
	streamIndex = av_find_best_stream(fmtCxt, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (streamIndex < 0)
	{
		printf("couldn't find video stream\n");
		return -1;
	}
	stream = fmtCxt->streams[streamIndex];

	AVCodec * codec;
	AVCodecContext * context;
	codec = avcodec_find_decoder(stream->codecpar->codec_id);
	if (!codec)
	{
		printf("couldn't find video codec\n");
		return -1;
	}

	context = avcodec_alloc_context3(NULL);
	if (!context)
	{
		printf("couldn't allocate codec context\n");
		return -1;
	}

	if (avcodec_parameters_to_context(context, stream->codecpar) < 0)
	{
		printf("couldn't copy codec params to decoder\n");
		return -1;
	}

	if (avcodec_open2(context, codec, NULL) < 0)
	{
		printf("couldn't open codec\n");
		return -1;
	}


	AVFrame * frame;
	frame = av_frame_alloc();
	if (!frame)
	{
		printf("couldn't alloc frame\n");
		return -1;
	}

	AVPacket pkt;
	av_init_packet(&pkt);
	int frameCount = 0;
	while (av_read_frame(fmtCxt, &pkt) >= 0)
	{
		if (pkt.stream_index == streamIndex)
		{
			if (decode_write_frame(savefile, context, frame, &frameCount, &pkt) < 0)
			{
				return -1;
			}
		}
		av_packet_unref(&pkt);
	}

	avformat_close_input(&fmtCxt);
	savePcmDataToFile(NULL, NULL, 1);
}
int decode_write_frame(char * savefile,
	AVCodecContext * context, 
	AVFrame * frame, int * frameCount, AVPacket * pkt)
{
	int len, got_frame;

	len = avcodec_decode_audio4(context, frame, &got_frame, pkt);
	if (len < 0)
	{
		printf("couldn't decode frame\n");
		return -1;
	}
	if (got_frame)
	{
		printf("save frame %3d \n", *frameCount);
		savePcmDataToFile(frame, savefile, 0);
		(*frameCount)++;
	}
	if (pkt->data)
	{
		pkt->size -= len;
		pkt->data += len;
	}
	return 0;
}
void savePcmDataToFile(AVFrame * frame, char * saveName, int isLast)
{
	static FILE * fp = NULL;
	if (isLast)
	{
		fclose(fp);
		return;
	}
	int height = frame->height;
	int width = frame->width;
	if (fp == NULL)
	{
		fp = fopen(saveName, "wb");
	}
	
	fwrite(frame->data[0], 1, frame->linesize[0], fp);
}