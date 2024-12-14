
// MapRouterView.cpp : CMapRouterView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MapRouter.h"
#endif

#include "MapRouterDoc.h"
#include "MapRouterView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double getDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}


// CMapRouterView

IMPLEMENT_DYNCREATE(CMapRouterView, CView)

BEGIN_MESSAGE_MAP(CMapRouterView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	//����¼�
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	//�˵��¼�
	ON_COMMAND(ID_EDIT_POINT, &CMapRouterView::OnEditPoint)
	ON_COMMAND(ID_EDIT_EDGE, &CMapRouterView::OnEditEdge)
	ON_COMMAND(ID_EDIT_BEGIN_END_POINT, &CMapRouterView::OnEditBeginEndPoint)
	ON_COMMAND(ID_RUN_ROUTE, &CMapRouterView::OnRunRoute)
	ON_COMMAND(ID_FILE_OPEN, &CMapRouterView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CMapRouterView::OnFileSave)
	ON_COMMAND(ID_CLEAN_EDGES, &CMapRouterView::OnCleanEdges)
	ON_COMMAND(ID_CLEAN_MAP, &CMapRouterView::OnCleanMap)
	ON_COMMAND(ID_DISPLAY_RESULT_ONE, &CMapRouterView::OnDisplayResultOne)
	ON_COMMAND(ID_DISPLAY_RESULT_THIRD, &CMapRouterView::OnDisplayResultThird)
	ON_COMMAND(ID_DISPLAY_RESULT_ALL, &CMapRouterView::OnDisplayResultAll)
	ON_COMMAND(ID_EDIT_NONE, &CMapRouterView::OnEditNone)
	ON_COMMAND(ID_SWITCH_BGIMG_SHOW, &CMapRouterView::OnSwitchBgimgShow)
	ON_COMMAND(ID_SWITCH_THEME_COLOR, &CMapRouterView::OnSwitchThemeColor)
	ON_COMMAND(ID_SWITCH_EDGE_DIRECT_DBL, &CMapRouterView::OnSwitchEdgeDirectDbl)
	ON_COMMAND(ID_SWITCH_POINT_DISTANCE_AS_WEIGHT, &CMapRouterView::OnSwitchPointDistanceAsWeight)
	ON_COMMAND(ID_SWITCH_FULL_PRIOR_WEIGHT, &CMapRouterView::OnSwitchFullPriorWeight)
	ON_COMMAND(ID_SWITCH_SHOW_WEIGHT, &CMapRouterView::OnSwitchShowWeight)
END_MESSAGE_MAP()

// CMapRouterView ����/����

CMapRouterView::CMapRouterView()
{
	// TODO:  �ڴ˴���ӹ������
	this->isLBtnDown = false;
	this->isRBtnDown = false;
	this->isMBtnDown = false;
	this->recogRadius = 8.0;
	this->beginIdx = -1;
	this->endIdx = -1;
	this->mostDisplayCount = 1;
	this->isShowBgImg = true;
	this->isBlackPanel = false;
	this->isEdgeDirectDbl = false;
	this->isPointDistanceAsEdgeWeight = false;
	this->isFullWeightPrior = true;
	this->isShowWeight = false;
	this->operType = OT_NULL;
	this->map.clean();
	srand((unsigned int)time(NULL));
}

CMapRouterView::~CMapRouterView()
{
	this->map.clean();
}


BOOL CMapRouterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMapRouterView ����

void CMapRouterView::OnDraw(CDC* pDC)
{
	CMapRouterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	CWnd * wnd = pDC->GetWindow();
	RECT rect;
	wnd->GetWindowRect(&rect);

	if (this->isBlackPanel){
		CBrush brush(RGB(50, 50, 50));
		CBrush * oldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(-1, -1, rect.right - rect.left + 1, rect.bottom - rect.top + 1);
		pDC->SelectObject(oldBrush);
		pDC->SetTextColor(RGB(255, 255, 255));
	}
	else{
		pDC->SetTextColor(RGB(0, 0, 0));
	}

	if (this->isShowBgImg){
		HDC hdc = GetImageHDC(&bgImg);
		SetStretchBltMode(pDC->GetSafeHdc(), STRETCH_HALFTONE);
		StretchBlt(pDC->GetSafeHdc(), 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdc, 0, 0, bgImg.getwidth(), bgImg.getheight(), SRCCOPY);
	}

	drawMapContent(pDC);
}


// CMapRouterView ��ӡ

BOOL CMapRouterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMapRouterView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	DEVMODE * dev = (LPDEVMODE)::GlobalLock(pInfo->m_pPD->m_pd.hDevMode);
	if (dev != NULL)
	{
		dev->dmOrientation = DMORIENT_LANDSCAPE;
		pDC->ResetDCW(dev);
	}

	::GlobalUnlock(pInfo->m_pPD->m_pd.hDevMode);
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMapRouterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMapRouterView ���

#ifdef _DEBUG
void CMapRouterView::AssertValid() const
{
	CView::AssertValid();
}

void CMapRouterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapRouterDoc* CMapRouterView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapRouterDoc)));
	return (CMapRouterDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapRouterView ��Ϣ�������

/////////////////////////////////////////////////////////////////////////////////////
template<typename T>
double getLineDirection(T x1, T y1, T x2, T y2)
{
	return atan2(y2 - y1*1.0, x2 - x1*1.0);
}
template<typename T>
double AngleToRadian(T angle)
{
	return angle / 180.0*3.141592653549;
}
template<typename T, typename E>
void getEndPoint(T ix, T iy, E length, double direct, T * ox, T * oy)
{
	*ox = ix + length*cos(direct);
	*oy = iy + length*sin(direct);
}

void CMapRouterView::drawArrow(CDC * pDC, double x1, double y1, double x2, double y2)
{
	POINT tp;
	pDC->MoveTo(x2, y2);
	pDC->LineTo(x1, y1);
	double direct = getLineDirection(x2, y2, x1, y1);
	double factor = AngleToRadian(15);
	double ldirect = direct - factor;
	double rdirect = direct + factor;
	double len = getDistance(x2, y2, x1, y1)*0.3;
	if (len < 3)len = 3;
	if (len>50)len = 50;
	POINT lend = { 0 };
	getEndPoint((long)x2, (long)y2, len, ldirect, &lend.x, &lend.y);
	pDC->MoveTo(x2, y2);
	pDC->LineTo(lend.x, lend.y);
	POINT rend = { 0 };
	getEndPoint((long)x2,(long)y2, len, rdirect, &rend.x, &rend.y);
	pDC->MoveTo(x2, y2);
	pDC->LineTo(rend.x, rend.y);
}
void CMapRouterView::drawMapContent(CDC * pDC)
{
	pDC->SetBkMode(TRANSPARENT);

	if (map.edges.size() > 0){
		CPen pen(PS_SOLID, 1, RGB(0, 255, 0));
		CPen * oldPen = pDC->SelectObject(&pen);
		for (int i = 0; i < map.edges.size(); i++){
			MapEdge e = map.edges.at(i);

			MapPoint ps = map.points.at(e.sidx);
			MapPoint pe = map.points.at(e.eidx);

			/*pDC->MoveTo(ps.x, ps.y);
			pDC->LineTo(pe.x, pe.y);
			pDC->Rectangle(pe.x - 2, pe.y - 2, pe.x + 2, pe.y + 2);*/
			drawArrow(pDC, ps.x, ps.y, pe.x, pe.y);

			if (isPointDistanceAsEdgeWeight || isShowWeight){
				if (isShowWeight){
					CString ostr;
					ostr.Format(TEXT("%.3lf"), e.weight);
					pDC->TextOutW((ps.x + pe.x) / 2, (ps.y + pe.y) / 2, ostr);
				}
			}
		}
		pDC->SelectObject(oldPen);
	}

	if (routes.size() > 0){
		int count = 0;
		CString routesStrs;
		for (int i = 0; i < routes.size(); i++){
			double rate = 1.0 - i*1.0 / routes.size();
			int balanceColor = rand() % 100;
			int lineWid = routes.size() - i;
			COLORREF lineColor = RGB(balanceColor, 150 * rate, 255 * rate);
			if (mostDisplayCount == 1){
				lineWid = 2;
			}
			CPen pen(PS_DOT, lineWid ,lineColor);
			CPen * oldPen = pDC->SelectObject(&pen);
			MapRouteResult rs = routes.at(i);
			if (rs.pass){
				count++;
				CString istr;
				istr.Format(TEXT("%d : "), count);
				routesStrs += istr;
				for (int j = 0; j < rs.routes.size(); j++){
					CString pstr;
					pstr.Format(TEXT("->%d"), rs.routes.at(j));
					routesStrs += pstr;
					if (j != 0 && i<mostDisplayCount){
						MapPoint ps = map.points.at(rs.routes.at(j - 1));
						MapPoint pe = map.points.at(rs.routes.at(j));

						/*pDC->MoveTo(ps.x, ps.y);
						pDC->LineTo(pe.x, pe.y);
						pDC->Rectangle(pe.x - 2, pe.y - 2, pe.x + 2, pe.y + 2);*/
						drawArrow(pDC, ps.x, ps.y, pe.x, pe.y);
					}
				}
				routesStrs += TEXT("\n");
			}
			pDC->SelectObject(oldPen);
		}
		CString str;
		str.Format(TEXT("��%d��·�����ҵ�:\n"),count);
		str += routesStrs;
		if (isPointDistanceAsEdgeWeight){
			str = str + TEXT("ʹ�õ������ΪȨ��״̬������\n");
		}
		else{
			str = str + TEXT("ʹ�õ������ΪȨ��״̬������\n");
		}
		if (isFullWeightPrior){
			str = str + TEXT("ȫ����СȨ�����ȣ�����\n");
		}
		else{
			str = str + TEXT("ȫ����СȨ�����ȣ�����\n");
		}
		//pDC->TextOutW(0, 0, str);
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = 1080;
		rect.bottom = 720;
		// ֧�ֻ���
		pDC->DrawText(str, &rect, DT_TOP);
	}

	if (map.points.size() > 0){
		CPen pen(0, 1, RGB(255, 0, 0));
		CPen * oldPen = pDC->SelectObject(&pen);
		CBrush brush(RGB(255, 0, 0));
		CBrush * oldBrush = pDC->SelectObject(&brush);
		for (int i = 0; i < map.points.size(); i++){
			MapPoint p = map.points.at(i);

			pDC->Ellipse(p.x - recogRadius, p.y - recogRadius, p.x + recogRadius, p.y + recogRadius);
			CString str;
			str.Format(TEXT("%d"), i);
			pDC->TextOutW(p.x,p.y,str);
		}
		pDC->SelectObject(oldPen);
		pDC->SelectObject(oldBrush);
	}

	if (beginIdx >= 0){
		CPen pen(0, 1, RGB(0, 255, 100));
		CPen * oldPen = pDC->SelectObject(&pen);
		CBrush brush(RGB(0, 255, 100));
		CBrush * oldBrush = pDC->SelectObject(&brush);

		MapPoint ps = map.points.at(beginIdx);
		pDC->Ellipse(ps.x - recogRadius, ps.y - recogRadius, ps.x + recogRadius, ps.y + recogRadius);

		pDC->SelectObject(oldPen);
		pDC->SelectObject(oldBrush);
	}
	
	if (endIdx >= 0){
		CPen pen(0, 1, RGB(0, 100, 255));
		CPen * oldPen = pDC->SelectObject(&pen);
		CBrush brush(RGB(0, 100, 255));
		CBrush * oldBrush = pDC->SelectObject(&brush);

		MapPoint ps = map.points.at(endIdx);
		pDC->Ellipse(ps.x - recogRadius, ps.y - recogRadius, ps.x + recogRadius, ps.y + recogRadius);

		pDC->SelectObject(oldPen);
		pDC->SelectObject(oldBrush);
	}
}

int CMapRouterView::findPointIdx(double x, double y, double radius)
{
	for (int i = 0; i < map.points.size(); i++){
		MapPoint p = map.points.at(i);
		double dis = getDistance(p.x, p.y, x, y);
		if (dis < radius){
			return i;
		}
	}
	return -1;
}



void CMapRouterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	isLBtnDown = true;
	beginPoint = point;
	
	//this->Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

void CMapRouterView::OnLButtonUp(UINT nFlags, CPoint point)
{
	isLBtnDown = false;
	switch (this->operType){
	case OT_EDIT_POINT:
	{
						  MapPoint p = { 0 };
						  p.x = point.x;
						  p.y = point.y;
						  this->map.points.push_back(p);
	}
		
		break;
	case OT_EDIT_EDGE:
	{
						 int sidx = findPointIdx(beginPoint.x, beginPoint.y, recogRadius);
						 int eidx = findPointIdx(point.x, point.y, recogRadius);
						 if (sidx >= 0 && eidx >= 0 && sidx != eidx){
							 this->map.addEdge(sidx, eidx);
							 if (isEdgeDirectDbl){
								 this->map.addEdge(eidx, sidx);
							 }
						 }
	}
		break;
	case OT_SET_SE_POINT:
	{
							int idx = findPointIdx(point.x, point.y, recogRadius);
							if (idx >= 0){
								this->beginIdx = idx;
							}
							else{
								beginIdx = -1;
							}
	}
		break;
	}
	this->Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CMapRouterView::OnMButtonDown(UINT nFlags, CPoint point)
{
	isMBtnDown = true;
	beginPoint = point;

	//this->Invalidate();
	CView::OnMButtonDown(nFlags, point);
}

void CMapRouterView::OnMButtonUp(UINT nFlags, CPoint point)
{
	isMBtnDown = false;

	//this->Invalidate();
	CView::OnMButtonDown(nFlags, point);
}

void CMapRouterView::OnMouseMove(UINT nFlags, CPoint point)
{
	static int lastIdx = -1;
	bool freshScreen = false;
	switch (this->operType){
	case OT_EDIT_POINT:
	{
						  if (isMBtnDown){
							  if (lastIdx >= 0){
								  map.points[lastIdx].x = point.x;
								  map.points[lastIdx].y = point.y;
								  freshScreen = true;
							  }
							  else{
								  int idx = findPointIdx(beginPoint.x, beginPoint.y, recogRadius);
								  if (idx >= 0){
									  if (map.points.size() > idx){
										  map.points[idx].x = point.x;
										  map.points[idx].y = point.y;
										  freshScreen = true;
										  lastIdx = idx;
									  }
								  }
							  }
							  
						  }
	}
		break;
	}
	if (freshScreen){
		this->Invalidate();
	}
	else{
		lastIdx = -1;
	}
	CView::OnMouseMove(nFlags, point);
}

void CMapRouterView::OnRButtonDown(UINT nFlags, CPoint point)
{
	isRBtnDown = true;
	beginPoint = point;

	//this->Invalidate();
	CView::OnRButtonDown(nFlags, point);
}

void CMapRouterView::OnRButtonUp(UINT nFlags, CPoint point)
{
	isRBtnDown = false;
	switch (this->operType){
	case OT_EDIT_POINT:
	{
						  int idx = findPointIdx(point.x, point.y, recogRadius);
						  if (idx >= 0){
							  this->map.removePoint(idx);
							  this->routes.clear();
						  }
	}

		break;
	case OT_EDIT_EDGE:
	{
						 int sidx = findPointIdx(beginPoint.x, beginPoint.y, recogRadius);
						 int eidx = findPointIdx(point.x, point.y, recogRadius);
						 if (sidx >= 0 && eidx >= 0 && sidx != eidx){
							 this->map.removeEdge(sidx, eidx);
							 if (isEdgeDirectDbl){
								 this->map.removeEdge(eidx, sidx);
							 }
							 this->routes.clear();
						 }
	}
		break;
	case OT_SET_SE_POINT:
	{
							int idx = findPointIdx(point.x, point.y, recogRadius);
							if (idx >= 0){
								this->endIdx = idx;
							}
							else{
								endIdx = -1;
							}
	}
		break;
	}
	this->Invalidate();
	CView::OnRButtonUp(nFlags, point);
}



void CMapRouterView::OnEditNone()
{
	// TODO:  �ڴ���������������
	this->operType = OT_NULL;
}


void CMapRouterView::OnEditPoint()
{
	// TODO:  �ڴ���������������
	this->operType = OT_EDIT_POINT;
}


void CMapRouterView::OnEditEdge()
{
	// TODO:  �ڴ���������������
	this->operType = OT_EDIT_EDGE;
}


void CMapRouterView::OnEditBeginEndPoint()
{
	// TODO:  �ڴ���������������
	this->operType = OT_SET_SE_POINT;
}


void CMapRouterView::OnRunRoute()
{
	// TODO:  �ڴ���������������
	MapRouter router;
	if (isPointDistanceAsEdgeWeight){
		map.setWeightsByDistance(false);
	}
	else{
		map.setWeightsByDistance(true);
	}
	
	routes = router.routeMap(map, beginIdx, endIdx, isPointDistanceAsEdgeWeight, isFullWeightPrior);
	this->Invalidate();
}


void CMapRouterView::OnFileOpen()
{
	// TODO:  �ڴ���������������
	CString gReadFilePathName;
	CFileDialog fileDlg(true, _T("png"), _T("*.png"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("png Files (*.png)|*.png|jpg File(*.jpg)|*.jpg|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //�����Ի���  
	{
		gReadFilePathName = fileDlg.GetPathName();//�õ��������ļ�����·��
		CString filename = fileDlg.GetFileName();//���ļ���
		IMAGE pimg;
		loadimage(&pimg, gReadFilePathName);
		bgImg = pimg;
		this->Invalidate();
	}
}


void CMapRouterView::OnFileSave()
{
	// TODO:  �ڴ���������������
	
	CString gReadFilePathName;
	CFileDialog fileDlg(false, _T("png"), _T("route.png"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("png Files (*.png)|*.png|jpg File(*.jpg)|*.jpg|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //�����Ի���  
	{
		gReadFilePathName = fileDlg.GetPathName();//�õ��������ļ�����·��
		CString filename = fileDlg.GetFileName();//���ļ���

		CDC * pDC = this->GetDC();
		CWnd * wnd = pDC->GetWindow();
		RECT rect;
		wnd->GetWindowRect(&rect);
		IMAGE img(rect.right - rect.left, rect.bottom - rect.top);
		HDC sdc = GetImageHDC(&img);
		BitBlt(sdc, 0, 0, img.getwidth(), img.getheight(), pDC->GetSafeHdc(), 0, 0, SRCCOPY);
		saveimage(gReadFilePathName, &img);
		this->Invalidate();
	}
}



void CMapRouterView::OnCleanEdges()
{
	// TODO:  �ڴ���������������
	this->map.edges.clear();
	this->routes.clear();
	this->Invalidate();
}


void CMapRouterView::OnCleanMap()
{
	// TODO:  �ڴ���������������
	this->map.edges.clear();
	this->map.points.clear();
	this->routes.clear();
	this->beginIdx = -1;
	this->endIdx = -1;
	this->Invalidate();
}


void CMapRouterView::OnDisplayResultOne()
{
	// TODO:  �ڴ���������������
	mostDisplayCount = 1;
	this->Invalidate();
}


void CMapRouterView::OnDisplayResultThird()
{
	// TODO:  �ڴ���������������
	mostDisplayCount = 3;
	this->Invalidate();
}


void CMapRouterView::OnDisplayResultAll()
{
	// TODO:  �ڴ���������������
	mostDisplayCount = 9999;
	this->Invalidate();
}




void CMapRouterView::OnSwitchBgimgShow()
{
	// TODO:  �ڴ���������������
	isShowBgImg = !isShowBgImg;
	this->Invalidate();
}


void CMapRouterView::OnSwitchThemeColor()
{
	// TODO:  �ڴ���������������
	isBlackPanel = !isBlackPanel;
	this->Invalidate();
}


void CMapRouterView::OnSwitchEdgeDirectDbl()
{
	// TODO:  �ڴ���������������
	isEdgeDirectDbl = !isEdgeDirectDbl;
}


void CMapRouterView::OnSwitchPointDistanceAsWeight()
{
	// TODO:  �ڴ���������������
	isPointDistanceAsEdgeWeight = !isPointDistanceAsEdgeWeight;
	if (isPointDistanceAsEdgeWeight){
		map.setWeightsByDistance(false);
	}
	this->OnRunRoute();
}


void CMapRouterView::OnSwitchFullPriorWeight()
{
	// TODO:  �ڴ���������������
	isFullWeightPrior = !isFullWeightPrior;
	this->OnRunRoute();
}


void CMapRouterView::OnSwitchShowWeight()
{
	// TODO:  �ڴ���������������
	isShowWeight = !isShowWeight;
	this->Invalidate();
}
