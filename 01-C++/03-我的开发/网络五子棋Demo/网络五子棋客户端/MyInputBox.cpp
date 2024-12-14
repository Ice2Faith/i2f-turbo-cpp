// MyInputBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����������ͻ���.h"
#include "MyInputBox.h"
#include "afxdialogex.h"


// MyInputBox �Ի���

IMPLEMENT_DYNAMIC(MyInputBox, CDialogEx)

MyInputBox::MyInputBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyInputBox::IDD, pParent)
	, m_tipsContext(_T(""))
	, m_inputContext(_T(""))
{

}
MyInputBox::MyInputBox(CString tips, CWnd* pParent)
: CDialogEx(MyInputBox::IDD, pParent)
, m_tipsContext(tips)
, m_inputContext(_T(""))
{

}
MyInputBox::~MyInputBox()
{
}

void MyInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TIPS, m_tipsContext);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_inputContext);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_edit_input);
}


BEGIN_MESSAGE_MAP(MyInputBox, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &MyInputBox::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &MyInputBox::OnBnClickedOk)
END_MESSAGE_MAP()


// MyInputBox ��Ϣ�������


void MyInputBox::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}


void MyInputBox::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


BOOL MyInputBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->hwnd == m_edit_input.GetSafeHwnd())
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_RETURN)
			{
				OnBnClickedOk();
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
