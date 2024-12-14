
// 16-注册表操作-启动项管理Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "16-注册表操作-启动项管理.h"
#include "16-注册表操作-启动项管理Dlg.h"
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


// CMy16注册表操作启动项管理Dlg 对话框



CMy16注册表操作启动项管理Dlg::CMy16注册表操作启动项管理Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy16注册表操作启动项管理Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy16注册表操作启动项管理Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOTLOAD, m_list_bootload);
}

BEGIN_MESSAGE_MAP(CMy16注册表操作启动项管理Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy16注册表操作启动项管理Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMy16注册表操作启动项管理Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_ADDBOOT, &CMy16注册表操作启动项管理Dlg::OnBnClickedButtonAddboot)
	ON_BN_CLICKED(IDC_BUTTON_DELBOOT, &CMy16注册表操作启动项管理Dlg::OnBnClickedButtonDelboot)
	ON_BN_CLICKED(IDC_BUTTON_CPKEY, &CMy16注册表操作启动项管理Dlg::OnBnClickedButtonCpkey)
END_MESSAGE_MAP()


// CMy16注册表操作启动项管理Dlg 消息处理程序

BOOL CMy16注册表操作启动项管理Dlg::OnInitDialog()
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
	InitListControl();
	UpdateBootRunList();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy16注册表操作启动项管理Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy16注册表操作启动项管理Dlg::OnPaint()
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
HCURSOR CMy16注册表操作启动项管理Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
	启动项管理（注意，本程序如果不能正常运行，请使用管理员方式运行）
	：
		通过枚举键值、添加键值、删除键值实现对启动项的管理

		系统注册表启动项路径：
			HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run\
		当然，还有其他诸多位置也有启动项的配置，甚至是一些手段也可以实现


	注册表操作：
		注册表实际上就是一棵树，每个键就像树的一个树根到叶子的枝干，每个叶子上就存储值，每个值分别有：名称，类型，数据
		注册表是个管理windows系统的配置数据库，这里面涉及：文件关联、启动项管理、映像劫持、篡改浏览器主页、禁用系统功能等
		也是一个名副其实的垃圾场，什么注册表垃圾应有尽有，错误配置项也层出不穷

		打开和关闭注册表：
			打开注册表函数：LONG RegOpenKeyEx(
				HKEY hkey,//指定一个父键句柄，共五个：HKEY_CLASSES_ROOT HKEY_CURRENT_USER HKEY_LOCAL_MACHINE HKEY_USERS HKEY_CURRENT_CONFIG
				LPCTSTR lpSubKey,//指定一个指向子键的字符串名称
				DWORD dwOptions,//系统保留字，必须指定为0
				REGSAM samDisired,//打开注册表的存取权限，为了方便，一般取完全控制权限：KEY_ALL_ACCESS
				PHKEY phkResult);//指向一个用来接收打开的子键句柄的双子变量
			返回值：成功：ERROR_SUCCESS，并在phkResult中保存打开的子键

			关闭注册表函数：LONG RegCloseKey(HKEY hkey);

		创建和删除子键：
			创建子键函数：LONG RegCreateKeyEx(
				HKEY hkey,//父键句柄
				LPCTSTR lpSubKey,//子键名称字符串
				DWORD reserved,//系统保留字，必须为0
				LPTSTR lpClass,//子键类名，一般为NULL
				DWORD dwOptions,//创建子键的选项，一般为REG_OPTION_NON_VOLATILE，标识被创建的子键放入注册表文件，而不是内存中
				REGSAM samDesired,//打开注册表的存取权限，同上
				LPSECURITY_ATTRIBUTES lpSecurityAttributes,//一般为NULL，否则指定结构体
				PHKEY phkResult,//用来接收打开的键的句柄双子变量
				LPSWORD lpdwDisposition);//一般为NULL
			返回值：成功：ERROR_SUCCESS，保存hkey，功能类似OpenKey，打开注册表也可使用此函数，不过参数会多不少

			删除子键函数：LONG RegDeleteKey(HKEY hkey,LPCTSTR lpSubKey);
			参数：父键句柄，子键名称字符串

		注册表键值的查询、写入和删除：
			查询键值函数：LONG RegQueryValueEx(
				HKEY hkey,//查询所在的子键句柄
				LPCTSTR lpValueName,//键值名称
				LPDWORD lpReserved,//保留字，必须为NULL
				LPDWORD lpType,//接受返回的键值类型，如不需要可以给NULL
				LPBYTE lpData,//接受数据的缓冲
				LPDWORD lpDataSize);//接收到数据的实际大小

			写入键值函数：LONG RegSetValueEx(
				HKEY hkey,//查询所在的子键句柄
				LPCTSTR lpValueName,//键值名称
				DWORD Reserved,//保留字，必须为0
				DWORD Type,//键值类型L
				const BYTE * lpData,//保存数据的缓冲
				DWORD DataSize);//保存数据的大小

			删除键值项函数：LONG RegDeleteValue(HKEY hkey,LPCTSTR lpValueName);
			参数：删除的键值句柄，被删除的键值项名称

		子键和键值的枚举：
			枚举子键函数：LONG RegEnumKeyEx(
				HKEY hkey,//被枚举的键句柄
				DWORD dwIndex,//需要返回的子键索引编号
				LPTSTR lpName,//接受子键名的缓冲
				LPDWORD nameCount,//接受到子键名的长度
				LPDWORD lpReserved,//系统保留字，必须为0
				LPTSTR lpClass,//一般为NULL
				LPDWORD classCount,//一般为NULL
				PFILETIME lpftLastWriteTime);//结构地址，接受最后被写入时间

			枚举键值的函数：LONG RegEnumValue(
				HKEY hkey,//被枚举的键句柄
				DWORD dwIndex,//需要返回的子键索引编号
				LPTSTR lpValueName,//接受值名称的缓冲
				LPDWORD valueNameCount,//接受到值名称的长度
				LPDWORD lpReserved,//系统保留字，必须为0
				LPDWORD lpType,//指向键值类型的双字变量
				LPBYTE lpData,/指向接受值数据的缓冲
				LPDWORD countData);//接收到值数据的实际大小

