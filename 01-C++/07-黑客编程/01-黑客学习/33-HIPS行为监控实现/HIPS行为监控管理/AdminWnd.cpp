// AdminWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HIPS��Ϊ��ع���.h"
#include "AdminWnd.h"
#include "afxdialogex.h"


// CAdminWnd �Ի���

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


// CAdminWnd ��Ϣ�������
/*Ĭ���޲���15����Զ������رմ���*/
#define TIMER_WAIT 0x101

void CAdminWnd::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_retCode = false;
	CDialogEx::OnCancel();
}


void CAdminWnd::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_retCode = true;
	CDialogEx::OnOK();
}


void CAdminWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_prewaittime -= 1000;
	if (m_prewaittime <=0)
	{
		m_retCode = true;
		KillTimer(TIMER_WAIT);
		CDialogEx::OnOK();
	}
	m_timer_display.Format(TEXT("%ds���Զ�����"), m_prewaittime / 1000);
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CAdminWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	this->SetActiveWindow();
	this->SetForegroundWindow();
	m_prewaittime = m_waitTime;
	SetTimer(TIMER_WAIT, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAdminWnd::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(TIMER_WAIT);
	CDialogEx::OnClose();
}
