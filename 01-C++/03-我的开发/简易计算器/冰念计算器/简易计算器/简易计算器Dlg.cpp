
// ���׼�����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���׼�����.h"
#include "���׼�����Dlg.h"
#include "afxdialogex.h"
#include <math.h>
#include <time.h>
#include <Windows.h>

///////////////////////////////////////////////////////////////
#include <stdio.h>
#include"Base64.h"
#include"CalCullator.h"
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <direct.h>
#include <io.h>
#include <process.h>
#include <afxpriv.h>
#define MAXSIZE 2048
char* FilePath[1024];
char PathBody[1024][2048] ;
int countepath = 0;
int FileLocker(char * FilePath, char * password);
void SimpleKeyCreat(char Key[]);
int GetFileBar(char * FileName, char * FileBar);
/////////////////////////////////////////////////////////////////
long beforetime;
long nowtime;
int money,bmoney;
int boom,bboom;
int core;
int glife;
int gover=1;
int suround[10] = { IDC_BUTTON_G1, IDC_BUTTON_G2, IDC_BUTTON_G3, IDC_BUTTON_G4, IDC_BUTTON_G5, IDC_BUTTON_G6, IDC_BUTTON_G7, IDC_BUTTON_G8, IDC_BUTTON_G9 };

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// C���׼�����Dlg �Ի���



C���׼�����Dlg::C���׼�����Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C���׼�����Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C���׼�����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C���׼�����Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REM, &C���׼�����Dlg::OnBnClickedButtonRem)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &C���׼�����Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &C���׼�����Dlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &C���׼�����Dlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &C���׼�����Dlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_MI, &C���׼�����Dlg::OnBnClickedButtonMi)
	ON_BN_CLICKED(IDC_BUTTON_MLS, &C���׼�����Dlg::OnBnClickedButtonMls)
	ON_BN_CLICKED(IDC_BUTTON_POW, &C���׼�����Dlg::OnBnClickedButtonPow)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &C���׼�����Dlg::OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &C���׼�����Dlg::OnBnClickedButtonLog)
	ON_BN_CLICKED(IDC_BUTTON_PI, &C���׼�����Dlg::OnBnClickedButtonPi)
	ON_BN_CLICKED(IDC_BUTTON_E, &C���׼�����Dlg::OnBnClickedButtonE)
	ON_BN_CLICKED(IDC_BUTTON_NUMONE, &C���׼�����Dlg::OnBnClickedButtonNumone)
	ON_BN_CLICKED(IDC_BUTTON_NUMTWE, &C���׼�����Dlg::OnBnClickedButtonNumtwe)
	ON_BN_CLICKED(IDC_BUTTON_SIN, &C���׼�����Dlg::OnBnClickedButtonSin)
	ON_BN_CLICKED(IDC_BUTTON_EXC, &C���׼�����Dlg::OnBnClickedButtonExc)
	ON_BN_CLICKED(IDC_BUTTON_COS, &C���׼�����Dlg::OnBnClickedButtonCos)
	ON_BN_CLICKED(IDC_BUTTON_TAN, &C���׼�����Dlg::OnBnClickedButtonTan)
	ON_EN_CHANGE(IDC_EDIT_SINGELIN, &C���׼�����Dlg::OnEnChangeEditSingelin)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &C���׼�����Dlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_ARCSIN, &C���׼�����Dlg::OnBnClickedButtonArcsin)
	ON_BN_CLICKED(IDC_BUTTON_ARCCOS, &C���׼�����Dlg::OnBnClickedButtonArccos)
	ON_BN_CLICKED(IDC_BUTTON_ARCTAN, &C���׼�����Dlg::OnBnClickedButtonArctan)
	ON_BN_CLICKED(IDC_BUTTON_PRESENT, &C���׼�����Dlg::OnBnClickedButtonPresent)
	ON_BN_CLICKED(IDC_BUTTON_MIADD, &C���׼�����Dlg::OnBnClickedButtonMiadd)
	ON_BN_CLICKED(IDC_BUTTON_RANDBEWTEEN, &C���׼�����Dlg::OnBnClickedButtonRandbewteen)
	ON_BN_CLICKED(IDC_BUTTON_MIMUL, &C���׼�����Dlg::OnBnClickedButtonMimul)
	ON_BN_CLICKED(IDC_BUTTON_VERT, &C���׼�����Dlg::OnBnClickedButtonVert)
	ON_BN_CLICKED(IDC_BUTTON_UPTIME, &C���׼�����Dlg::OnBnClickedButtonUptime)
	ON_BN_CLICKED(IDC_BUTTON_SURVIVE, &C���׼�����Dlg::OnBnClickedButtonSurvive)
	ON_BN_CLICKED(IDC_BUTTON1, &C���׼�����Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_EQUNEXT, &C���׼�����Dlg::OnBnClickedButtonEqunext)
	ON_BN_CLICKED(IDC_BUTTON_GOLDMATH, &C���׼�����Dlg::OnBnClickedButtonGoldmath)
	ON_BN_CLICKED(IDC_BUTTON_MATHLIGHT, &C���׼�����Dlg::OnBnClickedButtonMathlight)
	ON_BN_CLICKED(IDC_BUTTON_MATHKHINCHINK, &C���׼�����Dlg::OnBnClickedButtonMathkhinchink)
	ON_BN_CLICKED(IDC_BUTTON_MATHCONWAY, &C���׼�����Dlg::OnBnClickedButtonMathconway)
	ON_BN_CLICKED(IDC_BUTTON_HEXEXCHANGE, &C���׼�����Dlg::OnBnClickedButtonHexexchange)
	ON_BN_CLICKED(IDC_BUTTON_FILLING, &C���׼�����Dlg::OnBnClickedButtonFilling)
	ON_BN_CLICKED(IDC_BUTTON_LOCKCOMMPUTER, &C���׼�����Dlg::OnBnClickedButtonLockcommputer)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWNNOW, &C���׼�����Dlg::OnBnClickedButtonShutdownnow)
	ON_BN_CLICKED(IDC_BUTTON_REBOOTNOW, &C���׼�����Dlg::OnBnClickedButtonRebootnow)
	ON_BN_CLICKED(IDC_BUTTON_OPENCMD, &C���׼�����Dlg::OnBnClickedButtonOpencmd)
	ON_BN_CLICKED(IDC_BUTTON_OPENPOEWRSHELL, &C���׼�����Dlg::OnBnClickedButtonOpenpoewrshell)
	ON_BN_CLICKED(IDC_BUTTON_SWITCHCONTROL, &C���׼�����Dlg::OnBnClickedButtonSwitchcontrol)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWNLATER, &C���׼�����Dlg::OnBnClickedButtonShutdownlater)
	ON_BN_CLICKED(IDC_BUTTON_REBOOTLATER, &C���׼�����Dlg::OnBnClickedButtonRebootlater)
	ON_BN_CLICKED(IDC_BUTTON_CANCELPLAN, &C���׼�����Dlg::OnBnClickedButtonCancelplan)
	ON_BN_CLICKED(IDC_BUTTON_ADDFILE, &C���׼�����Dlg::OnBnClickedButtonAddfile)
	ON_BN_CLICKED(IDC_BUTTON_STARTLOCK, &C���׼�����Dlg::OnBnClickedButtonStartlock)
	ON_BN_CLICKED(IDC_BUTTON_GSTART, &C���׼�����Dlg::OnBnClickedButtonGstart)
	ON_BN_CLICKED(IDC_BUTTON_G1, &C���׼�����Dlg::OnBnClickedButtonG1)
	ON_BN_CLICKED(IDC_BUTTON_G2, &C���׼�����Dlg::OnBnClickedButtonG2)
	ON_BN_CLICKED(IDC_BUTTON_G3, &C���׼�����Dlg::OnBnClickedButtonG3)
	ON_BN_CLICKED(IDC_BUTTON_G4, &C���׼�����Dlg::OnBnClickedButtonG4)
	ON_BN_CLICKED(IDC_BUTTON_G5, &C���׼�����Dlg::OnBnClickedButtonG5)
	ON_BN_CLICKED(IDC_BUTTON_G6, &C���׼�����Dlg::OnBnClickedButtonG6)
	ON_BN_CLICKED(IDC_BUTTON_G7, &C���׼�����Dlg::OnBnClickedButtonG7)
	ON_BN_CLICKED(IDC_BUTTON_G8, &C���׼�����Dlg::OnBnClickedButtonG8)
	ON_BN_CLICKED(IDC_BUTTON_G9, &C���׼�����Dlg::OnBnClickedButtonG9)
	ON_BN_CLICKED(IDC_BUTTON_GOVER, &C���׼�����Dlg::OnBnClickedButtonGover)
	ON_BN_CLICKED(IDC_BUTTON_YAOSAIZI, &C���׼�����Dlg::OnBnClickedButtonYaosaizi)
	ON_BN_CLICKED(IDC_BUTTON_REGEDIT, &C���׼�����Dlg::OnBnClickedButtonRegedit)
	ON_BN_CLICKED(IDC_BUTTON_OPENHOST, &C���׼�����Dlg::OnBnClickedButtonOpenhost)
	ON_BN_CLICKED(IDC_BUTTON_TOBASE, &C���׼�����Dlg::OnBnClickedButtonTobase)
	ON_BN_CLICKED(IDC_BUTTON_TOSTRING, &C���׼�����Dlg::OnBnClickedButtonTostring)
	ON_BN_CLICKED(IDC_BUTTON_EXPCALCUL, &C���׼�����Dlg::OnBnClickedButtonExpcalcul)
