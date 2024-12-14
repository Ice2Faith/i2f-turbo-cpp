
// 06-ͼ�εĹ�դɨ����ʾView.cpp : CMy06ͼ�εĹ�դɨ����ʾView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "06-ͼ�εĹ�դɨ����ʾ.h"
#endif

#include "06-ͼ�εĹ�դɨ����ʾDoc.h"
#include "06-ͼ�εĹ�դɨ����ʾView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include<deque>
#include<iterator>

// CMy06ͼ�εĹ�դɨ����ʾView ����/����

CMy06ͼ�εĹ�դɨ����ʾView::CMy06ͼ�εĹ�դɨ����ʾView()
: p0(0)
, p1(0)
, m_isAntiAlias(false)
{
	// TODO:  �ڴ˴���ӹ������
	m_lineColor = 0x0000ff;
	m_FillColor = 0x00ff00;
}

// CMy06ͼ�εĹ�դɨ����ʾView ��Ϣ�������

void CMy06ͼ�εĹ�դɨ����ʾView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	p0 = point;
	CView::OnLButtonDown(nFlags, point);
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	p1 = point;
	CClientDC dc(this);
	if (m_isAntiAlias)
		AntialiasLine(p0, p1, m_lineColor, dc.GetPixel(point));
	else
		DDALine(p0, p1, m_lineColor);
	CView::OnLButtonUp(nFlags, point);
}


// DDA��ֵ΢���㷨��ֱ��
void CMy06ͼ�εĹ�դɨ����ʾView::DDALine(CPoint p1, CPoint p2, COLORREF color)
{
	CClientDC dc(this);
	double dk = 1.0*(p2.y - p1.y) / (p2.x - p1.x);
	if (dk > 1.0 || dk<-1.0)
	{
		if (p1.y > p2.y)
		{
			CPoint t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.x - p1.x) / (p2.y - p1.y);
		while (y < p2.y)
		{
			dc.SetPixelV(x + 0.5, y, color);
			x += k;
			y += 1;
		}
	}
	else
	{
		if (p1.x > p2.x)
		{
			CPoint t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.y - p1.y) / (p2.x - p1.x);
		while (x < p2.x)
		{
			dc.SetPixelV(x, y + 0.5, color);
			y += k;
			x += 1;
		}
	}

}

// ������ֱ�߻���
void CMy06ͼ�εĹ�դɨ����ʾView::AntialiasLine(CPoint p1, CPoint p2, COLORREF fgc, COLORREF bgc)
{
	CClientDC dc(this);
	double dk = 1.0*(p2.y - p1.y) / (p2.x - p1.x);
	if (dk > 1.0 || dk<-1.0)
	{
		if (p1.y > p2.y)
		{
			CPoint t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.x - p1.x) / (p2.y - p1.y);
		while (y < p2.y)
		{
			double e = x - (int)(x);
			dc.SetPixelV(x + 0.5, y, RGB((fgc & 0xff)*e + (bgc & 0xff)*(1 - e), ((fgc >> 8) & 0xff)*e + ((bgc >> 8) & 0xff)*(1 - e), ((fgc >> 16) & 0xff)*e + ((bgc >> 16) & 0xff)*(1 - e)));
			dc.SetPixelV(x + 0.5 + 1, y, RGB((fgc & 0xff)*(1 - e) + (bgc & 0xff)*e, ((fgc >> 8) & 0xff)*(1 - e) + ((bgc >> 8) & 0xff)*e, ((fgc >> 16) & 0xff)*(1 - e) + ((bgc >> 16) & 0xff)*e));
			x += k;
			y += 1;
		}
	}
	else
	{
		if (p1.x > p2.x)
		{
			CPoint t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.y - p1.y) / (p2.x - p1.x);
		while (x < p2.x)
		{
			double e = y - (int)(y);
			dc.SetPixelV(x, y + 0.5, RGB((fgc & 0xff)*e + (bgc & 0xff)*(1 - e), ((fgc >> 8) & 0xff)*e + ((bgc >> 8) & 0xff)*(1 - e), ((fgc >> 16) & 0xff)*e + ((bgc >> 16) & 0xff)*(1 - e)));
			dc.SetPixelV(x, y + 0.5 + 1, RGB((fgc & 0xff)*(1 - e) + (bgc & 0xff)*e, ((fgc >> 8) & 0xff)*(1 - e) + ((bgc >> 8) & 0xff)*e, ((fgc >> 16) & 0xff)*(1 - e) + ((bgc >> 16) & 0xff)*e));
			y += k;
			x += 1;
		}
	}


}


