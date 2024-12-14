
// 08-���������ʹ��View.cpp : CMy08���������ʹ��View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "08-���������ʹ��.h"
#endif

#include "08-���������ʹ��Doc.h"
#include "08-���������ʹ��View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy08���������ʹ��View

IMPLEMENT_DYNCREATE(CMy08���������ʹ��View, CView)

BEGIN_MESSAGE_MAP(CMy08���������ʹ��View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CMy08���������ʹ��View ����/����

CMy08���������ʹ��View::CMy08���������ʹ��View()
: m_myPoint(0)
, m_string(_T(""))
{
	// TODO:  �ڴ˴���ӹ������

}

CMy08���������ʹ��View::~CMy08���������ʹ��View()
{
}

BOOL CMy08���������ʹ��View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy08���������ʹ��View ����

void CMy08���������ʹ��View::OnDraw(CDC* /*pDC*/)
{
	CMy08���������ʹ��Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy08���������ʹ��View ��ӡ

BOOL CMy08���������ʹ��View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy08���������ʹ��View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy08���������ʹ��View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy08���������ʹ��View ���

#ifdef _DEBUG
void CMy08���������ʹ��View::AssertValid() const
{
	CView::AssertValid();
}

void CMy08���������ʹ��View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy08���������ʹ��Doc* CMy08���������ʹ��View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy08���������ʹ��Doc)));
	return (CMy08���������ʹ��Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy08���������ʹ��View ��Ϣ�������

/*���ڴ������Զ�����*/
int CMy08���������ʹ��View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//�̳���CWnd
	//��ȡ������Ϣ
	CClientDC dc(this);
	TEXTMETRIC tm;//������Ϣ�ṹ��
	dc.GetTextMetrics(&tm);
	//���������
	CreateSolidCaret(tm.tmAveCharWidth/8,tm.tmHeight);//��������߶ȺͿ��
	//��ʾ�����
	ShowCaret();
	return 0;
}


void CMy08���������ʹ��View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCaretPos(point);//���ù��λ��
	m_myPoint = point;//��������
	m_string.Empty();//���ԭ�����ַ���
	CView::OnLButtonDown(nFlags, point);
}


void CMy08���������ʹ��View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ʵ������
	CClientDC dc(this);
	
	if (nChar == VK_RETURN)//����
	{
		TEXTMETRIC tm;//������Ϣ�ṹ��
		dc.GetTextMetrics(&tm);
		m_string.Empty();
		m_myPoint.y += tm.tmHeight;
		m_myPoint.x = 0;
		SetCaretPos(m_myPoint);
	}
	else if (nChar == VK_BACK)//�˸�
	{
		//��ȡ����ɫ
		COLORREF color= dc.GetBkColor();
		//����д����ɫ
		COLORREF oldcolor = dc.SetTextColor(color);
		//��д����
		dc.TextOutW(m_myPoint.x, m_myPoint.y, m_string);
		m_string = m_string.Left(m_string.GetLength()-1);
		//�ָ�ԭ������ɫ
		dc.SetTextColor(oldcolor);
		dc.TextOutW(m_myPoint.x, m_myPoint.y, m_string);
	}
	else
	{
		m_string += (TCHAR)nChar;
	}
	CSize size = dc.GetTextExtent(m_string);
	int x = m_myPoint.x + size.cx;
	int y = m_myPoint.y;//ʵ�ֹ�����
	SetCaretPos(CPoint(x, y));//m_myPoint��ֵ�˴����ܸ���
	dc.TextOutW(m_myPoint.x, m_myPoint.y, m_string);
	CView::OnChar(nChar, nRepCnt, nFlags);
}
