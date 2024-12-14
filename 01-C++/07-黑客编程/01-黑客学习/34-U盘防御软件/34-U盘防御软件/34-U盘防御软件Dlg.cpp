
// 34-U盘防御软件Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "34-U盘防御软件.h"
#include "34-U盘防御软件Dlg.h"
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


// CMy34U盘防御软件Dlg 对话框



CMy34U盘防御软件Dlg::CMy34U盘防御软件Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy34U盘防御软件Dlg::IDD, pParent)
	, m_SafeOpenPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy34U盘防御软件Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SafeOpenPath);
}

BEGIN_MESSAGE_MAP(CMy34U盘防御软件Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy34U盘防御软件Dlg::OnBnClickedOk)
	ON_MESSAGE(WM_DEVICECHANGE,&OnDeviceChange)
	ON_BN_CLICKED(IDC_BUTTON_SAFE_OPEN, &CMy34U盘防御软件Dlg::OnBnClickedButtonSafeOpen)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TRULY_CLOSE, &CMy34U盘防御软件Dlg::OnBnClickedButtonTrulyClose)
	ON_BN_CLICKED(IDC_BUTTON_HIDEWND, &CMy34U盘防御软件Dlg::OnBnClickedButtonHidewnd)
END_MESSAGE_MAP()


// CMy34U盘防御软件Dlg 消息处理程序

BOOL CMy34U盘防御软件Dlg::OnInitDialog()
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
	SetTimer(TIMER_FRIST_LOAD, 300, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy34U盘防御软件Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy34U盘防御软件Dlg::OnPaint()
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
HCURSOR CMy34U盘防御软件Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy34U盘防御软件Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
/*

*/
#include<Dbt.h>
//BOOL CMy34U盘防御软件Dlg::OnDeviceChange(UINT nEventType, DWORD dwData)
LRESULT CMy34U盘防御软件Dlg::OnDeviceChange(WPARAM nEventType, LPARAM dwData)
{
	//设备插入信息
	if (nEventType == DBT_DEVICEARRIVAL)
	{
		//获取盘符
		char disk = GetDriverDisk(dwData);
		if (disk == 0)
			return FALSE;
		//组装盘符根路径
		CString driver;
		driver.Format(TEXT("%c:"),disk);
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
			
			if (nEventType == DBT_DEVICEREMOVECOMPLETE)
			{
				//当设备拔出时，重新隐藏窗口
				this->ShowWindow(SW_HIDE);
			}
		}

	}
	return TRUE;
}


char CMy34U盘防御软件Dlg::GetDriverDisk(DWORD dwData)
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


void CMy34U盘防御软件Dlg::OnBnClickedButtonSafeOpen()
{
	//安全打开目录，使用ShellExecute进行
	UpdateData(TRUE);
	ShellExecute(NULL, TEXT("open"), m_SafeOpenPath, NULL, NULL, SW_SHOW);
}


void CMy34U盘防御软件Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == TIMER_FRIST_LOAD)
	{
		this->ShowWindow(SW_HIDE);
		KillTimer(TIMER_FRIST_LOAD);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMy34U盘防御软件Dlg::ShowWindowInDeskRightDown()
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


void CMy34U盘防御软件Dlg::OnBnClickedButtonTrulyClose()
{
	CDialogEx::OnOK();
}


void CMy34U盘防御软件Dlg::OnBnClickedButtonHidewnd()
{
	this->ShowWindow(SW_HIDE);
}


void CMy34U盘防御软件Dlg::DeleteAutoRunOpenFile(CString autorunDirPath)
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
			//构造提示窗口并显示
			CString temp;
		temp.Format(TEXT("是否删除文件：%s"), szBuffer);
		if (MessageBox(temp, TEXT("U盘防御-文件删除确认"), MB_OKCANCEL) == IDOK)
		{
			//组装被运行的文件路径并删除，无法删除则给出提示音
			temp = autorunDirPath + TEXT("\\") + szBuffer;
			BOOL bret = DeleteFile(temp);
			if (bret == FALSE)
				MessageBeep(MB_ICONWARNING);
		}
	}
	
}
