
// U盘防护精灵Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "U盘防护精灵.h"
#include "U盘防护精灵Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_TIMER_CHECK_MOUSE_HOVER 0x101

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


// CU盘防护精灵Dlg 对话框



CU盘防护精灵Dlg::CU盘防护精灵Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CU盘防护精灵Dlg::IDD, pParent)
	, m_SafeOpenPath(_T(""))
	, m_curDiskFlag(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CU盘防护精灵Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_SafeOpenPath);
}

BEGIN_MESSAGE_MAP(CU盘防护精灵Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CU盘防护精灵Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CU盘防护精灵Dlg::OnBnClickedCancel)
	ON_MESSAGE(WM_DEVICECHANGE, &OnDeviceChange)
	ON_BN_CLICKED(IDC_BUTTON_SAFE_OPEN, &CU盘防护精灵Dlg::OnBnClickedButtonSafeOpen)
	ON_BN_CLICKED(IDC_BUTTON_IMMUNE_AUTORUN, &CU盘防护精灵Dlg::OnBnClickedButtonImmuneAutorun)
	ON_BN_CLICKED(ID_EXIT_PRO, &CU盘防护精灵Dlg::OnBnClickedExitPro)
	ON_BN_CLICKED(ID_HIDE_TO_BACK, &CU盘防护精灵Dlg::OnBnClickedHideToBack)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PLUGOUT_UDISK, &CU盘防护精灵Dlg::OnBnClickedButtonPlugoutUdisk)
	ON_BN_CLICKED(IDC_BUTTON_CHOICE_PLUG_DEVICE, &CU盘防护精灵Dlg::OnBnClickedButtonChoicePlugDevice)
END_MESSAGE_MAP()


// CU盘防护精灵Dlg 消息处理程序

BOOL CU盘防护精灵Dlg::OnInitDialog()
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
	ShowWindowInDeskRightDown(false);


	SetTimer(ID_TIMER_CHECK_MOUSE_HOVER, 60, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CU盘防护精灵Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CU盘防护精灵Dlg::OnPaint()
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
HCURSOR CU盘防护精灵Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CU盘防护精灵Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CU盘防护精灵Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
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
		_stprintf(SafeTips, TEXT("移动磁盘 %c: 威胁已拦截并免疫！\0"), disk);
	}
	else
	{
		_stprintf(SafeTips, TEXT("移动磁盘 %c: 安全，已开启免疫！\0"), disk);
	}
	MessageBox(NULL, SafeTips, TEXT("U盘安全提示"), MB_OK|MB_ICONINFORMATION);
}
///////////////////////////////////////////////////////////////////////////////////////////
#include<Dbt.h>
//BOOL CU盘防护精灵Dlg::OnDeviceChange(UINT nEventType, DWORD dwData)
LRESULT CU盘防护精灵Dlg::OnDeviceChange(WPARAM nEventType, LPARAM dwData)
{
	//设备插入信息
	if (nEventType == DBT_DEVICEARRIVAL)
	{
		//获取盘符
		char disk = GetDriverDisk(dwData);
		m_curDiskFlag = disk;
		if (disk == 0)
			return FALSE;
		
		//组装盘符根路径
		CString driver;
		driver.Format(TEXT("%c:"), disk);
		if (driver != "")
		{
			//显示为激活前置窗口，提供用户操作
			m_SafeOpenPath = driver + TEXT("\\");
			ShowWindowInDeskRightDown();
			//组装autorun.inf文件路径
			CString autoRunFile;
			autoRunFile = driver + TEXT("\\autorun.inf");
			//判断文件是否存在，利用获取属性
			if (GetFileAttributes(autoRunFile.GetBuffer(0)) == -1)
				return FALSE;
			//获取autorun文件中open配置后面的内容，这个就是会自动运行的目标文件名
			DeleteAutoRunOpenFile(driver);
		}

	}
	if (nEventType == DBT_DEVICEREMOVECOMPLETE)
	{
		//当设备拔出时，重新隐藏窗口
		this->ShowWindow(SW_HIDE);
		m_curDiskFlag = 0;
	}
	return TRUE;
}


void CU盘防护精灵Dlg::OnBnClickedExitPro()
{
	if (IDOK == MessageBox(TEXT("即将退出U盘防护，是否退出？"), 0, MB_OKCANCEL|MB_ICONWARNING))
		CDialogEx::OnCancel();
}