END_MESSAGE_MAP()


// C���׼�����Dlg ��Ϣ�������

BOOL C���׼�����Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	OnBnClickedButtonUptime();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CMFCEditBrowseCtrl * view = (CMFCEditBrowseCtrl *)GetDlgItem(IDC_MFCEDITBROWSE_GETFILEPATH);
	view->EnableFileBrowseButton(_T("FL|ȫ���ļ�|MP3|MP4"), _T("FL files|*.FL|ALL files|*.*|Media files|*.mp3|Vedio files|*.mp4||"));
	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C���׼�����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C���׼�����Dlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C���׼�����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void C���׼�����Dlg::OnBnClickedButtonRem()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_NUM1, L"\0");
	SetDlgItemText(IDC_EDIT_NUM2, L"\0");
	SetDlgItemText(IDC_EDIT_RES, L"\0");
	SetDlgItemText(IDC_EDIT_TMPRES, L"\0");
	SetDlgItemText(IDC_EDIT_SINGELIN, L"1");
	SetDlgItemText(IDC_EDIT_HOURIN, L"\0");
	SetDlgItemText(IDC_EDIT_MINUSIN, L"\0");
	SetDlgItemText(IDC_EDIT_SECONDIN, L"\0");
	SetDlgItemText(IDC_EDIT_HOUR, L"\0");
	SetDlgItemText(IDC_EDIT_MINUES, L"\0");
	SetDlgItemText(IDC_EDIT_SECOND, L"\0");

	SetDlgItemText(IDC_EDIT_INYEAR, L"\0");
	SetDlgItemText(IDC_EDIT_INMONTH, L"\0");
	SetDlgItemText(IDC_EDIT_INDAY, L"\0");
	SetDlgItemText(IDC_EDIT_INHOUR, L"\0");
	SetDlgItemText(IDC_EDIT_INMINUS, L"\0");
	SetDlgItemText(IDC_EDIT_INSECOND, L"\0");
	SetDlgItemText(IDC_EDIT_OUTYEAR, L"\0");
	SetDlgItemText(IDC_EDIT_OUTMONTH, L"\0");
	SetDlgItemText(IDC_EDIT_OUTDAY, L"\0");
	SetDlgItemText(IDC_EDIT_OUTHOUR, L"\0");
	SetDlgItemText(IDC_EDIT_OUTMINUS, L"\0");
	SetDlgItemText(IDC_EDIT_OUTSECOND, L"\0");

	SetDlgItemText(IDC_EDIT_OLDBMI, L"\0");
	SetDlgItemText(IDC_EDIT_NEWBMI, L"\0");
	SetDlgItemText(IDC_EDIT_MENBMI, L"\0");
	SetDlgItemText(IDC_EDIT_WOMENBMI, L"\0");
	SetDlgItemText(IDC_EDIT_NORTH, L"\0");
	SetDlgItemText(IDC_EDIT_SOUTH, L"\0");
	SetDlgItemText(IDC_EDIT_INHEIGH, L"\0");
	SetDlgItemText(IDC_EDIT_INWEIGH, L"\0");

	SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"Ů");
	SetDlgItemText(IDC_STATIC_SWIMAN, L"��");
	SetDlgItemText(IDC_EDIT_SINGELIN, L"1");
	SetDlgItemText(IDC_STATIC_OPE, L"->");
	SetDlgItemText(IDC_STATIC_SINGEL, L"->");

	SetDlgItemText(IDC_EDIT_OVERDISPLAY, L"\0");
	SetDlgItemText(IDC_EDIT_HEXIN, L"\0");
	SetDlgItemText(IDC_EDIT_HEXINITEM, L"\0");
	SetDlgItemText(IDC_EDIT_HEXOUT, L"\0");
	SetDlgItemText(IDC_EDIT_HEXINISOURECE, L"\0");

	SetDlgItemText(IDC_EDIT_INTIMEBASE, L"\0");

	((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->SetCheck(0);
	CListBox * list = (CListBox*)GetDlgItem(IDC_LIST_DISPLAY);
	list->ResetContent();

	((CButton *)GetDlgItem(IDC_CHECK_OPENSORT))->SetCheck(0);
	
	SetDlgItemText(IDC_STATIC_SAIZI1, L"null");
	SetDlgItemText(IDC_STATIC_SAIZI2, L"null");
	SetDlgItemText(IDC_STATIC_SAIZI3, L"null");
	SetDlgItemText(IDC_STATIC_SAIZI4, L"null");
	SetDlgItemText(IDC_STATIC_SAIZI5, L"null");

	SetDlgItemText(IDC_EDIT_STRINGIN, L"\0");
	SetDlgItemText(IDC_EDIT_BASEIN, L"\0");

	SetDlgItemText(IDC_EDIT_EXPCALCUL, L"\0");

	OnBnClickedButtonUptime();

}
void C���׼�����Dlg::OnOK()
{
	CString temp;
	GetDlgItemText(IDC_EDIT_RES, temp);
	if (temp.IsEmpty())
		return;
	SetDlgItemText(IDC_EDIT_NUM1, temp);
	SetDlgItemText(IDC_EDIT_NUM2, L"\0");
	SetDlgItemText(IDC_EDIT_RES, L"\0");
}


void C���׼�����Dlg::OnBnClickedButtonAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"+");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = num1 + num2;
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::UpdataResultToEditBox()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_RES, cresult);
	SetDlgItemText(IDC_EDIT_OVERDISPLAY, cresult);
	OnBnClickedButtonUptime();
}

