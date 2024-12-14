#include <iostream>
#include <Sdl.h>
#define __STDC_CONSTANT_MACROS
extern "C"
{
#include<libavutil/log.h>
#include<libavformat/avformat.h> //media file parser
#include<libavcodec/avcodec.h>	//codec support
#include<libswscale/swscale.h>	//scale display frame
#include<libswresample/swresample.h> //audio process
}

//adapte new API
#if LIBAVCODEC_VERSION_INT <AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif

#define SDL_AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIO_FRAME_SIZE 192000
int g_quit = 0;
typedef struct PacketQueue
{
	AVPacketList * fristPkt, * lastPkt;
	int nb_packets;
	int size;
	SDL_mutex * mutex;
	SDL_cond * cond;
}PacketQueue;
PacketQueue g_audioQue;
struct SwrContext * audioConvertCtx = NULL; //audio process context
void packet_queue_put(PacketQueue * audioQue, AVPacket * packet)
{
	AVPacketList * p=(AVPacketList *)malloc(sizeof(AVPacketList));
	p->next = NULL;
	av_copy_packet(&(p->pkt), packet);

	AVPacketList *sp = audioQue->fristPkt;
	while (sp->next)
	{
		sp = sp->next;
	}
	sp->next = p;
	audioQue->lastPkt = p;
}
void packet_queue_init(PacketQueue * audioQue)
{
	audioQue->fristPkt = (AVPacketList *)malloc(sizeof(AVPacketList));
	audioQue->fristPkt->next = NULL;
	audioQue->lastPkt = audioQue->fristPkt;
	audioQue->nb_packets = 0;
	audioQue->size = 0;
	audioQue->mutex = NULL;
	audioQue->cond = NULL;
}
int packet_queue_get(PacketQueue * audioQue, AVPacket * packet)
{
	if (audioQue->fristPkt->next == NULL)
		return -1;

	AVPacketList * p = audioQue->fristPkt->next;
	audioQue->fristPkt->next = p->next;

	av_copy_packet(packet, &(p->pkt));

	free(p);
	return 0;
}
int audio_decode_frame(AVCodecContext * acodecCtx, uint8_t * audioBuf, int bufSize)
{
	static AVPacket pkt;
	static uint8_t * audioPktData = NULL;
	static int audioPktSize = 0;
	static AVFrame frame;
	int plen, dataSize = 0;

	while (1)
	{
		while (audioPktSize > 0)
		{
			int gotFrame = 0;
			plen = avcodec_decode_audio4(acodecCtx, &frame, &gotFrame, &pkt);
			if (plen < 0)
			{
				audioPktSize = 0;
				break;
			}
			audioPktData += plen;
			audioPktSize -= plen;
			dataSize = 0;
			if (gotFrame)
			{
				/*dataSize = av_samples_get_buffer_size(NULL,acodecCtx->channels,
					frame.nb_samples,acodecCtx->sample_fmt,1);*/
				dataSize = 2 * 2 * frame.nb_samples;
				swr_convert(audioConvertCtx, &audioBuf,
					MAX_AUDIO_FRAME_SIZE * 3 / 2,
					(const uint8_t **)frame.data,
					frame.nb_samples);
				memcpy(audioBuf, frame.data[0], dataSize);
			}
			if (dataSize <= 0)
				continue;
			return dataSize;
		}
		if (pkt.data)
			av_free_packet(&pkt);
		if (g_quit)
		{
			return -1;
		}
		if (packet_queue_get(&g_audioQue, &pkt) < 0)
		{
			return -1;
		}
		audioPktData = pkt.data;
		audioPktSize = pkt.size;
	}
}
void audioCallBack(void * userdata, Uint8 * stream, int len)
{
	AVCodecContext * acodecCtx = (AVCodecContext *)userdata;
	int plen, audioSize;
	static uint8_t audioBuf[(MAX_AUDIO_FRAME_SIZE * 3) / 2];
	static unsigned int audioBufSize = 0;
	static unsigned int audioBufIndex = 0;
	while (len > 0)
	{
		if (audioBufIndex >= audioBufSize)
		{
			audioSize = audio_decode_frame(acodecCtx, audioBuf, sizeof(audioBuf));
			if (audioSize < 0)
			{
				//empty voice
				audioBufSize = 1024;
				memset(audioBuf, 0, audioBufSize);
			}
			else
			{
				audioBufSize = audioSize;
			}
			audioBufIndex = 0;
		}
		plen = audioBufSize - audioBufIndex;
		if (plen > len)
		{
			plen = len;
		}
		memcpy(stream, (uint8_t *)audioBuf + audioBufIndex, plen);
		len -= plen;
		stream += plen;
		audioBufIndex += plen;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("argument:filename\n");
		system("pause");
		return -1;
	}
	char * filename = argv[1];

	int retode = -1;

	AVFormatContext * fmtCtx = NULL; //media file context

	int videoStream = -1;
	int audioStream = -1;

	//video arguments
	AVCodecContext * vcodecCtxOrig = NULL; //original and useful codec context
	AVCodecContext * vcodecCtx = NULL;
	AVCodec * vcodec = NULL; //vcodec 
	struct SwsContext * swsCxt = NULL; //scale cut context

	//audio arguments
	AVCodecContext * acodecCtxOrig = NULL; //original and useful codec context
	AVCodecContext * acodecCtx = NULL;
	AVCodec * acodec = NULL; //vcodec 
	int64_t inChannelLayout;
	int64_t outChannelLayout;
	SDL_AudioSpec wantedSpec, spec; //audio paly args

	AVFrame * frame = NULL;
	AVPacket pkt;		//one packet maybe has more than one frame

	int frameFinished;
	float aspectRatio;

	AVPicture * picture = NULL; //specially to save YUV data

	SDL_Rect rect;		//play video window size rect
	Uint32 pixFormat;

	SDL_Window * window = NULL;	//SDL window companent
	SDL_Renderer * render = NULL;
	SDL_Texture * texture = NULL;

	int winWidth = 720;		//default window size
	int winHeight = 480;


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
	{
		printf("error of init SDL %s\n", SDL_GetError());
		return -1;
	}

	av_register_all();

	if (avformat_open_input(&fmtCtx, filename, NULL, NULL) != 0)
	{
		printf("error of open media file\n");
		goto __SDLQUIT;
	}

	if (avformat_find_stream_info(fmtCtx, NULL) < 0)
	{
		printf("error of not any media stream\n");
		goto __CLOSEFILEFMT;
	}

	av_dump_format(fmtCtx, 0, filename, 0);

	//find video stream
#if 1 //whether use new API way
	if ((videoStream = av_find_best_stream(fmtCtx,AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0)) < 0)
	{
		printf("error of couldn't find video stream\n");
		goto __CLOSEFILEFMT;
	}
	if ((audioStream = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0)) < 0)
	{
		printf("error of couldn't find video stream\n");
		goto __CLOSEFILEFMT;
	}
