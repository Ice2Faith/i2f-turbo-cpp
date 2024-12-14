
// 02-TM�ļ�������ͼView.cpp : CMy02TM�ļ�������ͼView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "02-TM�ļ�������ͼ.h"
#endif

#include "02-TM�ļ�������ͼDoc.h"
#include "02-TM�ļ�������ͼView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include<stdio.h>
#include<math.h>
//б���⻭��
//��άת��ά������X
#define V3TOV2X(x,y,z) (int)(x+y/2.0*cos(atan2(1.0,1.0)))
//��άת��ά������Y
#define V3TOV2Y(x,y,z) (int)(z+y/2.0*sin(atan2(1.0,1.0)))
//��άת��ά������X��Y
#define V3TOV2XY(x,y,z) (int)(x+y/2.0*cos(atan2(1.0,1.0))),(int)(z+y/2.0*sin(atan2(1.0,1.0)))
//ǿ������ת��
#define TOINT(x) (int)(x)
//���������ɫ
#define MCOLOR RGB(255,0,0)
//���ݿռ�ֱ�߻�ȡ��ֱ�ߵ�����
#define VECTORLINE(x1,y1,z1,x2,y2,z2) (int)(x2-x1), (int)(y2-y1), (int)(z2-z1)
//��ȡ�ռ�ƽ��ķ�����
#define NORMALLINE(x1,y1,z1,x2,y2,z2) (int)(y1*z2 - y2*z1), (int)(x1*z2 - x2*z1), (int)(x1*y2 - x2*y1)
//��ȡ�ռ������ļн�
#define MATRIXCOS(x1,y1,z1,x2,y2,z2) ((x1*x2 + y1*y2 + z1*z2)*1.0 / (sqrt(pow(x1, 2.0)+pow(y1, 2.0)+pow(z1, 2.0))*sqrt(pow(x2, 2.0)+pow(y2, 2.0)+ pow(z2, 2.0))))
void Wchar_t2Char(wchar_t Wchar[], char Char[])
{
	int size = WideCharToMultiByte(CP_ACP, 0, Wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Wchar, -1, Char, size, NULL, NULL);
}
void CMy02TM�ļ�������ͼView::ResetCenterOrg(CDC * pDC)
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
void CMy02TM�ļ�������ͼView::DrawOrgLine(CDC * pDC)
{
	//��������ϵ
	pDC->MoveTo(V3TOV2XY(-2000, 0, 0));
	pDC->LineTo(V3TOV2XY(2000, 0, 0));

	pDC->MoveTo(V3TOV2XY(0, -2000, 0));
	pDC->LineTo(V3TOV2XY(0, 2000, 0));

	pDC->MoveTo(V3TOV2XY(0, 0, -2000));
	pDC->LineTo(V3TOV2XY(0, 0, 2000));
}
bool CMy02TM�ļ�������ͼView::LoadTMFile(char * filename)
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
	this->m_points = (double **)malloc(this->m_pointcount*(sizeof(double*)));
	for (i = 0; i<this->m_pointcount; i++)
	{
		this->m_points[i] = (double*)malloc(3 * sizeof(double));
		fscanf(tmf, "%lf %lf %lf\n", &this->m_points[i][0], &this->m_points[i][1], &this->m_points[i][2]);
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
void CMy02TM�ļ�������ͼView::DrawVPolygon(CDC* pDC)
{
	if (this->m_isload == false)
		return;
	CPoint arr[4];
	if (this->m_drawtype == 0)
	{
		for (int i = 0; i<this->m_pointcount; i++)
		{
			pDC->SetPixelV(V3TOV2XY(TOINT(this->m_points[i][0] * this->m_shrink / 10.0), TOINT(this->m_points[i][1] * this->m_shrink / 10.0), TOINT(this->m_points[i][2] * this->m_shrink / 10.0)), MCOLOR);
		}
	}
	else if (this->m_drawtype == 1)
	{
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			for (int j = 0; j<3; j++)
			{
				arr[j].x = V3TOV2X(TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0));
				arr[j].y = V3TOV2Y(TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0), TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0));
			}
			arr[3] = arr[1];
			pDC->Polyline(arr, 4);
		}
	}
	else if (this->m_drawtype == 2)
	{
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			int darr[3][3] = {0};
			for (int j = 0; j<3; j++)
			{
				int d3x = TOINT(this->m_points[this->m_trangle[i][j]][0] * this->m_shrink / 10.0);
				int d3y = TOINT(this->m_points[this->m_trangle[i][j]][1] * this->m_shrink / 10.0);
				int d3z = TOINT(this->m_points[this->m_trangle[i][j]][2] * this->m_shrink / 10.0);
				arr[j].x = V3TOV2X(d3x, d3y, d3z);
				arr[j].y = V3TOV2Y(d3x, d3y, d3z);
				darr[j][0] = d3x;
				darr[j][1] = d3y;
				darr[j][2] = d3z;
			}
			if (this->m_openeye == true)
			{
				int vec1[3] = { VECTORLINE(darr[0][0], darr[0][1], darr[0][2], darr[1][0], darr[1][1], darr[1][2]) };
				int vec2[3] = { VECTORLINE(darr[1][0], darr[1][1], darr[1][2], darr[2][0], darr[2][1], darr[2][2]) };
				int nli[3] = { NORMALLINE(vec1[0], vec1[1], vec1[2], vec2[0], vec2[1], vec2[2]) };
				if (MATRIXCOS(nli[0], nli[1], nli[2], -1, -1, 1) >= 0 || MATRIXCOS(nli[0], nli[1], nli[2], 1, -1, -1) >= 0 || MATRIXCOS(nli[0], nli[1], nli[2], 1, -1, 1) >= 0)
					pDC->Polygon(arr, 3);
			}
			else
			{
				pDC->Polygon(arr, 3);
			}
		}
	}
}
void CMy02TM�ļ�������ͼView::ReLoadDrawData(char * filename)
{
	ClearDrawData();
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_isload = LoadTMFile(filename);
}
void CMy02TM�ļ�������ͼView::InitDraw()
{
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_isload = false;
	m_viewOrgLine = false;
	m_centerOrg = false;
	m_shrink = 10;
	m_openeye = false;
	m_drawtype = 0;//0 point 1 line 2 vprint
	m_isload = LoadTMFile("res\\Bunny.tm");
}
void CMy02TM�ļ�������ͼView::ClearDrawData()
{
	if (this->m_isload)
	{
		int i = 0;
		for (i = 0; i<this->m_pointcount; i++)
			free(this->m_points[i]);
		for (i = 0; i<this->m_tranglecount; i++)
			free(this->m_trangle[i]);
		free(m_points);
		free(m_trangle);
	}
}
CMy02TM�ļ�������ͼView::CMy02TM�ļ�������ͼView()
{
	// TODO: add construction code here
	InitDraw();
}