void C���׼�����Dlg::UpdataResultToEditBoxSingle()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	GetDlgItemText(IDC_EDIT_SINGELIN, temp);
	if (temp.IsEmpty())
		SetDlgItemText(IDC_EDIT_SINGELIN, L"1");
	tempstring.Format(_T("%.15lf"), tempnum);
	SetDlgItemText(IDC_EDIT_TMPRES, tempstring);
	SetDlgItemText(IDC_EDIT_OVERDISPLAY, tempstring);
	OnBnClickedButtonUptime();
}


void C���׼�����Dlg::OnBnClickedButtonSub()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"-");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = num1 - num2;
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonMul()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"*");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = num1 * num2;
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonDiv()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"/");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = num1 / num2;
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonMi()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"^");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = pow(num1,num2);
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonPow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"sqr");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = pow(num1, 1.0/num2);
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonMod()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"mod");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = (int)num1%(int)num2;
	cresult.Format(_T("%d"), (int)result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonLog()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"log");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = log(num2)/log(num1);
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonPi()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������GetDlgItemText(IDC_EDIT_NUM3, onlycal);
	SetDlgItemText(IDC_STATIC_SINGEL, L"*��");
	tempnum = PI*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonE()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"*e");
	tempnum = MATHE*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}



void C���׼�����Dlg::OnBnClickedButtonNumone()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_OVERDISPLAY, onlycal);
	if (!onlycal.GetLength())
	{
		onlycal = "1";
		SetDlgItemText(IDC_EDIT_OVERDISPLAY, onlycal);
	}
	tempnum = _ttof(onlycal);
	tempstring.Format(_T("%.15lf"), tempnum);
	SetDlgItemText(IDC_EDIT_NUM1, tempstring);
	tempstring.Empty();
}


void C���׼�����Dlg::OnBnClickedButtonNumtwe()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_OVERDISPLAY, onlycal);
	if (!onlycal.GetLength())
	{
		onlycal = "1";
		SetDlgItemText(IDC_EDIT_OVERDISPLAY, onlycal);
	}
	tempnum = _ttof(onlycal);
	tempstring.Format(_T("%.15lf"), tempnum);
	SetDlgItemText(IDC_EDIT_NUM2, tempstring);
	tempstring.Empty();
}


void C���׼�����Dlg::OnBnClickedButtonExc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (exc == 0)
	{
		exc = 1;
		SetDlgItemText(IDC_BUTTON_EXC, L"����");
	}
	else
	{
		exc = 0;
		SetDlgItemText(IDC_BUTTON_EXC, L"�Ƕ�");
	}
}

void C���׼�����Dlg::OnBnClickedButtonMls()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"!");
	tempnum = _ttof(onlycal);
	double tresult = 1;
	for (int i = 1; i <= (int)tempnum; i++)
		tresult *= i;
	tempnum = tresult;
	tempstring.Format(_T("%.0lf"), tresult);
	UpdataResultToEditBoxSingle();
}

void C���׼�����Dlg::OnBnClickedButtonSin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"sin");
	if (exc == 0)
		tempnum = sin((_ttof(onlycal) / 360.0)*(2 * PI));
	else
		tempnum = sin(_ttof(onlycal));
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}

void C���׼�����Dlg::OnBnClickedButtonCos()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"cos");
	if (exc==0)
		tempnum = cos((_ttof(onlycal) / 360.0)*(2 * PI));
	else
		tempnum = sin(_ttof(onlycal));
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonTan()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"tan");
	if (exc==0)
		tempnum = tan((_ttof(onlycal) / 360.0)*(2 * PI));
	else
		tempnum = sin(_ttof(onlycal));
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnEnChangeEditSingelin()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_SINGELIN, onlycal);
	if (!onlycal.GetLength())
	{
		onlycal = "1";
		SetDlgItemText(IDC_EDIT_SINGELIN, onlycal);
	}
}


