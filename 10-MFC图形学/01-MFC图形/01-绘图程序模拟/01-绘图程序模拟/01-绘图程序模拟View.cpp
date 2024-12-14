
// 01-绘图程序模拟View.cpp : CMy01绘图程序模拟View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "01-绘图程序模拟.h"
#endif

#include "01-绘图程序模拟Doc.h"
#include "01-绘图程序模拟View.h"
#include<cmath>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy01绘图程序模拟View

IMPLEMENT_DYNCREATE(CMy01绘图程序模拟View, CView)

BEGIN_MESSAGE_MAP(CMy01绘图程序模拟View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy01绘图程序模拟View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32771, &CMy01绘图程序模拟View::OnSelectPoint)
	ON_COMMAND(ID_32772, &CMy01绘图程序模拟View::OnSelectRecttangle)
	ON_COMMAND(ID_32773, &CMy01绘图程序模拟View::OnSelectElispe)
	ON_COMMAND(ID_32774, &CMy01绘图程序模拟View::OnSelectCircleLine)
	ON_COMMAND(ID_32775, &CMy01绘图程序模拟View::OnSelectLine)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32776, &CMy01绘图程序模拟View::OnSelectClearLine)
	ON_COMMAND(ID_32777, &CMy01绘图程序模拟View::OnSelectPolygon)
	ON_COMMAND(ID_32778, &CMy01绘图程序模拟View::OnSelectRadiate)
	ON_COMMAND(ID_32779, &CMy01绘图程序模拟View::OnSelectHu)
	ON_COMMAND(ID_32780, &CMy01绘图程序模拟View::OnSelectClear)
	ON_COMMAND(ID_32781, &CMy01绘图程序模拟View::OnSelectRoundRect)
	ON_COMMAND(ID_32782, &CMy01绘图程序模拟View::OnSelectBrush)
	ON_COMMAND(ID_32783, &CMy01绘图程序模拟View::OnSelectBigPoint)
	ON_COMMAND(ID_32784, &CMy01绘图程序模拟View::OnSelectStar)
END_MESSAGE_MAP()

// CMy01绘图程序模拟View 构造/析构

CMy01绘图程序模拟View::CMy01绘图程序模拟View()
	: m_Point(0)
	, isLDown(false)
	, canDraw(false)
	, drawType(0)
	, pslen(0)
	, m_hulen(0)
{
	// TODO: 在此处添加构造代码

}

CMy01绘图程序模拟View::~CMy01绘图程序模拟View()
{
}

BOOL CMy01绘图程序模拟View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy01绘图程序模拟View 绘制

void CMy01绘图程序模拟View::OnDraw(CDC* /*pDC*/)
{
	CMy01绘图程序模拟Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy01绘图程序模拟View 打印


void CMy01绘图程序模拟View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy01绘图程序模拟View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy01绘图程序模拟View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy01绘图程序模拟View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy01绘图程序模拟View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy01绘图程序模拟View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy01绘图程序模拟View 诊断

#ifdef _DEBUG
void CMy01绘图程序模拟View::AssertValid() const
{
	CView::AssertValid();
}

void CMy01绘图程序模拟View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy01绘图程序模拟Doc* CMy01绘图程序模拟View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy01绘图程序模拟Doc)));
	return (CMy01绘图程序模拟Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy01绘图程序模拟View 消息处理程序


void CMy01绘图程序模拟View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->canDraw=true;
	this->m_Point=point;
	this->isLDown=true;
	CClientDC dc(this);
	if (this->drawType != 7)
		this->pslen = 0;
	switch(this->drawType)
	{
	case 1:
		dc.SetPixel(point,RGB(255,0,0));
		break;
	case 21:
	{
			   CBrush brush(RGB(0, 0, 0));
			   dc.SelectObject(&brush);
			   dc.Ellipse(point.x-3,point.y-3,point.x+3,point.y+3);
	}
		break;
	case 22:
	{
			   dc.MoveTo(point.x-5,point.y);
			   dc.LineTo(point.x + 5,point.y);
			   dc.MoveTo(point.x, point.y - 5);
			   dc.LineTo(point.x, point.y + 5);
	}
		break;
	case 7:
	{
			  if (this->pslen < 299)
			  {
				  this->m_points[this->pslen++] = point;
				  dc.Polygon(this->m_points,this->pslen);
			  }
			  
			  break;
	}
	case 9:
	{
			  if (this->m_hulen < 3)
			  {
				  this->m_cirhu[this->m_hulen++] = point;
			  }
			  if (this->m_hulen==3)
			  {
				  int r = (int)sqrt(pow(this->m_cirhu[1].x*1.0 - this->m_cirhu[0].x, 2.0) + pow(this->m_cirhu[1].y*1.0 - this->m_cirhu[0].y, 2.0));
				  dc.Arc(this->m_cirhu[0].x - r, this->m_cirhu[0].y - r, this->m_cirhu[0].x + r, this->m_cirhu[0].y+r,
					  this->m_cirhu[1].x, this->m_cirhu[1].y, this->m_cirhu[2].x, this->m_cirhu[2].y);
				  this->m_hulen = 0;
			  }
			  break;
	}
	default:
		break;
	}
	
	CView::OnLButtonDown(nFlags, point);
}


