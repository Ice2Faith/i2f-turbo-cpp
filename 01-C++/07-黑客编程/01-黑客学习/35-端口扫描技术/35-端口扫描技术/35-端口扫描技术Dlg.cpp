
// 35-端口扫描技术Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "35-端口扫描技术.h"
#include "35-端口扫描技术Dlg.h"
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


// CMy35端口扫描技术Dlg 对话框



CMy35端口扫描技术Dlg::CMy35端口扫描技术Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy35端口扫描技术Dlg::IDD, pParent)
	, m_strHostName(_T(""))
	, m_iportStart(0)
	, m_iportEnd(0)
	, m_iTimeout(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy35端口扫描技术Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SCAN, m_btnScan);
	DDX_Control(pDX, IDC_IPADDRESS_STARTIP, m_ipAddrStart);
	DDX_Control(pDX, IDC_IPADDRESS_ENDIP, m_ipAddrEnd);
	DDX_Text(pDX, IDC_EDIT_HOSTNAME, m_strHostName);
	DDX_Control(pDX, IDC_IPADDRESS_HOSTADDRESS, m_ipAddrTranlated);
	DDX_Text(pDX, IDC_EDIT_STARTPORT, m_iportStart);
	DDX_Text(pDX, IDC_EDIT_ENDPORT, m_iportEnd);
	DDX_Control(pDX, IDC_TREE_SCANINFO, m_tree_info);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_iTimeout);
}

BEGIN_MESSAGE_MAP(CMy35端口扫描技术Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy35端口扫描技术Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMy35端口扫描技术Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_TRANSLATE, &CMy35端口扫描技术Dlg::OnBnClickedButtonTranslate)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CMy35端口扫描技术Dlg::OnBnClickedButtonScan)
END_MESSAGE_MAP()


// CMy35端口扫描技术Dlg 消息处理程序

BOOL CMy35端口扫描技术Dlg::OnInitDialog()
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
	InitControls();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy35端口扫描技术Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy35端口扫描技术Dlg::OnPaint()
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
HCURSOR CMy35端口扫描技术Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy35端口扫描技术Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
/*
端口扫描技术：
	说简单点就是尝试链接一个主机的每一个端口，如果能链接，那么就说明此端口是开通的

	端口扫描可以对单一主机进行扫描一定区间内的端口
	也可以对一个区间的地址扫描一定区间的端口
	这是实现的是第二种
		点击开始扫描之后，获取起止IP和端口号等信息，然后启动扫描控制线程，控制扫描子线程去执行扫描

	但是，端口扫描会有两个问题
		目标地址不存在，连接一直连不上，浪费时间等待
		目标地址存在，但是目标端口未使用，那也是一直连不上

		解决方案就是，使用非阻塞的链接方式，设置超时时间进行连接
		另外使用多线程进行连接，再次减少等待时间
		还可以考虑构造ping命令检测目标地址是否存在，进一步缩短时间

	既然考虑使用多线程，那么就不得不考虑临界区资源，也就是线程安全
	因此需要使用信号量和事件来进行控制

	创建信号量函数：
		HANDLE
		WINAPI
		CreateSemaphoreW(
		_In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, //SD
		_In_     LONG lInitialCount,	//初始计数
		_In_     LONG lMaximumCount,	//最大计数
		_In_opt_ LPCTSTR lpName	//对象名
		);

	释放信号量函数
		BOOL
		WINAPI
		ReleaseSemaphore(
		_In_ HANDLE hSemaphore,//信号量句柄
		_In_ LONG lReleaseCount,//计数的递减量
		_Out_opt_ LPLONG lpPreviousCount//前一个计数值保存指针
		);

	创建事件函数：
		HANDLE
		WINAPI
		CreateEventW(
		_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,//SD
		_In_ BOOL bManualReset,//重置类型
		_In_ BOOL bInitialState,//初始状态
		_In_opt_ LPCTSTR lpName//对象名
		);

	事件处于信号状态函数
		BOOL
		WINAPI
		SetEvent(
		_In_ HANDLE hEvent//事件句柄
		);

	事件处于无信号状态函数
		BOOL
		WINAPI
		ResetEvent(
		_In_ HANDLE hEvent//事件句柄
		);
	信号量和事件都配合WaitForSingleObject使用，它会等待对象有信号才会继续执行，否则会一直等待（具体等待根据代码而定，可能代码有超时）

*/


void CMy35端口扫描技术Dlg::InitControls()
{
	m_strHostName = TEXT("www.baidu.com");
	m_ipAddrTranlated.SetAddress(0, 0, 0, 0);
	m_ipAddrStart.SetAddress(192, 168, 0, 1);
	m_ipAddrEnd.SetAddress(192, 168, 0, 100);
	m_iportStart = 10;
	m_iportEnd = 120;
	m_iTimeout = 200;
	UpdateData(FALSE);
}

void CMy35端口扫描技术Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
#include<WinSock2.h>
#pragma comment(lib,"ws2_32")

void CMy35端口扫描技术Dlg::OnBnClickedButtonTranslate()
{
	/*
	域名转换
	struct hostent FAR *
	WSAAPI
	gethostbyname(
	_In_z_ const char FAR * name

	struct  hostent {
	char    FAR * h_name;           // official name of host 
	char    FAR * FAR * h_aliases;  // alias list
	short   h_addrtype;             // host address type 
	short   h_length;               // length of address 
	char    FAR * FAR * h_addr_list; // list of addresses 
	);
	*/
	USES_CONVERSION;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	UpdateData(TRUE);

	char hostName[MAXBYTE] = { 0 };
	strcpy(hostName, T2A(m_strHostName));

	HOSTENT * pHosten = gethostbyname(hostName);
	
	struct sockaddr_in sAddr;
	if (pHosten && pHosten->h_addr_list[0])
	{
		memcpy(&sAddr.sin_addr.S_un.S_addr, pHosten->h_addr_list[0], pHosten->h_length);
		m_ipAddrTranlated.SetAddress(ntohl(sAddr.sin_addr.S_un.S_addr));
	}
	else
	{
		MessageBox(TEXT("域名转换失败，请输入有效域名或检查网络连接！！"));
	}
	WSACleanup();
}
//主扫描线程参数结构
typedef struct _ThreadPortScanInfo
{
	DWORD dwIPStart;//扫描起始IP
	DWORD dwIPEnd;//扫描终止IP
	WORD wdPortStart;//扫描起始Port
	WORD wdPortEnd;//扫描终止Port
	DWORD dwTimeOutMilliSecond;//端口扫描超时
	CMy35端口扫描技术Dlg * lpWndMain;//主窗口指针
	HANDLE hEvent;//事件句柄
}ThreadPortScanInfo, *PThreadPortScanInfo;
//扫描子线程参数结构
typedef struct _ScanInfo
{
	DWORD dwIp;//扫描IP
	WORD wdPort;//扫描端口
	HANDLE hEvent;//事件句柄
	HANDLE hSemaphore;//信号量句柄
	DWORD dwTimeOutMilliSecond;//端口扫描超时
	CMy35端口扫描技术Dlg * lpWndMain;//主窗口指针
	HTREEITEM hTree;//树形控件项目句柄
}ScanInfo, *PScanInfo;
#define MAX_THREAD 20 //最大扫描线程数
DWORD WINAPI SubScanFunc(LPVOID lpThreadParameter)
{
	//拷贝传递过来的参数
	ScanInfo scanInfo = { 0 };
	MoveMemory(&scanInfo, lpThreadParameter, sizeof(ScanInfo));
	//设置事件信号存在，这将会影响到调用者处的WaitSingleObject
	SetEvent(scanInfo.hEvent);
	//打开WSA库
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//设置目标IP：port信息
	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.S_un.S_addr = htonl(scanInfo.dwIp);
	sockaddr.sin_port = htons(scanInfo.wdPort);
	//是否使用异步超时的链接方式
	/*
	如果不使用异步超时的方式链接，
	那么遇到端口不可用的情况，将会消耗大量的时间等待，造成不必要的时间等待
	*/
#define USE_ASYN_MODE_SCAN 1
#if USE_ASYN_MODE_SCAN
	TIMEVAL timeOut;
	FD_SET mask;
	unsigned long mode = 1;

	//设置扫描超时
	timeOut.tv_sec = 0;
	timeOut.tv_usec = scanInfo.dwTimeOutMilliSecond;

	FD_ZERO(&mask);
	FD_SET(sock,&mask);
	//设置为非阻塞套接字
	/*
	设置套接字模式
	int
	WSAAPI
	ioctlsocket(
    _In_ SOCKET s,
    _In_ long cmd,
    _Inout_ u_long FAR * argp
    );
	*/
	ioctlsocket(sock, FIONBIO, &mode);

	connect(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr));

	/*
	查询可写入状态
	int
	WSAAPI
	select(
	_In_ int nfds,
	_Inout_opt_ fd_set FAR * readfds,
	_Inout_opt_ fd_set FAR * writefds,
	_Inout_opt_ fd_set FAR * exceptfds,
	_In_opt_ const struct timeval FAR * timeout
	)
	*/
	int ret = select(0, NULL, &mask, NULL, &timeOut);
	CString str;
	if (ret != 0 && ret != -1)
	{
		//将连接成功的IP：Port显示到对应的树形控件项目下
		
		str.Format(TEXT("%d"),scanInfo.wdPort);
		scanInfo.lpWndMain->m_tree_info.InsertItem(str, 1, 1, scanInfo.hTree);
		scanInfo.lpWndMain->m_tree_info.Expand(scanInfo.hTree, 0);
		scanInfo.lpWndMain->m_tree_info.Invalidate(FALSE);
	}
