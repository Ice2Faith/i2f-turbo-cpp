/*
播放器核心剖析
--------------------------------------------------------
线程模型：
主线程：输入解析，事件处理，渲染显示，线程管理
流程：
主线程（输入文件）
	-创建线程（解复用）
		-创建线程（视频解码线程）
			-取出视频包，解码，放入解码视频队列
		-分别放入音视频流队列
			-SDL提供的音频渲染线程(打开音频设备时创建的)
				-取出音频包，播放到音频播放设备
			-SDL提供的视频渲染线程
				-取出视频数据，到GPU渲染显示

----------------------------------
因此可以看到，需要创建两个线程
主要通过队列进行中转
因为音视频的渲染，都是通过回调的方式去实现
由于音频是通过回调的方式的，因此我们视频也通过模拟回调的方式
这样就方便进行音视频同步，（都是回调）

--------------------------------------------------------
核心结构体
VideoState
包含了所需要使用到的基本所有参数，基本贯穿于整个程序中

*/
#include<stdio.h>
#include<math.h>
#include<assert.h>

#include <iostream>
#include <Sdl.h>
#define __STDC_CONSTANT_MACROS
extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>
#include<libavcodec\avcodec.h>
#include<libswresample\swresample.h>
#include<libswscale\swscale.h>
}

// 适配新API
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif

#define SIZE_SDL_AUDIO_BUFFER 1024
#define SIZE_MAX_AUDIO_FRAME 192000

#define SIZE_MAX_AUDIO_QUE (5 * 16 * 1024)
#define SIZE_MAX_VIDEO_QUE (5 * 256 * 1024)

#define EVT_REFRESH_VIDEO (SDL_USEREVENT)
#define EVT_QUIT_APP (SDL_USEREVENT + 1)

#define SIZE_VIDEO_PICTURE_QUEUE 1

#define SIZE_MAX_PATH 2048

typedef struct PacketQueue {
	AVPacketList *first_pkt, *last_pkt;
	int nb_packets;
	int size;
	SDL_mutex *mutex;
	SDL_cond *cond;
} PacketQueue;


typedef struct VideoPicture {
	AVPicture *pict;
	int width, height; /* source height & width */
	int allocated;
} VideoPicture;

typedef struct VideoState {

	//多媒体文件部分
	char            filename[SIZE_MAX_PATH];
	AVFormatContext *pFormatCtx;

	int             videoStreamIndex, audioStreamIndex;

	//音频部分
	AVStream        *audio_stream;
	AVCodecContext  *audio_ctx;
	PacketQueue     audio_que;
	uint8_t         audio_buf[(SIZE_MAX_AUDIO_FRAME * 3) / 2];
	unsigned int    audio_buf_size;
	unsigned int    audio_buf_index;
	AVFrame         audio_frame;
	AVPacket        audio_pkt;
	uint8_t         *audio_pkt_data;
	int             audio_pkt_size;
	struct SwrContext *audio_swr_ctx;

	//视频部分
	AVStream        *video_stream;
	AVCodecContext  *video_ctx;
	PacketQueue     video_que;
	struct SwsContext *video_sws_ctx;

	VideoPicture    pictq[SIZE_VIDEO_PICTURE_QUEUE];
	int             pictq_size, pictq_rindex, pictq_windex;

	//线程部分
	SDL_mutex       *pictq_mutex;
	SDL_cond        *pictq_cond;

	SDL_Thread      *parse_tid;
	SDL_Thread      *video_tid;

	//多线程之间，当程序退出时，就需要检查此标志位是否为真，为真时，所有的子线程
	//都应该退出他们的子线程，这样才能结束所有的线程，正常退出程序
	int             quit_flag;

} VideoState;

SDL_mutex       *texture_mutex;
SDL_Window      *win;
SDL_Renderer    *renderer;
SDL_Texture     *texture;


VideoState *global_video_state=NULL;

void packet_queue_init(PacketQueue *que);
int packet_queue_enque(PacketQueue *que, AVPacket *pkt);
int packet_queue_deque(PacketQueue *que, AVPacket *pkt, int block);

