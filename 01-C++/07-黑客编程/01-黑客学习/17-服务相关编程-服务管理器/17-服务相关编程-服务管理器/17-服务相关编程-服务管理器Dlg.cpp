
// 17-������ر��-���������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "17-������ر��-���������.h"
#include "17-������ر��-���������Dlg.h"
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


// CMy17������ر�̷��������Dlg �Ի���



CMy17������ر�̷��������Dlg::CMy17������ر�̷��������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy17������ر�̷��������Dlg::IDD, pParent)
	, m_display_type(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy17������ر�̷��������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVICE, m_list_service);
}

BEGIN_MESSAGE_MAP(CMy17������ر�̷��������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CMy17������ر�̷��������Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CMy17������ر�̷��������Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_WINAPP, &CMy17������ر�̷��������Dlg::OnBnClickedRadioWinapp)
	ON_BN_CLICKED(IDC_RADIO_DRIVE, &CMy17������ر�̷��������Dlg::OnBnClickedRadioDrive)
	ON_BN_CLICKED(IDC_BUTTON_START, &CMy17������ر�̷��������Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_BAN, &CMy17������ر�̷��������Dlg::OnBnClickedButtonBan)
	ON_BN_CLICKED(IDC_RADIO_ALLSVC, &CMy17������ر�̷��������Dlg::OnBnClickedRadioAllsvc)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_SERVICE, &CMy17������ر�̷��������Dlg::OnLvnColumnclickListService)
END_MESSAGE_MAP()


// CMy17������ر�̷��������Dlg ��Ϣ�������

BOOL CMy17������ر�̷��������Dlg::OnInitDialog()
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
	InitView();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy17������ر�̷��������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy17������ر�̷��������Dlg::OnPaint()
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
HCURSOR CMy17������ر�̷��������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
	�ر������ͷ�ļ���
		#include<winnt.h>//NT ϵͳ֧��
		#include<winsvc.h>//service ֧��
	ö�ٷ������ͣ�
		SERVICE_DRIVE:������������
		SERVICE_WIN32:Win32Ӧ�÷�������
		SERVICE_TYPE_ALL:���з�������

	�򿪺͹رշ����������
		�򿪷��������������SC_HANDLE OpenSCManager(
			LPCTSTR lpMachineName,//��Ҫ�򿪵ķ�����ƹ��������ݿ��������������ΪNULL
			LPCTSTR lpDataBaseName,//ָ��Ŀ������SCM���ݿ����ֵ��ַ���
			DWORD dwDesiredAccess);//ָ����SCM���ݿ�ķ���Ȩ��
		����ֵ���ɹ����ؾ����ʧ�ܷ���NULL

		�رշ�����������BOOL CloseServiceHandle(SC_HANDLE hscobj);
		���ã������ر�OpenSCManager��OpenService�򿪵ľ��

	�����ö�٣�
		ö�ٺ�����BOOL EnumServicesStatus(
			SC_HANDLE hscManager,//������������
			DWORD dwServiceType,//ָ��ö�ٵķ�������
			DWORD dwServiceState,//ö��ָ��״̬�ķ���
			LPENUM_SERVICE_STATUS lpServiceBuffer,//�ṹָ��
			DWORD cbBufferSize,//��������С
			LPDWORD pcbBytesNeeded,//����ʵ��ʹ�õĻ�������С
			LPDWORD lpServiceCountReturned,//����ö�ٵķ���ĸ���
			LPDWORD lpResumeHandle);//����ö���Ƿ�ɹ�

		�ṹ���壺
			typedef struct _ENUM_SERVICE_STATUSW {
			LPTSTR            lpServiceName;
			LPTSTR            lpDisplayName;
			SERVICE_STATUS    ServiceStatus;
			} ENUM_SERVICE_STATUS, *LPENUM_SERVICE_STATUS;

			typedef struct _SERVICE_STATUS {
			DWORD   dwServiceType;
			DWORD   dwCurrentState;
			DWORD   dwControlsAccepted;
			DWORD   dwWin32ExitCode;
			DWORD   dwServiceSpecificExitCode;
			DWORD   dwCheckPoint;
			DWORD   dwWaitHint;
			} SERVICE_STATUS, *LPSERVICE_STATUS;

	�����������ֹͣ��
		�򿪷�������SC_HANDLE OpenService(
			SC_HANDLE hscManager,//������������
			LPCTSTR lpServiceName,//Ҫ�򿪵ķ������ַ���
			DWORD dwDesiredAccess);//Ҫ�򿪵ķ���ķ���Ȩ�ޣ�Ϊ�˷��㣬һ�㣺SC_MANAGER_ALL_ACCESS
		����ֵ��ʧ��NULL���ɹ��򿪵ķ�����

		������������BOOL StartService(
			SC_HANDLE hService,//�Ѿ��򿪵ķ�����
			DWORD dwNUmServiceArgs,//ָ��������������Ĳ�������
			LPCTSTR * lpServiceArgVectors);//��������

		ֹͣ��������BOOL ControlService(
			SC_HANDLE hservice,//�Ѿ��򿪵ķ�����
			DWORD dwControl,//Ҫ���͵Ŀ�����
			LPSERVICE_STATUS lpServiceStatus);//���ط����״̬
			ֹͣ����Ŀ����룺SERVICE_CONTROL_STOP
			ע�⣬û��StopService
*/
#include<winnt.h>
#include<winsvc.h>
void CMy17������ر�̷��������Dlg::InitView()
{
	//����list��չ����������ѡ������
	m_list_service.SetExtendedStyle(m_list_service.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//����list��
	m_list_service.InsertColumn(0, TEXT("������                "));
	m_list_service.InsertColumn(1, TEXT("��ʾ��                                "));
	m_list_service.InsertColumn(2, TEXT("״̬   "));
	//����list�п�
	m_list_service.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_service.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_list_service.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	//Ĭ��ѡ��WinAppService
	CheckDlgButton(IDC_RADIO_WINAPP, 1);
	//��ʾ����list
	m_display_type = SERVICE_WIN32;
	UpdateList(m_display_type);
}
void CMy17������ر�̷��������Dlg::UpdateList(unsigned long serviceType)
{
	m_list_service.DeleteAllItems();

	//�򿪷��������
	SC_HANDLE  hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		return;
	}
	//��ѯ������������������С��ʹ��һЩ���������ȡ�ļ���
	DWORD serviceCount = 0;
	DWORD dwSize = 0;
	BOOL ret = EnumServicesStatus(hSCM, serviceType, SERVICE_STATE_ALL, NULL, 0, &dwSize, &serviceCount, NULL);
	//����������ݵ�ָ��
	LPENUM_SERVICE_STATUS lpInfo;
	//��������Ĳ�ѯ����Ϊû�и������ܻ�����������ʧ��ERROR_MORE_DATA����Ҫ����Ļ�����
	if (!ret && GetLastError() == ERROR_MORE_DATA)
	{
		//����ƥ��ռ�
		lpInfo = (LPENUM_SERVICE_STATUS)(new BYTE[dwSize]);
		//��ȡ�������ݲ�����
		ret = EnumServicesStatus(hSCM, serviceType, SERVICE_STATE_ALL, (LPENUM_SERVICE_STATUS)lpInfo, dwSize, &dwSize, &serviceCount, NULL);
		if (!ret)
		{
			//�������ݻ�ȡʧ����رշ�����
			CloseServiceHandle(hSCM);
			return;
		}
		//������õķ��񣬽�����䵽�б�
		for (DWORD i = 0; i < serviceCount; i++)
		{
			m_list_service.InsertItem(i, lpInfo[i].lpServiceName);
			m_list_service.SetItemText(i, 1, lpInfo[i].lpDisplayName);
			switch (lpInfo[i].ServiceStatus.dwCurrentState)
			{
			case SERVICE_PAUSED:
				m_list_service.SetItemText(i, 2, TEXT("��ͣ"));
				break;
			case SERVICE_STOPPED:
				m_list_service.SetItemText(i, 2, TEXT("ֹͣ"));
				break;
			case SERVICE_RUNNING:
				m_list_service.SetItemText(i, 2, TEXT("����"));
				break;
			default:
				m_list_service.SetItemText(i, 2, TEXT("����"));
				break;
			}
		}
		delete lpInfo;
	}
	CloseServiceHandle(hSCM);
}

