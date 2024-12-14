
// 09-定时器字体渐变View.cpp : CMy09定时器字体渐变View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "09-定时器字体渐变.h"
#endif

#include "09-定时器字体渐变Doc.h"
#include "09-定时器字体渐变View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy09定时器字体渐变View

IMPLEMENT_DYNCREATE(CMy09定时器字体渐变View, CView)

BEGIN_MESSAGE_MAP(CMy09定时器字体渐变View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMy09定时器字体渐变View 构造/析构

CMy09定时器字体渐变View::CMy09定时器字体渐变View()
{
	// TODO:  在此处添加构造代码

}

CMy09定时器字体渐变View::~CMy09定时器字体渐变View()
{
}

BOOL CMy09定时器字体渐变View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy09定时器字体渐变View 绘制

void CMy09定时器字体渐变View::OnDraw(CDC* /*pDC*/)
{
	CMy09定时器字体渐变Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMy09定时器字体渐变View 打印

BOOL CMy09定时器字体渐变View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy09定时器字体渐变View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy09定时器字体渐变View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy09定时器字体渐变View 诊断

#ifdef _DEBUG
void CMy09定时器字体渐变View::AssertValid() const
{
	CView::AssertValid();
}

void CMy09定时器字体渐变View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy09定时器字体渐变Doc* CMy09定时器字体渐变View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy09定时器字体渐变Doc)));
	return (CMy09定时器字体渐变Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy09定时器字体渐变View 消息处理程序


int CMy09定时器字体渐变View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//参数：ID，时间间隔（毫秒），回调函数（NULL，使用默认处理WM_TIMER）
	SetTimer(101,200,NULL);

	return 0;
}


void CMy09定时器字体渐变View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 101)//区分定时器ID
	{
#if 0
		//计时器使用简介
		static int i = 0;
		CString str;
		str.Format(TEXT("%d"), i++);
		MessageBox(str);
		if (i == 5)
		{//参数：ID
			KillTimer(101);
		}
#endif
		static int wid= 0;
		wid += 5;
		//获取字符串绘图长度
		CString text = TEXT("字符串渐变测试文字");
		CClientDC dc(this);
		CSize size = dc.GetTextExtent(text);
		if (wid > size.cx)//判断渐变矩形和字符矩形长度
		{
			wid = 0;
			Invalidate();//刷新窗口
		}
		int bx = 30;
		int by = 30;
		CRect rect(bx,by,bx+wid,by+size.cy);//创建矩形
		//黑色写一次
		dc.TextOutW(bx, by, text);
		//设置字体颜色
		dc.SetTextColor(RGB(255,0,0));
		dc.DrawText(text,&rect,DT_LEFT);//参数：文字，矩形指针，对其方式
	}
	CView::OnTimer(nIDEvent);
}
