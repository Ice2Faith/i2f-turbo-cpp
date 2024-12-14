#include "stdafx.h"
#include "TraceMouseStar.h"

TraceMouseStar::TraceMouseStar()
{
	SetDefaultArgument();
	SetWindowSize(720, 480);
	SetMaxCount(2000);
}

TraceMouseStar::TraceMouseStar(int width, int height, int count)
{
	SetDefaultArgument();
	SetWindowSize(width, height);
	SetMaxCount(count);
}

void TraceMouseStar::SetDefaultArgument()
{
	mMaxCount = 50;
	mNode = NULL;
	mWinWidth = 720;
	mWinHeight = 480;
}


TraceMouseStar::~TraceMouseStar()
{
	if (mNode != NULL)
	{
		free(mNode);
	}
}

void TraceMouseStar::SetMaxCount(int count)
{
	if (mNode != NULL)
	{
		free(mNode);
		mNode = NULL;
	}
	mMaxCount = count;
	mNode = (StarNode*)malloc(sizeof(StarNode)*mMaxCount);
}

void TraceMouseStar::SetWindowSize(int width, int height)
{
	mWinWidth = width;
	mWinHeight = height;
}


void TraceMouseStar::InitNode()
{
	for (int i = 0; i < mMaxCount; i++)
	{
		if (rand()%100<30)
			mNode[i].live = true;
		else
			mNode[i].live = false;
		ResetNodeArgs(i);
	}
}
double TraceMouseStar::AngleToRadian(double angle)
{
	return angle / 180.0*3.14159265354985;
}
short TraceMouseStar::getR(COLORREF color)
{
	return color & 0xff;
}
short TraceMouseStar::getG(COLORREF color)
{
	return (color >> 8) & 0xff;
}
short TraceMouseStar::getB(COLORREF color)
{
	return (color >> 16) & 0xff;
}
void TraceMouseStar::ResetNodeArgs(int pos)
{
	POINT cursor = { 0 };
	GetCursorPos(&cursor);
	mNode[pos].x = cursor.x;
	mNode[pos].y = cursor.y;;
	mNode[pos].speed = rand() % (mWinHeight * 1 / 100) + 1;
	if (mNode[pos].speed == 1) mNode[pos].speed = 2;
	mNode[pos].r = rand() % 200 + 54;
	mNode[pos].b = rand() % 200 + 54;
	mNode[pos].g = rand() % 200 + 54;
	mNode[pos].curTime = 0;
	mNode[pos].maxTimes = rand() % 35 + 5;
	mNode[pos].live = false;
	mNode[pos].direct = AngleToRadian(rand()%360);
	mNode[pos].size = rand() % 28 + 2;

}
void TraceMouseStar::CreateNode()
{
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mNode[i].live == false)
		{
			if (rand() % 100 < 20)
			{
				ResetNodeArgs(i);
				mNode[i].live = true;
			}
		}
	}
}
void TraceMouseStar::DrawBackground(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mNode[i].live)
		{
			int r = mNode[i].r;
			int g = mNode[i].g;
			int b = mNode[i].b;
			if (mNode[i].curTime % 8<4){
				r *= 0.6;
				g *= 0.6;
				b *= 0.6;
			}
			SetPixelV(hdc, mNode[i].x, mNode[i].y, RGB(r,g,b));
			int size = mNode[i].size;
			for (int j = 0; j < size; j++)
			{
				double rate = j *1.0/ size;
				int ux = mNode[i].x;
				int uy = mNode[i].y - j;
				COLORREF uc = GetPixel(hdc, ux, uy);
				SetPixelV(hdc, ux, uy, RGB(r*(1.0 - rate) + getR(uc)*rate, g*(1.0 - rate) + getG(uc)*rate, b*(1.0 - rate) + getB(uc)*rate));

				int dx = mNode[i].x;
				int dy = mNode[i].y + j;
				COLORREF dc = GetPixel(hdc, dx, dy);
				SetPixelV(hdc, dx, dy, RGB(r*(1.0 - rate) + getR(dc)*rate, g*(1.0 - rate) + getG(dc)*rate, b*(1.0 - rate) + getB(dc)*rate));

				int lx = mNode[i].x - j;
				int ly = mNode[i].y;
				COLORREF lc = GetPixel(hdc, lx, ly);
				SetPixelV(hdc, lx, ly, RGB(r*(1.0 - rate) + getR(lc)*rate, g*(1.0 - rate) + getG(lc)*rate, b*(1.0 - rate) + getB(lc)*rate));

				int rx = mNode[i].x+ j;
				int ry = mNode[i].y ;
				COLORREF rc = GetPixel(hdc, rx, ry);
				SetPixelV(hdc, rx, ry, RGB(r*(1.0 - rate) + getR(rc)*rate, g*(1.0 - rate) + getG(rc)*rate, b*(1.0 - rate) + getB(rc)*rate));
			}
		}

		mNode[i].x += mNode[i].speed*cos(mNode[i].direct);
		mNode[i].y += mNode[i].speed*sin(mNode[i].direct);

		mNode[i].curTime++;

		if (mNode[i].curTime == mNode[i].maxTimes){
			mNode[i].live = false;
		}

	}
	//记录上一次创建新的粒子的时间
	static DWORD last_create_time = GetTickCount();

	//判断是否有任何按键按下，如果有任何按键按下，就创建粒子
	bool isDown = false;
	//最小的虚拟键码就是VK_LBUTTON，值为0x01
	for (int i = 1; i < 256; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			CreateNode();
			isDown = true;
			last_create_time = GetTickCount();
			break;
		}
	}

	//如果没有任何按键按下，如果距离上一次创建粒子时间超过了一个时间，那就创建一次
	if (isDown == false)
	{
		DWORD now_time = GetTickCount();
		int diff = rand() % 1700 + 300;//时间随机到300-2000ms,也就是0.3-2秒之内随机
		if (now_time - last_create_time > diff)
		{
			CreateNode();
			last_create_time = now_time;
		}
	}
}
