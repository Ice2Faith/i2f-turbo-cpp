
// 自动壁纸切换Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "自动壁纸切换.h"
#include "自动壁纸切换Dlg.h"
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


// C自动壁纸切换Dlg 对话框



C自动壁纸切换Dlg::C自动壁纸切换Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C自动壁纸切换Dlg::IDD, pParent)
	, m_WPStyle(0)
	, m_WPWaitTime(0)
	, m_isLoadFile(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C自动壁纸切换Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_PICDIR, m_EBPicView);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_CBWPStyle);
	DDX_Control(pDX, IDC_COMBO_TWAIT, m_CBWTime);
	DDX_Control(pDX, IDC_CHECK_BANPOWER, m_CBBanPower);
	DDX_Control(pDX, IDC_LIST1, m_LBImgList);
}

BEGIN_MESSAGE_MAP(C自动壁纸切换Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C自动壁纸切换Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_BANPOWER, &C自动壁纸切换Dlg::OnBnClickedCheckBanpower)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// C自动壁纸切换Dlg 消息处理程序

BOOL C自动壁纸切换Dlg::OnInitDialog()
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
	srand((unsigned int)time(NULL));
	this->m_CBWPStyle.AddString(L"平铺");
	this->m_CBWPStyle.AddString(L"居中");
	this->m_CBWPStyle.AddString(L"拉伸");
	this->m_CBWTime.AddString(L"300ms");
	this->m_CBWTime.AddString(L"500ms");
	this->m_CBWTime.AddString(L"800ms");
	this->m_CBWTime.AddString(L"1s");
	this->m_CBWTime.AddString(L"2s");
	this->m_CBWTime.AddString(L"3s");
	this->m_CBWTime.AddString(L"5s");
	this->m_CBWTime.AddString(L"10s");
	this->m_CBWTime.AddString(L"30s");
	this->m_CBWTime.AddString(L"1m");
	this->m_CBWTime.AddString(L"5m");
	this->m_CBWPStyle.SetCurSel(0);
	this->m_CBWTime.SetCurSel(0);
	this->m_CBBanPower.SetCheck(1);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C自动壁纸切换Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C自动壁纸切换Dlg::OnPaint()
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
HCURSOR C自动壁纸切换Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C自动壁纸切换Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void C自动壁纸切换Dlg::OnBnClickedCheckBanpower()
{
	// TODO:  在此添加控件通知处理程序代码
	
	KillTimer(ID_TIMER_NEXT_PIC);
	if (this->m_CBBanPower.GetCheck() == 0)
	{
		this->m_isLoadFile = false;
		KillTimer(ID_TIMER_NEXT_PIC);
		this->m_LBImgList.ResetContent();
		CString path;
		this->m_EBPicView.GetWindowText(path);
		if (path.GetLength() != 0)
		{
			TCHAR dir[MAX_PATH*MAX_LEVEL];
			lstrcpy(dir, path);
			this->m_isLoadFile=LoadImgFilesInfo(dir);
			if (this->m_isLoadFile==true)
				SetTimer(ID_TIMER_NEXT_PIC, this->m_WPWaitTime, NULL);
		}
	}
	if (this->m_isLoadFile == false)
	{
		this->m_CBBanPower.SetCheck(1);
		MessageBox(L"目录没有选择或目录下不存在图片文件png|jpg|bmp",L"配置错误",MB_OK);
	}
}
bool C自动壁纸切换Dlg::ProcessFile(TCHAR * file)
{
	CString tail = PathFindExtension(file);
	CString fullname = PathFindFileName(file);
	CString ImgTypes[20] = {L".png",L".jpg",L".bmp",L"#"};
	bool isImgFile = false;
	for (int i = 0; i < 20; i++)
	{
		if (ImgTypes[i][0] == '#')
		{
			break;
		}
		CString stail = ImgTypes[i];
		if (tail.MakeLower() == stail)
		{
			this->m_LBImgList.AddString(file);
			isImgFile = true;
		}
	}
	return isImgFile;
}
bool C自动壁纸切换Dlg::LoadImgFilesInfo(TCHAR * dir)
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
		return false;
	}
	bool haveImgFile = false;
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
				haveImgFile|=LoadImgFilesInfo(nextDir);
			}
			else
			{
				TCHAR filename[MAX_PATH * MAX_LEVEL];
				lstrcpy(filename, szParentPath);
				lstrcat(filename, L"\\");
				lstrcat(filename, FindFileData.cFileName);
				if (ProcessFile(filename) == true)
					haveImgFile = true;
			}

		}

	} while (FindNextFile(hListFile, &FindFileData));
	return haveImgFile;
}
void C自动壁纸切换Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int Style[] = { WPSTYLE_TILE, WPSTYLE_CENTER, WPSTYLE_STRETCH };
	int WaitTime[] = { 300, 500, 800, 1000, 2000, 3000, 5000, 10 * 1000, 30 * 1000, 60 * 1000, 5 * 60 * 1000 };
	if (nIDEvent == ID_TIMER_NEXT_PIC)
	{
		this->m_WPStyle = Style[this->m_CBWPStyle.GetCurSel()];
		this->m_WPWaitTime = WaitTime[this->m_CBWTime.GetCurSel()];
		if (this->m_isLoadFile == true)
		{
			TCHAR str[MAX_PATH*MAX_LEVEL] = { 0 };
			CString path;
			this->m_LBImgList.GetText(rand() % this->m_LBImgList.GetCount(), path);
			_stprintf_s(str, L"%s\0", path);
			SetWallpaper(str, this->m_WPStyle);
		}
		
	}
	
	CDialogEx::OnTimer(nIDEvent);
}
BOOL C自动壁纸切换Dlg::SetWallpaper(WCHAR * strPicFile, DWORD dwStyle)
{
	HRESULT hr;
	IActiveDesktop * pIAD;
	CoInitialize(NULL);
	//创建接口的实例
	hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER, IID_IActiveDesktop, (void**)&pIAD);
	if (!SUCCEEDED(hr)) return FALSE;
	//设置墙纸
	hr = pIAD->SetWallpaper(strPicFile, 0);
	if (!SUCCEEDED(hr)) return FALSE;
	//设置墙纸样式
	WALLPAPEROPT wpo;
	wpo.dwSize = sizeof(wpo);
	wpo.dwStyle = dwStyle;
	hr = pIAD->SetWallpaperOptions(&wpo, 0);
	if (!SUCCEEDED(hr)) return FALSE;
	//应用墙纸
	hr = pIAD->ApplyChanges(AD_APPLY_ALL);
	if (!SUCCEEDED(hr)) return FALSE;
	//释放接口的实例
	pIAD->Release();
	CoUninitialize();
	return TRUE;
}