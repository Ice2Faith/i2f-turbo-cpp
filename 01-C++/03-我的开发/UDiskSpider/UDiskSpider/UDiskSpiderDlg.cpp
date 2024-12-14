
// UDiskSpiderDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "UDiskSpider.h"
#include "UDiskSpiderDlg.h"
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


// CUDiskSpiderDlg 对话框



CUDiskSpiderDlg::CUDiskSpiderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDiskSpiderDlg::IDD, pParent)
	, m_CSUserType(_T(""))
	, m_jumpSize(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDiskSpiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILETYPE, m_CBtype);
	DDX_Control(pDX, IDC_LIST_LISTTYPE, m_LBtype);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_SAVEPATH, m_EBCviewdir);
	DDX_Control(pDX, IDC_EDIT_USERTYPE, m_ECUserType);
	DDX_Text(pDX, IDC_EDIT_USERTYPE, m_CSUserType);
	DDX_Control(pDX, IDC_CHECK_BANPOWER, m_CKBanPower);
	DDX_Control(pDX, IDC_LIST_RUNLOG, m_LBRunLog);
	DDX_Control(pDX, IDC_CHECK_ALLFILES, m_CKAllFiles);
	DDX_Control(pDX, IDC_BUTTON_INSERTTYPE, m_BTAdd);
	DDX_Control(pDX, IDC_BUTTON_REMOVETYPE, m_BTRemove);
	DDX_Control(pDX, IDC_COMBO_JUMP_SIZE, m_CBjumpSize);
}

