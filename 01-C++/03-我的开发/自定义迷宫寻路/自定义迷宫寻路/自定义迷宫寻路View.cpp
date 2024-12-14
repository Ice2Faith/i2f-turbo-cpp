
// 自定义迷宫寻路View.cpp : C自定义迷宫寻路View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "自定义迷宫寻路.h"
#endif

#include "自定义迷宫寻路Doc.h"
#include "自定义迷宫寻路View.h"

#include<graphics.h>
#include"MFCBatchDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C自定义迷宫寻路View

IMPLEMENT_DYNCREATE(C自定义迷宫寻路View, CView)

BEGIN_MESSAGE_MAP(C自定义迷宫寻路View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_MAP, &C自定义迷宫寻路View::OnEditMap)
	ON_COMMAND(ID_EDIT_POINT, &C自定义迷宫寻路View::OnEditPoint)
	ON_COMMAND(ID_EDIT_START, &C自定义迷宫寻路View::OnEditStart)
	ON_COMMAND(ID_CLEAN, &C自定义迷宫寻路View::OnClean)
	ON_WM_TIMER()
	ON_COMMAND(ID_SIZE_20X20, &C自定义迷宫寻路View::OnSize20x20)
	ON_COMMAND(ID_SIZE_50X50, &C自定义迷宫寻路View::OnSize50x50)
	ON_COMMAND(ID_SIZE_80X80, &C自定义迷宫寻路View::OnSize80x80)
	ON_COMMAND(ID_SIZE_100X100, &C自定义迷宫寻路View::OnSize100x100)
	ON_COMMAND(ID_SIZE_200X200, &C自定义迷宫寻路View::OnSize200x200)
	ON_COMMAND(ID_SIZE_300X300, &C自定义迷宫寻路View::OnSize300x300)
	ON_COMMAND(ID_ANIMA_OPEN, &C自定义迷宫寻路View::OnAnimaOpen)
	ON_COMMAND(ID_ANIMA_CLOSE, &C自定义迷宫寻路View::OnAnimaClose)
	ON_COMMAND(ID_HELP_VIEW, &C自定义迷宫寻路View::OnHelpView)
	ON_COMMAND(ID_DIRECT_4, &C自定义迷宫寻路View::OnDirect4)
	ON_COMMAND(ID_DIRECT_8, &C自定义迷宫寻路View::OnDirect8)
	ON_COMMAND(ID_EDIT_RANDOMMAP, &C自定义迷宫寻路View::OnEditRandommap)
	ON_COMMAND(ID_SLEEP_16, &C自定义迷宫寻路View::OnSleep16)
	ON_COMMAND(ID_SLEEP_22, &C自定义迷宫寻路View::OnSleep22)
	ON_COMMAND(ID_SLEEP_33, &C自定义迷宫寻路View::OnSleep33)
	ON_COMMAND(ID_SLEEP_41, &C自定义迷宫寻路View::OnSleep41)
	ON_COMMAND(ID_SLEEP_83, &C自定义迷宫寻路View::OnSleep83)
	ON_COMMAND(ID_SLEEP_8, &C自定义迷宫寻路View::OnSleep8)
	ON_COMMAND(ID_STEP_ROUND, &C自定义迷宫寻路View::OnStepRound)
	ON_COMMAND(ID_STEP_STEP, &C自定义迷宫寻路View::OnStepStep)
	ON_COMMAND(ID_SLEEP_333, &C自定义迷宫寻路View::OnSleep333)
	ON_COMMAND(ID_SLEEP_1000, &C自定义迷宫寻路View::OnSleep1000)
	ON_COMMAND(ID_SHOW_ALLANI, &C自定义迷宫寻路View::OnShowAllani)
	ON_COMMAND(ID_SHOW_BORDERANI, &C自定义迷宫寻路View::OnShowBorderani)
	ON_COMMAND(ID_FILE_LOADIMG, &C自定义迷宫寻路View::OnFileLoadimg)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_FILE_SAVEIMG, &C自定义迷宫寻路View::OnFileSaveimg)
	ON_COMMAND(ID_EDIT_BLOCK, &C自定义迷宫寻路View::OnEditBlock)
	ON_COMMAND(ID_FILE_GRAYHALF, &C自定义迷宫寻路View::OnFileGrayhalf)
	ON_COMMAND(ID_FILE_BORDERLOAD, &C自定义迷宫寻路View::OnFileBorderload)
END_MESSAGE_MAP()

// C自定义迷宫寻路View 构造/析构

