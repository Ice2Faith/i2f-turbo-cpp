
// 01-��ͼ����ģ��View.cpp : CMy01��ͼ����ģ��View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "01-��ͼ����ģ��.h"
#endif

#include "01-��ͼ����ģ��Doc.h"
#include "01-��ͼ����ģ��View.h"
#include<cmath>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy01��ͼ����ģ��View

IMPLEMENT_DYNCREATE(CMy01��ͼ����ģ��View, CView)

BEGIN_MESSAGE_MAP(CMy01��ͼ����ģ��View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy01��ͼ����ģ��View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32771, &CMy01��ͼ����ģ��View::OnSelectPoint)
	ON_COMMAND(ID_32772, &CMy01��ͼ����ģ��View::OnSelectRecttangle)
	ON_COMMAND(ID_32773, &CMy01��ͼ����ģ��View::OnSelectElispe)
	ON_COMMAND(ID_32774, &CMy01��ͼ����ģ��View::OnSelectCircleLine)
	ON_COMMAND(ID_32775, &CMy01��ͼ����ģ��View::OnSelectLine)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32776, &CMy01��ͼ����ģ��View::OnSelectClearLine)
	ON_COMMAND(ID_32777, &CMy01��ͼ����ģ��View::OnSelectPolygon)
	ON_COMMAND(ID_32778, &CMy01��ͼ����ģ��View::OnSelectRadiate)
	ON_COMMAND(ID_32779, &CMy01��ͼ����ģ��View::OnSelectHu)
	ON_COMMAND(ID_32780, &CMy01��ͼ����ģ��View::OnSelectClear)
	ON_COMMAND(ID_32781, &CMy01��ͼ����ģ��View::OnSelectRoundRect)
	ON_COMMAND(ID_32782, &CMy01��ͼ����ģ��View::OnSelectBrush)
	ON_COMMAND(ID_32783, &CMy01��ͼ����ģ��View::OnSelectBigPoint)
	ON_COMMAND(ID_32784, &CMy01��ͼ����ģ��View::OnSelectStar)
END_MESSAGE_MAP()

// CMy01��ͼ����ģ��View ����/����

CMy01��ͼ����ģ��View::CMy01��ͼ����ģ��View()
	: m_Point(0)
	, isLDown(false)
	, canDraw(false)
	, drawType(0)
	, pslen(0)
	, m_hulen(0)
{
	// TODO: �ڴ˴���ӹ������

}

CMy01��ͼ����ģ��View::~CMy01��ͼ����ģ��View()
{
}

BOOL CMy01��ͼ����ģ��View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy01��ͼ����ģ��View ����

void CMy01��ͼ����ģ��View::OnDraw(CDC* /*pDC*/)
{
	CMy01��ͼ����ģ��Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy01��ͼ����ģ��View ��ӡ


void CMy01��ͼ����ģ��View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy01��ͼ����ģ��View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy01��ͼ����ģ��View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy01��ͼ����ģ��View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMy01��ͼ����ģ��View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy01��ͼ����ģ��View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy01��ͼ����ģ��View ���

#ifdef _DEBUG
void CMy01��ͼ����ģ��View::AssertValid() const
{
	CView::AssertValid();
}

void CMy01��ͼ����ģ��View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy01��ͼ����ģ��Doc* CMy01��ͼ����ģ��View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy01��ͼ����ģ��Doc)));
	return (CMy01��ͼ����ģ��Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy01��ͼ����ģ��View ��Ϣ�������


void CMy01��ͼ����ģ��View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->canDraw=true;
	this->m_Point=point;
	this->isLDown=true;
	CClientDC dc(this);
	if (this->drawType != 7)
		this->pslen = 0;
	switch(this->drawType)
	{
	case 1:
		dc.SetPixel(point,RGB(255,0,0));
		break;
	case 21:
	{
			   CBrush brush(RGB(0, 0, 0));
			   dc.SelectObject(&brush);
			   dc.Ellipse(point.x-3,point.y-3,point.x+3,point.y+3);
	}
		break;
	case 22:
	{
			   dc.MoveTo(point.x-5,point.y);
			   dc.LineTo(point.x + 5,point.y);
			   dc.MoveTo(point.x, point.y - 5);
			   dc.LineTo(point.x, point.y + 5);
	}
		break;
	case 7:
	{
			  if (this->pslen < 299)
			  {
				  this->m_points[this->pslen++] = point;
				  dc.Polygon(this->m_points,this->pslen);
			  }
			  
			  break;
	}
	case 9:
	{
			  if (this->m_hulen < 3)
			  {
				  this->m_cirhu[this->m_hulen++] = point;
			  }
			  if (this->m_hulen==3)
			  {
				  int r = (int)sqrt(pow(this->m_cirhu[1].x*1.0 - this->m_cirhu[0].x, 2.0) + pow(this->m_cirhu[1].y*1.0 - this->m_cirhu[0].y, 2.0));
				  dc.Arc(this->m_cirhu[0].x - r, this->m_cirhu[0].y - r, this->m_cirhu[0].x + r, this->m_cirhu[0].y+r,
					  this->m_cirhu[1].x, this->m_cirhu[1].y, this->m_cirhu[2].x, this->m_cirhu[2].y);
				  this->m_hulen = 0;
			  }
			  break;
	}
	default:
		break;
	}
	
	CView::OnLButtonDown(nFlags, point);
}