BEGIN_MESSAGE_MAP(CUDiskSpiderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(IDOK, &CUDiskSpiderDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_INSERTTYPE, &CUDiskSpiderDlg::OnBnClickedButtonInserttype)
	ON_CBN_SELCHANGE(IDC_COMBO_FILETYPE, &CUDiskSpiderDlg::OnCbnSelchangeComboFiletype)
	ON_BN_CLICKED(IDC_BUTTON_REMOVETYPE, &CUDiskSpiderDlg::OnBnClickedButtonRemovetype)
	ON_BN_CLICKED(IDC_BUTTON_CLEARTYPE, &CUDiskSpiderDlg::OnBnClickedButtonCleartype)
	ON_BN_CLICKED(IDC_CHECK_ALLFILES, &CUDiskSpiderDlg::OnBnClickedCheckAllfiles)
	ON_BN_CLICKED(IDC_BUTTON_HIDE_WND, &CUDiskSpiderDlg::OnBnClickedButtonHideWnd)
	ON_CBN_SELCHANGE(IDC_COMBO_JUMP_SIZE, &CUDiskSpiderDlg::OnCbnSelchangeComboJumpSize)
END_MESSAGE_MAP()


// CUDiskSpiderDlg 消息处理程序

BOOL CUDiskSpiderDlg::OnInitDialog()
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
	if (PathFileExists(L"D:\\") == FALSE){
		this->m_EBCviewdir.SetWindowTextW(L"C:\\UDiskSpider");
	}
	else
	{
		this->m_EBCviewdir.SetWindowTextW(L"D:\\UDiskSpider");
	}
	this->m_CBtype.AddString(L"图片文件.jpg/.png/.gif/.jpeg/.bmp/.tif/.raw");
	this->m_CBtype.AddString(L"音频文件.mp3/.aac/.ogg/.wav/.flac/.amr");
	this->m_CBtype.AddString(L"视频文件.mp4/.avi/.mkv/.rmvb/.flv/.mov/.wmv");
	this->m_CBtype.AddString(L"文档文件.txt/.doc/.docx/.pdf");
	this->m_CBtype.AddString(L"表格文件.xls/.xlsx");
	this->m_CBtype.AddString(L"演示文件.ppt/.pptx");
	this->m_CBtype.AddString(L"Windows程序.exe/.bat/.vbs/.msi");
	this->m_CBtype.AddString(L"安卓Linux程序.apk/.sh/.jar");
	this->m_CBtype.AddString(L"压缩文件.zip/.rar/.7z/.tar/.gz");
	this->m_CBtype.AddString(L"镜像文件.img/.iso/.wim/.gho");
	this->m_CBtype.AddString(L"编程文件.c/.cpp/.hpp/.h/.java/.py/.cs/.go/.asm/.sql");
	this->m_CBtype.AddString(L"Web网页.html/.css/.js/.chm/.xml/.json");
	this->m_CKBanPower.SetCheck(0);
	this->m_CBtype.SetCurSel(0);
	this->m_LBRunLog.SetHorizontalExtent(1024);
	this->m_CKAllFiles.SetCheck(0);

	this->m_CBjumpSize.AddString(L"无限制");
	this->m_CBjumpSize.AddString(L"1M");
	this->m_CBjumpSize.AddString(L"3M");
	this->m_CBjumpSize.AddString(L"8M");
	this->m_CBjumpSize.AddString(L"15M");
	this->m_CBjumpSize.AddString(L"30M");
	this->m_CBjumpSize.AddString(L"50M");
	this->m_CBjumpSize.AddString(L"100M");
	this->m_CBjumpSize.AddString(L"300M");
	this->m_CBjumpSize.AddString(L"500M");
	this->m_CBjumpSize.AddString(L"1G");
	this->m_CBjumpSize.AddString(L"2G");
	this->m_CBjumpSize.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUDiskSpiderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUDiskSpiderDlg::OnPaint()
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
HCURSOR CUDiskSpiderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUDiskSpiderDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

TCHAR CUDiskSpiderDlg::GetDiskCharFuMask(DWORD uMask)
{
	TCHAR disk = 'A';
	for (; disk < 'A' + 26; disk++)
	{
		if (uMask & 1)
			break;
		uMask = uMask >> 1;
	}
	return disk;
}
bool CUDiskSpiderDlg::ProcessFile(TCHAR * file)
{
	CString fullname = PathFindFileName(file);
	if (m_CKAllFiles.GetCheck() == 1)
	{
		CString savePath;
		this->m_EBCviewdir.GetWindowText(savePath);
		CString conPath(&file[2], lstrlen(file) - fullname.GetLength() - 2);
		savePath.Append(conPath);
		if (!PathFileExists(savePath))
		{
			MakeDirs(savePath);
			//MessageBox(savePath, tail, MB_OK);
		}
		CopyFile(file, savePath + fullname, TRUE);

		return true;
	}

	CString tail = PathFindExtension(file);
	tail.MakeUpper();
	
	for (int i = 0; i < this->m_LBtype.GetCount(); i++)
	{
		CString stail;
		this->m_LBtype.GetText(i,stail);
		stail.MakeUpper();
		bool needCopy = false;
		
		if (stail[0]=='.' &&  tail == stail)
			needCopy = true;
		else
		{
			if (fullname.Find(stail, 0) != -1)
				needCopy = true;
		}
		if (needCopy)
		{
			CString savePath;
			this->m_EBCviewdir.GetWindowText(savePath);
			CString conPath(&file[2], lstrlen(file) - fullname.GetLength() - 2);
			savePath.Append(conPath);
			if (!PathFileExists(savePath))
			{
				MakeDirs(savePath);
				//MessageBox(savePath, tail, MB_OK);
			}
			CopyFile(file, savePath + fullname, TRUE);
		}
	}
	
	return true;
}
void CUDiskSpiderDlg::ProcessDir(TCHAR * dir)
{
	TCHAR szParentPath[MAX_PATH * MAX_LEVEL];
	lstrcpy(szParentPath, dir);
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	TCHAR szFilePath[MAX_PATH * MAX_LEVEL];
	lstrcpy(szFilePath, dir);
	lstrcat(szFilePath, L"\\*");
	hListFile = FindFirstFile(szFilePath, &FindFileData);
	if (hListFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		if (!lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 &&
			!lstrcmp(FindFileData.cFileName, TEXT("..")) == 0)
		{
			//是否是文件夹
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				TCHAR nextDir[MAX_PATH * MAX_LEVEL];
				lstrcpy(nextDir, szParentPath);
				lstrcat(nextDir, L"\\");
				lstrcat(nextDir, FindFileData.cFileName);
				ProcessDir(nextDir);
			}
			else
			{
				if (m_jumpSize == -1 || FindFileData.nFileSizeLow <= m_jumpSize)
				{
					TCHAR filename[MAX_PATH * MAX_LEVEL];
					lstrcpy(filename, szParentPath);
					lstrcat(filename, L"\\");
					lstrcat(filename, FindFileData.cFileName);
					ProcessFile(filename);
				}
			}

		}

	} while (FindNextFile(hListFile, &FindFileData));
}
void CUDiskSpiderDlg::MakeDirs(CString path)
{
	CString ppath=path;
	for (int i = 0; i < path.GetLength(); i++)
	{
		ppath.SetAt(i, path[i]);
		if (path[i] == '\\')
		{
			ppath.SetAt(i, 0);
			CreateDirectory(ppath, NULL);
			ppath.SetAt(i, '\\');
		}
	}
	CreateDirectory(path, NULL);
	
}
void CUDiskSpiderDlg::ProcessNewMoveDisk(TCHAR disk)
{
	CString savePath;
	this->m_EBCviewdir.GetWindowTextW(savePath);
	MakeDirs(savePath);
	TCHAR rootDir[MAX_PATH];
	_stprintf_s(rootDir,L"%c:",disk);
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString log;
	log.Format(TEXT("%s @ %d-%d-%d %d:%d:%d Plug in."),rootDir,tm.wYear,tm.wMonth,tm.wDay,tm.wHour,tm.wMinute,tm.wSecond);
	this->m_LBRunLog.InsertString(0, log);
	ProcessDir(rootDir);
	GetLocalTime(&tm);
	log.Format(TEXT("%s @ %d-%d-%d %d:%d:%d Copy "), rootDir, tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
	for (int i = 0; i < this->m_LBtype.GetCount(); i++)
	{
		CString tp;
		this->m_LBtype.GetText(i,tp);
		log.Append(tp+" ");
	}
	this->m_LBRunLog.InsertString(0, log);
}

BOOL CUDiskSpiderDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	if (nEventType == DBT_DEVICEARRIVAL && this->m_CKBanPower.GetCheck() == 0 && this->m_LBtype.GetCount()!=0)
		{
			PDEV_BROADCAST_HDR  lhdr = (PDEV_BROADCAST_HDR)dwData;
			PDEV_BROADCAST_VOLUME lvol = (PDEV_BROADCAST_VOLUME)lhdr;
			TCHAR disk = GetDiskCharFuMask(lvol->dbcv_unitmask);
			ShowWindow(SW_HIDE);
			MessageBeep(MB_ICONINFORMATION);
			ProcessNewMoveDisk(disk);
			ShowWindow(SW_MINIMIZE);
			MessageBeep(MB_OK);
			return TRUE;
		}
		return CDialogEx::OnDeviceChange(nEventType, dwData);
}

