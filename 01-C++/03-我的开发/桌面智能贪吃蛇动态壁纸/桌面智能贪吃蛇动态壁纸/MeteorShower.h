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

	int mMaxCount; //������������������Խ�࣬ռ��CPU����Խ�ߣ�Խ������Ļ�Ͻ���ûʲô����
	Light * mLight;

	int mWinWidth;
	int mWinHeight;
};

