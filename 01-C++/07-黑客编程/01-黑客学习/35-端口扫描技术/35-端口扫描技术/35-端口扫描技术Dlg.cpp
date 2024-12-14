
// 35-�˿�ɨ�輼��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "35-�˿�ɨ�輼��.h"
#include "35-�˿�ɨ�輼��Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMy35�˿�ɨ�輼��Dlg �Ի���



CMy35�˿�ɨ�輼��Dlg::CMy35�˿�ɨ�輼��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy35�˿�ɨ�輼��Dlg::IDD, pParent)
	, m_strHostName(_T(""))
	, m_iportStart(0)
	, m_iportEnd(0)
	, m_iTimeout(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy35�˿�ɨ�輼��Dlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(CMy35�˿�ɨ�輼��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy35�˿�ɨ�輼��Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMy35�˿�ɨ�輼��Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_TRANSLATE, &CMy35�˿�ɨ�輼��Dlg::OnBnClickedButtonTranslate)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CMy35�˿�ɨ�輼��Dlg::OnBnClickedButtonScan)
END_MESSAGE_MAP()


// CMy35�˿�ɨ�輼��Dlg ��Ϣ�������

BOOL CMy35�˿�ɨ�輼��Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	InitControls();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy35�˿�ɨ�輼��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy35�˿�ɨ�輼��Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy35�˿�ɨ�輼��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy35�˿�ɨ�輼��Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
/*
�˿�ɨ�輼����
	˵�򵥵���ǳ�������һ��������ÿһ���˿ڣ���������ӣ���ô��˵���˶˿��ǿ�ͨ��

	�˿�ɨ����ԶԵ�һ��������ɨ��һ�������ڵĶ˿�
	Ҳ���Զ�һ������ĵ�ַɨ��һ������Ķ˿�
	����ʵ�ֵ��ǵڶ���
		�����ʼɨ��֮�󣬻�ȡ��ֹIP�Ͷ˿ںŵ���Ϣ��Ȼ������ɨ������̣߳�����ɨ�����߳�ȥִ��ɨ��

	���ǣ��˿�ɨ�������������
		Ŀ���ַ�����ڣ�����һֱ�����ϣ��˷�ʱ��ȴ�
		Ŀ���ַ���ڣ�����Ŀ��˿�δʹ�ã���Ҳ��һֱ������

		����������ǣ�ʹ�÷����������ӷ�ʽ�����ó�ʱʱ���������
		����ʹ�ö��߳̽������ӣ��ٴμ��ٵȴ�ʱ��
		�����Կ��ǹ���ping������Ŀ���ַ�Ƿ���ڣ���һ������ʱ��

	��Ȼ����ʹ�ö��̣߳���ô�Ͳ��ò������ٽ�����Դ��Ҳ�����̰߳�ȫ
	�����Ҫʹ���ź������¼������п���

	�����ź���������
		HANDLE
		WINAPI
		CreateSemaphoreW(
		_In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, //SD
		_In_     LONG lInitialCount,	//��ʼ����
		_In_     LONG lMaximumCount,	//������
		_In_opt_ LPCTSTR lpName	//������
		);

	�ͷ��ź�������
		BOOL
		WINAPI
		ReleaseSemaphore(
		_In_ HANDLE hSemaphore,//�ź������
		_In_ LONG lReleaseCount,//�����ĵݼ���
		_Out_opt_ LPLONG lpPreviousCount//ǰһ������ֵ����ָ��
		);

	�����¼�������
		HANDLE
		WINAPI
		CreateEventW(
		_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,//SD
		_In_ BOOL bManualReset,//��������
		_In_ BOOL bInitialState,//��ʼ״̬
		_In_opt_ LPCTSTR lpName//������
		);

	�¼������ź�״̬����
		BOOL
		WINAPI
		SetEvent(
		_In_ HANDLE hEvent//�¼����
		);

	�¼��������ź�״̬����
		BOOL
		WINAPI
		ResetEvent(
		_In_ HANDLE hEvent//�¼����
		);
	�ź������¼������WaitForSingleObjectʹ�ã�����ȴ��������źŲŻ����ִ�У������һֱ�ȴ�������ȴ����ݴ�����������ܴ����г�ʱ��

*/


void CMy35�˿�ɨ�輼��Dlg::InitControls()
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

void CMy35�˿�ɨ�輼��Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
#include<WinSock2.h>
#pragma comment(lib,"ws2_32")

