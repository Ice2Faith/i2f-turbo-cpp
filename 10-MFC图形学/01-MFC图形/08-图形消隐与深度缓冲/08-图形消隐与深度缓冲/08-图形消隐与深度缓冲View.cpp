
// 08-ͼ����������Ȼ���View.cpp : CMy08ͼ����������Ȼ���View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "08-ͼ����������Ȼ���.h"
#endif

#include "08-ͼ����������Ȼ���Doc.h"
#include "08-ͼ����������Ȼ���View.h"
#include"ZBuffer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void CMy08ͼ����������Ȼ���View::DrawGraph(CDC * pDC)
{
	if (m_isload == false)
		return;
#if 1
	D3Flat * flat = (D3Flat*)malloc(sizeof(D3Flat)*m_tranglecount);
	COLORREF * color = (COLORREF*)malloc(sizeof(COLORREF)*m_tranglecount);
	int beginIndex = 0;
	int count = m_tranglecount;
	for (int i = beginIndex; i < beginIndex + count; i++)
	{
		D3Point p;
		for (int j = 0; j < 3; j++)
		{
			p.x = m_points[this->m_trangle[i][j]].x;
			p.y = m_points[this->m_trangle[i][j]].y;
			p.z = m_points[this->m_trangle[i][j]].z;
			if (j == 0)
				flat[i].p1 = p;
			if (j == 1)
				flat[i].p2 = p;
			if (j == 2)
				flat[i].p3 = p;
		}
		color[i] =  RGB(rand() % 56 + 200, rand() % 106 + 150, rand() % 106 + 150);
	}
	COLORREF bgcolor = 0xffffff;
	ZBufferAlgorithm(flat, color, count, 1024, 1024, pDC->GetSafeHdc(), bgcolor);
	return;
#endif 
#if 0
	CPoint arr[4];
	D3Point p;
	for (int i = 0; i<this->m_tranglecount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			p.x = m_points[this->m_trangle[i][j]].x;
			p.y = m_points[this->m_trangle[i][j]].y;
			p.z = 0;
			arr[j].x = p.x;
			arr[j].y = p.y;

		}

		arr[3] = arr[0];
		pDC->Polyline(arr, 4);
	}
	return;
#endif
	
#if 0
	double aA = AngleToRadian(45);
	double bA = AngleToRadian(63.5);
	double R = 500, d = 400;
	COLORREF linecolor;
	D3Point lp;
	for (int i = -1000; i < 1000; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			
			switch (j)
			{
			case 0:
				lp.y = 0; lp.z = 0,lp.x=i;
				linecolor = 0x0000ff;
				break;
			case 1:
				lp.x = 0; lp.z = 0, lp.y = i;
				linecolor = 0x00ff00;
				break;
			case 2:
				lp.y = 0; lp.x = 0, lp.z = i;
				linecolor = 0xff0000;
				break;
			}
			//ProjOblique(&lp, aA, bA);
			ProjThreePoint(&lp, R, d);
			pDC->SetPixel(lp.x, lp.y, linecolor);
		}
		

	}
	/*D2Flat d2f=MakeD2Flat(MakeD2Point(500,-400),MakeD2Point(-800,0),MakeD2Point(500,400));
	FillScanLine(d2f, 0x00ff00, pDC->GetSafeHdc());
	return; */
	D3Point p;
	COLORREF m_pointColor = 0x0000ff;
	CBrush brush(0x0000ff);
	pDC->SelectObject(&brush);
	
	if (m_drawType == 0)
	{
		for (int i = 0; i < m_pointcount; i++)
		{
			D3Point p = m_points[i];
			ProjOblique(&p, aA, bA);
			pDC->SetPixelV(p.x, p.y, m_pointColor);

		}
	}
	else if (m_drawType == 1)
	{
		CPoint arr[4];
		D3Flat flat;
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				p.x = m_points[this->m_trangle[i][j]].x;
				p.y = m_points[this->m_trangle[i][j]].y;
				p.z = m_points[this->m_trangle[i][j]].z;
				if (j == 0)
					flat.p1 = p;
				if (j == 1)
					flat.p2 = p;
				if (j == 2)
					flat.p3 = p;
				GraphSpin(&p,0,AngleToRadian(m_roundAngle),0);
				//ProjOblique(&p, aA, bA);
				ProjThreePoint(&p, R, d);
				//ProjOrthogonal(&p);
				arr[j].x = p.x;
				arr[j].y = p.y;

			}
				
			arr[3] = arr[0];

			if (D3FlatBlankingAlgorithm(15000, AngleToRadian(0), AngleToRadian(90),flat)>0)
				pDC->Polygon(arr,3);
			//pDC->Polyline(arr, 4);
		}
	}
