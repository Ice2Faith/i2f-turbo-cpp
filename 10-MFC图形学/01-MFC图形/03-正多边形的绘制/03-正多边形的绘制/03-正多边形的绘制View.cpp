
// 03-������εĻ���View.cpp : CMy03������εĻ���View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "03-������εĻ���.h"
#endif

#include "03-������εĻ���Doc.h"
#include "03-������εĻ���View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<math.h>
//б���⻭��
//��άת��ά������X
#define V3TOV2X(x,y,z) (int)(x+y/2.0*cos(atan2(1.0,1.0)))
//��άת��ά������Y
#define V3TOV2Y(x,y,z) (int)(z+y/2.0*sin(atan2(1.0,1.0)))
//��άת��ά������X��Y
#define V3TOV2XY(x,y,z) (int)(x+y/2.0*cos(atan2(1.0,1.0))),(int)(z+y/2.0*sin(atan2(1.0,1.0)))
//ǿ������ת��
#define TOINT(x) (int)(x)
//���ݿռ�ֱ�߻�ȡ��ֱ�ߵ�����
#define VECTORLINE(x1,y1,z1,x2,y2,z2) (int)(x2-x1), (int)(y2-y1), (int)(z2-z1)
//��ȡ�ռ�ƽ��ķ�����
#define NORMALLINE(x1,y1,z1,x2,y2,z2) (int)(y1*z2 - y2*z1), (int)(x1*z2 - x2*z1), (int)(x1*y2 - x2*y1)
//��ȡ�ռ������ļн�
#define MATRIXCOS(x1,y1,z1,x2,y2,z2) ((x1*x2 + y1*y2 + z1*z2)*1.0 / (sqrt(pow(x1, 2.0)+pow(y1, 2.0)+pow(z1, 2.0))*sqrt(pow(x2, 2.0)+pow(y2, 2.0)+ pow(z2, 2.0))))

