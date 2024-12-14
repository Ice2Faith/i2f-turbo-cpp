
// 相同相似文件识别Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "相同相似文件识别.h"
#include "相同相似文件识别Dlg.h"
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


// C相同相似文件识别Dlg 对话框



C相同相似文件识别Dlg::C相同相似文件识别Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C相同相似文件识别Dlg::IDD, pParent)
	, m_str_moveToDir(_T(""))
	, m_str_all_count(_T(""))
	, m_str_group_count(_T(""))
	, m_str_src_count(_T(""))
	, m_str_useTime(_T(""))
	, m_int_pixelStep(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C相同相似文件识别Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BEGIN, m_btn_begin);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_btn_clear);
	DDX_Control(pDX, IDC_BUTTON_REMOVE, m_btn_remove);
	DDX_Control(pDX, IDC_CHECK_FILE_EQAULS, m_ckb_fileEquals);
	DDX_Control(pDX, IDC_CHECK_ONLY_FILE_SIZE, m_ckb_fileSize);
	DDX_Control(pDX, IDC_LIST_SMILAR_FILES, m_lsb_similarFiles);
	DDX_Control(pDX, IDC_LIST_SRCFILES, m_lsb_srcFiles);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, m_str_moveToDir);
	DDX_Text(pDX, IDC_STATIC_FIND_ALL_COUNT, m_str_all_count);
	DDX_Text(pDX, IDC_STATIC_FIND_GROUP_COUNT, m_str_group_count);
	DDX_Text(pDX, IDC_STATIC_SRCFILE_COUNT, m_str_src_count);
	DDX_Control(pDX, IDC_CHECK_DONT_OK, m_ckb_dontOk);
	DDX_Text(pDX, IDC_STATIC_USED_TIMESEC, m_str_useTime);
	DDX_Control(pDX, IDC_CHECK_UNIQUE_DROPFILE, m_ckb_needUniqueDropFile);
	DDX_Control(pDX, IDC_CHECK_ONLY_REPEAT, m_ckb_OnlyRepeat);
	DDX_Control(pDX, IDC_CHECK_SIMILIAR_IMAGE, m_ckb_similarImage);
	DDX_Control(pDX, IDC_CHECK_VERIFY_IMGSIZE, m_ckb_verifyImgSize);
	DDX_Control(pDX, IDC_SLIDER_SIMILAR_RATE, m_sld_similarRate);
	DDX_Text(pDX, IDC_EDIT_PIXEL_STEP, m_int_pixelStep);
	DDX_Control(pDX, IDC_CHECK_USE_IMG_GRAY, m_ckb_useImgGray);
	DDX_Control(pDX, IDC_BUTTON_DELETE_REPEAT, m_btn_deleteRepeat);
	DDX_Control(pDX, IDC_SLIDER_PIXEL_ALLOW_RATE, m_sld_pixelAllowRate);
}

BEGIN_MESSAGE_MAP(C相同相似文件识别Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C相同相似文件识别Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C相同相似文件识别Dlg::OnBnClickedCancel)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &C相同相似文件识别Dlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &C相同相似文件识别Dlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN, &C相同相似文件识别Dlg::OnBnClickedButtonBegin)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_2, &C相同相似文件识别Dlg::OnBnClickedButtonMove2)
	ON_BN_CLICKED(IDC_BUTTON_COPY_2, &C相同相似文件识别Dlg::OnBnClickedButtonCopy2)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BUTTON_DELETE_REPEAT, &C相同相似文件识别Dlg::OnBnClickedButtonDeleteRepeat)
	ON_BN_CLICKED(IDC_CHECK_ONLY_FILE_SIZE, &C相同相似文件识别Dlg::OnBnClickedCheckOnlyFileSize)
	ON_BN_CLICKED(IDC_CHECK_FILE_EQAULS, &C相同相似文件识别Dlg::OnBnClickedCheckFileEqauls)
	ON_BN_CLICKED(IDC_CHECK_SIMILIAR_IMAGE, &C相同相似文件识别Dlg::OnBnClickedCheckSimiliarImage)
	ON_BN_CLICKED(IDC_CHECK_VERIFY_IMGSIZE, &C相同相似文件识别Dlg::OnBnClickedCheckVerifyImgsize)
