#include<stdio.h>

/*
About:
��ȡ��ý�����Ƶ����
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
#define __STDC_CONSTANT_MACROS
extern "C"
{
	#include<libavutil/log.h>
	#include<libavformat/avformat.h>
}
//���adtsͷ���������������ܲ���
void adtsHeader(unsigned char * szAdtsHeader, int dataLen);
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

	char * srcFile = argv[1];
	char * dstFile = argv[2];
	if (!srcFile || !dstFile)
	{
		av_log(NULL, AV_LOG_ERROR, "argument error\n");
		return -1;
	}
	//������Ƶ�ļ�
	AVFormatContext * fmtContext = NULL;
	char errBuff[1024] = { 0 };

	int ret = avformat_open_input(&fmtContext, srcFile, NULL, NULL);
	if (ret<0)
	{
		av_make_error_string(errBuff, 1024 - 1, ret);
		av_log(NULL, AV_LOG_ERROR, "open file failure:%s\n", errBuff);
		return -1;
	}
	//��ӡý����Ϣ
	av_dump_format(fmtContext,0,srcFile,0);
	//��ȡ��Ƶ��
	ret = av_find_best_stream(fmtContext, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (ret<0)
	{
		av_log(NULL, AV_LOG_ERROR, "get stream error\n");
		avformat_close_input(&fmtContext);
		return -1;
	}
	//��ȡ��Ŀ��������
	int audioIndex = ret;
	//������ļ�
	FILE * fdstFile = fopen(dstFile, "wb");
	if (!fdstFile)
	{
		av_log(NULL, AV_LOG_ERROR, "write file error\n");
		avformat_close_input(&fmtContext);
		return -1;
	}
	
	//��ȡ���ݰ���д���ļ�
	AVPacket pkt;
	av_init_packet(&pkt);
	while (av_read_frame(fmtContext, &pkt) >= 0)
	{
		//�ж��Ƿ����Ҫ���������ݰ�
		if (pkt.stream_index == audioIndex)
		{
			//д��adtsHeader�����������ò���������
			char adts_header_buffer[7];
			adtsHeader((unsigned char *)adts_header_buffer, pkt.size);
			fwrite(adts_header_buffer, 1, 7, fdstFile);
			//д���ļ�
			int len = fwrite(pkt.data, 1, pkt.size, fdstFile);
			if (len != pkt.size)
			{
				av_log(NULL, AV_LOG_WARNING, "write file maybe wrong\n");
			}
		}
		//���ټ������Զ��ͷſռ�
		av_packet_unref(&pkt);
	}
	fclose(fdstFile);
	avformat_close_input(&fmtContext);
	return 0;
}

//���adtsͷ���������������ܲ���
void adtsHeader(unsigned char * szAdtsHeader, int dataLen)
{
	int audio_object_type = 2;
	int sampling_frequency_index = 7;
	int channel_config = 2;
	int adtsLen = dataLen + 7;
	//ͬ���ֶ�:0xfff
	szAdtsHeader[0] = 0xff;
	szAdtsHeader[1] = 0xf0;
	//MPEG�汾
	szAdtsHeader[1] |= (0 << 3);
	//Layer:0
	szAdtsHeader[1] |= (0 << 1);
	//protection absent:1
	szAdtsHeader[1] |= 1;
	//profile
	szAdtsHeader[2] = (audio_object_type - 1) << 6;
	szAdtsHeader[2] |= (sampling_frequency_index & 0x0f) << 2;
	//private bit :0
	szAdtsHeader[2] |= (0 << 1);
	//channel config
	szAdtsHeader[2] |= (channel_config & 0x04) >> 2;
	szAdtsHeader[3] |= (channel_config & 0x03) << 6;
	//original:0
	szAdtsHeader[3] |= (0 << 5);
	//home:0
	szAdtsHeader[3] |= (0 << 4);
	//copyright id bit:0
	szAdtsHeader[3] |= (0 << 3);
	//copyright id start:0
	szAdtsHeader[3] |= (0 << 2);
	//frame length
	szAdtsHeader[3] |= (adtsLen & 0x1800) >> 11;
	szAdtsHeader[4] |= (uint8_t)((adtsLen & 0x7f8) >> 3);
	szAdtsHeader[5] |= (uint8_t)((adtsLen & 0x7) << 5);
	//buffer fullness :0x7ff
	szAdtsHeader[5] |= 0x1f;
	szAdtsHeader[6] = 0xfc;

};
