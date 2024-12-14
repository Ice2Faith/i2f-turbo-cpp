
// 11-菜单静态操作View.cpp : CMy11菜单静态操作View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "11-菜单静态操作.h"
#endif

#include "11-菜单静态操作Doc.h"
#include "11-菜单静态操作View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy11菜单静态操作View

IMPLEMENT_DYNCREATE(CMy11菜单静态操作View, CView)

BEGIN_MESSAGE_MAP(CMy11菜单静态操作View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy11菜单静态操作View 构造/析构

CMy11菜单静态操作View::CMy11菜单静态操作View()
{
	// TODO:  在此处添加构造代码

}

CMy11菜单静态操作View::~CMy11菜单静态操作View()
{
}

BOOL CMy11菜单静态操作View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy11菜单静态操作View 绘制

void CMy11菜单静态操作View::OnDraw(CDC* /*pDC*/)
{
	CMy11菜单静态操作Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMy11菜单静态操作View 打印

BOOL CMy11菜单静态操作View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy11菜单静态操作View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy11菜单静态操作View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy11菜单静态操作View 诊断

#ifdef _DEBUG
void CMy11菜单静态操作View::AssertValid() const
{
	CView::AssertValid();
}

void CMy11菜单静态操作View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy11菜单静态操作Doc* CMy11菜单静态操作View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy11菜单静态操作Doc)));
	return (CMy11菜单静态操作Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy11菜单静态操作View 消息处理程序
/*
Frame Create
*/
//鼠标左键按下
void CMy11菜单静态操作View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//获取菜单项
	//CMenu * menu = GetMenu();//菜单属于框架类，不能直接进行加载
	//创建菜单项
	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	//获取子菜单
	CMenu * sonmenu = menu.GetSubMenu(0);
	//CMenu::TrackPopupMenu,子菜单作为快捷菜单
	//客户区坐标转屏幕坐标
	ClientToScreen(&point);
	sonmenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,this);
	CView::OnLButtonDown(nFlags, point);
}