C自定义迷宫寻路View::C自定义迷宫寻路View()
: isLbtnDown(false)
, isRbtnDown(false)
, downPoint(0)
, isDirectGrayPic(false)
{
	// TODO:  在此处添加构造代码
	editType = ET_Map;
	isRouting = false;
	isOpenAnimate = true;
	TIMER_SLEEP = 33;
	isDrawAllRoute = false;
}

C自定义迷宫寻路View::~C自定义迷宫寻路View()
{
}

BOOL C自定义迷宫寻路View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C自定义迷宫寻路View 绘制

void C自定义迷宫寻路View::OnDraw(CDC* pDC)
{
	C自定义迷宫寻路Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	this->DragAcceptFiles(TRUE);

	static COLORREF bkcolor = 0xffffff;
	MFCBatchDraw draw(pDC);

	// TODO:  在此处为本机数据添加绘制代码
	CDC * dc = draw.BeginBatchDraw();
	draw.clearDc(bkcolor);

	blockWid = draw.getDcWidth()*1.0 / autoRouter.getWidth();
	blockHei = draw.getDcHeight()*1.0 / autoRouter.getHeight();
	CPen pen(0, 0, (COLORREF)0xeeeeee);
	CPen* oldpen = dc->SelectObject(&pen);
	for (int i = 0; i < autoRouter.getHeight(); i++)
	{
		for (int j = 0; j < autoRouter.getWidth(); j++)
		{
			short elem = autoRouter.At(i,j);
			switch (elem)
			{
			case ELEM_VECANT:
			{
								if ((i+j)%2==0) //纹理拼图绘制，减少一半绘制量
									break;
								CBrush brush(bkcolor);
								CBrush* ob = dc->SelectObject(&brush);
								dc->Rectangle(j*blockWid, i*blockHei, (j + 1)*blockWid, (i + 1)*blockHei);
								dc->SelectObject(ob);
			}
				break;
			case ELEM_WALL:
			{
							  CBrush brush((COLORREF)0x000000);
							  CBrush* ob = dc->SelectObject(&brush);
							  dc->Rectangle(j*blockWid, i*blockHei, (j + 1)*blockWid, (i + 1)*blockHei);
							  dc->SelectObject(ob);
			}
				break;
			}
			
		}
	}
	if (isRouting )
	{
		int minX, minY;
		int maxX, maxY;
		CBrush brush((COLORREF)0xffdd00);
		CBrush* ob = dc->SelectObject(&brush);
		
		AutoRouterCore::TNode * node =NULL;
		if (isDrawAllRoute)
			node = autoRouter.getRouteList();
		else
			node= autoRouter.getCurrentRestList();
		minX = node->p.x;
		maxX = node->p.x;
		minY = node->p.y;
		maxY = node->p.y;
		while (node)
		{
			int j = node->p.y;
			int i = node->p.x;

			if (i < minX)minX = i;
			if (i>maxX)maxX = i;
			if (j < minY)minY = j;
			if (j>maxY)maxY = j;

			dc->Rectangle(j*blockWid, i*blockHei, (j + 1)*blockWid, (i + 1)*blockHei);
			node = node->next;
		}
		dc->SelectObject(ob);
		lastUpdateArea.top = (minX - 1)*blockHei;
		lastUpdateArea.left = (minY - 1)*blockWid;
		lastUpdateArea.bottom = (maxX + 2)*blockHei;
		lastUpdateArea.right = (maxY + 2)*blockWid;
	}
	if (isRouting == false && autoRouter.isRouteSuccess())
	{
		AutoRouterCore::TNode * node = autoRouter.getSuccessRouteNode();
		CBrush brush((COLORREF)0xff5500);
		CBrush* ob = dc->SelectObject(&brush);

		while (node)
		{
			int j = node->p.y;
			int i = node->p.x;
			dc->Rectangle(j*blockWid, i*blockHei, (j + 1)*blockWid, (i + 1)*blockHei);
			node = node->parent;
		}
		dc->SelectObject(ob);
	}
	int x, y;
	{
		x = autoRouter.getStartX();
		y = autoRouter.getStartY();
		CBrush brush((COLORREF)0x0000ff);
		CBrush* ob = dc->SelectObject(&brush);
		dc->Rectangle(y*blockWid, x*blockHei, (y + 1)*blockWid, (x + 1)*blockHei);
		dc->SelectObject(ob);
	}
	
	{
		x = autoRouter.getEndX();
		y = autoRouter.getEndY();
		CBrush brush((COLORREF)0x00ff00);
		CBrush* ob = dc->SelectObject(&brush);
		dc->Rectangle(y*blockWid, x*blockHei, (y + 1)*blockWid, (x + 1)*blockHei);
		dc->SelectObject(ob);
	}

	dc->SelectObject(&oldpen);

	draw.EndBatchDraw();
}


