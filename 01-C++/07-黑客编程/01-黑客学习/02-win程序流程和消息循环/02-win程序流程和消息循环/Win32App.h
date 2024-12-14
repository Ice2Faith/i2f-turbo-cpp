#ifndef _WIN32APP_H_
#define _WIN32APP_H_
#include<Windows.h>
/*
Win32程序入口（Main函数）：
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nCmdShow)
参数说明：当前实例句柄，之前的实例句柄（已经废弃不用），命令行参数，窗口显示模式
使用流程说明：
#include"Win32App.h"
int WAWin32Main()
{
	//进行注册窗口类，告诉系统有这样一个窗口类，还有回调函数入口
	if (0 == WARegisterWindowClass(hInstance, className))
		return FALSE;
	//创建窗口，显示窗口，更新窗口
	if (WACreateWindowAndShow(hInstance, nCmdShow, className, wndName) == FALSE)
		return FALSE;
	//进入消息循环，直到遇到关闭窗口消息退出循环，结束程序
	return WAMessageLoop();
}
你需要关注的是什么？
	根据自己的消息去改写回调函数：WAWindowProc
	根据自己的绘图去改写函数：WADrawApplication
其他的一些讲解：
	进入消息循环之后，不断获取自己窗口的消息，解释消息，分发消息，消息会分发出去给各自的响应处理过程处理
	这个分发过程，实际上是分发给操作系统，让操作系统去调用过程回调函数，也就是注册窗口类时指定的回调函数
	也就是说，窗口中发生的一切，都是因为消息发生变化而变化的，因此称为消息驱动机制

	大多数时候，交互都发生在消息处理中，因此消息处理过程函数（回调函数WAWindowProc）非常重要，
	参数：发出消息的窗口句柄（一般是自己的窗口），消息类型（WM_开头），消息参数1，消息参数2（两个消息参数可以是任何类型的指针或值）

	在Win32或者MFC中，变量以H开头，表示句柄（一类资源的标识，可以理解为一种指针），
	以LP开头，表示这是一个指针，去掉LP之后就是对应的类型（结构或者值），
	含有STR表示这是一个字符串，比如LPSTR
	如果多了一个字母或者多个，比如LPCSTR C就标识const,因此标识一个字符串常量指针
	LPTSTR T标识一个自动适应字节的TCHAR，如果当前是UNICODE，那么就是WCHAR类型，否则就是char，同理TEXT()也是自动适应的
*/
#define WAWin32Main() WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nCmdShow)
LRESULT CALLBACK WAWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
ATOM WARegisterWindowClass(HINSTANCE hInstance, LPTSTR className);
BOOL WACreateWindowAndShow(HINSTANCE hInstance, int nCmdShow, LPTSTR className, LPTSTR wndName);
BOOL WADirectCreateWindow(HINSTANCE hInstance, LPTSTR wndName, LPTSTR className, int nCmdShow);
WPARAM WAMessageLoop();
void WADrawApplication(HWND hWnd,HDC hdc);
#endif //_WIN32APP_H_