void CMy01��ͼ����ģ��View::OnSelectPoint()
{
	// TODO: �ڴ���������������
	this->drawType=1;
}


void CMy01��ͼ����ģ��View::OnSelectRecttangle()
{
	// TODO: �ڴ���������������
	this->drawType=2;
}


void CMy01��ͼ����ģ��View::OnSelectElispe()
{
	// TODO: �ڴ���������������
	this->drawType=3;
}


void CMy01��ͼ����ģ��View::OnSelectCircleLine()
{
	// TODO: �ڴ���������������
	this->drawType=4;
}


void CMy01��ͼ����ģ��View::OnSelectLine()
{
	// TODO: �ڴ���������������
	this->drawType=5;
}


void CMy01��ͼ����ģ��View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	switch(this->drawType)
	{
	case 1:
		//dc.SetPixel(point,RGB(255,0,0));
		break;
	case 2:
		if(isLDown)
			dc.Rectangle(this->m_Point.x,this->m_Point.y,point.x,point.y);
		break;
	case 3:
		if(isLDown)
			dc.Ellipse(this->m_Point.x,this->m_Point.y,point.x,point.y);
		break;
	case 5:
		if(isLDown)
		{
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
		}
		break;
	case 10:
	{
			   if (isLDown)
			   {
				   int rh = point.x - this->m_Point.x;
				   int rw = point.y - this->m_Point.y;
				   if (rh < 0)
					   rh = 0 - rh;
				   if (rw < 0)
					   rw = 0 - rw;
				   int r = rh < rw ? rh : rw;
				   r = r / 10;
				   if (r < 5)
					   r = 5;
				   dc.RoundRect(this->m_Point.x, this->m_Point.y, point.x, point.y, r, r);
			   }
				   
			   break;
	}
	default:
		break;
	}
	isLDown=false;
	CView::OnLButtonUp(nFlags, point);
}


void CMy01��ͼ����ģ��View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	if (drawType == 4)
	{
		if (isLDown)
		{
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
			this->m_Point = point;
		}
	}
	else if (drawType == 6)
	{
		if (isLDown)
		{
			CPen cPen;//��������
			cPen.CreatePen(PS_SOLID, 20, dc.GetBkColor());
			dc.SelectObject(&cPen);
			CBrush brush;
			brush.CreateSolidBrush(dc.GetBkColor());
			dc.SelectObject(&brush);
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
			this->m_Point = point;
		}
	}
	else if (drawType == 8)
	{
		if (isLDown)
		{
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
		}
	}
	else if (drawType == 11)
	{
		if (isLDown)
		{
			CPen cPen;//��������
			cPen.CreatePen(PS_SOLID, 20, RGB(0,0,0));
			dc.SelectObject(&cPen);
			CBrush brush;
			brush.CreateSolidBrush(dc.GetBkColor());
			dc.SelectObject(&brush);
			dc.MoveTo(this->m_Point);
			dc.LineTo(point);
			this->m_Point = point;
		}
	}
	
	CView::OnMouseMove(nFlags, point);
}


void CMy01��ͼ����ģ��View::OnSelectClearLine()
{
	// TODO:  �ڴ���������������
	this->drawType = 6;
}


void CMy01��ͼ����ģ��View::OnSelectPolygon()
{
	// TODO:  �ڴ���������������
	this->drawType = 7;
}


void CMy01��ͼ����ģ��View::OnSelectRadiate()
{
	// TODO:  �ڴ���������������
	this->drawType = 8;
}


void CMy01��ͼ����ģ��View::OnSelectHu()
{
	// TODO:  �ڴ���������������
	this->drawType = 9;
}


void CMy01��ͼ����ģ��View::OnSelectClear()
{
	// TODO:  �ڴ���������������
	CClientDC dc(this);
	CRect rect;
	GetWindowRect(&rect);
	dc.Rectangle(-2,-2,rect.right-rect.left+2,rect.bottom-rect.top+2);
	this->pslen = 0;
}


void CMy01��ͼ����ģ��View::OnSelectRoundRect()
{
	// TODO:  �ڴ���������������
	this->drawType = 10;
}


void CMy01��ͼ����ģ��View::OnSelectBrush()
{
	// TODO:  �ڴ���������������
	this->drawType = 11;
}


void CMy01��ͼ����ģ��View::OnSelectBigPoint()
{
	// TODO:  �ڴ���������������
	this->drawType = 21;
}


void CMy01��ͼ����ģ��View::OnSelectStar()
{
	// TODO:  �ڴ���������������
	this->drawType = 22;
}
