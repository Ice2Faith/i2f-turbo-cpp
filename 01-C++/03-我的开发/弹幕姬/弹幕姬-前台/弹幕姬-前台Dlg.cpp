
// ��Ļ��-ǰ̨Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��Ļ��-ǰ̨.h"
#include "��Ļ��-ǰ̨Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include"FooTextMsg.h"

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


// C��Ļ��ǰ̨Dlg �Ի���



C��Ļ��ǰ̨Dlg::C��Ļ��ǰ̨Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C��Ļ��ǰ̨Dlg::IDD, pParent)
	, m_strFoText(_T(""))
	, m_bRandomSize(FALSE)
	, m_bRandomColor(FALSE)
	, m_bRandomSpeed(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C��Ļ��ǰ̨Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IN_FOTEXT, m_strFoText);
	DDX_Control(pDX, IDC_BUTTON_SHOOT_FT, m_btnShoot);
	DDX_Control(pDX, IDC_EDIT_IN_FOTEXT, m_edt_inMsg);
	DDX_Control(pDX, IDC_BUTTON_OPENMSG, m_btnOpenMsg);
	DDX_Control(pDX, IDC_BUTTON_CLOSEMSG, m_btnCloseMsg);
	DDX_Control(pDX, IDC_BUTTON_CLEARMSG, m_btnClearMsg);
	DDX_Control(pDX, IDC_BUTTON_SHOWMSGWND, m_btnShowMsgWnd);
	DDX_Control(pDX, IDC_BUTTON_HIDEMSGWND, m_btnHideMsgWnd);
	DDX_Check(pDX, IDC_CHECK_RANDOMSIZE, m_bRandomSize);
	DDX_Check(pDX, IDC_CHECK_RANDOMCOLOR, m_bRandomColor);
	DDX_Check(pDX, IDC_CHECK_RANDOMSPEED, m_bRandomSpeed);
	DDX_Control(pDX, IDC_SLIDER_SIZE, m_scSize);
	DDX_Control(pDX, IDC_SLIDER_CRED, m_scCRed);
	DDX_Control(pDX, IDC_SLIDER_CGREEN, m_scCGreen);
	DDX_Control(pDX, IDC_SLIDER_CBLUE, m_scCBlue);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_scSpeed);
}

BEGIN_MESSAGE_MAP(C��Ļ��ǰ̨Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C��Ļ��ǰ̨Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SHOOT_FT, &C��Ļ��ǰ̨Dlg::OnBnClickedButtonShootFt)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON_EXITBGSERVICE, &C��Ļ��ǰ̨Dlg::OnBnClickedButtonExitbgservice)
	ON_BN_CLICKED(IDC_BUTTON_OPENMSG, &C��Ļ��ǰ̨Dlg::OnBnClickedButtonOpenmsg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEMSG, &C��Ļ��ǰ̨Dlg::OnBnClickedButtonClosemsg)
	ON_BN_CLICKED(IDC_BUTTON_CLEARMSG, &C��Ļ��ǰ̨Dlg::OnBnClickedButtonClearmsg)
	ON_BN_CLICKED(IDC_BUTTON_SHOWMSGWND, &C��Ļ��ǰ̨Dlg::OnBnClickedButtonShowmsgwnd)
	ON_BN_CLICKED(IDC_BUTTON_HIDEMSGWND, &C��Ļ��ǰ̨Dlg::OnBnClickedButtonHidemsgwnd)
	ON_BN_CLICKED(IDC_CHECK_RANDOMSIZE, &C��Ļ��ǰ̨Dlg::OnBnClickedCheckRandomsize)
	ON_BN_CLICKED(IDC_CHECK_RANDOMCOLOR, &C��Ļ��ǰ̨Dlg::OnBnClickedCheckRandomcolor)
	ON_BN_CLICKED(IDC_CHECK_RANDOMSPEED, &C��Ļ��ǰ̨Dlg::OnBnClickedCheckRandomspeed)
END_MESSAGE_MAP()


// C��Ļ��ǰ̨Dlg ��Ϣ�������

