
// 07-�����ʹ��View.cpp : CMy07�����ʹ��View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "07-�����ʹ��.h"
#endif

#include "07-�����ʹ��Doc.h"
#include "07-�����ʹ��View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy07�����ʹ��View

IMPLEMENT_DYNCREATE(CMy07�����ʹ��View, CView)

BEGIN_MESSAGE_MAP(CMy07�����ʹ��View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy07�����ʹ��View ����/����

CMy07�����ʹ��View::CMy07�����ʹ��View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMy07�����ʹ��View::~CMy07�����ʹ��View()
{
}

BOOL CMy07�����ʹ��View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy07�����ʹ��View ����

void CMy07�����ʹ��View::OnDraw(CDC* pDC)
{
	CMy07�����ʹ��Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CFont font;
	font.CreatePointFont(1000,TEXT("����"));
	pDC->SelectObject(&font);
	pDC->TextOutW(100,100,TEXT("Hello Font"));
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy07�����ʹ��View ��ӡ

BOOL CMy07�����ʹ��View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy07�����ʹ��View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy07�����ʹ��View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy07�����ʹ��View ���

#ifdef _DEBUG
void CMy07�����ʹ��View::AssertValid() const
{
	CView::AssertValid();
}

void CMy07�����ʹ��View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy07�����ʹ��Doc* CMy07�����ʹ��View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy07�����ʹ��Doc)));
	return (CMy07�����ʹ��Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy07�����ʹ��View ��Ϣ�������
