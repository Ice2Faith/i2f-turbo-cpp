
// 05-Bezier���߻���View.cpp : CMy05Bezier���߻���View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "05-Bezier���߻���.h"
#endif

#include "05-Bezier���߻���Doc.h"
#include "05-Bezier���߻���View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double CMy05Bezier���߻���View::Bernstein(int i, int n, double t)
{
	double son = 1, mon = 1, ti = 1, tin = 1;
	for (int j = 0; j<n; j++)
	{
		if (j<i)
		{
			son *= n - j;
			mon *= j + 1;
			ti *= t;
		}
		else
		{
			tin *= (1 - t);
		}

	}
	return (son / mon)*ti*tin;
}
double CMy05Bezier���߻���View::BezierX(int n, double t, CPoint points[])
{
	double sum = 0;
	for (int i = 0; i<n-1; i++)
	{
		sum += points[i].x*Bernstein(i, n-1, t);
	}
	return sum;
}
double CMy05Bezier���߻���View::BezierY(int n, double t, CPoint points[])
{
	double sum = 0;
	for (int i = 0; i<n-1; i++)
	{
		sum += points[i].y*Bernstein(i, n-1, t);
	}
	return sum;
}
void CMy05Bezier���߻���View::DrawBezierLine()
{
	int tCount = 20000;
	CClientDC dc(this);
	FILE * fp = fopen("log.txt","w");
	dc.Polyline(m_points,m_pointCount);
	for (int i = 0; i < tCount*0.8; i++)
	{
		int x = (int)BezierX(this->m_pointCount,1.0*i/tCount,this->m_points);
		int y = (int)BezierY(this->m_pointCount, 1.0*i / tCount, this->m_points);
		dc.SetPixelV(x,y,0x0000ff);
		fprintf(fp, "%d %d\n", x, y);
	}
	fclose(fp);
}
void CMy05Bezier���߻���View::ShowCtrlPoint()
{
	CClientDC dc(this);
	for (int i = 0; i < this->m_pointCount; i++)
	{
		dc.Ellipse(this->m_points[i].x - 3, this->m_points[i].y - 3, this->m_points[i].x + 3, this->m_points[i].y + 3);
	}
}
// CMy05Bezier���߻���View ����/����

CMy05Bezier���߻���View::CMy05Bezier���߻���View()
: m_pointCount(0)
, m_state(1)
, m_isLDown(false)
, m_moveIndex(0)
{
	// TODO:  �ڴ˴���ӹ������

}

CMy05Bezier���߻���View::~CMy05Bezier���߻���View()
{
}
// CMy05Bezier���߻���View ����

void CMy05Bezier���߻���View::OnDraw(CDC* pDC)
{
	CMy05Bezier���߻���Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	DrawBezierLine();
	if (m_state == 2)
		ShowCtrlPoint();
}
// CMy05Bezier���߻���View ��Ϣ�������


void CMy05Bezier���߻���View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isLDown = true;
	if (m_state == 1)
	{
		this->m_points[this->m_pointCount++] = point;
		Invalidate();
	}
	if (m_state == 2)
	{
		m_moveIndex = -1;
		for (int i = 0; i <m_pointCount; i++)
		{
			if (sqrt(pow(point.x - m_points[i].x, 2.0) + pow(point.y - m_points[i].y, 2.0)) < 3)
			{
				m_moveIndex = i;
				break;
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy05Bezier���߻���View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (m_state == 1)
	{
		this->m_pointCount = 0;
		Invalidate();
	}
	CView::OnRButtonDown(nFlags, point);
}


void CMy05Bezier���߻���View::OnBezierBeginDraw()
{
	// TODO:  �ڴ���������������
	m_state = 1;
	Invalidate();
}


void CMy05Bezier���߻���View::OnBezierEditPoint()
{
	// TODO:  �ڴ���������������
	m_state = 2;
	Invalidate();
}


void CMy05Bezier���߻���View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_isLDown)
	{
		if (m_moveIndex != -1)
		{
			m_points[m_moveIndex] = point;
			Invalidate();
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CMy05Bezier���߻���View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isLDown = false;
	CView::OnLButtonUp(nFlags, point);
}
// CMy05Bezier���߻���View

IMPLEMENT_DYNCREATE(CMy05Bezier���߻���View, CView)

BEGIN_MESSAGE_MAP(CMy05Bezier���߻���View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_BEZIER32771, &CMy05Bezier���߻���View::OnBezierBeginDraw)
	ON_COMMAND(ID_BEZIER32772, &CMy05Bezier���߻���View::OnBezierEditPoint)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


BOOL CMy05Bezier���߻���View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}


// CMy05Bezier���߻���View ��ӡ

BOOL CMy05Bezier���߻���View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy05Bezier���߻���View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy05Bezier���߻���View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy05Bezier���߻���View ���

#ifdef _DEBUG
void CMy05Bezier���߻���View::AssertValid() const
{
	CView::AssertValid();
}

void CMy05Bezier���߻���View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy05Bezier���߻���Doc* CMy05Bezier���߻���View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy05Bezier���߻���Doc)));
	return (CMy05Bezier���߻���Doc*)m_pDocument;
}
#endif //_DEBUG



