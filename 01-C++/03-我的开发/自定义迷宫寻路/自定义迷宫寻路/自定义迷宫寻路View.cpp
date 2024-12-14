
// �Զ����Թ�Ѱ·View.cpp : C�Զ����Թ�Ѱ·View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "�Զ����Թ�Ѱ·.h"
#endif

#include "�Զ����Թ�Ѱ·Doc.h"
#include "�Զ����Թ�Ѱ·View.h"

#include<graphics.h>
#include"MFCBatchDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C�Զ����Թ�Ѱ·View

IMPLEMENT_DYNCREATE(C�Զ����Թ�Ѱ·View, CView)

BEGIN_MESSAGE_MAP(C�Զ����Թ�Ѱ·View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_MAP, &C�Զ����Թ�Ѱ·View::OnEditMap)
	ON_COMMAND(ID_EDIT_POINT, &C�Զ����Թ�Ѱ·View::OnEditPoint)
	ON_COMMAND(ID_EDIT_START, &C�Զ����Թ�Ѱ·View::OnEditStart)
	ON_COMMAND(ID_CLEAN, &C�Զ����Թ�Ѱ·View::OnClean)
	ON_WM_TIMER()
	ON_COMMAND(ID_SIZE_20X20, &C�Զ����Թ�Ѱ·View::OnSize20x20)
	ON_COMMAND(ID_SIZE_50X50, &C�Զ����Թ�Ѱ·View::OnSize50x50)
	ON_COMMAND(ID_SIZE_80X80, &C�Զ����Թ�Ѱ·View::OnSize80x80)
	ON_COMMAND(ID_SIZE_100X100, &C�Զ����Թ�Ѱ·View::OnSize100x100)
	ON_COMMAND(ID_SIZE_200X200, &C�Զ����Թ�Ѱ·View::OnSize200x200)
	ON_COMMAND(ID_SIZE_300X300, &C�Զ����Թ�Ѱ·View::OnSize300x300)
	ON_COMMAND(ID_ANIMA_OPEN, &C�Զ����Թ�Ѱ·View::OnAnimaOpen)
	ON_COMMAND(ID_ANIMA_CLOSE, &C�Զ����Թ�Ѱ·View::OnAnimaClose)
	ON_COMMAND(ID_HELP_VIEW, &C�Զ����Թ�Ѱ·View::OnHelpView)
	ON_COMMAND(ID_DIRECT_4, &C�Զ����Թ�Ѱ·View::OnDirect4)
	ON_COMMAND(ID_DIRECT_8, &C�Զ����Թ�Ѱ·View::OnDirect8)
	ON_COMMAND(ID_EDIT_RANDOMMAP, &C�Զ����Թ�Ѱ·View::OnEditRandommap)
	ON_COMMAND(ID_SLEEP_16, &C�Զ����Թ�Ѱ·View::OnSleep16)
	ON_COMMAND(ID_SLEEP_22, &C�Զ����Թ�Ѱ·View::OnSleep22)
	ON_COMMAND(ID_SLEEP_33, &C�Զ����Թ�Ѱ·View::OnSleep33)
	ON_COMMAND(ID_SLEEP_41, &C�Զ����Թ�Ѱ·View::OnSleep41)
	ON_COMMAND(ID_SLEEP_83, &C�Զ����Թ�Ѱ·View::OnSleep83)
	ON_COMMAND(ID_SLEEP_8, &C�Զ����Թ�Ѱ·View::OnSleep8)
	ON_COMMAND(ID_STEP_ROUND, &C�Զ����Թ�Ѱ·View::OnStepRound)
	ON_COMMAND(ID_STEP_STEP, &C�Զ����Թ�Ѱ·View::OnStepStep)
	ON_COMMAND(ID_SLEEP_333, &C�Զ����Թ�Ѱ·View::OnSleep333)
	ON_COMMAND(ID_SLEEP_1000, &C�Զ����Թ�Ѱ·View::OnSleep1000)
	ON_COMMAND(ID_SHOW_ALLANI, &C�Զ����Թ�Ѱ·View::OnShowAllani)
	ON_COMMAND(ID_SHOW_BORDERANI, &C�Զ����Թ�Ѱ·View::OnShowBorderani)
	ON_COMMAND(ID_FILE_LOADIMG, &C�Զ����Թ�Ѱ·View::OnFileLoadimg)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_FILE_SAVEIMG, &C�Զ����Թ�Ѱ·View::OnFileSaveimg)
	ON_COMMAND(ID_EDIT_BLOCK, &C�Զ����Թ�Ѱ·View::OnEditBlock)
	ON_COMMAND(ID_FILE_GRAYHALF, &C�Զ����Թ�Ѱ·View::OnFileGrayhalf)
	ON_COMMAND(ID_FILE_BORDERLOAD, &C�Զ����Թ�Ѱ·View::OnFileBorderload)