int audio_decode_frame(VideoState *vdostate, uint8_t *audio_buf, int buf_size);
void audio_callback(void *userdata, Uint8 *stream, int len);
Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque);
void schedule_refresh(VideoState *is, int delay);
void video_display(VideoState *vdostate);
void video_refresh_timer(void *userdata);
void alloc_picture(void *userdata);
int queue_picture(VideoState *vdostate, AVFrame *pFrame);
int video_thread(void *arg);
int stream_component_open(VideoState *vdostate, int stream_index);
int decode_media_file_thread(void *arg);

int main(int argc, char *argv[]) {

	int 		  ret = -1;

	if (argc < 2) {
		printf("命令行参数：媒体文件名\n");
		exit(1);
	}


	//申请核心结构体空间，可以理解为环境上下文
	VideoState      *vdostate = NULL;
	vdostate = (VideoState*)av_mallocz(sizeof(VideoState));

	//注册所有ffmpeg库
	av_register_all();

	//初始化SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf( "SDL初始化失败：%s\n", SDL_GetError());
		exit(1);
	}

	//创建纹理互斥量
	texture_mutex = SDL_CreateMutex();

	//拷贝文件名
	//av_strlcpy(vdostate->filename, argv[1], sizeof(vdostate->filename));
	strncpy(vdostate->filename, argv[1], sizeof(vdostate->filename));
	//strcpy(vdostate->filename, "G:\\test.mp4");

	//创建视频帧互斥量和信号量
	vdostate->pictq_mutex = SDL_CreateMutex();
	vdostate->pictq_cond = SDL_CreateCond();

	//设置定时器，视频帧率25=1000/40
	schedule_refresh(vdostate, 40);

	//创建媒体文件解复用线程
	vdostate->parse_tid = SDL_CreateThread(decode_media_file_thread, "decode_media_file_thread", vdostate);
	if (!vdostate->parse_tid) {
		av_free(vdostate);
		goto __MAIN_FAIL;
	}

	//主线程捕获事件并调度处理，仅仅调度，具体工作基本使用子线程进行
	SDL_Event       event;
	while (1) {

		SDL_WaitEvent(&event);
		switch (event.type) {
			//用户退出事件或播放完毕
		case EVT_QUIT_APP:
		case SDL_QUIT:
			printf( "收到退出请求: %d\n", event.type);
			vdostate->quit_flag = 1;
			goto __MAIN_QUIT;
			break;
		case EVT_REFRESH_VIDEO:
			//fprintf("收到视频刷新请求: %d\n", event.type);
			video_refresh_timer(event.user.data1);//参数实际上就是VideoState
			break;
		default:
			break;
		}
	}

__MAIN_QUIT:
	ret = 0;


__MAIN_FAIL:
	SDL_Quit();
	return ret;

}

void packet_queue_init(PacketQueue *que) {
	memset(que, 0, sizeof(PacketQueue));
	que->mutex = SDL_CreateMutex();
	que->cond = SDL_CreateCond();
}

int packet_queue_enque(PacketQueue *que, AVPacket *pkt)
{

	AVPacketList *curNode;
	if (av_dup_packet(pkt) < 0) {
		return -1;
	}
	curNode = (AVPacketList*)av_malloc(sizeof(AVPacketList));
	if (!curNode)
		return -1;
	curNode->pkt = *pkt;
	curNode->next = NULL;

	SDL_LockMutex(que->mutex);

	if (!que->last_pkt)
		que->first_pkt = curNode;
	else
		que->last_pkt->next = curNode;
	que->last_pkt = curNode;
	que->nb_packets++;
	que->size += curNode->pkt.size;
	//printf("入队包:%d, 发送信号\n", q->nb_packets);
	SDL_CondSignal(que->cond);

	SDL_UnlockMutex(que->mutex);
	return 0;
}

