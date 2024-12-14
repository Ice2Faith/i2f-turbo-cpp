
// 14-对话框引入View.cpp : CMy14对话框引入View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "14-对话框引入.h"
#endif

#include "14-对话框引入Doc.h"
#include "14-对话框引入View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy14对话框引入View

IMPLEMENT_DYNCREATE(CMy14对话框引入View, CView)

BEGIN_MESSAGE_MAP(CMy14对话框引入View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy14对话框引入View 构造/析构

CMy14对话框引入View::CMy14对话框引入View()
{
	// TODO:  在此处添加构造代码

}

CMy14对话框引入View::~CMy14对话框引入View()
{
}

BOOL CMy14对话框引入View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy14对话框引入View 绘制

void CMy14对话框引入View::OnDraw(CDC* /*pDC*/)
{
	CMy14对话框引入Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMy14对话框引入View 打印

BOOL CMy14对话框引入View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy14对话框引入View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy14对话框引入View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy14对话框引入View 诊断

#ifdef _DEBUG
void CMy14对话框引入View::AssertValid() const
{
	CView::AssertValid();
}

void CMy14对话框引入View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy14对话框引入Doc* CMy14对话框引入View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy14对话框引入Doc)));
	return (CMy14对话框引入Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy14对话框引入View 消息处理程序
