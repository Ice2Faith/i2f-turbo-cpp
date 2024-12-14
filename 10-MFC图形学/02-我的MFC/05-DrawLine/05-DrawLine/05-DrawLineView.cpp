
// 05-DrawLineView.cpp : CMy05DrawLineView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "05-DrawLine.h"
#endif

#include "05-DrawLineDoc.h"
#include "05-DrawLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy05DrawLineView

IMPLEMENT_DYNCREATE(CMy05DrawLineView, CView)

BEGIN_MESSAGE_MAP(CMy05DrawLineView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMy05DrawLineView 构造/析构

CMy05DrawLineView::CMy05DrawLineView()
: m_myPoint(0)
, m_isPress(false)
{
	// TODO:  在此处添加构造代码

}

CMy05DrawLineView::~CMy05DrawLineView()
{
}

BOOL CMy05DrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy05DrawLineView 绘制

void CMy05DrawLineView::OnDraw(CDC* /*pDC*/)
{
	CMy05DrawLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMy05DrawLineView 打印

BOOL CMy05DrawLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy05DrawLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy05DrawLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy05DrawLineView 诊断

#ifdef _DEBUG
void CMy05DrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CMy05DrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy05DrawLineDoc* CMy05DrawLineView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy05DrawLineDoc)));
	return (CMy05DrawLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy05DrawLineView 消息处理程序
/*左键按下画连续线*/
/*划线,记录起点*/
void CMy05DrawLineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_myPoint = point;

	/**/
	m_isPress = true;
	CView::OnLButtonDown(nFlags, point);
}

/*划线，记录终点，开始划线--直线*/
void CMy05DrawLineView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_isPress = false;
	CView::OnLButtonUp(nFlags, point);
}


void CMy05DrawLineView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	/*终点作为起点使用，连续划线*/
	if (m_isPress == true)
	{
		CClientDC dc(this);
		dc.MoveTo(m_myPoint);
		dc.LineTo(point);
		m_myPoint = point;
	}
	CView::OnMouseMove(nFlags, point);
}

/*右键按下画直线*/
void CMy05DrawLineView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_myPoint = point;
	CView::OnRButtonDown(nFlags, point);
}


void CMy05DrawLineView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	dc.MoveTo(m_myPoint);
	dc.LineTo(point);
	CView::OnRButtonUp(nFlags, point);
}