void CUDiskSpiderDlg::OnCbnSelchangeComboFiletype()
{

	static CString InnerImage[12][15] = {
		{ L".jpg", L".png", L".gif", L".jpeg",L".bmp",L".tif",L".raw", L"#" },
		{ L".mp3", L".aac", L".ogg", L".wav",L".flac",L".amr", L"#" },
		{ L".mp4", L".avi", L".mkv", L".rmvb",L".flv",L".mov",L".wmv", L"#" },
		{ L".txt", L".doc", L".docx",L".pdf", L"#" },
		{ L".xls", L".xlsx", L"#" },
		{ L".ppt", L".pptx", L"#" },
		{ L".exe", L".bat", L".vbs", L".msi", L"#" },
		{ L".apk", L".sh",L".jar", L"#" },
		{ L".zip", L".rar", L".7z",L".tar",L".gz", L"#" },
		{ L".img", L".iso",L".wim",L"gho", L"#" },
		{ L".c", L".cpp",L".hpp", L".h", L".java", L".py", L".cs",L".go",L".asm",L".sql", L"#" },
		{ L".html", L".css", L".js",L".chm",L".xml",L".json",L"#" },
	};
	int selIndex = this->m_CBtype.GetCurSel();
	if (selIndex != -1)
	{
		int i = 0;
		while (InnerImage[selIndex][i][0] != '#')
		{
			CString str = InnerImage[selIndex][i];
			int excist = false;
			for (int j = 0; j < this->m_LBtype.GetCount(); j++)
			{
				CString instr;
				this->m_LBtype.GetText(j, instr);
				if (str == instr)
				{
					excist = true;
				}
			}
			if (excist == false)
				this->m_LBtype.AddString(str);
			i++;
		}
	}
}

