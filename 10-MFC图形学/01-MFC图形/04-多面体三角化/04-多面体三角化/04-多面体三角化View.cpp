
// 04-多面体三角化View.cpp : CMy04多面体三角化View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "04-多面体三角化.h"
#endif

#include "04-多面体三角化Doc.h"
#include "04-多面体三角化View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
///////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<math.h>
//斜二测画法
//三维转二维坐标获得X
#define V3TOV2X(x,y,z) (int)(x+y/2.0*cos(atan2(1.0,1.0)))
//三维转二维坐标获得Y
#define V3TOV2Y(x,y,z) (int)(z+y/2.0*sin(atan2(1.0,1.0)))
//三维转二维坐标获得X，Y
#define V3TOV2XY(x,y,z) (int)(x+y/2.0*cos(atan2(1.0,1.0))),(int)(z+y/2.0*sin(atan2(1.0,1.0)))
//强制类型转换
#define TOINT(x) (int)(x)
//根据空间直线获取改直线的向量
#define VECTORLINE(x1,y1,z1,x2,y2,z2) (int)(x2-x1), (int)(y2-y1), (int)(z2-z1)
//获取空间平面的法向量
#define NORMALLINE(x1,y1,z1,x2,y2,z2) (int)(y1*z2 - y2*z1), (int)(x1*z2 - x2*z1), (int)(x1*y2 - x2*y1)
//获取空间向量的夹角
#define MATRIXCOS(x1,y1,z1,x2,y2,z2) ((x1*x2 + y1*y2 + z1*z2)*1.0 / (sqrt(pow(x1, 2.0)+pow(y1, 2.0)+pow(z1, 2.0))*sqrt(pow(x2, 2.0)+pow(y2, 2.0)+ pow(z2, 2.0))))
//获取两点之间的距离
#define DISTANCE(x1,y1,z1,x2,y2,z2) (sqrt(pow(x2-x1,2.0)+pow(y2-y1,2.0)+pow(z2-z1,2.0)))

// CMy03正多边形的绘制View 构造/析构

CMy04多面体三角化View::CMy04多面体三角化View()
{
	// TODO:  在此处添加构造代码
	InitDraw();
	BulidLinearMatrix();
	m_drawtype = 1;
}
void CMy04多面体三角化View::InitDraw()
{
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	PointColor = RGB(0, 255, 0);
	LineColor = RGB(0, 0, 255);
	m_isload = true;
	m_viewOrgLine = true;
	m_shrink = 10;
	m_vectorNum = 3;
	m_openeye = false;
	this->func = &CMy04多面体三角化View::CreateCylinder;
	m_drawtype = 0;//0 point 1 line 2 vprint
	m_isload = BuildData();

}
CMy04多面体三角化View::~CMy04多面体三角化View()
{
	this->ClearDrawData();
}

