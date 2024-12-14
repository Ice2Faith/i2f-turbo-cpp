// BootItemAdder.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "16-ע������-���������.h"
#include "BootItemAdder.h"
#include "afxdialogex.h"


// CBootItemAdder �Ի���

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


// CBootItemAdder ��Ϣ�������


void CBootItemAdder::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


void CBootItemAdder::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
