
// 09-��ʱ�����彥��View.cpp : CMy09��ʱ�����彥��View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "09-��ʱ�����彥��.h"
#endif

#include "09-��ʱ�����彥��Doc.h"
#include "09-��ʱ�����彥��View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy09��ʱ�����彥��View

IMPLEMENT_DYNCREATE(CMy09��ʱ�����彥��View, CView)

BEGIN_MESSAGE_MAP(CMy09��ʱ�����彥��View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMy09��ʱ�����彥��View ����/����

CMy09��ʱ�����彥��View::CMy09��ʱ�����彥��View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMy09��ʱ�����彥��View::~CMy09��ʱ�����彥��View()
{
}

BOOL CMy09��ʱ�����彥��View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy09��ʱ�����彥��View ����

void CMy09��ʱ�����彥��View::OnDraw(CDC* /*pDC*/)
{
	CMy09��ʱ�����彥��Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy09��ʱ�����彥��View ��ӡ

BOOL CMy09��ʱ�����彥��View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy09��ʱ�����彥��View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy09��ʱ�����彥��View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy09��ʱ�����彥��View ���

#ifdef _DEBUG
void CMy09��ʱ�����彥��View::AssertValid() const
{
	CView::AssertValid();
}

void CMy09��ʱ�����彥��View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy09��ʱ�����彥��Doc* CMy09��ʱ�����彥��View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy09��ʱ�����彥��Doc)));
	return (CMy09��ʱ�����彥��Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy09��ʱ�����彥��View ��Ϣ�������


int CMy09��ʱ�����彥��View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//������ID��ʱ���������룩���ص�������NULL��ʹ��Ĭ�ϴ���WM_TIMER��
	SetTimer(101,200,NULL);

	return 0;
}


void CMy09��ʱ�����彥��View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 101)//���ֶ�ʱ��ID
	{
#if 0
		//��ʱ��ʹ�ü��
		static int i = 0;
		CString str;
		str.Format(TEXT("%d"), i++);
		MessageBox(str);
		if (i == 5)
		{//������ID
			KillTimer(101);
		}
#endif
		static int wid= 0;
		wid += 5;
		//��ȡ�ַ�����ͼ����
		CString text = TEXT("�ַ��������������");
		CClientDC dc(this);
		CSize size = dc.GetTextExtent(text);
		if (wid > size.cx)//�жϽ�����κ��ַ����γ���
		{
			wid = 0;
			Invalidate();//ˢ�´���
		}
		int bx = 30;
		int by = 30;
		CRect rect(bx,by,bx+wid,by+size.cy);//��������
		//��ɫдһ��
		dc.TextOutW(bx, by, text);
		//����������ɫ
		dc.SetTextColor(RGB(255,0,0));
		dc.DrawText(text,&rect,DT_LEFT);//���������֣�����ָ�룬���䷽ʽ
	}
	CView::OnTimer(nIDEvent);
}
