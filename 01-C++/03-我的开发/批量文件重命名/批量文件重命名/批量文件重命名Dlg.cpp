
// 批量文件重命名Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "批量文件重命名.h"
#include "批量文件重命名Dlg.h"
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


// C批量文件重命名Dlg 对话框



C批量文件重命名Dlg::C批量文件重命名Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C批量文件重命名Dlg::IDD, pParent)
	, m_str_newFileName(_T(""))
	, m_str_beginNumber(_T(""))
	, m_str_unifySuffix(_T(""))
	, m_str_addDirectoryAll(_T(""))
	, m_b_isFirstDropFiles(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C批量文件重命名Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_COMBO_NEW_FILE_MODE, m_cbx_newFileMode);
	DDX_Text(pDX, IDC_EDIT_NEW_FILE_NAME, m_str_newFileName);
	DDX_Control(pDX, IDC_CHECK_ADD_TIME, m_ckb_addTime);
	DDX_Control(pDX, IDC_COMBO_TIME_MODE, m_cmb_timeMode);
	DDX_Control(pDX, IDC_COMBO_NEW_FILE_MODE, m_cmb_newFileMode);
	DDX_Control(pDX, IDC_COMBO_SPLIT_OPERATOR, m_cmb_splitOperator);
	DDX_Control(pDX, IDC_COMBO_OPE_SPACE, m_cmb_opeSpace);
	DDX_Text(pDX, IDC_EDIT_BEGIN_NUMBER, m_str_beginNumber);
	DDX_Control(pDX, IDC_CHECK_UNIFY_SUFFIX, m_ckb_unifySuffix);
	DDX_Text(pDX, IDC_EDIT_UNIFY_SUFFIX, m_str_unifySuffix);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_ADD_DIRECTORY_ALL, m_str_addDirectoryAll);
	DDX_Control(pDX, IDC_LIST_FILES, m_lsb_files);
	DDX_Control(pDX, IDC_CHECK_TRANSPARENT_TOPMOST, m_ckb_useTransTopWnd);
	DDX_Control(pDX, ID_PROGRESS_OPERATION, m_pgs_operations);
	DDX_Control(pDX, IDC_COMBO_TIME_FORMAT, m_cmb_timeFormat);
	//  DDX_Control(pDX, IDC_COMBO_DATE_FORMAT, m_cmb_dataFormat);
	DDX_Control(pDX, IDC_COMBO_DATE_FORMAT, m_cmb_dateFormat);
	DDX_Control(pDX, IDC_CHECK_CLEAN_ALL_WHEN_DONE, m_ckb_cleanAllWhenDone);
	DDX_Control(pDX, IDC_EDIT_NEW_FILE_NAME, m_edt_newFileName);
	DDX_Control(pDX, IDC_EDIT_BEGIN_NUMBER, m_edt_beginNumber);
	DDX_Control(pDX, IDC_EDIT_UNIFY_SUFFIX, m_edt_unifySuffix);
}

BEGIN_MESSAGE_MAP(C批量文件重命名Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C批量文件重命名Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C批量文件重命名Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_ADD_DIR_ALL, &C批量文件重命名Dlg::OnBnClickedButtonAddDirAll)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_ALL, &C批量文件重命名Dlg::OnBnClickedButtonCleanAll)
	ON_BN_CLICKED(IDC_BUTTON_START_RENAME, &C批量文件重命名Dlg::OnBnClickedButtonStartRename)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_CHECK_TRANSPARENT_TOPMOST, &C批量文件重命名Dlg::OnBnClickedCheckTransparentTopmost)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &C批量文件重命名Dlg::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// C批量文件重命名Dlg 消息处理程序

