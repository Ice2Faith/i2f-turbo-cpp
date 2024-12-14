// DlgGeoModCreateSetting.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgGeoModCreateSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgGeoModCreateSetting dialog


DlgGeoModCreateSetting::DlgGeoModCreateSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGeoModCreateSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGeoModCreateSetting)
	m_a = 200;
	m_bAngleCount = 120;
	m_aAngleCount = 120;
	m_h = 300;
	m_hCount = 100;
	m_r = 220;
	m_rCount = 50;
	m_r2 = 80;
	m_rAngleCount = 120;
	m_Bezier_tCount = 30;
	m_Bezier_rAngleCount = 50;
	m_ballex_Level = 3;
	//}}AFX_DATA_INIT
}


void DlgGeoModCreateSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGeoModCreateSetting)
	DDX_Text(pDX, IDC_EDIT_A, m_a);
	DDX_Text(pDX, IDC_EDIT_BANGLECOUNT, m_bAngleCount);
	DDX_Text(pDX, IDC_EDIT_AANGLECOUNT, m_aAngleCount);
	DDX_Text(pDX, IDC_EDIT_H, m_h);
	DDX_Text(pDX, IDC_EDIT_HCOUNT, m_hCount);
	DDX_Text(pDX, IDC_EDIT_R, m_r);
	DDX_Text(pDX, IDC_EDIT_RCOUNT, m_rCount);
	DDX_Text(pDX, IDC_EDIT_RTWO, m_r2);
	DDX_Text(pDX, IDC_EDIT_RANGLECOUNT, m_rAngleCount);
	DDX_Text(pDX, IDC_EDIT_BEZIER_TCOUNT, m_Bezier_tCount);
	DDX_Text(pDX, IDC_EDIT_BEZIER_RANGLECOUNT, m_Bezier_rAngleCount);
	DDX_Text(pDX, IDC_EDIT_BALLEX_LEVEL, m_ballex_Level);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGeoModCreateSetting, CDialog)
	//{{AFX_MSG_MAP(DlgGeoModCreateSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgGeoModCreateSetting message handlers

void DlgGeoModCreateSetting::OnCancel() 
{
	// TODO: Add extra cleanup here
	this->UpdateData(TRUE);
	CDialog::OnCancel();
}

void DlgGeoModCreateSetting::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
