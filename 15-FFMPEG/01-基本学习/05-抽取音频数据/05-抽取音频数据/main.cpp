#include<stdio.h>

/*
About:
抽取多媒体的音频数据
相关函数：
初始化数据包结构体：
av_init_packet()
找到最好的流
int av_find_best_stream()
参数：格式上下文，流类型，流索引号，相关流索引号，处理流的编解码器，标志
从流中将数据包内容获取到
int av_read_frame()
参数：格式上下文，数据包结构体
解除数据包引用计数，计数为0时，会自动释放资源，防止内存泄漏
int av_packet_unref()
参数：数据包结构体
步骤：
控制台读取数据
打开文件
输出多媒体信息
获取流
获取音频数据并输出保存
*/
#define __STDC_CONSTANT_MACROS
extern "C"
{
	#include<libavutil/log.h>
	#include<libavformat/avformat.h>
}
//添加adts头，这样播放器才能播放
void adtsHeader(unsigned char * szAdtsHeader, int dataLen);
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

	char * srcFile = argv[1];
	char * dstFile = argv[2];
	if (!srcFile || !dstFile)
	{
		av_log(NULL, AV_LOG_ERROR, "argument error\n");
		return -1;
	}
	//打开音视频文件
	AVFormatContext * fmtContext = NULL;
	char errBuff[1024] = { 0 };

	int ret = avformat_open_input(&fmtContext, srcFile, NULL, NULL);
	if (ret<0)
	{
		av_make_error_string(errBuff, 1024 - 1, ret);
		av_log(NULL, AV_LOG_ERROR, "open file failure:%s\n", errBuff);
		return -1;
	}
	//打印媒体信息
	av_dump_format(fmtContext,0,srcFile,0);
	//获取音频流
	ret = av_find_best_stream(fmtContext, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (ret<0)
	{
		av_log(NULL, AV_LOG_ERROR, "get stream error\n");
		avformat_close_input(&fmtContext);
		return -1;
	}
	//获取到目标流索引
	int audioIndex = ret;
	//打开输出文件
	FILE * fdstFile = fopen(dstFile, "wb");
	if (!fdstFile)
	{
		av_log(NULL, AV_LOG_ERROR, "write file error\n");
		avformat_close_input(&fmtContext);
		return -1;
	}
	
	//读取数据包并写入文件
	AVPacket pkt;
	av_init_packet(&pkt);
	while (av_read_frame(fmtContext, &pkt) >= 0)
	{
		//判断是否符合要求流的数据包
		if (pkt.stream_index == audioIndex)
		{
			//写入adtsHeader，这样才能用播放器播放
			char adts_header_buffer[7];
			adtsHeader((unsigned char *)adts_header_buffer, pkt.size);
			fwrite(adts_header_buffer, 1, 7, fdstFile);
			//写入文件
			int len = fwrite(pkt.data, 1, pkt.size, fdstFile);
			if (len != pkt.size)
			{
				av_log(NULL, AV_LOG_WARNING, "write file maybe wrong\n");
			}
		}
		//减少计数，自动释放空间
		av_packet_unref(&pkt);
	}
	fclose(fdstFile);
	avformat_close_input(&fmtContext);
	return 0;
}

//添加adts头，这样播放器才能播放
void adtsHeader(unsigned char * szAdtsHeader, int dataLen)
{
	int audio_object_type = 2;
	int sampling_frequency_index = 7;
	int channel_config = 2;
	int adtsLen = dataLen + 7;
	//同步字段:0xfff
	szAdtsHeader[0] = 0xff;
	szAdtsHeader[1] = 0xf0;
	//MPEG版本
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