int packet_queue_deque(PacketQueue *que, AVPacket *pkt, int block)
{
	AVPacketList *curNode;
	int ret;

	SDL_LockMutex(que->mutex);

	while(1) {

		if (global_video_state->quit_flag) {
			printf("出队退出请求\n");
			ret = -1;
			break;
		}

		curNode = que->first_pkt;
		if (curNode) {
			que->first_pkt = curNode->next;
			if (!que->first_pkt)
				que->last_pkt = NULL;
			que->nb_packets--;
			que->size -= curNode->pkt.size;
			*pkt = curNode->pkt;
			av_free(curNode);
			ret = 1;
			break;
		}
		else if (!block) {
			ret = 0;
			break;
		}
		else {
			printf("队列为空，等待信号\n");
			SDL_CondWait(que->cond, que->mutex);
		}
	}
	SDL_UnlockMutex(que->mutex);
	return ret;
}

int audio_decode_frame(VideoState *vdostate, uint8_t *audio_buf, int buf_size) {

	int len1, data_size = 0;
	AVPacket *pkt = &vdostate->audio_pkt;

	while(1) {
		while (vdostate->audio_pkt_size > 0) {

			int got_frame = 0;
			len1 = avcodec_decode_audio4(vdostate->audio_ctx, &vdostate->audio_frame, &got_frame, pkt);
			if (len1 < 0) {
				//跳过异常帧
				printf("解码视频帧失败 ......\n");
				vdostate->audio_pkt_size = 0;
				break;
			}

			data_size = 0;
			if (got_frame) {
				
				/*printf("音频: 声道数:%d, 采样率:%d, 采样格式:%d\n",
				vdostate->audio_ctx->channels,
				vdostate->audio_frame.nb_samples,
				vdostate->audio_ctx->sample_fmt);

				data_size = av_samples_get_buffer_size(NULL,
				vdostate->audio_ctx->channels,
				vdostate->audio_frame.nb_samples,
				vdostate->audio_ctx->sample_fmt,
				1);*/
				
				data_size = 2 * vdostate->audio_frame.nb_samples * 2;
				assert(data_size <= buf_size);
				//memcpy(audio_buf, vdostate->audio_frame.data[0], data_size);

				swr_convert(vdostate->audio_swr_ctx,
					&audio_buf,
					SIZE_MAX_AUDIO_FRAME * 3 / 2,
					(const uint8_t **)vdostate->audio_frame.data,
					vdostate->audio_frame.nb_samples);

			}

			vdostate->audio_pkt_data += len1;
			vdostate->audio_pkt_size -= len1;
			if (data_size <= 0) {
				//没有音频帧，则重新获取
				continue;
			}
			//有数据则返回，等待下一次回调
			return data_size;
		}

		if (pkt->data)
			av_free_packet(pkt);

		if (vdostate->quit_flag) {
			printf("即将退出程序......\n");
			return -1;
		}

		//抓取下一个包
		if (packet_queue_deque(&vdostate->audio_que, pkt, 1) < 0) {
			return -1;
		}

		vdostate->audio_pkt_data = pkt->data;
		vdostate->audio_pkt_size = pkt->size;
	}
}

void audio_callback(void *userdata, Uint8 *stream, int len) {

	VideoState *vdostate = (VideoState *)userdata;
	int len1, audio_size;

	SDL_memset(stream, 0, len);

	while (len > 0) {
		if (vdostate->audio_buf_index >= vdostate->audio_buf_size) {
			//发送我们的解包数据
			audio_size = audio_decode_frame(vdostate, vdostate->audio_buf, sizeof(vdostate->audio_buf));
			if (audio_size < 0) {
				//错误则输出噪声
				vdostate->audio_buf_size = 1024 * 2 * 2;
				memset(vdostate->audio_buf, 0, vdostate->audio_buf_size);
			}
			else {
				vdostate->audio_buf_size = audio_size;
			}
			vdostate->audio_buf_index = 0;
		}
		len1 = vdostate->audio_buf_size - vdostate->audio_buf_index;
		printf( "音频流地址:%p, 缓冲索引:%d, 数据长度:%d, 请求长度:%d\n",
			stream,
			vdostate->audio_buf_index,
			len1,
			len);
		if (len1 > len)
			len1 = len;

		//memcpy(stream, (uint8_t *)vdostate->audio_buf + vdostate->audio_buf_index, len1);

		//混音到音频设备
		SDL_MixAudio(stream, (uint8_t *)vdostate->audio_buf, len1, SDL_MIX_MAXVOLUME);
		len -= len1;
		stream += len1;
		vdostate->audio_buf_index += len1;
	}
}

Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque) {
	//发送刷新视频事件，交给主线程调度处理
	SDL_Event event;
	event.type = EVT_REFRESH_VIDEO;
	event.user.data1 = opaque;
	SDL_PushEvent(&event);
	return 0;//表示停止定时器，返回0
}

