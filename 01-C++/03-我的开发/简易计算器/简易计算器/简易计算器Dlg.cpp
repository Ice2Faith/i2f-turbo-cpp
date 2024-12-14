
// 简易计算器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "简易计算器.h"
#include "简易计算器Dlg.h"
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



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// C简易计算器Dlg 对话框



C简易计算器Dlg::C简易计算器Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C简易计算器Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C简易计算器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C简易计算器Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REM, &C简易计算器Dlg::OnBnClickedButtonRem)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &C简易计算器Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &C简易计算器Dlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &C简易计算器Dlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &C简易计算器Dlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_MI, &C简易计算器Dlg::OnBnClickedButtonMi)
	ON_BN_CLICKED(IDC_BUTTON_MLS, &C简易计算器Dlg::OnBnClickedButtonMls)
	ON_BN_CLICKED(IDC_BUTTON_POW, &C简易计算器Dlg::OnBnClickedButtonPow)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &C简易计算器Dlg::OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &C简易计算器Dlg::OnBnClickedButtonLog)
	ON_BN_CLICKED(IDC_BUTTON_PI, &C简易计算器Dlg::OnBnClickedButtonPi)
	ON_BN_CLICKED(IDC_BUTTON_E, &C简易计算器Dlg::OnBnClickedButtonE)
	ON_BN_CLICKED(IDC_BUTTON_NUMONE, &C简易计算器Dlg::OnBnClickedButtonNumone)
	ON_BN_CLICKED(IDC_BUTTON_NUMTWE, &C简易计算器Dlg::OnBnClickedButtonNumtwe)
	ON_BN_CLICKED(IDC_BUTTON_SIN, &C简易计算器Dlg::OnBnClickedButtonSin)
	ON_BN_CLICKED(IDC_BUTTON_EXC, &C简易计算器Dlg::OnBnClickedButtonExc)
	ON_BN_CLICKED(IDC_BUTTON_COS, &C简易计算器Dlg::OnBnClickedButtonCos)
	ON_BN_CLICKED(IDC_BUTTON_TAN, &C简易计算器Dlg::OnBnClickedButtonTan)
	ON_EN_CHANGE(IDC_EDIT_SINGELIN, &C简易计算器Dlg::OnEnChangeEditSingelin)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &C简易计算器Dlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_ARCSIN, &C简易计算器Dlg::OnBnClickedButtonArcsin)
	ON_BN_CLICKED(IDC_BUTTON_ARCCOS, &C简易计算器Dlg::OnBnClickedButtonArccos)
	ON_BN_CLICKED(IDC_BUTTON_ARCTAN, &C简易计算器Dlg::OnBnClickedButtonArctan)
	ON_BN_CLICKED(IDC_BUTTON_PRESENT, &C简易计算器Dlg::OnBnClickedButtonPresent)
	ON_BN_CLICKED(IDC_BUTTON_MIADD, &C简易计算器Dlg::OnBnClickedButtonMiadd)
	ON_BN_CLICKED(IDC_BUTTON_RANDBEWTEEN, &C简易计算器Dlg::OnBnClickedButtonRandbewteen)
	ON_BN_CLICKED(IDC_BUTTON_MIMUL, &C简易计算器Dlg::OnBnClickedButtonMimul)
	ON_BN_CLICKED(IDC_BUTTON_VERT, &C简易计算器Dlg::OnBnClickedButtonVert)
	ON_BN_CLICKED(IDC_BUTTON_UPTIME, &C简易计算器Dlg::OnBnClickedButtonUptime)
	ON_BN_CLICKED(IDC_BUTTON_SURVIVE, &C简易计算器Dlg::OnBnClickedButtonSurvive)
	ON_BN_CLICKED(IDC_BUTTON1, &C简易计算器Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_EQUNEXT, &C简易计算器Dlg::OnBnClickedButtonEqunext)
	ON_BN_CLICKED(IDC_BUTTON_GOLDMATH, &C简易计算器Dlg::OnBnClickedButtonGoldmath)
	ON_BN_CLICKED(IDC_BUTTON_MATHLIGHT, &C简易计算器Dlg::OnBnClickedButtonMathlight)
	ON_BN_CLICKED(IDC_BUTTON_MATHKHINCHINK, &C简易计算器Dlg::OnBnClickedButtonMathkhinchink)
	ON_BN_CLICKED(IDC_BUTTON_MATHCONWAY, &C简易计算器Dlg::OnBnClickedButtonMathconway)
	ON_BN_CLICKED(IDC_BUTTON_HEXEXCHANGE, &C简易计算器Dlg::OnBnClickedButtonHexexchange)
	ON_BN_CLICKED(IDC_BUTTON_FILLING, &C简易计算器Dlg::OnBnClickedButtonFilling)
	ON_BN_CLICKED(IDC_BUTTON_LOCKCOMMPUTER, &C简易计算器Dlg::OnBnClickedButtonLockcommputer)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWNNOW, &C简易计算器Dlg::OnBnClickedButtonShutdownnow)
	ON_BN_CLICKED(IDC_BUTTON_REBOOTNOW, &C简易计算器Dlg::OnBnClickedButtonRebootnow)
	ON_BN_CLICKED(IDC_BUTTON_OPENCMD, &C简易计算器Dlg::OnBnClickedButtonOpencmd)
	ON_BN_CLICKED(IDC_BUTTON_OPENPOEWRSHELL, &C简易计算器Dlg::OnBnClickedButtonOpenpoewrshell)
	ON_BN_CLICKED(IDC_BUTTON_SWITCHCONTROL, &C简易计算器Dlg::OnBnClickedButtonSwitchcontrol)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWNLATER, &C简易计算器Dlg::OnBnClickedButtonShutdownlater)
	ON_BN_CLICKED(IDC_BUTTON_REBOOTLATER, &C简易计算器Dlg::OnBnClickedButtonRebootlater)
	ON_BN_CLICKED(IDC_BUTTON_CANCELPLAN, &C简易计算器Dlg::OnBnClickedButtonCancelplan)
	ON_BN_CLICKED(IDC_BUTTON_ADDFILE, &C简易计算器Dlg::OnBnClickedButtonAddfile)
	ON_BN_CLICKED(IDC_BUTTON_STARTLOCK, &C简易计算器Dlg::OnBnClickedButtonStartlock)
	ON_BN_CLICKED(IDC_BUTTON_GSTART, &C简易计算器Dlg::OnBnClickedButtonGstart)
	ON_BN_CLICKED(IDC_BUTTON_G1, &C简易计算器Dlg::OnBnClickedButtonG1)
	ON_BN_CLICKED(IDC_BUTTON_G2, &C简易计算器Dlg::OnBnClickedButtonG2)
	ON_BN_CLICKED(IDC_BUTTON_G3, &C简易计算器Dlg::OnBnClickedButtonG3)
	ON_BN_CLICKED(IDC_BUTTON_G4, &C简易计算器Dlg::OnBnClickedButtonG4)
	ON_BN_CLICKED(IDC_BUTTON_G5, &C简易计算器Dlg::OnBnClickedButtonG5)
	ON_BN_CLICKED(IDC_BUTTON_G6, &C简易计算器Dlg::OnBnClickedButtonG6)
	ON_BN_CLICKED(IDC_BUTTON_G7, &C简易计算器Dlg::OnBnClickedButtonG7)
	ON_BN_CLICKED(IDC_BUTTON_G8, &C简易计算器Dlg::OnBnClickedButtonG8)
	ON_BN_CLICKED(IDC_BUTTON_G9, &C简易计算器Dlg::OnBnClickedButtonG9)
	ON_BN_CLICKED(IDC_BUTTON_GOVER, &C简易计算器Dlg::OnBnClickedButtonGover)
	ON_BN_CLICKED(IDC_BUTTON_YAOSAIZI, &C简易计算器Dlg::OnBnClickedButtonYaosaizi)
	ON_BN_CLICKED(IDC_BUTTON_REGEDIT, &C简易计算器Dlg::OnBnClickedButtonRegedit)
	ON_BN_CLICKED(IDC_BUTTON_OPENHOST, &C简易计算器Dlg::OnBnClickedButtonOpenhost)
	ON_BN_CLICKED(IDC_BUTTON_TOBASE, &C简易计算器Dlg::OnBnClickedButtonTobase)
	ON_BN_CLICKED(IDC_BUTTON_TOSTRING, &C简易计算器Dlg::OnBnClickedButtonTostring)
	ON_BN_CLICKED(IDC_BUTTON_EXPCALCUL, &C简易计算器Dlg::OnBnClickedButtonExpcalcul)
