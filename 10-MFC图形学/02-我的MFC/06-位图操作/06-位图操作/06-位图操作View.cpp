
// 06-λͼ����View.cpp : CMy06λͼ����View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "06-λͼ����.h"
#endif

#include "06-λͼ����Doc.h"
#include "06-λͼ����View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy06λͼ����View

IMPLEMENT_DYNCREATE(CMy06λͼ����View, CView)

BEGIN_MESSAGE_MAP(CMy06λͼ����View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy06λͼ����View ����/����

CMy06λͼ����View::CMy06λͼ����View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMy06λͼ����View::~CMy06λͼ����View()
{
}

BOOL CMy06λͼ����View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy06λͼ����View ����

void CMy06λͼ����View::OnDraw(CDC* pDC)
{
	CMy06λͼ����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CBrush brush(RGB(255, 0, 0));
	pDC->SelectObject(&brush);
	pDC->Ellipse(120, 120, 240, 240);
	//����λͼ
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	//��λͼ������ˢ
	CBrush brush2(&bitmap);
	pDC->SelectObject(&brush2);
	pDC->Ellipse(240, 240, 480, 480);
	
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy06λͼ����View ��ӡ

BOOL CMy06λͼ����View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy06λͼ����View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy06λͼ����View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy06λͼ����View ���

#ifdef _DEBUG
void CMy06λͼ����View::AssertValid() const
{
	CView::AssertValid();
}

void CMy06λͼ����View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy06λͼ����Doc* CMy06λͼ����View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy06λͼ����Doc)));
	return (CMy06λͼ����Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy06λͼ����View ��Ϣ�������
