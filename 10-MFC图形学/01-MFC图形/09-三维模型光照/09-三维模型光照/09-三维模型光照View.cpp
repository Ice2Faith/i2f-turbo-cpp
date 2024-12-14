
// 09-��άģ�͹���View.cpp : CMy09��άģ�͹���View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "09-��άģ�͹���.h"
#endif

#include "09-��άģ�͹���Doc.h"
#include "09-��άģ�͹���View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CMy09��άģ�͹���View::DrawGraph(CDC * pDC)
{
	if (m_isload == false)
		return;
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
				lp.y = 0; lp.z = 0, lp.x = i;
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
		D3Color colors[1024];
		int cindex = 0;
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
				//ProjOblique(&p, aA, bA);
				ProjThreePoint(&p, R, d);
				arr[j].x = p.x;
				arr[j].y = p.y;

			}

			arr[3] = arr[0];

			if (D3FlatBlankingAlgorithm(15000, AngleToRadian(0), AngleToRadian(90), flat) > 0)
			{
				D3Point viewpoint;
				D3SphericalToCartesianCoordinates(1000, AngleToRadian(0), AngleToRadian(0), &viewpoint);
				D3Light light = { 0 };//��ɫ����
				light.diff_red = 0.752;
				light.diff_green = 0.606;
				light.diff_blue = 0.226;
				light.spec_red = 0.628;
				light.spec_green = 0.556;
				light.spec_blue = 0.366;
				light.c0 = 0.5;
				light.c1 = 0.8;
				light.c2 = 0.99;
				light.point = MakeD3Point(0,1000,0);
				D3Material mate = {0};//�̱�ʯ����
				mate.diff_red = 0.076;
				mate.diff_green = 0.614;
				mate.diff_blue = 0.075;
				mate.spec_red = 0.633;
				mate.spec_green = 0.728;
				mate.spec_blue = 0.633;
				mate.ambi_red = 0.022;
				mate.ambi_green = 0.175;
				mate.ambi_blue = 0.023;
				mate.heig_n = 30;
				Ambient am = { 0 };//�޻�����
				am.ambi_red = 0;
				am.ambi_green = 0;
				am.ambi_blue = 0;
				
				D3Vector v1, v2;
				GetD3Vector(flat.p1, flat.p2, &v1);
				GetD3Vector(flat.p2,flat.p3,&v2);
				D3NormalLine nl;
				GetD3NormalLine(v1,v2,&nl);
				D3Color color=GraphLight(light, flat.p1, viewpoint, nl, mate, am);
				colors[cindex++] = color;
				if (cindex >= 1023)
					cindex = 0;
				if (cindex % 512 == 0)
					cindex = cindex;
				CPen pen(0,1,RGB(color.red, color.green, color.blue));
				pDC->SelectObject(&pen);
				CBrush brush(RGB(color.red,color.green,color.blue));
				pDC->SelectObject(&brush);
				pDC->Polygon(arr, 3);
			}
				
			//pDC->Polyline(arr, 4);
		}
	}
}
// CMy07��άģ�ͼ��α任��ͶӰView ����/����
void CMy09��άģ�͹���View::ResetCenterOrg(CDC * pDC)
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

bool CMy09��άģ�͹���View::LoadTMFile(char * filename)
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
// CMy09��άģ�͹���View

IMPLEMENT_DYNCREATE(CMy09��άģ�͹���View, CView)

BEGIN_MESSAGE_MAP(CMy09��άģ�͹���View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy09��άģ�͹���View ����/����

CMy09��άģ�͹���View::CMy09��άģ�͹���View()
{
	// TODO:  �ڴ˴���ӹ������
	m_isload = false;
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_drawType = 1;
	m_isload = LoadTMFile("..\\Bunny.tm");
}

CMy09��άģ�͹���View::~CMy09��άģ�͹���View()
{
}

BOOL CMy09��άģ�͹���View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy09��άģ�͹���View ����

void CMy09��άģ�͹���View::OnDraw(CDC* pDC)
{
	CMy09��άģ�͹���Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	/*CPen pen(0, 1, 0x0000ff);
	pDC->SelectObject(&pen);*/
	ResetCenterOrg(pDC);
	DrawGraph(pDC);
}


// CMy09��άģ�͹���View ��ӡ

BOOL CMy09��άģ�͹���View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy09��άģ�͹���View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy09��άģ�͹���View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy09��άģ�͹���View ���

#ifdef _DEBUG
void CMy09��άģ�͹���View::AssertValid() const
{
	CView::AssertValid();
}

void CMy09��άģ�͹���View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy09��άģ�͹���Doc* CMy09��άģ�͹���View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy09��άģ�͹���Doc)));
	return (CMy09��άģ�͹���Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy09��άģ�͹���View ��Ϣ�������
