#include<graphics.h>
#include"MeteorShower.h"

int main(int argc, char * argv[])
{
	int winWid = GetSystemMetrics(SM_CXSCREEN);
	int winHei = GetSystemMetrics(SM_CYSCREEN);;
	HWND hwnd=initgraph(winWid,winHei);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	MeteorShower mate;
	mate.SetWindowSize(winWid, winHei);
	mate.SetMaxCount(50);
	mate.InitLight();

	while (1)
	{
		BeginBatchDraw();

		cleardevice();

		mate.DrawBackground(GetImageHDC());

		EndBatchDraw();

		Sleep(24);
	}


	return 0;
}