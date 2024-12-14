// MyMessageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "网络五子棋客户端.h"
#include "MyMessageDlg.h"
#include "afxdialogex.h"


// MyMessageDlg 对话框

IMPLEMENT_DYNAMIC(MyMessageDlg, CDialogEx)

MyMessageDlg::MyMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyMessageDlg::IDD, pParent)
	, m_context(_T(""))
	, m_title(_T(""))
	, SelBtnType(MMD_NULL)
{

}
MyMessageDlg::MyMessageDlg(CString Context, CString Title,long msWaitTime, CWnd* pParent) : 
CDialogEx(MyMessageDlg::IDD, pParent)
, m_context(Context)
, m_title(Title)
, SelBtnType(MMD_NULL)
, msWaittime(msWaitTime)
{
	
}

MyMessageDlg::~MyMessageDlg()
{
}

void MyMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_CONTEXT, m_context);
}


BEGIN_MESSAGE_MAP(MyMessageDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MyMessageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MyMessageDlg::OnBnClickedCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// MyMessageDlg 消息处理程序


void MyMessageDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	SelBtnType = MMD_YES;
	CDialogEx::OnOK();
}


void MyMessageDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	SelBtnType = MMD_NO;
	CDialogEx::OnCancel();
}


BOOL MyMessageDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此添加专用代码和/或调用基类
	
	return CDialogEx::PreCreateWindow(cs);
}


void MyMessageDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == ID_TIMER_WAIT)
	{
		if (msWaittime > 0)
		{
			if (GetTickCount()-msWaittime>startTime)
			{
				KillTimer(ID_TIMER_WAIT);
				OnBnClickedCancel();
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL MyMessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(m_title);
	if (msWaittime > 0)
	{
		startTime = GetTickCount();
		SetTimer(ID_TIMER_WAIT, 1, NULL);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