END_MESSAGE_MAP()

// C�Զ����Թ�Ѱ·View ����/����

C�Զ����Թ�Ѱ·View::C�Զ����Թ�Ѱ·View()
: isLbtnDown(false)
, isRbtnDown(false)
, downPoint(0)
, isDirectGrayPic(false)
{
	// TODO:  �ڴ˴���ӹ������
	editType = ET_Map;
	isRouting = false;
	isOpenAnimate = true;
	TIMER_SLEEP = 33;
	isDrawAllRoute = false;
}

C�Զ����Թ�Ѱ·View::~C�Զ����Թ�Ѱ·View()
{
}

BOOL C�Զ����Թ�Ѱ·View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// C�Զ����Թ�Ѱ·View ����

void C�Զ����Թ�Ѱ·View::OnDraw(CDC* pDC)
{
	C�Զ����Թ�Ѱ·Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	this->DragAcceptFiles(TRUE);

	static COLORREF bkcolor = 0xffffff;
	MFCBatchDraw draw(pDC);

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
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
								if ((i+j)%2==0) //����ƴͼ���ƣ�����һ�������
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


// C�Զ����Թ�Ѱ·View ��ӡ

BOOL C�Զ����Թ�Ѱ·View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C�Զ����Թ�Ѱ·View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C�Զ����Թ�Ѱ·View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// C�Զ����Թ�Ѱ·View ���

#ifdef _DEBUG
void C�Զ����Թ�Ѱ·View::AssertValid() const
{
	CView::AssertValid();
}

void C�Զ����Թ�Ѱ·View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C�Զ����Թ�Ѱ·Doc* C�Զ����Թ�Ѱ·View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C�Զ����Թ�Ѱ·Doc)));
	return (C�Զ����Թ�Ѱ·Doc*)m_pDocument;
}
#endif //_DEBUG


// C�Զ����Թ�Ѱ·View ��Ϣ�������


void C�Զ����Թ�Ѱ·View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


void C�Զ����Թ�Ѱ·View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

void C�Զ����Թ�Ѱ·View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


void C�Զ����Թ�Ѱ·View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

void C�Զ����Թ�Ѱ·View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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




void C�Զ����Թ�Ѱ·View::OnEditMap()
{
	editType = ET_Map;
}


void C�Զ����Թ�Ѱ·View::OnEditPoint()
{
	editType = ET_Point;
}

#define TIMER_SHOW_ROUTE_ANIMATE 0x101
void C�Զ����Թ�Ѱ·View::OnEditStart()
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


void C�Զ����Թ�Ѱ·View::OnClean()
{
	autoRouter.clean();
	Invalidate();
}


void C�Զ����Թ�Ѱ·View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


void C�Զ����Թ�Ѱ·View::OnSize20x20()
{
	// TODO:  �ڴ���������������
	autoRouter.setSize(20, 20);
	Invalidate();
}


void C�Զ����Թ�Ѱ·View::OnSize50x50()
{
	// TODO:  �ڴ���������������
	autoRouter.setSize(50, 50);
	Invalidate();
}


void C�Զ����Թ�Ѱ·View::OnSize80x80()
{
	// TODO:  �ڴ���������������
	autoRouter.setSize(80, 80);
	Invalidate();
}


void C�Զ����Թ�Ѱ·View::OnSize100x100()
{
	// TODO:  �ڴ���������������
	autoRouter.setSize(100, 100);
	Invalidate();
}


void C�Զ����Թ�Ѱ·View::OnSize200x200()
{
	// TODO:  �ڴ���������������
	autoRouter.setSize(200, 200);
	Invalidate();
}


void C�Զ����Թ�Ѱ·View::OnSize300x300()
{
	// TODO:  �ڴ���������������
	autoRouter.setSize(300, 300);
	Invalidate();
}


void C�Զ����Թ�Ѱ·View::OnAnimaOpen()
{
	// TODO:  �ڴ���������������
	isOpenAnimate = true;
}


void C�Զ����Թ�Ѱ·View::OnAnimaClose()
{
	// TODO:  �ڴ���������������
	isOpenAnimate = false;
}


void C�Զ����Թ�Ѱ·View::OnHelpView()
{
	// TODO:  �ڴ���������������
	MessageBox(L"�༭���Σ�\n\
\t������������߰�ס�϶������ǽ��\n\
\t����Ҽ�������߰�ס�϶����Ƴ�ǽ��\n\
�༭��ֹ�㣺\n\
\t���������ó�����\n\
\t�Ҽ�������ý�����\n\
ʹ�ò���\n\
\t��ѡ�༭����\n\
\tһ��������ʼ�㣬�����Ǿ�·\n\
\t�����ʼ\n\
������\n\
\t������������ʾѰ·����\n\
\t�رն�����ֱ�Ӹ���Ѱ·���\n\
");
}


