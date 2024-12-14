
// 02-TM文件解析绘图View.cpp : CMy02TM文件解析绘图View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "02-TM文件解析绘图.h"
#endif

#include "02-TM文件解析绘图Doc.h"
#include "02-TM文件解析绘图View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
//定义点云颜色
#define MCOLOR RGB(255,0,0)
//根据空间直线获取改直线的向量
#define VECTORLINE(x1,y1,z1,x2,y2,z2) (int)(x2-x1), (int)(y2-y1), (int)(z2-z1)
//获取空间平面的法向量
#define NORMALLINE(x1,y1,z1,x2,y2,z2) (int)(y1*z2 - y2*z1), (int)(x1*z2 - x2*z1), (int)(x1*y2 - x2*y1)
//获取空间向量的夹角
#define MATRIXCOS(x1,y1,z1,x2,y2,z2) ((x1*x2 + y1*y2 + z1*z2)*1.0 / (sqrt(pow(x1, 2.0)+pow(y1, 2.0)+pow(z1, 2.0))*sqrt(pow(x2, 2.0)+pow(y2, 2.0)+ pow(z2, 2.0))))
void Wchar_t2Char(wchar_t Wchar[], char Char[])
{
	int size = WideCharToMultiByte(CP_ACP, 0, Wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Wchar, -1, Char, size, NULL, NULL);
}
void CMy02TM文件解析绘图View::ResetCenterOrg(CDC * pDC)
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
void CMy02TM文件解析绘图View::DrawOrgLine(CDC * pDC)
{
	//绘制坐标系
	pDC->MoveTo(V3TOV2XY(-2000, 0, 0));
	pDC->LineTo(V3TOV2XY(2000, 0, 0));

	pDC->MoveTo(V3TOV2XY(0, -2000, 0));
	pDC->LineTo(V3TOV2XY(0, 2000, 0));

	pDC->MoveTo(V3TOV2XY(0, 0, -2000));
	pDC->LineTo(V3TOV2XY(0, 0, 2000));
}
bool CMy02TM文件解析绘图View::LoadTMFile(char * filename)
{
	FILE * tmf = fopen(filename, "r");
	if (tmf == NULL)
		return false;
	int temp = 0;
	int i = 0;
	if (3 != fscanf(tmf, "%d %d %d\n", &this->m_pointcount, &this->m_tranglecount, &temp))
	{
		fclose(tmf);
		return false;
	}
	this->m_points = (double **)malloc(this->m_pointcount*(sizeof(double*)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		this->m_points[i] = (double*)malloc(3 * sizeof(double));
		fscanf(tmf, "%lf %lf %lf\n", &this->m_points[i][0], &this->m_points[i][1], &this->m_points[i][2]);
	}
	this->m_trangle = (int **)malloc(this->m_tranglecount*(sizeof(int*)));
	for (i = 0; i<this->m_tranglecount; i++)
	{
		this->m_trangle[i] = (int*)malloc(3 * sizeof(int));
		fscanf(tmf, "%d %d %d\n", &this->m_trangle[i][0], &this->m_trangle[i][1], &this->m_trangle[i][2]);
	}
	fclose(tmf);
	return true;
}
void CMy02TM文件解析绘图View::DrawVPolygon(CDC* pDC)
{
	if (this->m_isload == false)
		return;
	CPoint arr[4];
	if (this->m_drawtype == 0)
	{
		for (int i = 0; i<this->m_pointcount; i++)
		{
			pDC->SetPixelV(V3TOV2XY(TOINT(this->m_points[i][0] * this->m_shrink / 10.0), TOINT(this->m_points[i][1] * this->m_shrink / 10.0), TOINT(this->m_points[i][2] * this->m_shrink / 10.0)), MCOLOR);
		}
	}
	else if (this->m_drawtype == 1)
	{
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			for (int j = 0; j<3; j++)
			{
				arr[j].x = V3TOV2X(TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0));
				arr[j].y = V3TOV2Y(TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0));
			}
			arr[3] = arr[1];
			pDC->Polyline(arr, 4);
		}
	}
	else if (this->m_drawtype == 2)
	{
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			int darr[3][3] = {0};
			for (int j = 0; j<3; j++)
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
					pDC->Polygon(arr, 3);
			}
			else
			{
				pDC->Polygon(arr, 3);
			}
		}
	}
}
void CMy02TM文件解析绘图View::ReLoadDrawData(char * filename)
{
	ClearDrawData();
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_isload = LoadTMFile(filename);
}
void CMy02TM文件解析绘图View::InitDraw()
{
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_isload = false;
	m_viewOrgLine = false;
	m_centerOrg = false;
	m_shrink = 10;
	m_openeye = false;
	m_drawtype = 0;//0 point 1 line 2 vprint
	m_isload = LoadTMFile("res\\Bunny.tm");
}
void CMy02TM文件解析绘图View::ClearDrawData()
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
}
CMy02TM文件解析绘图View::CMy02TM文件解析绘图View()
{
	// TODO: add construction code here
	InitDraw();
}

