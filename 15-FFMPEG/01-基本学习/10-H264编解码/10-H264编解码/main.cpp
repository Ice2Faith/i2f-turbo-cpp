#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
About:
FFMPEG�м������׶�
H264��AAC�ı����
��������Ϊ������������Ƶ�ı��������
�����ı����ʽҲ�����Ƶ�
*/

/*
H264���룺
ͷ�ļ���
libavcodec/avcodec.h

�ṹ�壺
AVCodec �������ṹ��
AVCodecContext ������������
AVFrame ������֡��δѹ���ģ�

�������ͷţ�
av_frame_alloc/av_frame_free()
avcodec_alloc_context3()
avcodec_free_context()

���벽�裺
avcodec_find_decoder ���ҽ�����
avcodec_open2 �򿪽�����
avcodec_decode_video2 ����
֮��Կ��Խ�����ʾ����Ⱦ

*/

/*
H264���룺

���̣�
avcodec_find_encoder_by_name ���ұ�����
avcodec_open2 ���ñ�����������򿪱�����
avcodec_encode_video2 ����

�������һ�����ӣ�ģ��һ�±���Ĺ���
���������в�����test.h264 libx264
�ڶ�����������h264������������
���ɵ��ļ�����ֱ��ʹ�ã�
fflpay test.h264
���в���
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
		printf("�������ļ��� �����������\n");
		system("pause");
		return 0;
	}
	char * filename = argv[1];
	char * codec_name = argv[2];

	//������־�����ע���
	av_log_set_level(AV_LOG_DEBUG);
	avcodec_register_all(); //ע�⣬����ֻʹ��codec�����ԾͲ���av_register_all

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

	//���ò���
	context->bit_rate = 400 * 1000;//����
	context->width = 720;//�ֱ�������
	context->height = 480;
	AVRational timebase = { 1, 25 };
	AVRational framerate = { 25, 1 };
	context->time_base = timebase; //ʱ���
	context->framerate = framerate; //֡��
	context->gop_size = 10;//һ��֡��������Ҳ����һ���ؼ���������һ��
	context->max_b_frames = 1; //ǰ��ο�֡
	context->pix_fmt = AV_PIX_FMT_YUV420P;//ԭʼ�����ʽ
	if (codec->id == AV_CODEC_ID_H264)//�������ٱ���
		av_opt_set(context->priv_data, "preset", "slow", 0);

	//�򿪽�����
	if (avcodec_open2(context, codec, NULL) < 0)
	{
		printf("couldn't open codec!\n");
		return -1;
	}

	//������ļ�
	FILE * outfp = fopen(filename,"wb");
	if (!outfp)
	{
		printf("couldn't open output file!\n");
		return -1;
	}

	//����֡�ռ�
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

	//����һ���ӵ���Ƶ����,֡��Ϊ25��֮ǰ���õ�
	AVPacket pkt;
	uint8_t endcode[] = { 0, 0, 1, 0xb7 };
	int got_output;
	for (int i = 0; i < 25*5; i++)
	{
		av_init_packet(&pkt);
		pkt.data = NULL; //�����������
		pkt.size = 0;

		fflush(stdout);

		//���֡�����Ƿ��д
		retCode = av_frame_make_writable(frame);
		if (retCode < 0){
			return -1;
		}

		//����һ֡����
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

		//���б���
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

	//����ʣ�µ�֡��û�д���ģ�
	for (int i = 1; i < got_output; i++)
	{
		//���б���
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
