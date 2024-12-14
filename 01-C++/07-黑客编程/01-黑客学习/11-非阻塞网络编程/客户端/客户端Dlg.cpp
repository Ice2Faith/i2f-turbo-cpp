
// 客户端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "客户端.h"
#include "客户端Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C客户端Dlg 对话框



C客户端Dlg::C客户端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C客户端Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C客户端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_listinfo);
}

BEGIN_MESSAGE_MAP(C客户端Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_USER_SOCK, OnUserSock)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &C客户端Dlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &C客户端Dlg::OnBnClickedButtonSend)
	ON_WM_CLOSE()
END_MESSAGE_MAP()



void C客户端Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C客户端Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C客户端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*

*/


// C客户端Dlg 消息处理程序

BOOL C客户端Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SetDlgItemTextA(this->GetSafeHwnd(), IDC_EDIT_IP_ADDR, "127.0.0.1");
	m_listinfo.AddString(TEXT("就绪\n"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
LRESULT C客户端Dlg::OnUserSock(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
	{
		return 0;
	}
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:
	{
		SetDlgItemText(IDC_BUTTON_CONNECT, TEXT("Deconnect"));
		m_listinfo.AddString(TEXT("连接成功！\n"));
	}
		break;
	case FD_READ:
	{
		SERVICE_DATA data;
		recv(clientSock, (char *)&data, sizeof(data), 0);
		ProcessMsgData(&data);
	}
		break;
	case FD_CLOSE:
	{
		closesocket(clientSock);
		m_listinfo.AddString(TEXT("对方已关闭连接\n"));
	}
		break;
	}
	return 0;
}
void C客户端Dlg::OnBnClickedButtonConnect()
{
	CString ConnBtnName;
	GetDlgItemText(IDC_BUTTON_CONNECT, ConnBtnName);
	if (ConnBtnName==TEXT("Deconnect"))
	{
		SetDlgItemText(IDC_BUTTON_CONNECT, TEXT("Connect"));
		closesocket(clientSock);
		m_listinfo.AddString(TEXT("主动断开连接！"));
		return;
	}
	char IPAddr[30] = { 0 };
	GetDlgItemTextA(this->GetSafeHwnd(),IDC_EDIT_IP_ADDR, IPAddr, 30);

	clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	WSAAsyncSelect(clientSock, this->GetSafeHwnd(), UM_USER_SOCK, FD_CONNECT | FD_READ | FD_CLOSE);

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr(IPAddr);
	serverAddr.sin_port = htons(5555);

	connect(clientSock, (SOCKADDR *)&serverAddr,sizeof(serverAddr));
}


void C客户端Dlg::OnBnClickedButtonSend()
{
	char command[2048] = { 0 };
	GetDlgItemTextA(this->GetSafeHwnd(),IDC_EDIT_COMMAND, command, 2048);
	char scmd[2048] = { 0 };
	sprintf(scmd,"cmd /c %s\0",command);
	send(clientSock, scmd, strlen(scmd), 0);
}
void C客户端Dlg::ProcessMsgData(PSERVICE_DATA data)
{
	if (data->s_type == TYPE_TEXT)
	{
		m_listinfo.AddString(data->s_value);
	}
}

void C客户端Dlg::OnClose()
{
	closesocket(clientSock);
	WSACleanup();
	CDialogEx::OnClose();
}
