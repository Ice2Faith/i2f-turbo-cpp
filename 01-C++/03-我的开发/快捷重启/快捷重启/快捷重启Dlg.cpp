
// �������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�������.h"
#include "�������Dlg.h"
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


// C�������Dlg �Ի���



C�������Dlg::C�������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�������Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->disk = 'D';
	this->OpeMode=0;
	this->TimeMode=0;
	this->TimeCount = 30;
	WCHAR pCOpeMode[2][20] = {L"�ػ�(D)",L"����(D)"};
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

void C�������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C�������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C�������Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C�������Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWN, &C�������Dlg::OnBnClickedButtonShutdown)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &C�������Dlg::OnBnClickedButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_LOCK, &C�������Dlg::OnBnClickedButtonLock)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &C�������Dlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &C�������Dlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_UP, &C�������Dlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_STARTOPE, &C�������Dlg::OnBnClickedButtonStartope)
	ON_BN_CLICKED(IDC_BUTTON_TIMEMODE, &C�������Dlg::OnBnClickedButtonTimemode)
	ON_BN_CLICKED(IDC_BUTTON_MODE, &C�������Dlg::OnBnClickedButtonMode)
	ON_BN_CLICKED(IDC_BUTTON_CMD, &C�������Dlg::OnBnClickedButtonCmd)
	ON_BN_CLICKED(IDC_BUTTON_POWERSHELL, &C�������Dlg::OnBnClickedButtonPowershell)
	ON_BN_CLICKED(IDC_BUTTON_REGEDIT, &C�������Dlg::OnBnClickedButtonRegedit)
	ON_BN_CLICKED(IDC_BUTTON_IMMUAUTORUN, &C�������Dlg::OnBnClickedButtonImmuautorun)
	ON_BN_CLICKED(IDC_BUTTON_UPDISK, &C�������Dlg::OnBnClickedButtonUpdisk)
	ON_BN_CLICKED(IDC_BUTTON_DOWNDISK, &C�������Dlg::OnBnClickedButtonDowndisk)
END_MESSAGE_MAP()


// C�������Dlg ��Ϣ�������

BOOL C�������Dlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C�������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C�������Dlg::OnPaint()
{
	UpdateDisplay();
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
HCURSOR C�������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C�������Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void C�������Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*if (MessageBox(L"ȷ���˳�������",L"�˳���ʾ",MB_YESNO)==IDYES)*/
	CDialogEx::OnCancel();
}
void C�������Dlg::HideSystem(char * mind)
{
	WinExec((LPCSTR)mind, SW_HIDE);
}
BOOL C�������Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
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
void C�������Dlg::UpdateDisplay()
{
	SetDlgItemText(IDC_BUTTON_TIMEMODE, this->CTimeMode[TimeMode]);
	SetDlgItemText(IDC_BUTTON_MODE, this->COpeMode[OpeMode]);
	CString temp;
	temp.Format(_T("%d"), this->TimeCount);
	SetDlgItemText(IDC_EDIT_TIME, temp);
	temp.Format(_T("���̣�%c"), this->disk);
	SetDlgItemText(IDC_EDIT_DISK, temp);
}
void C�������Dlg::OnBnClickedButtonShutdown()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HideSystem("shutdown /s /f /t 0");
}

void C�������Dlg::OnBnClickedButtonReboot()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HideSystem("shutdown /r /f /t 0");
}


void C�������Dlg::OnBnClickedButtonLock()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HideSystem("rundll32 user32.dll,LockWorkStation");
}


void C�������Dlg::OnBnClickedButtonRemove()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HideSystem("shutdown -a");
}


void C�������Dlg::OnBnClickedButtonDown()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->TimeCount > 0)
	{
		this->TimeCount -= 1;
		UpdateDisplay();
	}
}


void C�������Dlg::OnBnClickedButtonUp()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->TimeCount += 1;
	UpdateDisplay();
}


void C�������Dlg::OnBnClickedButtonStartope()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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


void C�������Dlg::OnBnClickedButtonTimemode()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->TimeMode = (this->TimeMode + 1) % 3;
	UpdateDisplay();
}


void C�������Dlg::OnBnClickedButtonMode()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->OpeMode = (this->OpeMode + 1) % 2;
	UpdateDisplay();
}


void C�������Dlg::OnBnClickedButtonCmd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HideSystem("cmd /k start cmd");
}


void C�������Dlg::OnBnClickedButtonPowershell()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HideSystem("cmd /k start powershell");
}


void C�������Dlg::OnBnClickedButtonRegedit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		_stprintf_s(SafeTips, L"�ƶ����� %c: ��в�����ز����ߣ�\0", disk);
	}
	else
	{
		_stprintf_s(SafeTips, L"�ƶ����� %c: ��ȫ���ѿ������ߣ�\0", disk);
	}
	MessageBox(NULL, SafeTips, L"U�̰�ȫ��ʾ", MB_OK);
}

void C�������Dlg::OnBnClickedButtonImmuautorun()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RemoveAutoRun(this->disk);
}


void C�������Dlg::OnBnClickedButtonUpdisk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->disk < 'Z')
		this->disk++;
	UpdateDisplay();
}


void C�������Dlg::OnBnClickedButtonDowndisk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->disk > 'A')
		this->disk--;
	UpdateDisplay();
}

