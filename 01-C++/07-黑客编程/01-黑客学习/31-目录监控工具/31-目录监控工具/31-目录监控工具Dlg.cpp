
// 31-Ŀ¼��ع���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "31-Ŀ¼��ع���.h"
#include "31-Ŀ¼��ع���Dlg.h"
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


// CMy31Ŀ¼��ع���Dlg �Ի���



CMy31Ŀ¼��ع���Dlg::CMy31Ŀ¼��ع���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy31Ŀ¼��ع���Dlg::IDD, pParent)
	, m_strSpyPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy31Ŀ¼��ع���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_SPY_PATH, m_strSpyPath);
	DDX_Control(pDX, IDC_LIST_SPY_LOG, m_list_spy_log);
	DDX_Control(pDX, IDC_BUTTON_SPY_ON, m_btn_spyon);
	DDX_Control(pDX, IDC_BUTTON_SPY_OFF, m_btn_spyoff);
}

BEGIN_MESSAGE_MAP(CMy31Ŀ¼��ع���Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy31Ŀ¼��ع���Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SPY_ON, &CMy31Ŀ¼��ع���Dlg::OnBnClickedButtonSpyOn)
	ON_BN_CLICKED(IDC_BUTTON_SPY_OFF, &CMy31Ŀ¼��ع���Dlg::OnBnClickedButtonSpyOff)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_LIST, &CMy31Ŀ¼��ع���Dlg::OnBnClickedButtonClearList)
END_MESSAGE_MAP()


// CMy31Ŀ¼��ع���Dlg ��Ϣ�������

