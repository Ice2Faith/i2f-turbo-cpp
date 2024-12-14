// DlgSizeSetting.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgSizeSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSizeSetting dialog


DlgSizeSetting::DlgSizeSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSizeSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSizeSetting)
	m_size = 1;
	//}}AFX_DATA_INIT
}


void DlgSizeSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSizeSetting)
	DDX_Control(pDX, IDC_SLIDER_SIZE, m_scSize);
	DDX_Slider(pDX, IDC_SLIDER_SIZE, m_size);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSizeSetting, CDialog)
	//{{AFX_MSG_MAP(DlgSizeSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSizeSetting message handlers

BOOL DlgSizeSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_scSize.SetRange(1,100);
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgSizeSetting::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);
	CDialog::OnOK();
}

void DlgSizeSetting::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

int DlgSizeSetting::GetSize()
{
	return this->m_size;
}