*/
#include"BootItemAdder.h"
//系统启动项的键路径
const TCHAR REG_BOOT_RUN[] = { TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\") };
#define REG_MAX_KEY 1024
#define REG_SHOW_COUNT 19
//常见注册表启动项键位置和对应的根
const HKEY ALL_REG_BOOT_ROOT[REG_SHOW_COUNT] = {
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE ,
	
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_LOCAL_MACHINE,
	HKEY_LOCAL_MACHINE,
	HKEY_LOCAL_MACHINE,

	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER,
	HKEY_LOCAL_MACHINE,
	HKEY_LOCAL_MACHINE,
};
const TCHAR ALL_REG_BOOT_ROOT_STR[REG_SHOW_COUNT][20] = {
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_LOCAL_MACHINE"),

	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_CURRENT_USER"),
	TEXT("HKEY_LOCAL_MACHINE"),
	TEXT("HKEY_LOCAL_MACHINE"),
};
const TCHAR ALL_REG_BOOT_KEY[REG_SHOW_COUNT][REG_MAX_KEY] = {
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"),

TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\Windows\\Load\\"),
TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\BootExecute\\"),
TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\SetupExecute\\"),
TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Execute\\"),
TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\S0InitialCommand\\"),

TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\"),
TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\Userinit\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunServices\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices\\"),
TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\Setup\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\Setup\\"),
TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx\\"),
};
//初始化List Control
void CMy16注册表操作启动项管理Dlg::InitListControl()
{
	//设置拓展样式，有网格线和选择一整行
	m_list_bootload.SetExtendedStyle(m_list_bootload.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	//插入列
	m_list_bootload.InsertColumn(0, TEXT("NO."));
	m_list_bootload.InsertColumn(1, TEXT("键                                    名"));
	m_list_bootload.InsertColumn(2, TEXT("键                                                                        值"));
	m_list_bootload.InsertColumn(3, TEXT("键  路  径"));
	//设置自动列宽
	m_list_bootload.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_bootload.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_list_bootload.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_list_bootload.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
}
//更新List Control 数据
void CMy16注册表操作启动项管理Dlg::UpdateBootRunList()
{
	//清空list数据
	m_list_bootload.DeleteAllItems();
	int dispalyIndex = 0;
	for (int i = 0; i < REG_SHOW_COUNT; i++)
	{
		//打开注册表键
		HKEY hkey = NULL;
		long ret = RegOpenKeyEx(ALL_REG_BOOT_ROOT[i], ALL_REG_BOOT_KEY[i], 0, KEY_ALL_ACCESS, &hkey);
		if (ret != ERROR_SUCCESS)
		{
			return;
		}
		//枚举索引
		int index = 0;
		CString temp;
		//值名称和值数据和其接收到数据的大小
		TCHAR szValueName[MAXBYTE] = { 0 };
		TCHAR szValueKey[MAXBYTE] = { 0 };
		DWORD dwBufferSize = MAXBYTE;
		DWORD dwKeySize = MAXBYTE;
		//值的数据类型
		DWORD dwType = 0;
		//枚举所有的值
		while (TRUE)
		{
			ret = RegEnumValue(hkey, index, szValueName, &dwBufferSize, NULL, &dwType, (unsigned char *)szValueKey, &dwKeySize);
			//如果没有更多的值项，则退出
			if (ret == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			//添加枚举的数据到list
			temp.Format(TEXT("%d"), dispalyIndex);
			m_list_bootload.InsertItem(dispalyIndex, temp);
			m_list_bootload.SetItemText(dispalyIndex, 1, szValueName);
			m_list_bootload.SetItemText(dispalyIndex, 2, szValueKey);
			temp.Format(TEXT("%s\\%s"),ALL_REG_BOOT_ROOT_STR[i],ALL_REG_BOOT_KEY[i]);
			m_list_bootload.SetItemText(dispalyIndex, 3, temp);
			//重置缓冲，并为下一次枚举做准备
			ZeroMemory(szValueKey, sizeof(szValueKey));
			ZeroMemory(szValueName, sizeof(szValueName));

			dwBufferSize = MAXBYTE;
			dwKeySize = MAXBYTE;
			index++;
			dispalyIndex++;

		}
		//关闭注册表键
		RegCloseKey(hkey);
	}
	
}
void CMy16注册表操作启动项管理Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CMy16注册表操作启动项管理Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMy16注册表操作启动项管理Dlg::OnBnClickedButtonAddboot()
{
	//创建添加项对话框
	CBootItemAdder adder;
	adder.DoModal();
	//添加项完整则添加
	if (!adder.m_bootkey.IsEmpty() && !adder.m_bootvalue.IsEmpty())
	{
		HKEY hkey = NULL;
		long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_BOOT_RUN, 0, KEY_ALL_ACCESS, &hkey);
		if (ret != ERROR_SUCCESS)
		{
			return;
		}

		RegSetValueEx(hkey, adder.m_bootkey, 0, REG_SZ, (unsigned char *)adder.m_bootvalue.GetBuffer(), adder.m_bootvalue.GetLength()*2+1);
		RegCloseKey(hkey);
		UpdateBootRunList();
	}
	
}


void CMy16注册表操作启动项管理Dlg::OnBnClickedButtonDelboot()
{
	//获取选中项
	POSITION pos = m_list_bootload.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_list_bootload.GetNextSelectedItem(pos);
	}
	//如果没有选中项则返回
	if (selIndex == -1)
	{
		return;
	}
	//获取选中项名称并删除该值
	TCHAR szValueName[MAXBYTE] = { 0 };
	m_list_bootload.GetItemText(selIndex, 1, szValueName, MAXBYTE);
	HKEY hkey = NULL;
	long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_BOOT_RUN, 0, KEY_ALL_ACCESS, &hkey);
	if (ret != ERROR_SUCCESS)
	{
		return;
	}
	RegDeleteValue(hkey,szValueName);
	RegCloseKey(hkey);
	UpdateBootRunList();
}