BOOL CMy31Ŀ¼��ع���Dlg::OnInitDialog()
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
	InitFaceControl();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy31Ŀ¼��ع���Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy31Ŀ¼��ع���Dlg::OnPaint()
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
HCURSOR CMy31Ŀ¼��ع���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy31Ŀ¼��ع���Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
/*
Ŀ¼��غ�����
	BOOL ReadDirectoryChangesW(
    _In_        HANDLE hDirectory,//ָ��Ҫ��ص�Ŀ¼�ľ������Ŀ¼Ҫ��FILE_LIST_DIRECTORY�ķ���Ȩ�޴�
    _Out_writes_bytes_to_(nBufferLength, *lpBytesReturned) LPVOID lpBuffer,//����ָ��һ����ŷ��ؽ���Ļ����������ΪFILE_NOTIFY_INFORMATION�Ľṹ�壬���ڸýṹ�����һ����Ա��һ�ֽڵ�����
    _In_        DWORD nBufferLength,//��ʶ�������Ĵ�С
    _In_        BOOL bWatchSubtree,//ָʾ�Ƿ�����Ŀ¼�Ĳ���
    _In_        DWORD dwNotifyFilter,//ָʾҪ���غ������͵��ļ�����������
    _Out_opt_   LPDWORD lpBytesReturned,//�����ķ��ص����ݴ�С
    _Inout_opt_ LPOVERLAPPED lpOverlapped,//����ִ��һ��OVERLAPPED�ṹ�壬�����첽����ʱ��һ��ΪNULL
    _In_opt_    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine//�첽�ص�������һ��ΪNULL
    );
*/
//ȫ�ֱ������ṩ���̺߳���ʹ��
static CListCtrl * g_p_list_spy_log;
static HANDLE g_hSpyFile;
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	//����б��
	g_p_list_spy_log->DeleteAllItems();
	//����ṹ�����ݶ���
	BYTE buffer[1024] = { 0 };
	int bufferSize = sizeof(buffer);
	FILE_NOTIFY_INFORMATION * pbuffer = (FILE_NOTIFY_INFORMATION *)buffer;
	
	BOOL bret = FALSE;
	DWORD bytesReturned = 0;
	int index = 0;
	//ѭ����ȡ�仯�ļ�¼
	while (true)
	{
		//��ȡ������Ϣ
		bret = ReadDirectoryChangesW(g_hSpyFile,
			&buffer,
			bufferSize,
			TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME |//�������в���
			FILE_NOTIFY_CHANGE_ATTRIBUTES |
			FILE_NOTIFY_CHANGE_LAST_WRITE|
			FILE_NOTIFY_CHANGE_CREATION|
			FILE_NOTIFY_CHANGE_DIR_NAME|
			FILE_NOTIFY_CHANGE_LAST_ACCESS|
			FILE_NOTIFY_CHANGE_SECURITY|
			FILE_NOTIFY_CHANGE_SIZE,
			&bytesReturned,
			NULL, NULL);
		if (bret == TRUE)//��ʾ������Ϣ
		{
			switch (pbuffer->Action)
			{
			case FILE_ACTION_ADDED:
				g_p_list_spy_log->InsertItem(index, TEXT("���"));
			case FILE_ACTION_REMOVED:
				 g_p_list_spy_log->InsertItem(index, TEXT("ɾ��"));
			case FILE_ACTION_MODIFIED:
				g_p_list_spy_log->InsertItem(index, TEXT("�޸�"));
			case FILE_ACTION_RENAMED_NEW_NAME:
			{
				if (pbuffer->Action == FILE_ACTION_RENAMED_NEW_NAME)//����ʹ����case�Ĵ�͸���ʣ����Դ˴���Ҫ�ж�
					g_p_list_spy_log->InsertItem(index, TEXT("������(new)"));
				g_p_list_spy_log->SetItemText(index, 1, pbuffer->FileName);//��Ӳ�������
				if (pbuffer->NextEntryOffset != 0)//��Ӳ������
				{//���������һ��������������ݾ�����������ھ��ÿ�
					 FILE_NOTIFY_INFORMATION * tpbuffer = (FILE_NOTIFY_INFORMATION *)((DWORD)pbuffer + pbuffer->NextEntryOffset);
					 g_p_list_spy_log->SetItemText(index, 2, tpbuffer->FileName);
				}
				else
					 g_p_list_spy_log->SetItemText(index, 2, TEXT(""));
				index++;//���б���в����λ������
			}
				break;
			case FILE_ACTION_RENAMED_OLD_NAME:
			{
									  g_p_list_spy_log->InsertItem(index, TEXT("������"));
									  g_p_list_spy_log->SetItemText(index, 1, pbuffer->FileName);
									  if (pbuffer->NextEntryOffset != 0)
									  {
										  FILE_NOTIFY_INFORMATION * tpbuffer = (FILE_NOTIFY_INFORMATION *)((DWORD)pbuffer+pbuffer->NextEntryOffset);
										  switch (tpbuffer->Action)
										  {
										  case FILE_ACTION_RENAMED_NEW_NAME://��ȡ������֮������ļ���
										  {
																			   g_p_list_spy_log->SetItemText(index, 2, tpbuffer->FileName);
										  }
											  break;
										  }
										 
									  }else
										g_p_list_spy_log->SetItemText(index, 2, TEXT(""));
									  index++;
			}
				break;
				
			}
			if (index < 0)//�������������������
			{
				index = 0;
				g_p_list_spy_log->DeleteAllItems();
			}

		}
	}
	return 0;
}
void CMy31Ŀ¼��ع���Dlg::OnBnClickedButtonSpyOn()
{
	UpdateData(TRUE);
	if (m_strSpyPath == "")//��ȡ�����Ŀ¼���п�
		return;
	g_hSpyFile = CreateFile(m_strSpyPath,//�����Ŀ¼���м���
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);
	if (g_hSpyFile == INVALID_HANDLE_VALUE)
	{
		g_hSpyFile = NULL;
		return;
	}
	g_p_list_spy_log = &m_list_spy_log;//�����̺߳���ʹ�õ�ȫ�ֱ����������ð�ť״̬
	m_btn_spyon.EnableWindow(FALSE);
	m_btn_spyoff.EnableWindow(TRUE);
	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);//�����߳�
	//WaitForSingleObject(hThread, INFINITE);//����ֻ��һ����ʾ�ȴ��߳̽������ѣ����ﲢ����Ҫ�ȴ�����
}


void CMy31Ŀ¼��ع���Dlg::OnBnClickedButtonSpyOff()
{
	m_btn_spyon.EnableWindow(TRUE);
	m_btn_spyoff.EnableWindow(FALSE);//�л���ť״̬
	TerminateThread(hThread, 0);//��ֹ�߳�
	if (hThread != NULL)//�ͷž��
		CloseHandle(hThread);
	if (g_hSpyFile != NULL)
		CloseHandle(g_hSpyFile);
	hThread = NULL;
	g_hSpyFile = NULL;

}

void CMy31Ŀ¼��ع���Dlg::InitFaceControl()
{
	//������չ��ʽ���������ߺ�ѡ��һ����
	m_list_spy_log.SetExtendedStyle(m_list_spy_log.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//������
	m_list_spy_log.InsertColumn(0, TEXT("������Ϊ"));
	m_list_spy_log.InsertColumn(1, TEXT("��       ��       ��       ��"));
	m_list_spy_log.InsertColumn(2, TEXT("��       ��       ��       ��"));
	//�����Զ��п�
	m_list_spy_log.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_spy_log.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_list_spy_log.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	//Ĭ�ϲ��������
	hThread = NULL;
	g_hSpyFile = NULL;
	
	m_btn_spyoff.EnableWindow(FALSE);
}


void CMy31Ŀ¼��ع���Dlg::OnBnClickedButtonClearList()
{
	m_list_spy_log.DeleteAllItems();
}
