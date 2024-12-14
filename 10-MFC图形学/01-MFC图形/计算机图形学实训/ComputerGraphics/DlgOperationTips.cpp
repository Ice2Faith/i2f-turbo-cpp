// DlgOperationTips.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgOperationTips.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgOperationTips dialog


DlgOperationTips::DlgOperationTips(CWnd* pParent /*=NULL*/)
	: CDialog(DlgOperationTips::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgOperationTips)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgOperationTips::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgOperationTips)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgOperationTips, CDialog)
	//{{AFX_MSG_MAP(DlgOperationTips)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgOperationTips message handlers

void DlgOperationTips::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void DlgOperationTips::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
