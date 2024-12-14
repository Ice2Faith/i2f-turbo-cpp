//YUV分量调整系数
double g_rate0=1.0;
double g_rate1=1.0;
double g_rate2=1.0;
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
		
		//////////////////////////////////////////////////////////////////////////////////
		//视频播放效果的调整，其实就是对YUV分量的调整，类似操作RGB一样，
		//这里，直接在获得的视频帧图像处理后，放入帧队列，等待播放即可实现效果调整
		//linesize表示一行的数据量
		int vhei = vp->height;
		for (int j = 0; j < vhei; j++)
		{
			//亮度调整
			for (int i = 0; i < vp->pict->linesize[0]; i++)
			{
				//其实就是一个二维组转以为线性的公式：行数j*一行的个数+最后一行的下标i
				vp->pict->data[0][j*vp->pict->linesize[0] + i] *= g_rate0;
			}

			//色相调整
			for (int i = 0; i < vp->pict->linesize[1]; i++)
			{
				vp->pict->data[1][j*vp->pict->linesize[1] + i] *= g_rate1;
			}

			//色调调整
			for (int i = 0; i < vp->pict->linesize[2]; i++)
			{
				//对于YUV420来说，需要注意的是V分量，是隔行采样的，因此，后面有除以2的操作
				vp->pict->data[2][j*vp->pict->linesize[2]/2 + i] *= g_rate2;
			}
			
		}
		

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