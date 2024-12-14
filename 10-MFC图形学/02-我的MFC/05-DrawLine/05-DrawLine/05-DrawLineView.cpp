
// 05-DrawLineView.cpp : CMy05DrawLineView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "05-DrawLine.h"
#endif

#include "05-DrawLineDoc.h"
#include "05-DrawLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy05DrawLineView

IMPLEMENT_DYNCREATE(CMy05DrawLineView, CView)

BEGIN_MESSAGE_MAP(CMy05DrawLineView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMy05DrawLineView ����/����

CMy05DrawLineView::CMy05DrawLineView()
: m_myPoint(0)
, m_isPress(false)
{
	// TODO:  �ڴ˴���ӹ������

}

CMy05DrawLineView::~CMy05DrawLineView()
{
}

BOOL CMy05DrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy05DrawLineView ����

void CMy05DrawLineView::OnDraw(CDC* /*pDC*/)
{
	CMy05DrawLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy05DrawLineView ��ӡ

BOOL CMy05DrawLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy05DrawLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy05DrawLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy05DrawLineView ���

#ifdef _DEBUG
void CMy05DrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CMy05DrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy05DrawLineDoc* CMy05DrawLineView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy05DrawLineDoc)));
	return (CMy05DrawLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy05DrawLineView ��Ϣ�������
/*������»�������*/
/*����,��¼���*/
void CMy05DrawLineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_myPoint = point;

	/**/
	m_isPress = true;
	CView::OnLButtonDown(nFlags, point);
}

/*���ߣ���¼�յ㣬��ʼ����--ֱ��*/
void CMy05DrawLineView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isPress = false;
	CView::OnLButtonUp(nFlags, point);
}


void CMy05DrawLineView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*�յ���Ϊ���ʹ�ã���������*/
	if (m_isPress == true)
	{
		CClientDC dc(this);
		dc.MoveTo(m_myPoint);
		dc.LineTo(point);
		m_myPoint = point;
	}
	CView::OnMouseMove(nFlags, point);
}

/*�Ҽ����»�ֱ��*/
void CMy05DrawLineView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_myPoint = point;
	CView::OnRButtonDown(nFlags, point);
}


void CMy05DrawLineView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	dc.MoveTo(m_myPoint);
	dc.LineTo(point);
	CView::OnRButtonUp(nFlags, point);
}
