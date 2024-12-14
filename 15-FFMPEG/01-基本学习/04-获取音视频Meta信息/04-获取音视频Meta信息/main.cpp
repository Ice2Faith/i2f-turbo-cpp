#include<stdio.h>

/*
About:
��ӡ����Ƶ����Ϣ��
Ҳ����Meta��Ϣ
��غ�����
��FFMPEG�ı�����͸�ʽ��������ע�����
av_register_all()
������Ƶ�ļ����Զ����ݺ�׺
int avformat_open_input(AVFormatContext **,char * openFileUrl,NULL,NULL)
�������ṹ�壬�򿪵��ļ������ļ���ʽ�������в���
����ֵ��С��0ʧ��
�ر�����Ƶ�ļ�
avformat_close_input()

��ӡ����Ƶ��meta��Ϣ
int av_dump_format(AVFormatContext *,int indexStream,char * fileNameUrl,int ioType)
�������ļ���ʽ�ṹ�壬����ţ���������ļ������������֪ʶ


*/
#define __STDC_CONSTANT_MACROS

extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>
}



int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		printf("�����һ��ִ��ý���ļ��Ĳ�����\n");
		system("pause");
		return 0;
	}
	char * inFile = argv[1];
	//������־�����ע���
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();

	//���ļ������ʽ������
	AVFormatContext* fmtContext = NULL;
	int ret = avformat_open_input(&fmtContext, inFile, NULL, NULL);
	if (ret<0)
	{
		char buffer[1024];
		av_make_error_string(buffer, 1024 - 1, ret);
		// av_err2str(ret) ��CPP������ʹ�ò����У�ʹ���������ַ���
		av_log(NULL, AV_LOG_ERROR, "open file failure:%s\n",buffer);
		return -1;
	}
	//��ӡ�ļ�mate��Ϣ
	av_dump_format(fmtContext, 0, inFile, 0);

	avformat_close_input(&fmtContext);
	system("pause");
	return 0;
}
