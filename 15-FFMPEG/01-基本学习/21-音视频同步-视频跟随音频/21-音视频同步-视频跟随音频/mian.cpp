/*
播放器核心剖析
--------------------------------------------------------
音视频同步：

时间戳：
PTS:展示时间戳，实际播放的时间戳，这就用于音视频的同步了
毕竟播放的时间戳是统一的
DTS:解码时间戳

三种帧：
IBP帧
I帧：关键帧，帧内压缩，包含一个帧的完整信息
P帧：向前参考帧，帧间压缩，一组连续帧之间，其实变化量是非常小的
参考与前一帧的差异
B帧：与前一帧和后一帧的差异，也可以是前多帧，实现更高的压缩

时间戳的顺序，由于参考的问题，导致顺序不一样：
实际顺序：IBBP
存放顺序：IPBB
解码时间戳：1423
展示时间戳：1234

因此，由于顺序不一样，就有了DTS
如果没有B帧的时候，PTS和DTS是一样的

PTS的获取：
AVPacket中的PTS
AVFrame中的PTS
大多数是一样的，但是，AVFrame中可能为永0
av_frame_get_best_effort_timestamp()
进行获取PTS

时间基
tbr:帧率
tbn:流的时间基
tbc:解码的时间基
一般来说，他们是不一样的，一般用tbn,最终转换为秒为单位

计算当前帧的PTS：
PTS=PTS*av_q2d(video_stream->time_base)
double av_q2d(AVRational a)//也就是分数结构体转double
{
return a.num*1.0/a.den;
}

计算下一帧的PTS：
video_clock:预测的下一帧视频的PTS，说白了就是加上一个增量
frame_delay:1/tbr
audio_clock:音频当前播放的时间戳

因此同步就是：
根据当前音频的时间戳进行比较，如果视频在前，就显示图像，否则就不显示，进行一个等待
等待的时长就是：audio_clock-video_clock

音视频同步方式：
1.视频同步到音频
音频一定的，那就视频跟着音频走就行
基本思路：
展示一个视频帧之后，获得下一个视频的PTS，设置定时器，定时器超时之后，刷新视频帧
如果PTS和音频的比较
小于就立即显示
大于就定时再显示
也就是上面说的同步方式，依次反复即可实现同步
2.音频同步到视频
音频参数一般是固定的，就可能导致音频视频数据长度不匹配的情况
就需要剔除或者添加部分音频，以达到同步，效果也可能不尽人意
3.音视频直接同步到一个固定时钟上
比如系统时钟上

--------------------------------------------------------
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
#include<libavutil\time.h>
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

#define AV_SYNC_THRESHOLD 0.01
#define AV_NOSYNC_THRESHOLD 10.0

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

	double pts;
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

	//音视频同步部分
	double audio_clock;//当前音频的PTS
	double video_clock;//下一帧视频的PTS

	double frame_timer;//下次回调的timer的时间
	double frame_last_pts;//上一次播放视频帧的PTS
	double frame_last_delay;//上一次视频播放增加的Delay时间

} VideoState;

SDL_mutex       *texture_mutex;
SDL_Window      *win;
SDL_Renderer    *renderer;
SDL_Texture     *texture;


VideoState *global_video_state = NULL;

void packet_queue_init(PacketQueue *que);
int packet_queue_enque(PacketQueue *que, AVPacket *pkt);
int packet_queue_deque(PacketQueue *que, AVPacket *pkt, int block);

int audio_decode_frame(VideoState *vdostate, uint8_t *audio_buf, int buf_size, double *pts_ptr);
void audio_callback(void *userdata, Uint8 *stream, int len);
Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque);
void schedule_refresh(VideoState *is, int delay);
void video_display(VideoState *vdostate);
void video_refresh_timer(void *userdata);
void alloc_picture(void *userdata);
int queue_picture(VideoState *vdostate, AVFrame *pFrame, double pts);
int video_thread(void *arg);
int stream_component_open(VideoState *vdostate, int stream_index);
int decode_media_file_thread(void *arg);

double syncronize_video(VideoState * vdostate, AVFrame * srcFrame, double pts);
double get_audio_clock(VideoState *vdostate);

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
		printf("SDL初始化失败：%s\n", SDL_GetError());
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
			printf("收到退出请求: %d\n", event.type);
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

	while (1) {

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

int audio_decode_frame(VideoState *vdostate, uint8_t *audio_buf, int buf_size, double *pts_ptr) {

	int len1, data_size = 0;
	AVPacket *pkt = &vdostate->audio_pkt;

	double pts=0;
	int n = 0;

	while (1) {
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
			pts = vdostate->audio_clock;
			*pts_ptr = pts;
			n = 2 * vdostate->audio_ctx->channels;
			vdostate->audio_clock += (double)data_size / (double)(n * vdostate->audio_ctx->sample_rate);
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

		if (pkt->pts != AV_NOPTS_VALUE) {
			vdostate->audio_clock = av_q2d(vdostate->audio_stream->time_base)*pkt->pts;
		}
	}
}

void audio_callback(void *userdata, Uint8 *stream, int len) {

	VideoState *vdostate = (VideoState *)userdata;
	int len1, audio_size;
	double pts=0;

	SDL_memset(stream, 0, len);

	while (len > 0) {
		if (vdostate->audio_buf_index >= vdostate->audio_buf_size) {
			//发送我们的解包数据
			audio_size = audio_decode_frame(vdostate, vdostate->audio_buf, sizeof(vdostate->audio_buf),&pts);
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
		printf("音频流地址:%p, 缓冲索引:%d, 数据长度:%d, 请求长度:%d\n",
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
			aspect_ratio = (float)vdostate->video_ctx->width / (float)vdostate->video_ctx->height;
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
double get_audio_clock(VideoState *vdostate) {
	double pts;
	int hw_buf_size, bytes_per_sec, n;

	pts = vdostate->audio_clock; //维护音频线程
	hw_buf_size = vdostate->audio_buf_size - vdostate->audio_buf_index;
	bytes_per_sec = 0;
	n = vdostate->audio_ctx->channels * 2;
	if (vdostate->audio_stream) {
		bytes_per_sec = vdostate->audio_ctx->sample_rate * n;
	}
	if (bytes_per_sec) {
		pts -= (double)hw_buf_size / bytes_per_sec;
	}
	return pts;
}

void video_refresh_timer(void * param) {

	VideoState *vdostate = (VideoState *)param;
	VideoPicture *vp;

	double actual_delay, delay, sync_threshold, ref_clock, diff;

	if (vdostate->video_stream)
	{
		if (vdostate->pictq_size == 0) {
			schedule_refresh(vdostate, 1); //如果栈空，则立即请求视频帧
		}
		else
		{
			vp = &vdostate->pictq[vdostate->pictq_rindex];

			//计算距离上次的pts时间差
			delay = vp->pts - vdostate->frame_last_pts;
			if (delay <= 0.0 || delay >= 1.0)//单位为秒
			{
				delay = vdostate->frame_last_delay;
			}
			//保存更新
			vdostate->frame_last_delay = delay;
			vdostate->frame_last_pts = vp->pts;
			//更新delay，和音频同步
			ref_clock = get_audio_clock(vdostate);
			diff = vp->pts - ref_clock;
			//取最大阀值，也需要最低时间
			sync_threshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
			//差值小于非同步阀值，也就是可以同步的
			if (fabs(diff) < AV_NOSYNC_THRESHOLD)
			{
				//小于负阀值，说明时间已经过去了，就应该立即显示视频了
				//否则，视频时间还没到，就加长等待时间
				if (diff <= -sync_threshold)
					delay = 0;
				else if (diff >= sync_threshold)
					delay = 2 * delay;
			}
			//得到时间戳
			vdostate->frame_timer += delay;
			//得到走过的时间，我们上面的计算也是需要时间的，因此需要排除
			actual_delay = vdostate->frame_timer - (av_gettime() / 1000000.0);
			if (actual_delay <= 0.010)
				actual_delay = 0.010;

			//根据计算出的延迟时间，设置定时器，进行视频同步到音频，换算为ms
			schedule_refresh(vdostate, (int)(actual_delay * 1000 + 0.5));

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

int queue_picture(VideoState *vdostate, AVFrame *pFrame, double pts) {

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
		vp->pts = pts;

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
double syncronize_video(VideoState * vdostate, AVFrame * srcFrame, double pts)
{
	double frame_delay = 0;

	//更新videoClock
	if (pts != 0.0)
		vdostate->video_clock = pts;
	else
		pts = vdostate->video_clock;
	//更新video clock
	//获取时间基
	frame_delay = av_q2d(vdostate->video_ctx->time_base);
	//加上重复播放帧的次数*0.5倍时间
	frame_delay += srcFrame->repeat_pict*(frame_delay*0.5);
	vdostate->video_clock += frame_delay;
	return pts;
}
int video_thread(void * param)
{
	VideoState *vdostate = (VideoState *)param;
	AVPacket pkt1, *packet = &pkt1;
	int frameFinished = 0;
	AVFrame *pFrame = NULL;
	double pts = 0;

	pFrame = av_frame_alloc();

	while (1) {
		if (packet_queue_deque(&vdostate->video_que, packet, 1) < 0) {
			break;//队空，发生异常
		}

		pts = 0;
		//解码视频帧
		avcodec_decode_video2(vdostate->video_ctx, pFrame, &frameFinished, packet);

		//获取并计算PTS
		if ((pts = av_frame_get_best_effort_timestamp(pFrame)) == AV_NOPTS_VALUE)
		{
			pts = 0;
		}
		//换算为秒
		pts *= av_q2d(vdostate->video_stream->time_base);


		//是否获取到视频帧
		if (frameFinished)
		{
			//计算同步的PTS
			pts = syncronize_video(vdostate, pFrame, pts);
			if (queue_picture(vdostate, pFrame, pts) < 0)
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

		//Out Audio Param
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

		SDL_PauseAudio(0);
		break;

	case AVMEDIA_TYPE_VIDEO:
		vdostate->videoStreamIndex = stream_index;
		vdostate->video_stream = pFormatCtx->streams[stream_index];
		vdostate->video_ctx = codecCtx;

		vdostate->frame_timer = (double)av_gettime() / 1000000.0;
		vdostate->frame_last_delay = 40e-3;

		packet_queue_init(&vdostate->video_que);
		vdostate->video_sws_ctx = sws_getContext(vdostate->video_ctx->width,
			vdostate->video_ctx->height,
			vdostate->video_ctx->pix_fmt,
			vdostate->video_ctx->width,
			vdostate->video_ctx->height,
			AV_PIX_FMT_YUV420P,
			SWS_BILINEAR,
			NULL, NULL, NULL);
		vdostate->video_tid = SDL_CreateThread(video_thread, "video_thread", vdostate);
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
	/*for (i = 0; i < pFormatCtx->nb_streams; i++) {
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO &&
			video_index < 0) {
			video_index = i;
		}
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO &&
			audio_index < 0) {
			audio_index = i;
		}
	}*/
	audio_index=av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	video_index = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

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
		printf("%s: 打开解码器失败\n", vdostate->filename);
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
	while (1)
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