//定义视频刷新延迟的计时器ms
void schedule_refresh(VideoState *is, int delay) {
	SDL_AddTimer(delay, sdl_refresh_timer_cb, is);
}

void video_display(VideoState *vdostate) {

	SDL_Rect rect;
	VideoPicture *vp;
	float aspect_ratio;
	int w, h, x, y;
	int i;

	//获取显示的视频请求帧
	vp = &vdostate->pictq[vdostate->pictq_rindex];
	if (vp->pict) {

		//获取视频宽高比
		if (vdostate->video_ctx->sample_aspect_ratio.num == 0) {
			aspect_ratio = 0;
		}
		else {
			aspect_ratio = av_q2d(vdostate->video_ctx->sample_aspect_ratio) *vdostate->video_ctx->width / vdostate->video_ctx->height;
		}

		if (aspect_ratio <= 0.0) {
			aspect_ratio = (float)vdostate->video_ctx->width /(float)vdostate->video_ctx->height;
		}


		//h = screen->h;
		//w = ((int)rint(h * aspect_ratio)) & -3;
		//if (w > screen->w) {
		//	w = screen->w;
		//	h = ((int)rint(w / aspect_ratio)) & -3;
		//}
		//x = (screen->w - w) / 2;
		//y = (screen->h - h) / 2;

		//更新纹理，从视频图片帧
		SDL_UpdateYUVTexture(texture, NULL,
			vp->pict->data[0], vp->pict->linesize[0],
			vp->pict->data[1], vp->pict->linesize[1],
			vp->pict->data[2], vp->pict->linesize[2]);

		//显示区域
		rect.x = 0;
		rect.y = 0;
		rect.w = vdostate->video_ctx->width;
		rect.h = vdostate->video_ctx->height;

		//纹理是需要线程互斥使用的
		SDL_LockMutex(texture_mutex);
		//重新渲染绘制，并显示到屏幕上
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_RenderPresent(renderer);
		SDL_UnlockMutex(texture_mutex);

	}
}

void video_refresh_timer(void * param) {

	VideoState *vdostate = (VideoState *)param;
	VideoPicture *vp;

	if (vdostate->video_stream) 
	{
		if (vdostate->pictq_size == 0) {
			schedule_refresh(vdostate, 1); //如果栈空，则立即请求视频帧
		}
		else 
		{
			vp = &vdostate->pictq[vdostate->pictq_rindex];
			
			//常规的请求下一个视频帧，虽然延迟你可以设置更短，但是不建议这样做
			schedule_refresh(vdostate, 40);

			//显示视频帧
			video_display(vdostate);

			//更新视频队列，也就是出队
			if (++vdostate->pictq_rindex == SIZE_VIDEO_PICTURE_QUEUE)
			{
				vdostate->pictq_rindex = 0;
			}

			//同样，视频帧的操作也是需要线程互斥的
			SDL_LockMutex(vdostate->pictq_mutex);
			vdostate->pictq_size--;
			SDL_CondSignal(vdostate->pictq_cond);
			SDL_UnlockMutex(vdostate->pictq_mutex);
		}
	}
	else 
	{
		//视频流还没有解析时，等待解析视频流
		schedule_refresh(vdostate, 100);
	}
}

