
// 04-�¼���ҵView.cpp : CMy04�¼���ҵView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "04-�¼���ҵ.h"
#endif

#include "04-�¼���ҵDoc.h"
#include "04-�¼���ҵView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy04�¼���ҵView

IMPLEMENT_DYNCREATE(CMy04�¼���ҵView, CView)

BEGIN_MESSAGE_MAP(CMy04�¼���ҵView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CMy04�¼���ҵView ����/����

CMy04�¼���ҵView::CMy04�¼���ҵView()
{
	// TODO:  �ڴ˴���ӹ������

}

CMy04�¼���ҵView::~CMy04�¼���ҵView()
{
}

BOOL CMy04�¼���ҵView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy04�¼���ҵView ����

void CMy04�¼���ҵView::OnDraw(CDC* /*pDC*/)
{
	CMy04�¼���ҵDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy04�¼���ҵView ��ӡ

BOOL CMy04�¼���ҵView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy04�¼���ҵView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy04�¼���ҵView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy04�¼���ҵView ���

#ifdef _DEBUG
void CMy04�¼���ҵView::AssertValid() const
{
	CView::AssertValid();
}

void CMy04�¼���ҵView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy04�¼���ҵDoc* CMy04�¼���ҵView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy04�¼���ҵDoc)));
	return (CMy04�¼���ҵDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy04�¼���ҵView ��Ϣ�������

/*
��Ӧ��Ϣ���
*/
void CMy04�¼���ҵView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	str.Format(TEXT("x=%d,y=%d"),point.x,point.y);
	MessageBox(str);
	CView::OnLButtonDown(nFlags, point);
}

/*
��Ӧ��Ϣ����
*/
void CMy04�¼���ҵView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	str.Format(TEXT("%d"), nChar);
	MessageBox(str);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

/*
��Ӧ��Ϣ��Ч����
*/
void CMy04�¼���ҵView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TCHAR ch = (TCHAR)nChar;
	CString str;
	str.Format(TEXT("%c"),ch);
	MessageBox(str);
	CView::OnChar(nChar, nRepCnt, nFlags);
}
