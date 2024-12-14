
// 服务器端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "服务器端.h"
#include "服务器端Dlg.h"
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


// C服务器端Dlg 对话框



C服务器端Dlg::C服务器端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C服务器端Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C服务器端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_listinfo);
}

BEGIN_MESSAGE_MAP(C服务器端Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_USER_SOCK,OnUserSock)
	ON_WM_CLOSE()
END_MESSAGE_MAP()




void C服务器端Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C服务器端Dlg::OnPaint()
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
HCURSOR C服务器端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// C服务器端Dlg 消息处理程序

BOOL C服务器端Dlg::OnInitDialog()
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
	//初始化WinSock库
	WSADATA wsaData;
	int nret=WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字，并设置为非阻塞异步模式
	serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	nret=WSAAsyncSelect(serverSock, this->GetSafeHwnd(), UM_USER_SOCK, FD_ACCEPT);

	//填写地址信息
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = ADDR_ANY;
	serverAddr.sin_port = htons(5555);

	//绑定地址并监听
	nret = bind(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	nret = listen(serverSock, 5);

	m_listinfo.AddString(TEXT("Listen Port:2222..."));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

/*
异步网络编程实现：
	添加自定义消息：
		#define UM_USER_SOCK (WM_USER+0x101)
	添加消息映射函数：
		afx_msg VOID OnUserSock(WPARAM wParam, LPARAM lParam);
	添加消息映射：
		ON_MESSAGE_VOID(UM_USER_SOCK,OnUserSock)
	实现消息映射函数

	在初始化中初始化监听等

	当一个套接字socket()创建之后，默认工作在阻塞状态（同步状态），如果不使用多线程的话，程序会因为等待造成卡死无响应的情况
	因此，在不使用多线程的情况下，基于Windows消息机制，就有了非阻塞（异步）网络

	设置一个SOCKET的非阻塞函数：int WSAAsyncSelect(SOCKET sock,HWND hWnd,unsigned int userMessage,long listenEvents);
	参数：要异步的套接字，接受回调的窗口句柄，一个自定义的用户消息，用户需要接受的通知码（可以使用位或多个）

	常用通知码：
		FD_READ:收到数据包，TCP中对于服务端和客户端都会用到
		FD_ACCEPT:接受客户端，TCP中仅限于服务器端
		FD_CONNECT:连接成功服务器，TCP中仅限于客户端
		FD_CLOSE:连接断开，TCP中对于服务端和客户端都会用到
		特别的，UDP中ACCEPT，CONNECT，CLOSE都是没有意义的，因为是无连接的通信

	其他技巧或使用提升：
		使用MFC开发异步通信是注意，否则可能程序会一直运行不对，也不会报错：
			注意在Init是初始化WinSock（服务器端做好绑定和监听，客户端可以在按钮之后再连接）
			注意在close是清理WinSock和Socket
		多字节和Unicode的相互转换：
			TCHAR * A2T(char *);(Ascii to TCHAR)
			char * T2A(TCHAR *);(TCHAR to Ascii)
			当然如果是明确的宽字节环境，直接指明：A2W W2A也行
			但是注意，使用这种转换的时候，需要在使用的作用域内添加：
				USES_CONVERSION;
			否则，不能使用。
		内存拷贝：
			memcpy(void * targetPoint,const char * resourcePoint,int copySize);
		打开光驱：
			mciSendString("set cdaudio door open",NULL,NULL,NULL);
		关闭光驱：
			mciSendString("set cdaudio door closed",NULL,NULL,NULL);
			使用msi需要头文件和库：
				#include<mmsystem.h>
				#pragma comment(lib,"Winmm")
		交换鼠标左右键：
			SwapMouseButton(TRUE);
		重置鼠标左右键：
			SwapMouseButton(FALSE);
		数据结构和char *之间转换：
			Data -> char *:(char *)&struct,sizeof(struct)
			char * -> Data:memcpy((void *)&struct,(const void *)char * p,sizeof(struct));
			当然，有时候，结构在char *之中的一部分，而不是开头时，记得加上偏移地址,例如偏移12字节：(p+12)，p+sizeof(int)等等
		在网络开发中，对于换行\n:
			建议采用\r\n
		
		有了这些知识，就可以做一个简单的远程控制了。
*/
//执行命令行，并捕获命令行输出，利用管道和进程
CString C服务器端Dlg::ExecuteCmd(CString str)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		MessageBox(TEXT("Error on CreatePipe()!"));
		return NULL;
	}
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	int len = str.GetLength();
	TCHAR* cmdline = str.GetBuffer(len);
	str.ReleaseBuffer();

	if (!CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		MessageBox(TEXT("Error on CreateProcess()!"));
		return NULL;
	}
	CloseHandle(hWrite);

	char buffer[4096];
	memset(buffer, 0, 4096);
	CString output;
	DWORD byteRead;
	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &byteRead, NULL) == NULL)
		{
			break;
		}
		output += buffer;
	}
	return output;
}
//发生异步消息的回调函数
LRESULT C服务器端Dlg::OnUserSock(WPARAM wParam, LPARAM lParam)
{
	//检查参数是否错误
	if (WSAGETSELECTERROR(lParam))
	{
		return 0;
	}
	//判断参数事件
	switch (WSAGETSELECTEVENT(lParam))
	{
		//新客户端接入事件，serverSock触发
	case FD_ACCEPT:
	{
		//获取客户端套接字和相关信息，并把刚获取的套接字也设置为异步模式
		struct sockaddr_in clientAddr;
		int psize = sizeof(clientAddr);
		clientSock = accept(serverSock, (SOCKADDR *)&clientAddr, &psize);
		WSAAsyncSelect(clientSock, this->GetSafeHwnd(), UM_USER_SOCK, FD_READ | FD_CLOSE);
		//显示出接入的客户端
		CString tp;
		USES_CONVERSION;
		tp.Format(TEXT("Client connected:%s:%d\n"), A2T(inet_ntoa(clientAddr.sin_addr)), ntohs(clientAddr.sin_port));
		m_listinfo.AddString(tp);
		//发送给客户端使用说明
		SERVICE_DATA data;
		data.s_type = TYPE_TEXT;
		data.s_class = 0;
		lstrcpy(data.s_value, TEXT(HELPINFO));

		send(clientSock, (const char *)&data, sizeof(data), 0);
	}
		break;
		//收到消息事件，clientSock触发
	case FD_READ:
	{
					char buffer[2048] = { 0 };
					recv(clientSock, buffer, 2048, 0);
					ProcessMsgData(buffer);
	}
		break;
		//收到客户端关闭事件，clientSock触发
	case FD_CLOSE:
	{
					 closesocket(clientSock);
					 CString tp=TEXT("Client Closed.\n");
					 m_listinfo.AddString(tp);
	}
		break;
	}
	return 0;
}
//直接交给控制台处理，并返回捕获的结果
void C服务器端Dlg::ProcessMsgData(char * buffer)
{
	CString tp;
	USES_CONVERSION;
	tp.Format(TEXT("Client Command:%s\n"),A2T(buffer));
	m_listinfo.AddString(tp);
	CString cmd = A2T(buffer);
	CString ret=ExecuteCmd(cmd);
	SERVICE_DATA data;
	data.s_type = TYPE_TEXT;
	data.s_class = 0;
	lstrcpy(data.s_value, ret);
	send(clientSock, (const char *)&data, sizeof(data), 0);
}
//关闭套接字和清理WinSock
void C服务器端Dlg::OnClose()
{
	closesocket(clientSock);
	closesocket(serverSock);

	WSACleanup();
	CDialogEx::OnClose();
}