void CMy17������ر�̷��������Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CMy17������ر�̷��������Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CMy17������ر�̷��������Dlg::OnBnClickedRadioWinapp()
{
	if (IsDlgButtonChecked(IDC_RADIO_WINAPP))
	{
		m_display_type = SERVICE_WIN32;
		UpdateList(m_display_type);
	}
}


void CMy17������ر�̷��������Dlg::OnBnClickedRadioDrive()
{
	if (IsDlgButtonChecked(IDC_RADIO_DRIVE))
	{
		m_display_type = SERVICE_DRIVER;
		UpdateList(m_display_type);
	}
}


void CMy17������ر�̷��������Dlg::OnBnClickedRadioAllsvc()
{
	if (IsDlgButtonChecked(IDC_RADIO_ALLSVC))
	{
		m_display_type = SERVICE_DRIVER;
		UpdateList(m_display_type);
	}
}

void CMy17������ر�̷��������Dlg::OnBnClickedButtonStart()
{
	//��ȡѡ��������
	POSITION pos = m_list_service.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_list_service.GetNextSelectedItem(pos);
	}
	if (selIndex == -1)
	{
		return;
	}
	//��ȡѡ����ķ�����
	TCHAR szServiceName[MAXBYTE] = { 0 };
	m_list_service.GetItemText(selIndex, 0, szServiceName, MAXBYTE);
	//�򿪷��������
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		return;
	}
	//��ѡ�еķ���
	SC_HANDLE hservice = OpenService(hSCM, szServiceName, SERVICE_ALL_ACCESS);
	//��������
	BOOL ret = StartService(hservice, 0, NULL);
	if (ret == TRUE)
	{
		m_list_service.SetItemText(selIndex, 2, TEXT("����"));
	}
	else
	{
		MessageBox(TEXT("��������ʧ�ܣ���"), TEXT("������ʾ"));
	}
	//�رշ�����
	CloseServiceHandle(hservice);
	CloseServiceHandle(hSCM);
}


void CMy17������ر�̷��������Dlg::OnBnClickedButtonBan()
{
	POSITION pos = m_list_service.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_list_service.GetNextSelectedItem(pos);
	}
	if (selIndex == -1)
	{
		return;
	}
	TCHAR szServiceName[MAXBYTE] = { 0 };
	m_list_service.GetItemText(selIndex, 0, szServiceName, MAXBYTE);
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		return;
	}
	SC_HANDLE hservice = OpenService(hSCM, szServiceName, SERVICE_ALL_ACCESS);
	SERVICE_STATUS serviceState;
	//ֹͣ����û��StopService��ֻ��ControlService
	BOOL ret = ControlService(hservice, SERVICE_CONTROL_STOP, &serviceState);
	if (ret == TRUE)
	{
		m_list_service.SetItemText(selIndex, 2, TEXT("ֹͣ"));
	}
	else
	{
		MessageBox(TEXT("����ֹͣʧ�ܣ���"), TEXT("������ʾ"));
	}
	CloseServiceHandle(hservice);
	CloseServiceHandle(hSCM);
}
//list��������Ĳ����ͻص�����
int sort_column;
bool sort_direct=false;
int CALLBACK CompareListColumn(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl* list = (CListCtrl*)lParamSort;
	//��ȡ�����е�lParam1��lParam2�еĵ�sort_column���ַ���
	CString lp1 = list->GetItemText((int)lParam1 , sort_column);
	CString lp2 = list->GetItemText((int)lParam2, sort_column);
	// ֱ�ӱȽ��ַ���ASCII
	if (sort_direct)
		return lp1.CompareNoCase(lp2);
	else
		return lp2.CompareNoCase(lp1);
}

void CMy17������ر�̷��������Dlg::OnLvnColumnclickListService(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//ת��������
	sort_direct = !sort_direct;
	//�������
	sort_column = pNMLV->iSubItem;
	// ����i�е�����Ϊi������������ݽ�������ıȽ�lParam1��lParam2����
	int count = m_list_service.GetItemCount();
	for (int i = 0; i<count; i++)
		m_list_service.SetItemData(i, i); 
	//�����б������|������������������������lParamSort������ֱ�ӽ�list��ַ����ȥ���ɣ�
	m_list_service.SortItems(CompareListColumn, (DWORD_PTR)&m_list_service);
	*pResult = 0;
}
