
// 09-三维模型光照View.cpp : CMy09三维模型光照View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "09-三维模型光照.h"
#endif

#include "09-三维模型光照Doc.h"
#include "09-三维模型光照View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CMy09三维模型光照View::DrawGraph(CDC * pDC)
{
	if (m_isload == false)
		return;
	double aA = AngleToRadian(45);
	double bA = AngleToRadian(63.5);
	double R = 500, d = 400;
	COLORREF linecolor;
	D3Point lp;
	for (int i = -1000; i < 1000; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			switch (j)
			{
			case 0:
				lp.y = 0; lp.z = 0, lp.x = i;
				linecolor = 0x0000ff;
				break;
			case 1:
				lp.x = 0; lp.z = 0, lp.y = i;
				linecolor = 0x00ff00;
				break;
			case 2:
				lp.y = 0; lp.x = 0, lp.z = i;
				linecolor = 0xff0000;
				break;
			}
			//ProjOblique(&lp, aA, bA);
			ProjThreePoint(&lp, R, d);
			pDC->SetPixel(lp.x, lp.y, linecolor);
		}


	}

	D3Point p;
	COLORREF m_pointColor = 0x0000ff;
	CBrush brush(0x0000ff);
	pDC->SelectObject(&brush);

	if (m_drawType == 0)
	{
		for (int i = 0; i < m_pointcount; i++)
		{
			D3Point p = m_points[i];
			ProjOblique(&p, aA, bA);
			pDC->SetPixelV(p.x, p.y, m_pointColor);

		}
	}
	else if (m_drawType == 1)
	{
		CPoint arr[4];
		D3Flat flat;
		D3Color colors[1024];
		int cindex = 0;
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				p.x = m_points[this->m_trangle[i][j]].x;
				p.y = m_points[this->m_trangle[i][j]].y;
				p.z = m_points[this->m_trangle[i][j]].z;
				if (j == 0)
					flat.p1 = p;
				if (j == 1)
					flat.p2 = p;
				if (j == 2)
					flat.p3 = p;
				//ProjOblique(&p, aA, bA);
				ProjThreePoint(&p, R, d);
				arr[j].x = p.x;
				arr[j].y = p.y;

			}

			arr[3] = arr[0];

			if (D3FlatBlankingAlgorithm(15000, AngleToRadian(0), AngleToRadian(90), flat) > 0)
			{
				D3Point viewpoint;
				D3SphericalToCartesianCoordinates(1000, AngleToRadian(0), AngleToRadian(0), &viewpoint);
				D3Light light = { 0 };//金色光照
				light.diff_red = 0.752;
				light.diff_green = 0.606;
				light.diff_blue = 0.226;
				light.spec_red = 0.628;
				light.spec_green = 0.556;
				light.spec_blue = 0.366;
				light.c0 = 0.5;
				light.c1 = 0.8;
				light.c2 = 0.99;
				light.point = MakeD3Point(0,1000,0);
				D3Material mate = {0};//绿宝石材质
				mate.diff_red = 0.076;
				mate.diff_green = 0.614;
				mate.diff_blue = 0.075;
				mate.spec_red = 0.633;
				mate.spec_green = 0.728;
				mate.spec_blue = 0.633;
				mate.ambi_red = 0.022;
				mate.ambi_green = 0.175;
				mate.ambi_blue = 0.023;
				mate.heig_n = 30;
				Ambient am = { 0 };//无环境光
				am.ambi_red = 0;
				am.ambi_green = 0;
				am.ambi_blue = 0;
				
				D3Vector v1, v2;
				GetD3Vector(flat.p1, flat.p2, &v1);
				GetD3Vector(flat.p2,flat.p3,&v2);
				D3NormalLine nl;
				GetD3NormalLine(v1,v2,&nl);
				D3Color color=GraphLight(light, flat.p1, viewpoint, nl, mate, am);
				colors[cindex++] = color;
				if (cindex >= 1023)
					cindex = 0;
				if (cindex % 512 == 0)
					cindex = cindex;
				CPen pen(0,1,RGB(color.red, color.green, color.blue));
				pDC->SelectObject(&pen);
				CBrush brush(RGB(color.red,color.green,color.blue));
				pDC->SelectObject(&brush);
				pDC->Polygon(arr, 3);
			}
				
			//pDC->Polyline(arr, 4);
		}
	}
}
// CMy07三维模型几何变换及投影View 构造/析构
void CMy09三维模型光照View::ResetCenterOrg(CDC * pDC)
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

bool CMy09三维模型光照View::LoadTMFile(char * filename)
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
	this->m_points = (D3Point*)malloc(this->m_pointcount*(sizeof(D3Point)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		fscanf(tmf, "%lf %lf %lf\n", &this->m_points[i].x, &this->m_points[i].y, &this->m_points[i].z);
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
// CMy09三维模型光照View

IMPLEMENT_DYNCREATE(CMy09三维模型光照View, CView)

BEGIN_MESSAGE_MAP(CMy09三维模型光照View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy09三维模型光照View 构造/析构

CMy09三维模型光照View::CMy09三维模型光照View()
{
	// TODO:  在此处添加构造代码
	m_isload = false;
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_drawType = 1;
	m_isload = LoadTMFile("..\\Bunny.tm");
}

CMy09三维模型光照View::~CMy09三维模型光照View()
{
}

BOOL CMy09三维模型光照View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy09三维模型光照View 绘制

void CMy09三维模型光照View::OnDraw(CDC* pDC)
{
	CMy09三维模型光照Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	/*CPen pen(0, 1, 0x0000ff);
	pDC->SelectObject(&pen);*/
	ResetCenterOrg(pDC);
	DrawGraph(pDC);
}


// CMy09三维模型光照View 打印

BOOL CMy09三维模型光照View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy09三维模型光照View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy09三维模型光照View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy09三维模型光照View 诊断

#ifdef _DEBUG
void CMy09三维模型光照View::AssertValid() const
{
	CView::AssertValid();
}

void CMy09三维模型光照View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy09三维模型光照Doc* CMy09三维模型光照View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy09三维模型光照Doc)));
	return (CMy09三维模型光照Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy09三维模型光照View 消息处理程序