// C自定义迷宫寻路View 打印

BOOL C自定义迷宫寻路View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C自定义迷宫寻路View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void C自定义迷宫寻路View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// C自定义迷宫寻路View 诊断

#ifdef _DEBUG
void C自定义迷宫寻路View::AssertValid() const
{
	CView::AssertValid();
}

void C自定义迷宫寻路View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C自定义迷宫寻路Doc* C自定义迷宫寻路View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C自定义迷宫寻路Doc)));
	return (C自定义迷宫寻路Doc*)m_pDocument;
}
#endif //_DEBUG


// C自定义迷宫寻路View 消息处理程序


void C自定义迷宫寻路View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	downPoint = point;
	int y = point.x / blockWid;
	int x = point.y / blockHei;
	CRect invRec(point.x - blockWid, point.y - blockHei, point.x + blockWid, point.y + blockHei);
	if (editType == ET_Map)
	{
		autoRouter.At(x, y) = ELEM_WALL;
		InvalidateRect(invRec);
	}
	else if (editType == ET_Point)
	{
		autoRouter.setStartPoint(x, y);
		Invalidate();
	}
	isLbtnDown = true;
	CView::OnLButtonDown(nFlags, point);
}


void C自定义迷宫寻路View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	downPoint = point;
	int y = point.x / blockWid;
	int x = point.y / blockHei;
	CRect invRec(point.x - blockWid, point.y - blockHei, point.x + blockWid, point.y + blockHei);
	if (editType == ET_Map)
	{
		autoRouter.At(x, y) = ELEM_VECANT;
		InvalidateRect(invRec);
	}
	else if (editType == ET_Point)
	{
		autoRouter.setEndPoint(x, y);
		Invalidate();
	}
	isRbtnDown = true;
	CView::OnRButtonDown(nFlags, point);
}

void C自定义迷宫寻路View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (editType == ET_Block)
	{
		CPoint ps = downPoint;
		CPoint pe = point;
		downPoint.x = ps.x < pe.x ? ps.x : pe.x;
		downPoint.y = ps.y < pe.y ? ps.y : pe.y;
		point.x = ps.x>pe.x ? ps.x : pe.x;
		point.y = ps.y>pe.y ? ps.y : pe.y;

		int xt = point.x - downPoint.x >= 0 ? 1 : -1;
		int yt = point.y - downPoint.y >= 0 ? 1 : -1;
		int by = downPoint.x / blockWid;
		int bx = downPoint.y / blockHei;
		int ey = point.x / blockWid;
		int ex = point.y / blockHei;
		for (int i = bx; i != ex; i += xt)
		{
			for (int j = by; j != ey; j += yt)
			{
				autoRouter.At(i, j) = ELEM_WALL;
			}
		}
		Invalidate();
	}
	isLbtnDown = false;
	CView::OnLButtonUp(nFlags, point);
}


void C自定义迷宫寻路View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (editType == ET_Block)
	{
		CPoint ps = downPoint;
		CPoint pe = point;
		downPoint.x = ps.x < pe.x ? ps.x : pe.x;
		downPoint.y = ps.y < pe.y ? ps.y : pe.y;
		point.x = ps.x>pe.x ? ps.x : pe.x;
		point.y = ps.y>pe.y ? ps.y : pe.y;

		int xt = point.x - downPoint.x >= 0 ? 1 : -1;
		int yt = point.y - downPoint.y >= 0 ? 1 : -1;
		int by = downPoint.x / blockWid;
		int bx = downPoint.y / blockHei;
		int ey = point.x / blockWid;
		int ex = point.y / blockHei;
		for (int i = bx; i != ex; i+=xt)
		{
			for (int j = by; j != ey; j+=yt)
			{
				autoRouter.At(i, j) = ELEM_VECANT;
			}
		}
		Invalidate();
	}
	isRbtnDown = false;
	CView::OnRButtonUp(nFlags, point);
}

