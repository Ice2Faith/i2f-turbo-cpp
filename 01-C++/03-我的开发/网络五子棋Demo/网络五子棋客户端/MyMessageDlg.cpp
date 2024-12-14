// MyMessageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����������ͻ���.h"
#include "MyMessageDlg.h"
#include "afxdialogex.h"


// MyMessageDlg �Ի���

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


// MyMessageDlg ��Ϣ�������


void MyMessageDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SelBtnType = MMD_YES;
	CDialogEx::OnOK();
}


void MyMessageDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SelBtnType = MMD_NO;
	CDialogEx::OnCancel();
}


BOOL MyMessageDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���
	
	return CDialogEx::PreCreateWindow(cs);
}


void MyMessageDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(m_title);
	if (msWaittime > 0)
	{
		startTime = GetTickCount();
		SetTimer(ID_TIMER_WAIT, 1, NULL);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