#else
	if (connect(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr)) == 0)
	{
		//将连接成功的IP：Port显示到对应的树形控件项目下
		CString str;
		str.Format(TEXT("%d"),scanInfo.wdPort);
		scanInfo.lpWndMain->m_tree_info.InsertItem(str, 1, 1, scanInfo.hTree);
		scanInfo.lpWndMain->m_tree_info.Invalidate(FALSE);
	}
#endif //USE_ASYN_MODE_SCAN
	//断开套接字并清理WSA库
	closesocket(sock);
	WSACleanup();

	//释放一个信号量
	ReleaseSemaphore(scanInfo.hSemaphore, 1, NULL);

	return 0;
}
DWORD WINAPI ThreadPortScanFunc(LPVOID lpThreadParameter)
{
	//拷贝传递过来的参数
	ThreadPortScanInfo thrInfo = { 0 };
	MoveMemory(&thrInfo, lpThreadParameter, sizeof(ThreadPortScanInfo));
	//设置事件信号存在，这将会影响到调用者处的WaitSingleObject
	SetEvent(thrInfo.hEvent);
	//创建事件对象和信号量对象，赋值给结构
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE hSemaphore = CreateSemaphore(NULL, MAX_THREAD, MAX_THREAD, NULL);
	//结构赋值
	ScanInfo scanInfo = { 0 };
	scanInfo.hEvent = hEvent;
	scanInfo.hSemaphore = hSemaphore;
	scanInfo.lpWndMain = thrInfo.lpWndMain;
	scanInfo.dwTimeOutMilliSecond = thrInfo.dwTimeOutMilliSecond;
	//当前需要扫描的IP：Port
	DWORD dwCurrentIP;
	WORD wdCurrentPort;
	//遍历每个IP
	for (dwCurrentIP = thrInfo.dwIPStart; dwCurrentIP <= thrInfo.dwIPEnd; dwCurrentIP++)
	{
		//设置参数扫描IP
		scanInfo.dwIp = dwCurrentIP;
		//将当前扫描IP添加到树形控件显示
		struct sockaddr_in sockaddr;
		sockaddr.sin_addr.S_un.S_addr = ntohl(dwCurrentIP);
		USES_CONVERSION;
		HTREEITEM hTreeItem = (thrInfo.lpWndMain)->m_tree_info.InsertItem(A2T(inet_ntoa(sockaddr.sin_addr)));
		(thrInfo.lpWndMain)->m_tree_info.Invalidate(FALSE);
		//遍历每个Port
		for (wdCurrentPort = thrInfo.wdPortStart; wdCurrentPort <= thrInfo.wdPortEnd; wdCurrentPort++)
		{
			//检查信号量，超时200ms
			DWORD dwWaitReturn = WaitForSingleObject(hSemaphore, 200);
			if (dwWaitReturn == WAIT_OBJECT_0)
			{
				//信号量可用则开启新线程进行扫描
				scanInfo.wdPort = wdCurrentPort;
				scanInfo.hTree = hTreeItem;

				HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SubScanFunc, (LPVOID)&scanInfo, 0, NULL);
				WaitForSingleObject(hEvent, INFINITE);
				ResetEvent(hEvent);
				//判断是否是最后一次扫描，给出提示
				if (wdCurrentPort == thrInfo.wdPortEnd && dwCurrentIP == thrInfo.dwIPEnd)
				{
					MessageBox((thrInfo.lpWndMain)->GetSafeHwnd(), TEXT("端口扫描已完成"), TEXT("扫描提示"), MB_OK);
				}
			}
			else if (dwWaitReturn==WAIT_TIMEOUT)
			{
				//信号量不可用则进行空转，继续等待
				wdCurrentPort--;
				continue;
			}
		}
	}
	return 0;
}
void CMy35端口扫描技术Dlg::OnBnClickedButtonScan()
{
	m_tree_info.DeleteAllItems();
	//获取起止IP和Port并赋值线程参数结构
	UpdateData(TRUE);
	ThreadPortScanInfo thrInfo = { 0 };
	m_ipAddrStart.GetAddress(thrInfo.dwIPStart);
	m_ipAddrEnd.GetAddress(thrInfo.dwIPEnd);

	thrInfo.wdPortStart = m_iportStart;
	thrInfo.wdPortEnd = m_iportEnd;

	thrInfo.dwTimeOutMilliSecond = m_iTimeout;
	//创建事件
	HANDLE hEnvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//赋值事件和窗口指针
	thrInfo.hEvent = hEnvent;
	thrInfo.lpWndMain = this;
	//开启线程
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPortScanFunc, (LPVOID)&thrInfo, 0, NULL);
	WaitForSingleObject(hEnvent, INFINITE);
	ResetEvent(hEnvent);
	CloseHandle(hEnvent);
	CloseHandle(hThread);
}

