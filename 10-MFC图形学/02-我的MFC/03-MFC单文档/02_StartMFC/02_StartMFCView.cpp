
// 02_StartMFCView.cpp : CMy02_StartMFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "02_StartMFC.h"
#endif

#include "02_StartMFCDoc.h"
#include "02_StartMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02_StartMFCView

IMPLEMENT_DYNCREATE(CMy02_StartMFCView, CView)

BEGIN_MESSAGE_MAP(CMy02_StartMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy02_StartMFCView 构造/析构

CMy02_StartMFCView::CMy02_StartMFCView()
{
	// TODO:  在此处添加构造代码

}

CMy02_StartMFCView::~CMy02_StartMFCView()
{
}

BOOL CMy02_StartMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy02_StartMFCView 绘制

void CMy02_StartMFCView::OnDraw(CDC* pDC)
{
	CMy02_StartMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	pDC->TextOutW(0,0,L"Hello");
}


// CMy02_StartMFCView 打印

BOOL CMy02_StartMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy02_StartMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy02_StartMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy02_StartMFCView 诊断

#ifdef _DEBUG
void CMy02_StartMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMy02_StartMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy02_StartMFCDoc* CMy02_StartMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy02_StartMFCDoc)));
	return (CMy02_StartMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy02_StartMFCView 消息处理程序


void CMy02_StartMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	MessageBox(L"ViewLBD", L"Tips", MB_OK);
	CView::OnLButtonDown(nFlags, point);
}
