#pragma once
#include<windows.h>

#include<math.h>
#include<stdlib.h>
#include<time.h>
class ScatteringLight
{
public:
	 typedef struct
	{
		int x;
		int y;
		double direc;
		float speed;
		bool live;
		int r;
		int b;
		int g;
	}Light;
	ScatteringLight();
	ScatteringLight(int width, int height,int count);
	~ScatteringLight();
	void InitLight();
	void DrawBackground(HDC hdc);
	void SetMaxCount(int count);
	void SetWindowSize(int width, int height);
private:
	void SetDefaultArgument();
	void CreateLight();

	int mMaxCount; //������������������Խ�࣬ռ��CPU����Խ�ߣ�Խ������Ļ�Ͻ���ûʲô����
	Light * mLight;

	int mWinWidth;
	int mWinHeight;
};