END_MESSAGE_MAP()


// C简易计算器Dlg 消息处理程序

BOOL C简易计算器Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	OnBnClickedButtonUptime();
	// TODO:  在此添加额外的初始化代码
	CMFCEditBrowseCtrl * view = (CMFCEditBrowseCtrl *)GetDlgItem(IDC_MFCEDITBROWSE_GETFILEPATH);
	view->EnableFileBrowseButton(_T("FL|全部文件|MP3|MP4"), _T("FL files|*.FL|ALL files|*.*|Media files|*.mp3|Vedio files|*.mp4||"));
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C简易计算器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C简易计算器Dlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C简易计算器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void C简易计算器Dlg::OnBnClickedButtonRem()
{
	// TODO:  在此添加控件通知处理程序代码
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

	SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"女");
	SetDlgItemText(IDC_STATIC_SWIMAN, L"男");
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
void C简易计算器Dlg::OnOK()
{
	CString temp;
	GetDlgItemText(IDC_EDIT_RES, temp);
	if (temp.IsEmpty())
		return;
	SetDlgItemText(IDC_EDIT_NUM1, temp);
	SetDlgItemText(IDC_EDIT_NUM2, L"\0");
	SetDlgItemText(IDC_EDIT_RES, L"\0");
}


void C简易计算器Dlg::OnBnClickedButtonAdd()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_OPE, L"+");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = num1 + num2;
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C简易计算器Dlg::UpdataResultToEditBox()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_RES, cresult);
	SetDlgItemText(IDC_EDIT_OVERDISPLAY, cresult);
	OnBnClickedButtonUptime();
}

