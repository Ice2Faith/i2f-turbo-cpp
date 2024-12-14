
// 06-图形的光栅扫描显示View.cpp : CMy06图形的光栅扫描显示View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "06-图形的光栅扫描显示.h"
#endif

#include "06-图形的光栅扫描显示Doc.h"
#include "06-图形的光栅扫描显示View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include<deque>
#include<iterator>

// CMy06图形的光栅扫描显示View 构造/析构

CMy06图形的光栅扫描显示View::CMy06图形的光栅扫描显示View()
: p0(0)
, p1(0)
, m_isAntiAlias(false)
{
	// TODO:  在此处添加构造代码
	m_lineColor = 0x0000ff;
	m_FillColor = 0x00ff00;
}

// CMy06图形的光栅扫描显示View 消息处理程序

void CMy06图形的光栅扫描显示View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	p0 = point;
	CView::OnLButtonDown(nFlags, point);
}


void CMy06图形的光栅扫描显示View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	p1 = point;
	CClientDC dc(this);
	if (m_isAntiAlias)
		AntialiasLine(p0, p1, m_lineColor, dc.GetPixel(point));
	else
		DDALine(p0, p1, m_lineColor);
	CView::OnLButtonUp(nFlags, point);
}


// DDA数值微分算法画直线
void CMy06图形的光栅扫描显示View::DDALine(CPoint p1, CPoint p2, COLORREF color)
{
	CClientDC dc(this);
	double dk = 1.0*(p2.y - p1.y) / (p2.x - p1.x);
	if (dk > 1.0 || dk<-1.0)
	{
		if (p1.y > p2.y)
		{
			CPoint t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.x - p1.x) / (p2.y - p1.y);
		while (y < p2.y)
		{
			dc.SetPixelV(x + 0.5, y, color);
			x += k;
			y += 1;
		}
	}
	else
	{
		if (p1.x > p2.x)
		{
			CPoint t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.y - p1.y) / (p2.x - p1.x);
		while (x < p2.x)
		{
			dc.SetPixelV(x, y + 0.5, color);
			y += k;
			x += 1;
		}
	}

}

// 反走样直线绘制
void CMy06图形的光栅扫描显示View::AntialiasLine(CPoint p1, CPoint p2, COLORREF fgc, COLORREF bgc)
{
	CClientDC dc(this);
	double dk = 1.0*(p2.y - p1.y) / (p2.x - p1.x);
	if (dk > 1.0 || dk<-1.0)
	{
		if (p1.y > p2.y)
		{
			CPoint t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.x - p1.x) / (p2.y - p1.y);
		while (y < p2.y)
		{
			double e = x - (int)(x);
			dc.SetPixelV(x + 0.5, y, RGB((fgc & 0xff)*e + (bgc & 0xff)*(1 - e), ((fgc >> 8) & 0xff)*e + ((bgc >> 8) & 0xff)*(1 - e), ((fgc >> 16) & 0xff)*e + ((bgc >> 16) & 0xff)*(1 - e)));
			dc.SetPixelV(x + 0.5 + 1, y, RGB((fgc & 0xff)*(1 - e) + (bgc & 0xff)*e, ((fgc >> 8) & 0xff)*(1 - e) + ((bgc >> 8) & 0xff)*e, ((fgc >> 16) & 0xff)*(1 - e) + ((bgc >> 16) & 0xff)*e));
			x += k;
			y += 1;
		}
	}
	else
	{
		if (p1.x > p2.x)
		{
			CPoint t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.y - p1.y) / (p2.x - p1.x);
		while (x < p2.x)
		{
			double e = y - (int)(y);
			dc.SetPixelV(x, y + 0.5, RGB((fgc & 0xff)*e + (bgc & 0xff)*(1 - e), ((fgc >> 8) & 0xff)*e + ((bgc >> 8) & 0xff)*(1 - e), ((fgc >> 16) & 0xff)*e + ((bgc >> 16) & 0xff)*(1 - e)));
			dc.SetPixelV(x, y + 0.5 + 1, RGB((fgc & 0xff)*(1 - e) + (bgc & 0xff)*e, ((fgc >> 8) & 0xff)*(1 - e) + ((bgc >> 8) & 0xff)*e, ((fgc >> 16) & 0xff)*(1 - e) + ((bgc >> 16) & 0xff)*e));
			y += k;
			x += 1;
		}
	}


}


void CMy06图形的光栅扫描显示View::SeedFillPoly(CPoint seed, COLORREF bgc, COLORREF flc)
{
	CClientDC dc(this);
	std::deque<CPoint> que;
	que.push_back(seed);
	dc.SetPixelV(seed, flc);
	int directs[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
	int directSum = 4;
	while (que.size() != 0)
	{
		for (int i = 0; i < directSum; i++)
		{
			CPoint tp = que.at(0);
			tp.x += directs[i][0];
			tp.y += directs[i][1];
			if (dc.GetPixel(tp) == bgc)
			{
				que.push_back(tp);
				dc.SetPixelV(tp, flc);
			}
		}
		que.pop_front();
	}
}


void CMy06图形的光栅扫描显示View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	SeedFillPoly(point, dc.GetPixel(point), m_FillColor);
	CView::OnRButtonDown(nFlags, point);
}



