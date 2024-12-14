
// 快捷重启Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "快捷重启.h"
#include "快捷重启Dlg.h"
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


// C快捷重启Dlg 对话框



C快捷重启Dlg::C快捷重启Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C快捷重启Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->disk = 'D';
	this->OpeMode=0;
	this->TimeMode=0;
	this->TimeCount = 30;
	WCHAR pCOpeMode[2][20] = {L"关机(D)",L"重启(D)"};
	WCHAR pCTimeMode[3][20] = { L"s(U)", L"m(U)", L"h(U)"};
	for (int i = 0; i < 2; i++)
	{
		StrCpyW(this->COpeMode[i], pCOpeMode[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		StrCpyW(this->CTimeMode[i], pCTimeMode[i]);
	}
}

void C快捷重启Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C快捷重启Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C快捷重启Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C快捷重启Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWN, &C快捷重启Dlg::OnBnClickedButtonShutdown)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &C快捷重启Dlg::OnBnClickedButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_LOCK, &C快捷重启Dlg::OnBnClickedButtonLock)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &C快捷重启Dlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &C快捷重启Dlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_UP, &C快捷重启Dlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_STARTOPE, &C快捷重启Dlg::OnBnClickedButtonStartope)
	ON_BN_CLICKED(IDC_BUTTON_TIMEMODE, &C快捷重启Dlg::OnBnClickedButtonTimemode)
	ON_BN_CLICKED(IDC_BUTTON_MODE, &C快捷重启Dlg::OnBnClickedButtonMode)
	ON_BN_CLICKED(IDC_BUTTON_CMD, &C快捷重启Dlg::OnBnClickedButtonCmd)
	ON_BN_CLICKED(IDC_BUTTON_POWERSHELL, &C快捷重启Dlg::OnBnClickedButtonPowershell)
	ON_BN_CLICKED(IDC_BUTTON_REGEDIT, &C快捷重启Dlg::OnBnClickedButtonRegedit)
	ON_BN_CLICKED(IDC_BUTTON_IMMUAUTORUN, &C快捷重启Dlg::OnBnClickedButtonImmuautorun)
	ON_BN_CLICKED(IDC_BUTTON_UPDISK, &C快捷重启Dlg::OnBnClickedButtonUpdisk)
	ON_BN_CLICKED(IDC_BUTTON_DOWNDISK, &C快捷重启Dlg::OnBnClickedButtonDowndisk)
END_MESSAGE_MAP()


// C快捷重启Dlg 消息处理程序

BOOL C快捷重启Dlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C快捷重启Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C快捷重启Dlg::OnPaint()
{
	UpdateDisplay();
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
HCURSOR C快捷重启Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C快捷重启Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void C快捷重启Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	/*if (MessageBox(L"确定退出程序吗？",L"退出提示",MB_YESNO)==IDYES)*/
	CDialogEx::OnCancel();
}
void C快捷重启Dlg::HideSystem(char * mind)
{
	WinExec((LPCSTR)mind, SW_HIDE);
}
BOOL C快捷重启Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case '1':
		case VK_NUMPAD1:
			OnBnClickedButtonShutdown();
			break;
		case '2':
		case VK_NUMPAD2:
			OnBnClickedButtonReboot();
			break;
		case '3':
		case VK_NUMPAD3:
			OnBnClickedButtonLock();
		case '0':
		case VK_NUMPAD0:
			OnBnClickedButtonRemove();
			return true;
			break;
		case '4':
		case VK_SPACE:
		case VK_NUMPAD4:
			OnBnClickedButtonStartope();
			break;
		case VK_LEFT:
			OnBnClickedButtonDown();
			break;
		case VK_RIGHT:
			OnBnClickedButtonUp();
			break;
		case VK_UP:
			OnBnClickedButtonTimemode();
			break;
		case VK_DOWN:
			OnBnClickedButtonMode();
			break;
		case '7':
		case VK_NUMPAD7:
			OnBnClickedButtonCmd();
			break;
		case '8':
		case VK_NUMPAD8:
			OnBnClickedButtonPowershell();
			break;
		case '9':
		case VK_NUMPAD9:
			OnBnClickedButtonRegedit();
			break;
		default:
			return false;
			break;
		}
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
void C快捷重启Dlg::UpdateDisplay()
{
	SetDlgItemText(IDC_BUTTON_TIMEMODE, this->CTimeMode[TimeMode]);
	SetDlgItemText(IDC_BUTTON_MODE, this->COpeMode[OpeMode]);
	CString temp;
	temp.Format(_T("%d"), this->TimeCount);
	SetDlgItemText(IDC_EDIT_TIME, temp);
	temp.Format(_T("磁盘：%c"), this->disk);
	SetDlgItemText(IDC_EDIT_DISK, temp);
}
void C快捷重启Dlg::OnBnClickedButtonShutdown()
{
	// TODO:  在此添加控件通知处理程序代码
	HideSystem("shutdown /s /f /t 0");
}

void C快捷重启Dlg::OnBnClickedButtonReboot()
{
	// TODO:  在此添加控件通知处理程序代码
	HideSystem("shutdown /r /f /t 0");
}


void C快捷重启Dlg::OnBnClickedButtonLock()
{
	// TODO:  在此添加控件通知处理程序代码
	HideSystem("rundll32 user32.dll,LockWorkStation");
}


void C快捷重启Dlg::OnBnClickedButtonRemove()
{
	// TODO:  在此添加控件通知处理程序代码
	HideSystem("shutdown -a");
}


void C快捷重启Dlg::OnBnClickedButtonDown()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->TimeCount > 0)
	{
		this->TimeCount -= 1;
		UpdateDisplay();
	}
}


void C快捷重启Dlg::OnBnClickedButtonUp()
{
	// TODO:  在此添加控件通知处理程序代码
	this->TimeCount += 1;
	UpdateDisplay();
}


void C快捷重启Dlg::OnBnClickedButtonStartope()
{
	// TODO:  在此添加控件通知处理程序代码
	int truetime = 0;
	switch (this->TimeMode)
	{
	case 0:
		truetime = this->TimeCount;
		break;
	case 1:
		truetime = this->TimeCount*60;
		break;
	case 2:
		truetime = this->TimeCount*60*60;
		break;
	}
	char mind[200] = { 0 };
	if (this->OpeMode == 0)
	{
		sprintf(mind, "shutdown -s -f -t %d\0", truetime);
	}
	else if (this->OpeMode==1)
	{
		sprintf(mind, "shutdown -r -f -t %d\0", truetime);
	}
	HideSystem(mind);
}


void C快捷重启Dlg::OnBnClickedButtonTimemode()
{
	// TODO:  在此添加控件通知处理程序代码
	this->TimeMode = (this->TimeMode + 1) % 3;
	UpdateDisplay();
}


void C快捷重启Dlg::OnBnClickedButtonMode()
{
	// TODO:  在此添加控件通知处理程序代码
	this->OpeMode = (this->OpeMode + 1) % 2;
	UpdateDisplay();
}


void C快捷重启Dlg::OnBnClickedButtonCmd()
{
	// TODO:  在此添加控件通知处理程序代码
	HideSystem("cmd /k start cmd");
}


void C快捷重启Dlg::OnBnClickedButtonPowershell()
{
	// TODO:  在此添加控件通知处理程序代码
	HideSystem("cmd /k start powershell");
}


void C快捷重启Dlg::OnBnClickedButtonRegedit()
{
	// TODO:  在此添加控件通知处理程序代码
	HideSystem("cmd /k start regedit");
}
void Wchar_t2Char(wchar_t Wchar[], char Char[])
{
	int size = WideCharToMultiByte(CP_ACP, 0, Wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Wchar, -1, Char, size, NULL, NULL);
}
void Char2Wchar_t(char Char[], wchar_t Wchar[])
{
	int size = MultiByteToWideChar(CP_ACP, 0, Char, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, Char, -1, Wchar, size);
}

void StringToUpper(char * str)
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
	WIN32_FIND_DATAA fdata;
	char diskroot[256] = { 0 };
	sprintf(diskroot, "%c:\\\0", disk);
	char file[2048] = { 0 };
	strcpy(file, diskroot);
	strcat(file, "*.*\0");
	char findname[300] = { 0 };
	char delfile[1024] = { 0 };
	char delmind[1024] = { 0 };
	HANDLE fhand = FindFirstFileA(file, &fdata);
	if (INVALID_HANDLE_VALUE == fhand) return true;
	char VirusList[3][100] = { "AUTORUN.INF", "AUTO.EXE", "SYSTEM.DLL" };
	int VirusListLen = 3;
	bool DiskSafe = true;
	char mind[4096] = { "cmd /c color f1 " };
	char temp[256] = { 0 };
	while (true)
	{
		strcpy(findname, fdata.cFileName);
		StringToUpper(findname);
		for (int i = 0; i < VirusListLen; i++)
		{
			if (strcmp(findname, VirusList[i]) == 0)
			{
				sprintf(delfile, "%s%s\0", diskroot, fdata.cFileName);
				remove(delfile);
				sprintf(temp, " && %s%s\0", DelAutoRun[0], delfile);
				strcat(mind, temp);
				sprintf(temp, " && %s%s\0", DelAutoRun[1], delfile);
				strcat(mind, temp);
				DiskSafe = false;
				break;
			}
		}
		if (!FindNextFileA(fhand, &fdata))break;
	}
	FindClose(fhand);
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

	WinExec((LPCSTR)mind, SW_HIDE);
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
		_stprintf_s(SafeTips, L"移动磁盘 %c: 威胁已拦截并免疫！\0", disk);
	}
	else
	{
		_stprintf_s(SafeTips, L"移动磁盘 %c: 安全，已开启免疫！\0", disk);
	}
	MessageBox(NULL, SafeTips, L"U盘安全提示", MB_OK);
}

void C快捷重启Dlg::OnBnClickedButtonImmuautorun()
{
	// TODO:  在此添加控件通知处理程序代码
	RemoveAutoRun(this->disk);
}


void C快捷重启Dlg::OnBnClickedButtonUpdisk()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->disk < 'Z')
		this->disk++;
	UpdateDisplay();
}


void C快捷重启Dlg::OnBnClickedButtonDowndisk()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->disk > 'A')
		this->disk--;
	UpdateDisplay();
}

