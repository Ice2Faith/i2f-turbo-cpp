
// 14-�Ի�������View.cpp : CMy14�Ի�������View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "14-�Ի�������.h"
#endif

#include "14-�Ի�������Doc.h"
#include "14-�Ի�������View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy14�Ի�������View

IMPLEMENT_DYNCREATE(CMy14�Ի�������View, CView)

BEGIN_MESSAGE_MAP(CMy14�Ի�������View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy14�Ի�������View ����/����

CMy14�Ի�������View::CMy14�Ի�������View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMy14�Ի�������View::~CMy14�Ի�������View()
{
}

BOOL CMy14�Ի�������View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy14�Ի�������View ����

void CMy14�Ի�������View::OnDraw(CDC* /*pDC*/)
{
	CMy14�Ի�������Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy14�Ի�������View ��ӡ

BOOL CMy14�Ի�������View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy14�Ի�������View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy14�Ի�������View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy14�Ի�������View ���

#ifdef _DEBUG
void CMy14�Ի�������View::AssertValid() const
{
	CView::AssertValid();
}

void CMy14�Ի�������View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy14�Ի�������Doc* CMy14�Ի�������View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy14�Ի�������Doc)));
	return (CMy14�Ի�������Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy14�Ի�������View ��Ϣ�������
