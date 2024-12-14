#ifndef _GHIDEZBUFFER_H_
#define _GHIDEZBUFFER_H_
#include"GData.h"
#include<Windows.h>
/*��Ȼ����㷨���ݽṹ*/
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
	�����㷨��
	��ÿ�����ϵ��������ص����ͶӰ����Ļ
	ѡȡ���ӵ�����ĵ���Ϊ��ʾ�㼴��
	*/
	static double D3FlatBlankingAlgorithm(double R, double aAngle, double bAngle, GD3Flat flat);
	/*��Ȼ����㷨ZBuffer*/
	static void ZBufferAlgorithm(GD3Flat * flat, COLORREF * color, int flatCount, int width, int height, HDC hdc, COLORREF bgcolor);
private:
	static LPZBufferData MakeZBufferData(int width, int height);
	static void FreeZbufferData(LPZBufferData * data);
	static void InitZBufferData(LPZBufferData zdata, double minDeep, COLORREF bgcolor);
	static void GetD3FlatExpr(GD3Flat flat, double * A, double * B, double * C, double * D);
	static GD2Flat ZBD3Flat2D2Falt(GD3Flat flat);
};
#endif // _GHIDEZBUFFER_H_