BOOL C批量文件重命名Dlg::OnInitDialog()
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
	initControls();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C批量文件重命名Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C批量文件重命名Dlg::OnPaint()
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
HCURSOR C批量文件重命名Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void C批量文件重命名Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void C批量文件重命名Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void C批量文件重命名Dlg::initControls()
{
	m_cmb_newFileMode.AddString(TEXT("新文件名"));
	m_cmb_newFileMode.AddString(TEXT("源文件名"));
	m_cmb_newFileMode.SetCurSel(0);

	m_cmb_timeMode.AddString(TEXT("日期"));
	m_cmb_timeMode.AddString(TEXT("时间"));
	m_cmb_timeMode.AddString(TEXT("日期时间"));
	m_cmb_timeMode.SetCurSel(0);

	m_cmb_timeFormat.AddString(TEXT("hhmmss"));
	m_cmb_timeFormat.AddString(TEXT("hh时mm分ss秒"));
	m_cmb_timeFormat.AddString(TEXT("hh_mm_ss"));
	m_cmb_timeFormat.SetCurSel(0);
	
	m_cmb_dateFormat.AddString(TEXT("yyyyMMdd"));
	m_cmb_dateFormat.AddString(TEXT("yyyy年MM月dd日"));
	m_cmb_dateFormat.AddString(TEXT("yyyy-MM-dd"));
	m_cmb_dateFormat.SetCurSel(0);

	m_cmb_splitOperator.AddString(TEXT("-"));
	m_cmb_splitOperator.AddString(TEXT("_"));
	m_cmb_splitOperator.AddString(TEXT("+"));
	m_cmb_splitOperator.AddString(TEXT("空格"));
	m_cmb_splitOperator.AddString(TEXT("无"));
	m_cmb_splitOperator.SetCurSel(0);

	m_cmb_opeSpace.AddString(TEXT("尾部"));
	m_cmb_opeSpace.AddString(TEXT("首部"));
	m_cmb_opeSpace.SetCurSel(0);

	m_str_beginNumber = TEXT("001");

	m_lsb_files.SetHorizontalExtent(MAX_PATH * 8);

	UpdateData(FALSE);
}

void SetWindowTranparentTopmostStyle(HWND hwnd, bool isTransTop)
{
	if (isTransTop)
	{
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
		SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 180, LWA_ALPHA);
	}
	else
	{
		SetWindowPos(hwnd, HWND_DESKTOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
		SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	}
}

void C批量文件重命名Dlg::OnBnClickedCheckTransparentTopmost()
{
	svcSwitchTranparentTopmostWnd();
}

bool isFilePath(const TCHAR * filePath)
{
	WIN32_FILE_ATTRIBUTE_DATA fileData;
	BOOL ret = ::GetFileAttributesEx(filePath, GetFileExInfoStandard, &fileData);
	if (ret == 0)
		return false;
	return fileData.dwFileAttributes && (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

bool C批量文件重命名Dlg::addItemToFileList(TCHAR * szStr,bool needUnique)
{
	if (needUnique)
	{
		bool hasExist = false;
		int count = m_lsb_files.GetCount();
		for (int k = 0; k < count; k++)
		{
			CString tps;
			m_lsb_files.GetText(k, tps);
			if (tps == szStr)
			{
				hasExist = true;
				break;
			}
		}
		if (hasExist == false)
		{
			m_lsb_files.AddString(szStr);
			return true;
		}
			
	}
	else
	{
		m_lsb_files.AddString(szStr);
		return true;
	}
	return false;
}

void C批量文件重命名Dlg::OnDropFiles(HDROP hDropInfo)
{

	UpdateData(TRUE);
	if (m_b_isFirstDropFiles)
	{
		MessageBox(TEXT("加载文件可能会比较耗时，将会与隐藏后台运行\n（此提示进首次运行显示）"), 0, MB_OK | MB_ICONINFORMATION);
		m_b_isFirstDropFiles = false;
	}

	this->ShowWindow(SW_HIDE);
	bool needUnique = m_lsb_files.GetCount() != 0;
	

	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目
	for (int i = 0; i< DropCount; i++)
	{
		TCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名
		addItemToFileList(wcStr,needUnique);
	}
	DragFinish(hDropInfo);  //拖放结束后,释放内存


	MessageBeep(MB_OK);
	this->ShowWindow(SW_SHOW);

	CDialogEx::OnDropFiles(hDropInfo);
}

void C批量文件重命名Dlg::OnBnClickedButtonAddDirAll()
{
	this->ShowWindow(SW_HIDE);

	UpdateData(TRUE);
	bool needUnique = m_lsb_files.GetCount() != 0;


	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	CString dir = m_str_addDirectoryAll;
	bool hasDirSplit = false;
	if (dir[dir.GetLength() - 1] == '\\')
	{
		dir += TEXT("*");
		hasDirSplit = true;
	}
	else
	{
		dir += TEXT("\\*");
	}
	hListFile = ::FindFirstFile(dir, &FindFileData);
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
				CString pst = m_str_addDirectoryAll;
				if (!hasDirSplit)
					pst += TEXT("\\");
				pst += FindFileData.cFileName;
				//addItemToFileList(pst.GetBuffer(), needUnique);//不添加文件夹
			}
			else
			{
				CString pst = m_str_addDirectoryAll;
				if (!hasDirSplit)
					pst += TEXT("\\");
				pst += FindFileData.cFileName;
				addItemToFileList(pst.GetBuffer(), needUnique);
			}
		}

	} while (::FindNextFile(hListFile, &FindFileData));

	MessageBeep(MB_OK);
	this->ShowWindow(SW_SHOW);
}

