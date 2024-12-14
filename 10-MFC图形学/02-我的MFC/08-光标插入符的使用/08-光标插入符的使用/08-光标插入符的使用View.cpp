
// 08-光标插入符的使用View.cpp : CMy08光标插入符的使用View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "08-光标插入符的使用.h"
#endif

#include "08-光标插入符的使用Doc.h"
#include "08-光标插入符的使用View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy08光标插入符的使用View

IMPLEMENT_DYNCREATE(CMy08光标插入符的使用View, CView)

BEGIN_MESSAGE_MAP(CMy08光标插入符的使用View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CMy08光标插入符的使用View 构造/析构

CMy08光标插入符的使用View::CMy08光标插入符的使用View()
: m_myPoint(0)
, m_string(_T(""))
{
	// TODO:  在此处添加构造代码

}

CMy08光标插入符的使用View::~CMy08光标插入符的使用View()
{
}

BOOL CMy08光标插入符的使用View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy08光标插入符的使用View 绘制

void CMy08光标插入符的使用View::OnDraw(CDC* /*pDC*/)
{
	CMy08光标插入符的使用Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMy08光标插入符的使用View 打印

BOOL CMy08光标插入符的使用View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy08光标插入符的使用View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy08光标插入符的使用View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy08光标插入符的使用View 诊断

#ifdef _DEBUG
void CMy08光标插入符的使用View::AssertValid() const
{
	CView::AssertValid();
}

void CMy08光标插入符的使用View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy08光标插入符的使用Doc* CMy08光标插入符的使用View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy08光标插入符的使用Doc)));
	return (CMy08光标插入符的使用Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy08光标插入符的使用View 消息处理程序

/*窗口创建后自动调用*/
int CMy08光标插入符的使用View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//继承于CWnd
	//获取字体信息
	CClientDC dc(this);
	TEXTMETRIC tm;//字体信息结构体
	dc.GetTextMetrics(&tm);
	//创建插入符
	CreateSolidCaret(tm.tmAveCharWidth/8,tm.tmHeight);//适配字体高度和宽度
	//显示插入符
	ShowCaret();
	return 0;
}


void CMy08光标插入符的使用View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SetCaretPos(point);//设置光标位置
	m_myPoint = point;//保存坐标
	m_string.Empty();//清空原来的字符串
	CView::OnLButtonDown(nFlags, point);
}


void CMy08光标插入符的使用View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//实现输入
	CClientDC dc(this);
	
	if (nChar == VK_RETURN)//换行
	{
		TEXTMETRIC tm;//字体信息结构体
		dc.GetTextMetrics(&tm);
		m_string.Empty();
		m_myPoint.y += tm.tmHeight;
		m_myPoint.x = 0;
		SetCaretPos(m_myPoint);
	}
	else if (nChar == VK_BACK)//退格
	{
		//获取背景色
		COLORREF color= dc.GetBkColor();
		//设置写字颜色
		COLORREF oldcolor = dc.SetTextColor(color);
		//重写覆盖
		dc.TextOutW(m_myPoint.x, m_myPoint.y, m_string);
		m_string = m_string.Left(m_string.GetLength()-1);
		//恢复原来的颜色
		dc.SetTextColor(oldcolor);
		dc.TextOutW(m_myPoint.x, m_myPoint.y, m_string);
	}
	else
	{
		m_string += (TCHAR)nChar;
	}
	CSize size = dc.GetTextExtent(m_string);
	int x = m_myPoint.x + size.cx;
	int y = m_myPoint.y;//实现光标跟随
	SetCaretPos(CPoint(x, y));//m_myPoint的值此处不能更改
	dc.TextOutW(m_myPoint.x, m_myPoint.y, m_string);
	CView::OnChar(nChar, nRepCnt, nFlags);
}
