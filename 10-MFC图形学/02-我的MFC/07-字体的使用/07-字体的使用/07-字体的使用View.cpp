
// 07-字体的使用View.cpp : CMy07字体的使用View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "07-字体的使用.h"
#endif

#include "07-字体的使用Doc.h"
#include "07-字体的使用View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy07字体的使用View

IMPLEMENT_DYNCREATE(CMy07字体的使用View, CView)

BEGIN_MESSAGE_MAP(CMy07字体的使用View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy07字体的使用View 构造/析构

CMy07字体的使用View::CMy07字体的使用View()
{
	// TODO:  在此处添加构造代码

}

CMy07字体的使用View::~CMy07字体的使用View()
{
}

BOOL CMy07字体的使用View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy07字体的使用View 绘制

void CMy07字体的使用View::OnDraw(CDC* pDC)
{
	CMy07字体的使用Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CFont font;
	font.CreatePointFont(1000,TEXT("宋体"));
	pDC->SelectObject(&font);
	pDC->TextOutW(100,100,TEXT("Hello Font"));
	// TODO:  在此处为本机数据添加绘制代码
}


// CMy07字体的使用View 打印

BOOL CMy07字体的使用View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy07字体的使用View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy07字体的使用View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy07字体的使用View 诊断

#ifdef _DEBUG
void CMy07字体的使用View::AssertValid() const
{
	CView::AssertValid();
}

void CMy07字体的使用View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy07字体的使用Doc* CMy07字体的使用View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy07字体的使用Doc)));
	return (CMy07字体的使用Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy07字体的使用View 消息处理程序
