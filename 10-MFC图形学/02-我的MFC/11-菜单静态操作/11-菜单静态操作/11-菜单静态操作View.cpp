
// 11-�˵���̬����View.cpp : CMy11�˵���̬����View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "11-�˵���̬����.h"
#endif

#include "11-�˵���̬����Doc.h"
#include "11-�˵���̬����View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy11�˵���̬����View

IMPLEMENT_DYNCREATE(CMy11�˵���̬����View, CView)

BEGIN_MESSAGE_MAP(CMy11�˵���̬����View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy11�˵���̬����View ����/����

CMy11�˵���̬����View::CMy11�˵���̬����View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMy11�˵���̬����View::~CMy11�˵���̬����View()
{
}

BOOL CMy11�˵���̬����View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy11�˵���̬����View ����

void CMy11�˵���̬����View::OnDraw(CDC* /*pDC*/)
{
	CMy11�˵���̬����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy11�˵���̬����View ��ӡ

BOOL CMy11�˵���̬����View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy11�˵���̬����View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy11�˵���̬����View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy11�˵���̬����View ���

#ifdef _DEBUG
void CMy11�˵���̬����View::AssertValid() const
{
	CView::AssertValid();
}

void CMy11�˵���̬����View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy11�˵���̬����Doc* CMy11�˵���̬����View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy11�˵���̬����Doc)));
	return (CMy11�˵���̬����Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy11�˵���̬����View ��Ϣ�������
/*
Frame Create
*/
//����������
void CMy11�˵���̬����View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡ�˵���
	//CMenu * menu = GetMenu();//�˵����ڿ���࣬����ֱ�ӽ��м���
	//�����˵���
	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	//��ȡ�Ӳ˵�
	CMenu * sonmenu = menu.GetSubMenu(0);
	//CMenu::TrackPopupMenu,�Ӳ˵���Ϊ��ݲ˵�
	//�ͻ�������ת��Ļ����
	ClientToScreen(&point);
	sonmenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,this);
	CView::OnLButtonDown(nFlags, point);
}
