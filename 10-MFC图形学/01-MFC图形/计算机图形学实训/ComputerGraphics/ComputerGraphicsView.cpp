// ComputerGraphicsView.cpp : implementation of the CComputerGraphicsView class
//

#include "stdafx.h"
#include "ComputerGraphics.h"

#include "ComputerGraphicsDoc.h"
#include "ComputerGraphicsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsView

IMPLEMENT_DYNCREATE(CComputerGraphicsView, CView)

BEGIN_MESSAGE_MAP(CComputerGraphicsView, CView)
	//{{AFX_MSG_MAP(CComputerGraphicsView)
	ON_COMMAND(ID_PEN_COLOR, OnPenColor)
	ON_COMMAND(ID_PEN_SIZE, OnPenSize)
	ON_COMMAND(ID_BRUSH_COLOR, OnBrushColor)
	ON_COMMAND(ID_DRAW_POINT, OnDrawPoint)
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_COMMAND(ID_DRAW_GON, OnDrawGon)
	ON_COMMAND(ID_DRAW_ELIPESE, OnDrawElipese)
	ON_COMMAND(ID_DRAW_CONLINE, OnDrawConline)
	ON_COMMAND(ID_DRAW_CLEANER, OnDrawCleaner)
	ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircle)
	ON_COMMAND(ID_DRAW_BEZIERLINE, OnDrawBezierline)
	ON_COMMAND(ID_DRAW_ARC, OnDrawArc)
	ON_COMMAND(ID_DRAW_POLYGON, OnDrawPolygon)
	ON_COMMAND(ID_DRAW_POLYLINE, OnDrawPolyline)
	ON_COMMAND(ID_DRAW_RECTANGLE, OnDrawRectangle)
	ON_COMMAND(ID_DRAW_NULL, OnDrawNull)
	ON_COMMAND(ID_DRAW_ROUNDRECT, OnDrawRoundrect)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_TMFILE_OPEN, OnTmfileOpen)
	ON_COMMAND(ID_TMFILE_SAVE, OnTmfileSave)
	ON_COMMAND(ID_DISMOD_FLAT, OnDismodFlat)
	ON_COMMAND(ID_DISMOD_LINEAR, OnDismodLinear)
	ON_COMMAND(ID_DISMOD_POINTCLOUD, OnDismodPointcloud)
	ON_COMMAND(ID_DISMOD_CLEANPAINTER, OnDismodCleanpainter)
	ON_COMMAND(ID_GEOMOD_BALL, OnGeomodBall)
	ON_COMMAND(ID_GEOMOD_CONE, OnGeomodCone)
	ON_COMMAND(ID_GEOMOD_CYLINDER, OnGeomodCylinder)
	ON_COMMAND(ID_GEOMOD_DODEC, OnGeomodDodec)
	ON_COMMAND(ID_GEOMOD_HEX, OnGeomodHex)
	ON_COMMAND(ID_GEOMOD_ICOS, OnGeomodIcos)
	ON_COMMAND(ID_GEOMOD_OCT, OnGeomodOct)
	ON_COMMAND(ID_GEOMOD_TETR, OnGeomodTetr)
	ON_COMMAND(ID_GEOMOD_TORUS, OnGeomodTorus)
	ON_COMMAND(ID_TRANGLELIZED, OnTranglelized)
	ON_COMMAND(ID_LINEMODE_BEZIER, OnLinemodeBezier)
	ON_COMMAND(ID_LINEMOD_EDIT, OnLinemodEdit)
	ON_COMMAND(ID_SCANDIS_DDALINE, OnScandisDdaline)
	ON_COMMAND(ID_SCANDIS_ANTIALIASLINE, OnScandisAntialiasline)
	ON_COMMAND(ID_SCAN_SEEDFILL, OnScanSeedfill)
	ON_COMMAND(ID_SCAN_TRANGLEFILL, OnScanTranglefill)
	ON_COMMAND(ID_GRAPH_VARY, OnGraphVary)
	ON_COMMAND(ID_PROJ_DEEPSCREEN, OnProjDeepscreen)
	ON_COMMAND(ID_PROJ_MAINVIEW, OnProjMainview)
	ON_COMMAND(ID_PROJ_OBLIQUE, OnProjOblique)
	ON_COMMAND(ID_PROJ_ONEPOINT, OnProjOnepoint)
	ON_COMMAND(ID_PROJ_ORTHOGONAL, OnProjOrthogonal)
	ON_COMMAND(ID_PROJ_SIDEVIEW, OnProjSideview)
	ON_COMMAND(ID_PROJ_THREEPOINT, OnProjThreepoint)
	ON_COMMAND(ID_PROJ_TOPVIEW, OnProjTopview)
	ON_COMMAND(ID_PROJ_TWOPOINT, OnProjTwopoint)
	ON_COMMAND(ID_PROJ_WORDTOSCREEN, OnProjWordtoscreen)
	ON_COMMAND(ID_MODHIDE_BACKREMOVE, OnModhideBackremove)
	ON_COMMAND(ID_MODHIDE_DEEPBUFF, OnModhideDeepbuff)
	ON_COMMAND(ID_MODHIDE_NONE, OnModhideNone)
	ON_COMMAND(ID_MODLIGHT_FLAT, OnModlightFlat)
	ON_COMMAND(ID_MODLIGHT_NONE, OnModlightNone)
	ON_COMMAND(ID_MODLIGHT_MATERIAEX, OnModlightMateriaex)
	ON_COMMAND(ID_MODLIGHT_LIGHT, OnModlightLight)
	ON_COMMAND(ID_OPERATION_TIPS, OnOperationTips)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CARTON_SETTING, OnCartonSetting)
	ON_WM_TIMER()
	ON_COMMAND(ID_DISMOD_NONE, OnDismodNone)
	ON_COMMAND(ID_LINEMOD_BEZIERYSPIN, OnLinemodBezieryspin)
	ON_COMMAND(ID_SHOW_ORGLINE, OnShowOrgline)
	ON_COMMAND(ID_HIDE_ORGLINE, OnHideOrgline)
	ON_COMMAND(ID_LINEMOD_BEZIERXSPIN, OnLinemodBezierxspin)
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYUP()
	ON_COMMAND(ID_OPERATION_BASEOPE, OnOperationBaseope)
	ON_COMMAND(ID_GEOMOD_BALLEX, OnGeomodBallex)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_LINEMODE_POLYLINE, &CComputerGraphicsView::OnLinemodePolyline)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsView construction/destruction

