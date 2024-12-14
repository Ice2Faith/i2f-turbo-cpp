#ifndef _GHIDEZBUFFER_H_
#define _GHIDEZBUFFER_H_
#include"GData.h"
#include<Windows.h>
/*深度缓冲算法数据结构*/
typedef struct
{
	double Deep;
	COLORREF color;
}ZBufferItem;
typedef struct
{
	ZBufferItem ** info;
	int height;
	int width;
}ZBufferData, *LPZBufferData;

class GHideZBuffer
{
public:
	/*
	隐面算法：
	对每个面上的所有像素点进行投影到屏幕
	选取离视点最近的点作为显示点即可
	*/
	static double D3FlatBlankingAlgorithm(double R, double aAngle, double bAngle, GD3Flat flat);
	/*深度缓冲算法ZBuffer*/
	static void ZBufferAlgorithm(GD3Flat * flat, COLORREF * color, int flatCount, int width, int height, HDC hdc, COLORREF bgcolor);
private:
	static LPZBufferData MakeZBufferData(int width, int height);
	static void FreeZbufferData(LPZBufferData * data);
	static void InitZBufferData(LPZBufferData zdata, double minDeep, COLORREF bgcolor);
	static void GetD3FlatExpr(GD3Flat flat, double * A, double * B, double * C, double * D);
	static GD2Flat ZBD3Flat2D2Falt(GD3Flat flat);
};
#endif // _GHIDEZBUFFER_H_