
// PgmAsisDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PgmAsis.h"
#include "PgmAsisDlg.h"
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


// CPgmAsisDlg 对话框



CPgmAsisDlg::CPgmAsisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPgmAsisDlg::IDD, pParent)
	, m_str_input(_T(""))
	, m_str_output(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPgmAsisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_str_input);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_str_output);
}

BEGIN_MESSAGE_MAP(CPgmAsisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPgmAsisDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPgmAsisDlg::OnBnClickedCancel)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_DOIT, &CPgmAsisDlg::OnBnClickedButtonDoit)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CPgmAsisDlg::OnBnClickedButtonClean)
END_MESSAGE_MAP()


// CPgmAsisDlg 消息处理程序

BOOL CPgmAsisDlg::OnInitDialog()
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

void CPgmAsisDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPgmAsisDlg::OnPaint()
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
HCURSOR CPgmAsisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPgmAsisDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CPgmAsisDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CPgmAsisDlg::InitControls()
{

	((CButton *)GetDlgItem(IDC_RADIO_PGMINTEXT))->SetCheck(TRUE);
}

void CPgmAsisDlg::OnDropFiles(HDROP hDropInfo)
{
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	for (int i = 0; i< DropCount; i++)
	{
		WCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);
		m_str_input += TEXT("\r\n");
		m_str_input += wcStr;
	}
	DragFinish(hDropInfo);

	UpdateData(FALSE);
	CDialogEx::OnDropFiles(hDropInfo);
}


void CPgmAsisDlg::OnBnClickedButtonDoit()
{
	UpdateData(TRUE);

	if (((CButton *)GetDlgItem(IDC_RADIO_CHEADER))->GetCheck())
	{
		makeCHeader();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_PGMINPATH))->GetCheck())
	{
		makeInPath();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_PGMOUTPATH))->GetCheck())
	{
		makeOutPath();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_PGMINTEXT))->GetCheck())
	{
		makeInText();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_PGMOUTTEXT))->GetCheck())
	{
		makeOutText();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_CGETSETMETHOD))->GetCheck())
	{
		makeGetSetMethod();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_CLASSMAKER))->GetCheck())
	{
		makeClass();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_SWITCHMAKER))->GetCheck())
	{
		makeSwitch();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_IFELSEIFMAKER))->GetCheck())
	{
		makeIfElseIf();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_PGMSTRINTOARRAY))->GetCheck())
	{
		makeStrToArray();
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_PGMVALINTOARRAY))->GetCheck())
	{
		makeValueArray();
	}

	UpdateData(FALSE);
}




void CPgmAsisDlg::makeCHeader()
{
	m_str_input.MakeUpper().Trim();
	m_str_output.Format(TEXT("#ifndef _%s_H_\r\n\
#define _%s_H_\r\n\
/*  */\r\n\
\r\n\
\r\n\
#endif // _%s_H_\r\n"),m_str_input,m_str_input,m_str_input);
}


void CPgmAsisDlg::makeInPath()
{
	m_str_output = TEXT("");
	m_str_input += '\n';

	CString line = TEXT("");
	int i = 0;
	while (m_str_input[i])
	{
		if (m_str_input[i] == '\n')
		{
			line.Trim();
			if (line.GetLength())
			{
				CString tmp;
				tmp += '\"';
				int j = 0;
				while (line[j])
				{
					if (line[j] == '\\')
					{
						tmp += line[j];
						tmp += '\\';
						j++;
					}
					else
					{
						tmp += line[j];
						j++;
					}
				}
				tmp += '\"';
				m_str_output += tmp;
				m_str_output += TEXT("\r\n");
			}
			

			line = TEXT("");
		}
		else if (m_str_input[i] == '\r')
		{
			//do nothing
		}
		else
		{
			line += m_str_input[i];
		}
		i++;

	}
}


void CPgmAsisDlg::makeOutPath()
{
	m_str_output = TEXT("");
	m_str_input += '\n';

	CString line = TEXT("");

	int i = 0;
	while (m_str_input[i])
	{
		if (m_str_input[i] == '\n')
		{
			line.Trim();
			if (line.GetLength())
			{
				CString tmp;
				int j = 0;
				while (line[j])
				{
					if (line[j] == '\"')
					{
						j++;
					}
					else if (line[j] == '\\' && line[j+1] == '\\')
					{
						tmp += line[j];
						j += 2;
					}
					else
					{
						tmp += line[j];
						j++;
					}
				}
				tmp += TEXT("\r\n");
				m_str_output += tmp;
			}
			line = TEXT("");
		}
		else if (m_str_input[i] == '\r')
		{
			//do nothing
		}
		else
		{
			line += m_str_input[i];
		}
		i++;
	}
}


