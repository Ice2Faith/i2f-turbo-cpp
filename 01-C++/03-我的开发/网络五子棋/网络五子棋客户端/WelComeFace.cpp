// WelComeFace.cpp : 实现文件
//

#include "stdafx.h"
#include "网络五子棋客户端.h"
#include "WelComeFace.h"
#include "afxdialogex.h"

#include"MyMessageDlg.h"
// WelComeFace 对话框

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
// WelComeFace 消息处理程序


void WelComeFace::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void WelComeFace::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}


void WelComeFace::OnBnClickedButtonExit()
{
	// TODO:  在此添加控件通知处理程序代码
	exit(0);
}


void WelComeFace::OnBnClickedButtonOffline()
{
	// TODO:  在此添加控件通知处理程序代码
	up = UP_OFFLINE;
	CDialogEx::OnCancel();
}

void WelComeFace::OnBnClickedButtonLogin()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	up = UP_LOGIN;
	m_uName = m_uName.Trim();
	m_uPwd = m_uPwd.Trim();
	if (m_uName.GetLength() == 0)
	{
		MyMessageDlg dlg(L"用户名不能为空",L"验证提示",1200,this);
		dlg.DoModal();
		return;
	}
	if (m_uPwd.GetLength() == 0)
	{
		MyMessageDlg dlg(L"密码不能为空", L"验证提示", 1200, this);
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
			MyMessageDlg dlg(L"Frist", L"验证提示", 800, this);
			dlg.DoModal();
			isFrist = true;
		}
		else if (strcmp(flag, "false") == 0)
		{
			MyMessageDlg dlg(L"Not Frist", L"验证提示", 800, this);
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
			MyMessageDlg dlg(L"登录成功", L"验证提示", 1500, this);
			dlg.DoModal();
			CDialogEx::OnCancel();
		}
		else
		{
			MyMessageDlg dlg(L"登录失败，用户名或密码错误，或未注册", L"验证提示", 3000, this);
			dlg.DoModal();
		}
	}
}


void WelComeFace::OnBnClickedButtonReg()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	up = UP_LOGIN;
	m_uName = m_uName.Trim();
	m_uPwd = m_uPwd.Trim();
	if (m_uName.GetLength() == 0)
	{
		MyMessageDlg dlg(L"用户名不能为空", L"验证提示", 1200, this);
		dlg.DoModal();
		return;
	}
	if (m_uPwd.GetLength() == 0)
	{
		MyMessageDlg dlg(L"密码不能为空", L"验证提示", 1200, this);
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

	// TODO:  在此添加额外的初始化
	char ip[256] = { "127.0.0.1" };
	unsigned short port = 12100;
	GetServerConfig(ip,&port);
	isConnectServer = true;
	if (!client->SetWSAStartup(2, 2))
	{
		printf("协议申请失败\n");
		isConnectServer = false;
	}
	printf("协议申请成功\n");
	if (!client->CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
	{
		printf("创建连接失败\n");
		isConnectServer = false;
	}
	printf("创建连接成功\n");
	if (!client->SetIpPort(ip, port))
	{
		printf("设置IP端口失败\n");
		isConnectServer = false;
	}
	printf("设置IP端口成功\n");
	if (!client->ConnectServer())
	{
		printf("连接服务器失败\n");
		isConnectServer = false;
	}
	if (!isConnectServer)
	{
		MyMessageDlg dlg(L"链接服务器失败", L"验证提示", 800, this);
		dlg.DoModal();
	}
	else
	{
		MyMessageDlg dlg(L"链接服务器成功", L"验证提示", 800, this);
		dlg.DoModal();
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
