
// 16-ע������-���������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "16-ע������-���������.h"
#include "16-ע������-���������Dlg.h"
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


// CMy16ע���������������Dlg �Ի���



CMy16ע���������������Dlg::CMy16ע���������������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy16ע���������������Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy16ע���������������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOTLOAD, m_list_bootload);
}

BEGIN_MESSAGE_MAP(CMy16ע���������������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy16ע���������������Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMy16ע���������������Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_ADDBOOT, &CMy16ע���������������Dlg::OnBnClickedButtonAddboot)
	ON_BN_CLICKED(IDC_BUTTON_DELBOOT, &CMy16ע���������������Dlg::OnBnClickedButtonDelboot)
	ON_BN_CLICKED(IDC_BUTTON_CPKEY, &CMy16ע���������������Dlg::OnBnClickedButtonCpkey)
END_MESSAGE_MAP()


// CMy16ע���������������Dlg ��Ϣ�������

BOOL CMy16ע���������������Dlg::OnInitDialog()
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
	InitListControl();
	UpdateBootRunList();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy16ע���������������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy16ע���������������Dlg::OnPaint()
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
HCURSOR CMy16ע���������������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
	���������ע�⣬��������������������У���ʹ�ù���Ա��ʽ���У�
	��
		ͨ��ö�ټ�ֵ����Ӽ�ֵ��ɾ����ֵʵ�ֶ�������Ĺ���

		ϵͳע���������·����
			HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run\
		��Ȼ�������������λ��Ҳ������������ã�������һЩ�ֶ�Ҳ����ʵ��


	ע��������
		ע���ʵ���Ͼ���һ������ÿ������������һ��������Ҷ�ӵ�֦�ɣ�ÿ��Ҷ���Ͼʹ洢ֵ��ÿ��ֵ�ֱ��У����ƣ����ͣ�����
		ע����Ǹ�����windowsϵͳ���������ݿ⣬�������漰���ļ����������������ӳ��ٳ֡��۸��������ҳ������ϵͳ���ܵ�
		Ҳ��һ��������ʵ����������ʲôע�������Ӧ�о��У�����������Ҳ�������

		�򿪺͹ر�ע���
			��ע�������LONG RegOpenKeyEx(
				HKEY hkey,//ָ��һ������������������HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS HKEY_CURRENT_CONFIG
				LPCTSTR lpSubKey,//ָ��һ��ָ���Ӽ����ַ�������
				DWORD dwOptions,//ϵͳ�����֣�����ָ��Ϊ0
				REGSAM samDisired,//��ע���Ĵ�ȡȨ�ޣ�Ϊ�˷��㣬һ��ȡ��ȫ����Ȩ�ޣ�KEY_ALL_ACCESS
				PHKEY phkResult);//ָ��һ���������մ򿪵��Ӽ������˫�ӱ���
			����ֵ���ɹ���ERROR_SUCCESS������phkResult�б���򿪵��Ӽ�

			�ر�ע�������LONG RegCloseKey(HKEY hkey);

		������ɾ���Ӽ���
			�����Ӽ�������LONG RegCreateKeyEx(
				HKEY hkey,//�������
				LPCTSTR lpSubKey,//�Ӽ������ַ���
				DWORD reserved,//ϵͳ�����֣�����Ϊ0
				LPTSTR lpClass,//�Ӽ�������һ��ΪNULL
				DWORD dwOptions,//�����Ӽ���ѡ�һ��ΪREG_OPTION_NON_VOLATILE����ʶ���������Ӽ�����ע����ļ����������ڴ���
				REGSAM samDesired,//��ע���Ĵ�ȡȨ�ޣ�ͬ��
				LPSECURITY_ATTRIBUTES lpSecurityAttributes,//һ��ΪNULL������ָ���ṹ��
				PHKEY phkResult,//�������մ򿪵ļ��ľ��˫�ӱ���
				LPSWORD lpdwDisposition);//һ��ΪNULL
			����ֵ���ɹ���ERROR_SUCCESS������hkey����������OpenKey����ע���Ҳ��ʹ�ô˺���������������಻��

			ɾ���Ӽ�������LONG RegDeleteKey(HKEY hkey,LPCTSTR lpSubKey);
			����������������Ӽ������ַ���

		ע����ֵ�Ĳ�ѯ��д���ɾ����
			��ѯ��ֵ������LONG RegQueryValueEx(
				HKEY hkey,//��ѯ���ڵ��Ӽ����
				LPCTSTR lpValueName,//��ֵ����
				LPDWORD lpReserved,//�����֣�����ΪNULL
				LPDWORD lpType,//���ܷ��صļ�ֵ���ͣ��粻��Ҫ���Ը�NULL
				LPBYTE lpData,//�������ݵĻ���
				LPDWORD lpDataSize);//���յ����ݵ�ʵ�ʴ�С

			д���ֵ������LONG RegSetValueEx(
				HKEY hkey,//��ѯ���ڵ��Ӽ����
				LPCTSTR lpValueName,//��ֵ����
				DWORD Reserved,//�����֣�����Ϊ0
				DWORD Type,//��ֵ����L
				const BYTE * lpData,//�������ݵĻ���
				DWORD DataSize);//�������ݵĴ�С

			ɾ����ֵ�����LONG RegDeleteValue(HKEY hkey,LPCTSTR lpValueName);
			������ɾ���ļ�ֵ�������ɾ���ļ�ֵ������

		�Ӽ��ͼ�ֵ��ö�٣�
			ö���Ӽ�������LONG RegEnumKeyEx(
				HKEY hkey,//��ö�ٵļ����
				DWORD dwIndex,//��Ҫ���ص��Ӽ��������
				LPTSTR lpName,//�����Ӽ����Ļ���
				LPDWORD nameCount,//���ܵ��Ӽ����ĳ���
				LPDWORD lpReserved,//ϵͳ�����֣�����Ϊ0
				LPTSTR lpClass,//һ��ΪNULL
				LPDWORD classCount,//һ��ΪNULL
				PFILETIME lpftLastWriteTime);//�ṹ��ַ���������д��ʱ��

			ö�ټ�ֵ�ĺ�����LONG RegEnumValue(
				HKEY hkey,//��ö�ٵļ����
				DWORD dwIndex,//��Ҫ���ص��Ӽ��������
				LPTSTR lpValueName,//����ֵ���ƵĻ���
				LPDWORD valueNameCount,//���ܵ�ֵ���Ƶĳ���
				LPDWORD lpReserved,//ϵͳ�����֣�����Ϊ0
				LPDWORD lpType,//ָ���ֵ���͵�˫�ֱ���
				LPBYTE lpData,/ָ�����ֵ���ݵĻ���
				LPDWORD countData);//���յ�ֵ���ݵ�ʵ�ʴ�С