void CMy06ͼ�εĹ�դɨ����ʾView::SeedFillPoly(CPoint seed, COLORREF bgc, COLORREF flc)
{
	CClientDC dc(this);
	std::deque<CPoint> que;
	que.push_back(seed);
	dc.SetPixelV(seed, flc);
	int directs[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
	int directSum = 4;
	while (que.size() != 0)
	{
		for (int i = 0; i < directSum; i++)
		{
			CPoint tp = que.at(0);
			tp.x += directs[i][0];
			tp.y += directs[i][1];
			if (dc.GetPixel(tp) == bgc)
			{
				que.push_back(tp);
				dc.SetPixelV(tp, flc);
			}
		}
		que.pop_front();
	}
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	SeedFillPoly(point, dc.GetPixel(point), m_FillColor);
	CView::OnRButtonDown(nFlags, point);
}



void CMy06ͼ�εĹ�դɨ����ʾView::OnPanelClean()
{
	// TODO:  �ڴ���������������
	Invalidate();
}

void CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineRed()
{
	// TODO:  �ڴ���������������
	m_lineColor = 0x0000ff;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineGreen()
{
	// TODO:  �ڴ���������������
	m_lineColor = 0x00ff00;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineBlue()
{
	// TODO:  �ڴ���������������
	m_lineColor = 0xff0000;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineBalck()
{
	// TODO:  �ڴ���������������
	m_lineColor = 0x000000;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillRed()
{
	// TODO:  �ڴ���������������
	m_FillColor = 0x0000ff;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillGreen()
{
	// TODO:  �ڴ���������������
	m_FillColor = 0x00ff00;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillBlue()
{
	// TODO:  �ڴ���������������
	m_FillColor = 0xff0000;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillBlack()
{
	// TODO:  �ڴ���������������
	m_FillColor = 0x000000;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineWhite()
{
	// TODO:  �ڴ���������������
	m_lineColor = 0xffffff;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillWhite()
{
	// TODO:  �ڴ���������������
	m_FillColor = 0xffffff;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnStlDda()
{
	// TODO:  �ڴ���������������
	m_isAntiAlias = false;
}


void CMy06ͼ�εĹ�դɨ����ʾView::OnStlAntialias()
{
	// TODO:  �ڴ���������������
	m_isAntiAlias = true;
}
// CMy06ͼ�εĹ�դɨ����ʾView

IMPLEMENT_DYNCREATE(CMy06ͼ�εĹ�դɨ����ʾView, CView)

BEGIN_MESSAGE_MAP(CMy06ͼ�εĹ�դɨ����ʾView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32771, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineRed)
	ON_COMMAND(ID_32772, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineGreen)
	ON_COMMAND(ID_32773, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineBlue)
	ON_COMMAND(ID_32777, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineBalck)
	ON_COMMAND(ID_32774, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillRed)
	ON_COMMAND(ID_32775, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillGreen)
	ON_COMMAND(ID_32776, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillBlue)
	ON_COMMAND(ID_32778, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillBlack)
	ON_COMMAND(ID_32779, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrLineWhite)
	ON_COMMAND(ID_32780, &CMy06ͼ�εĹ�դɨ����ʾView::OnClrFillWhite)
	ON_COMMAND(ID_32781, &CMy06ͼ�εĹ�դɨ����ʾView::OnStlDda)
	ON_COMMAND(ID_32782, &CMy06ͼ�εĹ�դɨ����ʾView::OnStlAntialias)
	ON_WM_RBUTTONDBLCLK()
	ON_COMMAND(ID_32783, &CMy06ͼ�εĹ�դɨ����ʾView::OnPanelClean)
END_MESSAGE_MAP()


CMy06ͼ�εĹ�դɨ����ʾView::~CMy06ͼ�εĹ�դɨ����ʾView()
{
}

BOOL CMy06ͼ�εĹ�դɨ����ʾView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy06ͼ�εĹ�դɨ����ʾView ����

void CMy06ͼ�εĹ�դɨ����ʾView::OnDraw(CDC* /*pDC*/)
{
	CMy06ͼ�εĹ�դɨ����ʾDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy06ͼ�εĹ�դɨ����ʾView ��ӡ

BOOL CMy06ͼ�εĹ�դɨ����ʾView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy06ͼ�εĹ�դɨ����ʾView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy06ͼ�εĹ�դɨ����ʾView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy06ͼ�εĹ�դɨ����ʾView ���

#ifdef _DEBUG
void CMy06ͼ�εĹ�դɨ����ʾView::AssertValid() const
{
	CView::AssertValid();
}

void CMy06ͼ�εĹ�դɨ����ʾView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy06ͼ�εĹ�դɨ����ʾDoc* CMy06ͼ�εĹ�դɨ����ʾView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy06ͼ�εĹ�դɨ����ʾDoc)));
	return (CMy06ͼ�εĹ�դɨ����ʾDoc*)m_pDocument;
}
#endif //_DEBUG





void CMy06ͼ�εĹ�դɨ����ʾView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CView::OnRButtonDblClk(nFlags, point);
}