void CMy03������εĻ���View::ResetCenterOrg(CDC * pDC)
{
	//��������ϵ
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(rect.right, -rect.bottom);
}
void CMy03������εĻ���View::DrawOrgLine(CDC * pDC)
{
	//��������ϵ
	CPen pen(0,1,RGB(255, 0, 0));
	CPen * oldpen = pDC->SelectObject(&pen);
	pDC->MoveTo(V3TOV2XY(-2000, 0, 0));
	pDC->LineTo(V3TOV2XY(2000, 0, 0));

	pDC->MoveTo(V3TOV2XY(0, -2000, 0));
	pDC->LineTo(V3TOV2XY(0, 2000, 0));

	pDC->MoveTo(V3TOV2XY(0, 0, -2000));
	pDC->LineTo(V3TOV2XY(0, 0, 2000));
	pDC->SelectObject(oldpen);
}
void CMy03������εĻ���View::AllocMemery()
{
	int i = 0;
	this->m_points = (double **)malloc(this->m_pointcount*(sizeof(double*)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		this->m_points[i] = (double*)malloc(3 * sizeof(double));
	}
	this->m_trangle = (int **)malloc(this->m_tranglecount*(sizeof(int*)));
	for (i = 0; i<this->m_tranglecount; i++)
	{
		this->m_trangle[i] = (int*)malloc(m_vectorNum * sizeof(int));
	}
}
void CMy03������εĻ���View::CreateTetrahedron()
{
	//������
	m_vectorNum = 3;
	this->m_pointcount = 4;
	this->m_tranglecount = 4;
	AllocMemery();
	double a = 100;
	this->m_points[0][0] = a, this->m_points[0][1] = a, this->m_points[0][2] = a;
	this->m_points[1][0] = a, this->m_points[1][1] = -a, this->m_points[1][2] = -a;
	this->m_points[2][0] = -a, this->m_points[2][1] = -a, this->m_points[2][2] = a;
	this->m_points[3][0] = -a, this->m_points[3][1] = a, this->m_points[3][2] = -a;

	this->m_trangle[0][0] = 1, this->m_trangle[0][1] = 2, this->m_trangle[0][2] = 3;
	this->m_trangle[1][0] = 0, this->m_trangle[1][1] = 3, this->m_trangle[1][2] = 2;
	this->m_trangle[2][0] = 0, this->m_trangle[2][1] = 1, this->m_trangle[2][2] = 3;
	this->m_trangle[3][0] = 0, this->m_trangle[3][1] = 2, this->m_trangle[3][2] = 1;
}
void CMy03������εĻ���View::CreateHexahedron()
{
	//������
	m_vectorNum = 4;
	this->m_pointcount = 8;
	this->m_tranglecount = 6;
	int i = 0;
	AllocMemery();
	double a = 100;
	this->m_points[0][0] = a, this->m_points[0][1] = -a, this->m_points[0][2] = -a;
	this->m_points[1][0] = a, this->m_points[1][1] = a, this->m_points[1][2] = -a;
	this->m_points[2][0] = -a, this->m_points[2][1] = a, this->m_points[2][2] = -a;
	this->m_points[3][0] = -a, this->m_points[3][1] = -a, this->m_points[3][2] = -a;
	this->m_points[4][0] = a, this->m_points[4][1] = -a, this->m_points[4][2] = a;
	this->m_points[5][0] = a, this->m_points[5][1] = a, this->m_points[5][2] = a;
	this->m_points[6][0] = -a, this->m_points[6][1] = a, this->m_points[6][2] = a;
	this->m_points[7][0] = -a, this->m_points[7][1] = -a, this->m_points[7][2] = a;


	this->m_trangle[0][0] = 0, this->m_trangle[0][1] = 1, this->m_trangle[0][2] = 2, this->m_trangle[0][3] = 3;
	this->m_trangle[1][0] = 0, this->m_trangle[1][1] = 1, this->m_trangle[1][2] = 5, this->m_trangle[1][3] = 4;
	this->m_trangle[2][0] = 0, this->m_trangle[2][1] = 3, this->m_trangle[2][2] = 7, this->m_trangle[2][3] = 4;
	this->m_trangle[3][0] = 6, this->m_trangle[3][1] = 5, this->m_trangle[3][2] = 1, this->m_trangle[3][3] = 2;
	this->m_trangle[4][0] = 6, this->m_trangle[4][1] = 7, this->m_trangle[4][2] = 4, this->m_trangle[4][3] = 5;
	this->m_trangle[5][0] = 6, this->m_trangle[5][1] = 2, this->m_trangle[5][2] = 3, this->m_trangle[5][3] = 7;

}
void CMy03������εĻ���View::CreateOctahedron()
{
	//������
	m_vectorNum = 3;
	this->m_pointcount = 6;
	this->m_tranglecount = 8;
	AllocMemery();
	double r = 100;
	this->m_points[0][0] = 0, this->m_points[0][1] = r, this->m_points[0][2] = 0;
	this->m_points[1][0] = 0, this->m_points[1][1] = -r, this->m_points[1][2] = 0;
	this->m_points[2][0] = r, this->m_points[2][1] = 0, this->m_points[2][2] = 0;
	this->m_points[3][0] = 0, this->m_points[3][1] = 0, this->m_points[3][2] = -r;
	this->m_points[4][0] = -r, this->m_points[4][1] = 0, this->m_points[4][2] = 0;
	this->m_points[5][0] = 0, this->m_points[5][1] = 0, this->m_points[5][2] = r;

	this->m_trangle[0][0] = 0, this->m_trangle[0][1] = 4, this->m_trangle[0][2] = 5;
	this->m_trangle[1][0] = 0, this->m_trangle[1][1] = 5, this->m_trangle[1][2] = 2;
	this->m_trangle[2][0] = 0, this->m_trangle[2][1] = 2, this->m_trangle[2][2] = 3;
	this->m_trangle[3][0] = 0, this->m_trangle[3][1] = 3, this->m_trangle[3][2] = 4;
	this->m_trangle[4][0] = 1, this->m_trangle[4][1] = 5, this->m_trangle[4][2] = 4;
	this->m_trangle[5][0] = 1, this->m_trangle[5][1] = 2, this->m_trangle[5][2] = 5;
	this->m_trangle[6][0] = 4, this->m_trangle[6][1] = 3, this->m_trangle[6][2] = 2;
	this->m_trangle[7][0] = 1, this->m_trangle[7][1] = 4, this->m_trangle[7][2] = 3;
}
void CMy03������εĻ���View::CreateDodecahedron()
{
	//ʮ������
	m_vectorNum = 5;
	this->m_pointcount = 20;
	this->m_tranglecount = 12;
	int i = 0;
	AllocMemery();
	double a = 100;
	double b = a*0.61828;
	this->m_points[0][0] = a, this->m_points[0][1] = a, this->m_points[0][2] = a;
	this->m_points[1][0] = a + b, this->m_points[1][1] = 0, this->m_points[1][2] = b;
	this->m_points[2][0] = a, this->m_points[2][1] = -a, this->m_points[2][2] = a;
	this->m_points[3][0] = 0, this->m_points[3][1] = -b, this->m_points[3][2] = a + b;
	this->m_points[4][0] = 0, this->m_points[4][1] = b, this->m_points[4][2] = a + b;
	this->m_points[5][0] = a + b, this->m_points[5][1] = 0, this->m_points[5][2] = -b;
	this->m_points[6][0] = a, this->m_points[6][1] = a, this->m_points[6][2] = -a;
	this->m_points[7][0] = b, this->m_points[7][1] = a + b, this->m_points[7][2] = 0;
	this->m_points[8][0] = -b, this->m_points[8][1] = a + b, this->m_points[8][2] = 0;
	this->m_points[9][0] = -a, this->m_points[9][1] = a, this->m_points[9][2] = -a;
	this->m_points[10][0] = 0, this->m_points[10][1] = b, this->m_points[10][2] = -a - b;
	this->m_points[11][0] = a, this->m_points[11][1] = -a, this->m_points[11][2] = -a;
	this->m_points[12][0] = b, this->m_points[12][1] = -a - b, this->m_points[12][2] = 0;
	this->m_points[13][0] = -b, this->m_points[13][1] = -a - b, this->m_points[13][2] = 0;
	this->m_points[14][0] = -a - b, this->m_points[14][1] = 0, this->m_points[14][2] = b;
	this->m_points[15][0] = -a, this->m_points[15][1] = a, this->m_points[15][2] = a;
	this->m_points[16][0] = -a, this->m_points[16][1] = -a, this->m_points[16][2] = -a;
	this->m_points[17][0] = 0, this->m_points[17][1] = -b, this->m_points[17][2] = -a - b;
	this->m_points[18][0] = -a, this->m_points[18][1] = -a, this->m_points[18][2] = a;
	this->m_points[19][0] = -a - b, this->m_points[19][1] = 0, this->m_points[19][2] = -b;

	this->m_trangle[0][0] = 0, this->m_trangle[0][1] = 7, this->m_trangle[0][2] = 8, this->m_trangle[0][3] = 15, this->m_trangle[0][4] = 4;
	this->m_trangle[1][0] = 6, this->m_trangle[1][1] = 10, this->m_trangle[1][2] = 9, this->m_trangle[1][3] = 8, this->m_trangle[1][4] = 7;
	this->m_trangle[2][0] = 1, this->m_trangle[2][1] = 5, this->m_trangle[2][2] = 6, this->m_trangle[2][3] = 7, this->m_trangle[2][4] = 0;
	this->m_trangle[3][0] = 1, this->m_trangle[3][1] = 2, this->m_trangle[3][2] = 12, this->m_trangle[3][3] = 11, this->m_trangle[3][4] = 5;
	this->m_trangle[4][0] = 11, this->m_trangle[4][1] = 12, this->m_trangle[4][2] = 13, this->m_trangle[4][3] = 16, this->m_trangle[4][4] = 17;
	this->m_trangle[5][0] = 2, this->m_trangle[5][1] = 3, this->m_trangle[5][2] = 18, this->m_trangle[5][3] = 13, this->m_trangle[5][4] = 12;
	this->m_trangle[6][0] = 0, this->m_trangle[6][1] = 4, this->m_trangle[6][2] = 3, this->m_trangle[6][3] = 2, this->m_trangle[6][4] = 1;
	this->m_trangle[7][0] = 3, this->m_trangle[7][1] = 4, this->m_trangle[7][2] = 15, this->m_trangle[7][3] = 14, this->m_trangle[7][4] = 18;
	this->m_trangle[8][0] = 5, this->m_trangle[8][1] = 11, this->m_trangle[8][2] = 17, this->m_trangle[8][3] = 10, this->m_trangle[8][4] = 6;
	this->m_trangle[9][0] = 9, this->m_trangle[9][1] = 10, this->m_trangle[9][2] = 17, this->m_trangle[9][3] = 16, this->m_trangle[9][4] = 19;
	this->m_trangle[10][0] = 8, this->m_trangle[10][1] = 9, this->m_trangle[10][2] = 19, this->m_trangle[10][3] = 14, this->m_trangle[10][4] = 15;
	this->m_trangle[11][0] = 13, this->m_trangle[11][1] = 18, this->m_trangle[11][2] = 14, this->m_trangle[11][3] = 19, this->m_trangle[11][4] = 16;

}
void CMy03������εĻ���View::CreateIcosahedron()
{
	//��ʮ����
	m_vectorNum = 3;
	this->m_pointcount = 12;
	this->m_tranglecount = 20;
	AllocMemery();
	double a = 100;
	double b = a*0.61828;
	this->m_points[0][0] = 0, this->m_points[0][1] = a, this->m_points[0][2] = b;
	this->m_points[1][0] = 0, this->m_points[1][1] = b, this->m_points[1][2] = -b;
	this->m_points[2][0] = a, this->m_points[2][1] = b, this->m_points[2][2] = 0;
	this->m_points[3][0] = a, this->m_points[3][1] = -b, this->m_points[3][2] = 0;
	this->m_points[4][0] = 0, this->m_points[4][1] = -a, this->m_points[4][2] = -b;
	this->m_points[5][0] = 0, this->m_points[5][1] = -a, this->m_points[5][2] = b;
	this->m_points[6][0] = b, this->m_points[6][1] = 0, this->m_points[6][2] = a;
	this->m_points[7][0] = -b, this->m_points[7][1] = 0, this->m_points[7][2] = a;
	this->m_points[8][0] = b, this->m_points[8][1] = 0, this->m_points[8][2] = -a;
	this->m_points[9][0] = -b, this->m_points[9][1] = 0, this->m_points[9][2] = -a;
	this->m_points[10][0] = -a, this->m_points[10][1] = b, this->m_points[10][2] = 0;
	this->m_points[11][0] = -a, this->m_points[11][1] = -b, this->m_points[11][2] = 0;

	this->m_trangle[0][0] = 0, this->m_trangle[0][1] = 6, this->m_trangle[0][2] = 2;
	this->m_trangle[1][0] = 2, this->m_trangle[1][1] = 6, this->m_trangle[1][2] = 3;
	this->m_trangle[2][0] = 3, this->m_trangle[2][1] = 6, this->m_trangle[2][2] = 5;
	this->m_trangle[3][0] = 5, this->m_trangle[3][1] = 6, this->m_trangle[3][2] = 7;
	this->m_trangle[4][0] = 0, this->m_trangle[4][1] = 7, this->m_trangle[4][2] = 6;
	this->m_trangle[5][0] = 2, this->m_trangle[5][1] = 3, this->m_trangle[5][2] = 8;
	this->m_trangle[6][0] = 1, this->m_trangle[6][1] = 2, this->m_trangle[6][2] = 8;
	this->m_trangle[7][0] = 0, this->m_trangle[7][1] = 2, this->m_trangle[7][2] = 1;

	this->m_trangle[8][0] = 0, this->m_trangle[8][1] = 1, this->m_trangle[8][2] = 10;
	this->m_trangle[9][0] = 1, this->m_trangle[9][1] = 9, this->m_trangle[9][2] = 10;
	this->m_trangle[10][0] = 1, this->m_trangle[10][1] = 8, this->m_trangle[10][2] = 9;
	this->m_trangle[11][0] = 3, this->m_trangle[11][1] = 4, this->m_trangle[11][2] = 8;
	this->m_trangle[12][0] = 3, this->m_trangle[12][1] = 5, this->m_trangle[12][2] = 4;
	this->m_trangle[13][0] = 4, this->m_trangle[13][1] = 5, this->m_trangle[13][2] = 11;
	this->m_trangle[14][0] = 7, this->m_trangle[14][1] = 10, this->m_trangle[14][2] = 11;
	this->m_trangle[15][0] = 0, this->m_trangle[15][1] = 10, this->m_trangle[15][2] = 7;

	this->m_trangle[16][0] = 4, this->m_trangle[16][1] = 11, this->m_trangle[16][2] = 9;
	this->m_trangle[17][0] = 4, this->m_trangle[17][1] = 9, this->m_trangle[17][2] = 8;
	this->m_trangle[18][0] = 5, this->m_trangle[18][1] = 7, this->m_trangle[18][2] = 11;
	this->m_trangle[19][0] = 9, this->m_trangle[19][1] = 11, this->m_trangle[19][2] = 10;

}
void CMy03������εĻ���View::CreateBall()
{
	//���� ��������
	int aAngleCount = 300;
	int bAngleCount = 300;
	double r = 300;
	double PI = 3.1415926525;
	this->m_pointcount = aAngleCount*bAngleCount;
	int i = 0;
	this->m_points = (double **)malloc(this->m_pointcount*(sizeof(double*)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		this->m_points[i] = (double*)malloc(3 * sizeof(double));
	}
	for (i = 0; i < bAngleCount; i++)
	{
		for (int j = 0; j < aAngleCount; j++)
		{
			this->m_points[i*aAngleCount + j][0] = r*sin(2 * PI / aAngleCount* j)*sin(PI / bAngleCount* i);
			this->m_points[i*aAngleCount + j][2] = r*cos(2 * PI / aAngleCount*j);
			this->m_points[i*aAngleCount + j][1] = r*sin(2 * PI / aAngleCount* j)*cos(PI / bAngleCount* i);
		}
	}
}
void CMy03������εĻ���View::CreateCylinder()
{
	//Բ���� ��������
	int hCount = 300;
	int rAngleCount = 300;
	double r = 150;
	double h = 200;
	int rCount = 20;
	double PI = 3.1415926525;
	this->m_pointcount = hCount*rAngleCount+rCount*rAngleCount*2;
	int i = 0;
	this->m_points = (double **)malloc(this->m_pointcount*(sizeof(double*)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		this->m_points[i] = (double*)malloc(3 * sizeof(double));
	}
	//��������
	for (i = 0; i < hCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			this->m_points[i*rAngleCount + j][0] = r*cos(2 * PI / rAngleCount* j);
			this->m_points[i*rAngleCount + j][1] = r*sin(2 * PI / rAngleCount*j);
			this->m_points[i*rAngleCount + j][2] = h / hCount*i;
		}
	}
	//�µ���
	for (i = 0; i < rCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			this->m_points[hCount*rAngleCount + i*rAngleCount + j][0] = (r / rCount*i)*cos(2 * PI / rAngleCount* j);
			this->m_points[hCount*rAngleCount + i*rAngleCount + j][1] = (r / rCount*i)*sin(2 * PI / rAngleCount*j);
			this->m_points[hCount*rAngleCount + i*rAngleCount + j][2] = 0;
		}
	}
	//�ϵ���
	for (i = 0; i < rCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			this->m_points[hCount*rAngleCount + rCount*rAngleCount + i*rAngleCount + j][0] = (r / rCount*i)*cos(2 * PI / rAngleCount* j);
			this->m_points[hCount*rAngleCount + rCount*rAngleCount + i*rAngleCount + j][1] = (r / rCount*i)*sin(2 * PI / rAngleCount*j);
			this->m_points[hCount*rAngleCount + rCount*rAngleCount + i*rAngleCount + j][2] = h;
		}
	}

}
void CMy03������εĻ���View::CreateCone()
{
	//Բ׶�� ��������
	int rAngleCount = 300;
	int hCount = 200;
	double h = 400;
	double r = 200;
	int rCount = 200;
	double PI = 3.1415926525;
	this->m_pointcount = rAngleCount*hCount + rAngleCount*rCount;
	int i = 0;
	this->m_points = (double **)malloc(this->m_pointcount*(sizeof(double*)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		this->m_points[i] = (double*)malloc(3 * sizeof(double));
	}
	//��������
	for (i = 0; i < hCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			this->m_points[i*rAngleCount + j][1] = (1.0 - h / hCount*i / h)*r*cos(2 * PI / rAngleCount* j);
			this->m_points[i*rAngleCount + j][0] = (1.0 - h / hCount*i / h)*r*sin(2 * PI / rAngleCount* j);
			this->m_points[i*rAngleCount + j][2] = h / hCount*i;
		}
	}
	//�µ���
	for (i = 0; i < rCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			this->m_points[hCount*rAngleCount + i*rAngleCount + j][0] = (r / rCount*i)*cos(2 * PI / rAngleCount* j);
			this->m_points[hCount*rAngleCount + i*rAngleCount + j][1] = (r / rCount*i)*sin(2 * PI / rAngleCount*j);
			this->m_points[hCount*rAngleCount + i*rAngleCount + j][2] = 0;
		}
	}
}
void CMy03������εĻ���View::CreateTorus()
{
	//Բ��
	double r1 = 200;
	double r2 = 50;
	int aAngleCount = 200;
	int bAngleCount = 100;
	double PI = 3.1415926525;
	this->m_pointcount = aAngleCount*bAngleCount;
	int i = 0;
	this->m_points = (double **)malloc(this->m_pointcount*(sizeof(double*)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		this->m_points[i] = (double*)malloc(3 * sizeof(double));
	}
	for (i = 0; i < aAngleCount; i++)
	{
		for (int j = 0; j < bAngleCount; j++)
		{
			this->m_points[i*bAngleCount + j][0] = (r1 + r2*sin(2 * PI / bAngleCount*j))*sin(2 * PI / aAngleCount*i);
			this->m_points[i*bAngleCount + j][1] = (r1 + r2*sin(2 * PI / bAngleCount*j))*cos(2 * PI / aAngleCount*i);
			this->m_points[i*bAngleCount + j][2] = r2*cos(2 * PI / bAngleCount*j);
		}
	}

}
bool CMy03������εĻ���View::BuildData()
{
	(this->*func)();
	
	FILE * tmf = fopen(".\\SavePoly.tm", "w");
	if (tmf != NULL)
	{
		int i = 0;
		fprintf(tmf, "%d %d %d\n", this->m_pointcount, this->m_tranglecount, this->m_vectorNum);
		for (i = 0; i<this->m_pointcount; i++)
		{
			fprintf(tmf, "%lf %lf %lf\n", this->m_points[i][0], this->m_points[i][1], this->m_points[i][2]);
		}
		if (this->m_drawtype == 1)
		{
			for (i = 0; i<this->m_tranglecount; i++)
			{
				for (int j = 0; j < this->m_vectorNum; j++)
				{
					if (j == this->m_vectorNum - 1)
						fprintf(tmf, "%d\n", this->m_trangle[i][j]);
					else
						fprintf(tmf, "%d ", this->m_trangle[i][j]);
				}

			}
		}
		fclose(tmf);
	}
	return true;
}
void CMy03������εĻ���View::DrawVPolygon(CDC* pDC)
{
	if (this->m_isload == false)
		return;
	CPoint arr[10];
	if (this->m_drawtype == 0)
	{
		for (int i = 0; i<this->m_pointcount; i++)
		{
			pDC->SetPixelV(V3TOV2XY(TOINT(this->m_points[i][0] * this->m_shrink / 10.0), TOINT(this->m_points[i][1] * this->m_shrink / 10.0), TOINT(this->m_points[i][2] * this->m_shrink / 10.0)), this->PointColor);
		}
	}
	else if (this->m_drawtype == 1)
	{
		CPen pen(0, 0, this->LineColor);
		CPen* oldpen=pDC->SelectObject(&pen);
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			for (int j = 0; j<m_vectorNum; j++)
			{
				arr[j].x = V3TOV2X(TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0));
				arr[j].y = V3TOV2Y(TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0));
			}
			arr[m_vectorNum] = arr[0];
			pDC->Polyline(arr, m_vectorNum+1);
		}
		pDC->SelectObject(oldpen);
	}
	else if (this->m_drawtype == 2)
	{
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			int darr[10][3] = { 0 };
			for (int j = 0; j<m_vectorNum; j++)
			{
				int d3x = TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0);
				int d3y = TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0);
				int d3z = TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0);
				arr[j].x = V3TOV2X(d3x, d3y, d3z);
				arr[j].y = V3TOV2Y(d3x, d3y, d3z);
				darr[j][0] = d3x;
				darr[j][1] = d3y;
				darr[j][2] = d3z;
			}
			if (this->m_openeye == true)
			{
				int vec1[3] = { VECTORLINE(darr[0][0], darr[0][1], darr[0][2], darr[1][0], darr[1][1], darr[1][2]) };
				int vec2[3] = { VECTORLINE(darr[1][0], darr[1][1], darr[1][2], darr[2][0], darr[2][1], darr[2][2]) };
				int nli[3] = { NORMALLINE(vec1[0], vec1[1], vec1[2], vec2[0], vec2[1], vec2[2]) };
				if (MATRIXCOS(nli[0], nli[1], nli[2], -1, -1, 1) >= 0 || MATRIXCOS(nli[0], nli[1], nli[2], 1, -1, -1) >= 0 || MATRIXCOS(nli[0], nli[1], nli[2], 1, -1, 1) >= 0)
					pDC->Polygon(arr, m_vectorNum);
			}
			else
			{
				pDC->Polygon(arr, m_vectorNum);
			}
		}
	}
}
void CMy03������εĻ���View::InitDraw()
{
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	PointColor=RGB(0,255,0);
	LineColor=RGB(0,0,255);
	m_isload = true;
	m_viewOrgLine = true;
	m_shrink = 10;
	m_vectorNum = 3;
	m_openeye = false;
	this->func = &CMy03������εĻ���View::CreateDodecahedron;
	m_drawtype = 1;//0 point 1 line 2 vprint
	m_isload = BuildData();
}
void CMy03������εĻ���View::ClearDrawData()
{
	if (this->m_isload)
	{
		int i = 0;
		for (i = 0; i<this->m_pointcount; i++)
			free(this->m_points[i]);
		for (i = 0; i<this->m_tranglecount; i++)
			free(this->m_trangle[i]);
		free(m_points);
		free(m_trangle);
	}
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
}
// CMy03������εĻ���View ����/����

CMy03������εĻ���View::CMy03������εĻ���View()
{
	// TODO:  �ڴ˴���ӹ������
	InitDraw();

}

CMy03������εĻ���View::~CMy03������εĻ���View()
{
	this->ClearDrawData();
}
// CMy03������εĻ���View ����

void CMy03������εĻ���View::OnDraw(CDC* pDC)
{
	CMy03������εĻ���Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	ResetCenterOrg(pDC);
	if (this->m_viewOrgLine)
		DrawOrgLine(pDC);
	DrawVPolygon(pDC);
}
// CMy03������εĻ���View ��Ϣ�������


void CMy03������εĻ���View::OnDrawTetrahedron()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = 1;
	this->ClearDrawData();
	this->func = &CMy03������εĻ���View::CreateTetrahedron;
	m_isload = BuildData();
	Invalidate();
}


void CMy03������εĻ���View::OnDrawHexahedron()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = 1;
	this->ClearDrawData();
	this->func = &CMy03������εĻ���View::CreateHexahedron;
	m_isload = BuildData();
	Invalidate();
}


void CMy03������εĻ���View::OnDrawOctahedron()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = 1;
	this->ClearDrawData();
	this->func = &CMy03������εĻ���View::CreateOctahedron;
	m_isload = BuildData();
	Invalidate();
}