void CU盘防护精灵Dlg::OnBnClickedHideToBack()
{
	ShowWindow(SW_HIDE);
}

void CU盘防护精灵Dlg::OnBnClickedButtonSafeOpen()
{
	//安全打开目录，使用ShellExecute进行
	UpdateData(TRUE);
	ShellExecute(NULL, TEXT("open"), m_SafeOpenPath, NULL, NULL, SW_SHOW);
}


void CU盘防护精灵Dlg::OnBnClickedButtonImmuneAutorun()
{
	TCHAR tips[256] = { 0 };
	_stprintf(tips, TEXT("将会对U盘[%c]进行免疫，是否继续？"), (m_curDiskFlag == 0 ? ' ' : m_curDiskFlag));
	if (m_curDiskFlag != 0 && IDOK == MessageBox(tips, 0, MB_OKCANCEL | MB_ICONINFORMATION))
		RemoveAutoRun(m_curDiskFlag);
}




char CU盘防护精灵Dlg::GetDriverDisk(DWORD dwData)
{
	//得到真正的数据结构
	PDEV_BROADCAST_HDR pDevHdr = (PDEV_BROADCAST_HDR)dwData;
	//根据指示类型，转换结构体
	if (pDevHdr->dbch_devicetype == DBT_DEVTYP_VOLUME)
	{
		PDEV_BROADCAST_VOLUME pDevVol = (PDEV_BROADCAST_VOLUME)pDevHdr;
		//定义常量，这个值代表是移动磁盘或者U盘
		const int MOVEABLE_DISK = 0;
		if (pDevVol->dbcv_flags == MOVEABLE_DISK)
		{
			//获取盘符掩码，并返回盘符字符
			//掩码：***0100 ***DCBA，这就标识是C盘
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

void CU盘防护精灵Dlg::ShowWindowInDeskRightDown(bool fullDisplay)
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


void CU盘防护精灵Dlg::DeleteAutoRunOpenFile(CString autorunDirPath)
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
		//构造提示窗口并显示
		CString temp;
		temp.Format(TEXT("是否删除文件：%s"), szBuffer);

		CString srcf = autorunDirPath + TEXT("\\") + szBuffer;
		CString drtf = autorunBackVirusDir + TEXT("\\") + szBuffer+TEXT(".arvbak");
		BOOL bret=MoveFile(srcf, drtf);
		if (bret)
			hasFilesBackup = true;
		
		//if (MessageBox(temp, TEXT("U盘防御-文件删除确认"), MB_OKCANCEL|MB_ICONWARNING) == IDOK)
		//{
		//	//组装被运行的文件路径并删除，无法删除则给出提示音
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
		CString tips = TEXT("被启动文件已经备份到：[") + autorunBackVirusDir + TEXT("]，\n是否需要进行删除？");
		if (MessageBox(tips, 0, MB_OKCANCEL|MB_ICONWARNING) == IDOK)
		{
			USES_CONVERSION;
			char cmd[256] = { 0 };
			sprintf(cmd, "cmd /c RMDIR /S /Q \"%s\"\0", T2A(autorunBackVirusDir));
			WinExec(cmd, SW_HIDE);
		}
	}
}



void CU盘防护精灵Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
void CU盘防护精灵Dlg::OnBnClickedButtonPlugoutUdisk()
{
	char disk = '+';
	UpdateData(TRUE);
	if (m_SafeOpenPath.GetLength() == 0){
		MessageBox(TEXT("请填写驱动器路径后重试，例如:H:\\"));
		return;
	}
	disk=m_SafeOpenPath.GetAt(0);
	
	if ((disk >= 'A' && disk <= 'Z') || (disk >= 'a' && disk <= 'z')){
		bool result =  plugoutTargetUDisk(disk);
		if (result){
			MessageBox(TEXT("U盘已弹出."));
		}
		else{
			MessageBox(TEXT("U盘弹出失败."));
		}
	}
	else{
		MessageBox(TEXT("非法的盘符."));
	}
}


void CU盘防护精灵Dlg::OnBnClickedButtonChoicePlugDevice()
{
	directChoicePlugoutDialog();
}
