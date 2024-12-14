// BootItemAdder.cpp : 实现文件
//

#include "stdafx.h"
#include "16-注册表操作-启动项管理.h"
#include "BootItemAdder.h"
#include "afxdialogex.h"


// CBootItemAdder 对话框

IMPLEMENT_DYNAMIC(CBootItemAdder, CDialogEx)

CBootItemAdder::CBootItemAdder(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBootItemAdder::IDD, pParent)
	, m_bootkey(_T(""))
	, m_bootvalue(_T(""))
{

}

CBootItemAdder::~CBootItemAdder()
{
}

void CBootItemAdder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BOOTNAME, m_bootkey);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_TARFILE, m_bootvalue);
}


BEGIN_MESSAGE_MAP(CBootItemAdder, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBootItemAdder::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBootItemAdder::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBootItemAdder 消息处理程序


void CBootItemAdder::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


void CBootItemAdder::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