CComputerGraphicsView::CComputerGraphicsView()
{
	// TODO: add construction code here
	penColor=0x000000;
	brushColor=0xffffff;
	penSize=1;
	penDraw=new CPen(1,1,penColor);
	brushDraw=new CBrush(brushColor);
	 colorDlg = new DlgColorSetting(this);
	 sizeDlg=new DlgSizeSetting(this);
	 inputDlg=new DlgInputBox(this);
	 varyDlg=new DlgGraphVarySetting(this);
	 metaDlg=new DlgMaterialSetting(this);
	lightDlg=new DlgLightSetting(this);
	geomodDlg=new DlgGeoModCreateSetting(this);
	opetipDlg=new DlgOperationTips(this);
	cartonDlg=new DlgCartonSetting(this);
	baseOpeDlg=new DlgBaseOperationHelp(this);
	 drawType=DT_NULL;
	 editBakDrawType = DT_NULL;
	 pointArr=new CPoint[MAXPOINTCOUNT];
	 prePointCount=0;
	isLBtnDown=false;
	isRBtnDown=false;
	isFristLoad=true;
	isShiftDown=false;
	isXDown=false;
	isYDown=false;
	isZDown=false;
	srand((unsigned int)time(NULL));
	viewType=VT_NONE;
	needCleanPainter=false;
	stbmoveIndex=-1;
	projType=PT_TWOPOINT;
	hideType=HT_NONE;
	//金色光照
	lg_light.diff_red = 0.752;
	lg_light.diff_green = 0.606;
	lg_light.diff_blue = 0.226;
	lg_light.spec_red = 0.628;
	lg_light.spec_green = 0.556;
	lg_light.spec_blue = 0.366;
	lg_light.c0 = 0.5;
	lg_light.c1 = 0.8;
	lg_light.c2 = 0.99;
	lg_light.point = GD3Point(1000,0,0);
	lg_mate=metaDlg->GetMaterial();
	lg_viewPoint.ParseSpherical(1000,0,0);
	lg_amb.ambi_red = 0;
	lg_amb.ambi_green = 0;
	lg_amb.ambi_blue = 0;
	needShowCtrlPoint=false;
	needShowOrgLine=false;
}	

CComputerGraphicsView::~CComputerGraphicsView()
{
	delete colorDlg;
	delete sizeDlg;
	delete pointArr;
	delete metaDlg;
	delete varyDlg;
	delete inputDlg;
	delete lightDlg;
	delete geomodDlg;
	delete cartonDlg;
	delete baseOpeDlg;
}

BOOL CComputerGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsView drawing

void CComputerGraphicsView::OnDraw(CDC* pDC)
{
	CComputerGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(isFristLoad)
	{
		//仅在第一次打开程序时适配缓冲绘图环境
		this->mdc=new CDC();
		mdc->CreateCompatibleDC(pDC);
		this->mdimg=new CBitmap();
		mdimg->CreateCompatibleBitmap(pDC,2048,1280);
		mdc->SelectObject(mdimg);
		mdc->SetBkColor(0xffffff);
		mdc->Rectangle(-1,-1,2048,1280);
		opetipDlg->DoModal();
		isFristLoad=false;
	}
	CRect rect;
	CWnd * wnd=pDC->GetWindow();
	wnd->GetWindowRect(rect);
	if(needCleanPainter)
	{
		//清空绘图内容，三维数据不收影响
		COLORREF balckColor=0x000000;
		CPen * pen=new CPen(0,1,balckColor);
		CBrush brush;
		brush.CreateSolidBrush(mdc->GetBkColor());
		CPen * oldPen=mdc->SelectObject(pen);
		CBrush * oldBrush=mdc->SelectObject(&brush);
		mdc->Rectangle(-1,-1,rect.Width(),rect.Height());
		mdc->SelectObject(oldBrush);
		mdc->SelectObject(oldPen);
		delete pen;
		needCleanPainter=false;
	}
	CentralOrg(rect);//三维数据使用中心坐标系
	DrawD3Graph();
	ResetOrg(rect);//绘制完毕之后需要重置坐标给Bitblt使用
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),mdc,0,0,SRCCOPY);
	if(needShowCtrlPoint)
	{
		int i;
		for (i = 0; i <prePointCount; i++)
		{
			pDC->Ellipse(pointArr[i].x-3,pointArr[i].y-3,pointArr[i].x+3,pointArr[i].y+3);
		}
	}
}

void CComputerGraphicsView::CentralOrg(CRect pdcRect)
{
	mdc->SetMapMode(MM_ANISOTROPIC);
	mdc->SetViewportOrg(pdcRect.Width()/2,pdcRect.Height()/2);
	mdc->SetViewportExt(pdcRect.Width(),pdcRect.Height());
	mdc->SetWindowOrg(0,0);
	mdc->SetWindowExt(pdcRect.Width(),-pdcRect.Height());
}

void CComputerGraphicsView::ResetOrg(CRect pdcRect)
{
	mdc->SetMapMode(MM_ANISOTROPIC);
	mdc->SetViewportOrg(0,0);
	mdc->SetViewportExt(pdcRect.Width(),pdcRect.Height());
	mdc->SetWindowOrg(0,0);
	mdc->SetWindowExt(pdcRect.Width(),pdcRect.Height());
}
/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsView printing

BOOL CComputerGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CComputerGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CComputerGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsView diagnostics

#ifdef _DEBUG
void CComputerGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CComputerGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CComputerGraphicsDoc* CComputerGraphicsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CComputerGraphicsDoc)));
	return (CComputerGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsView message handlers


void CComputerGraphicsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	isLBtnDown=true;
	int i=0,j=0;
	switch(drawType)
	{
	case DT_POINT://左键点击画点
		prePointCount=0;
		mdc->SetPixelV(point,penColor);
		break;
	case ST_SEENDFILL://左键点击进行种子填充
		{
			HDC hdc=mdc->GetSafeHdc();
			GD2Point seedp(point.x,point.y);
			GGrating::SeedFillAlgorithm(hdc,seedp,mdc->GetPixel(point),brushColor);
		}
		break;
	case DT_LINE:
	case DT_CONLINE:
	case DT_CIRCLE:
	case DT_ELIPESE:
	case DT_RECT:
	case DT_ROUNDRECT:
	case ST_DDALINE:
	case ST_WUALIASLINE://对于需要两点控制点的绘图记录起点
		prePointCount=0;
		pointArr[prePointCount++]=point;
		break;
	case DT_POLYGON://对于需要多点控制点的直接记录
		pointArr[prePointCount++]=point;
		break;
	case  DT_POLYLINE:
		pointArr[prePointCount++]=point;
		break;
	case  DT_BEZIER:
		pointArr[prePointCount++]=point;
		break;
	case DT_ARC:
		pointArr[prePointCount++]=point;
		break;
	case DT_GON://左键点击进行喷枪绘制，大小为画笔大小的矩形区域，填充小于等于1/3的像素
		{
			int count=penSize*penSize*0.33;
			for(j=0;j<count;j++)
			{
				int rx=rand()%penSize-penSize/2;
				int ry=rand()%penSize-penSize/2;
				mdc->SetPixelV(point.x+rx,point.y+ry,penColor);
			}
		}
		break;
	case DT_CLEANER://橡皮擦和连续划线一致
		prePointCount=0;
		pointArr[prePointCount++]=point;
		break;
	case  ST_BEZIER://Bezier曲线和多点控制一致
		pointArr[prePointCount++]=point;
		break;
	case ST_POLYLINE://PolyLine折线和多点控制一致
		pointArr[prePointCount++] = point;
		break;
	case ST_CTR_BEZIER://左键按下时获取控制点下标
		stbmoveIndex = -1;
		for (i = 0; i <prePointCount; i++)
		{
			if (sqrt(pow(point.x - pointArr[i].x, 2.0) + pow(point.y - pointArr[i].y, 2.0)) < 3)
			{
				stbmoveIndex = i;
				break;
			}
		}
		
		break;
		case  ST_TRANGLEFILL://三角填充，只要有三个控制点就进行填充区域
			pointArr[prePointCount++]=point;
			if(prePointCount==3)
			{
				HDC hdc=mdc->GetSafeHdc();
				GD2Point p1(pointArr[0].x,pointArr[0].y);
				GD2Point p2(pointArr[1].x,pointArr[1].y);
				GD2Point p3(pointArr[2].x,pointArr[2].y);
				GD2Flat flat(p1,p2,p3);
				GGrating::TrangleFillScanLine(flat,brushColor,hdc);
				prePointCount=0;
			}
		break;
		default:
			return;
	}
	this->Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

void CComputerGraphicsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	isLBtnDown=false;
	switch(drawType)//对于所有两控制点的绘图方式，都采用左键按下点作为起点，左键抬起作为终点交互
	{
	case DT_LINE:
		mdc->MoveTo(pointArr[0]);
		mdc->LineTo(point);
		break;
	case DT_CIRCLE:
		{
			int x=(point.x+pointArr[0].x)/2;
			int y=(point.y+pointArr[0].y)/2;
			int r=sqrt(pow(point.x-pointArr[0].x,2.0)+pow(point.y-pointArr[0].y,2.0))/2;
			mdc->Ellipse(x-r,y-r,x+r,y+r);
		}
		break;
	case DT_ELIPESE:
		mdc->Ellipse(pointArr[0].x,pointArr[0].y,point.x,point.y);
		break;
	case DT_RECT:
		mdc->Rectangle(pointArr[0].x,pointArr[0].y,point.x,point.y);
		break;
	case DT_ROUNDRECT:
		{
					int rh = point.x - pointArr[0].x;
				   int rw = point.y - pointArr[0].y;
				   if (rh < 0)
					   rh = 0 - rh;
				   if (rw < 0)
					   rw = 0 - rw;
				   int r = rh < rw ? rh : rw;
				   r = r / 10;
				   if (r < 5)
					   r = 5;
				   mdc->RoundRect(pointArr[0].x, pointArr[0].y, point.x, point.y, r, r);
		}
		break;
	case ST_DDALINE:
			{
				HDC hdc=mdc->GetSafeHdc();
				GD2Point p1(pointArr[0].x,pointArr[0].y);
				GD2Point p2(point.x,point.y);
				GGrating::DDALine(hdc,p1,p2,penColor);
			}
		break;
	case ST_WUALIASLINE:
		{
				HDC hdc=mdc->GetSafeHdc();
				GD2Point p1(pointArr[0].x,pointArr[0].y);
				GD2Point p2(point.x,point.y);
				GGrating::AntialiasLine(hdc,p1,p2,penColor,mdc->GetBkColor());
		}
		break;
	default://没有进行任何绘图时，左键抬起不触发刷新界面
		return;
	}
	
	this->Invalidate();
	CView::OnLButtonUp(nFlags, point);
}

void CComputerGraphicsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	switch(drawType)//连续曲线，橡皮擦，移动控制点都使用左键按下并移动的方式交互
	{
		case DT_CONLINE:
			if(isLBtnDown)
			{
				mdc->MoveTo(pointArr[0]);
				mdc->LineTo(point);
				pointArr[0]=point;
				prePointCount=1;
			}
			break;
		case DT_CLEANER:
			if(isLBtnDown)
			{
				int x=(point.x+pointArr[0].x)/2;
				int y=(point.y+pointArr[0].y)/2;
				int r=20;
				CPen cPen;//生明画笔
				cPen.CreatePen(PS_SOLID, 1, mdc->GetBkColor());
				CPen * oldPen=mdc->SelectObject(&cPen);
				CBrush brush;
				brush.CreateSolidBrush(mdc->GetBkColor());
				CBrush * oldBrush=mdc->SelectObject(&brush);
				mdc->Ellipse(x-r,y-r,x+r,y+r);
				mdc->SelectObject(oldPen);
				mdc->SelectObject(oldBrush);
			}
		break;
		case ST_CTR_BEZIER:
			if(isLBtnDown && stbmoveIndex!=-1)
			{
				{//清除原来的曲线
					HDC hdc=mdc->GetSafeHdc();
					GD2Point * gdpoints=new GD2Point[prePointCount];
					int i;
					for(i=0;i<prePointCount;i++)
					{
						gdpoints[i].x=pointArr[i].x;
						gdpoints[i].y=pointArr[i].y;
					}
					CPen cPen;//生明画笔
					cPen.CreatePen(PS_SOLID, 1, mdc->GetBkColor());
					CPen * oldPen = mdc->SelectObject(&cPen);
					mdc->Polyline(pointArr, prePointCount);
					mdc->SelectObject(oldPen);
					GGrating::BezierLine(hdc,gdpoints,prePointCount,mdc->GetBkColor());
					delete[] gdpoints;
					
				}
				pointArr[stbmoveIndex]=point;
				{//绘制新的曲线
					HDC hdc=mdc->GetSafeHdc();
					GD2Point * gdpoints=new GD2Point[prePointCount];
					int i;
					for(i=0;i<prePointCount;i++)
					{
						gdpoints[i].x=pointArr[i].x;
						gdpoints[i].y=pointArr[i].y;
					}
					CPen cPen;//生明画笔
					cPen.CreatePen(PS_SOLID, 1, 0x0000ff);
					CPen * oldPen = mdc->SelectObject(&cPen);
					mdc->Polyline(pointArr, prePointCount);
					mdc->SelectObject(oldPen);
					GGrating::BezierLine(hdc,gdpoints,prePointCount,0x0000ff);
					delete[] gdpoints;
					
				}
			}
			break;
		default:
			return;
	}
	this->Invalidate();
	CView::OnMouseMove(nFlags, point);
}

void CComputerGraphicsView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	isRBtnDown=true;
	CView::OnRButtonDown(nFlags, point);
}

void CComputerGraphicsView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	isRBtnDown=false;
	int i=0;
	switch(drawType)
	{
		case DT_POLYGON://对于多边形，只有鼠标右键点击时，才进行绘制，否则都是在增加控制点
			mdc->Polygon(pointArr,prePointCount);
			prePointCount=0;
			break;
		case DT_POLYLINE:
			pointArr[prePointCount]=pointArr[0];
			mdc->Polyline(pointArr,prePointCount+1);
			prePointCount=0;
			break;
		case DT_BEZIER://使用系统提供的Bezier绘制，每3个顶点作为一段进行拼接
			for(i=0;i<prePointCount-3;i+=3)
				mdc->PolyBezier(&pointArr[i],4);
			prePointCount=0;
			break;
		case DT_ARC://画弧线，需要四个控制点，前两个记录内接椭圆，后两个记录逆时针的角度起始点
			if(prePointCount>=4)
			{
				mdc->Arc(pointArr[0].x,pointArr[0].y,pointArr[1].x,pointArr[1].y,
					pointArr[2].x,pointArr[2].y,pointArr[3].x,pointArr[3].y);
				prePointCount=0;
			}
			break;
		case ST_BEZIER://使用自定义高阶Bezier曲线绘制
			{
				HDC hdc=mdc->GetSafeHdc();
				GD2Point * gdpoints=new GD2Point[prePointCount];
				for(i=0;i<prePointCount;i++)
				{
					gdpoints[i].x=pointArr[i].x;
					gdpoints[i].y=pointArr[i].y;
				}
				GGrating::BezierLine(hdc,gdpoints,prePointCount,0x0000ff);
				delete[] gdpoints;
				
			}
			break;
		case ST_POLYLINE:
			{
				CPen cPen;//生明画笔
				cPen.CreatePen(PS_SOLID, 1, 0x0000ff);
				CPen * oldPen = mdc->SelectObject(&cPen);
				mdc->Polyline(pointArr, prePointCount);
				mdc->SelectObject(oldPen);
			}
			break;
		default:
			return;
	}
	this->Invalidate();
	CView::OnRButtonUp(nFlags, point);
}
void CComputerGraphicsView::OnTmfileOpen() 
{
	inputDlg->DoModal();
	CString str=inputDlg->GetInputText();
	if(str.GetLength()==0)
	{
		MessageBox(_T("没有输入文件名"),_T("信息错误"));
		return;
	}
	GTMData gdata;
	gdata.loadTMFile(str.GetBuffer(256));
	if(gdata.isLoadFile()==false)
	{
		MessageBox(_T("文件打开失败或不是TM文件！！"),_T("文件错误"));
	}
	else
	{
		gddata=gdata.data;
		this->Invalidate();
	}
}

void CComputerGraphicsView::OnTmfileSave() 
{
	inputDlg->DoModal();
	CString str=inputDlg->GetInputText();
	if(str.GetLength()==0)
	{
		MessageBox(_T("没有输入文件名"),_T("信息错误"));
		return;
	}
	GTMData gdata;
	gdata.data=gddata;
	if(gdata.saveTMFile(str.GetBuffer(256))==false)
	{
		MessageBox(_T("文件保存失败或权限不足！！"),_T("文件错误"));
	}
}

void CComputerGraphicsView::OnPenColor() 
{
	colorDlg->DoModal();
	penColor=colorDlg->GetColor();
	delete penDraw;
	penDraw=new CPen(0,penSize,penColor);
	mdc->SelectObject(penDraw);
}

void CComputerGraphicsView::OnPenSize() 
{
	sizeDlg->DoModal();
	penSize=sizeDlg->GetSize();
	delete penDraw;
	penDraw=new CPen(0,penSize,penColor);
	mdc->SelectObject(penDraw);
}

void CComputerGraphicsView::OnBrushColor() 
{
	colorDlg->DoModal();
	brushColor=colorDlg->GetColor();
	delete brushDraw;
	brushDraw=new CBrush(brushColor);
	mdc->SelectObject(brushDraw);
}

void CComputerGraphicsView::DrawD3Graph()
{
	if(needShowOrgLine)
	{
		GD3Point op;
		CPoint cp;
		for(int p=0;p<2048;p++)
		{
			op.x=0;
			op.y=0;
			op.z=p;
			cp=GD3PointToCPoint(VaryProjGD3Point(op));
			mdc->SetPixelV(cp.x,cp.y,0xff0000);
			op.x=0;
			op.y=p;
			op.z=0;
			cp=GD3PointToCPoint(VaryProjGD3Point(op));
			mdc->SetPixelV(cp.x,cp.y,0x00ff00);
			op.x=p;
			op.y=0;
			op.z=0;
			cp=GD3PointToCPoint(VaryProjGD3Point(op));
			mdc->SetPixelV(cp.x,cp.y,0x0000ff);
		}
	}
	if(viewType==VT_NONE)
		return;
	if(hideType==HT_ZBUFFER)
	{
		ZBufferDrawGraph();
		return;
	}
	int i;
	if(viewType==VT_POINTCLOUD)
	{
		for(i=0;i<gddata.getPointCount();i++)
		{
			CPoint p=GD3PointToCPoint(VaryProjGD3Point(gddata.pointAt(i)));
			mdc->SetPixelV(p.x,p.y,penColor);
		}
	}
	else if(viewType==VT_LINEAR)
	{
		CPoint arr[4];
		GD3Flat flat;
		for(i=0;i<gddata.getTrangleCount();i++)
		{
			
			GD3Point tp=gddata.pointAt(gddata.trangleAt(i).p1);
			flat.p1=tp;
			arr[0]=GD3PointToCPoint(VaryProjGD3Point( tp ));
			tp=gddata.pointAt(gddata.trangleAt(i).p2);
			flat.p2=tp;
			arr[1]=GD3PointToCPoint(VaryProjGD3Point( tp ));
			tp=gddata.pointAt(gddata.trangleAt(i).p3);
			flat.p3=tp;
			arr[2]=GD3PointToCPoint(VaryProjGD3Point( tp ));
			arr[3]=arr[0];
			if(hideType==HT_BLANK)
			{
				double cosradian=GHideZBuffer::D3FlatBlankingAlgorithm(varyDlg->m_R,GTools::AngleToRadian(varyDlg->m_aAngle),GTools::AngleToRadian(varyDlg->m_bAngle),flat);
				if(cosradian>0)
					mdc->Polyline(arr,4);
			}
			else
			{
				mdc->Polyline(arr,4);
			}
			
		}
	}
	else if(viewType==VT_FALT)
	{
		CPoint arr[4];
		GD3Flat flat;
		for(i=0;i<gddata.getTrangleCount();i++)
		{
			GD3Point tp=gddata.pointAt(gddata.trangleAt(i).p1);
			flat.p1=tp;
			arr[0]=GD3PointToCPoint(VaryProjGD3Point( tp ));
			tp=gddata.pointAt(gddata.trangleAt(i).p2);
			flat.p2=tp;
			arr[1]=GD3PointToCPoint(VaryProjGD3Point( tp ));
			tp=gddata.pointAt(gddata.trangleAt(i).p3);
			flat.p3=tp;
			arr[2]=GD3PointToCPoint(VaryProjGD3Point( tp ));
			GD3NormalLine nl=flat.GetNormalLine();
			if(hideType==HT_BLANK)
			{
				double cosradian=GHideZBuffer::D3FlatBlankingAlgorithm(varyDlg->m_R,GTools::AngleToRadian(varyDlg->m_aAngle),GTools::AngleToRadian(varyDlg->m_bAngle),flat);
				if(cosradian>0)
					if(lightType==LT_OPEN)
					{
						D3Color color=GD3Light::Light(lg_light,flat.p1,lg_viewPoint,nl,lg_mate,lg_amb);
						CPen pen(0,1,RGB(color.red, color.green, color.blue));
						CPen * oldPen=mdc->SelectObject(&pen);
						CBrush brush(RGB(color.red,color.green,color.blue));
						CBrush * oldBrush=mdc->SelectObject(&brush);
						mdc->Polygon(arr,3);
						mdc->SelectObject(oldPen);
						mdc->SelectObject(oldBrush);
					}else
					{
						mdc->Polygon(arr,3);
					}
			}
			else
			{
					if(lightType==LT_OPEN)
					{
						D3Color color=GD3Light::Light(lg_light,flat.p1,lg_viewPoint,nl,lg_mate,lg_amb);
						CPen pen(0,1,RGB(color.red, color.green, color.blue));
						CPen * oldPen=mdc->SelectObject(&pen);
						CBrush brush(RGB(color.red,color.green,color.blue));
						CBrush * oldBrush=mdc->SelectObject(&brush);
						mdc->Polygon(arr,3);
						mdc->SelectObject(oldPen);
						mdc->SelectObject(oldBrush);
					}else
					{
						mdc->Polygon(arr,3);
					}
			}
			
		}
	}
}
void CComputerGraphicsView::ZBufferDrawGraph()
{
	GD3Flat * flats=new GD3Flat[gddata.getTrangleCount()];
	COLORREF * colors=(COLORREF * )malloc(sizeof(COLORREF)*gddata.getTrangleCount());
	int i;
	COLORREF uniformColor=0x0000ff;
	for(i=0;i<gddata.getTrangleCount();i++)
	{
			GD3Point tp=gddata.pointAt(gddata.trangleAt(i).p1);
			flats[i].p1=VaryProjGD3Point( tp );
			tp=gddata.pointAt(gddata.trangleAt(i).p2);
			flats[i].p2=VaryProjGD3Point( tp );
			tp=gddata.pointAt(gddata.trangleAt(i).p3);
			flats[i].p3=VaryProjGD3Point( tp );
			colors[i]=RGB(rand()%156+100,rand()%156+100,rand()%156+100);
	}
	CClientDC dc(this);
	CWnd * wnd=dc.GetWindow();
	CRect rect;
	wnd->GetWindowRect(rect);
	GHideZBuffer::ZBufferAlgorithm(flats,colors,gddata.getTrangleCount(),
		rect.Width(),rect.Height(),mdc->GetSafeHdc(),mdc->GetBkColor());
	delete[] flats;
	free(colors);
}