void C批量文件重命名Dlg::OnBnClickedButtonRemove()
{
	svcDeleteItem();
}

void C批量文件重命名Dlg::OnBnClickedButtonCleanAll()
{
	svcCleanAllItem();
}

CString C批量文件重命名Dlg::getFormatTime()
{
	CString ret;
	int selIndex = m_cmb_timeFormat.GetCurSel();
	switch (selIndex)
	{
	case 0:
		ret = TEXT("%02d%02d%02d");
		break;
	case 1:
		ret = TEXT("%02d时%02d分%02d秒");
		break;
	case 2:
		ret = TEXT("%02d_%02d_%02d");
		break;
	}
	return ret;
}


CString C批量文件重命名Dlg::getFormatDate()
{
	CString ret;
	int selIndex = m_cmb_dateFormat.GetCurSel();
	switch (selIndex)
	{
	case 0:
		ret = TEXT("%04d%02d%02d");
		break;
	case 1:
		ret = TEXT("%02d年%02d月%02d日");
		break;
	case 2:
		ret = TEXT("%02d-%02d-%02d");
		break;
	}
	return ret;
}

CString C批量文件重命名Dlg::getFormatDateTime()
{
	return getFormatDate() + getFormatTime();
}


CString C批量文件重命名Dlg::getSplitOperator()
{
	CString ret;
	int selIndex = m_cmb_splitOperator.GetCurSel();
	switch (selIndex)
	{
	case 0:
		ret = TEXT("-");
		break;
	case 1:
		ret = TEXT("_");
		break;
	case 2:
		ret = TEXT("+");
		break;
	case 3:
		ret = TEXT(" ");
		break;
	case 4:
		ret = TEXT("");
		break;
	}
	return ret;
}


CString C批量文件重命名Dlg::getUnifySuffix()
{
	UpdateData(TRUE);
	CString ret = m_str_unifySuffix.Trim();
	if (ret.GetLength() > 0 && ret[0] != '.')
		ret = TEXT(".") + ret;

	m_str_unifySuffix = ret;
	UpdateData(FALSE);
	return ret;
}


int C批量文件重命名Dlg::getBeginNumberAndFormatString(CString & formatStr)
{
	UpdateData(TRUE);
	CString ret = m_str_beginNumber.Trim();
	m_str_beginNumber = ret;
	UpdateData(FALSE);

	int lenRet = ret.GetLength();

	int numIndex = -1;
	for (int i = 0; i < lenRet; i++)
	{
		if (ret[i] != '0')
		{
			numIndex = i;
			break;
		}
	}

	int num = 0;
	for (; numIndex < lenRet; numIndex++)
	{
		num *= 10;
		num += ret[numIndex] - '0';
	}

	formatStr.Format(TEXT("%%0%dd"),lenRet);

	return num;
}


