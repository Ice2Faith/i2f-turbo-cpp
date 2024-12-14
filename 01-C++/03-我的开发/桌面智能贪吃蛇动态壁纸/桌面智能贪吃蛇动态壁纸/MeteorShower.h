#pragma once

#include<Windows.h>

#include<math.h>
#include<stdlib.h>
#include<time.h>
class MeteorShower
{
public:
	 typedef struct
	{
		int x;
		int y;
		double direc;
		float speed;
		int len;
		bool live;
		int maxTurned;
		int curTruned;
		bool isLight;
		int r;
		int b;
		int g;
	}Light;
	 MeteorShower();
	 MeteorShower(int width, int height, int count);
	 ~MeteorShower();
	void InitLight();
	void DrawBackground(HDC hdc);
	void SetMaxCount(int count);
	void SetWindowSize(int width, int height);
private:
	void SetDefaultArgument();
	void CreateLight();
	void SetLightToDefault(int index);

	int mMaxCount; //定义粒子数量，数量越多，占用CPU运算越高，越少则屏幕上将会没什么东西
	Light * mLight;

	int mWinWidth;
	int mWinHeight;
};