void C���׼�����Dlg::OnBnClickedButtonHelp()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageBoxA(NULL, "--���������--\n\
����һ���򵥵ļ�����\t\tֻ���������е��\n\
\t˫Ŀ������򵼣�\n\
\t\t1.�������������������ϣ�\t\t2.ѡ�������\n\
\t\t3.���ɵó����\n\
\t�������㹦�ܣ�\n\
\t\t�Զ�Ϊ������һ�μ���������num1\t����Խ��Ž��м���\n\
\tʱ��ˢ�£�\n\
\t\t1.���time��ťˢ��\t\t\t2.���м������Ҳ����ˢ��\n\
\t��Ŀ�����ʹ����\n\
\t\t1.����һ�����������м䣩\t\t2.ѡ�������\n\
\t\t3.ѡ������num1��num2\n\
\t���ʽ������\n\
\t\t1.֧�ֵ�������ţ�+ - * / ( ) ^ % S/s C/c T/t P/p ! =\n\
\t\t2.ʾ����\t^:2^3=8\t\t\tS/s.C/c.T/t=sin.cos.tan\n\
\t\tP/p:3.14..\t!:4!=4*3*2*1\t%:3=10*30%\tS/s.C/c.T/t:60s=sin60..\n\
\t\t3.���ʽʾ��\n\
\t\t(3+5*2-4/2)+1=\t12\t\t3+2*5-(2*2-3)=\t12\n\
\t\t60s+60c+60t+4!+10*30%+2p=\t36.3813\n\
\t����ת����:\n\
\t\t1.�����ת��ʮ������\t\t2.����Ҫת���ɵ�Ŀ����ƣ�2-36��\n\
\t\t3.���ת��Ϊ��ת��\t\t\t4.�㻹����ʹ�����빦������\n\
\tʱ��ת������\n\
\t\t1.����ʱ����\t\t\t2.���ת��\n\
\t\t3.�õ�ת�����\n\
\tBMI��������\n\
\t\t1.�����������\t\t\t2.����������\n\
\t������������\n\
\t\t1.����������ڵ���Ϣ\t\t2.���������ť��ɼ���\n\
\t��չʵ������\n\
\t\t1.��ѡ����Σ�ղ���\t\t\t2.�����������\n\
\t\t��ʱ����ɵ��ת����λ��/��/ʱ/\t��ʱ�����һ��ȡ��\n\
\tBase64ת����\n\
\t\t1.�ڶ�Ӧ��������������Ҫת�����ַ���\t2.����Ҳ��Ӧ��ť����ת��\n\
\t�ļ�������\n\
\t\t1.ѡ���ļ�\t\t\t2.���봦������\n\
\t\t3.�������/���ܰ�ť��ʼ����\t\t�����ĵȴ��������\n\
\t�������Ϸ\n\
\t\t1.�����ʼ��ť��ʼ��Ϸ\t\t2.$��ť�÷֣�@��ť��ը��\n\
\t\t�������ʱ��ɱ������Ϸ\t\t�����ʱ��δ�������Ѫ\n\
--Copyright @Ice2Faith--\n", "Question(s) & Answer(s)", MB_OK);
}