void alloc_picture(void * param) {

	VideoState *vdostate = (VideoState *)param;
	VideoPicture *vp;

	vp = &vdostate->pictq[vdostate->pictq_windex];
	if (vp->pict) 
	{
		//释放之前的空间
		avpicture_free(vp->pict);
		free(vp->pict);
	}

	// 申请空间存放YUV图像，提供给屏幕显示
	SDL_LockMutex(texture_mutex);
	vp->pict = (AVPicture*)malloc(sizeof(AVPicture));
	if (vp->pict)
	{
		avpicture_alloc(vp->pict,
			AV_PIX_FMT_YUV420P,
			vdostate->video_ctx->width,
			vdostate->video_ctx->height);
	}
	SDL_UnlockMutex(texture_mutex);

	vp->width = vdostate->video_ctx->width;
	vp->height = vdostate->video_ctx->height;
	vp->allocated = 1;

}

int queue_picture(VideoState *vdostate, AVFrame *pFrame) {

	VideoPicture *vp;
	int dst_pix_fmt;
	AVPicture pict;

	//等待空间准备完毕
	SDL_LockMutex(vdostate->pictq_mutex);
	while (vdostate->pictq_size >= SIZE_VIDEO_PICTURE_QUEUE &&
		!vdostate->quit_flag) {
		SDL_CondWait(vdostate->pictq_cond, vdostate->pictq_mutex);
	}
	SDL_UnlockMutex(vdostate->pictq_mutex);

	//收到退出请求
	if (vdostate->quit_flag){
		printf("退出请求： queue_picture....\n");
		return -1;
	}

	// windex 初始化为0
	vp = &vdostate->pictq[vdostate->pictq_windex];

	/*
	printf("vp.width=%d, vp.height=%d, video_ctx.width=%d, video_ctx.height=%d\n",
	vp->width,
	vp->height,
	vdostate->video_ctx->width,
	vdostate->video_ctx->height);
	*/

	//申请空间或者进行空间大小的缩放
	if (!vp->pict ||
		vp->width != vdostate->video_ctx->width ||
		vp->height != vdostate->video_ctx->height)
	{

		vp->allocated = 0;
		alloc_picture(vdostate);
		if (vdostate->quit_flag)
		{
			printf("退出请求： queue_picture....\n");
			return -1;
		}
	}

	//开始存放视频帧数据
	if (vp->pict) 
	{

		//转换图像为YVU图像给SDL使用
		sws_scale(vdostate->video_sws_ctx, (uint8_t const * const *)pFrame->data,
			pFrame->linesize, 0, vdostate->video_ctx->height,
			vp->pict->data, vp->pict->linesize);

		//入队图片，并通知准备完毕
		if (++vdostate->pictq_windex == SIZE_VIDEO_PICTURE_QUEUE) {
			vdostate->pictq_windex = 0;
		}
		SDL_LockMutex(vdostate->pictq_mutex);
		vdostate->pictq_size++;
		SDL_UnlockMutex(vdostate->pictq_mutex);
	}
	return 0;
}

int video_thread(void * param) 
{
	VideoState *vdostate = (VideoState *)param;
	AVPacket pkt1, *packet = &pkt1;
	int frameFinished=0;
	AVFrame *pFrame=NULL;

	pFrame = av_frame_alloc();

	while(1) {
		if (packet_queue_deque(&vdostate->video_que, packet, 1) < 0) {
			break;//队空，发生异常
		}

		//解码视频帧
		avcodec_decode_video2(vdostate->video_ctx, pFrame, &frameFinished, packet);

		//是否获取到视频帧
		if (frameFinished)
		{
			if (queue_picture(vdostate, pFrame) < 0) 
			{
				break;
			}
		}

		av_free_packet(packet);
	}
	av_frame_free(&pFrame);
	return 0;
}