BOOL C��Ļ��ǰ̨Dlg::OnInitDialog()
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
	this->m_scSize.SetRange(2,150,TRUE);
	this->m_scSize.SetPos(35);
	this->m_scSpeed.SetRange(1,80);
	this->m_scSpeed.SetPos(5);
	this->m_scCRed.SetRange(0,255);
	this->m_scCRed.SetPos(200);
	this->m_scCGreen.SetRange(0,255);
	this->m_scCGreen.SetPos(80);
	this->m_scCBlue.SetRange(0,255);
	this->m_scCBlue.SetPos(120);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C��Ļ��ǰ̨Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C��Ļ��ǰ̨Dlg::OnPaint()
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
HCURSOR C��Ļ��ǰ̨Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C��Ļ��ǰ̨Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void C��Ļ��ǰ̨Dlg::OnBnClickedButtonShootFt()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strFoText.GetLength() > 0)
	{
		HWND hWnd = 0;
		hWnd=::FindWindow(L"FooTextServiceClass", NULL);
		if (hWnd)
		{
			MsgBody mb = { 0 };
			lstrcpy(mb.text,m_strFoText.GetBuffer());
			if (this->m_bRandomSize==FALSE)
				mb.size = this->m_scSize.GetPos();
			else
				mb.size = rand() % 150 + 2;
			if (this->m_bRandomSpeed == FALSE)
				mb.speed = this->m_scSpeed.GetPos();
			else
				mb.speed = rand() % 80 + 1;
			int cr=0, cg=0, cb=0;
			if (this->m_bRandomColor == FALSE)
			{
				cr = this->m_scCRed.GetPos();
				cg = this->m_scCGreen.GetPos();
				cb = this->m_scCBlue.GetPos();
			}
			else
			{
				cr = rand() % 255;
				cg = rand() % 255;
				cb = rand() % 255;
			}
			mb.color = RGB(cr,cg,cb);
			COPYDATASTRUCT cdata;
			cdata.dwData = WM_TFM_ADDTEXT;
			cdata.cbData = sizeof(MsgBody);
			cdata.lpData = (LPVOID)&mb;
			::SendMessage(hWnd,WM_COPYDATA ,0,(LPARAM)(LPVOID)&cdata);
			m_strFoText.Empty();
			UpdateData(FALSE);
		}
		else
		{
			MessageBox(L"��Ļ��-��̨ ����û��������Ŷ����");
		}
	}
	else
	{
		MessageBox(L"��ǰ��û��������Ϣ�أ���");
	}
}



BOOL C��Ļ��ǰ̨Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->hwnd == m_edt_inMsg.GetSafeHwnd())
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_RETURN)
			{
				OnBnClickedButtonShootFt();
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void C��Ļ��ǰ̨Dlg::OnBnClickedButtonExitbgservice()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_CLOSE, 0, 0);
		
	}
	else
	{
		MessageBox(L"��Ļ��-��̨ ����û��������Ŷ����");
	}
}


void C��Ļ��ǰ̨Dlg::OnBnClickedButtonOpenmsg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_OPEN, 0, 0);

	}
	else
	{
		MessageBox(L"��Ļ��-��̨ ����û��������Ŷ����");
	}
}


void C��Ļ��ǰ̨Dlg::OnBnClickedButtonClosemsg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_CLOSE, 0, 0);

	}
	else
	{
		MessageBox(L"��Ļ��-��̨ ����û��������Ŷ����");
	}
}


void C��Ļ��ǰ̨Dlg::OnBnClickedButtonClearmsg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_CLEAR, 0, 0);

	}
	else
	{
		MessageBox(L"��Ļ��-��̨ ����û��������Ŷ����");
	}
}


void C��Ļ��ǰ̨Dlg::OnBnClickedButtonShowmsgwnd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_SHOW, 0, 0);

	}
	else
	{
		MessageBox(L"��Ļ��-��̨ ����û��������Ŷ����");
	}
}


void C��Ļ��ǰ̨Dlg::OnBnClickedButtonHidemsgwnd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_HIDE, 0, 0);

	}
	else
	{
		MessageBox(L"��Ļ��-��̨ ����û��������Ŷ����");
	}
}


void C��Ļ��ǰ̨Dlg::OnBnClickedCheckRandomsize()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (this->m_bRandomSize == FALSE)
	{
		this->m_scSize.EnableWindow(TRUE);
	}
	else
	{
		this->m_scSize.EnableWindow(FALSE);
	}
}


void C��Ļ��ǰ̨Dlg::OnBnClickedCheckRandomcolor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (this->m_bRandomColor == FALSE)
	{
		this->m_scCRed.EnableWindow(TRUE);
		this->m_scCGreen.EnableWindow(TRUE);
		this->m_scCBlue.EnableWindow(TRUE);
	}
	else
	{
		this->m_scCRed.EnableWindow(FALSE);
		this->m_scCGreen.EnableWindow(FALSE);
		this->m_scCBlue.EnableWindow(FALSE);
	}
}


void C��Ļ��ǰ̨Dlg::OnBnClickedCheckRandomspeed()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (this->m_bRandomSpeed == FALSE)
	{
		this->m_scSpeed.EnableWindow(TRUE);
	}
	else
	{
		this->m_scSpeed.EnableWindow(FALSE);
	}
}