#else
	videoStream = -1;
	audioStream = -1;
	for (int i = 0; i < fmtCtx->nb_streams; i++)
	{
		if (videoStream<0 && fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
		}
		if (audioStream<0 && fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audioStream = i;
		}
	}
	if (videoStream == -1 || audioStream==-1)
	{
		printf("error of couldn't find video or audio stream\n");
		goto __CLOSEFILEFMT;
	}
#endif //whether use new API

	//original vcodec context
	vcodecCtxOrig = fmtCtx->streams[videoStream]->codec;
	//get vcodec
	vcodec = avcodec_find_decoder(vcodecCtxOrig->codec_id);
	if (vcodec == NULL)
	{
		printf("error of get vcodec\n");
		goto __CLOSECODECCTX;
	}
	//the truth use vcodec context
	vcodecCtx = avcodec_alloc_context3(vcodec);
	if (avcodec_copy_context(vcodecCtx, vcodecCtxOrig) != 0)
	{
		printf("error of copy vcodec context\n");
		goto __CLOSECODECCTX;
	}
	if (avcodec_open2(vcodecCtx, vcodec, NULL) < 0)
	{
		printf("error of open vcodec\n");
		goto __CLOSECODECCTX;
	}

	acodecCtxOrig = fmtCtx->streams[audioStream]->codec;
	acodec = avcodec_find_decoder(acodecCtxOrig->codec_id);
	if (!acodec)
	{
		printf("error of get acodec\n");
		goto __CLOSECODECCTX;
	}
	acodecCtx = avcodec_alloc_context3(acodec);
	if (avcodec_copy_context(acodecCtx, acodecCtxOrig) != 0)
	{
		printf("error of copy acodec context\n");
		goto __CLOSECODECCTX;
	}
	//set audio setting form codec
	wantedSpec.freq = acodecCtx->sample_rate;
	wantedSpec.format = AUDIO_S16SYS;
	wantedSpec.channels = acodecCtx->channels;
	wantedSpec.silence = 0;
	wantedSpec.samples = SDL_AUDIO_BUFFER_SIZE;
	wantedSpec.callback = audioCallBack;
	wantedSpec.userdata = acodecCtx;
	if (SDL_OpenAudio(&wantedSpec, &spec) < 0)
	{
		printf("error of open audio env\n");
		goto __CLOSECODECCTX;
	}
	avcodec_open2(acodecCtx, acodec, NULL);
	packet_queue_init(&g_audioQue);
	inChannelLayout = av_get_default_channel_layout(acodecCtx->channels);
	outChannelLayout = inChannelLayout;//AV_CH_LAYOUT_STEREO;
	audioConvertCtx = swr_alloc();
	if (audioConvertCtx)
	{
		swr_alloc_set_opts(audioConvertCtx,
			outChannelLayout,
			AV_SAMPLE_FMT_S16,
			acodecCtx->sample_rate,
			inChannelLayout,
			acodecCtx->sample_fmt,
			acodecCtx->sample_rate,
			0, NULL);
	}
	swr_init(audioConvertCtx);
	


	frame = av_frame_alloc();
	if (!frame)
	{
		printf("error of allocate frame memory\n");
		goto __FREEFRAME;
	}

	winWidth = vcodecCtx->width;
	winHeight = vcodecCtx->height;

	window = SDL_CreateWindow(
		"Video Player",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		winWidth, winHeight,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		printf("error of create window\n");
		goto __FREEFRAME;
	}

	render = SDL_CreateRenderer(window, -1, 0);
	if (!render)
	{
		printf("error of create renderer\n");
		goto __DESTORYWINDOW;
	}

	pixFormat = SDL_PIXELFORMAT_IYUV;
	texture = SDL_CreateTexture(render,
		pixFormat,
		SDL_TEXTUREACCESS_STREAMING,
		winWidth, winHeight);
	if (!texture)
	{
		printf("error of create texture\n");
		goto __DESTORYRENDER;
	}

	//get SWS context for scale video frame
	swsCxt = sws_getContext(vcodecCtx->width, vcodecCtx->height,
		vcodecCtx->pix_fmt,
		vcodecCtx->width, vcodecCtx->height,
		AV_PIX_FMT_YUV420P,
		SWS_BILINEAR, NULL, NULL, NULL);

	picture = (AVPicture *)malloc(sizeof(AVPicture));
	avpicture_alloc(picture,
		AV_PIX_FMT_YUV420P,
		vcodecCtx->width, vcodecCtx->height);

	//start play audio
	SDL_PauseAudio(0);

	//start play video
	while (av_read_frame(fmtCtx, &pkt) >= 0)
	{
		if (pkt.stream_index == videoStream)
		{
			avcodec_decode_video2(vcodecCtx, frame, &frameFinished, &pkt);
			if (frameFinished)
			{
				//save the YUV data to Picture after scale size
				sws_scale(swsCxt,
					(uint8_t const * const *)frame->data,
					frame->linesize, 0,
					vcodecCtx->height,
					picture->data, picture->linesize);

				//SDL update texture
				SDL_UpdateYUVTexture(texture, NULL,
					picture->data[0], picture->linesize[0],//3 floor YUV data
					picture->data[1], picture->linesize[1],
					picture->data[2], picture->linesize[2]
					);

				//display window size
				rect.x = 0;
				rect.y = 0;
				rect.w = vcodecCtx->width;
				rect.h = vcodecCtx->height;

				//copy and display to screen
				SDL_RenderClear(render);
				SDL_RenderCopy(render, texture, NULL, &rect);
				SDL_RenderPresent(render);

				//adapt video frame rate
				SDL_Delay(33);
			}
		}
		else if (pkt.stream_index == audioStream)
		{
			packet_queue_put(&g_audioQue,&pkt);
		}
		else
		{
			av_free_packet(&pkt);
		}

		//check close window event
		SDL_Event evt;
		SDL_PollEvent(&evt);
		switch (evt.type)
		{
		case SDL_QUIT:
			goto __QUIT;
			break;
		default:
			break;
		}
	}

__QUIT:
	g_quit = 1;
	SDL_CloseAudio();
__FREEPICTURE :
	avpicture_free(picture);
	free(picture);

__DESTORYTEXTURE:
    SDL_DestroyTexture(texture);

__DESTORYRENDER:
    SDL_DestroyRenderer(render);

__DESTORYWINDOW:
    SDL_DestroyWindow(window);

__FREEFRAME:
    av_frame_free(&frame);

__CLOSECODECCTX:
	if (!acodecCtx)
		avcodec_free_context(&acodecCtx);
	if (!acodecCtxOrig)
		avcodec_free_context(&acodecCtxOrig);
    if (!vcodecCtx)
  	  avcodec_free_context(&vcodecCtx);
    if (!vcodecCtxOrig)
  	  avcodec_free_context(&vcodecCtxOrig);

__CLOSEFILEFMT:
    avformat_close_input(&fmtCtx);

__SDLQUIT:
    SDL_Quit();
    return 0;
}