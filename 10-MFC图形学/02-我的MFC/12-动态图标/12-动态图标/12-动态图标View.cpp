
// 12-��̬ͼ��View.cpp : CMy12��̬ͼ��View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "12-��̬ͼ��.h"
#endif

#include "12-��̬ͼ��Doc.h"
#include "12-��̬ͼ��View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy12��̬ͼ��View

IMPLEMENT_DYNCREATE(CMy12��̬ͼ��View, CView)

BEGIN_MESSAGE_MAP(CMy12��̬ͼ��View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy12��̬ͼ��View ����/����

CMy12��̬ͼ��View::CMy12��̬ͼ��View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMy12��̬ͼ��View::~CMy12��̬ͼ��View()
{
}

BOOL CMy12��̬ͼ��View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy12��̬ͼ��View ����

void CMy12��̬ͼ��View::OnDraw(CDC* /*pDC*/)
{
	CMy12��̬ͼ��Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy12��̬ͼ��View ��ӡ

BOOL CMy12��̬ͼ��View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy12��̬ͼ��View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy12��̬ͼ��View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy12��̬ͼ��View ���

#ifdef _DEBUG
void CMy12��̬ͼ��View::AssertValid() const
{
	CView::AssertValid();
}

void CMy12��̬ͼ��View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy12��̬ͼ��Doc* CMy12��̬ͼ��View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12��̬ͼ��Doc)));
	return (CMy12��̬ͼ��Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy12��̬ͼ��View ��Ϣ�������
