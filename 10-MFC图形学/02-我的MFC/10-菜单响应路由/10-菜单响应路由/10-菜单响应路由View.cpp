
// 10-菜单响应路由View.cpp : CMy10菜单响应路由View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "10-菜单响应路由.h"
#endif

#include "10-菜单响应路由Doc.h"
#include "10-菜单响应路由View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy10菜单响应路由View

IMPLEMENT_DYNCREATE(CMy10菜单响应路由View, CView)

BEGIN_MESSAGE_MAP(CMy10菜单响应路由View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	//ON_COMMAND(ID_TEST_DEMO, &CMy10菜单响应路由View::OnTestDemo)
END_MESSAGE_MAP()

// CMy10菜单响应路由View 构造/析构

CMy10菜单响应路由View::CMy10菜单响应路由View()
{
	// TODO:  在此处添加构造代码

}

CMy10菜单响应路由View::~CMy10菜单响应路由View()
{
}

BOOL CMy10菜单响应路由View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy10菜单响应路由View 绘制

void CMy10菜单响应路由View::OnDraw(CDC* /*pDC*/)
{
	CMy10菜单响应路由Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMy10菜单响应路由View 打印

BOOL CMy10菜单响应路由View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy10菜单响应路由View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy10菜单响应路由View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy10菜单响应路由View 诊断

#ifdef _DEBUG
void CMy10菜单响应路由View::AssertValid() const
{
	CView::AssertValid();
}

void CMy10菜单响应路由View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy10菜单响应路由Doc* CMy10菜单响应路由View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy10菜单响应路由Doc)));
	return (CMy10菜单响应路由Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy10菜单响应路由View 消息处理程序
/*
菜单命令消息路由的消息传递顺序，有处理就进行结束传递：
Frame->View->Doc->View->Frame->App
*/
/*
消息分类;
命令消息：WM_COMMAND:菜单处理函数使用
标准消息：WM_LBUTTONDOWN:普通消息等
通告消息：按钮点击消息等，回调函数
CWnd可以接受任何消息
CCmdTarget不能接受标准消息
*/

//void CMy10菜单响应路由View::OnTestDemo()
//{
//	// TODO:  在此添加命令处理程序代码
//	MessageBox(TEXT("View"));
//}