GD3Point CComputerGraphicsView::VaryProjGD3Point(GD3Point point)
{
	GD3Point retp(point);
	if(varyDlg->m_Switch_Move)
	{
		GD3Vary::Move(&retp,varyDlg->m_Move_x,varyDlg->m_Move_y,varyDlg->m_Move_z);
	}
	if(varyDlg->m_Switch_Scale)
	{
		GD3Vary::Scale(&retp,varyDlg->m_Scale_x,varyDlg->m_Scale_y,varyDlg->m_Scale_z);
	}
	if(varyDlg->m_Switch_Spin)
	{
		GD3Vary::Spin(&retp,GTools::AngleToRadian(varyDlg->m_Spin_x),GTools::AngleToRadian(varyDlg->m_Spin_y),GTools::AngleToRadian(varyDlg->m_Spin_z));
	}
	if(varyDlg->m_Switch_Reflact)
	{
		bool bx=true,by=true,bz=true;
		if(varyDlg->m_Reflact_x==FALSE)
			bx=false;
		if(varyDlg->m_Reflact_y==FALSE)
			by=false;
		if(varyDlg->m_Reflact_z==FALSE)
			bz=false;
		GD3Vary::Reflact(&retp,bx,by,bz);
	}
	if(varyDlg->m_Switch_FlatRef)
	{
		bool bxoy=true,byoz=true,bxoz=true;
		if(varyDlg->m_FlatRef_xoy==FALSE)
			bxoy=false;
		if(varyDlg->m_FlatRef_yoz==FALSE)
			byoz=false;
		if(varyDlg->m_FlatRef_xoz==FALSE)
			bxoz=false;
		GD3Vary::FlatReflact(&retp,bxoy,byoz,bxoz);
	}
	if(varyDlg->m_Switch_Miscut)
	{
		GD3Vary::Miscut(&retp,varyDlg->m_Miscut_xgz,varyDlg->m_Miscut_xdy
			,varyDlg->m_Miscut_yhz,varyDlg->m_Miscut_ybx
			,varyDlg->m_Miscut_zfy,varyDlg->m_Miscut_zcx);
	}
	switch(projType)
	{
	case PT_ORTHOGONAL:
		GProj::Orthogonal(&retp);
		break;
	case PT_MAINVIEW:
		GProj::MainView(&retp);
		GProj::SwapXandZ(&retp);
		break;
	case PT_SIDEVIEW:
		GProj::SideView(&retp);
		GProj::SwapXandZ(&retp);
		break;
	case PT_TOPVIEW:
		GProj::TopView(&retp);
		GProj::SwapXandZ(&retp);
		break;
	case PT_OBLIQUE:
		GProj::Oblique(&retp,GTools::AngleToRadian(varyDlg->m_aAngle),GTools::AngleToRadian(varyDlg->m_bAngle));
		break;
	case PT_WORDTOSCREEN:
		GProj::WorldOrgToScreenOrg(&retp,varyDlg->m_R,varyDlg->m_d,
			GTools::AngleToRadian(varyDlg->m_aAngle),GTools::AngleToRadian(varyDlg->m_bAngle));
		break;
	case PT_ONEPOINT:
		GProj::OnePoint(&retp,varyDlg->m_R,varyDlg->m_d);
		break;
	case PT_TWOPOINT:
		GProj::TwoPoint(&retp,varyDlg->m_R,varyDlg->m_d);
		break;
	case PT_THREEPOINT:
		GProj::ThreePoint(&retp,varyDlg->m_R,varyDlg->m_d);
		break;
	case PT_DEEPSCREEN:
		GProj::ViewOrgToDeepScreenD3Org(&retp, varyDlg->m_d, varyDlg->m_Near, varyDlg->m_Far);
		GProj::ViewOrgToScreenOrg(&retp, varyDlg->m_d);
		break;
	}
	return retp;
}
//以下为菜单响应函数部分
void CComputerGraphicsView::OnMove(int x, int y) 
{
	CView::OnMove(x, y);
}

void CComputerGraphicsView::OnDrawPoint() 
{
	drawType=DT_POINT;
}

void CComputerGraphicsView::OnDrawLine() 
{
	drawType=DT_LINE;
}

void CComputerGraphicsView::OnDrawGon() 
{
	drawType=DT_GON;
}

void CComputerGraphicsView::OnDrawElipese() 
{
	drawType=DT_ELIPESE;
}

void CComputerGraphicsView::OnDrawConline() 
{
	drawType=DT_CONLINE;
}

void CComputerGraphicsView::OnDrawCleaner() 
{
	drawType=DT_CLEANER;
}

void CComputerGraphicsView::OnDrawCircle() 
{
	drawType=DT_CIRCLE;
}

void CComputerGraphicsView::OnDrawBezierline() 
{
	drawType=DT_BEZIER;
}

void CComputerGraphicsView::OnDrawArc() 
{
	drawType=DT_ARC;
}

void CComputerGraphicsView::OnDrawPolygon() 
{
	drawType=DT_POLYGON;
}

void CComputerGraphicsView::OnDrawPolyline() 
{
	drawType=DT_POLYLINE;
}

void CComputerGraphicsView::OnDrawRectangle() 
{
	drawType=DT_RECT;
}

void CComputerGraphicsView::OnDrawNull() 
{
	drawType=DT_NULL;
}

void CComputerGraphicsView::OnDrawRoundrect() 
{
	drawType=DT_ROUNDRECT;
}


void CComputerGraphicsView::OnDismodFlat() 
{
	viewType=VT_FALT;
	this->Invalidate();
}

void CComputerGraphicsView::OnDismodLinear() 
{
	viewType=VT_LINEAR;
	this->Invalidate();
}

void CComputerGraphicsView::OnDismodPointcloud() 
{
	viewType=VT_POINTCLOUD;
	this->Invalidate();
}

CPoint CComputerGraphicsView::GD3PointToCPoint(GD3Point & p)
{
	CPoint rp(p.x,p.y);
	return rp;
}

void CComputerGraphicsView::OnDismodCleanpainter() 
{
	needCleanPainter=true;
	this->Invalidate();
}

void CComputerGraphicsView::OnGeomodBall() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateBall(geomodDlg->m_r,geomodDlg->m_aAngleCount,geomodDlg->m_bAngleCount);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnGeomodCone() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateCone(geomodDlg->m_h,geomodDlg->m_r,geomodDlg->m_hCount,geomodDlg->m_rCount,geomodDlg->m_rAngleCount);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnGeomodCylinder() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateCylinder(geomodDlg->m_r,geomodDlg->m_h,geomodDlg->m_rCount,geomodDlg->m_hCount,geomodDlg->m_rAngleCount);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnGeomodDodec() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateDodecahedron(geomodDlg->m_a);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnGeomodHex() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateHexahedron(geomodDlg->m_a);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnGeomodIcos() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateIcosahedron(geomodDlg->m_a);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnGeomodOct() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateOctahedron(geomodDlg->m_a);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnGeomodTetr() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateTetrahedron(geomodDlg->m_a);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnGeomodTorus() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateTorus(geomodDlg->m_r,geomodDlg->m_r2,geomodDlg->m_aAngleCount,geomodDlg->m_bAngleCount);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnTranglelized() 
{
	GD3DataGroup * pd=GTeanglelized::PointsTranglelized(&gddata);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}

void CComputerGraphicsView::OnLinemodeBezier() 
{
	drawType=ST_BEZIER;
	editBakDrawType = drawType;
	prePointCount=0;
	needShowCtrlPoint=false;
}

void CComputerGraphicsView::OnLinemodePolyline()
{
	drawType = ST_POLYLINE;
	editBakDrawType = drawType;
	prePointCount = 0;
	needShowCtrlPoint = false;
}

void CComputerGraphicsView::OnLinemodEdit() 
{
	if (drawType != ST_CTR_BEZIER){
		editBakDrawType = drawType;
	}
	drawType=ST_CTR_BEZIER;
	needShowCtrlPoint=true;
	this->Invalidate();
}