*/
#include"BootItemAdder.h"
//ϵͳ������ļ�·��
const TCHAR REG_BOOT_RUN[] = { TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\") };
#define REG_MAX_KEY 1024
#define REG_SHOW_COUNT 19
//����ע����������λ�úͶ�Ӧ�ĸ�
const HKEY ALL_REG_BOOT_ROOT[REG_SHOW_COUNT] = {
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE ,
	
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_LOCAL_MACHINE,
	HKEY_LOCAL_MACHINE,
	HKEY_LOCAL_MACHINE,

	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_LOCAL_MACHINE,
};
const TCHAR ALL_REG_BOOT_ROOT_STR[REG_SHOW_COUNT][20] = {
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_LOCAL_MACHINE"),

	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_LOCAL_MACHINE"),
};
const TCHAR ALL_REG_BOOT_KEY[REG_SHOW_COUNT][REG_MAX_KEY] = {
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"),

TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\Windows\\Load\\"),
TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\BootExecute\\"),
TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\SetupExecute\\"),
TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Execute\\"),
TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\S0InitialCommand\\"),

TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\"),
TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\Userinit\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunServices\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\Setup\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\Setup\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx\\"),
};
//��ʼ��List Control
void CMy16ע���������������Dlg::InitListControl()
{
	//������չ��ʽ���������ߺ�ѡ��һ����
	m_list_bootload.SetExtendedStyle(m_list_bootload.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	//������
	m_list_bootload.InsertColumn(0, TEXT("NO."));
	m_list_bootload.InsertColumn(1, TEXT("��                                    ��"));
	m_list_bootload.InsertColumn(2, TEXT("��                                                                        ֵ"));
	m_list_bootload.InsertColumn(3, TEXT("��  ·  ��"));
	//�����Զ��п�
	m_list_bootload.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_bootload.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_list_bootload.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_list_bootload.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
}
//����List Control ����
void CMy16ע���������������Dlg::UpdateBootRunList()
{
	//���list����
	m_list_bootload.DeleteAllItems();
	int dispalyIndex = 0;
	for (int i = 0; i < REG_SHOW_COUNT; i++)
	{
		//��ע����
		HKEY hkey = NULL;
		long ret = RegOpenKeyEx(ALL_REG_BOOT_ROOT[i], ALL_REG_BOOT_KEY[i], 0, KEY_ALL_ACCESS, &hkey);
		if (ret != ERROR_SUCCESS)
		{
			return;
		}
		//ö������
		int index = 0;
		CString temp;
		//ֵ���ƺ�ֵ���ݺ�����յ����ݵĴ�С
		TCHAR szValueName[MAXBYTE] = { 0 };
		TCHAR szValueKey[MAXBYTE] = { 0 };
		DWORD dwBufferSize = MAXBYTE;
		DWORD dwKeySize = MAXBYTE;
		//ֵ����������
		DWORD dwType = 0;
		//ö�����е�ֵ
		while (TRUE)
		{
			ret = RegEnumValue(hkey, index, szValueName, &dwBufferSize, NULL, &dwType, (unsigned char *)szValueKey, &dwKeySize);
			//���û�и����ֵ����˳�
			if (ret == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			//���ö�ٵ����ݵ�list
			temp.Format(TEXT("%d"), dispalyIndex);
			m_list_bootload.InsertItem(dispalyIndex, temp);
			m_list_bootload.SetItemText(dispalyIndex, 1, szValueName);
			m_list_bootload.SetItemText(dispalyIndex, 2, szValueKey);
			temp.Format(TEXT("%s\\%s"),ALL_REG_BOOT_ROOT_STR[i],ALL_REG_BOOT_KEY[i]);
			m_list_bootload.SetItemText(dispalyIndex, 3, temp);
			//���û��壬��Ϊ��һ��ö����׼��
			ZeroMemory(szValueKey, sizeof(szValueKey));
			ZeroMemory(szValueName, sizeof(szValueName));

			dwBufferSize = MAXBYTE;
			dwKeySize = MAXBYTE;
			index++;
			dispalyIndex++;

		}
		//�ر�ע����
		RegCloseKey(hkey);
	}
	
}
void CMy16ע���������������Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CMy16ע���������������Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CMy16ע���������������Dlg::OnBnClickedButtonAddboot()
{
	//���������Ի���
	CBootItemAdder adder;
	adder.DoModal();
	//��������������
	if (!adder.m_bootkey.IsEmpty() && !adder.m_bootvalue.IsEmpty())
	{
		HKEY hkey = NULL;
		long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_BOOT_RUN, 0, KEY_ALL_ACCESS, &hkey);
		if (ret != ERROR_SUCCESS)
		{
			return;
		}

		RegSetValueEx(hkey, adder.m_bootkey, 0, REG_SZ, (unsigned char *)adder.m_bootvalue.GetBuffer(), adder.m_bootvalue.GetLength()*2+1);
		RegCloseKey(hkey);
		UpdateBootRunList();
	}
	
}


void CMy16ע���������������Dlg::OnBnClickedButtonDelboot()
{
	//��ȡѡ����
	POSITION pos = m_list_bootload.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_list_bootload.GetNextSelectedItem(pos);
	}
	//���û��ѡ�����򷵻�
	if (selIndex == -1)
	{
		return;
	}
	//��ȡѡ�������Ʋ�ɾ����ֵ
	TCHAR szValueName[MAXBYTE] = { 0 };
	m_list_bootload.GetItemText(selIndex, 1, szValueName, MAXBYTE);
	HKEY hkey = NULL;
	long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_BOOT_RUN, 0, KEY_ALL_ACCESS, &hkey);
	if (ret != ERROR_SUCCESS)
	{
		return;
	}
	RegDeleteValue(hkey,szValueName);
	RegCloseKey(hkey);
	UpdateBootRunList();
}


