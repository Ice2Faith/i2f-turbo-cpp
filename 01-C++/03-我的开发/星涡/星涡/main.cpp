#include<graphics.h>
#include"StarVortex.h"

int main(int argc, char * argv[])
{
	int winWid = GetSystemMetrics(SM_CXSCREEN);
	int winHei = GetSystemMetrics(SM_CYSCREEN);;
	HWND hwnd=initgraph(winWid,winHei);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	StarVortex vortext;
	vortext.SetWindowSize(winWid,winHei);
	vortext.SetMaxCount(2000);
	vortext.InitLight();

	while (1)
	{
		BeginBatchDraw();

		cleardevice();

		vortext.DrawBackground(GetImageHDC());

		EndBatchDraw();

		Sleep(24);
	}


	return 0;
}