#include<stdio.h>
#include<string.h>
#if _MSC_VER
#define snprintf _snprintf
#endif
/*
About:
	从视频中截取一段视频
	相关函数：
		跳一段时间
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
	//注册库
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();

	AVOutputFormat * ofmt = NULL;
	AVFormatContext * ifmtContext = NULL, *ofmtContext = NULL;
	AVPacket pkt;
	int ret, i;
	char errBuff[1024] = { 0 };
	//获取输入文件上下文
	if ((ret = avformat_open_input(&ifmtContext, srcfile, 0, 0)) < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "open source file failure.\n");
		return -1;
	}
	//查找流
	if ((ret = avformat_find_stream_info(ifmtContext, 0)) < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "find stream info failure.\n");
		return -1;
	}
	//输出输入文件细腻系
	av_dump_format(ifmtContext, 0, srcfile, 0);
	//创建输出文件上下文
	avformat_alloc_output_context2(&ofmtContext, NULL, NULL, dstfile);
	if (!ofmtContext)
	{
		av_log(NULL, AV_LOG_ERROR, "alloc output context failure.\n");
		return -1;
	}

	ofmt = ofmtContext->oformat;
	//拷贝流
	for (i = 0; i < ifmtContext->nb_streams; i++)
	{
		//获取输入流，创建对应的输出流
		AVStream * in_stream = ifmtContext->streams[i];
		AVStream * out_stream = avformat_new_stream(ofmtContext, in_stream->codec->codec);
		if (!out_stream)
		{
			av_log(NULL, AV_LOG_ERROR, "new stream failure.\n");
			return -1;
		}
		//拷贝codec信息
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
	//显示输出信息
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
	//写出文件头
	ret = avformat_write_header(ofmtContext, NULL);
	if (ret < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "io write file header failure.\n");
		return -1;
	}
	//调整输出位置
	ret = av_seek_frame(ifmtContext, -1, stattime*AV_TIME_BASE, AVSEEK_FLAG_ANY);
	if (ret < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "seek frame failure.\n");
		return -1;
	}
	//同步时间戳
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
		//截取结束
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
		//调整时间戳
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
		//写出帧数据
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
	//写出文件尾
	av_write_trailer(ofmtContext);

	avformat_close_input(&ifmtContext);

	if (ofmtContext && !(ofmt->flags & AVFMT_NOFILE))
	{
		avio_closep(&ofmtContext->pb);
	}
	avformat_free_context(ofmtContext);

	return 0;
}
