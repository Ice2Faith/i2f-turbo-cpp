#include<stdio.h>

#define __STDC_CONSTANT_MACROS
extern "C"
{
#include<libavutil\avutil.h>
#include<libavformat\avformat.h>
}

/*
About:
��ȡ��ý�����Ƶ����
Start code
����ÿһ֡��Ƶ�������룬�������ܻ�ȡÿһ֡������
SPS/PPS
�����ʶ��������ֱ���֡�ʵ�
һ����˵ֻ��Ҫһ����ͬһ���ֱ��ʺ�֡�ʣ�����������ڶ�ֱ��ʵ�������Ǿ��ж��SPS��һ���ڹؼ�֮֡ǰ
codec->extradata
��ȡ���ݣ��ڱ���������չ���ݰ���
��غ�����
��ʼ�����ݰ��ṹ�壺
av_init_packet()
�ҵ���õ���
int av_find_best_stream()
��������ʽ�����ģ������ͣ��������ţ�����������ţ��������ı����������־
�����н����ݰ����ݻ�ȡ��
int av_read_frame()
��������ʽ�����ģ����ݰ��ṹ��
������ݰ����ü���������Ϊ0ʱ�����Զ��ͷ���Դ����ֹ�ڴ�й©
int av_packet_unref()
���������ݰ��ṹ��
���裺
����̨��ȡ����
���ļ�
�����ý����Ϣ
��ȡ��
��ȡ��Ƶ���ݲ��������
*/
int h264_extradata_to_annexb(const uint8_t * codec_extradata, const int codec_extradata_size, AVPacket * out_extradata, int padding);
void h264_mp4toannexb(AVFormatContext * fmtContext, AVPacket * pkt, FILE * fdst);
int alloc_and_copy(AVPacket * out,
	const uint8_t * sps_pps, uint32_t sps_pps_size,
	const uint8_t * in, uint32_t in_size);
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
	AVFormatContext * fmtContext = NULL;
	char errBuff[1024] = { 0 };

	int ret = avformat_open_input(&fmtContext, src, NULL, NULL);
	if (ret<0)
	{
		av_make_error_string(errBuff, 1024 - 1, ret);
		av_log(NULL, AV_LOG_ERROR, "open file failure:%s\n", errBuff);
		return -1;
	}
	//��ӡý����Ϣ
	av_dump_format(fmtContext,0,src,0);
	//��ȡ��Ƶ��
	ret = av_find_best_stream(fmtContext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	if (ret<0)
	{
		av_log(NULL, AV_LOG_ERROR, "get stream error\n");
		avformat_close_input(&fmtContext);
		return -1;
	}
	//������ļ�
	FILE * fdst = fopen(dst, "wb");
	if (!fdst)
	{
		av_log(NULL, AV_LOG_ERROR, "write file error\n");
		avformat_close_input(&fmtContext);
		return -1;
	}
	//��ȡ��Ŀ��������
	int videoIndex = ret;
	//��ȡ���ݰ���д���ļ�
	AVPacket pkt;
	av_init_packet(&pkt);
	pkt.data = NULL;
	pkt.size = 0;
	while (av_read_frame(fmtContext, &pkt) >= 0)
	{
		//�ж��Ƿ����Ҫ���������ݰ�
		if (pkt.stream_index == videoIndex)
		{
			//����startcode��spspps
			h264_mp4toannexb(fmtContext, &pkt, fdst);
		}
		//���ټ������Զ��ͷſռ�
		av_packet_unref(&pkt);
	}
	fclose(fdst);
	avformat_close_input(&fmtContext);
	return 0;
}
void h264_mp4toannexb(AVFormatContext * fmtContext, AVPacket * pkt, FILE * fdst)
{
	AVPacket * out = NULL;
	AVPacket spsppsPkt;

	int len;
	uint8_t uintType;
	int32_t nal_size;
	uint32_t cumul_size = 0;
	const uint8_t *buffer;
	const uint8_t * buffer_end;
	int buffer_size;
	int ret = 0, i;

	out = av_packet_alloc();
	//���ݻ����ʼ��
	buffer = pkt->data;
	buffer_size = pkt->size;
	buffer_end = pkt->data + pkt->size;
	//��ȡÿһ֡����
	do{
		ret = AVERROR(EINVAL);
		if (buffer + 4>buffer_end)
			goto fail;
		//ǰ�ĸ��ֽ���h264���Ĵ�С��������ж������
		for (nal_size = 0, i = 0; i<4; i++)
		{
			nal_size = (nal_size << 8) | buffer[i];
		}
		//�������ֽ�
		buffer += 4;

		uintType = *buffer & 0x1f;
		//nal��Ԫ��С
		if (nal_size>buffer_end - buffer || nal_size<0)
			goto fail;

		//�����һ���ؼ�֡
		if (uintType == 5)
		{
			//����չ���ݻ�ȡsps��pps
			h264_extradata_to_annexb(fmtContext->streams[pkt->stream_index]->codec->extradata,
				fmtContext->streams[pkt->stream_index]->codec->extradata_size,
				&spsppsPkt,
				AV_INPUT_BUFFER_PADDING_SIZE);
			//Ϊ��������������
			if ((ret = alloc_and_copy(out, spsppsPkt.data, spsppsPkt.size, buffer, nal_size))<0)
				goto fail;
		}
		else
		{
			if ((ret = alloc_and_copy(out, NULL, 0, buffer, nal_size))<0)
				goto fail;

		}
		//�����Ŀ���ļ�
		len = fwrite(out->data, 1, out->size, fdst);
		if (len != out->size)
		{
			av_log(NULL, AV_LOG_WARNING, "write file maybe wrong\n");
		}
		fflush(fdst);

		buffer += nal_size;
		cumul_size += nal_size + 4;
	} while (cumul_size<buffer_size);

fail:
	return;
}
#define AV_WB32(p,val) do { \
	uint32_t d = (val); \
	((uint8_t*)(p))[3] = (d); \
	((uint8_t*)(p))[3] = (d) >> 8; \
	((uint8_t*)(p))[3] = (d) >> 16; \
	((uint8_t*)(p))[3] = (d) >> 24; \
}while (0);
//����������
int alloc_and_copy(AVPacket * out,
	const uint8_t * sps_pps, uint32_t sps_pps_size,
	const uint8_t * in, uint32_t in_size)
{
	uint32_t offset = out->size;
	uint8_t nal_header_size = offset ? 3 : 4;//start code��sps pps 4:00 00 00 01 ��spspps:3 00 00 01
	int err;
	//����
	err = av_grow_packet(out, sps_pps_size + in_size + nal_header_size);
	if (err<0)
		return err;
	//�����sps���򿽱�����
	if (sps_pps)
		memcpy(out->data + offset, sps_pps, sps_pps_size);
	//����ԭʼ����
	memcpy(out->data + sps_pps_size + nal_header_size + offset, in, in_size);
	//����������
	if (!offset)
	{
		AV_WB32(out->data + sps_pps_size, 1);
	}
	else
	{
		(out->data + offset + sps_pps_size)[0] = 0;
		(out->data + offset + sps_pps_size)[1] = 0;
		(out->data + offset + sps_pps_size)[2] = 1;
	}
	return 0;
}
#define AV_RB16(x)\
	((((const uint8_t*)(x))[0] << 8) | \
	((const uint8_t*)(x))[1])