void C���׼�����Dlg::OnBnClickedButtonArcsin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"asin");
	if (exc == 0)
		tempnum = asin((_ttof(onlycal)))*180/PI;
	else
		tempnum = asin((_ttof(onlycal)))/PI;
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonArccos()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"acos");
	if (exc == 0)
		tempnum = acos((_ttof(onlycal))) * 180/PI;
	else
		tempnum = acos((_ttof(onlycal)))/PI;
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonArctan()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"atan");
	if (exc == 0)
		tempnum = atan((_ttof(onlycal))) * 180/PI;
	else
		tempnum = atan((_ttof(onlycal)))/PI;
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonPresent()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"%");
		tempnum = _ttof(onlycal)/100.0;
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonMiadd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"+.+");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttoi(cnum1);
	num2 = _ttoi(cnum2);
	if (num2 < num1)
	{
		double temp;
		temp = num1;
		num1 = num2;
		num2 = temp;
		cnum1.Format(_T("%d"), num1);
		cnum2.Format(_T("%d"), num2);
		SetDlgItemText(IDC_EDIT_NUM1, cnum1);
		SetDlgItemText(IDC_EDIT_NUM2, cnum2);

	}

	result = 0;
	for (int i = num1; i <= num2; i++)
	{
		result += i;
	}
	cresult.Format(_T("%.0lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonRandbewteen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"rand");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	int num1 = _ttoi(cnum1);
	int num2 = _ttoi(cnum2);
	if (num2 < num1)
	{
		num1 = num1^num2;
		num2 = num1^num2;
		num1 = num1^num2;
		cnum1.Format(_T("%d"), num1);
		cnum2.Format(_T("%d"), num2);
		SetDlgItemText(IDC_EDIT_NUM1, cnum1);
		SetDlgItemText(IDC_EDIT_NUM2, cnum2);

	}
	srand((unsigned)time(NULL) + rand());
	result = rand() % (num2 - num1 + 1) + num1;
	cresult.Format(_T("%.0lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonMimul()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_OPE, L"*..*");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	int num1 = _ttoi(cnum1);
	int num2 = _ttoi(cnum2);
	if (num2 < num1)
	{
		num1 = num1^num2;
		num2 = num1^num2;
		num1 = num1^num2;
		cnum1.Format(_T("%d"), num1);
		cnum2.Format(_T("%d"), num2);
		SetDlgItemText(IDC_EDIT_NUM1, cnum1);
		SetDlgItemText(IDC_EDIT_NUM2, cnum2);

	}
	result = 1;
	for (int i = num1; i <= num2; i++)
		result *= i;
	cresult.Format(_T("%.0lf"), result);
	UpdataResultToEditBox();
}


void C���׼�����Dlg::OnBnClickedButtonVert()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString hour, min, sec;
	GetDlgItemText(IDC_EDIT_HOURIN, hour);
	GetDlgItemText(IDC_EDIT_MINUSIN, min);
	GetDlgItemText(IDC_EDIT_SECONDIN, sec);
	int ih, im, is;
	ih = _ttoi(hour);
	im = _ttoi(min);
	is = _ttoi(sec);
	double sum = 0,oh,om,os;
	sum = is+im*60+ih*60*60;
	oh = sum / (60 * 60);
	om = sum / 60;
	os = sum;
	hour.Format(_T("%.4lf"), oh);
	min.Format(_T("%.4lf"), om);
	sec.Format(_T("%.4lf"), os);
	SetDlgItemText(IDC_EDIT_HOUR, hour);
	SetDlgItemText(IDC_EDIT_MINUES, min);
	SetDlgItemText(IDC_EDIT_SECOND, sec);
}


void C���׼�����Dlg::OnBnClickedButtonUptime()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	time_t ptime = time(NULL);
	struct tm  gtime; 
	localtime_s(&gtime, &ptime);
	CString otime;
	CString week[7]= { L"��", L"һ", L"��", L"��", L"��", L"��", L"��" };
	otime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d %s"), gtime.tm_year+1900,gtime.tm_mon+1,gtime.tm_mday,\
		gtime.tm_hour,gtime.tm_min,gtime.tm_sec,week[gtime.tm_wday]);
	SetDlgItemText(IDC_STATIC_PRETIME, otime);
}


void C���׼�����Dlg::OnBnClickedButtonSurvive()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString year, mon, day, hour,min,sec;
	int iyear, imon, iday, ihour, imin, isec; //����ʱ������
	int pyear, pmon, pday, phour,pmin,psec; //��ǰʱ������
	time_t ptime = time(NULL);
	struct tm  gtime;
	localtime_s(&gtime, &ptime);
	pyear = gtime.tm_year+1900;
	pmon = gtime.tm_mon + 1;
	pday = gtime.tm_mday;
	phour = gtime.tm_hour;
	pmin = gtime.tm_min;
	psec = gtime.tm_sec;

	GetDlgItemText(IDC_EDIT_INYEAR, year);
	GetDlgItemText(IDC_EDIT_INMONTH, mon);
	GetDlgItemText(IDC_EDIT_INDAY, day);
	GetDlgItemText(IDC_EDIT_INHOUR, hour);
	GetDlgItemText(IDC_EDIT_INMINUS, min);
	GetDlgItemText(IDC_EDIT_INSECOND, sec);

	iyear = _ttoi(year);
	imon = _ttoi(mon);
	iday=_ttoi(day);
	ihour = _ttoi(hour);
	imin = _ttoi(min);
	isec = _ttoi(sec);

	//��ʼ�ܼ���ʱ��/��
	double isumtime = SumTimeSec(iyear, imon, iday, ihour, imin, isec);
	double psumtime = SumTimeSec(pyear, pmon, pday, phour, pmin, psec);
	double ysumtime = 0;
	for (int i = iyear; i < pyear; i++)
	{
		if (IsRunYear(i))
			ysumtime += 366;
		else
			ysumtime += 365;
	}
	ysumtime *= 24*60*60.0;
	double endsumtime = psumtime + ysumtime - isumtime;
	double oyear, omon, oday, ohour, omin, osec;
	oyear = endsumtime / (365*24.0*60*60.0);
	omon = endsumtime / (30 *24.0*60*60.0);
	oday = endsumtime / (24.0*60*60.0);
	ohour = endsumtime/(60*60.0);
	omin = endsumtime /60.0;
	osec = endsumtime;
	CString coyear, comon, coday, cohour,comin,cosec;
	coyear.Format(_T("%.3lf"), oyear);
	comon.Format(_T("%.3lf"), omon);
	coday.Format(_T("%.3lf"), oday);
	cohour.Format(_T("%.3lf"), ohour);
	comin.Format(_T("%.2lf"), omin);
	cosec.Format(_T("%.0lf"), osec);
	SetDlgItemText(IDC_EDIT_OUTYEAR, coyear);
	SetDlgItemText(IDC_EDIT_OUTMONTH, comon);
	SetDlgItemText(IDC_EDIT_OUTDAY, coday);
	SetDlgItemText(IDC_EDIT_OUTHOUR, cohour);
	SetDlgItemText(IDC_EDIT_OUTMINUS, comin);
	SetDlgItemText(IDC_EDIT_OUTSECOND, cosec);
}

void C���׼�����Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString cheigh, cweigh,coldbmi,cnewbmi,cwomanw,cmanw,cnorw,csouw;
	double heigh, weigh,oldbmi,newbmi,womanw,manw,norw,souw;
	GetDlgItemText(IDC_EDIT_INHEIGH, cheigh);
	GetDlgItemText(IDC_EDIT_INWEIGH, cweigh);
	heigh = _ttof(cheigh);
	weigh = _ttof(cweigh);
	oldbmi = weigh / (heigh*heigh);
	newbmi = (1.3*weigh) / (pow(heigh, 2.5));
	manw = (heigh * 100 - 100)*0.9;
	womanw = heigh * 100 - 105;
	norw = (heigh * 100 - 150)*0.6 + 50;
	souw = (heigh * 100 - 150)*0.6 + 48;
	coldbmi.Format(_T("%.2lf"),oldbmi );
	cnewbmi.Format(_T("%.2lf"), newbmi);
	cwomanw.Format(_T("%.2lf"), womanw);
	cmanw.Format(_T("%.2lf"), manw);
	cnorw.Format(_T("%.2lf"), norw);
	csouw.Format(_T("%.2lf"), souw);
	SetDlgItemText(IDC_EDIT_OLDBMI, coldbmi);
	SetDlgItemText(IDC_EDIT_NEWBMI, cnewbmi);
	SetDlgItemText(IDC_EDIT_MENBMI, cmanw);
	SetDlgItemText(IDC_EDIT_WOMENBMI, cwomanw);
	SetDlgItemText(IDC_EDIT_NORTH, cnorw);
	SetDlgItemText(IDC_EDIT_SOUTH, csouw);
	double avgbmi = (oldbmi + newbmi) / 2.0;
	if (avgbmi<19)
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"ƫ��");
	else if (avgbmi<24)
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"����");
	else if (avgbmi<29)
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"����");
	else if (avgbmi<34)
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"����");
	else 
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"����");

	if (avgbmi < 20)
		SetDlgItemText(IDC_STATIC_SWIMAN, L"ƫ��");
	else if (avgbmi<25)
		SetDlgItemText(IDC_STATIC_SWIMAN, L"����");
	else if (avgbmi<30)
		SetDlgItemText(IDC_STATIC_SWIMAN, L"����");
	else if (avgbmi<35)
		SetDlgItemText(IDC_STATIC_SWIMAN, L"����");
	else
		SetDlgItemText(IDC_STATIC_SWIMAN, L"����");

}


