// DlgCartonSetting.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgCartonSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCartonSetting dialog


DlgCartonSetting::DlgCartonSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCartonSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCartonSetting)
	m_openCarton = FALSE;
	m_spinX = FALSE;
	m_spinY = FALSE;
	m_spinZ = FALSE;
	m_spinXup = 1;
	m_spinYup = 2;
	m_spinZup = 3;
	m_updataTime = 90;
	//}}AFX_DATA_INIT
}


void DlgCartonSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCartonSetting)
	DDX_Check(pDX, IDC_CHECK_OPENCARTON, m_openCarton);
	DDX_Check(pDX, IDC_CHECK_SPINX, m_spinX);
	DDX_Check(pDX, IDC_CHECK_SPINY, m_spinY);
	DDX_Check(pDX, IDC_CHECK_SPINZ, m_spinZ);
	DDX_Text(pDX, IDC_EDIT_SPINX, m_spinXup);
	DDX_Text(pDX, IDC_EDIT_SPINY, m_spinYup);
	DDX_Text(pDX, IDC_EDIT_SPINZ, m_spinZup);
	DDX_Text(pDX, IDC_EDIT_UPDATETIME, m_updataTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCartonSetting, CDialog)
	//{{AFX_MSG_MAP(DlgCartonSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCartonSetting message handlers

void DlgCartonSetting::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void DlgCartonSetting::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);
	if(m_spinXup>360)
		m_spinXup%=360;
	if(m_spinYup>360)
		m_spinYup%=360;
	if(m_spinZup>360)
		m_spinZup%=360;
	if(m_updataTime<24)
		m_updataTime=24;
	this->UpdateData(FALSE);
	CDialog::OnOK();
}