END_MESSAGE_MAP()


// C相同相似文件识别Dlg 消息处理程序

BOOL C相同相似文件识别Dlg::OnInitDialog()
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
	InitControls();
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C相同相似文件识别Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C相同相似文件识别Dlg::OnPaint()
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
HCURSOR C相同相似文件识别Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C相同相似文件识别Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void C相同相似文件识别Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
#include"AlgoMath.hpp"
#include"AlgoInterface.hpp"
#include"AlgoFunctional.hpp"
#include"AlgoContainer.hpp"
void C相同相似文件识别Dlg::InitControls()
{
	m_lsb_srcFiles.SetHorizontalExtent(300 * 8);
	m_lsb_similarFiles.SetHorizontalExtent(300 * 8);
	m_ckb_fileSize.SetCheck(1);

	m_sld_similarRate.SetRange(0, 100);
	m_sld_similarRate.SetPageSize(1);
	m_sld_similarRate.SetPos(75);
	m_sld_similarRate.EnableWindow(FALSE);

	m_sld_pixelAllowRate.SetRange(0, 100);
	m_sld_pixelAllowRate.SetPageSize(1);
	m_sld_pixelAllowRate.SetPos(5);
	m_sld_pixelAllowRate.EnableWindow(FALSE);

	m_int_pixelStep = 10;

	m_ckb_useImgGray.EnableWindow(FALSE);
	m_ckb_verifyImgSize.EnableWindow(FALSE);

	UpdateData(FALSE);
}

void C相同相似文件识别Dlg::OnBnClickedCheckOnlyFileSize()
{
	if (m_ckb_fileSize.GetCheck() == 1)
	{
		m_ckb_similarImage.SetCheck(0);
		m_ckb_verifyImgSize.SetCheck(0);
		m_sld_similarRate.EnableWindow(FALSE);
		m_sld_pixelAllowRate.EnableWindow(FALSE);
		m_ckb_useImgGray.EnableWindow(FALSE);
		m_ckb_verifyImgSize.EnableWindow(FALSE);

		m_ckb_OnlyRepeat.EnableWindow(TRUE);
		m_btn_deleteRepeat.EnableWindow(TRUE);
	}
}


void C相同相似文件识别Dlg::OnBnClickedCheckFileEqauls()
{
	if (m_ckb_fileEquals.GetCheck() == 1)
	{
		m_ckb_similarImage.SetCheck(0);
		m_ckb_verifyImgSize.SetCheck(0);
		m_sld_similarRate.EnableWindow(FALSE);
		m_sld_pixelAllowRate.EnableWindow(FALSE);
		m_ckb_useImgGray.EnableWindow(FALSE);
		m_ckb_verifyImgSize.EnableWindow(FALSE);

		m_ckb_OnlyRepeat.EnableWindow(TRUE);
		m_btn_deleteRepeat.EnableWindow(TRUE);
	}
}


void C相同相似文件识别Dlg::OnBnClickedCheckSimiliarImage()
{
	if (m_ckb_similarImage.GetCheck() == 1)
	{
		m_ckb_fileSize.SetCheck(0);
		m_ckb_fileEquals.SetCheck(0);
		m_sld_similarRate.EnableWindow(TRUE);
		m_sld_pixelAllowRate.EnableWindow(TRUE);
		m_ckb_useImgGray.EnableWindow(TRUE);
		m_ckb_verifyImgSize.EnableWindow(TRUE);


		m_ckb_OnlyRepeat.SetCheck(0);
		m_ckb_OnlyRepeat.EnableWindow(FALSE);
		m_btn_deleteRepeat.EnableWindow(FALSE);
	}
	else
	{
		m_ckb_OnlyRepeat.EnableWindow(TRUE);
		m_btn_deleteRepeat.EnableWindow(TRUE);
	}
}


void C相同相似文件识别Dlg::OnBnClickedCheckVerifyImgsize()
{
	if (m_ckb_verifyImgSize.GetCheck() == 1)
	{
		m_ckb_fileSize.SetCheck(0);
		m_ckb_fileEquals.SetCheck(0);
		m_sld_similarRate.EnableWindow(TRUE);
		m_sld_pixelAllowRate.EnableWindow(TRUE);
		m_ckb_useImgGray.EnableWindow(TRUE);
		m_ckb_verifyImgSize.EnableWindow(TRUE);
	}
}

