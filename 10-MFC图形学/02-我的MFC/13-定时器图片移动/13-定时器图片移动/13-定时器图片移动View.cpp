
// 13-��ʱ��ͼƬ�ƶ�View.cpp : CMy13��ʱ��ͼƬ�ƶ�View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "13-��ʱ��ͼƬ�ƶ�.h"
#endif

#include "13-��ʱ��ͼƬ�ƶ�Doc.h"
#include "13-��ʱ��ͼƬ�ƶ�View.h"
#include<time.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy13��ʱ��ͼƬ�ƶ�View

IMPLEMENT_DYNCREATE(CMy13��ʱ��ͼƬ�ƶ�View, CView)

BEGIN_MESSAGE_MAP(CMy13��ʱ��ͼƬ�ƶ�View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CMy13��ʱ��ͼƬ�ƶ�View::OnReStart)
END_MESSAGE_MAP()

// CMy13��ʱ��ͼƬ�ƶ�View ����/����

CMy13��ʱ��ͼƬ�ƶ�View::CMy13��ʱ��ͼƬ�ƶ�View()
{
	// TODO:  �ڴ˴���ӹ������
	for (int i = 0; i < 3;i++)
		px[i] = 0 ;
}

CMy13��ʱ��ͼƬ�ƶ�View::~CMy13��ʱ��ͼƬ�ƶ�View()
{
}

BOOL CMy13��ʱ��ͼƬ�ƶ�View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy13��ʱ��ͼƬ�ƶ�View ����

void CMy13��ʱ��ͼƬ�ƶ�View::OnDraw(CDC* /*pDC*/)
{
	CMy13��ʱ��ͼƬ�ƶ�Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	for (int i = 0; i < 3; i++)
	{
		CDC memdc;
		memdc.CreateCompatibleDC(NULL);
		memdc.SelectObject(&this->m_bitmap[i]);
		CClientDC dc(this);
		dc.BitBlt(0 + px[i], i * 134, 134 + px[i], i * 134 + 134, &memdc, 0, 0, SRCCOPY);
	}
	
}


// CMy13��ʱ��ͼƬ�ƶ�View ��ӡ

BOOL CMy13��ʱ��ͼƬ�ƶ�View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy13��ʱ��ͼƬ�ƶ�View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy13��ʱ��ͼƬ�ƶ�View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy13��ʱ��ͼƬ�ƶ�View ���

#ifdef _DEBUG
void CMy13��ʱ��ͼƬ�ƶ�View::AssertValid() const
{
	CView::AssertValid();
}

void CMy13��ʱ��ͼƬ�ƶ�View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy13��ʱ��ͼƬ�ƶ�Doc* CMy13��ʱ��ͼƬ�ƶ�View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy13��ʱ��ͼƬ�ƶ�Doc)));
	return (CMy13��ʱ��ͼƬ�ƶ�Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy13��ʱ��ͼƬ�ƶ�View ��Ϣ�������


int CMy13��ʱ��ͼƬ�ƶ�View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	this->m_bitmap[0].LoadBitmapW(IDB_BITMAP1);
	this->m_bitmap[1].LoadBitmapW(IDB_BITMAP2);
	this->m_bitmap[2].LoadBitmapW(IDB_BITMAP3);
	SetTimer(101,30,NULL);
	srand((unsigned int)time(NULL));
	return 0;
}


void CMy13��ʱ��ͼƬ�ƶ�View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*��Ҫ������д��ͼ���룬����д���´��ڼ��ɣ����Լ�ȥ����ondraw*/
	if (nIDEvent == 101)
	{
		CRect rect;
		GetClientRect(&rect);
		px[0] = (px[0] + rand()%10) % (rect.right - rect.left - 134);
		px[1] = (px[1] + rand() % 10) % (rect.right - rect.left - 134);
		px[2] = (px[2] + rand() % 10) % (rect.right - rect.left - 134);
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


void CMy13��ʱ��ͼƬ�ƶ�View::OnReStart()
{
	// TODO:  �ڴ���������������
	for (int i = 0; i < 3; i++)
		px[i] = 0;
}