void C批量文件重命名Dlg::OnBnClickedButtonStartRename()
{
	svcStartRename();
}


CString C批量文件重命名Dlg::getNumberPartStr(int num,const CString & formatStr)
{
	CString ret;
	ret.Format(formatStr, num);
	return ret;
}


CString C批量文件重命名Dlg::getTimePartStr(struct tm * loctime, const CString & formatStr)
{
	CString ret;
	ret.Format(formatStr, loctime->tm_hour, loctime->tm_min, loctime->tm_sec);
	return ret;
}
CString C批量文件重命名Dlg::getDatePartStr(struct tm * loctime, const CString & formatStr)
{
	CString ret;
	ret.Format(formatStr, loctime->tm_year + 1900, loctime->tm_mon + 1, loctime->tm_mday);
	return ret;
}
CString C批量文件重命名Dlg::getDateTimePartStr(struct tm * loctime, const CString & formatStr)
{
	CString ret;
	ret.Format(formatStr, loctime->tm_year + 1900, loctime->tm_mon + 1, loctime->tm_mday,
		loctime->tm_hour, loctime->tm_min, loctime->tm_sec);
	return ret;
}


bool C批量文件重命名Dlg::getIsUseNewFileName()
{
	return m_cmb_newFileMode.GetCurSel()==0;
}


bool C批量文件重命名Dlg::getIsNumSpaceHead()
{
	return m_cmb_opeSpace.GetCurSel()==1;
}


bool C批量文件重命名Dlg::getIsUseUnifySuffix()
{
	return m_ckb_unifySuffix.GetCheck() == 1;
}


bool C批量文件重命名Dlg::getIsUseTimePart()
{
	return m_ckb_addTime.GetCheck() == 1;
}


CString C批量文件重命名Dlg::getUseableTimeStr()
{
	struct tm * lotime = NULL;
	if (m_ckb_addTime.GetCheck() == 1)
	{
		time_t nowtime;
		time(&nowtime);
		lotime = localtime(&nowtime);
	}

	CString partTime;
	CString formatTime;
	int selTimeIndex = m_cmb_timeMode.GetCurSel();
	switch (selTimeIndex)
	{
	case 0:
		formatTime = getFormatDate();
		partTime = getDatePartStr(lotime, formatTime);
		break;
	case 1:
		formatTime = getFormatTime();
		partTime = getTimePartStr(lotime, formatTime);
		break;
	case 2:
		formatTime = getFormatDateTime();
		partTime = getDateTimePartStr(lotime, formatTime);
		break;
	}
	return partTime;
}


CString C批量文件重命名Dlg::getNewFileNameStr()
{
	return m_str_newFileName.Trim();
}


BOOL C批量文件重命名Dlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	MessageBox(TEXT("使用步骤：\n\
\t1.拖入文件（可以是包含目录）\n\
\t或者载入选中目录下的所有文件（不会包含目录）\n\
\t2.设定参数（必填起始序号）\n\
\t3.点击开始\n\
\t4.等待重命名结束\n\
注意事项：\n\
\t新文件名中，不要包含非法的文件名称\n\
\t否则可能重命名失败\n\
\t新文件名不要和旧文件名重名\n\
\t否则同样重命名失败\n\
按键指南：\n\
\tCtrl+Enter:相当于点击开始\n\
\tDelete:删除选中项\n\
\tCtrl+Delete:清空所有项\n\
\tCtrl+F:定位到新文件名输入框\n\
\tCtrl+N:定位到起始序号输入框\n\
\tCtrl+U:定位到统一后缀输入框\n\
\tCtrl+W:切换是否透明置顶\n\
\tCtrl+D:切换是否完成后清空\n\
\tCtrl+I:切换是否统一后缀\n\
\tCtrl+T:切换是否添加时间\n\
开发:\n\
\tCopyright @ Ugex.Savelar\n\
"), 0, MB_OK | MB_ICONINFORMATION);

	return TRUE;// CDialogEx::OnHelpInfo(pHelpInfo);
}


