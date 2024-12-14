#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
/*
About:
AAC编码
编码流程和视频编码流程一致，参考H264编码

函数：
avcodec_encodec_audio2


下面给出一个编码例子，数据是模拟的
*/
#define __STDC_CONSTANT_MACROS

extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>

#include<libavcodec\avcodec.h>
#include<libavutil\channel_layout.h>
#include<libavutil\common.h>
#include<libavutil\frame.h>
#include<libavutil\samplefmt.h>
}

int check_sample_fmt(const AVCodec *codec, enum AVSampleFormat sample_fmt)
{
	const enum AVSampleFormat *p = codec->sample_fmts;

	while (*p != AV_SAMPLE_FMT_NONE) {
		if (*p == sample_fmt)
			return 1;
		p++;
	}
	return 0;
}
// 从编码器中获取采样率(从编码器所支持的采样率中获取与44100最接近的采样率)
int select_sample_rate(const AVCodec *codec)
{
	const int *p;
	int best_samplerate = 0;

	if (!codec->supported_samplerates)
		return 44100;

	p = codec->supported_samplerates;
	while (*p) {
		if (!best_samplerate || abs(44100 - *p) < abs(44100 - best_samplerate))
			best_samplerate = *p;
		p++;
	}
	return best_samplerate;
}

/* select layout with the highest channel count */
int select_channel_layout(const AVCodec *codec)
{
	const uint64_t *p;
	uint64_t best_ch_layout = 0;
	int best_nb_channels = 0;

	if (!codec->channel_layouts)
		return AV_CH_LAYOUT_STEREO;

	p = codec->channel_layouts;
	while (*p) {
		int nb_channels = av_get_channel_layout_nb_channels(*p);

		if (nb_channels > best_nb_channels) {
			best_ch_layout = *p;
			best_nb_channels = nb_channels;
		}
		p++;
	}
	return best_ch_layout;
}


int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		printf("参数：文件名\n");
		system("pause");
		return 0;
	}

	av_log_set_level(AV_LOG_DEBUG);
	avcodec_register_all();

	char * filename = argv[1];

	AVCodec * codec;
	AVCodecContext * context = NULL;
	codec = avcodec_find_encoder_by_name("libfdk_aac"); //使用fdk 的aac 编码器
	if (!codec)
	{
		printf("couldn't find codec\n");
		return -1;
	}
	context = avcodec_alloc_context3(codec);
	if (!context)
	{
		printf("couldn't allocate codec context\n");
		return -1;
	}

	//设置编码参数
	context->bit_rate = 64*1000;
	context->sample_fmt = AV_SAMPLE_FMT_S16;
	if (!check_sample_fmt(codec, context->sample_fmt))
	{
		printf("couldn't find support encoder\n");
		return -1;
	}
	//通过函数的方式去设置其他支持的参数
	
	context->sample_rate = select_sample_rate(codec);
	context->channel_layout =  select_channel_layout(codec);
	context->channels =  av_get_channel_layout_nb_channels(context->channel_layout);

	//打开编码器
	if (avcodec_open2(context, codec, NULL) < 0)
	{
		printf("couldn't open codec\n");
		return -1;
	}

	AVFrame * frame;
	frame = av_frame_alloc();
	if (!frame)
	{
		printf("couldn't allocate frame\n");
		return -1;
	}
	frame->nb_samples = context->frame_size;
	frame->format = context->sample_fmt;
	frame->channel_layout = context->channel_layout;

	int retCode;
	retCode = av_frame_get_buffer(frame, 0);
	if (retCode < 0)
	{
		printf("couldn't get frame buffer\n");
		return -1;
	}

	FILE * outFp;
	outFp = fopen(filename, "wb");
	if (!outFp)
	{
		printf("couldn't open output file\n");
		return -1;
	}

	//创建模拟数据
	float t;
	float tincr;
	AVPacket pkt;
	uint16_t * samples;
	int got_output;
	t = 0;
	tincr = 2 * M_PI*440.0 / context->sample_rate;
	for (int i = 0; i < 200; i++)
	{
		av_init_packet(&pkt);
		pkt.data = NULL;
		pkt.size = 0;

		retCode = av_frame_make_writable(frame);
		if (retCode < 0)
		{
			printf("couldn't write frame\n");
			return -1;
		}

		samples = (uint16_t *)frame->data[0];

		for (int j = 0; j < context->frame_size; j++)
		{
			samples[2 * j] = (int)(sin(t)*10000);
			for (int k = 0; k < context->channels; k++)
				samples[2 * j + k] = samples[2*j];
			t += tincr;
		}

		//编码
		retCode = avcodec_encode_audio2(context, &pkt, frame, &got_output);
		if (retCode < 0)
		{
			printf("couldn't encode audio frame\n");
			return -1;
		}
		//写出编码数据
		if (got_output)
		{
			fwrite(pkt.data, 1, pkt.size, outFp);
			av_packet_unref(&pkt);
		}
	}
	//处理剩下的帧
	for (int i = 1; i < got_output; i++)
	{
		//编码
		retCode = avcodec_encode_audio2(context, &pkt, frame, &got_output);
		if (retCode < 0)
		{
			printf("couldn't encode audio frame\n");
			return -1;
		}
		//写出编码数据
		if (got_output)
		{
			fwrite(pkt.data, 1, pkt.size, outFp);
			av_packet_unref(&pkt);
		}
	}
	
	fclose(outFp);

	av_frame_free(&frame);
	avcodec_free_context(&context);
	
	system("pause");
	return 0;
}