void C�Զ����Թ�Ѱ·View::OnDirect4()
{
	// TODO:  �ڴ���������������
	autoRouter.setRouteMode4Direct(true);
}


void C�Զ����Թ�Ѱ·View::OnDirect8()
{
	// TODO:  �ڴ���������������
	autoRouter.setRouteMode4Direct(false);
}


void C�Զ����Թ�Ѱ·View::OnEditRandommap()
{
	// TODO:  �ڴ���������������
	autoRouter.setRandomWall();
	Invalidate();
}


void C�Զ����Թ�Ѱ·View::OnSleep16()
{
	// TODO:  �ڴ���������������
	TIMER_SLEEP = 16;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C�Զ����Թ�Ѱ·View::OnSleep22()
{
	// TODO:  �ڴ���������������
	TIMER_SLEEP = 22;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C�Զ����Թ�Ѱ·View::OnSleep33()
{
	// TODO:  �ڴ���������������
	TIMER_SLEEP = 33;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C�Զ����Թ�Ѱ·View::OnSleep41()
{
	// TODO:  �ڴ���������������
	TIMER_SLEEP = 41;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C�Զ����Թ�Ѱ·View::OnSleep83()
{
	// TODO:  �ڴ���������������
	TIMER_SLEEP = 83;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}


void C�Զ����Թ�Ѱ·View::OnSleep8()
{
	// TODO:  �ڴ���������������
	TIMER_SLEEP = 8;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}
}

void C�Զ����Թ�Ѱ·View::OnSleep333()
{
	// TODO:  �ڴ���������������
	TIMER_SLEEP = 333;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}

}


void C�Զ����Թ�Ѱ·View::OnSleep1000()
{
	// TODO:  �ڴ���������������
	TIMER_SLEEP = 1000;
	if (isRouting)
	{
		KillTimer(TIMER_SHOW_ROUTE_ANIMATE);
		SetTimer(TIMER_SHOW_ROUTE_ANIMATE, TIMER_SLEEP, NULL);
	}

}


void C�Զ����Թ�Ѱ·View::OnStepRound()
{
	// TODO:  �ڴ���������������
	autoRouter.setRouteStepModeIsRoundCircle(true);
}


void C�Զ����Թ�Ѱ·View::OnStepStep()
{
	// TODO:  �ڴ���������������
	autoRouter.setRouteStepModeIsRoundCircle(false);
}




void C�Զ����Թ�Ѱ·View::OnShowAllani()
{
	// TODO:  �ڴ���������������
	isDrawAllRoute = true;
}


void C�Զ����Թ�Ѱ·View::OnShowBorderani()
{
	// TODO:  �ڴ���������������
	isDrawAllRoute = false;
}


void C�Զ����Թ�Ѱ·View::OnFileLoadimg()
{
	// TODO:  �ڴ���������������
	TCHAR fileName[256];
	bool input = InputBox(fileName, 256, TEXT("�������ļ�����һ��ͼƬ������"), TEXT("��ȡͼƬ"));
	if (input)
	{
		LoadImgFileAsMap(fileName);
	}
}


void C�Զ����Թ�Ѱ·View::LoadImgFileAsMap(TCHAR * fileName)
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


void C�Զ����Թ�Ѱ·View::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//ȡ�ñ��϶��ļ�����Ŀ
	for (int i = 0; i< DropCount; i++)
	{
		TCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���
		LoadImgFileAsMap(wcStr);
	}
	DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�

	CView::OnDropFiles(hDropInfo);
}


void C�Զ����Թ�Ѱ·View::OnFileSaveimg()
{
	// TODO:  �ڴ���������������
	TCHAR fileName[256] = {TEXT(".\\")};
	bool input = InputBox(&fileName[2], 256, TEXT("�������ļ���,����Ϻ�׺����������ͼƬ��ʽ"), TEXT("����ͼƬ"));
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


void C�Զ����Թ�Ѱ·View::OnEditBlock()
{
	// TODO:  �ڴ���������������
	editType = ET_Block;
}


void C�Զ����Թ�Ѱ·View::OnFileGrayhalf()
{
	// TODO:  �ڴ���������������
	isDirectGrayPic = true;
}


void C�Զ����Թ�Ѱ·View::OnFileBorderload()
{
	// TODO:  �ڴ���������������
	isDirectGrayPic = false;
}
