
// 10-�˵���Ӧ·��View.cpp : CMy10�˵���Ӧ·��View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "10-�˵���Ӧ·��.h"
#endif

#include "10-�˵���Ӧ·��Doc.h"
#include "10-�˵���Ӧ·��View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy10�˵���Ӧ·��View

IMPLEMENT_DYNCREATE(CMy10�˵���Ӧ·��View, CView)

BEGIN_MESSAGE_MAP(CMy10�˵���Ӧ·��View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	//ON_COMMAND(ID_TEST_DEMO, &CMy10�˵���Ӧ·��View::OnTestDemo)
END_MESSAGE_MAP()

// CMy10�˵���Ӧ·��View ����/����

CMy10�˵���Ӧ·��View::CMy10�˵���Ӧ·��View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMy10�˵���Ӧ·��View::~CMy10�˵���Ӧ·��View()
{
}

BOOL CMy10�˵���Ӧ·��View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy10�˵���Ӧ·��View ����

void CMy10�˵���Ӧ·��View::OnDraw(CDC* /*pDC*/)
{
	CMy10�˵���Ӧ·��Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy10�˵���Ӧ·��View ��ӡ

BOOL CMy10�˵���Ӧ·��View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy10�˵���Ӧ·��View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy10�˵���Ӧ·��View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy10�˵���Ӧ·��View ���

#ifdef _DEBUG
void CMy10�˵���Ӧ·��View::AssertValid() const
{
	CView::AssertValid();
}

void CMy10�˵���Ӧ·��View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy10�˵���Ӧ·��Doc* CMy10�˵���Ӧ·��View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy10�˵���Ӧ·��Doc)));
	return (CMy10�˵���Ӧ·��Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy10�˵���Ӧ·��View ��Ϣ�������
/*
�˵�������Ϣ·�ɵ���Ϣ����˳���д���ͽ��н������ݣ�
Frame->View->Doc->View->Frame->App
*/
/*
��Ϣ����;
������Ϣ��WM_COMMAND:�˵�������ʹ��
��׼��Ϣ��WM_LBUTTONDOWN:��ͨ��Ϣ��
ͨ����Ϣ����ť�����Ϣ�ȣ��ص�����
CWnd���Խ����κ���Ϣ
CCmdTarget���ܽ��ܱ�׼��Ϣ
*/

//void CMy10�˵���Ӧ·��View::OnTestDemo()
//{
//	// TODO:  �ڴ���������������
//	MessageBox(TEXT("View"));
//}
