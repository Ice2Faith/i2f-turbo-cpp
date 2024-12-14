
// 07-三维模型几何变换及投影View.cpp : CMy07三维模型几何变换及投影View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "07-三维模型几何变换及投影.h"
#endif

#include "07-三维模型几何变换及投影Doc.h"
#include "07-三维模型几何变换及投影View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include"D3Graph.h"
#include"ThrDimGraph.h"
double AngleToRadian(double a)
{
	return a / 180.0*3.1415926535;
}
void CMy07三维模型几何变换及投影View::DrawGraph(CDC * pDC)
{
	if (m_isload == false)
		return;
	if (m_projType == PT_Null)
		return;
	double x = 0, y = 0, z = 0;
	
	if (m_drawType == 0)
	{
		for (int i = 0; i < m_pointcount; i++)
		{
			x = m_points[i][0];
			y = m_points[i][1];
			z = m_points[i][2];
			ProjToScreen(&x,&y,z);
			pDC->SetPixelV(x, y, m_pointColor);

		}
	}
	else if (m_drawType == 1)
	{
		CPoint arr[4];
		for (int i = 0; i<this->m_tranglecount; i++)
		{
			for (int j = 0; j<3; j++)
			{
				x = m_points[this->m_trangle[i][j]][0];
				y = m_points[this->m_trangle[i][j]][1];
				z = m_points[this->m_trangle[i][j]][2];
				ProjToScreen(&x, &y, z);
				arr[j].x = x;
				arr[j].y = y;
			}
			arr[3] = arr[0];
			pDC->Polyline(arr, 4);
		}
	}
	
}
void CMy07三维模型几何变换及投影View::ProjToScreen(double * rx, double * ry, double vz)
{
	double x = *rx,y=*ry,z=vz;
	if (VT_Move&m_varyType)
		GraphMove(&x, &y, &z, m_move_x, m_move_y, m_move_z);
	if (VT_Scale&m_varyType)
		GraphScale(&x, &y, &z, m_scale_x, m_scale_y, m_scale_z);
	if (VT_Spin&m_varyType)
		GraphSpin(&x, &y, &z, m_spin_x, m_spin_y, m_spin_z);
	if (VT_Reflact&m_varyType)
		GraphReflact(&x, &y, &z, m_reflact_x, m_reflact_y, m_reflact_z);
	if (VT_FlatReflact&m_varyType)
		GraphFlatReflact(&x, &y, &z, m_flat_refalct_xoy, m_flat_refalct_yoz, m_flat_refalct_xoz);
	if (VT_Miscut&m_varyType)
		GraphMiscut(&x, &y, &z, m_miscut_xgz, m_miscut_xdy, m_miscut_yhz, m_miscut_ybx, m_miscut_zfy, m_miscut_zcx);

	switch (m_projType)
	{
	case PT_Orthogonal:
		ProjOrthogonal(&x, &y, &z);
		break;
	case PT_MainView:
		ProjMainView(&x, &y, &z);
		x = y;
		y = z;
		break;
	case PT_SideView:
		ProjSideView(&x, &y, &z);
		x = y;
		y = z;
		break;
	case PT_TopView:
		ProjTopView(&x, &y, &z);
		x = y;
		y = z;
		break;
	case PT_Oblique:
		ProjOblique(&x, &y, &z, AngleToRadian(m_aAngle), AngleToRadian(m_bAngle));
		break;
	case PT_WorldOrgToScreenOrg:
		ProjWorldOrgToScreenOrg(&x, &y, &z, m_R, m_d, AngleToRadian(m_aAngle), AngleToRadian(m_bAngle));
		break;
	case PT_OnePoint:
		ProjOnePoint(&x, &y, &z, m_R, m_d);
		break;
	case PT_TwoPoint:
		ProjTwoPoint(&x, &y, &z, m_R, m_d);
		break;
	case PT_ThreePoint:
		ProjThreePoint(&x, &y, &z, m_R, m_d);
		break;
	case PT_ViewOrgToDeepScreenD3Org:
		ProjViewOrgToDeepScreenD3Org(&x, &y, &z, m_d, m_Near, m_Far);
		ProjViewOrgToScreenOrg(&x, &y, &z, m_d);
		break;
	}
	*rx = x;
	*ry = y;
}
CMy07三维模型几何变换及投影View::CMy07三维模型几何变换及投影View()
: m_drawType(0)
{
	// TODO:  在此处添加构造代码
	m_aAngle = 60;
	m_bAngle = 30;
	m_R = 200;
	m_d = 80;
	m_Near = 20;
	m_Far = 300;
	m_pointColor = 0x0000ff;
	m_projType = PT_OnePoint;
	m_varyType = VT_Null;
	m_move_x = 0, m_move_y = 0, m_move_z = 0;
	m_scale_x = 1, m_scale_y = 1, m_scale_z = 1;
	m_spin_x = 0, m_spin_y = 0, m_spin_z = 0;
	m_reflact_x = false, m_reflact_y = false, m_reflact_z = false;
	m_flat_refalct_xoy = false, m_flat_refalct_yoz = false, m_flat_refalct_xoz = false;
	m_miscut_xgz = 0, m_miscut_xdy = 0, m_miscut_yhz = 0, m_miscut_ybx = 0, m_miscut_zfy = 0, m_miscut_zcx = 0;
	m_isload = false;
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_isload = LoadTMFile("..\\Bunny.tm");

}
// CMy07三维模型几何变换及投影View

