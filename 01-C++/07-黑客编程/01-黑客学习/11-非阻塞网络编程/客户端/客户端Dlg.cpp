
// �ͻ���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�ͻ���.h"
#include "�ͻ���Dlg.h"
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


// C�ͻ���Dlg �Ի���



C�ͻ���Dlg::C�ͻ���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�ͻ���Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C�ͻ���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_listinfo);
}

BEGIN_MESSAGE_MAP(C�ͻ���Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_USER_SOCK, OnUserSock)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &C�ͻ���Dlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &C�ͻ���Dlg::OnBnClickedButtonSend)
	ON_WM_CLOSE()
END_MESSAGE_MAP()



void C�ͻ���Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C�ͻ���Dlg::OnPaint()
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
HCURSOR C�ͻ���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*

*/


// C�ͻ���Dlg ��Ϣ�������

BOOL C�ͻ���Dlg::OnInitDialog()
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

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SetDlgItemTextA(this->GetSafeHwnd(), IDC_EDIT_IP_ADDR, "127.0.0.1");
	m_listinfo.AddString(TEXT("����\n"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
LRESULT C�ͻ���Dlg::OnUserSock(WPARAM wParam, LPARAM lParam)
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
		m_listinfo.AddString(TEXT("���ӳɹ���\n"));
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
		m_listinfo.AddString(TEXT("�Է��ѹر�����\n"));
	}
		break;
	}
	return 0;
}
void C�ͻ���Dlg::OnBnClickedButtonConnect()
{
	CString ConnBtnName;
	GetDlgItemText(IDC_BUTTON_CONNECT, ConnBtnName);
	if (ConnBtnName==TEXT("Deconnect"))
	{
		SetDlgItemText(IDC_BUTTON_CONNECT, TEXT("Connect"));
		closesocket(clientSock);
		m_listinfo.AddString(TEXT("�����Ͽ����ӣ�"));
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


void C�ͻ���Dlg::OnBnClickedButtonSend()
{
	char command[2048] = { 0 };
	GetDlgItemTextA(this->GetSafeHwnd(),IDC_EDIT_COMMAND, command, 2048);
	char scmd[2048] = { 0 };
	sprintf(scmd,"cmd /c %s\0",command);
	send(clientSock, scmd, strlen(scmd), 0);
}
void C�ͻ���Dlg::ProcessMsgData(PSERVICE_DATA data)
{
	if (data->s_type == TYPE_TEXT)
	{
		m_listinfo.AddString(data->s_value);
	}
}

void C�ͻ���Dlg::OnClose()
{
	closesocket(clientSock);
	WSACleanup();
	CDialogEx::OnClose();
}
