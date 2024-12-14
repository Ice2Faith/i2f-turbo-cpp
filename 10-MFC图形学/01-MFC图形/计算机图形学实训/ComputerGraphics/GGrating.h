#ifndef _GGRATING_H_
#define _GGRATING_H_
#include"GData.h"
#include<Windows.h>
class GGrating
{
public:
	static void BezierLine(HDC hdc, GD2Point points[], int pointCount,COLORREF color);
	static void DDALine(HDC hdc, GD2Point p1, GD2Point p2, COLORREF color);
	static void AntialiasLine(HDC hdc, GD2Point p1, GD2Point p2, COLORREF fgc, COLORREF bgc);
	static void SeedFillAlgorithm(HDC hdc, GD2Point seed, COLORREF bgc, COLORREF flc);
	static void TrangleFillScanLine(GD2Flat flat, COLORREF fillcolor, HDC hdc);
	//����Bezier��ת����Y��
	static GD3DataGroup* CreateBezierSpinYCube(GD2Point ctrlPoints[],int ctrlPointCount,int tCount=30,int rAngleCount=50);
	//����Bezier��ת����X��
	static GD3DataGroup* CreateBezierSpinXCube(GD2Point ctrlPoints[],int ctrlPointCount,int tCount=30,int rAngleCount=50);

	//����PolyLine��ת����Y��,tCount<=0ʱ�����������㣬ֱ��ʹ��ctrlPointCount
	static GD3DataGroup* CreatePolyLineSpinYCube(GD2Point ctrlPoints[], int ctrlPointCount, int tCount = 30, int rAngleCount = 50);
	//����PolyLine��ת����X��,tCount<=0ʱ�����������㣬ֱ��ʹ��ctrlPointCount
	static GD3DataGroup* CreatePolyLineSpinXCube(GD2Point ctrlPoints[], int ctrlPointCount, int tCount = 30, int rAngleCount = 50);
private:
	static double Bernstein(int i, int n, double t);
	static double BezierX(int n, double t, GD2Point points[]);
	static double BezierY(int n, double t, GD2Point points[]);
};
#endif //_GGRATING_H_