void C���׼�����Dlg::OnBnClickedButtonEqunext()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	GetDlgItemText(IDC_EDIT_RES, temp);
	if (temp.IsEmpty())
		return;
	SetDlgItemText(IDC_EDIT_NUM1, temp);
	SetDlgItemText(IDC_EDIT_NUM2, L"\0");
	SetDlgItemText(IDC_EDIT_RES, L"\0");
}


void C���׼�����Dlg::OnBnClickedButtonGoldmath()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"*��");
	tempnum = MATHGOLD*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonMathlight()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"*c");
	tempnum = MATHLIGHTC*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonMathkhinchink()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"*K");
	tempnum = MATHKHINCHINK*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonMathconway()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_SINGEL, L"*��");
	tempnum = MATHCONWAY*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C���׼�����Dlg::OnBnClickedButtonHexexchange()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString in,out,source,item;
	double num;
	int sou,oth;
	GetDlgItemText(IDC_EDIT_HEXIN, in);
	GetDlgItemText(IDC_EDIT_HEXINISOURECE, source);
	GetDlgItemText(IDC_EDIT_HEXINITEM, item);
	sou = _ttof(source);
	oth = _ttoi(item);
	if (sou<2 || sou>36)
	{
		sou = 10;
		SetDlgItemText(IDC_EDIT_HEXINISOURECE, L"10-Default");
	}
	if (oth<2 || oth>36)
	{
		oth = 16;
		SetDlgItemText(IDC_EDIT_HEXINITEM, L"16-Default");
	}
	num = Oth2OTC(in, sou);
	OTC2Other(num, oth, out);
	
	//out.Format(_T("%lf"), num);
	SetDlgItemText(IDC_EDIT_HEXOUT, out);
	OnBnClickedButtonUptime();
}

void C���׼�����Dlg::OnBnClickedButtonFilling()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString in, out;
	double num;
	GetDlgItemText(IDC_EDIT_OVERDISPLAY, in);
	num = _ttof(in);
	out.Format(_T("%.8lf"), num);
	SetDlgItemText(IDC_EDIT_HEXIN, out);
	OnBnClickedButtonUptime();
}


void C���׼�����Dlg::OnBnClickedButtonLockcommputer()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if(((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
	system("rundll32 user32.dll,LockWorkStation");
	OnBnClickedButtonUptime();
}


void C���׼�����Dlg::OnBnClickedButtonShutdownnow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
	system("shutdown /s /f /t 0");
}


void C���׼�����Dlg::OnBnClickedButtonRebootnow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
	system("shutdown /r /f /t 0");
}


void C���׼�����Dlg::OnBnClickedButtonOpencmd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		system("start cmd /k echo ����\"help\"�鿴�����ĵ�");
	OnBnClickedButtonUptime();
}


void C���׼�����Dlg::OnBnClickedButtonOpenpoewrshell()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		system("start powershell");
	OnBnClickedButtonUptime();
}


void C���׼�����Dlg::OnBnClickedButtonSwitchcontrol()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString CBstring[3] = { L"s", L"m", L"h" };
	ControlBase = (ControlBase + 1) % 3;
	SetDlgItemText(IDC_BUTTON_SWITCHCONTROL, CBstring[ControlBase]);
	OnBnClickedButtonUptime();
}


void C���׼�����Dlg::OnBnClickedButtonShutdownlater()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		return;
	char mind[40] = {0};
	int time;
	CString temp;
	GetDlgItemText(IDC_EDIT_INTIMEBASE, temp);
	time = _ttoi(temp);
	if (temp.IsEmpty())
		return;
		
	switch (ControlBase)
	{
	case 0:
		time *= 1;
		break;
	case 1:
		time *= 60;
		break;
	case 2:
		time *= 60 * 60;
		break;
	}
	sprintf_s(mind, "shutdown -s -f -t %d\0", time);
	system(mind);
	OnBnClickedButtonUptime();

}


void C���׼�����Dlg::OnBnClickedButtonRebootlater()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		return;
	char mind[40] = { 0 };
	int time;
	CString temp;
	GetDlgItemText(IDC_EDIT_INTIMEBASE, temp);
	time = _ttoi(temp);
	if (temp.IsEmpty())
		return;

	switch (ControlBase)
	{
	case 0:
		time *= 1;
		break;
	case 1:
		time *= 60;
		break;
	case 2:
		time *= 60 * 60;
		break;
	}
	sprintf_s(mind, "shutdown -r -f -t %d\0", time);
	system(mind);
	OnBnClickedButtonUptime();
}
void C���׼�����Dlg::OnBnClickedButtonRegedit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		return;
	system("start regedit");
}


void C���׼�����Dlg::OnBnClickedButtonOpenhost()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		return;
	system("explorer C:\\Windows\\System32\\drivers\\etc\\hosts");
}



void C���׼�����Dlg::OnBnClickedButtonCancelplan()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
	system("shutdown -a");
	OnBnClickedButtonUptime();
}


void C���׼�����Dlg::OnBnClickedButtonAddfile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	GetDlgItemText(IDC_MFCEDITBROWSE_GETFILEPATH, temp);
	if (temp.IsEmpty())
		return;
	CListBox * list=(CListBox*)GetDlgItem(IDC_LIST_DISPLAY);
	list->AddString(temp);
	USES_CONVERSION;
	FilePath[countepath++] = T2A(temp);
	strcpy_s(PathBody[countepath-1], FilePath[countepath - 1]);
	SetDlgItemText(IDC_MFCEDITBROWSE_GETFILEPATH, L"\0");
	OnBnClickedButtonUptime();
}