void CComputerGraphicsView::OnScandisDdaline() 
{
	drawType=ST_DDALINE;
}

void CComputerGraphicsView::OnScandisAntialiasline() 
{
	drawType=ST_WUALIASLINE;
}

void CComputerGraphicsView::OnScanSeedfill() 
{
	drawType=ST_SEENDFILL;
}

void CComputerGraphicsView::OnScanTranglefill() 
{
	drawType=ST_TRANGLEFILL;
}

void CComputerGraphicsView::OnGraphVary() 
{
	varyDlg->DoModal();
	this->Invalidate();
}

void CComputerGraphicsView::OnProjDeepscreen() 
{
	projType=PT_DEEPSCREEN;
	this->Invalidate();
	
}

void CComputerGraphicsView::OnProjMainview() 
{
	projType=PT_MAINVIEW;
	this->Invalidate();
}

void CComputerGraphicsView::OnProjOblique() 
{
	projType=PT_OBLIQUE;
	this->Invalidate();
}

void CComputerGraphicsView::OnProjOnepoint() 
{
	projType=PT_ONEPOINT;
	this->Invalidate();
}

void CComputerGraphicsView::OnProjOrthogonal() 
{
	projType=PT_ORTHOGONAL;
	this->Invalidate();
}

void CComputerGraphicsView::OnProjSideview() 
{
	projType=PT_SIDEVIEW;
	this->Invalidate();
}

void CComputerGraphicsView::OnProjThreepoint() 
{
	projType=PT_THREEPOINT;
	this->Invalidate();
}

void CComputerGraphicsView::OnProjTopview() 
{
	projType=PT_TOPVIEW;
	this->Invalidate();
}

void CComputerGraphicsView::OnProjTwopoint() 
{
	projType=PT_TWOPOINT;
	this->Invalidate();
}

void CComputerGraphicsView::OnProjWordtoscreen() 
{
	projType=PT_WORDTOSCREEN;
	this->Invalidate();
}

void CComputerGraphicsView::OnModhideBackremove() 
{
	hideType=HT_BLANK;
	this->Invalidate();
}

void CComputerGraphicsView::OnModhideDeepbuff() 
{
	hideType=HT_ZBUFFER;
	this->Invalidate();
}

void CComputerGraphicsView::OnModhideNone() 
{
	hideType=HT_NONE;
	this->Invalidate();
}

void CComputerGraphicsView::OnModlightFlat() 
{
	lightType=LT_OPEN;
	this->Invalidate();
}


void CComputerGraphicsView::OnModlightNone() 
{
	lightType=LT_NONE;
	this->Invalidate();
}

void CComputerGraphicsView::OnModlightMateriaex() 
{
	metaDlg->DoModal();
	lg_mate=metaDlg->GetMaterial();
	this->Invalidate();
}

void CComputerGraphicsView::OnModlightLight() 
{
	lightDlg->DoModal();
	lg_light=lightDlg->GetLight();
	this->Invalidate();
}

void CComputerGraphicsView::OnOperationTips() 
{
	opetipDlg->DoModal();
}

void CComputerGraphicsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	
	switch(nChar)
	{
	case VK_F5:// F5清空其他绘图，只保留三维模型
		needCleanPainter=true;
		this->Invalidate();
		break;
	case VK_LEFT:// 左右键进行X轴左右移动
		varyDlg->m_Switch_Move=TRUE;
		varyDlg->m_Move_x-=10;
		needCleanPainter=true;
		this->Invalidate();
		break;
	case VK_RIGHT:
		varyDlg->m_Switch_Move=TRUE;
		varyDlg->m_Move_x+=10;
		needCleanPainter=true;
		this->Invalidate();
		break;
	case VK_UP:// 上下键进行Y轴上下移动，Shift+上下进行Z轴上下移动
		if(isShiftDown)
		{
			varyDlg->m_Switch_Move=TRUE;
			varyDlg->m_Move_z+=10;
		}
		else
		{
			varyDlg->m_Switch_Move=TRUE;
			varyDlg->m_Move_y+=10;
		}
		needCleanPainter=true;
		this->Invalidate();
		break;
	case VK_DOWN:
		if(isShiftDown)
		{
			varyDlg->m_Switch_Move=TRUE;
			varyDlg->m_Move_z-=10;
		}
		else
		{
			varyDlg->m_Switch_Move=TRUE;
			varyDlg->m_Move_y-=10;
		}
		needCleanPainter=true;
		this->Invalidate();
		break;
	case VK_SHIFT:
		isShiftDown=true;
		break;
	case 'X':// Shift+X/Y/Z轴反射
		isXDown=true;
		if(isShiftDown)
		{
			varyDlg->m_Switch_Reflact=TRUE;
			varyDlg->m_Reflact_x=!varyDlg->m_Reflact_x;
			needCleanPainter=true;
			this->Invalidate();
		}
		break;
	case 'Y':
		isYDown=true;
		if(isShiftDown)
		{
			varyDlg->m_Switch_Reflact=TRUE;
			varyDlg->m_Reflact_y=!varyDlg->m_Reflact_y;
			needCleanPainter=true;
			this->Invalidate();
		}
		break;
	case 'Z':
		isZDown=true;
		if(isShiftDown)
		{
			varyDlg->m_Switch_Reflact=TRUE;
			varyDlg->m_Reflact_z=!varyDlg->m_Reflact_z;
			needCleanPainter=true;
			this->Invalidate();
		}
		break;
	case VK_F1:// 显示帮助对话框
		opetipDlg->DoModal();
		break;
	case VK_F2:// F2-F4对XOY，YOZ，XOZ平面反射
		varyDlg->m_Switch_FlatRef=TRUE;
		varyDlg->m_FlatRef_xoy=!varyDlg->m_FlatRef_xoy;
		needCleanPainter=true;
		this->Invalidate();
		break;
	case VK_F3:
		varyDlg->m_Switch_FlatRef=TRUE;
		varyDlg->m_FlatRef_yoz=!varyDlg->m_FlatRef_yoz;
		needCleanPainter=true;
		this->Invalidate();
		break;
	case VK_F4:
		varyDlg->m_Switch_FlatRef=TRUE;
		varyDlg->m_FlatRef_xoz=!varyDlg->m_FlatRef_xoz;
		needCleanPainter=true;
		this->Invalidate();
		break;

	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CComputerGraphicsView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	
	switch(nChar)
	{
	case VK_SHIFT:
		isShiftDown=false;
		break;
	case 'X':
		isXDown=false;
		break;
	case 'Y':
		isYDown=false;
		break;
	case 'Z':
		isZDown=false;
		break;
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CComputerGraphicsView::OnCartonSetting() 
{
	cartonDlg->DoModal();
	if(cartonDlg->m_openCarton)
	{
		KillTimer(ID_TIMER_CARTON);
		varyDlg->m_Switch_Spin=TRUE;
		SetTimer(ID_TIMER_CARTON,cartonDlg->m_updataTime,NULL);
	}
	else
	{
		varyDlg->m_Switch_Spin=FALSE;
		KillTimer(ID_TIMER_CARTON);
	}
	
}

void CComputerGraphicsView::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==ID_TIMER_CARTON)
	{
		if(cartonDlg->m_openCarton)
		{
			if(cartonDlg->m_spinX)
			{
				varyDlg->m_Spin_x+=cartonDlg->m_spinXup;
				if(varyDlg->m_Spin_x>360)
					varyDlg->m_Spin_x-=360;
			}
			if(cartonDlg->m_spinY)
			{
				varyDlg->m_Spin_y+=cartonDlg->m_spinYup;
				if(varyDlg->m_Spin_y>360)
					varyDlg->m_Spin_y-=360;
			}
			if(cartonDlg->m_spinZ)
			{
				varyDlg->m_Spin_z+=cartonDlg->m_spinZup;
				if(varyDlg->m_Spin_z>360)
					varyDlg->m_Spin_z-=360;
			}
			needCleanPainter=true;
			this->Invalidate();
		}
	}
	CView::OnTimer(nIDEvent);
}