void CMy16ע���������������Dlg::OnBnClickedButtonCpkey()
{
	//��ȡѡ����
	POSITION pos = m_list_bootload.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_list_bootload.GetNextSelectedItem(pos);
	}
	//���û��ѡ�����򷵻�
	if (selIndex == -1)
	{
		return;
	}
	//��ȡѡ�������Ʋ�ɾ����ֵ
	TCHAR szKeyPath[MAXBYTE] = { 0 };
	m_list_bootload.GetItemText(selIndex, 3, szKeyPath, MAXBYTE);

	USES_CONVERSION;
	//���������а�
	//�򿪼��а�����޸�
	if (OpenClipboard())
	{
		HGLOBAL hclipbuffer;
		char   *   buffer;
		//��ռ��а�����
		EmptyClipboard();
		//����ȫ�ֹ����ڴ�鲢��þ��
		hclipbuffer = GlobalAlloc(GMEM_DDESHARE, strlen(T2A(szKeyPath)) + sizeof(char));
		//����ȫ�ֵ��ڴ���󲢷��ص�ַָ��
		buffer = (char*)GlobalLock(hclipbuffer);
		strcpy(buffer, LPCSTR(T2A(szKeyPath)));
		//���������ȫ���ڴ����
		GlobalUnlock(hclipbuffer);
		//�����ı���ʽ������а�����
		SetClipboardData(CF_TEXT, hclipbuffer);
		//�رռ��а壬���������ʹ��
		CloseClipboard();
	}
}