bool C批量文件重命名Dlg::svcStartRename()
{
	if (m_lsb_files.GetCount() == 0)
	{
		MessageBox(TEXT("未载入任何文件或目录，请拖入文件（/目录）后重试！\n(比如：拖动文件或目录到此窗口上\n或者加载一个目录下的所有文件（不含子目录）)"), 0, MB_OK | MB_ICONWARNING);
		return false;
	}

	UpdateData(TRUE);

	bool useUnifySuffix = getIsUseUnifySuffix();
	bool useTimePart = getIsUseTimePart();
	bool useNewFileName = getIsUseNewFileName();
	bool useHeadNumber = getIsNumSpaceHead();


	if (useNewFileName && m_str_newFileName.GetLength() == 0)
	{
		MessageBox(TEXT("新文件名模式下，请输入新文件名后重试！\n(比如：hello/.test/...)"), 0, MB_OK | MB_ICONWARNING);
		return false;
	}

	if (useUnifySuffix && m_str_unifySuffix.GetLength() == 0)
	{
		MessageBox(TEXT("统一后缀下，请输入新后缀名后重试！\n(比如：mp3/.jpg/...)"), 0, MB_OK | MB_ICONWARNING);
		return false;
	}

	if (m_str_beginNumber.GetLength() == 0)
	{
		MessageBox(TEXT("无开始序号，请输入开始序号后重试！\n(比如：1/01/001/050/1050/...)"), 0, MB_OK | MB_ICONWARNING);
		return false;
	}

	if (IDCANCEL == MessageBox(TEXT("即将开始重命名，此过程不可撤销，\n是否确认继续?"), 0, MB_OKCANCEL | MB_ICONQUESTION))
	{
		return false;
	}

	CString partSplitOperator = getSplitOperator();
	CString partUnifySuffix;
	if (useUnifySuffix)
		partUnifySuffix = getUnifySuffix();
	CString partTime;
	if (useTimePart)
		partTime = getUseableTimeStr();
	CString partNewFileName;
	if (useNewFileName)
		partNewFileName = getNewFileNameStr();

	CString numFormat;
	int numBegin = 0;
	numBegin = getBeginNumberAndFormatString(numFormat);

	m_pgs_operations.SetRange(0, 10000);
	m_pgs_operations.SetPos(0);

	int sucCount = 0;
	int count = m_lsb_files.GetCount();
	for (int i = 0; i < count; i++)
	{
		CString srcPath;
		m_lsb_files.GetText(i, srcPath);

		CString srcDir;
		CString srcName;
		CString srcSuffix;

		srcSuffix = PathFindExtension(srcPath);
		srcName = PathFindFileName(srcPath);
		srcDir = srcPath.Left(srcPath.GetLength() - srcName.GetLength());
		srcName = srcName.Left(srcName.GetLength() - srcSuffix.GetLength());

		CString drtPath;
		drtPath += srcDir;
		if (useHeadNumber)
		{
			drtPath += getNumberPartStr(numBegin + i, numFormat);
		}

		if (useHeadNumber && drtPath.GetLength() > 0)
			drtPath += partSplitOperator;

		if (useNewFileName)
			drtPath += partNewFileName;
		else
			drtPath += srcName;

		if (useTimePart)
		{
			if (drtPath.GetLength() > 0)
				drtPath += partSplitOperator;
			drtPath += partTime;
		}


		if (useHeadNumber == false)
		{
			if (drtPath.GetLength() > 0)
				drtPath += partSplitOperator;
			drtPath += getNumberPartStr(numBegin + i, numFormat);
		}


		if (useUnifySuffix)
			drtPath += partUnifySuffix;
		else
			drtPath += srcSuffix;


		if (MoveFile(srcPath, drtPath))
			sucCount++;

		m_pgs_operations.SetPos((i + 1)*1.0 / count * 10000);
	}

	CString tipsDone;
	tipsDone.Format(TEXT("共：%d 完成：%d 失败：%d"), count, sucCount, count - sucCount);
	MessageBox(tipsDone, 0, MB_OK | MB_ICONINFORMATION);

	if (m_ckb_cleanAllWhenDone.GetCheck() == 1)
	{
		m_lsb_files.ResetContent();
	}

	m_str_beginNumber = getNumberPartStr(numBegin + count, numFormat);
	UpdateData(FALSE);

	return true;
}