void CMy01绘图程序模拟View::OnSelectPoint()
{
	// TODO: 在此添加命令处理程序代码
	this->drawType=1;
}


void CMy01绘图程序模拟View::OnSelectRecttangle()
{
	// TODO: 在此添加命令处理程序代码
	this->drawType=2;
}


void CMy01绘图程序模拟View::OnSelectElispe()
{
	// TODO: 在此添加命令处理程序代码
	this->drawType=3;
}


void CMy01绘图程序模拟View::OnSelectCircleLine()
{
	// TODO: 在此添加命令处理程序代码
	this->drawType=4;
}


void CMy01绘图程序模拟View::OnSelectLine()
{
	// TODO: 在此添加命令处理程序代码
	this->drawType=5;
}


void CMy01绘图程序模拟View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	switch(this->drawType)
	{
	case 1:
		//dc.SetPixel(point,RGB(255,0,0));
		break;
	case 2:
		if(isLDown)
			dc.Rectangle(this->m_Point.x,this->m_Point.y,point.x,point.y);
		break;
	case 3:
		if(isLDown)
			dc.Ellipse(this->m_Point.x,this->m_Point.y,point.x,point.y);
		break;
	case 5:
		if(isLDown)
		{
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
		}
		break;
	case 10:
	{
			   if (isLDown)
			   {
				   int rh = point.x - this->m_Point.x;
				   int rw = point.y - this->m_Point.y;
				   if (rh < 0)
					   rh = 0 - rh;
				   if (rw < 0)
					   rw = 0 - rw;
				   int r = rh < rw ? rh : rw;
				   r = r / 10;
				   if (r < 5)
					   r = 5;
				   dc.RoundRect(this->m_Point.x, this->m_Point.y, point.x, point.y, r, r);
			   }
				   
			   break;
	}
	default:
		break;
	}
	isLDown=false;
	CView::OnLButtonUp(nFlags, point);
}


void CMy01绘图程序模拟View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	if (drawType == 4)
	{
		if (isLDown)
		{
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
			this->m_Point = point;
		}
	}
	else if (drawType == 6)
	{
		if (isLDown)
		{
			CPen cPen;//生明画笔
			cPen.CreatePen(PS_SOLID, 20, dc.GetBkColor());
			dc.SelectObject(&cPen);
			CBrush brush;
			brush.CreateSolidBrush(dc.GetBkColor());
			dc.SelectObject(&brush);
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
			this->m_Point = point;
		}
	}
	else if (drawType == 8)
	{
		if (isLDown)
		{
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
		}
	}
	else if (drawType == 11)
	{
		if (isLDown)
		{
			CPen cPen;//生明画笔
			cPen.CreatePen(PS_SOLID, 20, RGB(0,0,0));
			dc.SelectObject(&cPen);
			CBrush brush;
			brush.CreateSolidBrush(dc.GetBkColor());
			dc.SelectObject(&brush);
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
			this->m_Point = point;
		}
	}
	
	CView::OnMouseMove(nFlags, point);
}


void CMy01绘图程序模拟View::OnSelectClearLine()
{
	// TODO:  在此添加命令处理程序代码
	this->drawType = 6;
}


void CMy01绘图程序模拟View::OnSelectPolygon()
{
	// TODO:  在此添加命令处理程序代码
	this->drawType = 7;
}


void CMy01绘图程序模拟View::OnSelectRadiate()
{
	// TODO:  在此添加命令处理程序代码
	this->drawType = 8;
}


void CMy01绘图程序模拟View::OnSelectHu()
{
	// TODO:  在此添加命令处理程序代码
	this->drawType = 9;
}


void CMy01绘图程序模拟View::OnSelectClear()
{
	// TODO:  在此添加命令处理程序代码
	CClientDC dc(this);
	CRect rect;
	GetWindowRect(&rect);
	dc.Rectangle(-2,-2,rect.right-rect.left+2,rect.bottom-rect.top+2);
	this->pslen = 0;
}


void CMy01绘图程序模拟View::OnSelectRoundRect()
{
	// TODO:  在此添加命令处理程序代码
	this->drawType = 10;
}


void CMy01绘图程序模拟View::OnSelectBrush()
{
	// TODO:  在此添加命令处理程序代码
	this->drawType = 11;
}


void CMy01绘图程序模拟View::OnSelectBigPoint()
{
	// TODO:  在此添加命令处理程序代码
	this->drawType = 21;
}


void CMy01绘图程序模拟View::OnSelectStar()
{
	// TODO:  在此添加命令处理程序代码
	this->drawType = 22;
}
