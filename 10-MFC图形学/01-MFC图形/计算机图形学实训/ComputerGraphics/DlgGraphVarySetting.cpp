// DlgGraphVarySetting.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgGraphVarySetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgGraphVarySetting dialog


DlgGraphVarySetting::DlgGraphVarySetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGraphVarySetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGraphVarySetting)
	m_FlatRef_xoy = FALSE;
	m_FlatRef_xoz = FALSE;
	m_FlatRef_yoz = FALSE;
	m_Reflact_x = FALSE;
	m_Reflact_y = FALSE;
	m_Reflact_z = FALSE;
	m_Miscut_xdy = 0;
	m_Miscut_xgz = 0;
	m_Miscut_ybx = 0;
	m_Miscut_yhz = 0;
	m_Miscut_zfy = 0;
	m_Miscut_zcx = 0;
	m_Move_x = 0;
	m_Move_y = 0;
	m_Move_z = 0;
	m_Scale_x = 1.0;
	m_Scale_y = 1.0;
	m_Scale_z = 1.0;
	m_Spin_x = 0;
	m_Spin_y = 0;
	m_Spin_z = 0;
	m_aAngle = 30;
	m_bAngle = 60;
	m_d = 200;
	m_Far = 800;
	m_R = 500;
	m_Near = 200;
	m_Switch_Miscut = FALSE;
	m_Switch_Move = FALSE;
	m_Switch_Reflact = FALSE;
	m_Switch_Scale = FALSE;
	m_Switch_Spin = FALSE;
	m_Switch_FlatRef = FALSE;
	//}}AFX_DATA_INIT
}


void DlgGraphVarySetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGraphVarySetting)
	DDX_Check(pDX, IDC_CHECK_GFLATREFXOY, m_FlatRef_xoy);
	DDX_Check(pDX, IDC_CHECK_GFLATREFXOZ, m_FlatRef_xoz);
	DDX_Check(pDX, IDC_CHECK_GFLATREFYOZ, m_FlatRef_yoz);
	DDX_Check(pDX, IDC_CHECK_GREFLACTX, m_Reflact_x);
	DDX_Check(pDX, IDC_CHECK_GREFLACTY, m_Reflact_y);
	DDX_Check(pDX, IDC_CHECK_GREFLACTZ, m_Reflact_z);
	DDX_Text(pDX, IDC_EDIT_GMISCUTXDY, m_Miscut_xdy);
	DDX_Text(pDX, IDC_EDIT_GMISCUTXGZ, m_Miscut_xgz);
	DDX_Text(pDX, IDC_EDIT_GMISCUTYBX, m_Miscut_ybx);
	DDX_Text(pDX, IDC_EDIT_GMISCUTYHZ, m_Miscut_yhz);
	DDX_Text(pDX, IDC_EDIT_GMISCUTZFY, m_Miscut_zfy);
	DDX_Text(pDX, IDC_EDIT_GMISCUTZCX, m_Miscut_zcx);
	DDX_Text(pDX, IDC_EDIT_GMOVEX, m_Move_x);
	DDX_Text(pDX, IDC_EDIT_GMOVEY, m_Move_y);
	DDX_Text(pDX, IDC_EDIT_GMOVEZ, m_Move_z);
	DDX_Text(pDX, IDC_EDIT_GSCALEX, m_Scale_x);
	DDX_Text(pDX, IDC_EDIT_GSCALEY, m_Scale_y);
	DDX_Text(pDX, IDC_EDIT_GSCALEZ, m_Scale_z);
	DDX_Text(pDX, IDC_EDIT_GSPINX, m_Spin_x);
	DDX_Text(pDX, IDC_EDIT_GSPINY, m_Spin_y);
	DDX_Text(pDX, IDC_EDIT_GSPINZ, m_Spin_z);
	DDX_Text(pDX, IDC_EDIT_PROJAANGLE, m_aAngle);
	DDX_Text(pDX, IDC_EDIT_PROJBANGLE, m_bAngle);
	DDX_Text(pDX, IDC_EDIT_VIEWD, m_d);
	DDX_Text(pDX, IDC_EDIT_VIEWDFAR, m_Far);
	DDX_Text(pDX, IDC_EDIT_VIEWR, m_R);
	DDX_Text(pDX, IDC_EDIT_VIEWRNEAR, m_Near);
	DDX_Check(pDX, IDC_CHECK_MISCUT, m_Switch_Miscut);
	DDX_Check(pDX, IDC_CHECK_MOVE, m_Switch_Move);
	DDX_Check(pDX, IDC_CHECK_REFLACT, m_Switch_Reflact);
	DDX_Check(pDX, IDC_CHECK_SCALE, m_Switch_Scale);
	DDX_Check(pDX, IDC_CHECK_SPIN, m_Switch_Spin);
	DDX_Check(pDX, IDC_CHECK_FALTREF, m_Switch_FlatRef);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGraphVarySetting, CDialog)
	//{{AFX_MSG_MAP(DlgGraphVarySetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgGraphVarySetting message handlers

void DlgGraphVarySetting::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);

	CDialog::OnOK();
}

void DlgGraphVarySetting::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL DlgGraphVarySetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
