#include<stdio.h>

/*
About:

*/
#define __STDC_CONSTANT_MACROS

/*
About:
媒体格式转换
其实就是换一个外壳，内部的参数和数据都是不变的
相关函数：
分配输出文件的上下文
int avformat_alloc_output_context2()
释放分配的上下文
int avformat_free_context()
参数：
创建新的流
int avformat_new_stream()
参数：
拷贝视频信息参数
int avcodec_parameters_copy()
参数：
写出生成文件信息头
avformat_write_header()
写出数据，通常使用后者
av_write_frame()/av_interleaved_write_frame()
写出文件尾，虽然有的格式没有，但是也可以使用，因为底层实现就是空的调用
av_write_trailer()
步骤：
控制台读取数据
打开文件
输出多媒体信息
获取流
获取音频数据并输出保存
*/
extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>
}

int main(int argc, char * argv[])
{
	//设置日志级别和库注册
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();

	//获取控制台参数
	if (argc<3)
	{
		av_log(NULL, AV_LOG_ERROR, "argument not enough\n");
		return -1;
	}

	char * src = argv[1];
	char * dst = argv[2];
	if (!src || !dst)
	{
		av_log(NULL, AV_LOG_ERROR, "argument error\n");
		return -1;
	}
	//打开音视频文件
	AVFormatContext * ifmtContext = NULL, * ofmtContext;
	AVOutputFormat * ofmt = NULL;
	AVPacket pkt;
	int stream_index = 0;
	int * stream_mapping = NULL;
	int stream_mapping_size = 0;
	char errBuff[1024] = { 0 };
	

	int ret = avformat_open_input(&ifmtContext, src, NULL, NULL);
	if (ret<0)
	{
		av_log(NULL, AV_LOG_ERROR, "open file failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
		return -1;
	}

	if ((ret = avformat_find_stream_info(ifmtContext, 0))<0)
	{
		av_log(NULL, AV_LOG_ERROR, "find stream failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
		return -1;
	}

	//打印媒体信息
	av_dump_format(ifmtContext,0,src,0);

	//创建输出上下文
	avformat_alloc_output_context2(&ofmtContext, NULL, NULL, dst);
	if (!ofmtContext)
	{
		av_log(NULL, AV_LOG_ERROR, "create output context failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
		return -1;
	}

	stream_mapping_size = ifmtContext->nb_streams;
	stream_mapping = (int *)av_mallocz_array(stream_mapping_size, sizeof(*stream_mapping));
	if (!stream_mapping)
	{
		av_log(NULL, AV_LOG_ERROR, "alloc stream mapping failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
		return -1;
	}

	ofmt = ofmtContext->oformat;
	//遍历输入文件流
	for (int i = 0; i<ifmtContext->nb_streams; i++)
	{
		AVStream * out_stream;
		AVStream * in_stream = ifmtContext->streams[i];
		AVCodecParameters * in_codecpar = in_stream->codecpar;
		//过滤视频音频字幕流之外的流
		if (in_codecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
			in_codecpar->codec_type != AVMEDIA_TYPE_VIDEO &&
			in_codecpar->codec_type != AVMEDIA_TYPE_SUBTITLE)
		{
			stream_mapping[i] = -1;
			continue;
		}
		stream_mapping[i] = stream_index++;
		//创建新的输出流
		out_stream = avformat_new_stream(ofmtContext, NULL);
		if (!out_stream)
		{
			av_log(NULL, AV_LOG_ERROR, "create out stream failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
			return -1;
		}
		//复制流的参数
		ret = avcodec_parameters_copy(out_stream->codecpar, in_codecpar);
		if (ret<0)
		{
			av_log(NULL, AV_LOG_ERROR, "copy codec params failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
			return -1;
		}

		out_stream->codecpar->codec_tag = 0;
	}
	//输出新文件的信息
	av_dump_format(ofmtContext, 0, dst, 1);

	if (!(ofmt->flags & AVFMT_NOFILE))
	{
		ret = avio_open(&ofmtContext->pb, dst, AVIO_FLAG_WRITE);
		if (ret<0)
		{
			av_log(NULL, AV_LOG_ERROR, "open output file failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
			return -1;
		}
	}
	//输出文件头到文件，通过上下文
	ret = avformat_write_header(ofmtContext, NULL);
	if (ret<0)
	{
		av_log(NULL, AV_LOG_ERROR, "write file header failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
		return -1;
	}

	while (1)
	{
		AVStream * in_stream, *out_stream;
		//读取源数据包
		ret = av_read_frame(ifmtContext, &pkt);
		if (ret<0)
		{
			av_log(NULL, AV_LOG_ERROR, "read src frame failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
			break;
		}
		in_stream = ifmtContext->streams[pkt.stream_index];
		if (pkt.stream_index >= stream_mapping_size ||
			stream_mapping[pkt.stream_index]<0)
		{
			av_packet_unref(&pkt);
			continue;
		}

		pkt.stream_index = stream_mapping[pkt.stream_index];
		out_stream = ofmtContext->streams[pkt.stream_index];
		//log_packet(ifmtContext, &pkt, "in");
		//转换音视频刻度，对齐时间戳
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		//log_packet(ofmtContext, &pkt, "out");
		//写出数据包到输出文件
		ret = av_interleaved_write_frame(ofmtContext, &pkt);
		if (ret<0)
		{
			av_log(NULL, AV_LOG_ERROR, "muxing packet failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
			break;
		}
		av_packet_unref(&pkt);
	}
	//写出文件尾
	av_write_trailer(ofmtContext);
	//释放资源
	avformat_close_input(&ifmtContext);
	if (ofmtContext && !(ofmt->flags & AVFMT_NOFILE))
		avio_closep(&ofmtContext->pb);

	avformat_free_context(ofmtContext);

	av_freep(&stream_mapping);

	if (ret<0 && ret != AVERROR_EOF)
	{
		av_log(NULL, AV_LOG_ERROR, "release resource failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
		return -1;
	}

	return 0;
}