void CMy04多面体三角化View::CreateBall()
{
	//球体 点云数据
	int aAngleCount = 80;
	int bAngleCount = 40;
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
void CMy04多面体三角化View::CreateCylinder()
{
	//圆柱体 点云数据
	int hCount = 60;
	int rAngleCount = 80;
	double r = 200;
	double h = 350;
	int rCount = 20;
	double PI = 3.1415926525;
	this->m_pointcount = hCount*rAngleCount + rCount*rAngleCount * 2;
	int i = 0;
	this->m_points = (double **)malloc(this->m_pointcount*(sizeof(double*)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		this->m_points[i] = (double*)malloc(3 * sizeof(double));
	}
	//环形曲面
	for (i = 0; i < hCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			this->m_points[i*rAngleCount + j][0] = r*cos(2 * PI / rAngleCount* j);
			this->m_points[i*rAngleCount + j][1] = r*sin(2 * PI / rAngleCount*j);
			this->m_points[i*rAngleCount + j][2] = h / hCount*i;
		}
	}
	//下底面
	for (i = 0; i < rCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			this->m_points[hCount*rAngleCount + i*rAngleCount + j][0] = (r / rCount*i)*cos(2 * PI / rAngleCount* j);
			this->m_points[hCount*rAngleCount + i*rAngleCount + j][1] = (r / rCount*i)*sin(2 * PI / rAngleCount*j);
			this->m_points[hCount*rAngleCount + i*rAngleCount + j][2] = 0;
		}
	}
	//上底面
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
void CMy04多面体三角化View::CreateCone()
{
	//圆锥体 点云数据
	int rAngleCount = 80;
	int hCount = 50;
	double h = 400;
	double r = 250;
	int rCount = 20;
	double PI = 3.1415926525;
	this->m_pointcount = rAngleCount*hCount + rAngleCount*rCount;
	int i = 0;
	this->m_points = (double **)malloc(this->m_pointcount*(sizeof(double*)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		this->m_points[i] = (double*)malloc(3 * sizeof(double));
	}
	//环形曲面
	for (i = 0; i < hCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			this->m_points[i*rAngleCount + j][1] = (1.0 - h / hCount*i / h)*r*cos(2 * PI / rAngleCount* j);
			this->m_points[i*rAngleCount + j][0] = (1.0 - h / hCount*i / h)*r*sin(2 * PI / rAngleCount* j);
			this->m_points[i*rAngleCount + j][2] = h / hCount*i;
		}
	}
	//下底面
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
void CMy04多面体三角化View::CreateTorus()
{
	//圆环
	double r1 = 300;
	double r2 = 200;
	int aAngleCount = 80;
	int bAngleCount = 60;
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
void CMy04多面体三角化View::ResetCenterOrg(CDC * pDC)
{
	//中央坐标系
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(rect.right, -rect.bottom);
}
void CMy04多面体三角化View::DrawOrgLine(CDC * pDC)
{
	//绘制坐标系
	CPen pen(0, 1, RGB(255, 0, 0));
	CPen * oldpen = pDC->SelectObject(&pen);
	pDC->MoveTo(V3TOV2XY(-2000, 0, 0));
	pDC->LineTo(V3TOV2XY(2000, 0, 0));

	pDC->MoveTo(V3TOV2XY(0, -2000, 0));
	pDC->LineTo(V3TOV2XY(0, 2000, 0));

	pDC->MoveTo(V3TOV2XY(0, 0, -2000));
	pDC->LineTo(V3TOV2XY(0, 0, 2000));
	pDC->SelectObject(oldpen);
}
void CMy04多面体三角化View::AllocMemery()
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
void CMy04多面体三角化View::BulidLinearMatrix()
{
	/*
	建立以每个点为中心，周围最近的3个点,建立邻接矩阵m_matrix
	这三个点和中心点组成三角形
	#define CENTER 0 条件编译
	*/
	
#define CENTER 0	//是否采用中心点形成三个三角形，否则去除中心点形成一个三角形
#if CENTER
	int LinerPointCount = 3;
	this->m_tranglecount = this->m_pointcount*LinerPointCount;
#else
	this->m_tranglecount = this->m_pointcount;
#endif
	this->m_trangle = (int**)malloc(sizeof(int*)*this->m_tranglecount);
	for (int f = 0; f < m_tranglecount; f++)
	{
		this->m_trangle[f] = (int*)malloc(sizeof(int)* 3);
	}
	//allocate memory for m_matrix
	m_matrix = (PMAPNODE)malloc(sizeof(MAPNODE)*this->m_pointcount);
	//for every point calcul linear point
	PMATRIXNODE distPrePoint = (PMATRIXNODE)malloc(sizeof(MATRIXNODE)*this->m_pointcount);
	for (int i = 0; i < m_pointcount; i++)
	{
		m_matrix[i].prePointIndex = i;
		//calcul one point distance
		for (int j = 0; j < m_pointcount; j++)
		{
			distPrePoint[j].drtPointIndex = j;
			distPrePoint[j].distance = DISTANCE(this->m_points[i][0], this->m_points[i][1], this->m_points[i][2], \
				this->m_points[j][0], this->m_points[j][1], this->m_points[j][2], );
		}
		//get 5 point of min
		for (int m = 0; m < 3 + 2; m++)
		{
			//find the m th. min number
			int minIndex = m;
			for (int n = m; n < m_pointcount; n++)
			{
				if (n == i)
					continue;
				if (distPrePoint[n].distance < distPrePoint[minIndex].distance)
				{
					minIndex = n;
				}
			}
			//swap min distance point to m index
			MATRIXNODE temp;
			temp.drtPointIndex = distPrePoint[minIndex].drtPointIndex;
			temp.distance = distPrePoint[minIndex].distance;
			distPrePoint[minIndex].distance = distPrePoint[m].distance;
			distPrePoint[minIndex].drtPointIndex = distPrePoint[m].drtPointIndex;
			distPrePoint[m].distance = temp.distance;
			distPrePoint[m].drtPointIndex = temp.drtPointIndex;

		}

		//copy trangle data to m_trangle
		for (int h = 0; h < 3; h++)
		{
			m_matrix[i].linearPointIndexs[h] = distPrePoint[h].drtPointIndex;
		}
#if CENTER
		int PointArr[20][3];/* = { { 0, 0, 1 }, { 0, 1, 2 }, { 0, 2, 0 } };*/
		for (int b = 0; b < LinerPointCount; b++)
		{
			PointArr[b][0] = i;
			PointArr[b][1] = b;
			PointArr[b][2] = b + 1;
		}
		PointArr[LinerPointCount - 1][0] = i;
		PointArr[LinerPointCount - 1][1] = LinerPointCount - 1;
		PointArr[LinerPointCount - 1][2] = 0;
		for (int g = 0; g < LinerPointCount; g++)
		{
			for (int h = 0; h < 3; h++)
				this->m_trangle[LinerPointCount*i + g][h] = distPrePoint[PointArr[g][h]].drtPointIndex;
		}
#else
		for (int h = 0; h < 3; h++)
		{
			this->m_trangle[i][h] = distPrePoint[h].drtPointIndex;
		}
#endif
			
	}
	this->m_vectorNum = 3;
	free(distPrePoint);
	FILE * linearTxt = fopen("LinearMatrix.txt","w");
	for (int i = 0; i < m_pointcount; i++)
	{
		fprintf(linearTxt, "%d\t: %d\t%d\t%d\n", m_matrix[i].prePointIndex, m_matrix[i].linearPointIndexs[0], m_matrix[i].linearPointIndexs[1], m_matrix[i].linearPointIndexs[2] );
	}
	fclose(linearTxt);
}

bool CMy04多面体三角化View::BuildData()
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
void CMy04多面体三角化View::DrawVPolygon(CDC* pDC)
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
		CPen* oldpen = pDC->SelectObject(&pen);
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			for (int j = 0; j<m_vectorNum; j++)
			{
				arr[j].x = V3TOV2X(TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0));
				arr[j].y = V3TOV2Y(TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0));
			}
			arr[m_vectorNum] = arr[0];
			pDC->Polyline(arr, m_vectorNum + 1);
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

void CMy04多面体三角化View::ClearDrawData()
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

// CMy03正多边形的绘制View 绘制

void CMy04多面体三角化View::OnDraw(CDC* pDC)
{
	CMy04多面体三角化Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	ResetCenterOrg(pDC);
	if (this->m_viewOrgLine)
		DrawOrgLine(pDC);
	DrawVPolygon(pDC);
}

// CMy04多面体三角化View 消息处理程序


void CMy04多面体三角化View::OnDrawBall()
{
	// TODO:  在此添加命令处理程序代码
	ClearDrawData();
	this->func = &CMy04多面体三角化View::CreateBall;
	m_isload = BuildData();
	BulidLinearMatrix();
	Invalidate();
}


void CMy04多面体三角化View::OnDrawCylinder()
{
	// TODO:  在此添加命令处理程序代码
	ClearDrawData();
	this->func = &CMy04多面体三角化View::CreateCylinder;
	m_isload = BuildData();
	BulidLinearMatrix();
	Invalidate();
}


void CMy04多面体三角化View::OnDrawCone()
{
	// TODO:  在此添加命令处理程序代码
	ClearDrawData();
	this->func = &CMy04多面体三角化View::CreateCone;
	m_isload = BuildData();
	BulidLinearMatrix();
	Invalidate();
}


void CMy04多面体三角化View::OnDrawTorus()
{
	// TODO:  在此添加命令处理程序代码
	ClearDrawData();
	this->func = &CMy04多面体三角化View::CreateTorus;
	m_isload = BuildData();
	BulidLinearMatrix();
	Invalidate();
}
void CMy04多面体三角化View::OnModePoint()
{
	// TODO:  在此添加命令处理程序代码
	m_drawtype = 0;
	Invalidate();
}


void CMy04多面体三角化View::OnModeLine()
{
	// TODO:  在此添加命令处理程序代码
	m_drawtype = 1;
	Invalidate();
}


void CMy04多面体三角化View::OnModeTrangle()
{
	// TODO:  在此添加命令处理程序代码
	m_drawtype = 2;
	Invalidate();
}
//////////////////////////////////////////////////////////////////////////////////////////
// CMy04多面体三角化View

IMPLEMENT_DYNCREATE(CMy04多面体三角化View, CView)

BEGIN_MESSAGE_MAP(CMy04多面体三角化View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMy04多面体三角化View::OnDrawBall)
	ON_COMMAND(ID_32772, &CMy04多面体三角化View::OnDrawCylinder)
	ON_COMMAND(ID_32773, &CMy04多面体三角化View::OnDrawCone)
	ON_COMMAND(ID_32774, &CMy04多面体三角化View::OnDrawTorus)
	ON_COMMAND(ID_32775, &CMy04多面体三角化View::OnModePoint)
	ON_COMMAND(ID_32776, &CMy04多面体三角化View::OnModeLine)
	ON_COMMAND(ID_32777, &CMy04多面体三角化View::OnModeTrangle)
END_MESSAGE_MAP()

// CMy04多面体三角化View 构造/析构


BOOL CMy04多面体三角化View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy04多面体三角化View 绘制




// CMy04多面体三角化View 打印

BOOL CMy04多面体三角化View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy04多面体三角化View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy04多面体三角化View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy04多面体三角化View 诊断

#ifdef _DEBUG
void CMy04多面体三角化View::AssertValid() const
{
	CView::AssertValid();
}

void CMy04多面体三角化View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy04多面体三角化Doc* CMy04多面体三角化View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy04多面体三角化Doc)));
	return (CMy04多面体三角化Doc*)m_pDocument;
}
#endif //_DEBUG