IMPLEMENT_DYNCREATE(CMy07三维模型几何变换及投影View, CView)

BEGIN_MESSAGE_MAP(CMy07三维模型几何变换及投影View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMy07三维模型几何变换及投影View::OnProjOrthogonal)
	ON_COMMAND(ID_32772, &CMy07三维模型几何变换及投影View::OnProjMainView)
	ON_COMMAND(ID_32773, &CMy07三维模型几何变换及投影View::OnProjSideView)
	ON_COMMAND(ID_32774, &CMy07三维模型几何变换及投影View::OnProjTopView)
	ON_COMMAND(ID_32775, &CMy07三维模型几何变换及投影View::OnProjOblique)
	ON_COMMAND(ID_32776, &CMy07三维模型几何变换及投影View::OnProjWorldOrgToScreenOrg)
	ON_COMMAND(ID_32777, &CMy07三维模型几何变换及投影View::OnProjOnePoint)
	ON_COMMAND(ID_32778, &CMy07三维模型几何变换及投影View::OnProjTwoPoint)
	ON_COMMAND(ID_32779, &CMy07三维模型几何变换及投影View::OnProjThreePoint)
	ON_COMMAND(ID_32780, &CMy07三维模型几何变换及投影View::OnViewOrgToDeepScreenD3Org)
	ON_COMMAND(ID_Menu, &CMy07三维模型几何变换及投影View::OnMenuSetting)
	ON_COMMAND(ID_32782, &CMy07三维模型几何变换及投影View::OndrawTypePoint)
	ON_COMMAND(ID_32783, &CMy07三维模型几何变换及投影View::OndrawTypeLine)
END_MESSAGE_MAP()

// CMy07三维模型几何变换及投影View 构造/析构
void CMy07三维模型几何变换及投影View::ResetCenterOrg(CDC * pDC)
{
	//中央坐标系
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(rect.right, -rect.bottom);
}

bool CMy07三维模型几何变换及投影View::LoadTMFile(char * filename)
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



CMy07三维模型几何变换及投影View::~CMy07三维模型几何变换及投影View()
{
}
// CMy07三维模型几何变换及投影View 绘制

void CMy07三维模型几何变换及投影View::OnDraw(CDC* pDC)
{
	CMy07三维模型几何变换及投影Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	CPen pen(0,1,0x00ff00);
	pDC->SelectObject(&pen);
	ResetCenterOrg(pDC);
	DrawGraph(pDC);
}
BOOL CMy07三维模型几何变换及投影View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}




// CMy07三维模型几何变换及投影View 打印

BOOL CMy07三维模型几何变换及投影View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy07三维模型几何变换及投影View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMy07三维模型几何变换及投影View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMy07三维模型几何变换及投影View 诊断

#ifdef _DEBUG
void CMy07三维模型几何变换及投影View::AssertValid() const
{
	CView::AssertValid();
}

