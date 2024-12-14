
// 08-图形消隐与深度缓冲View.cpp : CMy08图形消隐与深度缓冲View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "08-图形消隐与深度缓冲.h"
#endif

#include "08-图形消隐与深度缓冲Doc.h"
#include "08-图形消隐与深度缓冲View.h"
#include"ZBuffer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void CMy08图形消隐与深度缓冲View::DrawGraph(CDC * pDC)
{
	if (m_isload == false)
		return;
#if 1
	D3Flat * flat = (D3Flat*)malloc(sizeof(D3Flat)*m_tranglecount);
	COLORREF * color = (COLORREF*)malloc(sizeof(COLORREF)*m_tranglecount);
	int beginIndex = 0;
	int count = m_tranglecount;
	for (int i = beginIndex; i < beginIndex + count; i++)
	{
		D3Point p;
		for (int j = 0; j < 3; j++)
		{
			p.x = m_points[this->m_trangle[i][j]].x;
			p.y = m_points[this->m_trangle[i][j]].y;
			p.z = m_points[this->m_trangle[i][j]].z;
			if (j == 0)
				flat[i].p1 = p;
			if (j == 1)
				flat[i].p2 = p;
			if (j == 2)
				flat[i].p3 = p;
		}
		color[i] =  RGB(rand() % 56 + 200, rand() % 106 + 150, rand() % 106 + 150);
	}
	COLORREF bgcolor = 0xffffff;
	ZBufferAlgorithm(flat, color, count, 1024, 1024, pDC->GetSafeHdc(), bgcolor);
	return;
#endif 
#if 0
	CPoint arr[4];
	D3Point p;
	for (int i = 0; i<this->m_tranglecount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			p.x = m_points[this->m_trangle[i][j]].x;
			p.y = m_points[this->m_trangle[i][j]].y;
			p.z = 0;
			arr[j].x = p.x;
			arr[j].y = p.y;

		}

		arr[3] = arr[0];
		pDC->Polyline(arr, 4);
	}
	return;
#endif
	
#if 0
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
				lp.y = 0; lp.z = 0,lp.x=i;
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
	/*D2Flat d2f=MakeD2Flat(MakeD2Point(500,-400),MakeD2Point(-800,0),MakeD2Point(500,400));
	FillScanLine(d2f, 0x00ff00, pDC->GetSafeHdc());
	return; */
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
				GraphSpin(&p,0,AngleToRadian(m_roundAngle),0);
				//ProjOblique(&p, aA, bA);
				ProjThreePoint(&p, R, d);
				//ProjOrthogonal(&p);
				arr[j].x = p.x;
				arr[j].y = p.y;

			}
				
			arr[3] = arr[0];

			if (D3FlatBlankingAlgorithm(15000, AngleToRadian(0), AngleToRadian(90),flat)>0)
				pDC->Polygon(arr,3);
			//pDC->Polyline(arr, 4);
		}
	}
#endif
}
// CMy07三维模型几何变换及投影View 构造/析构
void CMy08图形消隐与深度缓冲View::ResetCenterOrg(CDC * pDC)
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

bool CMy08图形消隐与深度缓冲View::LoadTMFile(char * filename)
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
// CMy08图形消隐与深度缓冲View

IMPLEMENT_DYNCREATE(CMy08图形消隐与深度缓冲View, CView)

BEGIN_MESSAGE_MAP(CMy08图形消隐与深度缓冲View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMy08图形消隐与深度缓冲View 构造/析构

CMy08图形消隐与深度缓冲View::CMy08图形消隐与深度缓冲View()
: m_roundAngle(0)
{
	// TODO:  在此处添加构造代码
	m_isload = false;
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_drawType = 1;
	m_isload = LoadTMFile("..\\Bunny.tm");
	srand(time(NULL));
}

CMy08图形消隐与深度缓冲View::~CMy08图形消隐与深度缓冲View()
{
}

BOOL CMy08图形消隐与深度缓冲View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CView::PreCreateWindow(cs);
}

// CMy08图形消隐与深度缓冲View 绘制

void CMy08图形消隐与深度缓冲View::OnDraw(CDC* pDC)
{
	CMy08图形消隐与深度缓冲Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	CPen pen(0, 1, 0x00ff00);
	pDC->SelectObject(&pen);
	ResetCenterOrg(pDC);
	DrawGraph(pDC);
}


// CMy08图形消隐与深度缓冲View 打印

BOOL CMy08图形消隐与深度缓冲View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy08图形消隐与深度缓冲View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy08图形消隐与深度缓冲View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy08图形消隐与深度缓冲View 诊断

#ifdef _DEBUG
void CMy08图形消隐与深度缓冲View::AssertValid() const
{
	CView::AssertValid();
}

void CMy08图形消隐与深度缓冲View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy08图形消隐与深度缓冲Doc* CMy08图形消隐与深度缓冲View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy08图形消隐与深度缓冲Doc)));
	return (CMy08图形消隐与深度缓冲Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy08图形消隐与深度缓冲View 消息处理程序


void CMy08图形消隐与深度缓冲View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (ID_TIMER_KARTON == nIDEvent)
	{
		m_roundAngle = (m_roundAngle+1);
		if (m_roundAngle > 360)
			m_roundAngle -= 360;
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


void CMy08图形消隐与深度缓冲View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_isload)
		SetTimer(ID_TIMER_KARTON, 800, NULL);
	CView::OnRButtonDown(nFlags, point);
}