void C简易计算器Dlg::UpdataResultToEditBoxSingle()
{
	// TODO:  在此添加控件通知处理程序代码
	CString temp;
	GetDlgItemText(IDC_EDIT_SINGELIN, temp);
	if (temp.IsEmpty())
		SetDlgItemText(IDC_EDIT_SINGELIN, L"1");
	tempstring.Format(_T("%.15lf"), tempnum);
	SetDlgItemText(IDC_EDIT_TMPRES, tempstring);
	SetDlgItemText(IDC_EDIT_OVERDISPLAY, tempstring);
	OnBnClickedButtonUptime();
}


void C简易计算器Dlg::OnBnClickedButtonSub()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_OPE, L"-");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = num1 - num2;
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C简易计算器Dlg::OnBnClickedButtonMul()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_OPE, L"*");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = num1 * num2;
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C简易计算器Dlg::OnBnClickedButtonDiv()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_OPE, L"/");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = num1 / num2;
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C简易计算器Dlg::OnBnClickedButtonMi()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_OPE, L"^");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = pow(num1,num2);
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C简易计算器Dlg::OnBnClickedButtonPow()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_OPE, L"sqr");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = pow(num1, 1.0/num2);
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C简易计算器Dlg::OnBnClickedButtonMod()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_OPE, L"mod");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = (int)num1%(int)num2;
	cresult.Format(_T("%d"), (int)result);
	UpdataResultToEditBox();
}


