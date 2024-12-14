
// 04-事件作业View.cpp : CMy04事件作业View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "04-事件作业.h"
#endif

#include "04-事件作业Doc.h"
#include "04-事件作业View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy04事件作业View

IMPLEMENT_DYNCREATE(CMy04事件作业View, CView)

BEGIN_MESSAGE_MAP(CMy04事件作业View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CMy04事件作业View 构造/析构

CMy04事件作业View::CMy04事件作业View()
{
	// TODO:  在此处添加构造代码

}

CMy04事件作业View::~CMy04事件作业View()
{
}

BOOL CMy04事件作业View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy04事件作业View 绘制

void CMy04事件作业View::OnDraw(CDC* /*pDC*/)
{
	CMy04事件作业Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMy04事件作业View 打印

BOOL CMy04事件作业View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy04事件作业View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy04事件作业View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy04事件作业View 诊断

#ifdef _DEBUG
void CMy04事件作业View::AssertValid() const
{
	CView::AssertValid();
}

void CMy04事件作业View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy04事件作业Doc* CMy04事件作业View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy04事件作业Doc)));
	return (CMy04事件作业Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy04事件作业View 消息处理程序

/*
响应消息左键
*/
void CMy04事件作业View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CString str;
	str.Format(TEXT("x=%d,y=%d"),point.x,point.y);
	MessageBox(str);
	CView::OnLButtonDown(nFlags, point);
}

/*
响应消息按键
*/
void CMy04事件作业View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CString str;
	str.Format(TEXT("%d"), nChar);
	MessageBox(str);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

/*
响应消息有效按键
*/
void CMy04事件作业View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	TCHAR ch = (TCHAR)nChar;
	CString str;
	str.Format(TEXT("%c"),ch);
	MessageBox(str);
	CView::OnChar(nChar, nRepCnt, nFlags);
}
