// AdminWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "HIPS行为监控管理.h"
#include "AdminWnd.h"
#include "afxdialogex.h"


// CAdminWnd 对话框

IMPLEMENT_DYNAMIC(CAdminWnd, CDialogEx)

CAdminWnd::CAdminWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminWnd::IDD, pParent)
	, m_str_tips(_T(""))
	, m_retCode(false)
	, m_timer_display(_T(""))
	, m_waitTime(15*1000)
	, m_prewaittime(0)
{

}

CAdminWnd::~CAdminWnd()
{
}

void CAdminWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_AUTHINFO, m_str_tips);
	DDX_Text(pDX, IDC_STATIC_TIMER_DISPLAY, m_timer_display);
}


BEGIN_MESSAGE_MAP(CAdminWnd, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CAdminWnd::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CAdminWnd::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CAdminWnd 消息处理程序
/*默认无操作15秒后自动允许后关闭窗口*/
#define TIMER_WAIT 0x101

void CAdminWnd::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	m_retCode = false;
	CDialogEx::OnCancel();
}


void CAdminWnd::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	m_retCode = true;
	CDialogEx::OnOK();
}


void CAdminWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_prewaittime -= 1000;
	if (m_prewaittime <=0)
	{
		m_retCode = true;
		KillTimer(TIMER_WAIT);
		CDialogEx::OnOK();
	}
	m_timer_display.Format(TEXT("%ds后自动允许"), m_prewaittime / 1000);
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CAdminWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->SetActiveWindow();
	this->SetForegroundWindow();
	m_prewaittime = m_waitTime;
	SetTimer(TIMER_WAIT, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CAdminWnd::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	KillTimer(TIMER_WAIT);
	CDialogEx::OnClose();
}