void C自定义迷宫寻路View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int y = point.x / blockWid;
	int x = point.y / blockHei;
	CRect invRec(point.x -  blockWid, point.y -  blockHei, point.x +  blockWid, point.y +  blockHei );
	if (editType == ET_Map)
	{
		if (isLbtnDown)
		{
			autoRouter.At(x, y) = ELEM_WALL;
			InvalidateRect(invRec);
		}
		else if (isRbtnDown)
		{
			autoRouter.At(x, y) = ELEM_VECANT;
			InvalidateRect(invRec);
		}
	}
	else if (editType == ET_Point)
	{

	}
	
	CView::OnMouseMove(nFlags, point);
}




void C自定义迷宫寻路View::OnEditMap()
{
	editType = ET_Map;
}


void C自定义迷宫寻路View::OnEditPoint()
{
	editType = ET_Point;
}

#define TIMER_SHOW_ROUTE_ANIMATE 0x101
void C自定义迷宫寻路View::OnEditStart()
{
	lastUpdateArea.top = (autoRouter.getStartY() - 1)*blockHei;
	lastUpdateArea.bottom = (autoRouter.getStartY() + 1)*blockHei;
	lastUpdateArea.left = (autoRouter.getStartX() - 1)*blockWid;
	lastUpdateArea.right = (autoRouter.getStartX() + 1)*blockWid;
	Invalidate();

	editType=ET_Map;
	isRouting = true;
	autoRouter.routeFirst();
	KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
	if (isOpenAnimate)
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	else
	{
		while (autoRouter.routeStep());
		isRouting = false;
		Invalidate();
	}

}


void C自定义迷宫寻路View::OnClean()
{
	autoRouter.clean();
	Invalidate();
}


void C自定义迷宫寻路View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (TIMER_SHOW_ROUTE_ANIMATE == nIDEvent)
	{
		if (isOpenAnimate == false)
		{
			KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
			while (autoRouter.routeStep());
			isRouting = false;
			Invalidate();
			return;
		}
		if (autoRouter.routeStep() == false)
		{
			isRouting = false;
			KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
			Invalidate();
		}
		if (isOpenAnimate)
			InvalidateRect(lastUpdateArea);
	}
	CView::OnTimer(nIDEvent);
}


void C自定义迷宫寻路View::OnSize20x20()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setSize(20, 20);
	Invalidate();
}


void C自定义迷宫寻路View::OnSize50x50()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setSize(50, 50);
	Invalidate();
}


void C自定义迷宫寻路View::OnSize80x80()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setSize(80, 80);
	Invalidate();
}


void C自定义迷宫寻路View::OnSize100x100()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setSize(100, 100);
	Invalidate();
}


void C自定义迷宫寻路View::OnSize200x200()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setSize(200, 200);
	Invalidate();
}


void C自定义迷宫寻路View::OnSize300x300()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setSize(300, 300);
	Invalidate();
}


void C自定义迷宫寻路View::OnAnimaOpen()
{
	// TODO:  在此添加命令处理程序代码
	isOpenAnimate = true;
}


void C自定义迷宫寻路View::OnAnimaClose()
{
	// TODO:  在此添加命令处理程序代码
	isOpenAnimate = false;
}


void C自定义迷宫寻路View::OnHelpView()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox(L"编辑地形：\n\
\t鼠标左键点击或者按住拖动，添加墙体\n\
\t鼠标右键点击或者按住拖动，移除墙体\n\
编辑起止点：\n\
\t左键点击设置出发点\n\
\t右键点击设置结束点\n\
使用步骤\n\
\t可选编辑地形\n\
\t一定设置起始点，可以是绝路\n\
\t点击开始\n\
动画：\n\
\t开启动画则演示寻路过程\n\
\t关闭动画则直接给出寻路结果\n\
");
}


void C自定义迷宫寻路View::OnDirect4()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setRouteMode4Direct(true);
}


void C自定义迷宫寻路View::OnDirect8()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setRouteMode4Direct(false);
}


void C自定义迷宫寻路View::OnEditRandommap()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setRandomWall();
	Invalidate();
}