bool isFile(const TCHAR * filePath)
{
	WIN32_FILE_ATTRIBUTE_DATA fileData;
	BOOL ret = ::GetFileAttributesEx(filePath, GetFileExInfoStandard, &fileData);
	if (ret == 0)
		return false;
	return fileData.dwFileAttributes && (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}


void C相同相似文件识别Dlg::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);
	if (m_ckb_dontOk.GetCheck() == 0)
		MessageBox(TEXT("操作可能耗时，即将进入后台运行"),0,MB_OK|MB_ICONINFORMATION);
	this->ShowWindow(SW_HIDE);
	bool needUnique = m_ckb_needUniqueDropFile.GetCheck() == 1;
	//对于一次拖动操作来说，所拖动的文件一般都是不重复的，因此如果现有数量为0，也就没有重复的可能性，不需要去重
	if (m_lsb_srcFiles.GetCount() == 0)
		needUnique = false;
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目
	for (int i = 0; i< DropCount; i++)
	{
		WCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名
		if (needUnique)
		{
			bool hasExist = false;
			for (int k = 0; k < m_lsb_srcFiles.GetCount(); k++)
			{
				CString tps;
				m_lsb_srcFiles.GetText(k, tps);
				if (tps == wcStr)
				{
					hasExist = true;
					break;
				}
			}
			if (hasExist == false && isFile(wcStr))
				m_lsb_srcFiles.AddString(wcStr);
		}
		else
		{
			if (isFile(wcStr))
				m_lsb_srcFiles.AddString(wcStr);
		}
	}
	DragFinish(hDropInfo);  //拖放结束后,释放内存

	m_str_src_count.Format(TEXT("源：%d"), m_lsb_srcFiles.GetCount());
	UpdateData(FALSE);

	MessageBeep(MB_OK);
	this->ShowWindow(SW_SHOW);

	CDialogEx::OnDropFiles(hDropInfo);
}


void C相同相似文件识别Dlg::OnBnClickedButtonClear()
{
	m_lsb_srcFiles.ResetContent();
	m_str_src_count.Format(TEXT("源：%d"), m_lsb_srcFiles.GetCount());
	UpdateData(FALSE);
}


void C相同相似文件识别Dlg::OnBnClickedButtonRemove()
{
	int index = m_lsb_srcFiles.GetCurSel();
	if (index == -1)
	{
		MessageBeep(MB_ICONWARNING);
		return;
	}
	m_lsb_srcFiles.DeleteString(index);
	m_str_src_count.Format(TEXT("源：%d"), m_lsb_srcFiles.GetCount());
	UpdateData(FALSE);
}


void C相同相似文件识别Dlg::OnBnClickedButtonBegin()
{
	if (m_lsb_srcFiles.GetCount() == 0)
	{
		MessageBox(TEXT("请先拖动文件到程序中"), 0, MB_OK | MB_ICONWARNING);
		return;
	}
	UpdateData(TRUE);
	if (m_ckb_dontOk.GetCheck() == 0)
		MessageBox(TEXT("操作可能耗时，即将进入后台运行"), 0, MB_OK | MB_ICONINFORMATION);
	long befTime = GetTickCount();
	this->ShowWindow(SW_HIDE);

	m_lsb_similarFiles.ResetContent();

	if (m_ckb_fileEquals.GetCheck() == 1)
	{
		checkFilesEquals();
	}
	else if (m_ckb_fileSize.GetCheck() == 1)
	{
		checkFileSize();
	}
	else if (m_ckb_similarImage.GetCheck() == 1)
	{
		checkImageSimilar();
	}

	MessageBeep(MB_OK);
	this->ShowWindow(SW_SHOW);

	m_str_useTime.Format(TEXT("耗时：%.2lfs"),(GetTickCount()-befTime)/1000.0);
	UpdateData(FALSE);
}