void CUDiskSpiderDlg::OnBnClickedButtonInserttype()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (this->m_CSUserType.GetLength() == 0)
		return;
	//if (this->m_CSUserType[0] != '.')
	//{
	//	this->m_CSUserType = CString(".") + this->m_CSUserType.Trim();
	//}	
	CString str=this->m_CSUserType.Trim();
	int excist = false;
	for (int i = 0; i < this->m_LBtype.GetCount(); i++)
	{
		CString instr;
		this->m_LBtype.GetText(i, instr);
		if (str == instr)
		{
			excist = true;
			MessageBeep(MB_ICONWARNING);
		}
	}
	if (excist == false)
		this->m_LBtype.AddString(str);
	this->m_CSUserType = "";
	UpdateData(FALSE);
}


void CUDiskSpiderDlg::OnBnClickedButtonRemovetype()
{
	// TODO:  在此添加控件通知处理程序代码
	int selIndex = m_LBtype.GetCurSel();
	if (selIndex != -1)
	{
		this->m_LBtype.DeleteString(selIndex);
	}

}


void CUDiskSpiderDlg::OnBnClickedButtonCleartype()
{
	// TODO:  在此添加控件通知处理程序代码
	this->m_LBtype.ResetContent();
	this->m_LBRunLog.ResetContent();
	this->m_CSUserType = "";
	UpdateData(FALSE);
}


BOOL CUDiskSpiderDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->hwnd == this->m_ECUserType.GetSafeHwnd())
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_RETURN)
			{
				OnBnClickedButtonInserttype();
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUDiskSpiderDlg::OnBnClickedCheckAllfiles()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_CKAllFiles.GetCheck() == 1)
	{
		this->m_LBtype.ResetContent();
		this->m_CBtype.EnableWindow(FALSE);
		this->m_ECUserType.EnableWindow(FALSE);
		this->m_BTAdd.EnableWindow(FALSE);
		this->m_BTRemove.EnableWindow(FALSE);
	}
	else
	{
		this->m_CBtype.EnableWindow(TRUE);
		this->m_ECUserType.EnableWindow(TRUE);
		this->m_BTAdd.EnableWindow(TRUE);
		this->m_BTRemove.EnableWindow(TRUE);
	}
}


void CUDiskSpiderDlg::OnBnClickedButtonHideWnd()
{
	this->ShowWindow(SW_HIDE);
}


void CUDiskSpiderDlg::OnCbnSelchangeComboJumpSize()
{
	static int jumpSizeTable[]=
	{
		-1,
		3 * 1024 * 1024,
		8 * 1024 * 1024,
		15 * 1024 * 1024,
		30 * 1024 * 1024,
		50 * 1024 * 1024,
		100 * 1024 * 1024,
		300 * 1024 * 1024,
		500 * 1024 * 1024,
		1*1024 * 1024 * 1024,
		2*1024 * 1024 * 1024,
	};
	int selIndex = this->m_CBtype.GetCurSel();
	if (selIndex != -1)
	{
		m_jumpSize = jumpSizeTable[selIndex];
	}
}