void CPgmAsisDlg::makeInText()
{
	m_str_output = TEXT("\"");

	int i = 0;
	while (m_str_input[i])
	{
		if (m_str_input[i] == '\t')
		{
			m_str_output += TEXT("\\t");
		}
		else if (m_str_input[i] == '\n')
		{
			m_str_output += TEXT("\\n\\\r\n");
		}
		else if (m_str_input[i] == '"')
		{
			m_str_output += TEXT("\\\"");
		}

		else if (m_str_input[i] == '\r')
		{
			//do nothing
		}
		else
		{
			m_str_output += m_str_input[i];
		}
		i++;
	}

	m_str_output += TEXT("\"");
}


void CPgmAsisDlg::makeOutText()
{
	m_str_output = TEXT("");

	int i = 0;
	while (m_str_input[i])
	{
		if (m_str_input[i] == '\\')
		{
			if (m_str_input[i + 1] == '\"')
			{
				i++;
				m_str_output += '\"';
			}
			else if (m_str_input[i + 1] == 'n')
			{
				i++;
				m_str_output += '\n';
			}
			else if (m_str_input[i + 1] == 'r')
			{
				i++;
				m_str_output += '\r';
			}
			else if (m_str_input[i + 1] == 't')
			{
				i++;
				m_str_output += '\t';
			}
			else if (m_str_input[i + 1] == '\n')
			{
				i++;
			}
		}
		else if (m_str_input[i] == '\"')
		{
			//do nothing
		}
		else
		{
			m_str_output += m_str_input[i];
		}
		i++;
	}
}


void CPgmAsisDlg::makeGetSetMethod()
{
	m_str_output = TEXT("");
	m_str_input += '\n';

	CString line=TEXT("");
	CString type = TEXT("");
	CString name = TEXT("");

	int i = 0;
	while (m_str_input[i])
	{
		if (m_str_input[i] == '\n')
		{
			type = TEXT("");
			name = TEXT("");
			int j = 0;
			bool isType = true;
			while (line[j])
			{
				if (line[j] == ' ' || line[j] == '\t' || line[j] == ';')
				{
					isType = false;
				}
				else
				{
					if (isType)
					{
						type += line[j];
					}
					else
					{
						name += line[j];
					}
				}
				j++;
			}
			type.Trim();
			name.Trim();
			if (type.GetLength() > 0 && name.GetLength() > 0)
			{
				CString upname;
				if (name[0] >= 'a' && name[0] <= 'z')
				{
					upname += (TCHAR)(name[0] & (~32));
					upname += name.Mid(1);
				}
				else
				{
					upname = name;
				}
				CString tmp;
				tmp.Format(TEXT("void Set%s(%s %s)\r\n\
{\r\n\
\tthis->%s=%s;\r\n\
}\r\n\
%s Get%s()\r\n\
{\r\n\
\treturn this->%s;\r\n\
}\r\n"), upname, type, name, name, name, type, upname, name);
				m_str_output += tmp;
			}
			line = TEXT("");
		}
		else if (m_str_input[i] == '\r')
		{
			//do nothing
		}
		else
		{
			line += m_str_input[i];
		}
		i++;
	}
}

void CPgmAsisDlg::makeClass()
{
	m_str_output = TEXT("");
	m_str_input += '\n';

	CString line = TEXT("");

	int i = 0;
	while (m_str_input[i])
	{
		if (m_str_input[i] == ' ' || m_str_input[i] == '\n' || m_str_input[i] == '\t')
		{
			line.Trim();
			if (line.GetLength() > 0)
			{
				CString upname;
				if (line[0]>='a' && line[0]<='z')
				{
					upname += (TCHAR)(line[0] & (~32));
					upname += line.Mid(1);
				}
				else
				{
					upname = line;
				}
				CString tmp;
				tmp.Format(TEXT("class %s //: public Object\r\n\
{\r\n\
public:\r\n\
\t%s()\r\n\
\t{\r\n\
\t\tInit();\r\n\
\t}\r\n\
\t%s(const %s & val)\r\n\
\t{\r\n\
\t\tCopyTo(val);\r\n\
\t}\r\n\
\t%s & operator=(const %s & val)\r\n\
\t{\r\n\
\t\tCopyTo(val);\r\n\
\t\treturn *this;\r\n\
\t}\r\n\
\tvirtual ~%s()\r\n\
\t{\r\n\
\t\t\r\n\
\t}\r\n\
protected:\r\n\
\r\n\
private:\r\n\
\r\n\
\tvoid Init()\r\n\
\t{\r\n\
\r\n\
\t}\r\n\
\tvoid CopyTo(const %s & val)\r\n\
\t{\r\n\
\r\n\
\t}\r\n\
\r\n\
};\r\n"), upname, upname, upname, upname, upname, upname, upname,upname);
				m_str_output += tmp;
			}
			
			line = TEXT("");
		}
		else
		{
			line += m_str_input[i];
		}
		i++;
	}
}

