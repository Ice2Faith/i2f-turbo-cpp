#pragma once

#include<Windows.h>

#include<math.h>
#include<stdlib.h>
#include<time.h>
class IntelligentNetwork
{
public:
	typedef struct
	{
		double x;
		double y;
		double direc;
		double speed;
		double maxDis;
		bool live;
		double curDis;
		double maxRadius;
		double minRadius;
		double curRadius;
		double stepRadius;
		bool radiusVary;
		int r;
		int b;
		int g;
		int linkedIndexArr[10];
		int linkedCount;
	}Light;
	IntelligentNetwork();
	IntelligentNetwork(int width, int height, int count);
	~IntelligentNetwork();
	void InitLight();
	void DrawBackground(HDC hdc);
	void SetMaxCount(int count);
	void SetWindowSize(int width, int height);
private:
	void SetDefaultArgument();
	void CreateLight();
	void SetLightToDefault(int index);
	void BuildLinkRelation(int index);
	void UpdateLinkRelation(int index);

	int mMaxCount; //������������������Խ�࣬ռ��CPU����Խ�ߣ�Խ������Ļ�Ͻ���ûʲô����
	Light * mLight;

	int mWinWidth;
	int mWinHeight;

	int extendDistance;
};