void C���׼�����Dlg::OnBnClickedButtonStartlock()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CProgressCtrl * prog = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS_LOCK);
	CListBox * list = (CListBox*)GetDlgItem(IDC_LIST_DISPLAY);
	prog->SetRange(1, 100);
	prog->SetPos(0);
	char Key[2048] = { "01"};
	SimpleKeyCreat(Key);
	long a = time(NULL);
	list->AddString(L"�����ĵȴ�...");
	for (int i = 0; i < countepath; i++)
	{
		FileLocker(PathBody[i], Key);
		prog->SetPos((((i+1)*1.0) / countepath) * 100);
	}
	countepath = 0;
	long b = time(NULL);
	a = b - a;
	CString temp;
	temp.Format(_T("����ɣ���ʱ��%u s"), a);
	list->AddString(temp);
	OnBnClickedButtonUptime();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SimpleKeyCreat(char Key[])
{
	double DAKey = 0, DBKey = 0, DCKey = 0, DFKey = 0;
	char CAKey[50] = { 0 };
	char CBKey[50] = { 0 };
	char CCKey[50] = { 0 };
	char CDKey[1024] = { "this is a simple test string! look at no any waring.\0" };
	char CEKey[1024] = { "my frist windows visual application,maybe have much bugs not found.\0" };
	char CFKey[50] = { 0 };
	DAKey = 3.14159265358979323846 * 11;
	DBKey = 2.718281828459 * 13;
	DCKey = 0.6180339887498948 * 17;
	DFKey = 1234.567891011 * 19;
	sprintf_s(CAKey, "%.11lf\0", DAKey);
	sprintf_s(CBKey, "%.13lf\0", DBKey);
	sprintf_s(CCKey, "%.17lf\0", DCKey);
	sprintf_s(CFKey, "%.10lf\0", DFKey);
	int AE = 0, BE = 0, CE = 0, DE = 0, EE = 0, FE = 0;
	int i = 0, j = 0;
	while (CAKey[j] || CBKey[j] || CCKey[j] || CDKey[j] || CEKey[j] || CFKey[j])
	{
		if (CAKey[j] && !AE)
			Key[i++] = CAKey[j];
		if (CBKey[j] && !BE)
			Key[i++] = CBKey[j];
		if (CCKey[j] && !CE)
			Key[i++] = CCKey[j];
		if (CDKey[j] && !DE)
			Key[i++] = CDKey[j];
		if (CEKey[j] && !EE)
			Key[i++] = CEKey[j];
		if (CFKey[j] && !FE)
			Key[i++] = CFKey[j];
		j++;
		if (!CAKey[j])
			AE = 1;
		if (!CBKey[j])
			BE = 1;
		if (!CCKey[j])
			CE = 1;
		if (!CDKey[j])
			DE = 1;
		if (!CEKey[j])
			EE = 1;
		if (!CFKey[j])
			FE = 1;

	}
	Key[i] = '\0';
}
int FileLocker(char * FilePath, char * password)
{
	FILE * Soure, *Lock;
	Soure = NULL;
	Lock = NULL;
	char Key[MAXSIZE] = { "\0" };
	char PreWorkDir[MAXSIZE] = { 0 };
	strcpy_s(PreWorkDir, FilePath);
	strcat_s(PreWorkDir, ".tmp\0");

	fopen_s(&Soure, FilePath, "rb");
	fopen_s(&Lock, PreWorkDir, "wb");

	int KeyLen = 0;
	strcpy_s(Key, password);
	KeyLen = strlen(Key);

	char * temp = NULL;
	temp = (char *)malloc(sizeof(char));
	int counter = 0;
	while (!feof(Soure))
	{
		if (fread(temp, sizeof(char), 1, Soure) == 0)
			break;
		*temp ^= (char)(Key[counter%KeyLen]);
		fwrite(temp, sizeof(char), 1, Lock);
		counter = (counter++) % KeyLen;
	}
	fclose(Soure);
	fclose(Lock);

	remove(FilePath);
	rename(PreWorkDir, FilePath);
	char FileBar[20] = { 0 };
	int space = GetFileBar(FilePath, FileBar);
	char NewFileName[4096] = { 0 };
	strcpy_s(NewFileName, FilePath);
	printf("Bar:%s\n", FileBar);
	if (strcmp(FileBar, ".FL") == 0)
	{
		NewFileName[space] = '\0';
		rename(FilePath, NewFileName);
	}
	else
	{
		strcat_s(NewFileName, ".FL\0");
		rename(FilePath, NewFileName);
	}
	return 1;
}
int GetFileBar(char * FileName, char * FileBar)
{
	char name[4096] = { 0 };
	strcpy_s(name, FileName);
	int ret = -1;
	int end = 0;
	while (*(FileName + end))
		end++;
	int dona = end;
	while (*(FileName + dona) != '.'&&*(FileName + dona) != '\\')
		dona--;
	if (*(FileName + dona) == '.')
	{
		ret = dona;
		end = 0;
		while (*(FileName + dona))
		{
			*(FileBar + end) = *(FileName + dona);
			end++;
			dona++;
		}
		*(FileBar + end) = '\0';
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void C���׼�����Dlg::OnBnClickedButtonGstart()
{
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!gover)
		return;
	for (int i = 0; i < 9; i++)
	{
		SetDlgItemText(suround[i], L"\0");
	}
	SetDlgItemText(IDC_BUTTON_GSTART, L"��Ϸ��");
	beforetime = time(NULL);
	nowtime = beforetime;
	core = 0;
	glife = 100;
	gover = 0;
	bboom = 0;
	bmoney = 0;
	SetMoney();
	SetBoom();
	CString temp;
	temp.Format(_T("%d"), core);
	SetDlgItemText(IDC_EDIT_GAMECORE, temp);
	temp.Format(_T("%d"), glife);
	SetDlgItemText(IDC_EDIT_GAMELIFE, temp);
	OnBnClickedButtonUptime();
}

void C���׼�����Dlg::SetMoney()
{
	srand((unsigned)time(NULL) + rand());
	money = rand() % 9;
	boom = money;
	SetDlgItemText(suround[bmoney], L"\0");
	SetDlgItemText(suround[money], L"$");
	bmoney = money;
}
void C���׼�����Dlg::SetBoom()
{
	srand((unsigned)time(NULL) + rand());
	while (boom == money)
		boom = rand() % 9;
	SetDlgItemText(suround[bboom], L"\0");
	SetDlgItemText(suround[boom], L"@");
	bboom = boom;
}
void C���׼�����Dlg::CoreUpdataMore(int nID)
{
	if (gover)
	{
		SetDlgItemText(IDC_BUTTON_GSTART, L"��ʼ");
		return;
	}
		
	nowtime = time(NULL);
	if (nowtime - beforetime > 5)
		glife--;
	if (nID == suround[money])
	{
		core++;
	}
	else
	if (nID == suround[boom])
	{
		glife -= 3;
	}
	else
	{
		glife--;
	}
	if (glife<0)
		gover = 1;
	SetMoney();
	SetBoom();
	CString temp;
	temp.Format(_T("%d"), core);
	SetDlgItemText(IDC_EDIT_GAMECORE, temp);
	temp.Format(_T("%d"), glife);
	SetDlgItemText(IDC_EDIT_GAMELIFE, temp);
	beforetime = nowtime;
	OnBnClickedButtonUptime();
}
void C���׼�����Dlg::OnBnClickedButtonG1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CoreUpdataMore(IDC_BUTTON_G1);
	
}


