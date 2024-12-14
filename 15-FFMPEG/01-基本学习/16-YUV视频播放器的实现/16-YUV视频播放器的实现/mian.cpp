#include <iostream>
/*
SDL+FFMPEG实现一个YUV视频播放器
创建线程：
SDL_CreateThread
参数：
	fn:执行函数
	name:线程名称
	data:执行函数的参数
更新纹理：
SDL_UpdateTexture()
SDL_UpdateYUVTexture()
 
逻辑：
	用定时器来定时更新播放画面
	来实现绘制一帧图像在屏幕上

	YUV444=YYYYUUUUVVVV
	
由于这里主要是讲解SDL中播放YUV视频，因此流程设计如下：
使用FFMPEG获得视频文件的YUV数据，保存到文件中：文件格式：视频宽（int）视频高（int）YUV数据
之后打开此YUV数据的文件，读取数据进行播放
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

int REFRESH_EVENT = 0;
int QUIT_EVENT = 0;
int thread_exit = 0;
int refresh_video_timer(void * udata)
{
	thread_exit = 0;

	while (!thread_exit)
	{
		SDL_Event event;
		event.type = REFRESH_EVENT;
		SDL_PushEvent(&event);
		SDL_Delay(40);
	}


	SDL_Event event;
	event.type = QUIT_EVENT;
	SDL_PushEvent(&event);
	return 0;
}
int decode_write_frame(char * savefile,
	AVCodecContext * context, struct SwsContext * imgConvertCxt,
	AVFrame * frame, int * frameCount, AVPacket * pkt);
void saveYuvDataToFile(AVFrame * frame, char * saveName, int isLast);
int getVideoYuvData(char * filename,char * savefile);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("参数：文件名\n");
		system("pause");
		return -1;
	}
	if (getVideoYuvData(argv[1],"_tmp.yuv") < 0)
	{
		printf("get yuv data failure\n");
		goto __FAILURE;
	}
	char * videoPath = "_tmp.yuv";

	int winWid = 720;
	int winHei = 480;
	int videoWid = 720;
	int videoHei = 480;

	FILE * fpVideo = NULL;
	fpVideo = fopen(videoPath, "rb");
	if (!fpVideo)
	{
		printf("open video file failure\n");
		goto __FAILURE;
	}
	fread(&videoWid, sizeof(int), 1, fpVideo);
	fread(&videoHei, sizeof(int), 1, fpVideo);
	winWid = videoWid;
	winHei = videoHei;
	printf("video Size:%d %d\n",videoWid,videoHei);

	//计算一帧的大小
	unsigned int yuvFrameLen = videoWid*videoHei * 12 / 8;
	unsigned int tmpYuvFrameLen = yuvFrameLen;
	//考虑对齐
	if (yuvFrameLen & 0xf)
	{
		tmpYuvFrameLen = (yuvFrameLen & 0xfff0) + 0x10;
	}

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("init sdl failure\n");
		return -1;
	}

	SDL_Window * window = NULL;
	window = SDL_CreateWindow(
		"YUV player",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		winWid, winHei,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		printf("create window failure\n");
		goto __DESTORYWINDOW;
	}

	SDL_Renderer * render = NULL;
	render = SDL_CreateRenderer(window, -1, 0);
	if (!render)
	{
		printf("create render failure\n");
		goto __DESTORYRENDER;
	}

	//IYUV:YUV
	//YV12:YVU
	SDL_Texture * texture = NULL;
	Uint32 pixFormat = 0;
	pixFormat = SDL_PIXELFORMAT_IYUV;
	texture = SDL_CreateTexture(render, pixFormat,
		SDL_TEXTUREACCESS_STREAMING,
		videoWid, videoHei);
	if (!texture)
	{
		printf("create texture failure\n");
		goto __DESTORYTEXTURE;
	}

	size_t videoBuffLen = 0;
	Uint8 * videoBuf = NULL;
	videoBuf = (Uint8*)malloc(tmpYuvFrameLen);
	if (!videoBuf){
		printf("allocate video buff failure\n");
		goto __FAILURE;
	}

	if ((videoBuffLen = fread(videoBuf, 1, yuvFrameLen, fpVideo) <= 0))
	{
		printf("read yuv data failure\n");
		goto __FAILURE;
	}

	Uint8 * videoPos = NULL;
	Uint8 * videoEnd = NULL;
	videoPos = videoBuf;
	/*
	videoEnd = videoBuf + videoBuffLen;
	blankSpaceLen = BLOCK_SIZE - videoBuffLen;
	*/
	//使用自定义的事件，需要进行注册，否则直接用宏定义是无效的
	//注册函数：要注册的自定义事件数量，返回第一个事件的ID，后面的依次+1
	REFRESH_EVENT = SDL_RegisterEvents(2);
	QUIT_EVENT = REFRESH_EVENT + 1;
	SDL_Thread * timerThread = NULL;
	timerThread = SDL_CreateThread(refresh_video_timer,NULL,NULL);

	SDL_Event event;
	SDL_Rect rect;
	do{
		SDL_WaitEvent(&event);
		if (event.type == REFRESH_EVENT)
		{
			SDL_UpdateTexture(texture, NULL, videoPos, videoWid);

			//如果窗口大小改变
			rect.x = 0;
			rect.y = 0;
			rect.w = winWid;
			rect.h = winHei;

			SDL_RenderCopy(render, texture, NULL, &rect);
			SDL_RenderPresent(render);

			if ((videoBuffLen = fread(videoBuf, 1, yuvFrameLen, fpVideo)) <= 0)
			{
				thread_exit = 1;
				continue;
			}

		}
		else if (event.type == SDL_WINDOWEVENT)
		{
			SDL_GetWindowSize(window, &winWid, &winHei);
		}
		else if (event.type == SDL_QUIT)
		{
			thread_exit = 1;
		}
		else if (event.type == QUIT_EVENT)
		{
			break;
		}
	} while (1);