void C自定义迷宫寻路View::OnSleep16()
{
	// TODO:  在此添加命令处理程序代码
	TIMER_SLEEP = 16;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C自定义迷宫寻路View::OnSleep22()
{
	// TODO:  在此添加命令处理程序代码
	TIMER_SLEEP = 22;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C自定义迷宫寻路View::OnSleep33()
{
	// TODO:  在此添加命令处理程序代码
	TIMER_SLEEP = 33;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C自定义迷宫寻路View::OnSleep41()
{
	// TODO:  在此添加命令处理程序代码
	TIMER_SLEEP = 41;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C自定义迷宫寻路View::OnSleep83()
{
	// TODO:  在此添加命令处理程序代码
	TIMER_SLEEP = 83;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C自定义迷宫寻路View::OnSleep8()
{
	// TODO:  在此添加命令处理程序代码
	TIMER_SLEEP = 8;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}

void C自定义迷宫寻路View::OnSleep333()
{
	// TODO:  在此添加命令处理程序代码
	TIMER_SLEEP = 333;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}

}


void C自定义迷宫寻路View::OnSleep1000()
{
	// TODO:  在此添加命令处理程序代码
	TIMER_SLEEP = 1000;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}

}


void C自定义迷宫寻路View::OnStepRound()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setRouteStepModeIsRoundCircle(true);
}


void C自定义迷宫寻路View::OnStepStep()
{
	// TODO:  在此添加命令处理程序代码
	autoRouter.setRouteStepModeIsRoundCircle(false);
}




void C自定义迷宫寻路View::OnShowAllani()
{
	// TODO:  在此添加命令处理程序代码
	isDrawAllRoute = true;
}


void C自定义迷宫寻路View::OnShowBorderani()
{
	// TODO:  在此添加命令处理程序代码
	isDrawAllRoute = false;
}


void C自定义迷宫寻路View::OnFileLoadimg()
{
	// TODO:  在此添加命令处理程序代码
	TCHAR fileName[256];
	bool input = InputBox(fileName, 256, TEXT("请输入文件名，一张图片的名称"), TEXT("读取图片"));
	if (input)
	{
		LoadImgFileAsMap(fileName);
	}
}


void C自定义迷宫寻路View::LoadImgFileAsMap(TCHAR * fileName)
{
	IMAGE img;
	int wid = autoRouter.getWidth();
	int hei = autoRouter.getHeight();
	loadimage(&img, fileName, wid,hei , true);
	HDC hdc=GetImageHDC(&img);
	short last = 0;
	static double similarRate = 0.85;
	for (int i = 0; i < hei; i++)
	{
		for (int j = 0; j < wid; j++)
		{
			short gray = RGBtoGRAY(GetPixel(hdc, j, i)) & 0xff;
			bool drawW = false;
			if (isDirectGrayPic)
				drawW = gray < 128;
			else
			{
				short little = last < gray ? last : gray;
				short bigger = last>gray ? last : gray;
				double rate = little*1.0 / bigger;
				drawW = rate < similarRate ? true : false;
			}
			if (drawW)
			{
				autoRouter.At(i, j) = ELEM_WALL;
			}
			else
			{
				autoRouter.At(i, j) = ELEM_VECANT;
			}
			last = gray;

		}
	}
	Invalidate();
}


void C自定义迷宫寻路View::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目
	for (int i = 0; i< DropCount; i++)
	{
		TCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名
		LoadImgFileAsMap(wcStr);
	}
	DragFinish(hDropInfo);  //拖放结束后,释放内存

	CView::OnDropFiles(hDropInfo);
}


void C自定义迷宫寻路View::OnFileSaveimg()
{
	// TODO:  在此添加命令处理程序代码
	TCHAR fileName[256] = {TEXT(".\\")};
	bool input = InputBox(&fileName[2], 256, TEXT("请输入文件名,请带上后缀，这会是你的图片格式"), TEXT("保存图片"));
	if (input)
	{
		int wid = autoRouter.getWidth();
		int hei = autoRouter.getHeight();
		IMAGE img(wid, hei);
		HDC hdc = GetImageHDC(&img);
		for (int i = 0; i < hei; i++)
		{
			for (int j = 0; j < wid; j++)
			{
				bool isWall = autoRouter.At(i, j) == ELEM_WALL;
				if (isWall)
					SetPixelV(hdc, j, i,(COLORREF) 0x000000);
				else
					SetPixelV(hdc, j, i, (COLORREF)0xffffff);
			}
		}
		SetPixelV(hdc, autoRouter.getStartX(), autoRouter.getStartY(), (COLORREF)0x0000ff);
		SetPixelV(hdc, autoRouter.getEndX(),autoRouter.getEndY(), (COLORREF)0x00ff00);
		saveimage(fileName, &img);
	}
}


void C自定义迷宫寻路View::OnEditBlock()
{
	// TODO:  在此添加命令处理程序代码
	editType = ET_Block;
}


void C自定义迷宫寻路View::OnFileGrayhalf()
{
	// TODO:  在此添加命令处理程序代码
	isDirectGrayPic = true;
}


void C自定义迷宫寻路View::OnFileBorderload()
{
	// TODO:  在此添加命令处理程序代码
	isDirectGrayPic = false;
}
