//#include "stdafx.h"
#include "MeteorShower.h"

MeteorShower::MeteorShower()
{
	SetDefaultArgument();
	SetWindowSize(720, 480);
	SetMaxCount(2000);
}

MeteorShower::MeteorShower(int width, int height, int count)
{
	SetDefaultArgument();
	SetWindowSize(width,height);
	SetMaxCount(count);
}

void MeteorShower::SetDefaultArgument()
{
	mMaxCount = 2000;
	mLight = NULL;
	mWinWidth = 720;
	mWinHeight=480;
}


MeteorShower::~MeteorShower()
{
	if (mLight != NULL)
	{
		free(mLight);
	}
}

void MeteorShower::SetMaxCount(int count)
{
	if (mLight != NULL)
	{
		free(mLight);
		mLight = NULL;
	}
	mMaxCount = count;
	mLight = (Light*)malloc(sizeof(Light)*mMaxCount);
}

void MeteorShower::SetWindowSize(int width, int height)
{
	mWinWidth = width;
	mWinHeight = height;
}
void MeteorShower::SetLightToDefault(int index)
{
	//POINT cursor = { 0 };
	//GetCursorPos(&cursor);

	if (rand() % 2 == 1)
	{
		mLight[index].x = rand() % mWinWidth;
		mLight[index].y = 0;
	}
	else
	{
		mLight[index].x =  0;
		mLight[index].y =rand() % (mWinHeight/2);
	}

	mLight[index].live = false;
	
	mLight[index].direc =  ((rand() % 60+10) / 180.0*3.141592653549);

	mLight[index].speed = rand() % (mWinHeight * 1 / 50) + (mWinHeight * 1 / 100);
	mLight[index].r = rand() % 200 + 54;
	mLight[index].b = rand() % 200 + 54;
	mLight[index].g = rand() % 200 + 54;
	if (rand()%100<80)
		mLight[index].len = rand() % (mWinHeight / 20) + 3;
	else
		mLight[index].len = rand() % (mWinHeight / 10) + 10;
	mLight[index].maxTurned = rand() % 5+2;
	mLight[index].curTruned = 0;
	mLight[index].isLight = true;
}

void MeteorShower::InitLight()
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
void MeteorShower::CreateLight()
{
	int maxCount = rand() % mMaxCount+1;
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
void MeteorShower::DrawBackground(HDC hdc)
{
	static int PER_SIFT = 3;
	for (int i = 0; i < mMaxCount; i++)
	{
		int ex = 0, ey = 0;
		int er = 0, eg = 0, eb = 0;
		if (mLight[i].live)
		{
			mLight[i].curTruned++;
			if (mLight[i].curTruned == mLight[i].maxTurned)
			{
				mLight[i].curTruned = 0;
				mLight[i].isLight = !mLight[i].isLight;
			}

			double dposx = cos(mLight[i].direc);
			double dposy = sin(mLight[i].direc);

			double maxWid = 8;
			for (int k = 0; k<maxWid; k++)
			{
				double hrate = k*1.0 / maxWid;
				int plen = mLight[i].len*(1.0-hrate);
				double chrate = hrate;
				if (mLight[i].isLight == false)
				{
					chrate *= 0.4;
				}
				int pr = mLight[i].r*(1.0 - chrate);
				int pg = mLight[i].g*(1.0 - chrate);
				int pb = mLight[i].b*(1.0 - chrate);
				
				for (int p = 0; p < 2; p++)		   
				{
					double fac = (3.141592653549 / 2);
					if (p==1)
						fac = 0.0 - fac;
					int tpx = mLight[i].x + k*cos(mLight[i].direc + fac);
					int tpy = mLight[i].y + k*sin(mLight[i].direc + fac);
					COLORREF bkc = GetPixel(hdc, tpx, tpy);
					int br = bkc & 0xff;
					int bg = (bkc >> 8) & 0xff;
					int bb = (bkc >> 16) & 0xff;
					pr += br*chrate;
					pg += bg*chrate;
					pb += bb*chrate;
					
					
					for (int j = maxWid*hrate; j < plen * PER_SIFT; j++)
					{
						ex = tpx - j*dposx;
						ey = tpy - j*dposy;

						double rate = j*1.0 / (plen * PER_SIFT);
						bkc = GetPixel(hdc, ex, ey);
						br = bkc & 0xff;
						bg = (bkc >> 8) & 0xff;
						bb = (bkc >> 16) & 0xff;

						er = pr*(1.0 - rate) + br*rate;
						eg = pg*(1.0 - rate) + bg*rate;
						eb = pb*(1.0 - rate) + bb*rate;

						SetPixelV(hdc, ex, ey, RGB(er, eg, eb));
					}
				}
				
			}

			mLight[i].x = mLight[i].x + mLight[i].speed*dposx;
			mLight[i].y = mLight[i].y + mLight[i].speed*dposy;

			if ((ey>mWinHeight-mLight[i].len)&&(ex<0 || ey<0 || ex>mWinWidth || ey>mWinHeight))
				mLight[i].live = false;
		}
		

	}
	CreateLight();

}