#include "stdafx.h"
#include "IntelligentNetwork.h"

IntelligentNetwork::IntelligentNetwork()
{
	SetDefaultArgument();
	SetWindowSize(720, 480);
	SetMaxCount(200);
}

IntelligentNetwork::IntelligentNetwork(int width, int height, int count)
{
	SetDefaultArgument();
	SetWindowSize(width, height);
	SetMaxCount(count);
}

void IntelligentNetwork::SetDefaultArgument()
{
	extendDistance = 200;
	mMaxCount = 200;
	mLight = NULL;
	mWinWidth = 720;
	mWinHeight = 480;
}


IntelligentNetwork::~IntelligentNetwork()
{
	if (mLight != NULL)
	{
		free(mLight);
	}
}

void IntelligentNetwork::SetMaxCount(int count)
{
	if (mLight != NULL)
	{
		free(mLight);
		mLight = NULL;
	}
	mMaxCount = count;
	mLight = (Light*)malloc(sizeof(Light)*mMaxCount);
}

void IntelligentNetwork::SetWindowSize(int width, int height)
{
	mWinWidth = width;
	mWinHeight = height;
}
void IntelligentNetwork::SetLightToDefault(int index)
{
	mLight[index].x = rand()%(mWinWidth+extendDistance)-(extendDistance/2);
	mLight[index].y = rand() % (mWinHeight + extendDistance) - (extendDistance / 2);

	mLight[index].live = false;

	mLight[index].direc = ((rand() % 360) / 180.0*3.141592653549);
	if (mLight[index].direc > 2 * 3.141592653549)
	{
		mLight[index].direc -= 2 * 3.141592653549;
	}


	mLight[index].speed = rand() % (mWinWidth * 1 / 100) + 1;
	mLight[index].r = rand() % 200 + 54;
	mLight[index].b = rand() % 200 + 54;
	mLight[index].g = rand() % 200 + 54;
	mLight[index].maxDis = rand()%(mWinWidth*4/10)+(mWinWidth*2/10);
	mLight[index].curDis = 0;

	mLight[index].maxRadius = rand() % 5 + 5.0;
	mLight[index].minRadius = rand() % 5 + 1.0;
	mLight[index].stepRadius= (rand()%10+1)/20.0;
	mLight[index].curRadius = mLight[index].minRadius;
	mLight[index].radiusVary = true;

	BuildLinkRelation(index);
}

void IntelligentNetwork::BuildLinkRelation(int index)
{
	mLight[index].linkedCount = rand() % (sizeof(mLight[index].linkedIndexArr) / sizeof(int));

	if (rand() % 100 < 75 && mLight[index].linkedCount>=2)
		mLight[index].linkedCount /= 2;
	
	if (mLight[index].linkedCount == 0){
		mLight[index].linkedCount = 1;
	}
	for (int i = 0; i < mLight[index].linkedCount; i++)
	{
		mLight[index].linkedIndexArr[i] = rand() % mMaxCount;
	}
}

void IntelligentNetwork::UpdateLinkRelation(int index)
{
	int befCount = mLight[index].linkedCount;
	int newCount = rand() % (sizeof(mLight[index].linkedIndexArr) / sizeof(int));
	if (rand() % 100<75 && newCount>=2)
		newCount /= 2;

	if (newCount == 0){
		newCount = 1;
	}

	if (newCount == befCount){
		return;
	}

	mLight[index].linkedCount = newCount;

	if (newCount > befCount)
	{
		for (int i = befCount; i < newCount; i++)
		{
			mLight[index].linkedIndexArr[i] = rand() % mMaxCount;
		}
	}
	else
	{
		for (int i = befCount-1; i > newCount; i--)
		{
			mLight[index].linkedIndexArr[rand() % newCount] = mLight[index].linkedIndexArr[i];
		}
	}
}

void IntelligentNetwork::InitLight()
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
void IntelligentNetwork::CreateLight()
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
void IntelligentNetwork::DrawBackground(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);

	POINT tp = {0};
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mLight[i].live)
		{
			mLight[i].x += mLight[i].speed*cos(mLight[i].direc);
			mLight[i].y += mLight[i].speed*sin(mLight[i].direc);

			if (rand() % 100 < 12)
			{
				mLight[i].direc += ((rand() % 30 - 15) / 180.0*3.141592653549);
			}
			
			mLight[i].curDis += mLight[i].speed;

			

			if (mLight[i].radiusVary == true)
			{
				if (mLight[i].curRadius < mLight[i].maxRadius)
				{
					mLight[i].curRadius += mLight[i].stepRadius;
				}
				else{
					mLight[i].radiusVary = false;
				}
			}
			else{
				if (mLight[i].curRadius > mLight[i].minRadius)
				{
					mLight[i].curRadius -= mLight[i].stepRadius;
				}
				else{
					mLight[i].radiusVary = true;
				}
			}
			

			if (rand() % 100 < 5)
			{
				UpdateLinkRelation(i);
			}


			for (int k = 0; k < mLight[i].linkedCount; k++)
			{
				int ti = mLight[i].linkedIndexArr[k];
				if (mLight[ti].live)
				{
					double sumR = mLight[i].curRadius + mLight[ti].curRadius;
					double iR = mLight[i].curRadius / sumR;
					double tiR = mLight[ti].curRadius / sumR;

					int lr = (mLight[i].r*iR + mLight[ti].r*tiR);
					int lg = (mLight[i].g*iR + mLight[ti].g*tiR);
					int lb = (mLight[i].b*iR + mLight[ti].b*tiR);
					
					COLORREF color = RGB(lr, lg,lb );
					HPEN pen = CreatePen(rand()%3, 1, color);
					HGDIOBJ obj = SelectObject(hdc, pen);

					MoveToEx(hdc, mLight[i].x, mLight[i].y, &tp);
					LineTo(hdc, mLight[ti].x, mLight[ti].y);

					SelectObject(hdc, obj);
					DeleteObject(pen);
					DeleteObject(obj);
				}
			}
			
			COLORREF color = RGB(mLight[i].r,mLight[i].g,mLight[i].b);
			HPEN pen = CreatePen(1, 1, color);
			HGDIOBJ op = SelectObject(hdc, pen);
			HBRUSH brush = CreateSolidBrush(color);
			HGDIOBJ ob = SelectObject(hdc, brush);

			Ellipse(hdc, mLight[i].x - mLight[i].curRadius, mLight[i].y - mLight[i].curRadius, mLight[i].x + mLight[i].curRadius, mLight[i].y + mLight[i].curRadius);


			SelectObject(hdc, op);
			SelectObject(hdc, ob);
			DeleteObject(pen);
			DeleteObject(brush);
			DeleteObject(op);
			DeleteObject(ob);

			if (mLight[i].curDis > mLight[i].maxDis && rand() % 100 < 20)
				mLight[i].live = false;

			if (mLight[i].x <= 0 - extendDistance || mLight[i].x > mWinWidth + extendDistance || mLight[i].y <= 0 - extendDistance || mLight[i].y > mWinHeight + extendDistance)
			{
				mLight[i].live = false;
			}

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