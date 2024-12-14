#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
About:
FFMPEG中级开发阶段
H264和AAC的编解码
以这两个为例，进行音视频的编解码流程
其他的编码格式也是类似的
*/

/*
H264解码：
头文件：
libavcodec/avcodec.h

结构体：
AVCodec 编码器结构体
AVCodecContext 编码器上下文
AVFrame 解码后的帧（未压缩的）

分配与释放：
av_frame_alloc/av_frame_free()
avcodec_alloc_context3()
avcodec_free_context()

解码步骤：
avcodec_find_decoder 查找解码器
avcodec_open2 打开解码器
avcodec_decode_video2 解码
之后皆可以进行显示，渲染

*/

/*
H264编码：

流程：
avcodec_find_encoder_by_name 查找编码器
avcodec_open2 设置编码参数，并打开编码器
avcodec_encode_video2 编码

下面给出一个例子，模拟一下编码的过程
调用命令行参数：test.h264 libx264
第二个参数就是h264编码器的名称
生成的文件可以直接使用：
fflpay test.h264
进行播放
*/
#define __STDC_CONSTANT_MACROS

extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>

#include<libavcodec/avcodec.h>

#include<libavutil/opt.h>
#include<libavutil/imgutils.h>
}



int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		printf("参数：文件名 编解码器名称\n");
		system("pause");
		return 0;
	}
	char * filename = argv[1];
	char * codec_name = argv[2];

	//设置日志级别和注册库
	av_log_set_level(AV_LOG_DEBUG);
	avcodec_register_all(); //注意，这里只使用codec，所以就不用av_register_all

	AVCodec * codec = NULL;
	AVCodecContext * context = NULL;
	

	codec = avcodec_find_encoder_by_name(codec_name);
	if (!codec)
	{
		printf("codec not found!\n");
		return -1;
	}

	context = avcodec_alloc_context3(codec);
	if (!context)
	{
		printf("couldn't alocate codec context!\n");
		return -1;
	}

	//设置参数
	context->bit_rate = 400 * 1000;//码率
	context->width = 720;//分辨率设置
	context->height = 480;
	AVRational timebase = { 1, 25 };
	AVRational framerate = { 25, 1 };
	context->time_base = timebase; //时间机
	context->framerate = framerate; //帧率
	context->gop_size = 10;//一组帧的数量，也就是一个关键字引导的一组
	context->max_b_frames = 1; //前后参考帧
	context->pix_fmt = AV_PIX_FMT_YUV420P;//原始编码格式
	if (codec->id == AV_CODEC_ID_H264)//适用慢速编码
		av_opt_set(context->priv_data, "preset", "slow", 0);

	//打开解码器
	if (avcodec_open2(context, codec, NULL) < 0)
	{
		printf("couldn't open codec!\n");
		return -1;
	}

	//打开输出文件
	FILE * outfp = fopen(filename,"wb");
	if (!outfp)
	{
		printf("couldn't open output file!\n");
		return -1;
	}

	//申请帧空间
	AVFrame * frame;
	frame = av_frame_alloc();
	if (!frame)
	{
		printf("couldn't allocate frame!\n");
		return -1;
	}
	frame->format = context->pix_fmt;
	frame->width = context->width;
	frame->height = context->height;

	int retCode = av_frame_get_buffer(frame, 32);
	if (retCode < 0)
	{
		printf("couldn't allocate video frame data!\n");
		return -1;
	}

	//编码一秒钟的视频数据,帧率为25，之前设置的
	AVPacket pkt;
	uint8_t endcode[] = { 0, 0, 1, 0xb7 };
	int got_output;
	for (int i = 0; i < 25*5; i++)
	{
		av_init_packet(&pkt);
		pkt.data = NULL; //编码器会分配
		pkt.size = 0;

		fflush(stdout);

		//检查帧数据是否可写
		retCode = av_frame_make_writable(frame);
		if (retCode < 0){
			return -1;
		}

		//绘制一帧数据
		for (int y = 0; y < context->height; y++)
		{
			for (int x = 0; x < context->width; x++)
			{
				frame->data[0][y*frame->linesize[0] + x] = x + y + i * 3;
			}
		}

		for (int y = 0; y < context->height / 2; y++)
		{
			for (int x = 0; x < context->width / 2; x++)
			{
				frame->data[1][y*frame->linesize[1] + x] = 128 + y + i * 2;

				frame->data[2][y*frame->linesize[2] + x] = 64 + x + i * 5;
			}
		}

		//进行编码
		retCode = avcodec_encode_video2(context, &pkt, frame, &got_output);
		if (retCode < 0)
		{
			printf("couldn't encode video frame!\n");
			return -1;
		}
		if (got_output)
		{
			printf("write frame %3d size is %5d\n",i,pkt.size);
			fwrite(pkt.data, 1, pkt.size, outfp);
			av_packet_unref(&pkt);
		}
	}

	//处理剩下的帧（没有打包的）
	for (int i = 1; i < got_output; i++)
	{
		//进行编码
		retCode = avcodec_encode_video2(context, &pkt, frame, &got_output);
		if (retCode < 0)
		{
			printf("couldn't encode video frame!\n");
			return -1;
		}
		if (got_output)
		{
			printf("write frame %3d size is %5d\n", i, pkt.size);
			fwrite(pkt.data, 1, pkt.size, outfp);
			av_packet_unref(&pkt);
		}
	}

	fclose(outfp);

	return 0;
}
