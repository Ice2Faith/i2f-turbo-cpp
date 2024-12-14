#include<stdio.h>

/*
About:
思路：将一个媒体文件中的所有除了音频的流和另外一个媒体文件中的音频流进行合并
这里给出的实例中，只考虑音频比视频长的情况，音频会被截断
*/
#define __STDC_CONSTANT_MACROS

extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>
}



int main(int argc, char * argv[])
{
	//参数检查
	if (argc < 4)
	{
		printf("参数：含有视频的媒体 含有音频的媒体 最终的文件名\n");
		system("pause");
		return 0;
	}

	char * srcVideo =argv[1];
	char * srcAudio =argv[2];
	char * drtVideo =argv[3]; 

	if (!srcAudio || !srcVideo || !drtVideo)
	{
		av_log(NULL,AV_LOG_ERROR,"argument error!");
		return -1;
	}

	//初始化AV
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();

	char errBuf[1024] = { 0 };

	//分别打开源输入媒体文件
	AVFormatContext * fmtCxtSrcVideo = NULL;
	AVFormatContext * fmtCxtSrcAudio = NULL;

	int retCode = avformat_open_input(&fmtCxtSrcVideo, srcVideo, NULL, NULL);
	if (retCode < 0)
	{
		av_make_error_string(errBuf, sizeof(errBuf)-1, retCode);
		av_log(NULL, AV_LOG_ERROR, "open source video failure:%s\n", errBuf);
		return -1;
	}

	retCode = avformat_open_input(&fmtCxtSrcAudio, srcAudio, NULL, NULL);
	if (retCode < 0)
	{
		av_make_error_string(errBuf, sizeof(errBuf)-1, retCode);
		av_log(NULL, AV_LOG_ERROR, "open source audio failure:%s\n", errBuf);
		return -1;
	}

	//打印输入文件信息
	av_dump_format(fmtCxtSrcVideo, 0, srcVideo, 0);
	av_dump_format(fmtCxtSrcAudio, 0, srcAudio, 0);


	//打开输出文件
	AVFormatContext * fmtCxtDrt = NULL;
	avformat_alloc_output_context2(&fmtCxtDrt, NULL, NULL, drtVideo);
	if (!fmtCxtDrt)
	{
		av_log(NULL, AV_LOG_ERROR, "create out context error\n");
		avformat_close_input(&fmtCxtSrcVideo);
		avformat_close_input(&fmtCxtSrcAudio);
		return -1;
	}

	//获取流索引
	int inVdoMapSize = 0;
	int inVdoMap[10] = { 0 };
	int inAdoMapSize = 0;
	int inAdoMap[10] = { 0 };
	for (int i = 0; i < fmtCxtSrcVideo->nb_streams; i++) //视频文件中，拿取排出音频的所有流
	{
		AVStream * in_stream = fmtCxtSrcVideo->streams[i];
		AVCodecParameters * in_codecpar = in_stream->codecpar;
		//过滤视频音频字幕流之外的流
		if (in_codecpar->codec_type != AVMEDIA_TYPE_AUDIO)
		{
			inVdoMap[inVdoMapSize++] = i;
		}
	}
	for (int i = 0; i < fmtCxtSrcAudio->nb_streams; i++) //音频文件中，只拿取音频的流
	{
		AVStream * in_stream = fmtCxtSrcAudio->streams[i];
		AVCodecParameters * in_codecpar = in_stream->codecpar;
		//过滤视频音频字幕流之外的流
		if (in_codecpar->codec_type == AVMEDIA_TYPE_AUDIO )
		{
			inAdoMap[inAdoMapSize++] = i;
		}
	}

	int stream_mapping_size = 0;
	int * stream_mapping = NULL;
	stream_mapping_size = inAdoMapSize + inVdoMapSize;
	stream_mapping = (int *)av_mallocz_array(stream_mapping_size, sizeof(*stream_mapping));
	if (!stream_mapping)
	{
		av_log(NULL, AV_LOG_ERROR, "alloc stream mapping failure\n");
		return -1;
	}

	int stream_index = 0;
	//复制流参数
	for (int i = 0; i < inVdoMapSize; i++)
	{
		AVStream * out_stream;
		AVStream * in_stream = fmtCxtSrcVideo->streams[inVdoMap[i]];
		AVCodecParameters * in_codecpar = in_stream->codecpar;
		
		stream_mapping[i] = stream_index++;
		//创建新的输出流
		out_stream = avformat_new_stream(fmtCxtDrt, NULL);
		if (!out_stream)
		{
			av_log(NULL, AV_LOG_ERROR, "create out stream failure\n");
			return -1;
		}
		//复制流的参数
		retCode = avcodec_parameters_copy(out_stream->codecpar, in_codecpar);
		if (retCode<0)
		{
			av_log(NULL, AV_LOG_ERROR, "copy codec params failure:%s\n", av_make_error_string(errBuf, 1024 - 1, retCode));
			return -1;
		}
		out_stream->codecpar->codec_tag = 0;
	}
	for (int i = 0; i < inAdoMapSize; i++)
	{
		AVStream * out_stream;
		AVStream * in_stream = fmtCxtSrcAudio->streams[inAdoMap[i]];
		AVCodecParameters * in_codecpar = in_stream->codecpar;

		stream_mapping[inAdoMapSize+i] = stream_index++;
		//创建新的输出流
		out_stream = avformat_new_stream(fmtCxtDrt, NULL);
		if (!out_stream)
		{
			av_log(NULL, AV_LOG_ERROR, "create out stream failure\n");
			return -1;
		}
		//复制流的参数
		retCode = avcodec_parameters_copy(out_stream->codecpar, in_codecpar);
		if (retCode<0)
		{
			av_log(NULL, AV_LOG_ERROR, "copy codec params failure:%s\n", av_make_error_string(errBuf, 1024 - 1, retCode));
			return -1;
		}
		out_stream->codecpar->codec_tag = 0;
	}

	//输出新文件的信息
	av_dump_format(fmtCxtDrt, 0, drtVideo, 1);

	AVOutputFormat * ofmt = NULL;
	ofmt = fmtCxtDrt->oformat;
	if (!(ofmt->flags & AVFMT_NOFILE))
	{
		retCode = avio_open(&fmtCxtDrt->pb, drtVideo, AVIO_FLAG_WRITE);
		if (retCode<0)
		{
			av_log(NULL, AV_LOG_ERROR, "open output file failure:%s\n", av_make_error_string(errBuf, 1024 - 1, retCode));
			return -1;
		}
	}

	//输出文件头到文件，通过上下文
	retCode = avformat_write_header(fmtCxtDrt, NULL);
	if (retCode<0)
	{
		av_log(NULL, AV_LOG_ERROR, "write file header failure:%s\n", av_make_error_string(errBuf, 1024 - 1, retCode));
		return -1;
	}



	//输出混流数据
	AVPacket pktVdo;
	av_init_packet(&pktVdo);
	pktVdo.data = NULL;
	pktVdo.size = 0;
	AVPacket pktAdo;
	av_init_packet(&pktAdo);
	pktAdo.data = NULL;
	pktAdo.size = 0;

	//拷贝上面需要的流，进行流的合并
	AVStream * in_stream, *out_stream;
	int endTime = 0;
	while (av_read_frame(fmtCxtSrcVideo, &pktVdo) >= 0)
	{
		
		for (int i = 0; i < inVdoMapSize; i++)
		{
			if (pktVdo.stream_index == inVdoMap[i])
			{
				in_stream = fmtCxtSrcVideo->streams[pktVdo.stream_index];
				int ptime = pktVdo.pts*av_q2d(in_stream->time_base);
				if (ptime>endTime)
					endTime = ptime;
				pktVdo.stream_index = stream_mapping[i];
				out_stream = fmtCxtDrt->streams[i];
				pktVdo.pts = av_rescale_q_rnd(pktVdo.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
				pktVdo.dts = av_rescale_q_rnd(pktVdo.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
				pktVdo.duration = av_rescale_q(pktVdo.duration, in_stream->time_base, out_stream->time_base);
				pktVdo.pos = -1;
				retCode = av_interleaved_write_frame(fmtCxtDrt, &pktVdo);
				if (retCode<0)
				{
					av_log(NULL, AV_LOG_ERROR, "muxing packet failure:%s\n", av_make_error_string(errBuf, 1024 - 1, retCode));
				}
			}
		}
		
		av_packet_unref(&pktVdo);
	}
	while (av_read_frame(fmtCxtSrcAudio, &pktAdo) >= 0)
	{
		for (int j = 0; j < inAdoMapSize; j++)
		{
			if (pktAdo.stream_index == inAdoMap[j])
			{
				in_stream = fmtCxtSrcAudio->streams[pktAdo.stream_index];
				int ptime = pktAdo.pts*av_q2d(in_stream->time_base);
				if (ptime>endTime)
				{
					av_packet_unref(&pktAdo);
					goto copyend;
				}

				pktAdo.stream_index = stream_mapping[inVdoMapSize + j];
				out_stream = fmtCxtDrt->streams[inVdoMapSize + j];
				pktAdo.pts = av_rescale_q_rnd(pktAdo.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
				pktAdo.dts = av_rescale_q_rnd(pktAdo.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
				pktAdo.duration = av_rescale_q(pktAdo.duration, in_stream->time_base, out_stream->time_base);
				pktAdo.pos = -1;
				retCode = av_interleaved_write_frame(fmtCxtDrt, &pktAdo);
				if (retCode<0)
				{
					av_log(NULL, AV_LOG_ERROR, "muxing packet failure:%s\n", av_make_error_string(errBuf, 1024 - 1, retCode));
				}

			}
		}
		av_packet_unref(&pktAdo);
	}
	copyend:
	av_write_trailer(fmtCxtDrt);
	if (fmtCxtDrt && !(ofmt->flags & AVFMT_NOFILE))
		avio_closep(&fmtCxtDrt->pb);
	avformat_free_context(fmtCxtDrt);
	av_freep(&stream_mapping);

	avformat_close_input(&fmtCxtSrcVideo);
	avformat_close_input(&fmtCxtSrcAudio);

	return 0;
}
