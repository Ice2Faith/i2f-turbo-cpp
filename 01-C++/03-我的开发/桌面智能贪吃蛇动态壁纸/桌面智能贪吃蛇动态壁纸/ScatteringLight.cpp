#include "stdafx.h"
#include "ScatteringLight.h"

ScatteringLight::ScatteringLight()
{
	SetDefaultArgument();
	SetWindowSize(720, 480);
	SetMaxCount(2000);
}

ScatteringLight::ScatteringLight(int width, int height, int count)
{
	SetDefaultArgument();
	SetWindowSize(width,height);
	SetMaxCount(count);
}

void ScatteringLight::SetDefaultArgument()
{
	mMaxCount = 2000;
	mLight = NULL;
	mWinWidth = 720;
	mWinHeight=480;
}


ScatteringLight::~ScatteringLight()
{
	if (mLight != NULL)
	{
		free(mLight);
	}
}

void ScatteringLight::SetMaxCount(int count)
{
	if (mLight != NULL)
	{
		free(mLight);
		mLight = NULL;
	}
	mMaxCount = count;
	mLight = (Light*)malloc(sizeof(Light)*mMaxCount);
}

void ScatteringLight::SetWindowSize(int width, int height)
{
	mWinWidth = width;
	mWinHeight = height;
}


void ScatteringLight::InitLight()
{
	for (int i = 0; i < mMaxCount; i++)
	{
		if (3 > rand() % 100)
			mLight[i].live = true;
		else
			mLight[i].live = false;
		mLight[i].x = mWinWidth / 2;
		mLight[i].y = mWinHeight / 2;
		mLight[i].direc = atan2(rand() % 4096 - 2048.0, rand() % 4096 - 2048.0);
		mLight[i].speed = rand() % (mWinWidth * 1 / 100) + 1;
		if (mLight[i].speed == 1) mLight[i].speed = 2;
		mLight[i].r = rand() % 200 + 54;
		mLight[i].b = rand() % 200 + 54;
		mLight[i].g = rand() % 200 + 54;
	}
}
void ScatteringLight::CreateLight()
{
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mLight[i].live == false)
		{
			if (rand() % 100 < 21)
			{
				mLight[i].live = true;
				mLight[i].x = mWinWidth / 2;
				mLight[i].y = mWinHeight / 2;
				mLight[i].direc = atan2(rand() % 4096 - 2048.0, rand() % 4096 - 2048.0);
				mLight[i].speed = rand() % (mWinWidth * 1 / 100) + 1;
				if (mLight[i].speed == 1) mLight[i].speed = 2;
				mLight[i].r = rand() % 200 + 54;
				mLight[i].b = rand() % 200 + 54;
				mLight[i].g = rand() % 200 + 54;
			}
		}
	}
}
void ScatteringLight::DrawBackground(HDC hdc)
{
	POINT cursor = { 0 };
	GetCursorPos(&cursor);
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mLight[i].live)
		{
			SetPixelV(hdc, mLight[i].x, mLight[i].y, RGB(mLight[i].r, mLight[i].g, mLight[i].b));


			SetPixelV(hdc, mLight[i].x - 1, mLight[i].y, RGB(mLight[i].r - 20, mLight[i].g - 20, mLight[i].b - 20));
			SetPixelV(hdc, mLight[i].x + 1, mLight[i].y, RGB(mLight[i].r - 20, mLight[i].g - 20, mLight[i].b - 20));
			SetPixelV(hdc, mLight[i].x, mLight[i].y - 1, RGB(mLight[i].r - 20, mLight[i].g - 20, mLight[i].b - 20));
			SetPixelV(hdc, mLight[i].x, mLight[i].y + 1, RGB(mLight[i].r - 20, mLight[i].g - 20, mLight[i].b - 20));

		}
		if (rand() % 100 < 5)
		{
			POINT point = { 0 };
			point.x = mLight[i].x;
			point.y = mLight[i].y;
			//ClientToScreen(hwndThis, &point);
			double ndirect = atan2((double)cursor.y - point.y, (double)cursor.x - point.x);
			mLight[i].direc = (ndirect*0.3 + mLight[i].direc*0.7);
			//mLight[i].direc += (rand() % 30) / 180.0*3.1415926535;

			

		}
		mLight[i].speed += 0.02;
		
		mLight[i].x += mLight[i].speed*cos(mLight[i].direc);
		mLight[i].y += mLight[i].speed*sin(mLight[i].direc);
		if (rand() % 100 < 30)
		{
			mLight[i].x += rand() % 5 - 2;
			mLight[i].y += rand() % 5 - 2;
		}
		if (rand() % 100 < 7)
		{
			if (mLight[i].x <= mWinWidth * 0.1 || mLight[i].x > mWinWidth*0.9 || mLight[i].y <= mWinHeight*0.1 || mLight[i].y > mWinHeight*0.9)
			{
				for (int j = 0; j < 7; j++)
				{
					SetPixelV(hdc, mLight[i].x - (j + 1), mLight[i].y, RGB(mLight[i].r - (j * 10), mLight[i].g - (j * 3), mLight[i].b - (j * 2)));
					SetPixelV(hdc, mLight[i].x + (j + 1), mLight[i].y, RGB(mLight[i].r - (j * 10), mLight[i].g - (j * 3), mLight[i].b - (j * 2)));
					SetPixelV(hdc, mLight[i].x, mLight[i].y - (j + 1), RGB(mLight[i].r - (j * 10), mLight[i].g - (j * 3), mLight[i].b - (j * 2)));
					SetPixelV(hdc, mLight[i].x, mLight[i].y + (j + 1), RGB(mLight[i].r - (j * 10), mLight[i].g - (j * 3), mLight[i].b - (j * 2)));
				}

				mLight[i].live = false;
				continue;
			}
		}

		if (mLight[i].x <= 0 || mLight[i].x > mWinWidth || mLight[i].y <= 0 || mLight[i].y > mWinHeight)
		{
			mLight[i].live = false;
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
		int diff = rand() % 900 + 100;//时间随机到此区间
		if (now_time - last_create_time > diff)
		{
			CreateLight();
			last_create_time = now_time;
		}
	}

}