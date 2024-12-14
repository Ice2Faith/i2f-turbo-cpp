#include<stdio.h>

/*
About:

*/
#define __STDC_CONSTANT_MACROS

/*
About:
ý���ʽת��
��ʵ���ǻ�һ����ǣ��ڲ��Ĳ��������ݶ��ǲ����
��غ�����
��������ļ���������
int avformat_alloc_output_context2()
�ͷŷ����������
int avformat_free_context()
������
�����µ���
int avformat_new_stream()
������
������Ƶ��Ϣ����
int avcodec_parameters_copy()
������
д�������ļ���Ϣͷ
avformat_write_header()
д�����ݣ�ͨ��ʹ�ú���
av_write_frame()/av_interleaved_write_frame()
д���ļ�β����Ȼ�еĸ�ʽû�У�����Ҳ����ʹ�ã���Ϊ�ײ�ʵ�־��ǿյĵ���
av_write_trailer()
���裺
����̨��ȡ����
���ļ�
�����ý����Ϣ
��ȡ��
��ȡ��Ƶ���ݲ��������
*/
extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>
}

int main(int argc, char * argv[])
{
	//������־����Ϳ�ע��
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();

	//��ȡ����̨����
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
	//������Ƶ�ļ�
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

	//��ӡý����Ϣ
	av_dump_format(ifmtContext,0,src,0);

	//�������������
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
	//���������ļ���
	for (int i = 0; i<ifmtContext->nb_streams; i++)
	{
		AVStream * out_stream;
		AVStream * in_stream = ifmtContext->streams[i];
		AVCodecParameters * in_codecpar = in_stream->codecpar;
		//������Ƶ��Ƶ��Ļ��֮�����
		if (in_codecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
			in_codecpar->codec_type != AVMEDIA_TYPE_VIDEO &&
			in_codecpar->codec_type != AVMEDIA_TYPE_SUBTITLE)
		{
			stream_mapping[i] = -1;
			continue;
		}
		stream_mapping[i] = stream_index++;
		//�����µ������
		out_stream = avformat_new_stream(ofmtContext, NULL);
		if (!out_stream)
		{
			av_log(NULL, AV_LOG_ERROR, "create out stream failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
			return -1;
		}
		//�������Ĳ���
		ret = avcodec_parameters_copy(out_stream->codecpar, in_codecpar);
		if (ret<0)
		{
			av_log(NULL, AV_LOG_ERROR, "copy codec params failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
			return -1;
		}

		out_stream->codecpar->codec_tag = 0;
	}
	//������ļ�����Ϣ
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
	//����ļ�ͷ���ļ���ͨ��������
	ret = avformat_write_header(ofmtContext, NULL);
	if (ret<0)
	{
		av_log(NULL, AV_LOG_ERROR, "write file header failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
		return -1;
	}

	while (1)
	{
		AVStream * in_stream, *out_stream;
		//��ȡԴ���ݰ�
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
		//ת������Ƶ�̶ȣ�����ʱ���
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		//log_packet(ofmtContext, &pkt, "out");
		//д�����ݰ�������ļ�
		ret = av_interleaved_write_frame(ofmtContext, &pkt);
		if (ret<0)
		{
			av_log(NULL, AV_LOG_ERROR, "muxing packet failure:%s\n", av_make_error_string(errBuff, 1024 - 1, ret));
			break;
		}
		av_packet_unref(&pkt);
	}
	//д���ļ�β
	av_write_trailer(ofmtContext);
	//�ͷ���Դ
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