void C简易计算器Dlg::OnBnClickedButtonLog()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_OPE, L"log");
	GetDlgItemText(IDC_EDIT_NUM1, cnum1);
	GetDlgItemText(IDC_EDIT_NUM2, cnum2);
	num1 = _ttof(cnum1);
	num2 = _ttof(cnum2);
	result = log(num2)/log(num1);
	cresult.Format(_T("%.15lf"), result);
	UpdataResultToEditBox();
}


void C简易计算器Dlg::OnBnClickedButtonPi()
{
	// TODO:  在此添加控件通知处理程序代码GetDlgItemText(IDC_EDIT_NUM3, onlycal);
	SetDlgItemText(IDC_STATIC_SINGEL, L"*π");
	tempnum = PI*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonE()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"*e");
	tempnum = MATHE*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}



void C简易计算器Dlg::OnBnClickedButtonNumone()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonNumtwe()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonExc()
{
	// TODO:  在此添加控件通知处理程序代码
	if (exc == 0)
	{
		exc = 1;
		SetDlgItemText(IDC_BUTTON_EXC, L"弧度");
	}
	else
	{
		exc = 0;
		SetDlgItemText(IDC_BUTTON_EXC, L"角度");
	}
}

void C简易计算器Dlg::OnBnClickedButtonMls()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"!");
	tempnum = _ttof(onlycal);
	double tresult = 1;
	for (int i = 1; i <= (int)tempnum; i++)
		tresult *= i;
	tempnum = tresult;
	tempstring.Format(_T("%.0lf"), tresult);
	UpdataResultToEditBoxSingle();
}

void C简易计算器Dlg::OnBnClickedButtonSin()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"sin");
	if (exc == 0)
		tempnum = sin((_ttof(onlycal) / 360.0)*(2 * PI));
	else
		tempnum = sin(_ttof(onlycal));
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}

void C简易计算器Dlg::OnBnClickedButtonCos()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"cos");
	if (exc==0)
		tempnum = cos((_ttof(onlycal) / 360.0)*(2 * PI));
	else
		tempnum = sin(_ttof(onlycal));
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonTan()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"tan");
	if (exc==0)
		tempnum = tan((_ttof(onlycal) / 360.0)*(2 * PI));
	else
		tempnum = sin(_ttof(onlycal));
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnEnChangeEditSingelin()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_SINGELIN, onlycal);
	if (!onlycal.GetLength())
	{
		onlycal = "1";
		SetDlgItemText(IDC_EDIT_SINGELIN, onlycal);
	}
}


void C简易计算器Dlg::OnBnClickedButtonHelp()
{
	// TODO:  在此添加控件通知处理程序代码
	MessageBoxA(NULL, "--冰念计算器--\n\
这是一个简单的计算器\t\t只不过功能有点多\n\
\t双目运算符向导：\n\
\t\t1.输入两个操作数（顶上）\t\t2.选择运算符\n\
\t\t3.即可得出结果\n\
\t继续计算功能：\n\
\t\t自动为您将上一次计算结果放入num1\t你可以接着进行计算\n\
\t时间刷新：\n\
\t\t1.点击time按钮刷新\t\t\t2.进行计算操作也可以刷新\n\
\t单目运算符使用向导\n\
\t\t1.输入一个操作数（中间）\t\t2.选择操作符\n\
\t\t3.选择填入num1和num2\n\
\t表达式计算器\n\
\t\t1.支持的运算符号：+ - * / ( ) ^ % S/s C/c T/t P/p ! =\n\
\t\t2.示范：\t^:2^3=8\t\t\tS/s.C/c.T/t=sin.cos.tan\n\
\t\tP/p:3.14..\t!:4!=4*3*2*1\t%:3=10*30%\tS/s.C/c.T/t:60s=sin60..\n\
\t\t3.表达式示范\n\
\t\t(3+5*2-4/2)+1=\t12\t\t3+2*5-(2*2-3)=\t12\n\
\t\t60s+60c+60t+4!+10*30%+2p=\t36.3813\n\
\t进制转换器:\n\
\t\t1.输入待转换十进制数\t\t2.输入要转换成的目标进制（2-36）\n\
\t\t3.点击转换为您转换\t\t\t4.你还可以使用填入功能填入\n\
\t时间转换器：\n\
\t\t1.输入时分秒\t\t\t2.点击转换\n\
\t\t3.得到转换结果\n\
\tBMI计算器：\n\
\t\t1.输入身高体重\t\t\t2.点击计算完成\n\
\t生辰计算器：\n\
\t\t1.输入出生日期等信息\t\t2.点击生辰按钮完成计算\n\
\t扩展实验区：\n\
\t\t1.勾选允许危险操作\t\t\t2.点击操作即可\n\
\t\t延时任务可点击转换单位秒/分/时/\t延时任务可一键取消\n\
\tBase64转换器\n\
\t\t1.在对应的栏里面输入需要转换的字符串\t2.点击右侧对应按钮进行转换\n\
\t文件加密器\n\
\t\t1.选择文件\t\t\t2.加入处理名单\n\
\t\t3.点击加密/解密按钮开始操作\t\t请耐心等待操作完成\n\
\t打地鼠游戏\n\
\t\t1.点击开始按钮开始游戏\t\t2.$按钮得分，@按钮是炸弹\n\
\t\t你可以随时自杀结束游戏\t\t如果长时间未操作会掉血\n\
--Copyright @Ice2Faith--\n", "Question(s) & Answer(s)", MB_OK);
}


