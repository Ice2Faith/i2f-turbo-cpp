/*
多线程与锁

播放器核心是要做到音视频同步
本质就是多线程的同步

多线程的的互斥与同步
锁与信号量

锁的种类：
读写锁
自旋锁
可重入锁

SDL线程的创建
SDL_CreateThread
SDL_WaitThread

SDL锁
SDL_CreateMutex/SDL_DestoryMutex

SDL_LockMutex/SDL_UnlockMutex

条件变量、信号量
SDL_CreateCond/SDL_DestoryCond
SDL_CondWait/SDL_CondSignal //其实内部实现上，包含了lock与unlock过程，否则就锁不能匹配出错，从而死锁了
//内部其实就是：unlock,对信号做操作，lock

下面给出一个简单的队列示例：
*/
#include <iostream>
#include <Sdl.h>
#define __STDC_CONSTANT_MACROS
extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h>
}
int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Quit();
	std::cout << "Hello SDL" << std::endl;
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
		av_log(NULL, AV_LOG_ERROR, "open file failure:%s\n", buffer);
		return -1;
	}
	//打印文件mate信息
	av_dump_format(fmtContext, 0, inFile, 0);

	avformat_close_input(&fmtContext);
	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/*
实现线程同步的队列
【注意】仅仅包含主要核心代码，并不能使用
*/
//队列结构
typedef struct _PacketQueue
{
	AVPacketList * first_pkt, *last_pkt;//包列表头尾指针
	int nb_packets;//包数量
	int size;//容量
	SDL_mutex * mutex;//互斥量
	SDL_cond * cond;//信号量
}PacketQueue;

//入队函数
int packet_queue_put(PacketQueue * q, AVPacket * pkt)
{
	AVPacketList * pktl;
	if (av_dup_packet(pkt) < 0)//引用计数加一
	{
		return -1;
	}

	//分配空间并填充
	pktl = (AVPacketList*)av_malloc(sizeof(AVPacketList));
	if (pktl == NULL)
	{
		return -1;
	}

	pktl->pkt = *pkt;
	pktl->next = NULL;

	//加锁操作
	SDL_LockMutex(q->mutex);
	
	//添加到队列中
	if (q->last_pkt == NULL)
	{
		q->first_pkt = pktl;
	}
	else
	{
		q->last_pkt->next = pktl;
	}
	q->last_pkt = pktl;
	q->nb_packets++;
	q->size += pktl->pkt.size;

	//唤醒信号量，信号的发送也需要在锁内部
	SDL_CondSignal(q->cond);//配合出队时的wait

	//解锁操作
	SDL_UnlockMutex(q->mutex);

	return 0;
}

int packet_queue_get(PacketQueue * q, AVPacket * pkt, int block/*阻塞非阻塞*/)
{
	AVPacketList * pktl;
	int ret;

	SDL_LockMutex(q->mutex);

	while (1)//因为有锁的存在，因此如果不异步获取的话，就需要一直等待，知道满足返回条件
	{
		//if (global_video_state->quit)
		//{
		//	ret = -1;
		//	break;
		//}

		pktl = q->first_pkt;
		if (pktl != NULL)
		{
			q->first_pkt = pktl->next;
			if (q->first_pkt == NULL)
			{
				q->last_pkt = NULL;
			}
			q->nb_packets--;
			q->size -= pktl->pkt.size;
			*pkt = pktl->pkt;
			av_free(pktl);
			ret = 1;
			break;
		}
		else if (!block)
		{
			ret = 0;
			break;
		}
		else
		{
			//空队
			SDL_CondWait(q->cond, q->mutex);
		}
	}
	SDL_UnlockMutex(q->mutex);
	return ret;
}