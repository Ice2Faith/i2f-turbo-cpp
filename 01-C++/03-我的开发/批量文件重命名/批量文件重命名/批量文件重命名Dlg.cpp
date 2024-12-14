
// �����ļ�������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�����ļ�������.h"
#include "�����ļ�������Dlg.h"
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


// C�����ļ�������Dlg �Ի���



C�����ļ�������Dlg::C�����ļ�������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�����ļ�������Dlg::IDD, pParent)
	, m_str_newFileName(_T(""))
	, m_str_beginNumber(_T(""))
	, m_str_unifySuffix(_T(""))
	, m_str_addDirectoryAll(_T(""))
	, m_b_isFirstDropFiles(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C�����ļ�������Dlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(C�����ļ�������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C�����ļ�������Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C�����ļ�������Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_ADD_DIR_ALL, &C�����ļ�������Dlg::OnBnClickedButtonAddDirAll)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_ALL, &C�����ļ�������Dlg::OnBnClickedButtonCleanAll)
	ON_BN_CLICKED(IDC_BUTTON_START_RENAME, &C�����ļ�������Dlg::OnBnClickedButtonStartRename)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_CHECK_TRANSPARENT_TOPMOST, &C�����ļ�������Dlg::OnBnClickedCheckTransparentTopmost)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &C�����ļ�������Dlg::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// C�����ļ�������Dlg ��Ϣ�������

BOOL C�����ļ�������Dlg::OnInitDialog()
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
	initControls();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C�����ļ�������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C�����ļ�������Dlg::OnPaint()
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
HCURSOR C�����ļ�������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void C�����ļ�������Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void C�����ļ�������Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void C�����ļ�������Dlg::initControls()
{
	m_cmb_newFileMode.AddString(TEXT("���ļ���"));
	m_cmb_newFileMode.AddString(TEXT("Դ�ļ���"));
	m_cmb_newFileMode.SetCurSel(0);

	m_cmb_timeMode.AddString(TEXT("����"));
	m_cmb_timeMode.AddString(TEXT("ʱ��"));
	m_cmb_timeMode.AddString(TEXT("����ʱ��"));
	m_cmb_timeMode.SetCurSel(0);

	m_cmb_timeFormat.AddString(TEXT("hhmmss"));
	m_cmb_timeFormat.AddString(TEXT("hhʱmm��ss��"));
	m_cmb_timeFormat.AddString(TEXT("hh_mm_ss"));
	m_cmb_timeFormat.SetCurSel(0);
	
	m_cmb_dateFormat.AddString(TEXT("yyyyMMdd"));
	m_cmb_dateFormat.AddString(TEXT("yyyy��MM��dd��"));
	m_cmb_dateFormat.AddString(TEXT("yyyy-MM-dd"));
	m_cmb_dateFormat.SetCurSel(0);

	m_cmb_splitOperator.AddString(TEXT("-"));
	m_cmb_splitOperator.AddString(TEXT("_"));
	m_cmb_splitOperator.AddString(TEXT("+"));
	m_cmb_splitOperator.AddString(TEXT("�ո�"));
	m_cmb_splitOperator.AddString(TEXT("��"));
	m_cmb_splitOperator.SetCurSel(0);

	m_cmb_opeSpace.AddString(TEXT("β��"));
	m_cmb_opeSpace.AddString(TEXT("�ײ�"));
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

void C�����ļ�������Dlg::OnBnClickedCheckTransparentTopmost()
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

bool C�����ļ�������Dlg::addItemToFileList(TCHAR * szStr,bool needUnique)
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

void C�����ļ�������Dlg::OnDropFiles(HDROP hDropInfo)
{

	UpdateData(TRUE);
	if (m_b_isFirstDropFiles)
	{
		MessageBox(TEXT("�����ļ����ܻ�ȽϺ�ʱ�����������غ�̨����\n������ʾ���״�������ʾ��"), 0, MB_OK | MB_ICONINFORMATION);
		m_b_isFirstDropFiles = false;
	}

	this->ShowWindow(SW_HIDE);
	bool needUnique = m_lsb_files.GetCount() != 0;
	

	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//ȡ�ñ��϶��ļ�����Ŀ
	for (int i = 0; i< DropCount; i++)
	{
		TCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���
		addItemToFileList(wcStr,needUnique);
	}
	DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�


	MessageBeep(MB_OK);
	this->ShowWindow(SW_SHOW);

	CDialogEx::OnDropFiles(hDropInfo);
}

void C�����ļ�������Dlg::OnBnClickedButtonAddDirAll()
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
			//�Ƿ����ļ���
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				CString pst = m_str_addDirectoryAll;
				if (!hasDirSplit)
					pst += TEXT("\\");
				pst += FindFileData.cFileName;
				//addItemToFileList(pst.GetBuffer(), needUnique);//������ļ���
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

void C�����ļ�������Dlg::OnBnClickedButtonRemove()
{
	svcDeleteItem();
}

void C�����ļ�������Dlg::OnBnClickedButtonCleanAll()
{
	svcCleanAllItem();
}

CString C�����ļ�������Dlg::getFormatTime()
{
	CString ret;
	int selIndex = m_cmb_timeFormat.GetCurSel();
	switch (selIndex)
	{
	case 0:
		ret = TEXT("%02d%02d%02d");
		break;
	case 1:
		ret = TEXT("%02dʱ%02d��%02d��");
		break;
	case 2:
		ret = TEXT("%02d_%02d_%02d");
		break;
	}
	return ret;
}


CString C�����ļ�������Dlg::getFormatDate()
{
	CString ret;
	int selIndex = m_cmb_dateFormat.GetCurSel();
	switch (selIndex)
	{
	case 0:
		ret = TEXT("%04d%02d%02d");
		break;
	case 1:
		ret = TEXT("%02d��%02d��%02d��");
		break;
	case 2:
		ret = TEXT("%02d-%02d-%02d");
		break;
	}
	return ret;
}

CString C�����ļ�������Dlg::getFormatDateTime()
{
	return getFormatDate() + getFormatTime();
}


CString C�����ļ�������Dlg::getSplitOperator()
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


CString C�����ļ�������Dlg::getUnifySuffix()
{
	UpdateData(TRUE);
	CString ret = m_str_unifySuffix.Trim();
	if (ret.GetLength() > 0 && ret[0] != '.')
		ret = TEXT(".") + ret;

	m_str_unifySuffix = ret;
	UpdateData(FALSE);
	return ret;
}


int C�����ļ�������Dlg::getBeginNumberAndFormatString(CString & formatStr)
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


void C�����ļ�������Dlg::OnBnClickedButtonStartRename()
{
	svcStartRename();
}


CString C�����ļ�������Dlg::getNumberPartStr(int num,const CString & formatStr)
{
	CString ret;
	ret.Format(formatStr, num);
	return ret;
}


CString C�����ļ�������Dlg::getTimePartStr(struct tm * loctime, const CString & formatStr)
{
	CString ret;
	ret.Format(formatStr, loctime->tm_hour, loctime->tm_min, loctime->tm_sec);
	return ret;
}
CString C�����ļ�������Dlg::getDatePartStr(struct tm * loctime, const CString & formatStr)
{
	CString ret;
	ret.Format(formatStr, loctime->tm_year + 1900, loctime->tm_mon + 1, loctime->tm_mday);
	return ret;
}
CString C�����ļ�������Dlg::getDateTimePartStr(struct tm * loctime, const CString & formatStr)
{
	CString ret;
	ret.Format(formatStr, loctime->tm_year + 1900, loctime->tm_mon + 1, loctime->tm_mday,
		loctime->tm_hour, loctime->tm_min, loctime->tm_sec);
	return ret;
}


bool C�����ļ�������Dlg::getIsUseNewFileName()
{
	return m_cmb_newFileMode.GetCurSel()==0;
}


bool C�����ļ�������Dlg::getIsNumSpaceHead()
{
	return m_cmb_opeSpace.GetCurSel()==1;
}


bool C�����ļ�������Dlg::getIsUseUnifySuffix()
{
	return m_ckb_unifySuffix.GetCheck() == 1;
}


bool C�����ļ�������Dlg::getIsUseTimePart()
{
	return m_ckb_addTime.GetCheck() == 1;
}


CString C�����ļ�������Dlg::getUseableTimeStr()
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


CString C�����ļ�������Dlg::getNewFileNameStr()
{
	return m_str_newFileName.Trim();
}


BOOL C�����ļ�������Dlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	MessageBox(TEXT("ʹ�ò��裺\n\
\t1.�����ļ��������ǰ���Ŀ¼��\n\
\t��������ѡ��Ŀ¼�µ������ļ����������Ŀ¼��\n\
\t2.�趨������������ʼ��ţ�\n\
\t3.�����ʼ\n\
\t4.�ȴ�����������\n\
ע�����\n\
\t���ļ����У���Ҫ�����Ƿ����ļ�����\n\
\t�������������ʧ��\n\
\t���ļ�����Ҫ�;��ļ�������\n\
\t����ͬ��������ʧ��\n\
����ָ�ϣ�\n\
\tCtrl+Enter:�൱�ڵ����ʼ\n\
\tDelete:ɾ��ѡ����\n\
\tCtrl+Delete:���������\n\
\tCtrl+F:��λ�����ļ��������\n\
\tCtrl+N:��λ����ʼ��������\n\
\tCtrl+U:��λ��ͳһ��׺�����\n\
\tCtrl+W:�л��Ƿ�͸���ö�\n\
\tCtrl+D:�л��Ƿ���ɺ����\n\
\tCtrl+I:�л��Ƿ�ͳһ��׺\n\
\tCtrl+T:�л��Ƿ����ʱ��\n\
����:\n\
\tCopyright @ Ugex.Savelar\n\
"), 0, MB_OK | MB_ICONINFORMATION);

	return TRUE;// CDialogEx::OnHelpInfo(pHelpInfo);
}


