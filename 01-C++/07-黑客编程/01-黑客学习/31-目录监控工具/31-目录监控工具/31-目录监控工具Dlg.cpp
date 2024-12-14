
// 31-目录监控工具Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "31-目录监控工具.h"
#include "31-目录监控工具Dlg.h"
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


// CMy31目录监控工具Dlg 对话框



CMy31目录监控工具Dlg::CMy31目录监控工具Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy31目录监控工具Dlg::IDD, pParent)
	, m_strSpyPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy31目录监控工具Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_SPY_PATH, m_strSpyPath);
	DDX_Control(pDX, IDC_LIST_SPY_LOG, m_list_spy_log);
	DDX_Control(pDX, IDC_BUTTON_SPY_ON, m_btn_spyon);
	DDX_Control(pDX, IDC_BUTTON_SPY_OFF, m_btn_spyoff);
}

BEGIN_MESSAGE_MAP(CMy31目录监控工具Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy31目录监控工具Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SPY_ON, &CMy31目录监控工具Dlg::OnBnClickedButtonSpyOn)
	ON_BN_CLICKED(IDC_BUTTON_SPY_OFF, &CMy31目录监控工具Dlg::OnBnClickedButtonSpyOff)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_LIST, &CMy31目录监控工具Dlg::OnBnClickedButtonClearList)
END_MESSAGE_MAP()


// CMy31目录监控工具Dlg 消息处理程序