void C简易计算器Dlg::OnBnClickedButtonArcsin()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"asin");
	if (exc == 0)
		tempnum = asin((_ttof(onlycal)))*180/PI;
	else
		tempnum = asin((_ttof(onlycal)))/PI;
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonArccos()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"acos");
	if (exc == 0)
		tempnum = acos((_ttof(onlycal))) * 180/PI;
	else
		tempnum = acos((_ttof(onlycal)))/PI;
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonArctan()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"atan");
	if (exc == 0)
		tempnum = atan((_ttof(onlycal))) * 180/PI;
	else
		tempnum = atan((_ttof(onlycal)))/PI;
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonPresent()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"%");
		tempnum = _ttof(onlycal)/100.0;
	tempstring.Format(_T("%.15lf"), tempnum);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonMiadd()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonRandbewteen()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonMimul()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonVert()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonUptime()
{
	// TODO:  在此添加控件通知处理程序代码
	time_t ptime = time(NULL);
	struct tm  gtime; 
	localtime_s(&gtime, &ptime);
	CString otime;
	CString week[7]= { L"日", L"一", L"二", L"三", L"四", L"五", L"六" };
	otime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d %s"), gtime.tm_year+1900,gtime.tm_mon+1,gtime.tm_mday,\
		gtime.tm_hour,gtime.tm_min,gtime.tm_sec,week[gtime.tm_wday]);
	SetDlgItemText(IDC_STATIC_PRETIME, otime);
}


void C简易计算器Dlg::OnBnClickedButtonSurvive()
{
	// TODO:  在此添加控件通知处理程序代码
	CString year, mon, day, hour,min,sec;
	int iyear, imon, iday, ihour, imin, isec; //输入时间日期
	int pyear, pmon, pday, phour,pmin,psec; //当前时间日期
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

	//开始总计算时间/秒
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

void C简易计算器Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
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
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"偏瘦");
	else if (avgbmi<24)
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"正常");
	else if (avgbmi<29)
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"超重");
	else if (avgbmi<34)
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"肥胖");
	else 
		SetDlgItemText(IDC_STATIC_SWEIWOMAN, L"超胖");

	if (avgbmi < 20)
		SetDlgItemText(IDC_STATIC_SWIMAN, L"偏瘦");
	else if (avgbmi<25)
		SetDlgItemText(IDC_STATIC_SWIMAN, L"正常");
	else if (avgbmi<30)
		SetDlgItemText(IDC_STATIC_SWIMAN, L"超重");
	else if (avgbmi<35)
		SetDlgItemText(IDC_STATIC_SWIMAN, L"肥胖");
	else
		SetDlgItemText(IDC_STATIC_SWIMAN, L"超胖");

}