CMy02TM�ļ�������ͼView::~CMy02TM�ļ�������ͼView()
{
	ClearDrawData();
}
// CMy02TM�ļ�������ͼView

IMPLEMENT_DYNCREATE(CMy02TM�ļ�������ͼView, CView)

BEGIN_MESSAGE_MAP(CMy02TM�ļ�������ͼView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMy02TM�ļ�������ͼView::OnSelectCenterOrg)
	ON_COMMAND(ID_32772, &CMy02TM�ļ�������ͼView::OnSelectViewOrgLine)
	ON_COMMAND(ID_32773, &CMy02TM�ļ�������ͼView::OnSelectViewMode)
	ON_WM_DROPFILES()
	ON_WM_CREATE()
	ON_COMMAND(ID_32774, &CMy02TM�ļ�������ͼView::OnSelectShrink)
	ON_WM_MOUSEHWHEEL()
	ON_COMMAND(ID_32775, &CMy02TM�ļ�������ͼView::OnSelectResetShrink)
	ON_COMMAND(ID_32776, &CMy02TM�ļ�������ͼView::OnSelectEyeView)
END_MESSAGE_MAP()



BOOL CMy02TM�ļ�������ͼView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy02TM�ļ�������ͼView ����

void CMy02TM�ļ�������ͼView::OnDraw(CDC* pDC)
{
	CMy02TM�ļ�������ͼDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	if (m_centerOrg==true)
		ResetCenterOrg(pDC);
	if (m_viewOrgLine==true)
		DrawOrgLine(pDC);
	DrawVPolygon(pDC);
}


// CMy02TM�ļ�������ͼView ��ӡ

BOOL CMy02TM�ļ�������ͼView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy02TM�ļ�������ͼView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy02TM�ļ�������ͼView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMy02TM�ļ�������ͼView ���

#ifdef _DEBUG
void CMy02TM�ļ�������ͼView::AssertValid() const
{
	CView::AssertValid();
}

void CMy02TM�ļ�������ͼView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy02TM�ļ�������ͼDoc* CMy02TM�ļ�������ͼView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy02TM�ļ�������ͼDoc)));
	return (CMy02TM�ļ�������ͼDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy02TM�ļ�������ͼView ��Ϣ�������


void CMy02TM�ļ�������ͼView::OnSelectCenterOrg()
{
	// TODO:  �ڴ���������������
	this->m_centerOrg = true;
	Invalidate();
}


void CMy02TM�ļ�������ͼView::OnSelectViewOrgLine()
{
	// TODO:  �ڴ���������������
	this->m_viewOrgLine = !this->m_viewOrgLine;
	Invalidate();
}


void CMy02TM�ļ�������ͼView::OnSelectViewMode()
{
	// TODO:  �ڴ���������������
	this->m_drawtype = (this->m_drawtype + 1) % 3;
	Invalidate();
}


void CMy02TM�ļ�������ͼView::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TCHAR filePath[200];
	if (DragQueryFile(hDropInfo, -1, NULL, 0))
	{
		DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));
	}
	DragFinish(hDropInfo);
	char filename[256] = { 0 };
	Wchar_t2Char(filePath, filename);
	ReLoadDrawData(filename);
	Invalidate();
	CView::OnDropFiles(hDropInfo);
}


int CMy02TM�ļ�������ͼView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	DragAcceptFiles(TRUE);
	return 0;
}


void CMy02TM�ļ�������ͼView::OnSelectShrink()
{
	// TODO:  �ڴ���������������
	this->m_shrink = (this->m_shrink + 2) % 100;
	Invalidate();
}


void CMy02TM�ļ�������ͼView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// �˹���Ҫ�� Windows Vista ����߰汾��
	// _WIN32_WINNT ���ű��� >= 0x0600��
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (zDelta > 0)
	{
		this->m_shrink = (this->m_shrink + 2) % 100;
	}
	else
	{
		this->m_shrink = (this->m_shrink - 2);
		if (this->m_shrink < 2)
			this->m_shrink = 2;
	}
	Invalidate();
	CView::OnMouseHWheel(nFlags, zDelta, pt);
}


void CMy02TM�ļ�������ͼView::OnSelectResetShrink()
{
	// TODO:  �ڴ���������������
	this->m_shrink = 10;
	Invalidate();
}


void CMy02TM�ļ�������ͼView::OnSelectEyeView()
{
	// TODO:  �ڴ���������������
	this->m_openeye = !this->m_openeye;
	Invalidate();
}
