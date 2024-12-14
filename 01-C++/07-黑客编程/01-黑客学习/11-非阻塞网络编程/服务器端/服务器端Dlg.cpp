
// ��������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��������.h"
#include "��������Dlg.h"
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


// C��������Dlg �Ի���



C��������Dlg::C��������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C��������Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C��������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_listinfo);
}

BEGIN_MESSAGE_MAP(C��������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_USER_SOCK,OnUserSock)
	ON_WM_CLOSE()
END_MESSAGE_MAP()




void C��������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C��������Dlg::OnPaint()
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
HCURSOR C��������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// C��������Dlg ��Ϣ�������

BOOL C��������Dlg::OnInitDialog()
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
	//��ʼ��WinSock��
	WSADATA wsaData;
	int nret=WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽��֣�������Ϊ�������첽ģʽ
	serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	nret=WSAAsyncSelect(serverSock, this->GetSafeHwnd(), UM_USER_SOCK, FD_ACCEPT);

	//��д��ַ��Ϣ
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = ADDR_ANY;
	serverAddr.sin_port = htons(5555);

	//�󶨵�ַ������
	nret = bind(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	nret = listen(serverSock, 5);

	m_listinfo.AddString(TEXT("Listen Port:2222..."));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

/*
�첽������ʵ�֣�
	����Զ�����Ϣ��
		#define UM_USER_SOCK (WM_USER+0x101)
	�����Ϣӳ�亯����
		afx_msg VOID OnUserSock(WPARAM wParam, LPARAM lParam);
	�����Ϣӳ�䣺
		ON_MESSAGE_VOID(UM_USER_SOCK,OnUserSock)
	ʵ����Ϣӳ�亯��

	�ڳ�ʼ���г�ʼ��������

	��һ���׽���socket()����֮��Ĭ�Ϲ���������״̬��ͬ��״̬���������ʹ�ö��̵߳Ļ����������Ϊ�ȴ���ɿ�������Ӧ�����
	��ˣ��ڲ�ʹ�ö��̵߳�����£�����Windows��Ϣ���ƣ������˷��������첽������

	����һ��SOCKET�ķ�����������int WSAAsyncSelect(SOCKET sock,HWND hWnd,unsigned int userMessage,long listenEvents);
	������Ҫ�첽���׽��֣����ܻص��Ĵ��ھ����һ���Զ�����û���Ϣ���û���Ҫ���ܵ�֪ͨ�루����ʹ��λ������

	����֪ͨ�룺
		FD_READ:�յ����ݰ���TCP�ж��ڷ���˺Ϳͻ��˶����õ�
		FD_ACCEPT:���ܿͻ��ˣ�TCP�н����ڷ�������
		FD_CONNECT:���ӳɹ���������TCP�н����ڿͻ���
		FD_CLOSE:���ӶϿ���TCP�ж��ڷ���˺Ϳͻ��˶����õ�
		�ر�ģ�UDP��ACCEPT��CONNECT��CLOSE����û������ģ���Ϊ�������ӵ�ͨ��

	�������ɻ�ʹ��������
		ʹ��MFC�����첽ͨ����ע�⣬������ܳ����һֱ���в��ԣ�Ҳ���ᱨ��
			ע����Init�ǳ�ʼ��WinSock�������������ð󶨺ͼ������ͻ��˿����ڰ�ť֮�������ӣ�
			ע����close������WinSock��Socket
		���ֽں�Unicode���໥ת����
			TCHAR * A2T(char *);(Ascii to TCHAR)
			char * T2A(TCHAR *);(TCHAR to Ascii)
			��Ȼ�������ȷ�Ŀ��ֽڻ�����ֱ��ָ����A2W W2AҲ��
			����ע�⣬ʹ������ת����ʱ����Ҫ��ʹ�õ�����������ӣ�
				USES_CONVERSION;
			���򣬲���ʹ�á�
		�ڴ濽����
			memcpy(void * targetPoint,const char * resourcePoint,int copySize);
		�򿪹�����
			mciSendString("set cdaudio door open",NULL,NULL,NULL);
		�رչ�����
			mciSendString("set cdaudio door closed",NULL,NULL,NULL);
			ʹ��msi��Ҫͷ�ļ��Ϳ⣺
				#include<mmsystem.h>
				#pragma comment(lib,"Winmm")
		����������Ҽ���
			SwapMouseButton(TRUE);
		����������Ҽ���
			SwapMouseButton(FALSE);
		���ݽṹ��char *֮��ת����
			Data -> char *:(char *)&struct,sizeof(struct)
			char * -> Data:memcpy((void *)&struct,(const void *)char * p,sizeof(struct));
			��Ȼ����ʱ�򣬽ṹ��char *֮�е�һ���֣������ǿ�ͷʱ���ǵü���ƫ�Ƶ�ַ,����ƫ��12�ֽڣ�(p+12)��p+sizeof(int)�ȵ�
		�����翪���У����ڻ���\n:
			�������\r\n
		
		������Щ֪ʶ���Ϳ�����һ���򵥵�Զ�̿����ˡ�
*/
//ִ�������У���������������������ùܵ��ͽ���
CString C��������Dlg::ExecuteCmd(CString str)
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
//�����첽��Ϣ�Ļص�����
LRESULT C��������Dlg::OnUserSock(WPARAM wParam, LPARAM lParam)
{
	//�������Ƿ����
	if (WSAGETSELECTERROR(lParam))
	{
		return 0;
	}
	//�жϲ����¼�
	switch (WSAGETSELECTEVENT(lParam))
	{
		//�¿ͻ��˽����¼���serverSock����
	case FD_ACCEPT:
	{
		//��ȡ�ͻ����׽��ֺ������Ϣ�����Ѹջ�ȡ���׽���Ҳ����Ϊ�첽ģʽ
		struct sockaddr_in clientAddr;
		int psize = sizeof(clientAddr);
		clientSock = accept(serverSock, (SOCKADDR *)&clientAddr, &psize);
		WSAAsyncSelect(clientSock, this->GetSafeHwnd(), UM_USER_SOCK, FD_READ | FD_CLOSE);
		//��ʾ������Ŀͻ���
		CString tp;
		USES_CONVERSION;
		tp.Format(TEXT("Client connected:%s:%d\n"), A2T(inet_ntoa(clientAddr.sin_addr)), ntohs(clientAddr.sin_port));
		m_listinfo.AddString(tp);
		//���͸��ͻ���ʹ��˵��
		SERVICE_DATA data;
		data.s_type = TYPE_TEXT;
		data.s_class = 0;
		lstrcpy(data.s_value, TEXT(HELPINFO));

		send(clientSock, (const char *)&data, sizeof(data), 0);
	}
		break;
		//�յ���Ϣ�¼���clientSock����
	case FD_READ:
	{
					char buffer[2048] = { 0 };
					recv(clientSock, buffer, 2048, 0);
					ProcessMsgData(buffer);
	}
		break;
		//�յ��ͻ��˹ر��¼���clientSock����
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
//ֱ�ӽ�������̨���������ز���Ľ��
void C��������Dlg::ProcessMsgData(char * buffer)
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
//�ر��׽��ֺ�����WinSock
void C��������Dlg::OnClose()
{
	closesocket(clientSock);
	closesocket(serverSock);

	WSACleanup();
	CDialogEx::OnClose();
}
