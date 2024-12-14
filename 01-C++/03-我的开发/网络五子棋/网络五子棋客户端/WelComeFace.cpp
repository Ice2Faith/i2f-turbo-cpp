// WelComeFace.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����������ͻ���.h"
#include "WelComeFace.h"
#include "afxdialogex.h"

#include"MyMessageDlg.h"
// WelComeFace �Ի���

IMPLEMENT_DYNAMIC(WelComeFace, CDialogEx)

WelComeFace::WelComeFace(CWnd* pParent /*=NULL*/)
	: CDialogEx(WelComeFace::IDD, pParent)
	, m_uName(_T(""))
	, m_uPwd(_T(""))
	, isFrist(false)
{
	client = new Client();
}

WelComeFace::~WelComeFace()
{
}

void WelComeFace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UNAME, m_uName);
	DDX_Text(pDX, IDC_EDIT_UPWD, m_uPwd);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btn_login);
}


BEGIN_MESSAGE_MAP(WelComeFace, CDialogEx)
	ON_BN_CLICKED(IDOK, &WelComeFace::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &WelComeFace::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &WelComeFace::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_OFFLINE, &WelComeFace::OnBnClickedButtonOffline)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &WelComeFace::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_REG, &WelComeFace::OnBnClickedButtonReg)
END_MESSAGE_MAP()

void Wchar_t2Char(wchar_t Wchar[], char Char[])
{
	int size = WideCharToMultiByte(CP_ACP, 0, Wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Wchar, -1, Char, size, NULL, NULL);
}
void Char2Wchar_t(char Char[], wchar_t Wchar[])
{
	int size = MultiByteToWideChar(CP_ACP, 0, Char, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, Char, -1, Wchar, size);
}
// WelComeFace ��Ϣ�������


void WelComeFace::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void WelComeFace::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}


void WelComeFace::OnBnClickedButtonExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void WelComeFace::OnBnClickedButtonOffline()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	up = UP_OFFLINE;
	CDialogEx::OnCancel();
}

void WelComeFace::OnBnClickedButtonLogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	up = UP_LOGIN;
	m_uName = m_uName.Trim();
	m_uPwd = m_uPwd.Trim();
	if (m_uName.GetLength() == 0)
	{
		MyMessageDlg dlg(L"�û�������Ϊ��",L"��֤��ʾ",1200,this);
		dlg.DoModal();
		return;
	}
	if (m_uPwd.GetLength() == 0)
	{
		MyMessageDlg dlg(L"���벻��Ϊ��", L"��֤��ʾ", 1200, this);
		dlg.DoModal();
		return;
	}
	UpdateData(FALSE);
	if (isConnectServer)
	{
		char name[256];
		char pwd[256];
		Wchar_t2Char(m_uName.GetBuffer(), name);
		Wchar_t2Char(m_uPwd.GetBuffer(), pwd);
		char buffer[1024];
		client->AcceptMsg(buffer,1024-1);
		char flag[20];
		sscanf(buffer,"frist %s",flag);
		if (strcmp(flag, "true") == 0)
		{
			MyMessageDlg dlg(L"Frist", L"��֤��ʾ", 800, this);
			dlg.DoModal();
			isFrist = true;
		}
		else if (strcmp(flag, "false") == 0)
		{
			MyMessageDlg dlg(L"Not Frist", L"��֤��ʾ", 800, this);
			dlg.DoModal();
			isFrist = false;
		}
		sprintf(buffer, "login \"%s\" \"%s\"\0", name, pwd);
		client->SendMsg(buffer, strlen(buffer));
		client->AcceptMsg(buffer, 256 - 1);
		char result[20];
		sscanf(buffer, "login %s", result);
		if (strcmp(result, "success")==0)
		{
			MyMessageDlg dlg(L"��¼�ɹ�", L"��֤��ʾ", 1500, this);
			dlg.DoModal();
			CDialogEx::OnCancel();
		}
		else
		{
			MyMessageDlg dlg(L"��¼ʧ�ܣ��û�����������󣬻�δע��", L"��֤��ʾ", 3000, this);
			dlg.DoModal();
		}
	}
}


void WelComeFace::OnBnClickedButtonReg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	up = UP_LOGIN;
	m_uName = m_uName.Trim();
	m_uPwd = m_uPwd.Trim();
	if (m_uName.GetLength() == 0)
	{
		MyMessageDlg dlg(L"�û�������Ϊ��", L"��֤��ʾ", 1200, this);
		dlg.DoModal();
		return;
	}
	if (m_uPwd.GetLength() == 0)
	{
		MyMessageDlg dlg(L"���벻��Ϊ��", L"��֤��ʾ", 1200, this);
		dlg.DoModal();
		return;
	}

	UpdateData(FALSE);
	CDialogEx::OnCancel();
}

void GetServerConfig(char * ip, unsigned short * port)
{
	FILE * fconfig = fopen("GobangClient.config", "r");
	bool IsError = false;
	if (!fconfig)
	{
		sprintf(ip, "127.0.0.1\0");
		*port = 12100;
		return;
	}
	char tempip[256];
	if (1 != fscanf(fconfig, "ServerIP=%s\n", tempip))
		IsError = true;
	else
		strcpy(ip, tempip);
	int tempport = 12100;
	if (1 != fscanf(fconfig, "ServerPort=%d\n", &tempport))
		IsError = true;
	else
		*port = tempport;
	fclose(fconfig);
	if (IsError)
	{
		sprintf(ip, "127.0.0.1\0");
		*port = 12100;
	}
}
BOOL WelComeFace::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	char ip[256] = { "127.0.0.1" };
	unsigned short port = 12100;
	GetServerConfig(ip,&port);
	isConnectServer = true;
	if (!client->SetWSAStartup(2, 2))
	{
		printf("Э������ʧ��\n");
		isConnectServer = false;
	}
	printf("Э������ɹ�\n");
	if (!client->CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
	{
		printf("��������ʧ��\n");
		isConnectServer = false;
	}
	printf("�������ӳɹ�\n");
	if (!client->SetIpPort(ip, port))
	{
		printf("����IP�˿�ʧ��\n");
		isConnectServer = false;
	}
	printf("����IP�˿ڳɹ�\n");
	if (!client->ConnectServer())
	{
		printf("���ӷ�����ʧ��\n");
		isConnectServer = false;
	}
	if (!isConnectServer)
	{
		MyMessageDlg dlg(L"���ӷ�����ʧ��", L"��֤��ʾ", 800, this);
		dlg.DoModal();
	}
	else
	{
		MyMessageDlg dlg(L"���ӷ������ɹ�", L"��֤��ʾ", 800, this);
		dlg.DoModal();
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
