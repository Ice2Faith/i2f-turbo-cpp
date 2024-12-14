
// �Զ���ֽ�л�Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�Զ���ֽ�л�.h"
#include "�Զ���ֽ�л�Dlg.h"
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


// C�Զ���ֽ�л�Dlg �Ի���



C�Զ���ֽ�л�Dlg::C�Զ���ֽ�л�Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�Զ���ֽ�л�Dlg::IDD, pParent)
	, m_WPStyle(0)
	, m_WPWaitTime(0)
	, m_isLoadFile(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C�Զ���ֽ�л�Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_PICDIR, m_EBPicView);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_CBWPStyle);
	DDX_Control(pDX, IDC_COMBO_TWAIT, m_CBWTime);
	DDX_Control(pDX, IDC_CHECK_BANPOWER, m_CBBanPower);
	DDX_Control(pDX, IDC_LIST1, m_LBImgList);
}

BEGIN_MESSAGE_MAP(C�Զ���ֽ�л�Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C�Զ���ֽ�л�Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_BANPOWER, &C�Զ���ֽ�л�Dlg::OnBnClickedCheckBanpower)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// C�Զ���ֽ�л�Dlg ��Ϣ�������

BOOL C�Զ���ֽ�л�Dlg::OnInitDialog()
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
	srand((unsigned int)time(NULL));
	this->m_CBWPStyle.AddString(L"ƽ��");
	this->m_CBWPStyle.AddString(L"����");
	this->m_CBWPStyle.AddString(L"����");
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C�Զ���ֽ�л�Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C�Զ���ֽ�л�Dlg::OnPaint()
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
HCURSOR C�Զ���ֽ�л�Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C�Զ���ֽ�л�Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void C�Զ���ֽ�л�Dlg::OnBnClickedCheckBanpower()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
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
		MessageBox(L"Ŀ¼û��ѡ���Ŀ¼�²�����ͼƬ�ļ�png|jpg|bmp",L"���ô���",MB_OK);
	}
}
bool C�Զ���ֽ�л�Dlg::ProcessFile(TCHAR * file)
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
bool C�Զ���ֽ�л�Dlg::LoadImgFilesInfo(TCHAR * dir)
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
			//�Ƿ����ļ���
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
void C�Զ���ֽ�л�Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
BOOL C�Զ���ֽ�л�Dlg::SetWallpaper(WCHAR * strPicFile, DWORD dwStyle)
{
	HRESULT hr;
	IActiveDesktop * pIAD;
	CoInitialize(NULL);
	//�����ӿڵ�ʵ��
	hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER, IID_IActiveDesktop, (void**)&pIAD);
	if (!SUCCEEDED(hr)) return FALSE;
	//����ǽֽ
	hr = pIAD->SetWallpaper(strPicFile, 0);
	if (!SUCCEEDED(hr)) return FALSE;
	//����ǽֽ��ʽ
	WALLPAPEROPT wpo;
	wpo.dwSize = sizeof(wpo);
	wpo.dwStyle = dwStyle;
	hr = pIAD->SetWallpaperOptions(&wpo, 0);
	if (!SUCCEEDED(hr)) return FALSE;
	//Ӧ��ǽֽ
	hr = pIAD->ApplyChanges(AD_APPLY_ALL);
	if (!SUCCEEDED(hr)) return FALSE;
	//�ͷŽӿڵ�ʵ��
	pIAD->Release();
	CoUninitialize();
	return TRUE;
}