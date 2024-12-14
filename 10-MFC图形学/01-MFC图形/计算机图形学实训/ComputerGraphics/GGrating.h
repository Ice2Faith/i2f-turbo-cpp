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
	//创建Bezier旋转体绕Y轴
	static GD3DataGroup* CreateBezierSpinYCube(GD2Point ctrlPoints[],int ctrlPointCount,int tCount=30,int rAngleCount=50);
	//创建Bezier旋转体绕X轴
	static GD3DataGroup* CreateBezierSpinXCube(GD2Point ctrlPoints[],int ctrlPointCount,int tCount=30,int rAngleCount=50);

	//创建PolyLine旋转体绕Y轴,tCount<=0时，不进行重算，直接使用ctrlPointCount
	static GD3DataGroup* CreatePolyLineSpinYCube(GD2Point ctrlPoints[], int ctrlPointCount, int tCount = 30, int rAngleCount = 50);
	//创建PolyLine旋转体绕X轴,tCount<=0时，不进行重算，直接使用ctrlPointCount
	static GD3DataGroup* CreatePolyLineSpinXCube(GD2Point ctrlPoints[], int ctrlPointCount, int tCount = 30, int rAngleCount = 50);
private:
	static double Bernstein(int i, int n, double t);
	static double BezierX(int n, double t, GD2Point points[]);
	static double BezierY(int n, double t, GD2Point points[]);
};
#endif //_GGRATING_H_