void CMy06图形的光栅扫描显示View::OnPanelClean()
{
	// TODO:  在此添加命令处理程序代码
	Invalidate();
}

void CMy06图形的光栅扫描显示View::OnClrLineRed()
{
	// TODO:  在此添加命令处理程序代码
	m_lineColor = 0x0000ff;
}


void CMy06图形的光栅扫描显示View::OnClrLineGreen()
{
	// TODO:  在此添加命令处理程序代码
	m_lineColor = 0x00ff00;
}


void CMy06图形的光栅扫描显示View::OnClrLineBlue()
{
	// TODO:  在此添加命令处理程序代码
	m_lineColor = 0xff0000;
}


void CMy06图形的光栅扫描显示View::OnClrLineBalck()
{
	// TODO:  在此添加命令处理程序代码
	m_lineColor = 0x000000;
}


void CMy06图形的光栅扫描显示View::OnClrFillRed()
{
	// TODO:  在此添加命令处理程序代码
	m_FillColor = 0x0000ff;
}


void CMy06图形的光栅扫描显示View::OnClrFillGreen()
{
	// TODO:  在此添加命令处理程序代码
	m_FillColor = 0x00ff00;
}


void CMy06图形的光栅扫描显示View::OnClrFillBlue()
{
	// TODO:  在此添加命令处理程序代码
	m_FillColor = 0xff0000;
}


void CMy06图形的光栅扫描显示View::OnClrFillBlack()
{
	// TODO:  在此添加命令处理程序代码
	m_FillColor = 0x000000;
}


void CMy06图形的光栅扫描显示View::OnClrLineWhite()
{
	// TODO:  在此添加命令处理程序代码
	m_lineColor = 0xffffff;
}


void CMy06图形的光栅扫描显示View::OnClrFillWhite()
{
	// TODO:  在此添加命令处理程序代码
	m_FillColor = 0xffffff;
}


void CMy06图形的光栅扫描显示View::OnStlDda()
{
	// TODO:  在此添加命令处理程序代码
	m_isAntiAlias = false;
}


void CMy06图形的光栅扫描显示View::OnStlAntialias()
{
	// TODO:  在此添加命令处理程序代码
	m_isAntiAlias = true;
}
// CMy06图形的光栅扫描显示View

IMPLEMENT_DYNCREATE(CMy06图形的光栅扫描显示View, CView)

BEGIN_MESSAGE_MAP(CMy06图形的光栅扫描显示View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32771, &CMy06图形的光栅扫描显示View::OnClrLineRed)
	ON_COMMAND(ID_32772, &CMy06图形的光栅扫描显示View::OnClrLineGreen)
	ON_COMMAND(ID_32773, &CMy06图形的光栅扫描显示View::OnClrLineBlue)
	ON_COMMAND(ID_32777, &CMy06图形的光栅扫描显示View::OnClrLineBalck)
	ON_COMMAND(ID_32774, &CMy06图形的光栅扫描显示View::OnClrFillRed)
	ON_COMMAND(ID_32775, &CMy06图形的光栅扫描显示View::OnClrFillGreen)
	ON_COMMAND(ID_32776, &CMy06图形的光栅扫描显示View::OnClrFillBlue)
	ON_COMMAND(ID_32778, &CMy06图形的光栅扫描显示View::OnClrFillBlack)
	ON_COMMAND(ID_32779, &CMy06图形的光栅扫描显示View::OnClrLineWhite)
	ON_COMMAND(ID_32780, &CMy06图形的光栅扫描显示View::OnClrFillWhite)
	ON_COMMAND(ID_32781, &CMy06图形的光栅扫描显示View::OnStlDda)
	ON_COMMAND(ID_32782, &CMy06图形的光栅扫描显示View::OnStlAntialias)
	ON_WM_RBUTTONDBLCLK()
	ON_COMMAND(ID_32783, &CMy06图形的光栅扫描显示View::OnPanelClean)
END_MESSAGE_MAP()


CMy06图形的光栅扫描显示View::~CMy06图形的光栅扫描显示View()
{
}

BOOL CMy06图形的光栅扫描显示View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy06图形的光栅扫描显示View 绘制

void CMy06图形的光栅扫描显示View::OnDraw(CDC* /*pDC*/)
{
	CMy06图形的光栅扫描显示Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMy06图形的光栅扫描显示View 打印

BOOL CMy06图形的光栅扫描显示View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy06图形的光栅扫描显示View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy06图形的光栅扫描显示View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy06图形的光栅扫描显示View 诊断

#ifdef _DEBUG
void CMy06图形的光栅扫描显示View::AssertValid() const
{
	CView::AssertValid();
}

void CMy06图形的光栅扫描显示View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy06图形的光栅扫描显示Doc* CMy06图形的光栅扫描显示View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy06图形的光栅扫描显示Doc)));
	return (CMy06图形的光栅扫描显示Doc*)m_pDocument;
}
#endif //_DEBUG





void CMy06图形的光栅扫描显示View::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	CView::OnRButtonDblClk(nFlags, point);
}



