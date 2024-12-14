
// 02_StartMFCView.cpp : CMy02_StartMFCView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "02_StartMFC.h"
#endif

#include "02_StartMFCDoc.h"
#include "02_StartMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02_StartMFCView

IMPLEMENT_DYNCREATE(CMy02_StartMFCView, CView)

BEGIN_MESSAGE_MAP(CMy02_StartMFCView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy02_StartMFCView ����/����

CMy02_StartMFCView::CMy02_StartMFCView()
{
	// TODO:  �ڴ˴���ӹ������

}

CMy02_StartMFCView::~CMy02_StartMFCView()
{
}

BOOL CMy02_StartMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy02_StartMFCView ����

void CMy02_StartMFCView::OnDraw(CDC* pDC)
{
	CMy02_StartMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	pDC->TextOutW(0,0,L"Hello");
}


// CMy02_StartMFCView ��ӡ

BOOL CMy02_StartMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy02_StartMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy02_StartMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy02_StartMFCView ���

#ifdef _DEBUG
void CMy02_StartMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMy02_StartMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy02_StartMFCDoc* CMy02_StartMFCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy02_StartMFCDoc)));
	return (CMy02_StartMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy02_StartMFCView ��Ϣ�������


void CMy02_StartMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MessageBox(L"ViewLBD", L"Tips", MB_OK);
	CView::OnLButtonDown(nFlags, point);
}