#endif
}
// CMy07��άģ�ͼ��α任��ͶӰView ����/����
void CMy08ͼ����������Ȼ���View::ResetCenterOrg(CDC * pDC)
{
	//��������ϵ
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(rect.right, -rect.bottom);
}

bool CMy08ͼ����������Ȼ���View::LoadTMFile(char * filename)
{
	FILE * tmf = fopen(filename, "r");
	if (tmf == NULL)
		return false;
	int temp = 0;
	int i = 0;
	if (3 != fscanf(tmf, "%d %d %d\n", &this->m_pointcount, &this->m_tranglecount, &temp))
	{
		fclose(tmf);
		return false;
	}
	this->m_points = (D3Point*)malloc(this->m_pointcount*(sizeof(D3Point)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		fscanf(tmf, "%lf %lf %lf\n", &this->m_points[i].x, &this->m_points[i].y, &this->m_points[i].z);
	}
	this->m_trangle = (int **)malloc(this->m_tranglecount*(sizeof(int*)));
	for (i = 0; i<this->m_tranglecount; i++)
	{
		this->m_trangle[i] = (int*)malloc(3 * sizeof(int));
		fscanf(tmf, "%d %d %d\n", &this->m_trangle[i][0], &this->m_trangle[i][1], &this->m_trangle[i][2]);
	}
	fclose(tmf);
	return true;
}
// CMy08ͼ����������Ȼ���View

IMPLEMENT_DYNCREATE(CMy08ͼ����������Ȼ���View, CView)

BEGIN_MESSAGE_MAP(CMy08ͼ����������Ȼ���View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMy08ͼ����������Ȼ���View ����/����

CMy08ͼ����������Ȼ���View::CMy08ͼ����������Ȼ���View()
: m_roundAngle(0)
{
	// TODO:  �ڴ˴���ӹ������
	m_isload = false;
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_drawType = 1;
	m_isload = LoadTMFile("..\\Bunny.tm");
	srand(time(NULL));
}

CMy08ͼ����������Ȼ���View::~CMy08ͼ����������Ȼ���View()
{
}

BOOL CMy08ͼ����������Ȼ���View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return CView::PreCreateWindow(cs);
}

// CMy08ͼ����������Ȼ���View ����

void CMy08ͼ����������Ȼ���View::OnDraw(CDC* pDC)
{
	CMy08ͼ����������Ȼ���Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	CPen pen(0, 1, 0x00ff00);
	pDC->SelectObject(&pen);
	ResetCenterOrg(pDC);
	DrawGraph(pDC);
}


// CMy08ͼ����������Ȼ���View ��ӡ

BOOL CMy08ͼ����������Ȼ���View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy08ͼ����������Ȼ���View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy08ͼ����������Ȼ���View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy08ͼ����������Ȼ���View ���

#ifdef _DEBUG
void CMy08ͼ����������Ȼ���View::AssertValid() const
{
	CView::AssertValid();
}

void CMy08ͼ����������Ȼ���View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy08ͼ����������Ȼ���Doc* CMy08ͼ����������Ȼ���View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy08ͼ����������Ȼ���Doc)));
	return (CMy08ͼ����������Ȼ���Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy08ͼ����������Ȼ���View ��Ϣ�������


void CMy08ͼ����������Ȼ���View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (ID_TIMER_KARTON == nIDEvent)
	{
		m_roundAngle = (m_roundAngle+1);
		if (m_roundAngle > 360)
			m_roundAngle -= 360;
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


void CMy08ͼ����������Ȼ���View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_isload)
		SetTimer(ID_TIMER_KARTON, 800, NULL);
	CView::OnRButtonDown(nFlags, point);
}
