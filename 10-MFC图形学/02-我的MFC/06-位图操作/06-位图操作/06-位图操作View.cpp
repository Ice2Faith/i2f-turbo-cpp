
// 06-位图操作View.cpp : CMy06位图操作View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "06-位图操作.h"
#endif

#include "06-位图操作Doc.h"
#include "06-位图操作View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy06位图操作View

IMPLEMENT_DYNCREATE(CMy06位图操作View, CView)

BEGIN_MESSAGE_MAP(CMy06位图操作View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy06位图操作View 构造/析构

CMy06位图操作View::CMy06位图操作View()
{
	// TODO:  在此处添加构造代码

}

CMy06位图操作View::~CMy06位图操作View()
{
}

BOOL CMy06位图操作View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy06位图操作View 绘制

void CMy06位图操作View::OnDraw(CDC* pDC)
{
	CMy06位图操作Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CBrush brush(RGB(255, 0, 0));
	pDC->SelectObject(&brush);
	pDC->Ellipse(120, 120, 240, 240);
	//定义位图
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	//用位图制作画刷
	CBrush brush2(&bitmap);
	pDC->SelectObject(&brush2);
	pDC->Ellipse(240, 240, 480, 480);
	
	// TODO:  在此处为本机数据添加绘制代码
}


// CMy06位图操作View 打印

BOOL CMy06位图操作View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy06位图操作View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy06位图操作View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy06位图操作View 诊断

#ifdef _DEBUG
void CMy06位图操作View::AssertValid() const
{
	CView::AssertValid();
}

void CMy06位图操作View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy06位图操作Doc* CMy06位图操作View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy06位图操作Doc)));
	return (CMy06位图操作Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy06位图操作View 消息处理程序
