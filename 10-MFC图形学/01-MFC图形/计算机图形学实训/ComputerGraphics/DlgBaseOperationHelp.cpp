// DlgBaseOperationHelp.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgBaseOperationHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgBaseOperationHelp dialog


DlgBaseOperationHelp::DlgBaseOperationHelp(CWnd* pParent /*=NULL*/)
	: CDialog(DlgBaseOperationHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgBaseOperationHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgBaseOperationHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgBaseOperationHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgBaseOperationHelp, CDialog)
	//{{AFX_MSG_MAP(DlgBaseOperationHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgBaseOperationHelp message handlers


void DlgBaseOperationHelp::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
