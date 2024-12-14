// DlgColorSetting.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgColorSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgColorSetting dialog


DlgColorSetting::DlgColorSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgColorSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgColorSetting)
	m_blue = 100;
	m_green = 100;
	m_red = 100;
	//}}AFX_DATA_INIT
	
}


void DlgColorSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgColorSetting)
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_scBlue);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_scGreen);
	DDX_Control(pDX, IDC_SLIDER_RED, m_scRed);
	DDX_Slider(pDX, IDC_SLIDER_BLUE, m_blue);
	DDX_Slider(pDX, IDC_SLIDER_GREEN, m_green);
	DDX_Slider(pDX, IDC_SLIDER_RED, m_red);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgColorSetting, CDialog)
	//{{AFX_MSG_MAP(DlgColorSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgColorSetting message handlers

void DlgColorSetting::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);
	CDialog::OnOK();
}

void DlgColorSetting::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

COLORREF DlgColorSetting::GetColor()
{
	return RGB(m_red,m_green,m_blue);
}

int DlgColorSetting::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DoModal();
}

BOOL DlgColorSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_scRed.SetRange(0,255);
	this->m_scGreen.SetRange(0,255);
	this->m_scBlue.SetRange(0,255);
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