bool C批量文件重命名Dlg::svcDeleteItem()
{
	int selIndex = m_lsb_files.GetCurSel();
	if (selIndex == -1)
	{
		MessageBeep(MB_ICONWARNING);
		return false;
	}
	m_lsb_files.DeleteString(selIndex);

	return true;
}



bool C批量文件重命名Dlg::svcCleanAllItem()
{
	m_lsb_files.ResetContent();
	return true;
}


bool C批量文件重命名Dlg::svcSwitchTranparentTopmostWnd(bool isUserClick)
{
	if (isUserClick)
	{
		bool isTransparentTopMost = m_ckb_useTransTopWnd.GetCheck() == 1;
		SetWindowTranparentTopmostStyle(this->GetSafeHwnd(), isTransparentTopMost);
	}
	else
	{
		if (m_ckb_useTransTopWnd.GetCheck() == 1)
		{
			m_ckb_useTransTopWnd.SetCheck(0);
			SetWindowTranparentTopmostStyle(this->GetSafeHwnd(), false);
		}
		else
		{
			m_ckb_useTransTopWnd.SetCheck(1);
			SetWindowTranparentTopmostStyle(this->GetSafeHwnd(), true);
		}

	}
	
	return true;
}


bool C批量文件重命名Dlg::svcSwitchCleanAllWhenDone()
{
	if (m_ckb_cleanAllWhenDone.GetCheck() == 1)
	{
		m_ckb_cleanAllWhenDone.SetCheck(0);
	}
	else
	{
		m_ckb_cleanAllWhenDone.SetCheck(1);
	}
	return true;
}
bool C批量文件重命名Dlg::svcSwitchUnifySuffix()
{
	if (m_ckb_unifySuffix.GetCheck() == 1)
	{
		m_ckb_unifySuffix.SetCheck(0);
	}
	else
	{
		m_ckb_unifySuffix.SetCheck(1);
	}
	return true;
}


bool C批量文件重命名Dlg::svcSwitchAddTime()
{
	if (m_ckb_addTime.GetCheck() == 1)
	{
		m_ckb_addTime.SetCheck(0);
	}
	else
	{
		m_ckb_addTime.SetCheck(1);
	}
	return true;
}

BOOL C批量文件重命名Dlg::PreTranslateMessage(MSG* pMsg)
{
	static bool isControlDown = false;
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_CONTROL:
			isControlDown = true;
			break;
		case VK_RETURN:
			if (isControlDown)
				svcStartRename();
			break;
		case VK_DELETE:
			if (isControlDown)
				svcCleanAllItem();
			else
				svcDeleteItem();
			break;
		case 'F':
			if (isControlDown)
				m_edt_newFileName.SetFocus();
			break;
		case 'N':
			if (isControlDown)
				m_edt_beginNumber.SetFocus();
			break;
		case 'U':
			if (isControlDown)
				m_edt_unifySuffix.SetFocus();
			break;
		case 'W':
			if (isControlDown)
				svcSwitchTranparentTopmostWnd(false);
			break;
		case 'D':
			if (isControlDown)
				svcSwitchCleanAllWhenDone();
			break;
		case 'I':
			if (isControlDown)
				svcSwitchUnifySuffix();
			break;
		case 'T':
			if (isControlDown)
				svcSwitchAddTime();
			break;
		}
	}
	else if (pMsg->message == WM_KEYUP)
	{
		if (pMsg->wParam == VK_CONTROL)
			isControlDown = false;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

