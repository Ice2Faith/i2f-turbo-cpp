#include<graphics.h>
#include<windows.h>
#include<time.h>
#include<math.h>
int SX = GetSystemMetrics(SM_CXSCREEN);
int SY = GetSystemMetrics(SM_CYSCREEN);
int WX = SX ;
int WY = SY ;
IMAGE bkimg;
unsigned int pixelArray[1920][2080];
double disradius = 0;
bool isBig = true;
double Distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(double((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))));
}
void GetImgPixel()
{
	SetWorkingImage(&bkimg);
	for (int i = 0; i < WY; i++)
	{
		for (int j = 0; j < WX; j++)
		{
			pixelArray[i][j] = getpixel(j,i);
		}
	}
	SetWorkingImage(NULL);
}
void DrawImgPixel()
{
	for (int i = 0; i < WY; i++)
	{
		for (int j = 0; j < WX; j++)
		{
			if (Distance(j,i,WX/2,WY/2)<disradius)
			putpixel(j, i, pixelArray[i][j]);
		}
	}
	if (isBig)
	{
		if (disradius <= WY / 8)
			disradius += WY*1/150.0;
		else if (disradius <= WY / 6)
			disradius += WY*2/150.0;
		else if (disradius <= WY / 4)
			disradius += WY*3/150.0;
		else if (disradius <= WY / 2)
			disradius += WY * 5 / 150.0;
		else
			disradius += WY * 7 / 150.0;
	}
	else
	{
		if (disradius >= WY )
			disradius -= WY * 7 / 150.0;
		else if (disradius >= WY / 2)
			disradius -= WY * 5 / 150.0;
		else if (disradius >= WY / 4)
			disradius -= WY * 3 / 150.0;
		else if (disradius >= WY / 6)
			disradius -= WY * 2 / 150.0;
		else
			disradius -= WY * 1 / 150.0;
	}
	if (disradius > Distance(0,0,WX/2,WY/2))
		isBig = false;
	if (disradius < 0)
		isBig = true;

}
int main()
{
	srand((unsigned)time(NULL));
	HWND hwnd=initgraph(WX, WY);
	//设置窗口透明
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 254, LWA_ALPHA|LWA_COLORKEY);
	//设置窗口最底部
	SetWindowPos(hwnd, HWND_TOPMOST, SX / 2 - (WX / 2), SY / 2 - (WY / 2), WX, WY, SWP_SHOWWINDOW);
	//消除窗口边框
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	loadimage(&bkimg, "bkimg.jpg", WX, WY);
	GetImgPixel();
	
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		DrawImgPixel();
		FlushBatchDraw();
		Sleep(30);
		EndBatchDraw();
	}
	return 0;
}