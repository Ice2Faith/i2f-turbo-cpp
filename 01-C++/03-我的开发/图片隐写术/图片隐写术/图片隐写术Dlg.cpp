
// 图片隐写术Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "图片隐写术.h"
#include "图片隐写术Dlg.h"
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


// C图片隐写术Dlg 对话框



C图片隐写术Dlg::C图片隐写术Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C图片隐写术Dlg::IDD, pParent)
	, m_strPicturePath(_T(""))
	, m_strPictureSize(_T(""))
	, m_strMaxHideByteSize(_T(""))
	, m_strHideDatas(_T(""))
	, m_strTipsResult(_T(""))
	, m_strSavePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C图片隐写术Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_VIEW_PICTURE, m_edtViewPicture);
	DDX_Control(pDX, IDC_EDIT_IMG_SIZE, m_edtImgSize);
	DDX_Control(pDX, IDC_EDIT_IMG_MAXBYTE, m_edtImgMaxByte);
	DDX_Control(pDX, IDC_EDIT_HIDE_DATA, m_edtHideData);
	DDX_Control(pDX, IDC_EDIT_TIP_RESULT, m_edtTipResult);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_VIEW_PICTURE, m_strPicturePath);
	DDX_Text(pDX, IDC_EDIT_IMG_SIZE, m_strPictureSize);
	DDX_Text(pDX, IDC_EDIT_IMG_MAXBYTE, m_strMaxHideByteSize);
	DDX_Text(pDX, IDC_EDIT_HIDE_DATA, m_strHideDatas);
	DDX_Text(pDX, IDC_EDIT_TIP_RESULT, m_strTipsResult);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_SAVE_PICTURE, m_edtSavePicture);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_SAVE_PICTURE, m_strSavePath);
}

BEGIN_MESSAGE_MAP(C图片隐写术Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C图片隐写术Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C图片隐写术Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_READ_HIDE_DATA, &C图片隐写术Dlg::OnBnClickedButtonReadHideData)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_HIDE_DATA, &C图片隐写术Dlg::OnBnClickedButtonWriteHideData)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &C图片隐写术Dlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &C图片隐写术Dlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_DATA_SIZE, &C图片隐写术Dlg::OnBnClickedButtonDataSize)
END_MESSAGE_MAP()


// C图片隐写术Dlg 消息处理程序

BOOL C图片隐写术Dlg::OnInitDialog()
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

void C图片隐写术Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C图片隐写术Dlg::OnPaint()
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
HCURSOR C图片隐写术Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void C图片隐写术Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

char * Unicode2Utf8(wchar_t * wstr, char * astr,int * needSize)
{
	int size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	if (astr == NULL){
		*needSize = size;
		return astr;
	}
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, astr, size, NULL, NULL);
	return astr;
}
wchar_t * Utf82Unicode(char * astr, wchar_t * wstr, int * needSize)
{
	int size = MultiByteToWideChar(CP_UTF8, 0, astr, -1, NULL, 0);
	if (wstr == NULL){
		*needSize = size;
		return wstr;
	}
	MultiByteToWideChar(CP_UTF8, 0, astr, -1, wstr, size);
	return wstr;
}

void C图片隐写术Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	UpdateData(TRUE);

	if (m_strPicturePath.GetLength() == 0){
		m_strTipsResult = TEXT("请先浏览图片！");
		UpdateData(FALSE);
		return;
	}
	TCHAR path[MAX_PATH] = { 0 };
	m_edtViewPicture.GetWindowText(path, MAX_PATH);

	m_hide.loadImageFile(path);

	m_strPictureSize.Format(TEXT("%d * %d"), m_hide.getPictureWidth(), m_hide.getPictureHeight());

	int size = m_hide.getMaxHideByte();
	m_strMaxHideByteSize.Format(TEXT("%d kb %d byte"), size/1024, size);

	m_strSavePath = m_strPicturePath;
	m_strTipsResult = TEXT("确认图片");

	UpdateData(FALSE);
}



