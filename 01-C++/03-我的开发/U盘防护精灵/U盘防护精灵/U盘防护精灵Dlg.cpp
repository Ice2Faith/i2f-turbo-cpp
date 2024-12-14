
// U�̷�������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "U�̷�������.h"
#include "U�̷�������Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_TIMER_CHECK_MOUSE_HOVER 0x101

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


// CU�̷�������Dlg �Ի���



CU�̷�������Dlg::CU�̷�������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CU�̷�������Dlg::IDD, pParent)
	, m_SafeOpenPath(_T(""))
	, m_curDiskFlag(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CU�̷�������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_SafeOpenPath);
}

BEGIN_MESSAGE_MAP(CU�̷�������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CU�̷�������Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CU�̷�������Dlg::OnBnClickedCancel)
	ON_MESSAGE(WM_DEVICECHANGE, &OnDeviceChange)
	ON_BN_CLICKED(IDC_BUTTON_SAFE_OPEN, &CU�̷�������Dlg::OnBnClickedButtonSafeOpen)
	ON_BN_CLICKED(IDC_BUTTON_IMMUNE_AUTORUN, &CU�̷�������Dlg::OnBnClickedButtonImmuneAutorun)
	ON_BN_CLICKED(ID_EXIT_PRO, &CU�̷�������Dlg::OnBnClickedExitPro)
	ON_BN_CLICKED(ID_HIDE_TO_BACK, &CU�̷�������Dlg::OnBnClickedHideToBack)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PLUGOUT_UDISK, &CU�̷�������Dlg::OnBnClickedButtonPlugoutUdisk)
	ON_BN_CLICKED(IDC_BUTTON_CHOICE_PLUG_DEVICE, &CU�̷�������Dlg::OnBnClickedButtonChoicePlugDevice)
END_MESSAGE_MAP()


// CU�̷�������Dlg ��Ϣ�������

BOOL CU�̷�������Dlg::OnInitDialog()
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
	ShowWindowInDeskRightDown(false);


	SetTimer(ID_TIMER_CHECK_MOUSE_HOVER, 60, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CU�̷�������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CU�̷�������Dlg::OnPaint()
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
HCURSOR CU�̷�������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CU�̷�������Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CU�̷�������Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}
///////////////////////////////////////////////////////////////////////////////////////////
void StringToUpper(TCHAR * str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] >= 'a'&&str[i] <= 'z')
		{
			str[i] &= ~32;
		}
		i++;
	}
}

bool DelVirusFile(char disk)
{
	char DelAutoRun[2][80] = { "DEL /F /A /Q ", "RMDIR /S /Q " };
	WIN32_FIND_DATA fdata;
	TCHAR diskroot[256] = { 0 };
	_stprintf(diskroot, TEXT("%c:\\\0"), disk);
	TCHAR file[2048] = { 0 };
	lstrcpy(file, diskroot);
	lstrcat(file, TEXT("*.*\0"));
	TCHAR findname[300] = { 0 };
	char delfile[1024] = { 0 };
	char delmind[1024] = { 0 };
	HANDLE fhand = FindFirstFile(file, &fdata);
	if (INVALID_HANDLE_VALUE == fhand) return true;
	TCHAR VirusList[3][100] = { TEXT("AUTORUN.INF"), TEXT("AUTO.EXE"), TEXT("SYSTEM.EXE") };
	int VirusListLen = 3;
	bool DiskSafe = true;
	FILE * usbavb = fopen(".\\usbavconf.bat", "w");
	while (true)
	{
		lstrcpy(findname, fdata.cFileName);
		StringToUpper(findname);
		for (int i = 0; i < VirusListLen; i++)
		{
			if (lstrcmp(findname, VirusList[i]) == 0)
			{
				USES_CONVERSION;
				sprintf(delfile, "%s%s\0", T2A(diskroot), T2A(fdata.cFileName));
				remove(delfile);
				fprintf(usbavb, "%s%s\n", DelAutoRun[0], delfile);
				fprintf(usbavb, "%s%s\n", DelAutoRun[1], delfile);
				DiskSafe = false;
				break;
			}
		}
		if (!FindNextFile(fhand, &fdata))break;
	}
	FindClose(fhand);
	fclose(usbavb);
	return DiskSafe;
}


void ImmuneHardDisk(char disk)
{
	char ImmuneList[3][100] = { "Autorun.inf", "Auto.exe", "System.exe" };
	int ImmuneListLen = 3;
	char mind[4096] = { "cmd /c color f1 " };
	char temp[256] = { 0 };
	for (int i = 0; i < ImmuneListLen; i++)
	{
		sprintf(temp, " && MKDIR %c:\\%s\0", disk, ImmuneList[i]);
		strcat(mind, temp);
		sprintf(temp, " && CHDIR %c:\\%s\0", disk, ImmuneList[i]);
		strcat(mind, temp);
		sprintf(temp, " && MKDIR %c:\\%s\\Immune...\\\\\0", disk, ImmuneList[i]);
		strcat(mind, temp);
		sprintf(temp, " && attrib +r +h %c:\\%s\0", disk, ImmuneList[i]);
		strcat(mind, temp);
	}
	strcat(mind, " && DEL %%0");
	strcat(mind, " && exit");

	WinExec(mind, SW_HIDE);
}
void WriteAntiImmuneBat(char disk)
{
	char ImmuneList[3][100] = { "Autorun.inf", "Auto.exe", "System.exe" };
	int ImmuneListLen = 3;
	char DelBatList[3][100] = { "attrib -r -h ", "DEL /F /A /Q ", "RMDIR /S /Q " };
	FILE * AntiImmuneFile = NULL;
	char  AntiImmuneFileName[256] = { 0 };
	sprintf(AntiImmuneFileName, "%c:\\AntiImmuneFile.bat", disk);
	AntiImmuneFile = fopen(AntiImmuneFileName, "w");
	fprintf(AntiImmuneFile, "@echo off\n");
	fprintf(AntiImmuneFile, "cd/\n");
	for (int i = 0; i < ImmuneListLen; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fprintf(AntiImmuneFile, "%s%s\n", DelBatList[j], ImmuneList[i]);
		}
	}
	fprintf(AntiImmuneFile, "DEL %%0\n");
	fprintf(AntiImmuneFile, "exit\n");
	fclose(AntiImmuneFile);

}

void RemoveAutoRun(char disk)
{
	bool DiskSafe = DelVirusFile(disk);
	ImmuneHardDisk(disk);
	WriteAntiImmuneBat(disk);

	TCHAR SafeTips[256] = { 0 };
	if (DiskSafe == false)
	{
		_stprintf(SafeTips, TEXT("�ƶ����� %c: ��в�����ز����ߣ�\0"), disk);
	}
	else
	{
		_stprintf(SafeTips, TEXT("�ƶ����� %c: ��ȫ���ѿ������ߣ�\0"), disk);
	}
	MessageBox(NULL, SafeTips, TEXT("U�̰�ȫ��ʾ"), MB_OK|MB_ICONINFORMATION);
}
///////////////////////////////////////////////////////////////////////////////////////////
#include<Dbt.h>
//BOOL CU�̷�������Dlg::OnDeviceChange(UINT nEventType, DWORD dwData)
LRESULT CU�̷�������Dlg::OnDeviceChange(WPARAM nEventType, LPARAM dwData)
{
	//�豸������Ϣ
	if (nEventType == DBT_DEVICEARRIVAL)
	{
		//��ȡ�̷�
		char disk = GetDriverDisk(dwData);
		m_curDiskFlag = disk;
		if (disk == 0)
			return FALSE;
		
		//��װ�̷���·��
		CString driver;
		driver.Format(TEXT("%c:"), disk);
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
		}

	}
	if (nEventType == DBT_DEVICEREMOVECOMPLETE)
	{
		//���豸�γ�ʱ���������ش���
		this->ShowWindow(SW_HIDE);
		m_curDiskFlag = 0;
	}
	return TRUE;
}


void CU�̷�������Dlg::OnBnClickedExitPro()
{
	if (IDOK == MessageBox(TEXT("�����˳�U�̷������Ƿ��˳���"), 0, MB_OKCANCEL|MB_ICONWARNING))
		CDialogEx::OnCancel();
}


void CU�̷�������Dlg::OnBnClickedHideToBack()
{
	ShowWindow(SW_HIDE);
}

void CU�̷�������Dlg::OnBnClickedButtonSafeOpen()
{
	//��ȫ��Ŀ¼��ʹ��ShellExecute����
	UpdateData(TRUE);
	ShellExecute(NULL, TEXT("open"), m_SafeOpenPath, NULL, NULL, SW_SHOW);
}


void CU�̷�������Dlg::OnBnClickedButtonImmuneAutorun()
{
	TCHAR tips[256] = { 0 };
	_stprintf(tips, TEXT("�����U��[%c]�������ߣ��Ƿ������"), (m_curDiskFlag == 0 ? ' ' : m_curDiskFlag));
	if (m_curDiskFlag != 0 && IDOK == MessageBox(tips, 0, MB_OKCANCEL | MB_ICONINFORMATION))
		RemoveAutoRun(m_curDiskFlag);
}




char CU�̷�������Dlg::GetDriverDisk(DWORD dwData)
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
					disk = i + 'A';
					break;
				}
				dwUnimask = dwUnimask >> 1;
			}
			return disk;
		}
	}
	return 0;
}

