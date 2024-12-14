
// 05-Bezier曲线绘制View.cpp : CMy05Bezier曲线绘制View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "05-Bezier曲线绘制.h"
#endif

#include "05-Bezier曲线绘制Doc.h"
#include "05-Bezier曲线绘制View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double CMy05Bezier曲线绘制View::Bernstein(int i, int n, double t)
{
	double son = 1, mon = 1, ti = 1, tin = 1;
	for (int j = 0; j<n; j++)
	{
		if (j<i)
		{
			son *= n - j;
			mon *= j + 1;
			ti *= t;
		}
		else
		{
			tin *= (1 - t);
		}

	}
	return (son / mon)*ti*tin;
}
double CMy05Bezier曲线绘制View::BezierX(int n, double t, CPoint points[])
{
	double sum = 0;
	for (int i = 0; i<n-1; i++)
	{
		sum += points[i].x*Bernstein(i, n-1, t);
	}
	return sum;
}
double CMy05Bezier曲线绘制View::BezierY(int n, double t, CPoint points[])
{
	double sum = 0;
	for (int i = 0; i<n-1; i++)
	{
		sum += points[i].y*Bernstein(i, n-1, t);
	}
	return sum;
}
void CMy05Bezier曲线绘制View::DrawBezierLine()
{
	int tCount = 20000;
	CClientDC dc(this);
	FILE * fp = fopen("log.txt","w");
	dc.Polyline(m_points,m_pointCount);
	for (int i = 0; i < tCount*0.8; i++)
	{
		int x = (int)BezierX(this->m_pointCount,1.0*i/tCount,this->m_points);
		int y = (int)BezierY(this->m_pointCount, 1.0*i / tCount, this->m_points);
		dc.SetPixelV(x,y,0x0000ff);
		fprintf(fp, "%d %d\n", x, y);
	}
	fclose(fp);
}
void CMy05Bezier曲线绘制View::ShowCtrlPoint()
{
	CClientDC dc(this);
	for (int i = 0; i < this->m_pointCount; i++)
	{
		dc.Ellipse(this->m_points[i].x - 3, this->m_points[i].y - 3, this->m_points[i].x + 3, this->m_points[i].y + 3);
	}
}
// CMy05Bezier曲线绘制View 构造/析构

CMy05Bezier曲线绘制View::CMy05Bezier曲线绘制View()
: m_pointCount(0)
, m_state(1)
, m_isLDown(false)
, m_moveIndex(0)
{
	// TODO:  在此处添加构造代码

}

CMy05Bezier曲线绘制View::~CMy05Bezier曲线绘制View()
{
}
// CMy05Bezier曲线绘制View 绘制

void CMy05Bezier曲线绘制View::OnDraw(CDC* pDC)
{
	CMy05Bezier曲线绘制Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	DrawBezierLine();
	if (m_state == 2)
		ShowCtrlPoint();
}
// CMy05Bezier曲线绘制View 消息处理程序


void CMy05Bezier曲线绘制View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_isLDown = true;
	if (m_state == 1)
	{
		this->m_points[this->m_pointCount++] = point;
		Invalidate();
	}
	if (m_state == 2)
	{
		m_moveIndex = -1;
		for (int i = 0; i <m_pointCount; i++)
		{
			if (sqrt(pow(point.x - m_points[i].x, 2.0) + pow(point.y - m_points[i].y, 2.0)) < 3)
			{
				m_moveIndex = i;
				break;
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy05Bezier曲线绘制View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (m_state == 1)
	{
		this->m_pointCount = 0;
		Invalidate();
	}
	CView::OnRButtonDown(nFlags, point);
}


void CMy05Bezier曲线绘制View::OnBezierBeginDraw()
{
	// TODO:  在此添加命令处理程序代码
	m_state = 1;
	Invalidate();
}


void CMy05Bezier曲线绘制View::OnBezierEditPoint()
{
	// TODO:  在此添加命令处理程序代码
	m_state = 2;
	Invalidate();
}


void CMy05Bezier曲线绘制View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_isLDown)
	{
		if (m_moveIndex != -1)
		{
			m_points[m_moveIndex] = point;
			Invalidate();
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CMy05Bezier曲线绘制View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_isLDown = false;
	CView::OnLButtonUp(nFlags, point);
}
// CMy05Bezier曲线绘制View

IMPLEMENT_DYNCREATE(CMy05Bezier曲线绘制View, CView)

BEGIN_MESSAGE_MAP(CMy05Bezier曲线绘制View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_BEZIER32771, &CMy05Bezier曲线绘制View::OnBezierBeginDraw)
	ON_COMMAND(ID_BEZIER32772, &CMy05Bezier曲线绘制View::OnBezierEditPoint)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


BOOL CMy05Bezier曲线绘制View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}


// CMy05Bezier曲线绘制View 打印

BOOL CMy05Bezier曲线绘制View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy05Bezier曲线绘制View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy05Bezier曲线绘制View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy05Bezier曲线绘制View 诊断

#ifdef _DEBUG
void CMy05Bezier曲线绘制View::AssertValid() const
{
	CView::AssertValid();
}

void CMy05Bezier曲线绘制View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy05Bezier曲线绘制Doc* CMy05Bezier曲线绘制View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy05Bezier曲线绘制Doc)));
	return (CMy05Bezier曲线绘制Doc*)m_pDocument;
}
#endif //_DEBUG