void CMy03������εĻ���View::OnDrawDodecahedron()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = 1;
	this->ClearDrawData();
	this->func = &CMy03������εĻ���View::CreateDodecahedron;
	m_isload = BuildData();
	Invalidate();
}


void CMy03������εĻ���View::OnDrawIcosahedron()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = 1;
	this->ClearDrawData();
	this->func = &CMy03������εĻ���View::CreateIcosahedron;
	m_isload = BuildData();
	Invalidate();
}
void CMy03������εĻ���View::OnDrawBall()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = 0;
	this->ClearDrawData();
	this->func = &CMy03������εĻ���View::CreateBall;
	m_isload = BuildData();
	Invalidate();
}


void CMy03������εĻ���View::OnDrawCylinder()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = 0;
	this->ClearDrawData();
	this->func = &CMy03������εĻ���View::CreateCylinder;
	m_isload = BuildData();
	Invalidate();
}


void CMy03������εĻ���View::OnDrawCone()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = 0;
	this->ClearDrawData();
	this->func = &CMy03������εĻ���View::CreateCone;
	m_isload = BuildData();
	Invalidate();
}


void CMy03������εĻ���View::OnDrawTorus()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = 0;
	this->ClearDrawData();
	this->func = &CMy03������εĻ���View::CreateTorus;
	m_isload = BuildData();
	Invalidate();

}
void CMy03������εĻ���View::OnPointRed()
{
	// TODO:  �ڴ���������������
	this->PointColor = RGB(255,0,0);
	Invalidate();
}