void CU�̷�������Dlg::ShowWindowInDeskRightDown(bool fullDisplay)
{
	UpdateData(FALSE);
	this->ShowWindow(SW_NORMAL);
	int Sx = GetSystemMetrics(SM_CXSCREEN);
	int Sy = GetSystemMetrics(SM_CYSCREEN);
	CRect rect;
	this->GetWindowRect(rect);
	int px = Sx - rect.Width();
	if (fullDisplay == false)
		px = Sx - rect.Width() * 1 / 6;
	::SetWindowPos(this->GetSafeHwnd(),HWND_TOPMOST, px, Sy*0.8 - rect.Height(), 0, 0, SWP_NOSIZE);
}


void CU�̷�������Dlg::DeleteAutoRunOpenFile(CString autorunDirPath)
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
	CString autorunBackVirusDir = autorunDirPath + TEXT("\\_auto_bak_dir_");
	bool hasFilesBackup = false;
	bool hasFindOne = false;
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
		if (hasFindOne == false)
		{
			CreateDirectory(autorunBackVirusDir, NULL);
			hasFindOne = true;
		}
		//������ʾ���ڲ���ʾ
		CString temp;
		temp.Format(TEXT("�Ƿ�ɾ���ļ���%s"), szBuffer);

		CString srcf = autorunDirPath + TEXT("\\") + szBuffer;
		CString drtf = autorunBackVirusDir + TEXT("\\") + szBuffer+TEXT(".arvbak");
		BOOL bret=MoveFile(srcf, drtf);
		if (bret)
			hasFilesBackup = true;
		
		//if (MessageBox(temp, TEXT("U�̷���-�ļ�ɾ��ȷ��"), MB_OKCANCEL|MB_ICONWARNING) == IDOK)
		//{
		//	//��װ�����е��ļ�·����ɾ�����޷�ɾ���������ʾ��
		//	temp = autorunDirPath + TEXT("\\") + szBuffer;
		//	BOOL bret = DeleteFile(temp);
		//	if (bret == FALSE)
		//		MessageBeep(MB_ICONWARNING);
		//}
	}
	if (hasFindOne && hasFilesBackup == false)
	{
		USES_CONVERSION;
		char cmd[256] = { 0 };
		sprintf(cmd, "cmd /c RMDIR /S /Q \"%s\"\0", T2A(autorunBackVirusDir));
		WinExec(cmd, SW_HIDE);
	}
	if (hasFilesBackup)
	{
		CString tips = TEXT("�������ļ��Ѿ����ݵ���[") + autorunBackVirusDir + TEXT("]��\n�Ƿ���Ҫ����ɾ����");
		if (MessageBox(tips, 0, MB_OKCANCEL|MB_ICONWARNING) == IDOK)
		{
			USES_CONVERSION;
			char cmd[256] = { 0 };
			sprintf(cmd, "cmd /c RMDIR /S /Q \"%s\"\0", T2A(autorunBackVirusDir));
			WinExec(cmd, SW_HIDE);
		}
	}
}



void CU�̷�������Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	static bool isFull = false;
	if (nIDEvent == ID_TIMER_CHECK_MOUSE_HOVER)
	{
		POINT pos;
		GetCursorPos(&pos);
		CRect rect;
		this->GetWindowRect(rect);
		ScreenToClient(&pos);
		if (this->IsWindowVisible())
		{
			if (pos.x >= 0 && pos.y >= 0 && pos.x <= rect.Width() && pos.y <= rect.Height())
			{
				if (isFull == false)
				{
					ShowWindowInDeskRightDown();
					isFull = true;
				}

			}
			else
			{
				if (isFull == true)
				{
					ShowWindowInDeskRightDown(false);
					isFull = false;
				}
			}
		}
		
	}
	CDialogEx::OnTimer(nIDEvent);
}

#include"PlugoutUDisk.hpp"
void CU�̷�������Dlg::OnBnClickedButtonPlugoutUdisk()
{
	char disk = '+';
	UpdateData(TRUE);
	if (m_SafeOpenPath.GetLength() == 0){
		MessageBox(TEXT("����д������·�������ԣ�����:H:\\"));
		return;
	}
	disk=m_SafeOpenPath.GetAt(0);
	
	if ((disk >= 'A' && disk <= 'Z') || (disk >= 'a' && disk <= 'z')){
		bool result =  plugoutTargetUDisk(disk);
		if (result){
			MessageBox(TEXT("U���ѵ���."));
		}
		else{
			MessageBox(TEXT("U�̵���ʧ��."));
		}
	}
	else{
		MessageBox(TEXT("�Ƿ����̷�."));
	}
}


void CU�̷�������Dlg::OnBnClickedButtonChoicePlugDevice()
{
	directChoicePlugoutDialog();
}