void CMy07三维模型几何变换及投影View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy07三维模型几何变换及投影Doc* CMy07三维模型几何变换及投影View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy07三维模型几何变换及投影Doc)));
	return (CMy07三维模型几何变换及投影Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy07三维模型几何变换及投影View 消息处理程序


void CMy07三维模型几何变换及投影View::OnProjOrthogonal()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_Orthogonal;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OnProjMainView()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_MainView;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OnProjSideView()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_SideView;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OnProjTopView()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_TopView;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OnProjOblique()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_Oblique;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OnProjWorldOrgToScreenOrg()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_WorldOrgToScreenOrg;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OnProjOnePoint()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_OnePoint;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OnProjTwoPoint()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_TwoPoint;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OnProjThreePoint()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_ThreePoint;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OnViewOrgToDeepScreenD3Org()
{
	// TODO:  在此添加命令处理程序代码
	m_projType = PT_ViewOrgToDeepScreenD3Org;
	Invalidate();
}

void Wchar_t2Char(wchar_t Wchar[], char Char[])
{
	int size = WideCharToMultiByte(CP_ACP, 0, Wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Wchar, -1, Char, size, NULL, NULL);
}
void CMy07三维模型几何变换及投影View::OnMenuSetting()
{
	// TODO:  在此添加命令处理程序代码
	dlg.DoModal();
	if (dlg.m_applyed == false)
		return;
	else
		dlg.m_applyed = false;
	this->m_aAngle= dlg.m_aAngle;
	this->m_bAngle= dlg.m_bAngle;
	this ->m_R= dlg.m_R;
	this ->m_d= dlg.m_d;
	this ->m_Near= dlg.m_Near;
	this ->m_Far= dlg.m_Far;
	this->m_varyType = VT_Null;
	if(dlg.m_b_move)
		this->m_varyType |=VT_Move;
	this ->m_move_x= dlg.m_move_x;
	this ->m_move_y= dlg.m_move_y;
	this ->m_move_z= dlg.m_move_z;
	if (dlg.m_b_scale)
		this->m_varyType |= VT_Scale;
	this ->m_scale_x= dlg.m_scale_x;
	this ->m_scale_y= dlg.m_scale_y;
	this ->m_scale_z= dlg.m_scale_z;
	if (dlg.m_b_spin)
		this->m_varyType |= VT_Spin;
	this ->m_spin_x= dlg.m_spin_x;
	this ->m_spin_y= dlg.m_spin_y;
	this ->m_spin_z= dlg.m_spin_z;
	if(dlg.m_b_reflact)
		this->m_varyType |= VT_Reflact;
	if (dlg.m_b_reflact_x)
		this->m_reflact_x = true;
	else
		this->m_reflact_x = false;
	if(dlg.m_b_reflact_y)
		this->m_reflact_y = true;
	else
		this->m_reflact_y = false;
	if(dlg.m_b_reflact_z)
		this->m_reflact_z = true;
	else
		this->m_reflact_z = false;
	if(dlg.m_b_flat_reflact)
		this->m_varyType |= VT_FlatReflact;
	if (dlg.m_b_flat_reflact_xoy)
		this->m_flat_refalct_xoy = true;
	else
		this->m_flat_refalct_xoy = false;
	if(dlg.m_b_flat_reflact_yoz)
		this->m_flat_refalct_yoz = true;
	else
		this->m_flat_refalct_yoz = false;
	if(dlg.m_b_flat_reflact_xoz)
		this->m_flat_refalct_xoz = true;
	else
		this->m_flat_refalct_xoz = false;
	if(dlg.m_b_miscut)
		this->m_varyType |= VT_Miscut;
	this ->m_miscut_xgz= dlg.m_miscut_xgz;
	this ->m_miscut_xdy= dlg.m_miscut_xdy;
	this ->m_miscut_yhz= dlg.m_miscut_yhz;
	this ->m_miscut_ybx= dlg.m_miscut_ybx;
	this ->m_miscut_zfy= dlg.m_miscut_zfy;
	this ->m_miscut_zcx= dlg.m_miscut_zcx;
	if (dlg.m_b_loadFile)
	{
		if (dlg.m_filePath.Trim().GetLength() > 0)
		{
			char filename[300] = { 0 };
			Wchar_t2Char(dlg.m_filePath.Trim().GetBuffer(),filename);
			ReLoadDrawData(filename);
			dlg.m_filePath.Empty();
		}
		dlg.m_b_loadFile = FALSE;
		dlg.UpdateData();
	}
	Invalidate();
}
void CMy07三维模型几何变换及投影View::ReLoadDrawData(char * filename)
{
	ClearDrawData();
	m_pointcount = 0;
	m_tranglecount = 0;
	m_points = NULL;
	m_trangle = NULL;
	m_isload = LoadTMFile(filename);
}

void CMy07三维模型几何变换及投影View::ClearDrawData()
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

void CMy07三维模型几何变换及投影View::OndrawTypePoint()
{
	// TODO:  在此添加命令处理程序代码
	m_drawType = 0;
	Invalidate();
}


void CMy07三维模型几何变换及投影View::OndrawTypeLine()
{
	// TODO:  在此添加命令处理程序代码
	m_drawType = 1;
	Invalidate();
}