void CMy16注册表操作启动项管理Dlg::OnBnClickedButtonCpkey()
{
	//获取选中项
	POSITION pos = m_list_bootload.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_list_bootload.GetNextSelectedItem(pos);
	}
	//如果没有选中项则返回
	if (selIndex == -1)
	{
		return;
	}
	//获取选中项名称并删除该值
	TCHAR szKeyPath[MAXBYTE] = { 0 };
	m_list_bootload.GetItemText(selIndex, 3, szKeyPath, MAXBYTE);

	USES_CONVERSION;
	//拷贝到剪切板
	//打开剪切板进行修改
	if (OpenClipboard())
	{
		HGLOBAL hclipbuffer;
		char   *   buffer;
		//清空剪切板内容
		EmptyClipboard();
		//分配全局共享内存块并获得句柄
		hclipbuffer = GlobalAlloc(GMEM_DDESHARE, strlen(T2A(szKeyPath)) + sizeof(char));
		//锁定全局的内存对象并返回地址指针
		buffer = (char*)GlobalLock(hclipbuffer);
		strcpy(buffer, LPCSTR(T2A(szKeyPath)));
		//解除锁定的全局内存对象
		GlobalUnlock(hclipbuffer);
		//按照文本格式放入剪切板数据
		SetClipboardData(CF_TEXT, hclipbuffer);
		//关闭剪切板，其他程序好使用
		CloseClipboard();
	}
}
