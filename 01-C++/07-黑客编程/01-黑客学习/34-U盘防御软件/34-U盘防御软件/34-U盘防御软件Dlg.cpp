
// 34-U�̷������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "34-U�̷������.h"
#include "34-U�̷������Dlg.h"
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


// CMy34U�̷������Dlg �Ի���



CMy34U�̷������Dlg::CMy34U�̷������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy34U�̷������Dlg::IDD, pParent)
	, m_SafeOpenPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy34U�̷������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SafeOpenPath);
}

BEGIN_MESSAGE_MAP(CMy34U�̷������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy34U�̷������Dlg::OnBnClickedOk)
	ON_MESSAGE(WM_DEVICECHANGE,&OnDeviceChange)
	ON_BN_CLICKED(IDC_BUTTON_SAFE_OPEN, &CMy34U�̷������Dlg::OnBnClickedButtonSafeOpen)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TRULY_CLOSE, &CMy34U�̷������Dlg::OnBnClickedButtonTrulyClose)
	ON_BN_CLICKED(IDC_BUTTON_HIDEWND, &CMy34U�̷������Dlg::OnBnClickedButtonHidewnd)
END_MESSAGE_MAP()


// CMy34U�̷������Dlg ��Ϣ�������

BOOL CMy34U�̷������Dlg::OnInitDialog()
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
	SetTimer(TIMER_FRIST_LOAD, 300, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy34U�̷������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy34U�̷������Dlg::OnPaint()
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
HCURSOR CMy34U�̷������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy34U�̷������Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
/*

*/
#include<Dbt.h>
//BOOL CMy34U�̷������Dlg::OnDeviceChange(UINT nEventType, DWORD dwData)
LRESULT CMy34U�̷������Dlg::OnDeviceChange(WPARAM nEventType, LPARAM dwData)
{
	//�豸������Ϣ
	if (nEventType == DBT_DEVICEARRIVAL)
	{
		//��ȡ�̷�
		char disk = GetDriverDisk(dwData);
		if (disk == 0)
			return FALSE;
		//��װ�̷���·��
		CString driver;
		driver.Format(TEXT("%c:"),disk);
		if (driver != "")
		{
			//��ʾΪ����ǰ�ô��ڣ��ṩ�û�����
			m_SafeOpenPath = driver + TEXT("\\");
			ShowWindowInDeskRightDown();
			//��װautorun.inf�ļ�·��
			CString autoRunFile;
			autoRunFile = driver + TEXT("\\autorun.inf");
			//�ж��ļ��Ƿ���ڣ����û�ȡ����
			if (GetFileAttributes(autoRunFile.GetBuffer(0)) == -1)
				return FALSE;
			//��ȡautorun�ļ���open���ú�������ݣ�������ǻ��Զ����е�Ŀ���ļ���
			DeleteAutoRunOpenFile(driver);
			
			if (nEventType == DBT_DEVICEREMOVECOMPLETE)
			{
				//���豸�γ�ʱ���������ش���
				this->ShowWindow(SW_HIDE);
			}
		}

	}
	return TRUE;
}


char CMy34U�̷������Dlg::GetDriverDisk(DWORD dwData)
{
	//�õ����������ݽṹ
	PDEV_BROADCAST_HDR pDevHdr = (PDEV_BROADCAST_HDR)dwData;
	//����ָʾ���ͣ�ת���ṹ��
	if (pDevHdr->dbch_devicetype == DBT_DEVTYP_VOLUME)
	{
		PDEV_BROADCAST_VOLUME pDevVol = (PDEV_BROADCAST_VOLUME)pDevHdr;
		//���峣�������ֵ�������ƶ����̻���U��
		const int MOVEABLE_DISK = 0;
		if (pDevVol->dbcv_flags == MOVEABLE_DISK)
		{
			//��ȡ�̷����룬�������̷��ַ�
			//���룺***0100 ***DCBA����ͱ�ʶ��C��
			char disk = 0;
			DWORD dwUnimask = pDevVol->dbcv_unitmask;
			for (int i = 0; i < 26; i++)
			{
				if (dwUnimask & 0x1)
				{
					disk = i+'A';
					break;
				}
				dwUnimask = dwUnimask >> 1;
			}
			return disk;
		}
	}
	return 0;
}


void CMy34U�̷������Dlg::OnBnClickedButtonSafeOpen()
{
	//��ȫ��Ŀ¼��ʹ��ShellExecute����
	UpdateData(TRUE);
	ShellExecute(NULL, TEXT("open"), m_SafeOpenPath, NULL, NULL, SW_SHOW);
}


void CMy34U�̷������Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == TIMER_FRIST_LOAD)
	{
		this->ShowWindow(SW_HIDE);
		KillTimer(TIMER_FRIST_LOAD);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMy34U�̷������Dlg::ShowWindowInDeskRightDown()
{
	UpdateData(FALSE);
	this->ShowWindow(SW_NORMAL);
	int Sx = GetSystemMetrics(SM_CXSCREEN);
	int Sy = GetSystemMetrics(SM_CYSCREEN);
	CRect rect;
	this->GetWindowRect(rect);
	this->SetWindowPos(NULL, Sx - rect.Width(), Sy*0.8 - rect.Height(), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	this->SetActiveWindow();
	this->SetForegroundWindow();
}


void CMy34U�̷������Dlg::OnBnClickedButtonTrulyClose()
{
	CDialogEx::OnOK();
}


void CMy34U�̷������Dlg::OnBnClickedButtonHidewnd()
{
	this->ShowWindow(SW_HIDE);
}


void CMy34U�̷������Dlg::DeleteAutoRunOpenFile(CString autorunDirPath)
{
	static TCHAR nodeList[4][40] = {
		TEXT("AutoRun"),
		TEXT("AutoRun"),
		TEXT("AutoRun.alpha"),
		TEXT("AutoRun.alpha"),
	};
	static TCHAR keyList[4][40] = {
		TEXT("open"),
		TEXT("shellexecute"),
		TEXT("open"),
		TEXT("shellexecute"),
	};
	CString autorunFileName = autorunDirPath + TEXT("\\autorun.inf");
	for (int i = 0; i < 4; i++)
	{
		TCHAR szBuffer[MAX_PATH] = { 0 };
		GetPrivateProfileString(
			nodeList[i],
			keyList[i],
			NULL,
			szBuffer,
			MAX_PATH,
			autorunFileName);
		if (lstrlen(szBuffer) == 0)
			continue;
			//������ʾ���ڲ���ʾ
			CString temp;
		temp.Format(TEXT("�Ƿ�ɾ���ļ���%s"), szBuffer);
		if (MessageBox(temp, TEXT("U�̷���-�ļ�ɾ��ȷ��"), MB_OKCANCEL) == IDOK)
		{
			//��װ�����е��ļ�·����ɾ�����޷�ɾ���������ʾ��
			temp = autorunDirPath + TEXT("\\") + szBuffer;
			BOOL bret = DeleteFile(temp);
			if (bret == FALSE)
				MessageBeep(MB_ICONWARNING);
		}
	}
	
}