__FAILURE:
	if (videoBuf)
	{
		free(videoBuf);
	}
	if (fpVideo)
	{
		fclose(fpVideo);
		remove(videoPath);
	}

__DESTORYTEXTURE:
	//销毁纹理
	if (texture)
		SDL_DestroyTexture(texture);

__DESTORYRENDER:
	//销毁渲染器
	SDL_DestroyRenderer(render);

__DESTORYWINDOW:
	//销毁窗口
	SDL_DestroyWindow(window);

__EXIT:
	SDL_Quit();
	return 0;
}

int getVideoYuvData(char * filename, char * savefile)
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
	streamIndex = av_find_best_stream(fmtCxt, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
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

	struct SwsContext * imgConvertCxt;
	imgConvertCxt = sws_getContext(context->width, context->height,
		context->pix_fmt,
		context->width, context->height,
		AV_PIX_FMT_YUV420P,
		SWS_BICUBIC, NULL, NULL, NULL);
	if (!imgConvertCxt)
	{
		printf("couldn't init convert context\n");
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
			if (decode_write_frame(savefile,context, imgConvertCxt, frame, &frameCount, &pkt) < 0)
			{
				return -1;
			}
		}
		av_packet_unref(&pkt);
	}

	avformat_close_input(&fmtCxt);
	saveYuvDataToFile(NULL, NULL, 1);
}
int decode_write_frame(char * savefile,
	AVCodecContext * context, struct SwsContext * imgConvertCxt,
	AVFrame * frame, int * frameCount, AVPacket * pkt)
{
	int len, got_frame;

	len = avcodec_decode_video2(context, frame, &got_frame, pkt);
	if (len < 0)
	{
		printf("couldn't decode frame\n");
		return -1;
	}
	if (got_frame)
	{
		printf("save frame %3d \n", *frameCount);
		saveYuvDataToFile(frame, savefile, 0);
		(*frameCount)++;
	}
	if (pkt->data)
	{
		pkt->size -= len;
		pkt->data += len;
	}
	return 0;
}
void saveYuvDataToFile(AVFrame * frame, char * saveName, int isLast)
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
		fp = fopen(saveName,"wb");
		fwrite(&width, sizeof(int), 1, fp);
		fwrite(&height, sizeof(int), 1, fp);
	}
	for (int j = 0; j<height; j++)
		fwrite(frame->data[0] + j * frame->linesize[0], 1, width, fp);
	for (int j = 0; j<height / 2; j++)
		fwrite(frame->data[1] + j * frame->linesize[1], 1, width / 2, fp);
	for (int j = 0; j<height / 2; j++)
		fwrite(frame->data[2] + j * frame->linesize[2], 1, width / 2, fp);
}