void CMy35�˿�ɨ�輼��Dlg::OnBnClickedButtonTranslate()
{
	/*
	����ת��
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
		MessageBox(TEXT("����ת��ʧ�ܣ���������Ч���������������ӣ���"));
	}
	WSACleanup();
}
//��ɨ���̲߳����ṹ
typedef struct _ThreadPortScanInfo
{
	DWORD dwIPStart;//ɨ����ʼIP
	DWORD dwIPEnd;//ɨ����ֹIP
	WORD wdPortStart;//ɨ����ʼPort
	WORD wdPortEnd;//ɨ����ֹPort
	DWORD dwTimeOutMilliSecond;//�˿�ɨ�賬ʱ
	CMy35�˿�ɨ�輼��Dlg * lpWndMain;//������ָ��
	HANDLE hEvent;//�¼����
}ThreadPortScanInfo, *PThreadPortScanInfo;
//ɨ�����̲߳����ṹ
typedef struct _ScanInfo
{
	DWORD dwIp;//ɨ��IP
	WORD wdPort;//ɨ��˿�
	HANDLE hEvent;//�¼����
	HANDLE hSemaphore;//�ź������
	DWORD dwTimeOutMilliSecond;//�˿�ɨ�賬ʱ
	CMy35�˿�ɨ�輼��Dlg * lpWndMain;//������ָ��
	HTREEITEM hTree;//���οؼ���Ŀ���
}ScanInfo, *PScanInfo;
#define MAX_THREAD 20 //���ɨ���߳���
DWORD WINAPI SubScanFunc(LPVOID lpThreadParameter)
{
	//�������ݹ����Ĳ���
	ScanInfo scanInfo = { 0 };
	MoveMemory(&scanInfo, lpThreadParameter, sizeof(ScanInfo));
	//�����¼��źŴ��ڣ��⽫��Ӱ�쵽�����ߴ���WaitSingleObject
	SetEvent(scanInfo.hEvent);
	//��WSA��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	//�����׽���
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//����Ŀ��IP��port��Ϣ
	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.S_un.S_addr = htonl(scanInfo.dwIp);
	sockaddr.sin_port = htons(scanInfo.wdPort);
	//�Ƿ�ʹ���첽��ʱ�����ӷ�ʽ
	/*
	�����ʹ���첽��ʱ�ķ�ʽ���ӣ�
	��ô�����˿ڲ����õ�������������Ĵ�����ʱ��ȴ�����ɲ���Ҫ��ʱ��ȴ�
	*/
#define USE_ASYN_MODE_SCAN 1
#if USE_ASYN_MODE_SCAN
	TIMEVAL timeOut;
	FD_SET mask;
	unsigned long mode = 1;

	//����ɨ�賬ʱ
	timeOut.tv_sec = 0;
	timeOut.tv_usec = scanInfo.dwTimeOutMilliSecond;

	FD_ZERO(&mask);
	FD_SET(sock,&mask);
	//����Ϊ�������׽���
	/*
	�����׽���ģʽ
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
	��ѯ��д��״̬
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
		//�����ӳɹ���IP��Port��ʾ����Ӧ�����οؼ���Ŀ��
		
		str.Format(TEXT("%d"),scanInfo.wdPort);
		scanInfo.lpWndMain->m_tree_info.InsertItem(str, 1, 1, scanInfo.hTree);
		scanInfo.lpWndMain->m_tree_info.Expand(scanInfo.hTree, 0);
		scanInfo.lpWndMain->m_tree_info.Invalidate(FALSE);
	}
#else
	if (connect(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr)) == 0)
	{
		//�����ӳɹ���IP��Port��ʾ����Ӧ�����οؼ���Ŀ��
		CString str;
		str.Format(TEXT("%d"),scanInfo.wdPort);
		scanInfo.lpWndMain->m_tree_info.InsertItem(str, 1, 1, scanInfo.hTree);
		scanInfo.lpWndMain->m_tree_info.Invalidate(FALSE);
	}
#endif //USE_ASYN_MODE_SCAN
	//�Ͽ��׽��ֲ�����WSA��
	closesocket(sock);
	WSACleanup();

	//�ͷ�һ���ź���
	ReleaseSemaphore(scanInfo.hSemaphore, 1, NULL);

	return 0;
}
DWORD WINAPI ThreadPortScanFunc(LPVOID lpThreadParameter)
{
	//�������ݹ����Ĳ���
	ThreadPortScanInfo thrInfo = { 0 };
	MoveMemory(&thrInfo, lpThreadParameter, sizeof(ThreadPortScanInfo));
	//�����¼��źŴ��ڣ��⽫��Ӱ�쵽�����ߴ���WaitSingleObject
	SetEvent(thrInfo.hEvent);
	//�����¼�������ź������󣬸�ֵ���ṹ
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE hSemaphore = CreateSemaphore(NULL, MAX_THREAD, MAX_THREAD, NULL);
	//�ṹ��ֵ
	ScanInfo scanInfo = { 0 };
	scanInfo.hEvent = hEvent;
	scanInfo.hSemaphore = hSemaphore;
	scanInfo.lpWndMain = thrInfo.lpWndMain;
	scanInfo.dwTimeOutMilliSecond = thrInfo.dwTimeOutMilliSecond;
	//��ǰ��Ҫɨ���IP��Port
	DWORD dwCurrentIP;
	WORD wdCurrentPort;
	//����ÿ��IP
	for (dwCurrentIP = thrInfo.dwIPStart; dwCurrentIP <= thrInfo.dwIPEnd; dwCurrentIP++)
	{
		//���ò���ɨ��IP
		scanInfo.dwIp = dwCurrentIP;
		//����ǰɨ��IP��ӵ����οؼ���ʾ
		struct sockaddr_in sockaddr;
		sockaddr.sin_addr.S_un.S_addr = ntohl(dwCurrentIP);
		USES_CONVERSION;
		HTREEITEM hTreeItem = (thrInfo.lpWndMain)->m_tree_info.InsertItem(A2T(inet_ntoa(sockaddr.sin_addr)));
		(thrInfo.lpWndMain)->m_tree_info.Invalidate(FALSE);
		//����ÿ��Port
		for (wdCurrentPort = thrInfo.wdPortStart; wdCurrentPort <= thrInfo.wdPortEnd; wdCurrentPort++)
		{
			//����ź�������ʱ200ms
			DWORD dwWaitReturn = WaitForSingleObject(hSemaphore, 200);
			if (dwWaitReturn == WAIT_OBJECT_0)
			{
				//�ź��������������߳̽���ɨ��
				scanInfo.wdPort = wdCurrentPort;
				scanInfo.hTree = hTreeItem;

				HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SubScanFunc, (LPVOID)&scanInfo, 0, NULL);
				WaitForSingleObject(hEvent, INFINITE);
				ResetEvent(hEvent);
				//�ж��Ƿ������һ��ɨ�裬������ʾ
				if (wdCurrentPort == thrInfo.wdPortEnd && dwCurrentIP == thrInfo.dwIPEnd)
				{
					MessageBox((thrInfo.lpWndMain)->GetSafeHwnd(), TEXT("�˿�ɨ�������"), TEXT("ɨ����ʾ"), MB_OK);
				}
			}
			else if (dwWaitReturn==WAIT_TIMEOUT)
			{
				//�ź�������������п�ת�������ȴ�
				wdCurrentPort--;
				continue;
			}
		}
	}
	return 0;
}
void CMy35�˿�ɨ�輼��Dlg::OnBnClickedButtonScan()
{
	m_tree_info.DeleteAllItems();
	//��ȡ��ֹIP��Port����ֵ�̲߳����ṹ
	UpdateData(TRUE);
	ThreadPortScanInfo thrInfo = { 0 };
	m_ipAddrStart.GetAddress(thrInfo.dwIPStart);
	m_ipAddrEnd.GetAddress(thrInfo.dwIPEnd);

	thrInfo.wdPortStart = m_iportStart;
	thrInfo.wdPortEnd = m_iportEnd;

	thrInfo.dwTimeOutMilliSecond = m_iTimeout;
	//�����¼�
	HANDLE hEnvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//��ֵ�¼��ʹ���ָ��
	thrInfo.hEvent = hEnvent;
	thrInfo.lpWndMain = this;
	//�����߳�
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPortScanFunc, (LPVOID)&thrInfo, 0, NULL);
	WaitForSingleObject(hEnvent, INFINITE);
	ResetEvent(hEnvent);
	CloseHandle(hEnvent);
	CloseHandle(hThread);
}