void C简易计算器Dlg::OnBnClickedButtonEqunext()
{
	// TODO:  在此添加控件通知处理程序代码
	CString temp;
	GetDlgItemText(IDC_EDIT_RES, temp);
	if (temp.IsEmpty())
		return;
	SetDlgItemText(IDC_EDIT_NUM1, temp);
	SetDlgItemText(IDC_EDIT_NUM2, L"\0");
	SetDlgItemText(IDC_EDIT_RES, L"\0");
}


void C简易计算器Dlg::OnBnClickedButtonGoldmath()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"*φ");
	tempnum = MATHGOLD*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonMathlight()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"*c");
	tempnum = MATHLIGHTC*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonMathkhinchink()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"*K");
	tempnum = MATHKHINCHINK*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonMathconway()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_SINGEL, L"*λ");
	tempnum = MATHCONWAY*_ttof(onlycal);
	UpdataResultToEditBoxSingle();
}


void C简易计算器Dlg::OnBnClickedButtonHexexchange()
{
	// TODO:  在此添加控件通知处理程序代码
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

void C简易计算器Dlg::OnBnClickedButtonFilling()
{
	// TODO:  在此添加控件通知处理程序代码
	CString in, out;
	double num;
	GetDlgItemText(IDC_EDIT_OVERDISPLAY, in);
	num = _ttof(in);
	out.Format(_T("%.8lf"), num);
	SetDlgItemText(IDC_EDIT_HEXIN, out);
	OnBnClickedButtonUptime();
}


void C简易计算器Dlg::OnBnClickedButtonLockcommputer()
{
	// TODO:  在此添加控件通知处理程序代码
	if(((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
	system("rundll32 user32.dll,LockWorkStation");
	OnBnClickedButtonUptime();
}


void C简易计算器Dlg::OnBnClickedButtonShutdownnow()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
	system("shutdown /s /f /t 0");
}


void C简易计算器Dlg::OnBnClickedButtonRebootnow()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
	system("shutdown /r /f /t 0");
}


void C简易计算器Dlg::OnBnClickedButtonOpencmd()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		system("start cmd /k echo 输入\"help\"查看帮助文档");
	OnBnClickedButtonUptime();
}


void C简易计算器Dlg::OnBnClickedButtonOpenpoewrshell()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		system("start powershell");
	OnBnClickedButtonUptime();
}


void C简易计算器Dlg::OnBnClickedButtonSwitchcontrol()
{
	// TODO:  在此添加控件通知处理程序代码
	CString CBstring[3] = { L"s", L"m", L"h" };
	ControlBase = (ControlBase + 1) % 3;
	SetDlgItemText(IDC_BUTTON_SWITCHCONTROL, CBstring[ControlBase]);
	OnBnClickedButtonUptime();
}


void C简易计算器Dlg::OnBnClickedButtonShutdownlater()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonRebootlater()
{
	// TODO:  在此添加控件通知处理程序代码
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
void C简易计算器Dlg::OnBnClickedButtonRegedit()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		return;
	system("start regedit");
}


void C简易计算器Dlg::OnBnClickedButtonOpenhost()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
		return;
	system("explorer C:\\Windows\\System32\\drivers\\etc\\hosts");
}



void C简易计算器Dlg::OnBnClickedButtonCancelplan()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_CHECK_SENIOROPE))->GetCheck())
	system("shutdown -a");
	OnBnClickedButtonUptime();
}


void C简易计算器Dlg::OnBnClickedButtonAddfile()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonStartlock()
{
	// TODO:  在此添加控件通知处理程序代码
	CProgressCtrl * prog = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS_LOCK);
	CListBox * list = (CListBox*)GetDlgItem(IDC_LIST_DISPLAY);
	prog->SetRange(1, 100);
	prog->SetPos(0);
	char Key[2048] = { "01"};
	SimpleKeyCreat(Key);
	long a = time(NULL);
	list->AddString(L"请耐心等待...");
	for (int i = 0; i < countepath; i++)
	{
		FileLocker(PathBody[i], Key);
		prog->SetPos((((i+1)*1.0) / countepath) * 100);
	}
	countepath = 0;
	long b = time(NULL);
	a = b - a;
	CString temp;
	temp.Format(_T("已完成！耗时：%u s"), a);
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