bool C�����ļ�������Dlg::svcStartRename()
{
	if (m_lsb_files.GetCount() == 0)
	{
		MessageBox(TEXT("δ�����κ��ļ���Ŀ¼���������ļ���/Ŀ¼�������ԣ�\n(���磺�϶��ļ���Ŀ¼���˴�����\n���߼���һ��Ŀ¼�µ������ļ���������Ŀ¼��)"), 0, MB_OK | MB_ICONWARNING);
		return false;
	}

	UpdateData(TRUE);

	bool useUnifySuffix = getIsUseUnifySuffix();
	bool useTimePart = getIsUseTimePart();
	bool useNewFileName = getIsUseNewFileName();
	bool useHeadNumber = getIsNumSpaceHead();


	if (useNewFileName && m_str_newFileName.GetLength() == 0)
	{
		MessageBox(TEXT("���ļ���ģʽ�£����������ļ��������ԣ�\n(���磺hello/.test/...)"), 0, MB_OK | MB_ICONWARNING);
		return false;
	}

	if (useUnifySuffix && m_str_unifySuffix.GetLength() == 0)
	{
		MessageBox(TEXT("ͳһ��׺�£��������º�׺�������ԣ�\n(���磺mp3/.jpg/...)"), 0, MB_OK | MB_ICONWARNING);
		return false;
	}

	if (m_str_beginNumber.GetLength() == 0)
	{
		MessageBox(TEXT("�޿�ʼ��ţ������뿪ʼ��ź����ԣ�\n(���磺1/01/001/050/1050/...)"), 0, MB_OK | MB_ICONWARNING);
		return false;
	}

	if (IDCANCEL == MessageBox(TEXT("������ʼ���������˹��̲��ɳ�����\n�Ƿ�ȷ�ϼ���?"), 0, MB_OKCANCEL | MB_ICONQUESTION))
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
	tipsDone.Format(TEXT("����%d ��ɣ�%d ʧ�ܣ�%d"), count, sucCount, count - sucCount);
	MessageBox(tipsDone, 0, MB_OK | MB_ICONINFORMATION);

	if (m_ckb_cleanAllWhenDone.GetCheck() == 1)
	{
		m_lsb_files.ResetContent();
	}

	m_str_beginNumber = getNumberPartStr(numBegin + count, numFormat);
	UpdateData(FALSE);

	return true;
}


bool C�����ļ�������Dlg::svcDeleteItem()
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



bool C�����ļ�������Dlg::svcCleanAllItem()
{
	m_lsb_files.ResetContent();
	return true;
}


bool C�����ļ�������Dlg::svcSwitchTranparentTopmostWnd(bool isUserClick)
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


bool C�����ļ�������Dlg::svcSwitchCleanAllWhenDone()
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
bool C�����ļ�������Dlg::svcSwitchUnifySuffix()
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


bool C�����ļ�������Dlg::svcSwitchAddTime()
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

BOOL C�����ļ�������Dlg::PreTranslateMessage(MSG* pMsg)
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

