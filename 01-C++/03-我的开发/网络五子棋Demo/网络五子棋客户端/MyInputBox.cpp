// MyInputBox.cpp : 实现文件
//

#include "stdafx.h"
#include "网络五子棋客户端.h"
#include "MyInputBox.h"
#include "afxdialogex.h"


// MyInputBox 对话框

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


// MyInputBox 消息处理程序


void MyInputBox::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}


void MyInputBox::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


BOOL MyInputBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
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