void CComputerGraphicsView::OnDismodNone() 
{
	viewType=VT_NONE;
	this->Invalidate();
}

void CComputerGraphicsView::OnLinemodBezieryspin() 
{
	if(prePointCount>0)
	{
		geomodDlg->DoModal();
		CRect rect;
		this->GetWindowRect(rect);
		int wndhei=rect.Height();
		GD2Point * points=new GD2Point[prePointCount];
		for(int i=0;i<prePointCount;i++)
		{
			points[i].x=pointArr[i].x;
			points[i].y=wndhei-pointArr[i].y;
		}
		GD3DataGroup* pd = NULL;
		if (editBakDrawType == ST_POLYLINE){
			pd = GGrating::CreatePolyLineSpinYCube(points, prePointCount, geomodDlg->m_Bezier_tCount, geomodDlg->m_Bezier_rAngleCount);
		}
		else{
			pd=GGrating::CreateBezierSpinYCube(points, prePointCount, geomodDlg->m_Bezier_tCount, geomodDlg->m_Bezier_rAngleCount);
		}
		gddata=*pd;
		delete pd;
		delete points;
		this->Invalidate();
	}
}

void CComputerGraphicsView::OnLinemodBezierxspin() 
{
	if(prePointCount>0)
	{
		geomodDlg->DoModal();
		GD2Point * points=new GD2Point[prePointCount];
		for(int i=0;i<prePointCount;i++)
		{
			points[i].x=pointArr[i].x;
			points[i].y=pointArr[i].y;
		}
		GD3DataGroup* pd = NULL;
		if (editBakDrawType == ST_POLYLINE){
			pd = GGrating::CreatePolyLineSpinXCube(points, prePointCount, geomodDlg->m_Bezier_tCount, geomodDlg->m_Bezier_rAngleCount);
		}
		else {
			pd=GGrating::CreateBezierSpinXCube(points, prePointCount, geomodDlg->m_Bezier_tCount, geomodDlg->m_Bezier_rAngleCount);
		}
		gddata=*pd;
		delete pd;
		delete points;
		this->Invalidate();
	}
}

void CComputerGraphicsView::OnShowOrgline() 
{
	needShowOrgLine=true;
	this->Invalidate();
}

void CComputerGraphicsView::OnHideOrgline() 
{
	needShowOrgLine=false;
	this->Invalidate();
	
}


BOOL CComputerGraphicsView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if(isXDown)// 按住X/Y/Z按键再滚动鼠标，进行轴旋转
	{
		varyDlg->m_Switch_Spin=TRUE;
		if(zDelta>0)
		{
			varyDlg->m_Spin_x=(varyDlg->m_Spin_x+5)%360;
		}else
		{
			varyDlg->m_Spin_x-=5;
			if(varyDlg->m_Spin_x<0)
				varyDlg->m_Spin_x=360-varyDlg->m_Spin_x;
		}
		needCleanPainter=true;
		this->Invalidate();
	}
	else if(isYDown)
	{
		varyDlg->m_Switch_Spin=TRUE;
		if(zDelta>0)
		{
			varyDlg->m_Spin_y=(varyDlg->m_Spin_y+5)%360;
		}else
		{
			varyDlg->m_Spin_y-=5;
			if(varyDlg->m_Spin_y<0)
				varyDlg->m_Spin_y=360-varyDlg->m_Spin_y;
		}
		needCleanPainter=true;
		this->Invalidate();
	}
	else if(isZDown)
	{
		varyDlg->m_Switch_Spin=TRUE;
		if(zDelta>0)
		{
			varyDlg->m_Spin_z=(varyDlg->m_Spin_z+5)%360;
		}else
		{
			varyDlg->m_Spin_z-=5;
			if(varyDlg->m_Spin_z<0)
				varyDlg->m_Spin_z=360-varyDlg->m_Spin_z;
		}
		needCleanPainter=true;
		this->Invalidate();
	}
	else // 鼠标滚动，进行图形缩放
	{
		varyDlg->m_Switch_Scale=TRUE;
		if(zDelta>0)
		{
			varyDlg->m_Scale_x*=1.1;
			varyDlg->m_Scale_y*=1.1;
			varyDlg->m_Scale_z*=1.1;
		}else
		{
			varyDlg->m_Scale_x*=0.9;
			varyDlg->m_Scale_y*=0.9;
			varyDlg->m_Scale_z*=0.9;
		}
		needCleanPainter=true;
		this->Invalidate();
	}
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CComputerGraphicsView::OnOperationBaseope() 
{
	baseOpeDlg->DoModal();
}

void CComputerGraphicsView::OnGeomodBallex() 
{
	geomodDlg->DoModal();
	GD3DataGroup * pd=GStereo::CreateBallEx(geomodDlg->m_r,geomodDlg->m_ballex_Level);
	gddata=*pd;
	delete pd;
	this->Invalidate();
}