void C���׼�����Dlg::OnBnClickedButtonG2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CoreUpdataMore(IDC_BUTTON_G2);
}


void C���׼�����Dlg::OnBnClickedButtonG3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CoreUpdataMore(IDC_BUTTON_G3);
}


void C���׼�����Dlg::OnBnClickedButtonG4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CoreUpdataMore(IDC_BUTTON_G4);
}


void C���׼�����Dlg::OnBnClickedButtonG5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CoreUpdataMore(IDC_BUTTON_G5);
}


void C���׼�����Dlg::OnBnClickedButtonG6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CoreUpdataMore(IDC_BUTTON_G6);
}


void C���׼�����Dlg::OnBnClickedButtonG7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CoreUpdataMore(IDC_BUTTON_G7);
}


void C���׼�����Dlg::OnBnClickedButtonG8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CoreUpdataMore(IDC_BUTTON_G8);
}


void C���׼�����Dlg::OnBnClickedButtonG9()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CoreUpdataMore(IDC_BUTTON_G9);
}


void C���׼�����Dlg::OnBnClickedButtonGover()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (gover != 0)
		return;
	glife = -1;
	gover = 1;
	SetDlgItemText(IDC_EDIT_GAMELIFE, L"-1");
	SetDlgItemText(IDC_BUTTON_GSTART, L"��ʼ");
	OnBnClickedButtonUptime();
}


void C���׼�����Dlg::OnBnClickedButtonYaosaizi()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	srand((unsigned)time(NULL) + rand());
	int saizi[5] = { 0 };
	int butt[5] = { IDC_STATIC_SAIZI1,IDC_STATIC_SAIZI2,IDC_STATIC_SAIZI3,IDC_STATIC_SAIZI4,IDC_STATIC_SAIZI5 };
	for (int i = 0; i < 5; i++)
	{
		srand((unsigned)time(NULL) + rand());
		saizi[i] = rand() % 6 + 1;
	}
		
	if (((CButton *)GetDlgItem(IDC_CHECK_OPENSORT))->GetCheck())
	{
		for (int i = 0,tempn,swap; i < 5; i++)
		{
			swap = 0;
			for (int j = 0; j < 5-1; j++)
			{
				if (saizi[j] > saizi[j+1])
				{
					tempn = saizi[j];
					saizi[j] = saizi[j + 1];
					saizi[j + 1] = tempn;
					swap = 1;
				}
			}
			if (!swap)
				break;
		}
	}
	CString temp;
	for (int i = 0; i < 5; i++)
	{
		temp.Format(_T("%d"), saizi[i]);
		SetDlgItemText(butt[i],temp);
	}
	OnBnClickedButtonUptime();
}

void Wchar_t2Char(wchar_t Wchar[], char Char[])
{
	int size = WideCharToMultiByte(CP_ACP, 0, Wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Wchar, -1, Char, size, NULL, NULL);
}
void Char2Wchar_t(char Char[], wchar_t Wchar[])
{
	int size = MultiByteToWideChar(CP_ACP, 0, Char, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, Char, -1, Wchar, size);
}
void C���׼�����Dlg::OnBnClickedButtonTobase()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString StringIn;
	GetDlgItemText(IDC_EDIT_STRINGIN, StringIn);
	wchar_t temp[1024] = { 0 };
	char str[1024] = { 0 };
	char base64[1024 * 4 / 3] = { 0 };
	StrCpyW(temp, StringIn.GetString());

	//wchar_t to char
	Wchar_t2Char(temp,str);

	Base64(str, base64, sizeof(base64), BASE_NORMAL_STR);

	//char to wchar_t
	Char2Wchar_t(base64,temp);

	StringIn.SetString(temp);

	SetDlgItemText(IDC_EDIT_BASEIN, StringIn);
}


void C���׼�����Dlg::OnBnClickedButtonTostring()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString BaseIn;
	GetDlgItemText(IDC_EDIT_BASEIN, BaseIn);
	wchar_t temp[1024] = { 0 };
	char str[1024] = { 0 };
	char base64[1024 * 4 / 3] = { 0 };
	StrCpyW(temp, BaseIn.GetString());

	//wchar_t to char
	Wchar_t2Char(temp, base64);

	Anti_Base64(base64,str,  sizeof(str), BASE_NORMAL_STR);

	//char to wchar_t
	Char2Wchar_t(str, temp);

	BaseIn.SetString(temp);

	SetDlgItemText(IDC_EDIT_STRINGIN, BaseIn);
}


void C���׼�����Dlg::OnBnClickedButtonExpcalcul()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	GetDlgItemText(IDC_EDIT_EXPCALCUL, temp);
	wchar_t Wread[1024] = {0};
	StrCpyW(Wread, temp.GetString());
	char calculstring[1024] = { 0 };
	Wchar_t2Char(Wread, calculstring);
	calculstring[strlen(calculstring) ] = '=';
	calculstring[strlen(calculstring)+1] = '\0';
	double result = 0;
	Calculator calor;
	calor.CalculateMain(calculstring,&result);
	temp.Format(L"%.10lf",result);
	SetDlgItemText(IDC_EDIT_OVERDISPLAY, temp);
}