void C图片隐写术Dlg::OnBnClickedButtonReadHideData()
{
	UpdateData(TRUE);

	if (m_strPicturePath.GetLength() == 0){
		m_strTipsResult = TEXT("请先浏览图片并点击确定！");
		UpdateData(FALSE);
		return;
	}


	int needSize = m_hide.getHideDataByteSize();
	char * udata = (char *)malloc(sizeof(char)*(needSize+1));
	memset(udata, 0, needSize + 1);
	int rdSize = m_hide.readData((unsigned char *)udata, needSize);

	if (rdSize>0){
		m_strTipsResult.Format(TEXT("读隐数据成功:%d kb %d byte"), needSize / 1024, needSize);
	}
	else{
		m_strTipsResult = TEXT("读隐数据失败，未隐写图片或隐写数据为0");
	}


	UpdateData(FALSE);

	SetDlgItemTextA(this->GetSafeHwnd(), IDC_EDIT_HIDE_DATA, udata);

	free(udata);
	/*
	//转为UTF8会出现乱码，启用，使用ASCII的GBK
	int wsize = 0;
	Utf82Unicode(udata, NULL, &wsize);
	WCHAR * wdata = (WCHAR *)malloc(sizeof(WCHAR)*(wsize + 1));
	memset(wdata, 0, sizeof(WCHAR)*(wsize + 1));
	Utf82Unicode(udata, wdata, &wsize);

	m_strHideDatas = wdata;
	free(udata);
	free(wdata);

	if (rdSize>0){
		m_strTipsResult.Format(TEXT("读隐数据成功:%d kb %d byte"),needSize/1024,needSize);
	}
	else{
		m_strTipsResult = TEXT("读隐数据失败，未隐写图片或隐写数据为0");
	}


	UpdateData(FALSE);
	*/
}


void C图片隐写术Dlg::OnBnClickedButtonWriteHideData()
{
	UpdateData(TRUE);

	if (m_strPicturePath.GetLength() == 0){
		m_strTipsResult = TEXT("请先浏览图片并点击确定！");
		UpdateData(FALSE);
		return;
	}

	//申请1M空间
	int byteSize = 1024 * 1024;
	char * maxBuf = (char *)malloc(sizeof(char)*(byteSize));
	int needSize = GetDlgItemTextA(this->GetSafeHwnd(), IDC_EDIT_HIDE_DATA, maxBuf, byteSize - 1);
	
	bool res = m_hide.writeData((unsigned char *)maxBuf, needSize + 1);
	free(maxBuf);

	if (res){
		needSize = needSize + 1;
		m_strTipsResult.Format(TEXT("隐写数据成功:%d kb %d byte"), needSize / 1024, needSize);
	}
	else{
		m_strTipsResult = TEXT("隐写数据失败，图片尺寸不足以保存隐写数据量");
	}

	UpdateData(FALSE);
	
	/*
	//转为UTF8会出现乱码，启用，使用ASCII的GBK
	int ssize = m_strHideDatas.GetLength() + 1;
	WCHAR * sdata = (WCHAR*)malloc(sizeof(WCHAR)*ssize);
	m_edtHideData.GetWindowTextW(sdata, ssize-1);


	int needSize = 0;
	Unicode2Utf8(sdata, NULL, &needSize);

	char * udata = (char *)malloc(sizeof(char)*(needSize + 1));
	Unicode2Utf8(sdata, udata, &needSize);

	//多写入一个字节，作为字符串结尾，防止读取数据时处理不当，字符串结尾乱码
	bool res = m_hide.writeData((unsigned char *)udata, needSize+1);
	free(sdata);
	free(udata);
	
	if (res){
		needSize = needSize + 1;
		m_strTipsResult.Format(TEXT("隐写数据成功:%d kb %d byte"), needSize / 1024, needSize);
	}
	else{
		m_strTipsResult = TEXT("隐写数据失败，图片尺寸不足以保存隐写数据量");
	}

	UpdateData(FALSE);
	*/
}


void C图片隐写术Dlg::OnBnClickedButtonSave()
{
	UpdateData(TRUE);
	if (m_strPicturePath.GetLength() == 0){
		m_strTipsResult = TEXT("请先浏览图片并点击确定！");
		UpdateData(FALSE);
		return;
	}
	if (m_strSavePath.GetLength() == 0){
		m_strTipsResult = TEXT("请先浏览保存图片路径！");
		UpdateData(FALSE);
		return;
	}

	TCHAR path[MAX_PATH] = { 0 };
	m_edtSavePicture.GetWindowText(path, MAX_PATH);

	m_hide.saveImage(path);

	m_strTipsResult = TEXT("文件已保存");

	UpdateData(FALSE);
}


void C图片隐写术Dlg::OnBnClickedButtonClear()
{
	m_strHideDatas = TEXT("");
	UpdateData(FALSE);
}


void C图片隐写术Dlg::OnBnClickedButtonDataSize()
{
	UpdateData(TRUE);

	int needSize = 0;
	Unicode2Utf8(T2W(m_strHideDatas.GetBuffer()), NULL, &needSize);
	m_strHideDatas.ReleaseBuffer();

	m_strTipsResult.Format(TEXT("%d kb %d byte"), needSize / 1024, needSize);
	UpdateData(FALSE);
}
