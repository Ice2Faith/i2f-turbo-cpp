#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
/*
About:
上一节的说明中，使用了H264的编码，产生了我们的视频
现在，我们使用H264的解码，来实现视频转图片

*/
#define __STDC_CONSTANT_MACROS

extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>
#include<libavcodec/avcodec.h>
#include<libswscale/swscale.h>

}
void savePicture(AVFrame * frame, char * buf);
int decode_write_frame(char * outfile,
AVCodecContext * context, struct SwsContext * imgConvertCxt,
AVFrame * frame, int * frameCount, AVPacket * pkt);


int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		printf("参数：文件名 图片文件名\n");
		system("pause");
		return 0;
	}
	
	//设置日志级别和注册库
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();

	char * filename = argv[1];
	char * outfile = argv[2]; 

	AVFormatContext * fmtCxt=NULL;
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
		AV_PIX_FMT_RGB32,
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
	int frameCount=0;
	while (av_read_frame(fmtCxt, &pkt) >= 0)
	{
		if (pkt.stream_index == streamIndex)
		{
			if (decode_write_frame(outfile, context, imgConvertCxt, frame, &frameCount, &pkt) < 0)
			{
				return -1;
			}
		}
		av_packet_unref(&pkt);
	}

	avformat_close_input(&fmtCxt);

	return 0;
}

int decode_write_frame(char * outfile,
	AVCodecContext * context, struct SwsContext * imgConvertCxt,
	AVFrame * frame, int * frameCount, AVPacket * pkt)
{
	int len, got_frame;
	char buf[1024];

	len = avcodec_decode_video2(context, frame, &got_frame, pkt);
	if (len < 0)
	{
		printf("couldn't decode frame\n");
		return -1;
	}
	if (got_frame)
	{
		printf("save frame %3d \n",*frameCount);
		sprintf(buf, ".\\%s-%d.jpg", outfile, *frameCount);
		savePicture(frame, buf);
		(*frameCount)++;
	/*	if ((*frameCount) == 4)
		{
			exit(0);
		}*/
	}
	if (pkt->data)
	{
		pkt->size -= len;
		pkt->data += len;
	}
	return 0;
}
void savePicture(AVFrame * frame, char * buf)
{
	IMAGE img(frame->width, frame->height);
	SetWorkingImage(&img);
	for (int x = 0; x < frame->width; x++)
	{
		for (int y = 0; y < frame->height; y++)
		{
			int p = x + y*frame->linesize[0];
			/*short r = frame->data[0][y*frame->linesize[0] + x];
			short g = frame->data[1][y/2*frame->linesize[1] + x/2];
			short b = frame->data[2][y/2*frame->linesize[2] + x/2];*/
			short r = frame->data[0][p ];
			short g = frame->data[0][p +1];
			short b = frame->data[0][p + 2];
			putpixel(x, y, RGB(r, g, b));
		}
	}
	SetWorkingImage(NULL);
	saveimage(buf, &img);
}

