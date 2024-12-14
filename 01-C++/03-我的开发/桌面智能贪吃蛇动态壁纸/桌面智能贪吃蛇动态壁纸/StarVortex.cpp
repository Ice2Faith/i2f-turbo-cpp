#include "stdafx.h"
#include "StarVortex.h"

StarVortex::StarVortex()
{
	SetDefaultArgument();
	SetWindowSize(720, 480);
	SetMaxCount(2000);
}

StarVortex::StarVortex(int width, int height, int count)
{
	SetDefaultArgument();
	SetWindowSize(width,height);
	SetMaxCount(count);
}

void StarVortex::SetDefaultArgument()
{
	mMaxCount = 2000;
	mLight = NULL;
	mWinWidth = 720;
	mWinHeight=480;
}


StarVortex::~StarVortex()
{
	if (mLight != NULL)
	{
		free(mLight);
	}
}

void StarVortex::SetMaxCount(int count)
{
	if (mLight != NULL)
	{
		free(mLight);
		mLight = NULL;
	}
	mMaxCount = count;
	mLight = (Light*)malloc(sizeof(Light)*mMaxCount);
}

void StarVortex::SetWindowSize(int width, int height)
{
	mWinWidth = width;
	mWinHeight = height;
}
void StarVortex::SetLightToDefault(int index)
{
	static double lastDirect = 0;
	POINT cursor = { 0 };
	GetCursorPos(&cursor);
	
	mLight[index].x = cursor.x;
	mLight[index].y = cursor.y;

	mLight[index].live = false;
	/*mLight[index].x = mWinWidth / 2;
	mLight[index].y = mWinHeight / 2;*/
	
	mLight[index].direc = lastDirect + ((rand() % 15) / 180.0*3.141592653549);
	if (mLight[index].direc > 2 * 3.141592653549)
	{
		mLight[index].direc -= 2 * 3.141592653549;
	}
	lastDirect = mLight[index].direc;

	mLight[index].speed = rand() % (mWinWidth * 1 / 150) + 1;
	if (mLight[index].speed == 1) mLight[index].speed = 2;
	mLight[index].r = rand() % 200 + 54;
	mLight[index].b = rand() % 200 + 54;
	mLight[index].g = rand() % 200 + 54;
	mLight[index].curR =1;
	mLight[index].addR = (rand() % 100 + 1)%100;
	mLight[index].curDis = 0;

}

void StarVortex::InitLight()
{
	for (int i = 0; i < mMaxCount; i++)
	{
		SetLightToDefault(i);
		if (3 > rand() % 100)
			mLight[i].live = true;
		else
			mLight[i].live = false;
	}
}
void StarVortex::CreateLight()
{
	int maxCount = mMaxCount / 100.0;
	if (maxCount <= 0)
		maxCount = 1;
	int curCount = 0;
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mLight[i].live == false)
		{
			if (rand() % 100 < 21)
			{
				SetLightToDefault(i);
				mLight[i].live = true;
				curCount++;
			}
		}
		if (curCount >= maxCount)
			break;
	}
}
void StarVortex::DrawBackground(HDC hdc)
{
	double winMaxDis = sqrt(pow(mWinWidth*0.6,2.0)+pow(mWinHeight*0.6,2.0));
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mLight[i].live)
		{
			int px = mLight[i].x + mLight[i].curDis*cos(mLight[i].direc);
			int py = mLight[i].y + mLight[i].curDis*sin(mLight[i].direc);

			COLORREF cor = RGB(mLight[i].r,mLight[i].g,mLight[i].b);
			HPEN pen = CreatePen(0, 1, cor);
			HGDIOBJ op=SelectObject(hdc, pen);
			HBRUSH brush = CreateSolidBrush(cor);
			HGDIOBJ ob = SelectObject(hdc, brush);
			
			mLight[i].curR = 8.0*mLight[i].curDis / winMaxDis;
			if (mLight[i].curR <= 1)
				mLight[i].curR = 1;

			Ellipse(hdc, px - mLight[i].curR, py - mLight[i].curR, px + mLight[i].curR, py + mLight[i].curR);

			DeleteObject(op);
			DeleteObject(pen);
			DeleteObject(ob);
			DeleteObject(brush);

			/////////////////////////////////
			mLight[i].curDis += mLight[i].speed;
			mLight[i].speed += 0.1;

			if (mLight[i].curDis > winMaxDis && rand() % 100 < 12)
				mLight[i].live = false;

			//if (rand() % 100 < 85)
			{
				int rfac = (300 - (280.0*(mLight[i].curDis>winMaxDis ? winMaxDis : mLight[i].curDis) / winMaxDis));
				rfac = rfac<2 ? 2 : rfac;
				mLight[i].direc = ((((rand() % rfac)/10.0) / 180.0*3.141592653549) + mLight[i].direc)*0.3 + mLight[i].direc*0.7;
				if (mLight[i].direc > 3.141592653549*2)
					mLight[i].direc -= 3.141592653549*2;
			}

			////////////////////////////////
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
			CreateLight();
			isDown = true;
			last_create_time = GetTickCount();
			break;
		}
	}

	//如果没有任何按键按下，如果距离上一次创建粒子时间超过了一个时间，那就创建一次
	if (isDown == false)
	{
		DWORD now_time = GetTickCount();
		int diff = rand() % 170 + 80;//时间随机到此区间
		if (now_time - last_create_time > diff)
		{
			CreateLight();
			last_create_time = now_time;
		}
	}
	

}