void C相同相似文件识别Dlg::OnBnClickedButtonMove2()
{
	if (m_lsb_similarFiles.GetCount() == 0)
	{
		MessageBox(TEXT("还没有项目哦，请先点击【开始】"), 0, MB_OK | MB_ICONWARNING);
		return;
	}
	UpdateData(TRUE);

	bool isOnlyRepeat = m_ckb_OnlyRepeat.GetCheck() == 1;
	if (m_ckb_dontOk.GetCheck() == 0)
		MessageBox(TEXT("操作可能耗时，即将进入后台运行"), 0, MB_OK | MB_ICONINFORMATION);
	this->ShowWindow(SW_HIDE);
	UpdateData(TRUE);
	int succCount = 0;
	int count = m_lsb_similarFiles.GetCount();
	for (int i = 0; i < count; i++)
	{
		CString srcStr;
		m_lsb_similarFiles.GetText(i, srcStr);
		if (srcStr[0] == '#')
		{
			if (isOnlyRepeat)
				continue;
			srcStr = srcStr.Mid(1);
		}
		CString drtStr = m_str_moveToDir + TEXT("\\") + PathFindFileName(srcStr);
		if (MoveFile(srcStr, drtStr))
			succCount++;
	}

	this->ShowWindow(SW_SHOW);
	CString tips;
	tips.Format(TEXT("总共：%d 成功：%d"), count, succCount);
	MessageBox(tips, 0, MB_OK | MB_ICONINFORMATION);
}


void C相同相似文件识别Dlg::OnBnClickedButtonCopy2()
{
	if (m_lsb_similarFiles.GetCount() == 0)
	{
		MessageBox(TEXT("还没有项目哦，请先点击【开始】"), 0, MB_OK | MB_ICONWARNING);
		return;
	}
	
	UpdateData(TRUE);

	bool isOnlyRepeat = m_ckb_OnlyRepeat.GetCheck() == 1;
	if (m_ckb_dontOk.GetCheck() == 0)
		MessageBox(TEXT("操作可能耗时，即将进入后台运行"), 0, MB_OK | MB_ICONINFORMATION);
	this->ShowWindow(SW_HIDE);
	int succCount = 0;
	int count = m_lsb_similarFiles.GetCount();
	for (int i = 0; i < count; i++)
	{
		CString srcStr;
		m_lsb_similarFiles.GetText(i, srcStr);
		if (srcStr[0] == '#')
		{
			if (isOnlyRepeat)
				continue;
			srcStr = srcStr.Mid(1);
		}
		CString drtStr = m_str_moveToDir + TEXT("\\") + PathFindFileName(srcStr);
		if (CopyFile(srcStr, drtStr, TRUE))
			succCount++;
	}

	this->ShowWindow(SW_SHOW);
	CString tips;
	tips.Format(TEXT("总共：%d 成功：%d"), count, succCount);
	MessageBox(tips, 0, MB_OK | MB_ICONINFORMATION);
}


BOOL C相同相似文件识别Dlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	MessageBox(TEXT("先拖入文件，\n\
勾选上识别模式，\n\
点击开始，\n\
等待结束即可,\n\
结束后支持移动和复制操作\n\n\
文件内容相同比较模式\n\t\
将会涉及到文件IO的操作，时间可能很漫长\n\
仅文件大小相同模式\n\t\
只进行读取文件属性，速度很快\n\n\
拖入文件去重\n\t\
当文件数量较大时，不建议去重，否则非常耗费时间,仅拖入一次\n\t\
当文件数量较少是，可以进行去重，这样方便在多文件夹中拖进来\n\n\
相似图片\n\t\
相当耗费时间，因此步长越长将会降低耗费时间，但是精确度随之降低\n\t\
使用灰度，将大概率会增加一些识别度(也可能降低识别度)，耗时也会降低\n\t\
检查尺寸，将会直接比较图片宽高大小，即刻返回，对于大小不一样的图片，将会认定不相似\n\t\
像素容差，指两张图片中的像素的允许差异，差异越大，越不像的图片也可能成为相似图片\n\t\
相似率，决定了认定两张图片相似的下线，不低于此下线，将会认定相似\n\
"),0,MB_OK|MB_ICONINFORMATION);

	return TRUE;// CDialogEx::OnHelpInfo(pHelpInfo);
}


