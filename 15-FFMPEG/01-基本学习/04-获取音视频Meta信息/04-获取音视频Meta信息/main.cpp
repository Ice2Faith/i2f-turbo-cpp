#include<stdio.h>

/*
About:
打印音视频的信息，
也就是Meta信息
相关函数：
将FFMPEG的编解码库和格式库网络库等注册进来
av_register_all()
打开音视频文件，自动根据后缀
int avformat_open_input(AVFormatContext **,char * openFileUrl,NULL,NULL)
参数：结构体，打开的文件名，文件格式，命令行参数
返回值：小于0失败
关闭音视频文件
avformat_close_input()

打印音视频的meta信息
int av_dump_format(AVFormatContext *,int indexStream,char * fileNameUrl,int ioType)
参数：文件格式结构体，流序号，输入输出文件名，输入输出知识


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
		printf("请添加一个执行媒体文件的参数！\n");
		system("pause");
		return 0;
	}
	char * inFile = argv[1];
	//设置日志级别和注册库
	av_log_set_level(AV_LOG_DEBUG);
	av_register_all();

	//打开文件放入格式上下文
	AVFormatContext* fmtContext = NULL;
	int ret = avformat_open_input(&fmtContext, inFile, NULL, NULL);
	if (ret<0)
	{
		char buffer[1024];
		av_make_error_string(buffer, 1024 - 1, ret);
		// av_err2str(ret) 在CPP中这样使用不可行，使用上面这种方法
		av_log(NULL, AV_LOG_ERROR, "open file failure:%s\n",buffer);
		return -1;
	}
	//打印文件mate信息
	av_dump_format(fmtContext, 0, inFile, 0);

	avformat_close_input(&fmtContext);
	system("pause");
	return 0;
}
