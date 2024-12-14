#include <iostream>
#include<cstdlib>
using namespace std;
/*
SDL的基本使用

流程：
包含头文件
初始化SDL
退出SDL

SDL渲染窗口：
SDL_Init/SDL_Quit()
SDL_CreateWindow/SDL_DestoryWindow()	//创建与销毁窗口
SDL_CreateRender/SDL_DestoryRender()	//创建与销毁渲染器
SDL_RenderClear		//清空屏幕
SDL_RenderPresent	//推送显示到界面

SDL的事件：
事件队列
实际上就是对队列操作

SDL事件种类：
SDL_WindowEvent 窗口事件
SDL_KeyboardEvent 键盘事件
SDL_MouseMotionEvent 鼠标事件
用户自定义事件

事件的处理：
SDL_PollEvent 轮询，借助延时，主动查询
SDL_WaitEvent 事件驱动，被动触发，可能阻塞
SDL_WaitEventTimeout	防止被阻塞，类似定时器逻辑

纹理渲染：
图片直接传递虽然也可以显示，但是这是CPU处理显示，不太好，能调用GPU那不是很好？
同样是画一条线，使用纹理之后，只需要告诉，起始点和终点的信息，以及中间的颜色渐变怎么处理即可
而不用全部的像素都传递过去，也就是只存储重要的决定信息，计算是在GPU上计算了，而不再是CPU进行计算
基本原理：
内存图像--通过渲染器--变成纹理--显卡计算--显示在屏幕
纹理相关函数：
SDL_CreateTexture()
	format:YUV/RGB
	access:Texture类型，Target,Stream
SDL_DestoryTexture()
渲染相关函数：
SDL_SetRenderTarget() //设置渲染的目标，默认是窗口
SDL_RenderClear() //清空
SDL_RenderCopy() //拷贝纹理数据
SDL_RenderPresent() //投屏

纹理使用流程：
SDL_CreateTexture 创建纹理
SDL_SetRenderTarget 设置渲染目标为纹理，这就开始GPU处理
进行纹理的渲染操作
SDL_SetRenderTarget 设置渲染目标回到屏幕，这就退出GPU处理
SDL_RenderCopy 拷贝纹理内容给显存
SDL_RenderPresent 显示到屏幕上
*/

/*
这个实例，给出了：
SDL的使用
渲染器
纹理

主要逻辑：
如果有鼠标移动事件：SDL_MOUSEMOTION
就使用纹理去绘制一个跟随鼠标的纹理，显示一个红色的矩形

如果没有移动事件
那么就不使用CPU，直接绘制我们原来的渐变背景色

流程：
绘制渐变背景
如果 鼠标移动
	绘制矩形
显示到屏幕
*/
//包含SDL头文件
#include <Sdl.h>

int main(int argc, char *argv[])
{
	//初始化SDL
	SDL_Init(SDL_INIT_VIDEO); //初始化为视频处理环境

	//创建一个窗口
	SDL_Window * window=NULL;
	window = SDL_CreateWindow(
		"SDL Window Title",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,//window pos
		//窗口位置有点坑，如果设置了0,0，那么最大化最小化按钮标题栏都将看不到，导致无法操作
		720,480,//window size
		SDL_WINDOW_SHOWN  //window flag
		);
	if (!window)
	{
		cout << "create window failure!" << endl;
		goto __EXIT;
	}
	
	//进行窗口渲染
	SDL_Renderer * render=NULL;
	render=SDL_CreateRenderer(window,-1,0);
	if (!window)
	{
		cout << "create window failure!" << endl;
		goto __DESTORY;
	}

	//使用一个纹理,和窗口一样大
	SDL_Texture * texture=NULL;
	texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_TARGET,
		720, 480);
	//通过纹理，让GPU进行绘制一个矩形
	SDL_Rect rect;
	rect.w = 30;
	rect.h = 30;
	//现在，来模拟渲染一个视频，做一个变色的纯色显示
	Uint8 r = 0, g = 0, b = 0;
	bool needQuit = false;
	while (1)
	{
		////设置绘制颜色，RGBA
		SDL_SetRenderDrawColor(render, r, g, b, 255);

		//清空渲染器，默认变为黑色
		SDL_RenderClear(render);

		r--;
		g+=2;
		b+=3;

		SDL_Event event;
		//SDL_WaitEvent(&event);
		//这里不使用WaitEvent,因为这样会导致我们原本的变色背景不能自由变化，需要等待事件才能变化
		//因此我们使用带超时的时间抓取，这样就算没有事件，也能够进行绘制
		if (SDL_WaitEventTimeout(&event, 30))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				needQuit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == 3)//0:无区分 1:鼠标左 2:鼠标中 3:鼠标右
					b = 255;
				else
					r = 255;
				break;
			case SDL_KEYDOWN:
				g = 255;
				break;
			case SDL_MOUSEMOTION: //使用纹理进行渲染
				rect.x = event.motion.x;
				rect.y = event.motion.y;

				//设置渲染的目标成为纹理，这样就交给GPU处理了
				SDL_SetRenderTarget(render, texture);
				//刷新纹理的背景，因为此刻渲染目标是纹理
				SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
				SDL_RenderClear(render);
				//绘制矩形
				SDL_RenderDrawRect(render,&rect);
				//填充矩形为红色
				SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
				SDL_RenderFillRect(render, &rect);
				//GPU的工作结束之后，重新让屏幕成为渲染目标
				SDL_SetRenderTarget(render, NULL);
				//将GPU绘制好的纹理拷贝到屏幕
				SDL_RenderCopy(render, texture, NULL, NULL);
				//SDL_RenderPresent(render);
				break;
			default:
				SDL_Log("event type is %d", event.type);
				break;
			}
		}
		
		//推送渲染内容给GPU显示
		SDL_RenderPresent(render);

		//进行一个延时
		SDL_Delay(30);

		if (needQuit)
			break;
	}
	
	//销毁纹理
	if (texture)
		SDL_DestroyTexture(texture);

	//销毁渲染器
	SDL_DestroyRenderer(render);
	

__DESTORY:
	//销毁窗口
	SDL_DestroyWindow(window);

	//退出、注销SDL
__EXIT:
	SDL_Quit();
	return 0;
}