void C简易计算器Dlg::OnBnClickedButtonGstart()
{
	
	// TODO:  在此添加控件通知处理程序代码
	if (!gover)
		return;
	for (int i = 0; i < 9; i++)
	{
		SetDlgItemText(suround[i], L"\0");
	}
	SetDlgItemText(IDC_BUTTON_GSTART, L"游戏中");
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

void C简易计算器Dlg::SetMoney()
{
	srand((unsigned)time(NULL) + rand());
	money = rand() % 9;
	boom = money;
	SetDlgItemText(suround[bmoney], L"\0");
	SetDlgItemText(suround[money], L"$");
	bmoney = money;
}
void C简易计算器Dlg::SetBoom()
{
	srand((unsigned)time(NULL) + rand());
	while (boom == money)
		boom = rand() % 9;
	SetDlgItemText(suround[bboom], L"\0");
	SetDlgItemText(suround[boom], L"@");
	bboom = boom;
}
void C简易计算器Dlg::CoreUpdataMore(int nID)
{
	if (gover)
	{
		SetDlgItemText(IDC_BUTTON_GSTART, L"开始");
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
void C简易计算器Dlg::OnBnClickedButtonG1()
{
	// TODO:  在此添加控件通知处理程序代码
	CoreUpdataMore(IDC_BUTTON_G1);
	
}


void C简易计算器Dlg::OnBnClickedButtonG2()
{
	// TODO:  在此添加控件通知处理程序代码
	CoreUpdataMore(IDC_BUTTON_G2);
}


void C简易计算器Dlg::OnBnClickedButtonG3()
{
	// TODO:  在此添加控件通知处理程序代码
	CoreUpdataMore(IDC_BUTTON_G3);
}


void C简易计算器Dlg::OnBnClickedButtonG4()
{
	// TODO:  在此添加控件通知处理程序代码
	CoreUpdataMore(IDC_BUTTON_G4);
}


void C简易计算器Dlg::OnBnClickedButtonG5()
{
	// TODO:  在此添加控件通知处理程序代码
	CoreUpdataMore(IDC_BUTTON_G5);
}


void C简易计算器Dlg::OnBnClickedButtonG6()
{
	// TODO:  在此添加控件通知处理程序代码
	CoreUpdataMore(IDC_BUTTON_G6);
}


void C简易计算器Dlg::OnBnClickedButtonG7()
{
	// TODO:  在此添加控件通知处理程序代码
	CoreUpdataMore(IDC_BUTTON_G7);
}


void C简易计算器Dlg::OnBnClickedButtonG8()
{
	// TODO:  在此添加控件通知处理程序代码
	CoreUpdataMore(IDC_BUTTON_G8);
}


void C简易计算器Dlg::OnBnClickedButtonG9()
{
	// TODO:  在此添加控件通知处理程序代码
	CoreUpdataMore(IDC_BUTTON_G9);
}


void C简易计算器Dlg::OnBnClickedButtonGover()
{
	// TODO:  在此添加控件通知处理程序代码
	if (gover != 0)
		return;
	glife = -1;
	gover = 1;
	SetDlgItemText(IDC_EDIT_GAMELIFE, L"-1");
	SetDlgItemText(IDC_BUTTON_GSTART, L"开始");
	OnBnClickedButtonUptime();
}


void C简易计算器Dlg::OnBnClickedButtonYaosaizi()
{
	// TODO:  在此添加控件通知处理程序代码
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
void C简易计算器Dlg::OnBnClickedButtonTobase()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonTostring()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C简易计算器Dlg::OnBnClickedButtonExpcalcul()
{
	// TODO:  在此添加控件通知处理程序代码
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