int h264_extradata_to_annexb(const uint8_t * codec_extradata, const int codec_extradata_size, AVPacket * out_extradata, int padding)
{
	uint16_t uint_size;
	uint64_t total_size = 0;
	uint8_t * out = NULL, uint_nb, sps_done = 0, sps_seen = 0, pps_seen = 0, sps_offset = 0, pps_offset = 0;
	const uint8_t * extradata = codec_extradata + 4;//������ͷ���ĸ��ֽ�
	static const uint8_t nalu_header[4] = { 0, 0, 0, 1 };//start code
	int length_size = (*extradata++ & 0x3) + 1;//��־sps pps���ֽڳ���

	sps_offset = pps_offset = -1;
	uint_nb = *extradata++ & 0x1f;//��ȡsps pps�ĸ���
	if (!uint_nb)
	{
		goto pps;
	}
	else
	{
		sps_offset = 0;
		sps_seen = 1;
	}
	while (uint_nb--)//����ÿ�� sps pps
	{
		int err;
		uint_size = AV_RB16(extradata);//ȡsps pps�ĳ���
		total_size += uint_size + 4;//����start code ����

		if (total_size>INT_MAX - padding)
		{
			av_log(NULL, AV_LOG_ERROR, "extradata size too big\n");
			av_free(out);
			return AVERROR(EINVAL);
		}
		if (extradata + 2 + uint_size>codec_extradata + codec_extradata_size)
		{
			av_log(NULL, AV_LOG_ERROR, "packet header is not contained in extradata\n");
			av_free(out);
			return AVERROR(EINVAL);
		}
		if ((err = av_reallocp(&out, total_size + padding))<0)//������ռ����
			return err;
		memcpy(out + total_size - uint_size - 4, nalu_header, 4);//����start code��sps pps����
		memcpy(out + total_size - uint_size, extradata + 2, uint_size);
		extradata += 2 + uint_size;
	pps:
		if (!uint_nb && !sps_done++)
		{
			uint_nb = *extradata++;
			if (uint_nb)
			{
				pps_offset = total_size;
				pps_seen = 1;
			}
		}
	}
	if (out)
		memset(out + total_size, 0, padding);
	if (!pps_seen)
		av_log(NULL, AV_LOG_WARNING, "pps nalu missing or invalid\n");

	out_extradata->data = out;
	out_extradata->size = total_size;

	return length_size;
}