void CMy03������εĻ���View::OnPointGreen()
{
	// TODO:  �ڴ���������������
	this->PointColor = RGB(0, 255, 0);
	Invalidate();
}


void CMy03������εĻ���View::OnPointBlue()
{
	// TODO:  �ڴ���������������
	this->PointColor = RGB(0, 0, 255);
	Invalidate();
}


void CMy03������εĻ���View::OnPointBlack()
{
	// TODO:  �ڴ���������������
	this->PointColor = RGB(0, 0, 0);
	Invalidate();
}


void CMy03������εĻ���View::OnLineRed()
{
	// TODO:  �ڴ���������������
	this->LineColor = RGB(255, 0, 0);
	Invalidate();
}


void CMy03������εĻ���View::OnLineGreen()
{
	// TODO:  �ڴ���������������
	this->LineColor = RGB(0, 255, 0);
	Invalidate();
}


void CMy03������εĻ���View::OnLineBlue()
{
	// TODO:  �ڴ���������������
	this->LineColor = RGB(0, 0, 255);
	Invalidate();
}


void CMy03������εĻ���View::OnLineBlack()
{
	// TODO:  �ڴ���������������
	this->LineColor = RGB(0, 0, 0);
	Invalidate();
}
void CMy03������εĻ���View::OnOrgLineShow()
{
	// TODO:  �ڴ���������������
	this->m_viewOrgLine = true;
	Invalidate();
}


