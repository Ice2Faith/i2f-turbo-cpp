// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��¼��֤ģ���ƽ�.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// DlgLogin �Ի���

IMPLEMENT_DYNAMIC(DlgLogin, CDialogEx)

DlgLogin::DlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgLogin::IDD, pParent)
	, m_isLogined(false)
	, m_account(_T(""))
	, m_password(_T(""))
{

}

DlgLogin::~DlgLogin()
{
}

void DlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_account);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
}


BEGIN_MESSAGE_MAP(DlgLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DlgLogin::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgLogin ��Ϣ�������


void DlgLogin::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_account == _T("admin")
		&& m_password == _T("123456"))
	{
		m_isLogined = true;
	}
	else
	{
		m_isLogined = false;
		m_account = _T("");
		m_password = _T("");
	}
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void DlgLogin::OnBnClickedCancel()
{
	m_isLogined = false;
	m_account = _T("");
	m_password = _T("");
	UpdateData(FALSE);
	CDialogEx::OnCancel();
}