int stream_component_open(VideoState *vdostate, int stream_index)
{
	//输入输出通道布局
	int64_t in_channel_layout, out_channel_layout;

	AVFormatContext *pFormatCtx = vdostate->pFormatCtx;
	AVCodecContext *codecCtx = NULL;
	AVCodec *codec = NULL;
	SDL_AudioSpec wanted_spec, spec;

	//异常流ID
	if (stream_index < 0 || stream_index >= pFormatCtx->nb_streams) {
		return -1;
	}
	//查找流解码器
	codec = avcodec_find_decoder(pFormatCtx->streams[stream_index]->codec->codec_id);
	if (!codec)
	{
		printf("不支持的解码器!\n");
		return -1;
	}
	//拷贝解码上下文
	codecCtx = avcodec_alloc_context3(codec);
	if (avcodec_copy_context(codecCtx, pFormatCtx->streams[stream_index]->codec) != 0)
	{
		printf("拷贝解码上下文失败\n");
		return -1; 
	}


	if (codecCtx->codec_type == AVMEDIA_TYPE_AUDIO) 
	{
		// 根据解码器设置相关参数
		wanted_spec.freq = codecCtx->sample_rate;
		wanted_spec.format = AUDIO_S16SYS;
		wanted_spec.channels = codecCtx->channels;
		wanted_spec.silence = 0;
		wanted_spec.samples = SIZE_SDL_AUDIO_BUFFER;
		wanted_spec.callback = audio_callback;
		wanted_spec.userdata = vdostate;

		//这里，记个笔记，不知道为什么，第二个参数如果是:SDL_OpenAudio(&wanted_spec, &spec)
		//那么播放就不会发出声音，像下面这样写就可以有声音
		if (SDL_OpenAudio(&wanted_spec, NULL) < 0)
		{
			printf("SDL_OpenAudio: %s\n", SDL_GetError());
			return -1;
		}
	}

	if (avcodec_open2(codecCtx, codec, NULL) < 0) 
	{
		fprintf(stderr, "打开解码器失败!\n");
		return -1;
	}

	switch (codecCtx->codec_type)
	{
	case AVMEDIA_TYPE_AUDIO:
		vdostate->audioStreamIndex = stream_index;
		vdostate->audio_stream = pFormatCtx->streams[stream_index];
		vdostate->audio_ctx = codecCtx;
		vdostate->audio_buf_size = 0;
		vdostate->audio_buf_index = 0;
		memset(&vdostate->audio_pkt, 0, sizeof(vdostate->audio_pkt));
		packet_queue_init(&vdostate->audio_que);
		SDL_PauseAudio(0);

		in_channel_layout = av_get_default_channel_layout(vdostate->audio_ctx->channels);
		out_channel_layout = in_channel_layout;

		vdostate->audio_swr_ctx = swr_alloc();
		swr_alloc_set_opts(vdostate->audio_swr_ctx,
			out_channel_layout,
			AV_SAMPLE_FMT_S16,
			vdostate->audio_ctx->sample_rate,
			in_channel_layout,
			vdostate->audio_ctx->sample_fmt,
			vdostate->audio_ctx->sample_rate,
			0,
			NULL);

		fprintf(stderr, "音频重采样参数: out_channel_layout:%lld, out_sample_fmt:%d, out_sample_rate:%d, in_channel_layout:%lld, in_sample_fmt:%d, in_sample_rate:%d",
			out_channel_layout,
			AV_SAMPLE_FMT_S16,
			vdostate->audio_ctx->sample_rate,
			in_channel_layout,
			vdostate->audio_ctx->sample_fmt,
			vdostate->audio_ctx->sample_rate);

		swr_init(vdostate->audio_swr_ctx);

		break;

	case AVMEDIA_TYPE_VIDEO:
		vdostate->videoStreamIndex = stream_index;
		vdostate->video_stream = pFormatCtx->streams[stream_index];
		vdostate->video_ctx = codecCtx;
		packet_queue_init(&vdostate->video_que);
		vdostate->video_tid = SDL_CreateThread(video_thread, "video_thread", vdostate);
		vdostate->video_sws_ctx = sws_getContext(vdostate->video_ctx->width,
			vdostate->video_ctx->height,
			vdostate->video_ctx->pix_fmt,
			vdostate->video_ctx->width,
			vdostate->video_ctx->height,
			AV_PIX_FMT_YUV420P,
			SWS_BILINEAR,
			NULL, NULL, NULL);
		break;
	default:
		break;
	}

	return 0;
}

