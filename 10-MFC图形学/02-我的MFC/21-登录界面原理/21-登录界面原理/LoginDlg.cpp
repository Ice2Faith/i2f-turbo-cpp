// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "21-��¼����ԭ��.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg �Ի���

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


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CLoginDlg::OnBnClickedButtonClear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_user_name.Empty();
	m_user_pwd.Empty();
	UpdateData(FALSE);
}


void CLoginDlg::OnBnClickedButtonExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CLoginDlg::OnBnClickedButtonLogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_user_name == L"admin" && m_user_pwd == "pass")
		this->OnOK();
	else
		MessageBox(L"�û��������벻��ȷ�������ԣ�",L"��¼ʧ��",MB_OK);
}
