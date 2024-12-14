#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#define WAITTIME (10*1000)	//等待运行时间
#define RUNTIME (5*60*1000)	//单次例程运行时间
//隐藏控制台窗口和任务栏图标
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
//获得屏幕尺寸
int SX = GetSystemMetrics(SM_CXSCREEN);
int SY = GetSystemMetrics(SM_CYSCREEN);
//添加一个开机自启动条目，条目名称为name，启动程序路径为bootpath
void RegAddBootItem(char * name, char * bootpath)
{
	HKEY hkey;
	char path[] = { "Software\\Microsoft\\Windows\\CurrentVersion\\Run" };
	RegOpenKey(HKEY_CURRENT_USER, path, &hkey);
	RegSetValueEx(hkey, name, 0, REG_SZ, (unsigned char *)bootpath, strlen(bootpath) + 1);
}
//鼠标无法选中窗口，躲避鼠标
void MoveAwayCursorForegroundWindow()
{
	long begintime = GetTickCount();
	long nowtime = begintime;
	while (1)
	{
		nowtime = GetTickCount();
		if (nowtime - begintime > RUNTIME)
			break;
		HWND hwnd = GetForegroundWindow();
		HWND selfhwnd = FindWindow(NULL, "点不着的窗口");
		if (hwnd == selfhwnd)
		{
			continue;
		}
		POINT cursor = { 0 };
		RECT wrect = { 0 };
		GetWindowRect(hwnd, &wrect);
		GetCursorPos(&cursor);
		int WndWid = wrect.right - wrect.left;
		int WndHei = wrect.bottom - wrect.top;
		if (WndWid > SX * 9 / 10)
		{
			WndWid = SX * 9 / 10;
		}
		if (WndHei > SY * 9 / 10)
		{
			WndHei = SY * 9 / 10;
		}
		if (cursor.x >= wrect.left&&cursor.x <= wrect.right&&
			cursor.y >= wrect.top&&cursor.y <= wrect.bottom)
		{
			int w_newx = rand() % (SX - WndWid);
			int w_newy = rand() % (SY - WndHei);
			MoveWindow(hwnd, w_newx, w_newy, WndWid, WndHei, true);
		}
		Sleep(30);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
}
//窗口任意方向撞击屏幕边缘后再随机移动方向
void MoveAnyDirectForegroundWindow()
{
	long begintime = GetTickCount();
	long nowtime = begintime;
	double direct = atan2(rand() % 100 - 50.0, rand() % 100 - 50.0);;
	begintime = nowtime = GetTickCount();
	while (1)
	{
		nowtime = GetTickCount();
		if (nowtime - begintime > RUNTIME)
			break;
		HWND hwnd = GetForegroundWindow();
		HWND selfhwnd = FindWindow(NULL, "点不着的窗口");
		if (hwnd == selfhwnd)
		{
			continue;
		}
		RECT wrect = { 0 };
		GetWindowRect(hwnd, &wrect);
		int WndWid = wrect.right - wrect.left;
		int WndHei = wrect.bottom - wrect.top;
		if (WndWid > SX * 9 / 10)
		{
			WndWid = SX * 9 / 10;
		}
		if (WndHei > SY * 9 / 10)
		{
			WndHei = SY * 9 / 10;
		}
		int w_newx = wrect.left + 3 * sin(direct);
		int w_newy = wrect.top + 3 * cos(direct);
		if (w_newx <= 0 || w_newx >= SX - WndWid||
			w_newy <= 0 || w_newy >= SY - WndHei)
		{
			direct = atan2(rand() % 100 - 50.0, rand() % 100 - 50.0);
		}
		MoveWindow(hwnd, w_newx, w_newy, WndWid, WndHei, true);
		Sleep(30);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
}
//将窗口放到任意位置进行任意大小缩放
void ExtendShrinkWindow()
{
	long begintime = GetTickCount();
	long nowtime = begintime;
	begintime = nowtime = GetTickCount();
	while (1)
	{
		nowtime = GetTickCount();
		if (nowtime - begintime > RUNTIME)
			break;
		HWND hwnd = GetForegroundWindow();
		HWND selfhwnd = FindWindow(NULL, "点不着的窗口");
		if (hwnd == selfhwnd||hwnd==NULL)
		{
			continue;
		}
		RECT wrect = { 0 };
		GetWindowRect(hwnd, &wrect);
		int WndWid = wrect.right - wrect.left;
		int WndHei = wrect.bottom - wrect.top;
		MoveWindow(hwnd, rand()%(SX/2), rand()%(SY/2), rand()%SX, rand()%SY, true);
		Sleep(30);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
}
int main(int argc, char * argv[])
{
	system("title 点不着的窗口");	//这个作为自己窗口名称，防止编译测试阶段无法中断退出
	system("mode con lines=5 cols=20");	//在不隐藏窗口的时候显示一个小窗口，能够点击退出
	srand((unsigned int)time(NULL));
	//RegAddBootItem("WindowBugs",argv[0]);
	Sleep(WAITTIME);	//等待一段时间在运行，防止第一反应就是刚打开的程序的问题
	int choice = rand() % 3;	//随机一个状态
	switch (choice)
	{
	case 0:
		MoveAwayCursorForegroundWindow();
		break;
	case 1:
		MoveAnyDirectForegroundWindow();
		break;
	case 2:
		ExtendShrinkWindow();
		break;
	}
	return 0;
}