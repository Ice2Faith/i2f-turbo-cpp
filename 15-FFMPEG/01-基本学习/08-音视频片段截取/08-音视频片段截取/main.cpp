#include<stdio.h>
#include<string.h>
#if _MSC_VER
#define snprintf _snprintf
#endif
/*
About:
	����Ƶ�н�ȡһ����Ƶ
	��غ�����
		��һ��ʱ��
			av_seek_frame()

*/
#define __STDC_CONSTANT_MACROS

extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>
#include<libavutil/timestamp.h>
#include<libavcodec/avcodec.h>
}


int cut_video(int stattime, int endtime, char * srcfile, char *dstfile);
int main(int argc, char * argv[])
{
	if (argc < 5)
	{
		printf("command:starttime endtime srcfile dstfile\n");
		system("pause");
		return -1;
	}
	double starttime = atoi(argv[1]);
	double endtime = atoi(argv[2]);
	cut_video(starttime, endtime, argv[3], argv[4]);
	return 0;
}
int cut_video(int stattime, int endtime, char * srcfile, char *dstfile)
{
	//ע���
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();

	AVOutputFormat * ofmt = NULL;
	AVFormatContext * ifmtContext = NULL, *ofmtContext = NULL;
	AVPacket pkt;
	int ret, i;
	char errBuff[1024] = { 0 };
	//��ȡ�����ļ�������
	if ((ret = avformat_open_input(&ifmtContext, srcfile, 0, 0)) < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "open source file failure.\n");
		return -1;
	}
	//������
	if ((ret = avformat_find_stream_info(ifmtContext, 0)) < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "find stream info failure.\n");
		return -1;
	}
	//��������ļ�ϸ��ϵ
	av_dump_format(ifmtContext, 0, srcfile, 0);
	//��������ļ�������
	avformat_alloc_output_context2(&ofmtContext, NULL, NULL, dstfile);
	if (!ofmtContext)
	{
		av_log(NULL, AV_LOG_ERROR, "alloc output context failure.\n");
		return -1;
	}

	ofmt = ofmtContext->oformat;
	//������
	for (i = 0; i < ifmtContext->nb_streams; i++)
	{
		//��ȡ��������������Ӧ�������
		AVStream * in_stream = ifmtContext->streams[i];
		AVStream * out_stream = avformat_new_stream(ofmtContext, in_stream->codec->codec);
		if (!out_stream)
		{
			av_log(NULL, AV_LOG_ERROR, "new stream failure.\n");
			return -1;
		}
		//����codec��Ϣ
		ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
		if (ret < 0)
		{
			av_log(NULL, AV_LOG_ERROR, "copy context failure.\n");
			return -1;
		}
		out_stream->codec->codec_tag = 0;
		if (ofmtContext->oformat->flags & AVFMT_GLOBALHEADER)
			out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	}
	//��ʾ�����Ϣ
	av_dump_format(ofmtContext, 0, dstfile, 1);

	if (!(ofmt->flags & AVFMT_NOFILE))
	{
		ret = avio_open(&ofmtContext->pb, dstfile, AVIO_FLAG_WRITE);
		if (ret < 0)
		{
			av_log(NULL, AV_LOG_ERROR, "io open file failure.\n");
			return -1;
		}
	}
	//д���ļ�ͷ
	ret = avformat_write_header(ofmtContext, NULL);
	if (ret < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "io write file header failure.\n");
		return -1;
	}
	//�������λ��
	ret = av_seek_frame(ifmtContext, -1, stattime*AV_TIME_BASE, AVSEEK_FLAG_ANY);
	if (ret < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "seek frame failure.\n");
		return -1;
	}
	//ͬ��ʱ���
	int64_t * dts_start_from = (int64_t *)malloc(sizeof(int64_t)*ifmtContext->nb_streams);
	memset(dts_start_from, 0, sizeof(int64_t)*ifmtContext->nb_streams);

	int64_t * pts_start_from = (int64_t *)malloc(sizeof(int64_t)*ifmtContext->nb_streams);
	memset(pts_start_from, 0, sizeof(int64_t)*ifmtContext->nb_streams);

	while (1)
	{
		AVStream * in_stream, *out_stream;
		ret = av_read_frame(ifmtContext, &pkt);
		if (ret < 0)
			break;
		in_stream = ifmtContext->streams[pkt.stream_index];
		out_stream = ofmtContext->streams[pkt.stream_index];
		//��ȡ����
		if (av_q2d(in_stream->time_base)*pkt.pts>endtime)
		{
			av_free_packet(&pkt);
			break;
		}
		
		if (dts_start_from[pkt.stream_index] == 0)
		{
			dts_start_from[pkt.stream_index] = pkt.dts;
			
			printf("dts_start_from:%s\n", av_ts_make_string(errBuff, dts_start_from[pkt.stream_index]));
		}
		if (pts_start_from[pkt.stream_index] == 0)
		{
			pts_start_from[pkt.stream_index] = pkt.pts;
			printf("pts_start_from:%s\n", av_ts_make_string(errBuff, pts_start_from[pkt.stream_index]));
		}
		//����ʱ���
		pkt.pts = av_rescale_q_rnd(pkt.pts - pts_start_from[pkt.stream_index], in_stream->time_base, out_stream->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

		pkt.dts = av_rescale_q_rnd(pkt.dts - dts_start_from[pkt.stream_index], in_stream->time_base, out_stream->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

		if (pkt.pts < 0)
			pkt.pts = 0;
		if (pkt.dts < 0)
			pkt.dts = 0;

		pkt.duration = (int)av_rescale_q((int64_t)pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		//д��֡����
		ret = av_interleaved_write_frame(ofmtContext, &pkt);
		if (ret < 0)
		{
			av_log(NULL, AV_LOG_ERROR, "muxing packet failure.\n");
			break;
		}
		av_free_packet(&pkt);
	}
	free(dts_start_from);
	free(pts_start_from);
	//д���ļ�β
	av_write_trailer(ofmtContext);

	avformat_close_input(&ifmtContext);

	if (ofmtContext && !(ofmt->flags & AVFMT_NOFILE))
	{
		avio_closep(&ofmtContext->pb);
	}
	avformat_free_context(ofmtContext);

	return 0;
}