void CPgmAsisDlg::makeSwitch()
{
	m_str_output = TEXT("");
	m_str_input += '\n';

	CString line = TEXT("");

	bool hadEnd = false;
	bool isFirst = true;
	int i = 0;
	while (m_str_input[i])
	{
		if (m_str_input[i] == ' ' || m_str_input[i] == '\n' || m_str_input[i] == '\t')
		{
			line.Trim();
			if (line.GetLength() > 0)
			{
				if (isFirst)
				{
					CString tmp;
					tmp.Format(TEXT("switch (%s)\r\n\
{\r\n"), line);
					m_str_output += tmp;
					isFirst = false;
				}
				else
				{
					CString tmp;
					tmp.Format(TEXT("\tcase %s:\r\n\
\t{\r\n\
\t\t\r\n\
\t}\r\n\
\tbreak; \r\n"), line);
					m_str_output += tmp;
				}

				if (m_str_input[i + 1] == 0)
				{
					hadEnd = true;
					CString tmp;
					tmp.Format(TEXT("\tdefault:\r\n\
\t{\r\n\
\t\t\r\n\
\t}\r\n\
\tbreak; \r\n\
}\r\n"));
					m_str_output += tmp;
				}
				

			}

			line = TEXT("");
		}
		else
		{
			line += m_str_input[i];
		}
		i++;
	}
	if (hadEnd==false)
	{
		CString tmp;
		tmp.Format(TEXT("\tdefault:\r\n\
\t{\r\n\
\t\t\r\n\
\t}\r\n\
\tbreak; \r\n\
}\r\n"));
		m_str_output += tmp;
	}
}

void CPgmAsisDlg::makeIfElseIf()
{
	m_str_output = TEXT("");
	m_str_input += '\n';

	CString line = TEXT("");

	bool hadEnd = false;
	bool isFirst = true;
	int i = 0;
	while (m_str_input[i])
	{
		if (m_str_input[i] == '\n')
		{
			line.Trim();
			if (line.GetLength() > 0)
			{
				if (isFirst)
				{
					CString tmp;
					tmp.Format(TEXT("if (%s)\r\n\
{\r\n\
\t\r\n\
}\r\n"), line);
					m_str_output += tmp;
					isFirst = false;
				}
				else
				{
					CString tmp;
					tmp.Format(TEXT("else if (%s)\r\n\
{\r\n\
\t\r\n\
}\r\n"), line);
					m_str_output += tmp;
				}

				if (m_str_input[i + 1] == 0)
				{
					hadEnd = true;
					CString tmp;
					tmp.Format(TEXT("else\r\n\
{\r\n\
\t\r\n\
}\r\n"));
					m_str_output += tmp;
				}


			}

			line = TEXT("");
		}
		else
		{
			line += m_str_input[i];
		}
		i++;
	}
	if (hadEnd == false)
	{
		CString tmp;
		tmp.Format(TEXT("else\r\n\
{\r\n\
\t\r\n\
}\r\n"));
		m_str_output += tmp;
	}
}


void CPgmAsisDlg::makeStrToArray()
{
	m_str_output = TEXT("={");

	int i = 0;
	while (m_str_input[i])
	{
		CString fmt;
		fmt.Format(TEXT("'%c',"),m_str_input[i]);
		m_str_output += fmt;
		i++;
	}

	m_str_output += TEXT("0};");
}



void CPgmAsisDlg::makeValueArray()
{
	m_str_output = TEXT("={\r\n");
	m_str_input += '\n';

	CString line = TEXT("");
	CString elem = TEXT("");

	int i = 0;
	while (m_str_input[i])
	{
		if (m_str_input[i] == '\n')
		{
			line.Trim();
			if (line.GetLength())
			{
				line += ' ';
				bool hadEnd = false;
				bool isFirst = true;
				int j = 0;
				while (line[j])
				{
					if (line[j] == ' ' || line[j] == '\t' || line[j] == ',')
					{
						elem.Trim();
						if (elem.GetLength())
						{
							if (isFirst)
							{
								CString fmt;
								fmt.Format(TEXT("\t{ %s"), elem);
								m_str_output += fmt;
								isFirst = false;
							}
							else
							{
								CString fmt;
								fmt.Format(TEXT(",%s"), elem);
								m_str_output += fmt;
							}
							if (line[j + 1] == 0)
							{
								CString fmt;
								fmt.Format(TEXT("}, \r\n"));
								m_str_output += fmt;
								hadEnd = true;
							}
						}
						elem = TEXT("");
					}
					else
					{
						elem += line[j];
					}
					j++;
				}
				if (hadEnd == false)
				{
					CString fmt;
					fmt.Format(TEXT("}, \r\n"));
					m_str_output += fmt;
				}
			}
			
			line = TEXT("");
		}
		else if (m_str_input[i] == '\r')
		{
			//do nothing
		}
		else
		{
			line += m_str_input[i];
		}
		i++;
	}

	m_str_output += TEXT("};\r\n");
}


void CPgmAsisDlg::OnBnClickedButtonClean()
{
	m_str_input = TEXT("");
	UpdateData(FALSE);
}
