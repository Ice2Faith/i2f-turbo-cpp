
// 13-定时器图片移动View.cpp : CMy13定时器图片移动View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "13-定时器图片移动.h"
#endif

#include "13-定时器图片移动Doc.h"
#include "13-定时器图片移动View.h"
#include<time.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy13定时器图片移动View

IMPLEMENT_DYNCREATE(CMy13定时器图片移动View, CView)

BEGIN_MESSAGE_MAP(CMy13定时器图片移动View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CMy13定时器图片移动View::OnReStart)
END_MESSAGE_MAP()

// CMy13定时器图片移动View 构造/析构

CMy13定时器图片移动View::CMy13定时器图片移动View()
{
	// TODO:  在此处添加构造代码
	for (int i = 0; i < 3;i++)
		px[i] = 0 ;
}

CMy13定时器图片移动View::~CMy13定时器图片移动View()
{
}

BOOL CMy13定时器图片移动View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy13定时器图片移动View 绘制

void CMy13定时器图片移动View::OnDraw(CDC* /*pDC*/)
{
	CMy13定时器图片移动Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	for (int i = 0; i < 3; i++)
	{
		CDC memdc;
		memdc.CreateCompatibleDC(NULL);
		memdc.SelectObject(&this->m_bitmap[i]);
		CClientDC dc(this);
		dc.BitBlt(0 + px[i], i * 134, 134 + px[i], i * 134 + 134, &memdc, 0, 0, SRCCOPY);
	}
	
}


// CMy13定时器图片移动View 打印

BOOL CMy13定时器图片移动View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy13定时器图片移动View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy13定时器图片移动View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy13定时器图片移动View 诊断

#ifdef _DEBUG
void CMy13定时器图片移动View::AssertValid() const
{
	CView::AssertValid();
}

void CMy13定时器图片移动View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy13定时器图片移动Doc* CMy13定时器图片移动View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy13定时器图片移动Doc)));
	return (CMy13定时器图片移动Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy13定时器图片移动View 消息处理程序


int CMy13定时器图片移动View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	this->m_bitmap[0].LoadBitmapW(IDB_BITMAP1);
	this->m_bitmap[1].LoadBitmapW(IDB_BITMAP2);
	this->m_bitmap[2].LoadBitmapW(IDB_BITMAP3);
	SetTimer(101,30,NULL);
	srand((unsigned int)time(NULL));
	return 0;
}


void CMy13定时器图片移动View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	/*不要在这里写绘图代码，这里写更新窗口即可，它自己去调用ondraw*/
	if (nIDEvent == 101)
	{
		CRect rect;
		GetClientRect(&rect);
		px[0] = (px[0] + rand()%10) % (rect.right - rect.left - 134);
		px[1] = (px[1] + rand() % 10) % (rect.right - rect.left - 134);
		px[2] = (px[2] + rand() % 10) % (rect.right - rect.left - 134);
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


void CMy13定时器图片移动View::OnReStart()
{
	// TODO:  在此添加命令处理程序代码
	for (int i = 0; i < 3; i++)
		px[i] = 0;
}