void CMy03������εĻ���View::OnOrgLineHide()
{
	// TODO:  �ڴ���������������
	this->m_viewOrgLine = false;
	Invalidate();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CMy03������εĻ���View

IMPLEMENT_DYNCREATE(CMy03������εĻ���View, CView)

BEGIN_MESSAGE_MAP(CMy03������εĻ���View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMy03������εĻ���View::OnDrawTetrahedron)
	ON_COMMAND(ID_32772, &CMy03������εĻ���View::OnDrawHexahedron)
	ON_COMMAND(ID_32773, &CMy03������εĻ���View::OnDrawOctahedron)
	ON_COMMAND(ID_32774, &CMy03������εĻ���View::OnDrawDodecahedron)
	ON_COMMAND(ID_32775, &CMy03������εĻ���View::OnDrawIcosahedron)
	ON_COMMAND(ID_Menu, &CMy03������εĻ���View::OnDrawBall)
	ON_COMMAND(ID_32777, &CMy03������εĻ���View::OnDrawCylinder)
	ON_COMMAND(ID_32778, &CMy03������εĻ���View::OnDrawCone)
	ON_COMMAND(ID_32779, &CMy03������εĻ���View::OnDrawTorus)
	ON_COMMAND(ID_32780, &CMy03������εĻ���View::OnPointRed)
	ON_COMMAND(ID_32781, &CMy03������εĻ���View::OnPointGreen)
	ON_COMMAND(ID_32782, &CMy03������εĻ���View::OnPointBlue)
	ON_COMMAND(ID_32783, &CMy03������εĻ���View::OnPointBlack)
	ON_COMMAND(ID_32784, &CMy03������εĻ���View::OnLineRed)
	ON_COMMAND(ID_32785, &CMy03������εĻ���View::OnLineGreen)
	ON_COMMAND(ID_32786, &CMy03������εĻ���View::OnLineBlue)
	ON_COMMAND(ID_32787, &CMy03������εĻ���View::OnLineBlack)
	ON_COMMAND(ID_32788, &CMy03������εĻ���View::OnOrgLineShow)
	ON_COMMAND(ID_32789, &CMy03������εĻ���View::OnOrgLineHide)
END_MESSAGE_MAP()



BOOL CMy03������εĻ���View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}



// CMy03������εĻ���View ��ӡ

BOOL CMy03������εĻ���View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy03������εĻ���View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy03������εĻ���View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy03������εĻ���View ���

#ifdef _DEBUG
void CMy03������εĻ���View::AssertValid() const
{
	CView::AssertValid();
}

void CMy03������εĻ���View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy03������εĻ���Doc* CMy03������εĻ���View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy03������εĻ���Doc)));
	return (CMy03������εĻ���Doc*)m_pDocument;
}
#endif //_DEBUG
