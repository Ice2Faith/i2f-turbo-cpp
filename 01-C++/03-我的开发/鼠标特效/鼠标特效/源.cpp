/** Name: 鼠标特效
Shift+Space:切换是否开启使用
*/
#include<stdio.h>
#include<graphics.h>
#include"TraceMouseStar.h"
void setWindowStyle(HWND hwnd,COLORREF bkColor)
{
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TOOLWINDOW;//添加透明、任务栏不显示图标属性
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	SetLayeredWindowAttributes(hwnd, bkColor, 0, LWA_COLORKEY);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);//去除边框属性

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);//设置窗口最前端，覆盖全屏
}
int main(int argc, char * argv[])
{
	int winWid = GetSystemMetrics(SM_CXSCREEN);
	int winHei = GetSystemMetrics(SM_CYSCREEN);

	HWND hwnd=initgraph(winWid,winHei);
	COLORREF bkColor = 0xffffff;

	setWindowStyle(hwnd,bkColor);

	setbkcolor(bkColor);
	cleardevice();

	TraceMouseStar star;
	star.SetWindowSize(winWid,winHei);
	star.SetMaxCount(120);
	star.InitNode();

	int SleepMillSec = 30;
	static bool isPowerState = true;

	int loopTimes = 60;
	int curloop = 0;
	
	COLORREF fcolor = RGB(0, 0, 255);

	
	while (1)
	{
		BeginBatchDraw();

		if (isPowerState)
		{
			

			SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);//始终保持最前端
			cleardevice();
			HDC hdc = GetImageHDC();	
			star.DrawBackground(hdc);


			POINT point = { 0 };
			GetCursorPos(&point);
			setcolor(bkColor);
			setfillcolor(bkColor);
			solidcircle(point.x, point.y, 3);

			

		}
		if ((0x8000 & GetAsyncKeyState(VK_CAPITAL)) && (0x8000 & GetAsyncKeyState(VK_TAB)))
		{
			curloop = loopTimes;
			fcolor = RGB(rand() % 156 + 100, rand() % 156 + 100, rand() % 106 + 150);

		}
		if (curloop == 0){			       
			cleardevice();
			curloop--;		
		}
		if (curloop>0)
		{
			if (isPowerState == false){
				cleardevice();
			}
			settextcolor(fcolor);
			LOGFONT lgfont = { 0 };
			lgfont.lfHeight = winHei * 8 / 100;
			double rateShrink = (1.0-(curloop*1.0 / loopTimes))*2;
			if (rateShrink > 1.0){
				rateShrink = 1.0; 
			}
			lgfont.lfHeight *= rateShrink;
			settextstyle(&lgfont);
			POINT curpos;
			GetCursorPos(&curpos);
			SYSTEMTIME sysTime = { 0 };
			GetLocalTime(&sysTime);
			TCHAR tpTime[1024] = { 0 };
			TCHAR weeks[][5] = { TEXT("日"), TEXT("一"), TEXT("二"), TEXT("三"), TEXT("四"), TEXT("五"), TEXT("六") };
			_stprintf(tpTime, TEXT("%04d-%02d-%02d %02d:%02d:%02d %s"), sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, weeks[sysTime.wDayOfWeek]);
			//TextOut(hdc, curpos.x, curpos.y, tpTime, lstrlen(tpTime));

			outtextxy(curpos.x, curpos.y, tpTime);

			curloop--;
		}
		
		if ((0x8000 & GetAsyncKeyState(VK_SHIFT))  && (0x8000 & GetAsyncKeyState(VK_SPACE)))
		{
			isPowerState = !isPowerState;
			cleardevice();
		}
			
		EndBatchDraw();
		Sleep(SleepMillSec);
	}

	closegraph();
	return 0;
}