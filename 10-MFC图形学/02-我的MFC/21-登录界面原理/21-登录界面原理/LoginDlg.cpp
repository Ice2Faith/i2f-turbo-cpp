// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "21-登录界面原理.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_user_name(_T(""))
	, m_user_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_user_name);
	DDX_Text(pDX, IDC_EDIT_USERPWD, m_user_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CLoginDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CLoginDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CLoginDlg::OnBnClickedButtonClear()
{
	// TODO:  在此添加控件通知处理程序代码
	m_user_name.Empty();
	m_user_pwd.Empty();
	UpdateData(FALSE);
}


void CLoginDlg::OnBnClickedButtonExit()
{
	// TODO:  在此添加控件通知处理程序代码
	exit(0);
}


void CLoginDlg::OnBnClickedButtonLogin()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_user_name == L"admin" && m_user_pwd == "pass")
		this->OnOK();
	else
		MessageBox(L"用户名或密码不正确，请重试！",L"登录失败",MB_OK);
}
