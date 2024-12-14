#pragma once
#include"graphics\GData.h"
#include"graphics\GProjection.h"
#include"graphics\GStereo.h"
#include"graphics\GVary.h"
#include"graphics\GTranglelized.h"
class D3EmitBall
{
public:
	typedef struct
	{
		double len;
		double aAngleDirect;
		double bAngleDirect;
		double aAngleStep;
		double bAngleStep;
		double maxLen;
		double lenStep;
		double clipLen;
		bool live;
		int r;
		int b;
		int g;
		GD3DataGroup * head4;
	}Light;
	D3EmitBall();
	D3EmitBall(int width, int height, int count);
	~D3EmitBall();
	void InitLight();
	void DrawBackground(HDC hdc);
	void SetMaxCount(int count);
	void SetWindowSize(int width, int height);
	void makeUniqueStereo();
private:
	void SetDefaultArgument();
	void CreateLight();
	void SetLightToDefault(int index);
	void drawD3Data(HDC hdc, GD3DataGroup * gddata, double viewR, double viewD);
	void drawHead4(HDC hdc, int index, GD3Point & relpoint, double viewR, double viewD);

	int mMaxCount; //定义粒子数量，数量越多，占用CPU运算越高，越少则屏幕上将会没什么东西
	Light * mLight;

	int mWinWidth;
	int mWinHeight;

	GD3DataGroup * m_storeo;
	double xAngleDirect;
	double yAngleDirect;
	double zAngleDirect;
	double xAngleStep;
	double yAngleStep;
	double zAngleStep;

	int roundR;
	double roundAAngle;
	double roundBAngle;
};