CMy02TM文件解析绘图View::~CMy02TM文件解析绘图View()
{
	ClearDrawData();
}
// CMy02TM文件解析绘图View

IMPLEMENT_DYNCREATE(CMy02TM文件解析绘图View, CView)

BEGIN_MESSAGE_MAP(CMy02TM文件解析绘图View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMy02TM文件解析绘图View::OnSelectCenterOrg)
	ON_COMMAND(ID_32772, &CMy02TM文件解析绘图View::OnSelectViewOrgLine)
	ON_COMMAND(ID_32773, &CMy02TM文件解析绘图View::OnSelectViewMode)
	ON_WM_DROPFILES()
	ON_WM_CREATE()
	ON_COMMAND(ID_32774, &CMy02TM文件解析绘图View::OnSelectShrink)
	ON_WM_MOUSEHWHEEL()
	ON_COMMAND(ID_32775, &CMy02TM文件解析绘图View::OnSelectResetShrink)
	ON_COMMAND(ID_32776, &CMy02TM文件解析绘图View::OnSelectEyeView)
END_MESSAGE_MAP()



BOOL CMy02TM文件解析绘图View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy02TM文件解析绘图View 绘制

void CMy02TM文件解析绘图View::OnDraw(CDC* pDC)
{
	CMy02TM文件解析绘图Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	if (m_centerOrg==true)
		ResetCenterOrg(pDC);
	if (m_viewOrgLine==true)
		DrawOrgLine(pDC);
	DrawVPolygon(pDC);
}


// CMy02TM文件解析绘图View 打印

BOOL CMy02TM文件解析绘图View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy02TM文件解析绘图View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy02TM文件解析绘图View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy02TM文件解析绘图View 诊断

#ifdef _DEBUG
void CMy02TM文件解析绘图View::AssertValid() const
{
	CView::AssertValid();
}

void CMy02TM文件解析绘图View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy02TM文件解析绘图Doc* CMy02TM文件解析绘图View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy02TM文件解析绘图Doc)));
	return (CMy02TM文件解析绘图Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy02TM文件解析绘图View 消息处理程序


void CMy02TM文件解析绘图View::OnSelectCenterOrg()
{
	// TODO:  在此添加命令处理程序代码
	this->m_centerOrg = true;
	Invalidate();
}


void CMy02TM文件解析绘图View::OnSelectViewOrgLine()
{
	// TODO:  在此添加命令处理程序代码
	this->m_viewOrgLine = !this->m_viewOrgLine;
	Invalidate();
}


void CMy02TM文件解析绘图View::OnSelectViewMode()
{
	// TODO:  在此添加命令处理程序代码
	this->m_drawtype = (this->m_drawtype + 1) % 3;
	Invalidate();
}


void CMy02TM文件解析绘图View::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	TCHAR filePath[200];
	if (DragQueryFile(hDropInfo, -1, NULL, 0))
	{
		DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));
	}
	DragFinish(hDropInfo);
	char filename[256] = { 0 };
	Wchar_t2Char(filePath, filename);
	ReLoadDrawData(filename);
	Invalidate();
	CView::OnDropFiles(hDropInfo);
}


int CMy02TM文件解析绘图View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	DragAcceptFiles(TRUE);
	return 0;
}


void CMy02TM文件解析绘图View::OnSelectShrink()
{
	// TODO:  在此添加命令处理程序代码
	this->m_shrink = (this->m_shrink + 2) % 100;
	Invalidate();
}


void CMy02TM文件解析绘图View::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (zDelta > 0)
	{
		this->m_shrink = (this->m_shrink + 2) % 100;
	}
	else
	{
		this->m_shrink = (this->m_shrink - 2);
		if (this->m_shrink < 2)
			this->m_shrink = 2;
	}
	Invalidate();
	CView::OnMouseHWheel(nFlags, zDelta, pt);
}


void CMy02TM文件解析绘图View::OnSelectResetShrink()
{
	// TODO:  在此添加命令处理程序代码
	this->m_shrink = 10;
	Invalidate();
}


void CMy02TM文件解析绘图View::OnSelectEyeView()
{
	// TODO:  在此添加命令处理程序代码
	this->m_openeye = !this->m_openeye;
	Invalidate();
}
