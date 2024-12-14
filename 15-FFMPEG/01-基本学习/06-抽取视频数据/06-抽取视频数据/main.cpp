#include<stdio.h>

#define __STDC_CONSTANT_MACROS
extern "C"
{
#include<libavutil\avutil.h>
#include<libavformat\avformat.h>
}

/*
About:
抽取多媒体的视频数据
Start code
区分每一帧视频的特征码，这样才能获取每一帧的数据
SPS/PPS
解码的识别参数，分辨率帧率等
一般来说只需要一个，同一个分辨率和帧率，但是如果存在多分辨率的情况，那就有多个SPS，一般在关键帧之前
codec->extradata
获取数据，在编码器和扩展数据包中
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
int h264_extradata_to_annexb(const uint8_t * codec_extradata, const int codec_extradata_size, AVPacket * out_extradata, int padding);
void h264_mp4toannexb(AVFormatContext * fmtContext, AVPacket * pkt, FILE * fdst);
int alloc_and_copy(AVPacket * out,
	const uint8_t * sps_pps, uint32_t sps_pps_size,
	const uint8_t * in, uint32_t in_size);
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
	AVFormatContext * fmtContext = NULL;
	char errBuff[1024] = { 0 };

	int ret = avformat_open_input(&fmtContext, src, NULL, NULL);
	if (ret<0)
	{
		av_make_error_string(errBuff, 1024 - 1, ret);
		av_log(NULL, AV_LOG_ERROR, "open file failure:%s\n", errBuff);
		return -1;
	}
	//打印媒体信息
	av_dump_format(fmtContext,0,src,0);
	//获取视频流
	ret = av_find_best_stream(fmtContext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	if (ret<0)
	{
		av_log(NULL, AV_LOG_ERROR, "get stream error\n");
		avformat_close_input(&fmtContext);
		return -1;
	}
	//打开输出文件
	FILE * fdst = fopen(dst, "wb");
	if (!fdst)
	{
		av_log(NULL, AV_LOG_ERROR, "write file error\n");
		avformat_close_input(&fmtContext);
		return -1;
	}
	//获取到目标流索引
	int videoIndex = ret;
	//读取数据包并写入文件
	AVPacket pkt;
	av_init_packet(&pkt);
	pkt.data = NULL;
	pkt.size = 0;
	while (av_read_frame(fmtContext, &pkt) >= 0)
	{
		//判断是否符合要求流的数据包
		if (pkt.stream_index == videoIndex)
		{
			//设置startcode和spspps
			h264_mp4toannexb(fmtContext, &pkt, fdst);
		}
		//减少计数，自动释放空间
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
	//数据缓冲初始化
	buffer = pkt->data;
	buffer_size = pkt->size;
	buffer_end = pkt->data + pkt->size;
	//获取每一帧数据
	do{
		ret = AVERROR(EINVAL);
		if (buffer + 4>buffer_end)
			goto fail;
		//前四个字节是h264包的大小，这里进行端序调整
		for (nal_size = 0, i = 0; i<4; i++)
		{
			nal_size = (nal_size << 8) | buffer[i];
		}
		//后移四字节
		buffer += 4;

		uintType = *buffer & 0x1f;
		//nal单元大小
		if (nal_size>buffer_end - buffer || nal_size<0)
			goto fail;

		//如果是一个关键帧
		if (uintType == 5)
		{
			//从扩展数据获取sps和pps
			h264_extradata_to_annexb(fmtContext->streams[pkt->stream_index]->codec->extradata,
				fmtContext->streams[pkt->stream_index]->codec->extradata_size,
				&spsppsPkt,
				AV_INPUT_BUFFER_PADDING_SIZE);
			//为数据增加特征码
			if ((ret = alloc_and_copy(out, spsppsPkt.data, spsppsPkt.size, buffer, nal_size))<0)
				goto fail;
		}
		else
		{
			if ((ret = alloc_and_copy(out, NULL, 0, buffer, nal_size))<0)
				goto fail;

		}
		//输出到目标文件
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
//增加特征码
int alloc_and_copy(AVPacket * out,
	const uint8_t * sps_pps, uint32_t sps_pps_size,
	const uint8_t * in, uint32_t in_size)
{
	uint32_t offset = out->size;
	uint8_t nal_header_size = offset ? 3 : 4;//start code：sps pps 4:00 00 00 01 非spspps:3 00 00 01
	int err;
	//扩容
	err = av_grow_packet(out, sps_pps_size + in_size + nal_header_size);
	if (err<0)
		return err;
	//如果带sps，则拷贝过来
	if (sps_pps)
		memcpy(out->data + offset, sps_pps, sps_pps_size);
	//拷贝原始数据
	memcpy(out->data + sps_pps_size + nal_header_size + offset, in, in_size);
	//设置特征码
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
	const uint8_t * extradata = codec_extradata + 4;//跳过开头的四个字节
	static const uint8_t nalu_header[4] = { 0, 0, 0, 1 };//start code
	int length_size = (*extradata++ & 0x3) + 1;//标志sps pps的字节长度

	sps_offset = pps_offset = -1;
	uint_nb = *extradata++ & 0x1f;//获取sps pps的个数
	if (!uint_nb)
	{
		goto pps;
	}
	else
	{
		sps_offset = 0;
		sps_seen = 1;
	}
	while (uint_nb--)//遍历每个 sps pps
	{
		int err;
		uint_size = AV_RB16(extradata);//取sps pps的长度
		total_size += uint_size + 4;//加上start code 长度

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
		if ((err = av_reallocp(&out, total_size + padding))<0)//检测分配空间充足
			return err;
		memcpy(out + total_size - uint_size - 4, nalu_header, 4);//拷贝start code和sps pps数据
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