BOOL CMy31目录监控工具Dlg::OnInitDialog()
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
	InitFaceControl();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy31目录监控工具Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy31目录监控工具Dlg::OnPaint()
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
HCURSOR CMy31目录监控工具Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy31目录监控工具Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
/*
目录监控函数：
	BOOL ReadDirectoryChangesW(
    _In_        HANDLE hDirectory,//指向要监控的目录的句柄，该目录要用FILE_LIST_DIRECTORY的访问权限打开
    _Out_writes_bytes_to_(nBufferLength, *lpBytesReturned) LPVOID lpBuffer,//参数指向一个存放返回结果的缓冲区，结果为FILE_NOTIFY_INFORMATION的结构体，由于该结构体最后一个成员是一字节的数组
    _In_        DWORD nBufferLength,//标识缓冲区的大小
    _In_        BOOL bWatchSubtree,//指示是否监控子目录的操作
    _In_        DWORD dwNotifyFilter,//指示要返回何种类型的文件变更后的类型
    _Out_opt_   LPDWORD lpBytesReturned,//真正的返回的数据大小
    _Inout_opt_ LPOVERLAPPED lpOverlapped,//参数执行一个OVERLAPPED结构体，用于异步操作时，一般为NULL
    _In_opt_    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine//异步回调函数，一般为NULL
    );
*/
//全局变量，提供给线程函数使用
static CListCtrl * g_p_list_spy_log;
static HANDLE g_hSpyFile;
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	//清空列表框
	g_p_list_spy_log->DeleteAllItems();
	//缓冲结构体数据定义
	BYTE buffer[1024] = { 0 };
	int bufferSize = sizeof(buffer);
	FILE_NOTIFY_INFORMATION * pbuffer = (FILE_NOTIFY_INFORMATION *)buffer;
	
	BOOL bret = FALSE;
	DWORD bytesReturned = 0;
	int index = 0;
	//循环获取变化的记录
	while (true)
	{
		//获取监视信息
		bret = ReadDirectoryChangesW(g_hSpyFile,
			&buffer,
			bufferSize,
			TRUE,
			FILE_NOTIFY_CHANGE_FILE_NAME |//监视所有操作
			FILE_NOTIFY_CHANGE_ATTRIBUTES |
			FILE_NOTIFY_CHANGE_LAST_WRITE|
			FILE_NOTIFY_CHANGE_CREATION|
			FILE_NOTIFY_CHANGE_DIR_NAME|
			FILE_NOTIFY_CHANGE_LAST_ACCESS|
			FILE_NOTIFY_CHANGE_SECURITY|
			FILE_NOTIFY_CHANGE_SIZE,
			&bytesReturned,
			NULL, NULL);
		if (bret == TRUE)//显示监视信息
		{
			switch (pbuffer->Action)
			{
			case FILE_ACTION_ADDED:
				g_p_list_spy_log->InsertItem(index, TEXT("添加"));
			case FILE_ACTION_REMOVED:
				 g_p_list_spy_log->InsertItem(index, TEXT("删除"));
			case FILE_ACTION_MODIFIED:
				g_p_list_spy_log->InsertItem(index, TEXT("修改"));
			case FILE_ACTION_RENAMED_NEW_NAME:
			{
				if (pbuffer->Action == FILE_ACTION_RENAMED_NEW_NAME)//由于使用了case的穿透性质，所以此处需要判断
					g_p_list_spy_log->InsertItem(index, TEXT("重命名(new)"));
				g_p_list_spy_log->SetItemText(index, 1, pbuffer->FileName);//添加操作对象
				if (pbuffer->NextEntryOffset != 0)//添加操作结果
				{//如果存在下一个操作结果项数据就输出，不存在就置空
					 FILE_NOTIFY_INFORMATION * tpbuffer = (FILE_NOTIFY_INFORMATION *)((DWORD)pbuffer + pbuffer->NextEntryOffset);
					 g_p_list_spy_log->SetItemText(index, 2, tpbuffer->FileName);
				}
				else
					 g_p_list_spy_log->SetItemText(index, 2, TEXT(""));
				index++;//在列表框中插入的位置增加
			}
				break;
			case FILE_ACTION_RENAMED_OLD_NAME:
			{
									  g_p_list_spy_log->InsertItem(index, TEXT("重命名"));
									  g_p_list_spy_log->SetItemText(index, 1, pbuffer->FileName);
									  if (pbuffer->NextEntryOffset != 0)
									  {
										  FILE_NOTIFY_INFORMATION * tpbuffer = (FILE_NOTIFY_INFORMATION *)((DWORD)pbuffer+pbuffer->NextEntryOffset);
										  switch (tpbuffer->Action)
										  {
										  case FILE_ACTION_RENAMED_NEW_NAME://获取重命名之后的新文件名
										  {
																			   g_p_list_spy_log->SetItemText(index, 2, tpbuffer->FileName);
										  }
											  break;
										  }
										 
									  }else
										g_p_list_spy_log->SetItemText(index, 2, TEXT(""));
									  index++;
			}
				break;
				
			}
			if (index < 0)//如果出现整数溢出，清空
			{
				index = 0;
				g_p_list_spy_log->DeleteAllItems();
			}

		}
	}
	return 0;
}
void CMy31目录监控工具Dlg::OnBnClickedButtonSpyOn()
{
	UpdateData(TRUE);
	if (m_strSpyPath == "")//获取输入的目录并判空
		return;
	g_hSpyFile = CreateFile(m_strSpyPath,//打开这个目录进行监视
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);
	if (g_hSpyFile == INVALID_HANDLE_VALUE)
	{
		g_hSpyFile = NULL;
		return;
	}
	g_p_list_spy_log = &m_list_spy_log;//设置线程函数使用的全局变量，并设置按钮状态
	m_btn_spyon.EnableWindow(FALSE);
	m_btn_spyoff.EnableWindow(TRUE);
	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);//启动线程
	//WaitForSingleObject(hThread, INFINITE);//这里只是一个提示等待线程结束而已，这里并不需要等待结束
}


void CMy31目录监控工具Dlg::OnBnClickedButtonSpyOff()
{
	m_btn_spyon.EnableWindow(TRUE);
	m_btn_spyoff.EnableWindow(FALSE);//切换按钮状态
	TerminateThread(hThread, 0);//终止线程
	if (hThread != NULL)//释放句柄
		CloseHandle(hThread);
	if (g_hSpyFile != NULL)
		CloseHandle(g_hSpyFile);
	hThread = NULL;
	g_hSpyFile = NULL;

}

void CMy31目录监控工具Dlg::InitFaceControl()
{
	//设置拓展样式，有网格线和选择一整行
	m_list_spy_log.SetExtendedStyle(m_list_spy_log.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//插入列
	m_list_spy_log.InsertColumn(0, TEXT("操作行为"));
	m_list_spy_log.InsertColumn(1, TEXT("操       作       对       象"));
	m_list_spy_log.InsertColumn(2, TEXT("操       作       结       果"));
	//设置自动列宽
	m_list_spy_log.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_spy_log.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_list_spy_log.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	//默认不开启监控
	hThread = NULL;
	g_hSpyFile = NULL;
	
	m_btn_spyoff.EnableWindow(FALSE);
}


void CMy31目录监控工具Dlg::OnBnClickedButtonClearList()
{
	m_list_spy_log.DeleteAllItems();
}
