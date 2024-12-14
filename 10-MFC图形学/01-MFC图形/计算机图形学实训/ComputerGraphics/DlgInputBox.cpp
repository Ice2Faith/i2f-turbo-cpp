// DlgInputBox.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgInputBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgInputBox dialog


DlgInputBox::DlgInputBox(CWnd* pParent /*=NULL*/)
	: CDialog(DlgInputBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgInputBox)
	m_strInputTips = _T("请输入或拖入文件：");
	m_strInputText = _T("");
	//}}AFX_DATA_INIT
}


void DlgInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgInputBox)
	DDX_Text(pDX, IDC_STATIC_TIPS, m_strInputTips);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInputText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgInputBox, CDialog)
	//{{AFX_MSG_MAP(DlgInputBox)
	//}}AFX_MSG_MAP

	ON_WM_DROPFILES()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgInputBox message handlers

void DlgInputBox::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);
	CDialog::OnOK();
}

void DlgInputBox::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL DlgInputBox::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_strInputTips="请输入或拖入文件：";
	this->m_strInputText="";
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


CString DlgInputBox::GetInputText()
{
	return this->m_strInputText;
}


void DlgInputBox::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	// int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	TCHAR szFullFileName[MAX_PATH];
	DragQueryFile(hDropInfo, 0, szFullFileName, MAX_PATH);
	this->m_strInputText = szFullFileName;
	this->UpdateData(FALSE);
	DragFinish(hDropInfo);

	CDialog::OnDropFiles(hDropInfo);
}
