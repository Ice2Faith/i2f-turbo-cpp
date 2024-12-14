
// 15-AutoRun���߹���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "15-AutoRun���߹���.h"
#include "15-AutoRun���߹���Dlg.h"
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


// CMy15AutoRun���߹���Dlg �Ի���



CMy15AutoRun���߹���Dlg::CMy15AutoRun���߹���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy15AutoRun���߹���Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy15AutoRun���߹���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DRIVES, m_combox_drives);
}

BEGIN_MESSAGE_MAP(CMy15AutoRun���߹���Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy15AutoRun���߹���Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMy15AutoRun���߹���Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_IMMUNE, &CMy15AutoRun���߹���Dlg::OnBnClickedButtonImmune)
	ON_BN_CLICKED(IDC_BUTTON_ANTIIMMUNE, &CMy15AutoRun���߹���Dlg::OnBnClickedButtonAntiimmune)
	ON_BN_CLICKED(IDC_BUTTON_CREATEDIR, &CMy15AutoRun���߹���Dlg::OnBnClickedButtonCreatedir)
	ON_BN_CLICKED(IDC_BUTTON_DELETEDIR, &CMy15AutoRun���߹���Dlg::OnBnClickedButtonDeletedir)
END_MESSAGE_MAP()


// CMy15AutoRun���߹���Dlg ��Ϣ�������

BOOL CMy15AutoRun���߹���Dlg::OnInitDialog()
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
	InitComboxDrives();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy15AutoRun���߹���Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy15AutoRun���߹���Dlg::OnPaint()
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
HCURSOR CMy15AutoRun���߹���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy15AutoRun���߹���Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CMy15AutoRun���߹���Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
//��ȡ�����б��б����
void CMy15AutoRun���߹���Dlg::InitComboxDrives()
{
	SetDlgItemText(IDC_COMBO_DRIVES, TEXT("��ѡ����̣�"));

	TCHAR drivers[MAXBYTE] = { 0 };
	GetLogicalDriveStrings(MAXBYTE, drivers);

	TCHAR * tp = drivers;
	while (*tp)
	{
		m_combox_drives.AddString(tp);
		tp += 4;
	}
}
//������ѡ��Ĵ���,�������autorun.inf�ļ������ƶ�������֮���autorun.inf�ļ���
//�������autorun.inf�ļ��У�������ɾ�����������
void CMy15AutoRun���߹���Dlg::OnBnClickedButtonImmune()
{
	//��ȡ��ѡ�����
	TCHAR drive[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_COMBO_DRIVES, drive, MAX_PATH);
	//������ʱĿ¼
	TCHAR tempDir[MAX_PATH] = { 0 };
	lstrcpy(tempDir, drive);
	lstrcat(tempDir,TEXT("temprature...\\"));
	BOOL ret = CreateDirectory(tempDir, NULL);
	if (!ret)
	{
		MessageBox(TEXT("�޷����߸Ĵ��̣���ѡ������Ƿ�ɶ�д"), TEXT("���߳���"));
		return;
	}
	//�´����������ļ���
	lstrcat(drive, TEXT("autorun.inf"));
	//�ƶ�autorun.inf�ļ�����ʱ�ļ���
	TCHAR tempAuto[MAX_PATH] = { 0 };
	lstrcpy(tempAuto, tempDir);
	lstrcat(tempAuto, TEXT("\\autorun.inf"));
	MoveFile(drive, tempAuto);
	//�����Ƴ�autorun.inf�ļ���
	RemoveDirectory(drive);
	//���������ļ���·������������
	ret = CreateDirectory(drive, NULL);
	if (!ret)
	{
		MessageBox(TEXT("�޷����߸Ĵ��̣���ѡ����̻��߼������Ƿ��Ѵ���autorun.inf�ļ����У�"), TEXT("���߳���"));
		return;
	}
	SetFileAttributes(drive, FILE_ATTRIBUTE_HIDDEN);
	//�����ݵ�Դautorun.inf�ļ��ƶ������߸�·��
	TCHAR tempTrueAuto[MAX_PATH] = { 0 };
	lstrcpy(tempTrueAuto, drive);
	lstrcat(tempTrueAuto, TEXT("\\autorun.inf"));
	MoveFile(tempAuto, tempTrueAuto);
	//ɾ����ʱĿ¼
	RemoveDirectory(tempDir);
	//����������Ŀ¼
	lstrcat(drive, TEXT("\\immune...\\"));
	ret = CreateDirectory(drive, NULL);
	if (!ret)
	{
		MessageBox(TEXT("�޷����߸Ĵ��̣���ѡ����̻��߼������Ƿ��Ѵ���immune...�ļ����У�"), TEXT("���߳���"));
		return;
	}
	MessageBox(TEXT("���߳ɹ�"), TEXT("������ʾ"));
}


void CMy15AutoRun���߹���Dlg::OnBnClickedButtonAntiimmune()
{
	//ɾ��������Ŀ¼
	TCHAR drive[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_COMBO_DRIVES, drive, MAX_PATH);
	lstrcat(drive, TEXT("autorun.inf\\immune...\\"));
	RemoveDirectory(drive);
	//ɾ�����߸�Ŀ¼
	ZeroMemory(drive, sizeof(drive));
	GetDlgItemText(IDC_COMBO_DRIVES, drive, MAX_PATH);
	lstrcat(drive, TEXT("autorun.inf"));
	RemoveDirectory(drive);
	MessageBox(TEXT("ȡ�����߳ɹ�"), TEXT("������ʾ"));
}


void CMy15AutoRun���߹���Dlg::OnBnClickedButtonCreatedir()
{
	TCHAR path[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_EDIT_DIRPATH, path, MAX_PATH);
	CreateDirectory(path, NULL);
}


void CMy15AutoRun���߹���Dlg::OnBnClickedButtonDeletedir()
{
	TCHAR path[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_EDIT_DIRPATH, path, MAX_PATH);
	RemoveDirectory(path);
}
