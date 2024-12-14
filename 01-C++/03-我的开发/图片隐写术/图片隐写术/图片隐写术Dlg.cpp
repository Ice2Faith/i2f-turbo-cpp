
// ͼƬ��д��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ͼƬ��д��.h"
#include "ͼƬ��д��Dlg.h"
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


// CͼƬ��д��Dlg �Ի���



CͼƬ��д��Dlg::CͼƬ��д��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CͼƬ��д��Dlg::IDD, pParent)
	, m_strPicturePath(_T(""))
	, m_strPictureSize(_T(""))
	, m_strMaxHideByteSize(_T(""))
	, m_strHideDatas(_T(""))
	, m_strTipsResult(_T(""))
	, m_strSavePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CͼƬ��д��Dlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(CͼƬ��д��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CͼƬ��д��Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CͼƬ��д��Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_READ_HIDE_DATA, &CͼƬ��д��Dlg::OnBnClickedButtonReadHideData)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_HIDE_DATA, &CͼƬ��д��Dlg::OnBnClickedButtonWriteHideData)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CͼƬ��д��Dlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CͼƬ��д��Dlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_DATA_SIZE, &CͼƬ��д��Dlg::OnBnClickedButtonDataSize)
END_MESSAGE_MAP()


// CͼƬ��д��Dlg ��Ϣ�������

BOOL CͼƬ��д��Dlg::OnInitDialog()
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

void CͼƬ��д��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CͼƬ��д��Dlg::OnPaint()
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
HCURSOR CͼƬ��д��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CͼƬ��д��Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

void CͼƬ��д��Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	UpdateData(TRUE);

	if (m_strPicturePath.GetLength() == 0){
		m_strTipsResult = TEXT("�������ͼƬ��");
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
	m_strTipsResult = TEXT("ȷ��ͼƬ");

	UpdateData(FALSE);
}



void CͼƬ��д��Dlg::OnBnClickedButtonReadHideData()
{
	UpdateData(TRUE);

	if (m_strPicturePath.GetLength() == 0){
		m_strTipsResult = TEXT("�������ͼƬ�����ȷ����");
		UpdateData(FALSE);
		return;
	}


	int needSize = m_hide.getHideDataByteSize();
	char * udata = (char *)malloc(sizeof(char)*(needSize+1));
	memset(udata, 0, needSize + 1);
	int rdSize = m_hide.readData((unsigned char *)udata, needSize);

	if (rdSize>0){
		m_strTipsResult.Format(TEXT("�������ݳɹ�:%d kb %d byte"), needSize / 1024, needSize);
	}
	else{
		m_strTipsResult = TEXT("��������ʧ�ܣ�δ��дͼƬ����д����Ϊ0");
	}


	UpdateData(FALSE);

	SetDlgItemTextA(this->GetSafeHwnd(), IDC_EDIT_HIDE_DATA, udata);

	free(udata);
	/*
	//תΪUTF8��������룬���ã�ʹ��ASCII��GBK
	int wsize = 0;
	Utf82Unicode(udata, NULL, &wsize);
	WCHAR * wdata = (WCHAR *)malloc(sizeof(WCHAR)*(wsize + 1));
	memset(wdata, 0, sizeof(WCHAR)*(wsize + 1));
	Utf82Unicode(udata, wdata, &wsize);

	m_strHideDatas = wdata;
	free(udata);
	free(wdata);

	if (rdSize>0){
		m_strTipsResult.Format(TEXT("�������ݳɹ�:%d kb %d byte"),needSize/1024,needSize);
	}
	else{
		m_strTipsResult = TEXT("��������ʧ�ܣ�δ��дͼƬ����д����Ϊ0");
	}


	UpdateData(FALSE);
	*/
}


void CͼƬ��д��Dlg::OnBnClickedButtonWriteHideData()
{
	UpdateData(TRUE);

	if (m_strPicturePath.GetLength() == 0){
		m_strTipsResult = TEXT("�������ͼƬ�����ȷ����");
		UpdateData(FALSE);
		return;
	}

	//����1M�ռ�
	int byteSize = 1024 * 1024;
	char * maxBuf = (char *)malloc(sizeof(char)*(byteSize));
	int needSize = GetDlgItemTextA(this->GetSafeHwnd(), IDC_EDIT_HIDE_DATA, maxBuf, byteSize - 1);
	
	bool res = m_hide.writeData((unsigned char *)maxBuf, needSize + 1);
	free(maxBuf);

	if (res){
		needSize = needSize + 1;
		m_strTipsResult.Format(TEXT("��д���ݳɹ�:%d kb %d byte"), needSize / 1024, needSize);
	}
	else{
		m_strTipsResult = TEXT("��д����ʧ�ܣ�ͼƬ�ߴ粻���Ա�����д������");
	}

	UpdateData(FALSE);
	
	/*
	//תΪUTF8��������룬���ã�ʹ��ASCII��GBK
	int ssize = m_strHideDatas.GetLength() + 1;
	WCHAR * sdata = (WCHAR*)malloc(sizeof(WCHAR)*ssize);
	m_edtHideData.GetWindowTextW(sdata, ssize-1);


	int needSize = 0;
	Unicode2Utf8(sdata, NULL, &needSize);

	char * udata = (char *)malloc(sizeof(char)*(needSize + 1));
	Unicode2Utf8(sdata, udata, &needSize);

	//��д��һ���ֽڣ���Ϊ�ַ�����β����ֹ��ȡ����ʱ���������ַ�����β����
	bool res = m_hide.writeData((unsigned char *)udata, needSize+1);
	free(sdata);
	free(udata);
	
	if (res){
		needSize = needSize + 1;
		m_strTipsResult.Format(TEXT("��д���ݳɹ�:%d kb %d byte"), needSize / 1024, needSize);
	}
	else{
		m_strTipsResult = TEXT("��д����ʧ�ܣ�ͼƬ�ߴ粻���Ա�����д������");
	}

	UpdateData(FALSE);
	*/
}


void CͼƬ��д��Dlg::OnBnClickedButtonSave()
{
	UpdateData(TRUE);
	if (m_strPicturePath.GetLength() == 0){
		m_strTipsResult = TEXT("�������ͼƬ�����ȷ����");
		UpdateData(FALSE);
		return;
	}
	if (m_strSavePath.GetLength() == 0){
		m_strTipsResult = TEXT("�����������ͼƬ·����");
		UpdateData(FALSE);
		return;
	}

	TCHAR path[MAX_PATH] = { 0 };
	m_edtSavePicture.GetWindowText(path, MAX_PATH);

	m_hide.saveImage(path);

	m_strTipsResult = TEXT("�ļ��ѱ���");

	UpdateData(FALSE);
}


void CͼƬ��д��Dlg::OnBnClickedButtonClear()
{
	m_strHideDatas = TEXT("");
	UpdateData(FALSE);
}


void CͼƬ��д��Dlg::OnBnClickedButtonDataSize()
{
	UpdateData(TRUE);

	int needSize = 0;
	Unicode2Utf8(T2W(m_strHideDatas.GetBuffer()), NULL, &needSize);
	m_strHideDatas.ReleaseBuffer();

	m_strTipsResult.Format(TEXT("%d kb %d byte"), needSize / 1024, needSize);
	UpdateData(FALSE);
}
