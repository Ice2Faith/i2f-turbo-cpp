
// 12-动态图标View.cpp : CMy12动态图标View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "12-动态图标.h"
#endif

#include "12-动态图标Doc.h"
#include "12-动态图标View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy12动态图标View

IMPLEMENT_DYNCREATE(CMy12动态图标View, CView)

BEGIN_MESSAGE_MAP(CMy12动态图标View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy12动态图标View 构造/析构

CMy12动态图标View::CMy12动态图标View()
{
	// TODO:  在此处添加构造代码

}

CMy12动态图标View::~CMy12动态图标View()
{
}

BOOL CMy12动态图标View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy12动态图标View 绘制

void CMy12动态图标View::OnDraw(CDC* /*pDC*/)
{
	CMy12动态图标Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMy12动态图标View 打印

BOOL CMy12动态图标View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy12动态图标View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy12动态图标View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy12动态图标View 诊断

#ifdef _DEBUG
void CMy12动态图标View::AssertValid() const
{
	CView::AssertValid();
}

void CMy12动态图标View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy12动态图标Doc* CMy12动态图标View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12动态图标Doc)));
	return (CMy12动态图标Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy12动态图标View 消息处理程序