int decode_media_file_thread(void *param)
{

	Uint32 pixformat;

	VideoState *vdostate = (VideoState *)param;
	AVFormatContext *pFormatCtx = NULL;
	AVPacket pkt1, *packet = &pkt1;

	int i;
	int video_index = -1;
	int audio_index = -1;

	vdostate->videoStreamIndex = -1;
	vdostate->audioStreamIndex = -1;

	global_video_state = vdostate;

	// 打开媒体文件
	if (avformat_open_input(&pFormatCtx, vdostate->filename, NULL, NULL) != 0)
		return -1; 

	vdostate->pFormatCtx = pFormatCtx;

	// 查找媒体流信息
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
		return -1; 

	// 打印媒体文件meta信息
	av_dump_format(pFormatCtx, 0, vdostate->filename, 0);

	// 获得音视频流索引
	for (i = 0; i < pFormatCtx->nb_streams; i++) {
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO &&
			video_index < 0) {
			video_index = i;
		}
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO &&
			audio_index < 0) {
			audio_index = i;
		}
	}

	//打开音视频流进行解析
	if (audio_index >= 0)
	{
		stream_component_open(vdostate, audio_index);
	}
	if (video_index >= 0) 
	{
		stream_component_open(vdostate, video_index);
	}

	if (vdostate->videoStreamIndex < 0 || vdostate->audioStreamIndex < 0) 
	{
		printf( "%s: 打开解码器失败\n", vdostate->filename);
		goto __decode_media_file_thread_FAIL;
	}

	printf("视频参数: width=%d, height=%d\n", vdostate->video_ctx->width, vdostate->video_ctx->height);
	win = SDL_CreateWindow("Media Player",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		vdostate->video_ctx->width, vdostate->video_ctx->height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(win, -1, 0);

	pixformat = SDL_PIXELFORMAT_IYUV;
	texture = SDL_CreateTexture(renderer,
		pixformat,
		SDL_TEXTUREACCESS_STREAMING,
		vdostate->video_ctx->width,
		vdostate->video_ctx->height);

	// 主函数事件调度循环
	while(1)
	{

		if (vdostate->quit_flag)//退出信号，通知线程退出
		{
			SDL_CondSignal(vdostate->video_que.cond);
			SDL_CondSignal(vdostate->audio_que.cond);
			break;
		}

		// 等待播放，出队一些包
		if (vdostate->audio_que.size > SIZE_MAX_AUDIO_QUE ||
			vdostate->video_que.size > SIZE_MAX_VIDEO_QUE) 
		{
			SDL_Delay(10);
			continue;
		}

		if (av_read_frame(vdostate->pFormatCtx, packet) < 0) 
		{
			if (vdostate->pFormatCtx->pb->error == 0)
			{
				//仅仅是真里面没有数据，但不是错误，等待下一个帧即可
				SDL_Delay(100); 
				continue;
			}
			else {
				break;
			}
		}

		// 不同的类型的包进入不同的包队列
		if (packet->stream_index == vdostate->videoStreamIndex) {
			packet_queue_enque(&vdostate->video_que, packet);
			printf("视频包入队, size :%d\n", vdostate->video_que.nb_packets);
		}
		else if (packet->stream_index == vdostate->audioStreamIndex) {
			packet_queue_enque(&vdostate->audio_que, packet);
			printf("音频包入队, size :%d\n", vdostate->audio_que.nb_packets);
		}
		else {//其他不需要的包进行释放
			av_free_packet(packet);
		}

	}

	//解析完所有包，还要等待播放结束
	while (!vdostate->quit_flag) {
		SDL_Delay(100);
	}

__decode_media_file_thread_FAIL:
	{
		//播放完毕之后，自动退出程序
		SDL_Event event;
		event.type = EVT_QUIT_APP;
		event.user.data1 = vdostate;
		SDL_PushEvent(&event);
	}

	return 0;
}