void C相同相似文件识别Dlg::OnBnClickedButtonDeleteRepeat()
{
	if (m_lsb_similarFiles.GetCount() == 0)
	{
		MessageBox(TEXT("还没有项目哦，请先点击【开始】"), 0, MB_OK | MB_ICONWARNING);
		return;
	}

	UpdateData(TRUE);

	if (MessageBox(TEXT("您即将删除右侧框中，同组内重复元素\n（同组内视为相同文件）,是否确认删除？"), 0, MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
	{
		MessageBeep(MB_ICONWARNING);
		return;
	}

	int repeatCount = 0;
	int succCount = 0;
	int count = m_lsb_similarFiles.GetCount();
	for (int i = 0; i < count; i++)
	{
		CString srcStr;
		m_lsb_similarFiles.GetText(i, srcStr);
		if (srcStr[0] == '#')
		{
			continue;
		}
		repeatCount++;
		if (DeleteFile(srcStr))
			succCount++;
	}

	CString tips;
	tips.Format(TEXT("总共：%d 重复：%d 成功：%d"), count,repeatCount, succCount);
	MessageBox(tips, 0, MB_OK | MB_ICONINFORMATION);
}

//////////////////////////////////////////////////////////////////////////////////////////
//file part

int CmpFileSize(PEqualsFilesInfo fp1, PEqualsFilesInfo fp2)
{
	if (fp1->fzSize.HighPart == fp2->fzSize.HighPart)
	{
		if (fp1->fzSize.LowPart == fp2->fzSize.LowPart)
		{
			return 0;
		}
		else if (fp1->fzSize.LowPart < fp2->fzSize.LowPart)
		{
			return -1;
		}
		else
		{
			return 1;
		}

	}
	else if (fp1->fzSize.HighPart < fp2->fzSize.HighPart)
	{
		return -1;
	}
	else
	{
		return 1;
	}

}
void C相同相似文件识别Dlg::checkFileSize()
{
	int count = m_lsb_srcFiles.GetCount();
	AlgoArray<PEqualsFilesInfo, int> arrs(count);
	for (int i = 0; i < count; i++)
	{
		arrs[i] = new EqualsFilesInfo;
		m_lsb_srcFiles.GetText(i, arrs[i]->fzName);
		HANDLE hFile = CreateFile(arrs[i]->fzName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		GetFileSizeEx(hFile, &(arrs[i]->fzSize));
		CloseHandle(hFile);
	}
	AlgoSortQuick<
		PEqualsFilesInfo,
		PEqualsFilesInfo,
		int,
		int(*)(PEqualsFilesInfo, PEqualsFilesInfo)
	>
	(arrs.getData(), count, CmpFileSize,
	AlgoArraySelectGet<PEqualsFilesInfo, PEqualsFilesInfo, int >,
	AlgoArraySelectSet<PEqualsFilesInfo, PEqualsFilesInfo, int >,
	true);

	int resultGroup = 0;
	bool firstOne = true;
	for (int i = 1; i < count; i++)
	{
		if (CmpFileSize(arrs[i], arrs[i - 1]) == 0)
		{
			if (firstOne)
			{
				CString str = TEXT("#");
				str = str + arrs[i - 1]->fzName;
				m_lsb_similarFiles.AddString(str);
				resultGroup++;
			}
			m_lsb_similarFiles.AddString(arrs[i]->fzName);
			firstOne = false;
		}
		else
		{
			firstOne = true;
		}
	}


	m_lsb_srcFiles.ResetContent();
	for (int i = 0; i < count; i++)
	{
		m_lsb_srcFiles.AddString(arrs[i]->fzName);
		delete arrs[i];
	}

	m_str_all_count.Format(TEXT("重：%d"), m_lsb_similarFiles.GetCount());
	m_str_group_count.Format(TEXT("组：%d"), resultGroup);
	UpdateData(FALSE);
}
int CmpFile(PEqualsFilesDataInfo  fp1, PEqualsFilesDataInfo fp2)
{
	fseek(fp1->fp, 0, SEEK_SET);
	fseek(fp2->fp, 0, SEEK_SET);
	while (!feof(fp1->fp) && !feof(fp2->fp))
	{
		unsigned char ch1, ch2;
		int r1c = fread(&ch1, sizeof(unsigned char), 1, fp1->fp);
		int r2c = fread(&ch2, sizeof(unsigned char), 1, fp1->fp);

		if (r1c == 0 && r1c == r2c)
			return 0;
		if (r1c == 0 && r2c)
			return -1;
		if (r1c && r2c == 0)
			return 1;

		if (ch1 != ch2)
			return (int)ch1 - (int)ch2;
	}
	return 0;
}
int CmpFileCheckSum(PEqualsFilesDataInfo  fp1, PEqualsFilesDataInfo fp2)
{
	return (fp1->checkSum) - (fp2->checkSum);
}

long getFileCheckSum(FILE * fp)
{
	long ret = 0;
	fseek(fp, 0, SEEK_SET);
	long fac = 0x23571113;
	while (!feof(fp))
	{
		unsigned char ch1;
		int r1c = fread(&ch1, sizeof(unsigned char), 1, fp);
		if (r1c == 0)
			return ret;
		ret = (long)(ret * 7 + (ch1 * 31)) ^ fac;
		fac = (long)(fac + 19);
	}
}


void C相同相似文件识别Dlg::checkFilesEquals()
{
	//先得到等大小的列表，减少文件IO操作带来的时长
	checkFileSize();
	//获得列表里的所有项目保存（等大小）
	int count = m_lsb_similarFiles.GetCount();
	AlgoArray<CString, int> allItems(count);
	AlgoArray<int, int> groupIndexs;
	groupIndexs.setSize(0);
	for (int i = 0; i < count; i++)
	{
		CString srcStr;
		m_lsb_similarFiles.GetText(i, srcStr);
		if (srcStr[0] == '#')
		{
			//根据分组依据，记录分组的开始下标
			groupIndexs.push(i);
			srcStr = srcStr.Mid(1);
		}
		allItems[i] = srcStr;
	}
	//为了方便程序运行，记录最后一组索引结束
	groupIndexs.push(count - 1);

	//清空等大小列表框
	m_lsb_similarFiles.ResetContent();

	//保存最终相同文件
	AlgoArray<CString, int> saveItems;
	int resultGroup = 0;

	USES_CONVERSION;
	//遍历所有等大小组，进行组文件比较
	int gpid = 0;
	while (gpid < groupIndexs.size() - 1)
	{
		//获取当前组的大小的相关数据进行保存
		int tpgpsize = groupIndexs[gpid + 1] - groupIndexs[gpid] + 1;
		AlgoArray<PEqualsFilesDataInfo, int> tpgpArr(tpgpsize);
		for (int k = 0; k < tpgpsize; k++)
		{
			tpgpArr[k] = new EqualsFilesDataInfo;
			lstrcpy(tpgpArr[k]->fzName, allItems[groupIndexs[gpid] + k]);
			tpgpArr[k]->fp = fopen(T2A(tpgpArr[k]->fzName), "rb");
			tpgpArr[k]->checkSum = getFileCheckSum(tpgpArr[k]->fp);//直接比较文件的话，IO操作将会非常频繁，将会非常浪费时间，因此直接计算出一个特征码进行比较算了
			//注意，这个只是特征码，不是散列值，因此发生重复的可能性还是比较大的
			//但是由于是在等大小文件的前提下计算，因此这个重复性会有所降低，一般来说，可以得到唯一的特征码（文件内容不同的情况下）
			//这样，直接比较特征码就行了
		}

		//根据特征码排序
		AlgoSortQuick<
			PEqualsFilesDataInfo,
			PEqualsFilesDataInfo,
			int,
			int(*)(PEqualsFilesDataInfo, PEqualsFilesDataInfo)
		>
		(tpgpArr.getData(), tpgpsize, CmpFileCheckSum,
		AlgoArraySelectGet<PEqualsFilesDataInfo, PEqualsFilesDataInfo, int >,
		AlgoArraySelectSet<PEqualsFilesDataInfo, PEqualsFilesDataInfo, int >,
		true);
		//获得相同特征码的所有数据项进行保存

		bool firstOne = true;
		for (int i = 1; i < tpgpsize; i++)
		{
			if (CmpFileCheckSum(tpgpArr[i], tpgpArr[i - 1]) == 0)
			{
				if (firstOne)
				{
					CString str = TEXT("#");
					str = str + tpgpArr[i - 1]->fzName;
					saveItems.push(str);
					resultGroup++;
				}
				saveItems.push(tpgpArr[i]->fzName);
				firstOne = false;
			}
			else
			{
				firstOne = true;
			}
		}
		//关闭之前打开的文件等资源
		for (int k = 0; k < tpgpsize; k++)
		{
			EqualsFilesDataInfo tpk = *tpgpArr[k];
			fclose(tpgpArr[k]->fp);
			tpgpArr[k]->fp = NULL;
			delete tpgpArr[k];
		}

		gpid++;
	}
	//将最终结果进行显示
	for (int i = 0; i < saveItems.size(); i++)
	{
		m_lsb_similarFiles.AddString(saveItems[i]);
	}

	m_str_all_count.Format(TEXT("重：%d"), saveItems.size());
	m_str_group_count.Format(TEXT("组：%d"), resultGroup);
	UpdateData(FALSE);

}

///////////////////////////////////////////////////////////////////////////////////////////
//image part

#include<Windows.h>
#include<graphics.h>
double getImageSimilarRate(HDC hdc1, HDC hdc2, int wid, int hei, double allowRate = 0.2, bool useGray = false, int fastPer = 1)
{
	int xstep = fastPer;
	int ystep = fastPer;
	if (xstep <= 1)
		xstep = 1;
	if (ystep <= 1)
		ystep = 1;

	double countAll = 0;
	double countSimilar = 0;
	for (int x = 0; x < wid; x += xstep)
	{
		for (int y = 0; y < hei; y += ystep)
		{
			countAll++;
			COLORREF c1 = GetPixel(hdc1, x, y);
			COLORREF c2 = GetPixel(hdc2, x, y);
			if (useGray)
			{
				c1 = RGBtoGRAY(c1);
				c2 = RGBtoGRAY(c2);

				double g1 = c1 & 0xff;
				double g2 = c2 & 0xff;

				if (abs(g1 - g2) / 256.0 <= allowRate)
					countSimilar++;
			}
			else
			{
				double r1 = (c1)& 0xff;
				double g1 = (c1 >> 8) & 0xff;
				double b1 = (c1 >> 16) & 0xff;
				double a1 = (c1 >> 24) & 0xff;
				
				double r2 = (c2)& 0xff;
				double g2 = (c2 >> 8) & 0xff;
				double b2 = (c2 >> 16) & 0xff;
				double a2 = (c2 >> 24) & 0xff;

				if (abs(r1 - r2) / 256.0 <= allowRate
					&& abs(g1 - g2) / 256.0 <= allowRate
					&& abs(b1 - b2) / 256.0 <= allowRate
					&& abs(a1 - a2) / 256.0 <= allowRate)
					countSimilar++;
			}
		}
	}

	return countSimilar*1.0 / countAll;
}

double getImageSimilarRate(IMAGE * img1, IMAGE * img2, double allowRate = 0.2, bool useGray = false, int fastPer = 1, bool checkSize = true)
{
	int wid1, hei1, wid2, hei2;
	wid1 = img1->getwidth();
	hei1 = img1->getheight();
	wid2 = img2->getwidth();
	hei2 = img2->getheight();
	if (wid1 != wid2 || hei1 != hei2)
	{
		if (checkSize)
			return 0;


		wid2 = wid1;
		hei2 = hei1;

		img2->Resize(wid2, hei2);
	}


	HDC hdc1 = GetImageHDC(img1);
	HDC hdc2 = GetImageHDC(img2);

	return getImageSimilarRate(hdc1, hdc2, wid1, hei1, allowRate, useGray, fastPer);
}


typedef struct _image_size_info
{
	TCHAR fzName[MAX_PATH];
	int width;
	int height;
}IMAGE_SIZE_INFO,*PIMAGE_SIZE_INFO;
typedef struct _image_similiar_info
{
	int id1;
	int id2;
	double similarRate;
}IMAGE_SIMILIAR_INFO,*PIMAGE_SIMILIAR_INFO;

int CmpImageSize(PIMAGE_SIZE_INFO img1, PIMAGE_SIZE_INFO img2)
{
	int size1 = img1->width*img1->height;
	int size2 = img2->width*img2->height;
	return size1 - size2;
}

void C相同相似文件识别Dlg::checkImageSimilar()
{
	UpdateData(TRUE);

	bool needCheckSize = false;
	if (m_ckb_verifyImgSize.GetCheck() == 1)
	{
		needCheckSize = true;
	}
	else
	{
		needCheckSize = false;
	}
	double allowRate = m_sld_similarRate.GetPos() / 100.0;
	double pixAllowRate = m_sld_pixelAllowRate.GetPos() / 100.0;
	bool useGray = m_ckb_useImgGray.GetCheck() == 1;
	int pixStep = m_int_pixelStep;

	int dig_all_file_count = m_lsb_srcFiles.GetCount();
	int dig_all_image_count = 0;
	int dig_all_repeat_count = 0;

	int srccount = m_lsb_srcFiles.GetCount();
	AlgoArray<PIMAGE_SIZE_INFO, int> allImages;
	for (int i = 0; i < srccount; i++)
	{
		PIMAGE_SIZE_INFO tps = new IMAGE_SIZE_INFO;
		m_lsb_srcFiles.GetText(i, tps->fzName);
		IMAGE timg;
		loadimage(&timg, tps->fzName);
		tps->width = timg.getwidth();
		tps->height = timg.getheight();
		if (tps->width>0 && tps->height > 0)
			allImages.push(tps);
		else
			delete tps;
	}

	dig_all_image_count = allImages.size();


	
	AlgoArray<PIMAGE_SIMILIAR_INFO, int> allSimInfoArr;
	for (int i = 0; i < dig_all_image_count; i++)
	{
		IMAGE img1;
		loadimage(&img1, allImages[i]->fzName);
		for (int j = i + 1; j < dig_all_image_count; j++)
		{
			PIMAGE_SIMILIAR_INFO ptp = new IMAGE_SIMILIAR_INFO;
			ptp->id1 = i;
			ptp->id2 = j;
			IMAGE img2;
			loadimage(&img1, allImages[j]->fzName);
			ptp->similarRate = getImageSimilarRate(&img1, &img2, pixAllowRate, useGray, pixStep, needCheckSize);
			if (ptp->similarRate >= allowRate)
				allSimInfoArr.push(ptp);
			else
				delete ptp;
		}
	}

	AlgoArray<int, int> allRepeats;
	for (int i = 0; i < allSimInfoArr.size(); i++)
	{
		bool containsId1 = false;
		bool containsId2 = false;
		for (int j = 0; j < allRepeats.size(); j++)
		{
			if (allSimInfoArr[i]->id1 == allRepeats[j])
				containsId1 = true;
			if (allSimInfoArr[i]->id2 == allRepeats[j])
				containsId2 = true;
			if (containsId1 && containsId2)
				break;
		}
		if (containsId1 == false)
			allRepeats.push(allSimInfoArr[i]->id1);
		if (containsId2 == false)
			allRepeats.push(allSimInfoArr[i]->id2);

		delete allSimInfoArr[i];
		allSimInfoArr[i] = NULL;
	}

	dig_all_repeat_count = allRepeats.size();

	for (int i = 0; i < dig_all_repeat_count; i++)
	{
		m_lsb_similarFiles.AddString(allImages[allRepeats[i]]->fzName);
	}

	for (int i = 0; i < dig_all_image_count; i++)
	{
		delete allImages[i];
		allImages[i] = NULL;
	}

	m_str_all_count.Format(TEXT("重：%d"), dig_all_repeat_count);
	m_str_group_count.Format(TEXT("源图：%d"), dig_all_image_count);
	UpdateData(FALSE);

	/*CString tips;
	tips.Format(TEXT("总文件:%d 图像文件:%d 相似:%d\n参数：检查大小：%d 使用灰度：%d 步长：%d 像素容差率：%.2f 相似率：%.2f"),
		dig_all_file_count,dig_all_image_count,dig_all_repeat_count,
		needCheckSize,useGray,pixStep,pixAllowRate,allowRate);
	MessageBox(tips,0,MB_OK|MB_ICONINFORMATION);*/
}
