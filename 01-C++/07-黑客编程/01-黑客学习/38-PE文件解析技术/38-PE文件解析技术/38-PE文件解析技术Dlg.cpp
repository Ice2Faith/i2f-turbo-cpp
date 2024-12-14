
// 38-PE文件解析技术Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "38-PE文件解析技术.h"
#include "38-PE文件解析技术Dlg.h"
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


// CMy38PE文件解析技术Dlg 对话框



CMy38PE文件解析技术Dlg::CMy38PE文件解析技术Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy38PE文件解析技术Dlg::IDD, pParent)
	, m_vstr_peFile(_T(""))
	, m_vstr_startPoint(_T(""))
	, m_vstr_fileAlign(_T(""))
	, m_vstr_mapBaseAddress(_T(""))
	, m_vstr_nodeCount(_T(""))
	, m_vstr_memoryAlign(_T(""))
	, m_vstr_linkerVersion(_T(""))
	, m_vstr_targetCPUType(_T(""))
	, m_vstr_minOSVersion(_T(""))
	, m_vstr_fileStatusType(_T(""))
	, m_vstr_fileVersion(_T(""))
	, m_vstr_subsystemType(_T(""))
	, m_vstr_codeSectorSize(_T(""))
	, m_vstr_fileTypeDescript(_T(""))
	, m_vstr_peEntryInfo(_T(""))
	, m_vstr_virtualAddress(_T(""))
	, m_vstr_relativeVirtualAddress(_T(""))
	, m_vstr_fileOffsetAddress(_T(""))
	, m_vstr_addressSector(_T(""))
	, m_vstr_newSectorName(_T(""))
	, m_vdw_newSectorSize(0)
	, m_vstr_newSectorFillData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy38PE文件解析技术Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_PEFILE, m_vstr_peFile);
	DDX_Text(pDX, IDC_EDIT_STARTPOINT, m_vstr_startPoint);
	DDX_Text(pDX, IDC_EDIT_FILEALIGN, m_vstr_fileAlign);
	DDX_Text(pDX, IDC_EDIT_MAPBASEADDRESS, m_vstr_mapBaseAddress);
	DDX_Text(pDX, IDC_EDIT_NODECOUNT, m_vstr_nodeCount);
	DDX_Text(pDX, IDC_EDIT_MEMORYALIGN, m_vstr_memoryAlign);
	DDX_Text(pDX, IDC_EDIT_LINKERVERSION, m_vstr_linkerVersion);
	DDX_Control(pDX, IDC_LIST_PEINFO, m_clist_peInfo);
	DDX_Text(pDX, IDC_EDIT_TARGETCPUTYPE, m_vstr_targetCPUType);
	DDX_Text(pDX, IDC_EDIT_OPERATINGSYSTEMVERSION, m_vstr_minOSVersion);
	DDX_Text(pDX, IDC_EDIT_FILESTATETYPE, m_vstr_fileStatusType);
	DDX_Text(pDX, IDC_EDIT_FILEVERSION, m_vstr_fileVersion);
	DDX_Text(pDX, IDC_EDIT_SUBSYSTEMTYPE, m_vstr_subsystemType);
	DDX_Text(pDX, IDC_EDIT_CODESECTORSIZE, m_vstr_codeSectorSize);
	DDX_Text(pDX, IDC_EDIT_FILETYPEDESCRIPT, m_vstr_fileTypeDescript);
	DDX_Text(pDX, IDC_EDIT_PEENTRYPOINTINFO, m_vstr_peEntryInfo);
	DDX_Text(pDX, IDC_EDIT_VIRTUALLADDRESS, m_vstr_virtualAddress);
	DDX_Text(pDX, IDC_EDIT_RELATIVEVIRTUALADDRESS, m_vstr_relativeVirtualAddress);
	DDX_Text(pDX, IDC_EDIT_FILEOFFSETADDRESS, m_vstr_fileOffsetAddress);
	DDX_Text(pDX, IDC_EDIT_ADDRESSSECTOR, m_vstr_addressSector);
	DDX_Text(pDX, IDC_EDIT_NEWSECTORNAME, m_vstr_newSectorName);
	DDX_Text(pDX, IDC_EDIT_NEWSECTORSIZE, m_vdw_newSectorSize);
	DDX_Text(pDX, IDC_EDIT_NEWSECTORFILLDATA, m_vstr_newSectorFillData);
}

BEGIN_MESSAGE_MAP(CMy38PE文件解析技术Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy38PE文件解析技术Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ANALIZE, &CMy38PE文件解析技术Dlg::OnBnClickedButtonAnalize)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_CALCULATEADDRESS, &CMy38PE文件解析技术Dlg::OnBnClickedButtonCalculateaddress)
	ON_BN_CLICKED(IDC_BUTTON_ADDNEWSECTOR, &CMy38PE文件解析技术Dlg::OnBnClickedButtonAddnewsector)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_FILL_DATA, &CMy38PE文件解析技术Dlg::OnBnClickedButtonViewFillData)
END_MESSAGE_MAP()


// CMy38PE文件解析技术Dlg 消息处理程序

BOOL CMy38PE文件解析技术Dlg::OnInitDialog()
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

void CMy38PE文件解析技术Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy38PE文件解析技术Dlg::OnPaint()
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
HCURSOR CMy38PE文件解析技术Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy38PE文件解析技术Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
PE文件结构：
	DOS头 IMAGE_DOS_HEADER
	DOS存根程序 一段用于提示程序不能运行在DOS下的兼容提示，可以删了或者清空数据
	PE头 IMAGE_NT_HEADERS
	节表 包含多个节表项（IMAGE_SECTION_HEADER）
	节数据

	详细结构说明：
	（部分结构存在64位版本，这里以32位版本进行介绍，64位版本有一些拓展）
	typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
    WORD   e_magic;                     // Magic number，DOS头标记，值为：x5a4d == MZ == IMAGE_DOS_SIGNATURE
    WORD   e_cblp;                      // Bytes on last page of file
    WORD   e_cp;                        // Pages in file
    WORD   e_crlc;                      // Relocations
    WORD   e_cparhdr;                   // Size of header in paragraphs
    WORD   e_minalloc;                  // Minimum extra paragraphs needed
    WORD   e_maxalloc;                  // Maximum extra paragraphs needed
    WORD   e_ss;                        // Initial (relative) SS value
    WORD   e_sp;                        // Initial SP value
    WORD   e_csum;                      // Checksum
    WORD   e_ip;                        // Initial IP value
    WORD   e_cs;                        // Initial (relative) CS value
    WORD   e_lfarlc;                    // File address of relocation table
    WORD   e_ovno;                      // Overlay number
    WORD   e_res[4];                    // Reserved words
    WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
    WORD   e_oeminfo;                   // OEM information; e_oemid specific
    WORD   e_res2[10];                  // Reserved words
    LONG   e_lfanew;                    // File address of new exe header,保存PE头的起始位置
  } IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

  typedef struct _IMAGE_NT_HEADERS {
  DWORD Signature;//PE标识符，值为：0x00004550 ==PE\0\0 == IMAGE_NT_SIGNATURE
  IMAGE_FILE_HEADER FileHeader;//文件头
  IMAGE_OPTIONAL_HEADER32 OptionalHeader;//参数可选头
  } IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

  typedef struct _IMAGE_SECTION_HEADER {
  BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];//节表项名称 ASCII
  union {
  DWORD   PhysicalAddress;
  DWORD   VirtualSize;//数据实际的节表项大小，不一定是对齐值
  } Misc;
  DWORD   VirtualAddress;//该节表项装载入内存之后的相对虚拟地址，内存对齐的
  DWORD   SizeOfRawData;//节表项在磁盘上的大小，一般为对齐值
  DWORD   PointerToRawData;//节表项在磁盘上的偏移地址FileOffset
  DWORD   PointerToRelocations;
  DWORD   PointerToLinenumbers;
  WORD    NumberOfRelocations;
  WORD    NumberOfLinenumbers;
  DWORD   Characteristics;//节表项的属性，宏以 IMAGE_SCN_CNT_CODE 为例
  } IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

  typedef struct _IMAGE_FILE_HEADER {
  WORD    Machine;//可执行文件的目标CPU类型，宏以 IMAGE_FILE_MACHINE_I386 为例
  WORD    NumberOfSections;//标识PE的节区数量
  DWORD   TimeDateStamp;//文件的创建时间，格林尼治1970-1-1秒数
  DWORD   PointerToSymbolTable;//
  DWORD   NumberOfSymbols;//
  WORD    SizeOfOptionalHeader;//参数可选头的大小，也就是说参数可选头的大小可能发生变化
  WORD    Characteristics;//指定文件的类型 宏以 IMAGE_FILE_EXECUTABLE_IMAGE 为例
  } IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

  typedef struct _IMAGE_OPTIONAL_HEADER {
  //
  // Standard fields.
  //

  WORD    Magic;//文件状态类型 宏以 IMAGE_NT_OPTIONAL_HDR_MAGIC 为例
  BYTE    MajorLinkerVersion;//链接器的主副版本号
  BYTE    MinorLinkerVersion;
  DWORD   SizeOfCode;//代码节的总大小
  DWORD   SizeOfInitializedData;//已初始化和未初始化的数据大小
  DWORD   SizeOfUninitializedData;
  DWORD   AddressOfEntryPoint;//程序执行的入口地址
  DWORD   BaseOfCode;//代码段的起始相对位置
  DWORD   BaseOfData;//数据段的起始选对位置

  //
  // NT additional fields.
  //

  DWORD   ImageBase;//被装载入内存之后的建议装载地址，exe一般就是装载地址。dll就很可能不是了
  DWORD   SectionAlignment;//节表被装入内存后的对齐值，一般为0x1000，也就是4k对齐
  DWORD   FileAlignment;//节表在文件中的对齐值，一般为x1000或者0x200，4k/512byte,值为0x1000装载块，而x200省磁盘空间
  WORD    MajorOperatingSystemVersion;//主副最低运行的系统版本号
  WORD    MinorOperatingSystemVersion;
  WORD    MajorImageVersion;//可执行文件的主副版本号
  WORD    MinorImageVersion;
  WORD    MajorSubsystemVersion;//子系统的主副版本号
  WORD    MinorSubsystemVersion;
  DWORD   Win32VersionValue;//保留
  DWORD   SizeOfImage;//可执行文件装入内存后的总大小，按内存对齐
  DWORD   SizeOfHeaders;//整个PE头部的总大小，包含DOS头，PE头，节表
  DWORD   CheckSum;//校验和，对于exe一般为0，但是对于驱动sys必须有一个校验值
  WORD    Subsystem;//可执行文件的子系统类型，宏以 IMAGE_SUBSYSTEM_WINDOWS_GUI 为例
  WORD    DllCharacteristics;//指定DLL文件属性，一般为0
  DWORD   SizeOfStackReserve;//为线程保留的栈大小
  DWORD   SizeOfStackCommit;//为线程已提交的栈大小
  DWORD   SizeOfHeapReserve;//为线程保留的堆大小
  DWORD   SizeOfHeapCommit;//为线程已提交的堆大小
  DWORD   LoaderFlags;//已经废弃，但是修改这个值会起到反调试的作用
  DWORD   NumberOfRvaAndSizes;//数据目录项的个数，IMAGE_NUMBEROF_DIRECTORY_ENTRIES == 16
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];//特定索引项拥有特定的含义，如下
  } IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

  #define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory，导出表
  #define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory，导入表
  #define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory，资源
  #define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table，重定位表
  #define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table，导入地址表IAT

  typedef struct _IMAGE_DATA_DIRECTORY {
  DWORD   VirtualAddress;//该目录项的相对虚拟地址起始值
  DWORD   Size;//该目录项的长度
  } IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

  创建文件映像相关函数：
  返回一个内存映射的句柄
  HANDLE
  WINAPI
  CreateFileMapping(
  _In_ HANDLE hFile,//文件句柄，通过CreateFile打开或者创建的
  _In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,//安全属性，一般NULL
  _In_ DWORD flProtect,//创建文件映射之后的属性，通常可读可写 PAGE_READWRITE ，但是如果要映射入内存的话，需要 SEC_IMAGE
  _In_ DWORD dwMaximumSizeHigh,//一般0
  _In_ DWORD dwMaximumSizeLow,//一般0
  _In_opt_ LPCTSTR lpName//如果需要多进程共享的话，设置一个名称，方便给其他进程找到
  );

  返回一个内存映射的内存地址
  LPVOID
  WINAPI
  MapViewOfFile(
  _In_ HANDLE hFileMappingObject,//内存映射的句柄，CreateFileMapping创建的返回值
  _In_ DWORD dwDesiredAccess,//想要获得的访问权限，一般也是可读可写 FILE_MAP_READ | FILE_SHARE_WRITE
  _In_ DWORD dwFileOffsetHigh,//这剩余三个参数，一般0
  _In_ DWORD dwFileOffsetLow,
  _In_ SIZE_T dwNumberOfBytesToMap
  );

  //释放内存映射的内存地址
  BOOL
  WINAPI
  UnmapViewOfFile(
  _In_ LPCVOID lpBaseAddress//内存映射的内存地址，MapViewOfFile的返回值
  );
*/

void CMy38PE文件解析技术Dlg::InitControls()
{
	//设置拓展样式，有网格线和选择一整行
	m_clist_peInfo.SetExtendedStyle(m_clist_peInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//插入列
	m_clist_peInfo.InsertColumn(0, TEXT("节  区  名"));
	m_clist_peInfo.InsertColumn(1, TEXT("RVA.  偏  移"));
	m_clist_peInfo.InsertColumn(2, TEXT("RVA.  大  小"));
	m_clist_peInfo.InsertColumn(3, TEXT("FOS.  偏  移"));
	m_clist_peInfo.InsertColumn(4, TEXT("FOS.  大  小"));
	m_clist_peInfo.InsertColumn(5, TEXT("标                                 志"));
	//设置自动列宽
	m_clist_peInfo.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);

	((CButton*)GetDlgItem(IDC_RADIO_VIRTUALADDRESS))->SetCheck(1);

	m_vstr_peFile = TEXT("请选择一个PE文件或者拖入文件，exe,dll,sys...");
	m_vstr_newSectorName = ("最长7字节，建议以.开头");
	m_vstr_newSectorFillData = TEXT("请输入一个十六进制串，将会按照每两位16进制字符进行转换，你可以先进行预览 比如：\\x34 gfenk26\\x35o77 转换为：34 fe 26 35 77");
	UpdateData(FALSE);
}


void CMy38PE文件解析技术Dlg::OnBnClickedButtonAnalize()
{
	AnalizePeFile();
}
void CMy38PE文件解析技术Dlg::AnalizePeFile()
{
	UpdateData(TRUE);
	BOOL bRet = OpenFileAndCreateMappingView(m_vstr_peFile);
	if (bRet == FALSE)
	{
		MessageBox(TEXT("文件打开失败或创建文件内存映像失败,\n请检查文件名是否正确或选择可执行程序！！"));
		return;
	}

	bRet = IsPeFileAndGetSectorTablePointer();
	if (bRet == FALSE)
	{
		MessageBox(TEXT("文件不是PE文件，请选择可执行文件，例如：\n.exe .dll .sys .ocx .com！！"));
		return;
	}
	GetPeShellInfo();
	m_clist_peInfo.DeleteAllItems();
	//解析并枚举节表
	ParseBasePeHeader();
	EnumurateSections();
	//释放资源并更新
	CloseFileHandles();
	UpdateData(FALSE);
}


BOOL CMy38PE文件解析技术Dlg::OpenFileAndCreateMappingView(CString strFileName, bool useSecImage)
{
	//创建内存文件映像是为了更方便的进行文件的随机访问，不用借助SetFilePointer设置文件指针位置
	//而是能够像访问内存一样随机访问
	BOOL bRet = FALSE;
	//打开文件
	m_hFile = CreateFile(strFileName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		return bRet;
	}
	//创建内存映像
	DWORD flProtect = PAGE_READWRITE;
	if (useSecImage)
		flProtect |= SEC_IMAGE;
	m_hMap = CreateFileMapping(m_hFile, NULL,
		flProtect,
		0, 0, 0);
	if (m_hMap == NULL)
	{
		CloseHandle(m_hFile);
		return bRet;
	}
	//获取内存映像指针
	m_lpMapBase = MapViewOfFile(m_hMap,
		FILE_MAP_READ | FILE_SHARE_WRITE,
		0, 0, 0);
	if (m_lpMapBase == NULL)
	{
		CloseHandle(m_hMap);
		CloseHandle(m_hFile);
		return bRet;
	}
	bRet = TRUE;
	return bRet;
}


void CMy38PE文件解析技术Dlg::CloseFileHandles()
{
	//关闭打开的相关资源
	UnmapViewOfFile(m_lpMapBase);
	CloseHandle(m_hMap);
	CloseHandle(m_hFile);
}


BOOL CMy38PE文件解析技术Dlg::IsPeFileAndGetSectorTablePointer()
{
	BOOL bRet = FALSE;
	//判断是否是DOS头
	m_pDosHeader = (PIMAGE_DOS_HEADER)m_lpMapBase;
	if (m_pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return bRet;
	//获取PE头位置
	m_pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)m_lpMapBase+m_pDosHeader->e_lfanew);
	//判断是否是PE头:PE\0\0
	if (m_pNtHeader->Signature != IMAGE_NT_SIGNATURE)
		return bRet;
	//获取节表头指针
	m_pSectionHeader = (PIMAGE_SECTION_HEADER)(((DWORD)&(m_pNtHeader->OptionalHeader)+m_pNtHeader->FileHeader.SizeOfOptionalHeader));
	
	bRet = TRUE;
	return bRet;
}


void CMy38PE文件解析技术Dlg::ParseBasePeHeader()
{
	//解析基本信息
	//程序入口点
	m_vstr_startPoint.Format(TEXT("%08x"),m_pNtHeader->OptionalHeader.AddressOfEntryPoint);
	//映像基址
	m_vstr_mapBaseAddress.Format(TEXT("%08x"),m_pNtHeader->OptionalHeader.ImageBase);
	//链接器版本
	m_vstr_linkerVersion.Format(TEXT("%d.%d"),m_pNtHeader->OptionalHeader.MajorLinkerVersion,
		m_pNtHeader->OptionalHeader.MinorLinkerVersion);
	//节数量
	m_vstr_nodeCount.Format(TEXT("%02x"),m_pNtHeader->FileHeader.NumberOfSections);
	
	/*
	相对虚拟地址的计算：
		RVA=VA-ImageBase
		RVA:相对虚拟地址
		VA：虚拟地址
		ImageBase：IMAGE_OPTIONAL_HEADER.ImageBase
	文件偏移的计算：
		某数据的文件偏移=该数据所在节的起始文件位置+（该数据的RVA-该数据所在节的起始位置RVA）
		《==》某数据的文件偏移=该数据所在节的起始文件位置+RVA下的偏移
		也就是相对所在节的起始位置的偏移去计算，而且就算数据进行不同的对齐，但是他们的相对虚拟地址之间的偏移是不变的，和文件偏移一致
	内存对齐和文件对齐一致时，文件偏移就等于相对虚拟地址
	*/
	//文件对其，为0x1000或者0x200,前者加载速度快，后者节省磁盘空间
	m_vstr_fileAlign.Format(TEXT("%08x"),m_pNtHeader->OptionalHeader.FileAlignment);
	//内存对齐
	m_vstr_memoryAlign.Format(TEXT("%08x"), m_pNtHeader->OptionalHeader.SectionAlignment);
	//目标CPU平台
	switch (m_pNtHeader->FileHeader.Machine)
	{
	case IMAGE_FILE_MACHINE_I386:
		m_vstr_targetCPUType = TEXT("Intel I386");
		break;
	case IMAGE_FILE_MACHINE_IA64:
		m_vstr_targetCPUType = TEXT("Intel 64bit");
		break;
	case IMAGE_FILE_MACHINE_ALPHA:
		m_vstr_targetCPUType = TEXT("DEC Alpha");
		break;
	case IMAGE_FILE_MACHINE_AXP64:
		m_vstr_targetCPUType = TEXT("DEC Alpha 64bit");
		break;
	case IMAGE_FILE_MACHINE_ARM:
		m_vstr_targetCPUType = TEXT("ARM");
		break;
	case IMAGE_FILE_MACHINE_UNKNOWN:
		m_vstr_targetCPUType = TEXT("UNKNOW");
		break;
	case IMAGE_FILE_MACHINE_AMD64:
		m_vstr_targetCPUType = TEXT("AMD64");
		break;
	case IMAGE_FILE_MACHINE_MIPSFPU:
		m_vstr_targetCPUType = TEXT("MIPS FPU");
		break;
	}
	//文件状态类型
	switch (m_pNtHeader->OptionalHeader.Magic)
	{
	case IMAGE_NT_OPTIONAL_HDR_MAGIC:
		m_vstr_fileStatusType = TEXT("可执行文件");
		break;
	case IMAGE_ROM_OPTIONAL_HDR_MAGIC:
		m_vstr_fileStatusType = TEXT("ROM文件");
		break;
	}
	//最低支持系统版本
	m_vstr_minOSVersion.Format(TEXT("%d.%d"),m_pNtHeader->OptionalHeader.MajorOperatingSystemVersion,
		m_pNtHeader->OptionalHeader.MinorOperatingSystemVersion);
	//文件版本
	m_vstr_fileVersion.Format(TEXT("%d.%d"), m_pNtHeader->OptionalHeader.MajorImageVersion,
		m_pNtHeader->OptionalHeader.MinorImageVersion);
	//子系统类型
	switch (m_pNtHeader->OptionalHeader.Subsystem)
	{
	case IMAGE_SUBSYSTEM_UNKNOWN:
		m_vstr_subsystemType = TEXT("未知");
		break;
	case IMAGE_SUBSYSTEM_NATIVE:
		m_vstr_subsystemType = TEXT("不需要");
		break;
	case IMAGE_SUBSYSTEM_WINDOWS_CUI:
		m_vstr_subsystemType = TEXT("控制台");
		break;
	case IMAGE_SUBSYSTEM_WINDOWS_GUI:
		m_vstr_subsystemType = TEXT("图形界面");
		break;
	case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
		m_vstr_subsystemType = TEXT("CE 图形");
		break;
	}
	//代码节大小，就算有多个代码节，那也是总代码节大小
	m_vstr_codeSectorSize.Format(TEXT("%08x"), m_pNtHeader->OptionalHeader.SizeOfCode);

	//文件类型
	m_vstr_fileTypeDescript.Format(TEXT("类型：%d"), m_pNtHeader->FileHeader.Characteristics);
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_SYSTEM)
			m_vstr_fileTypeDescript += TEXT(" 系统文件");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_DLL)
			m_vstr_fileTypeDescript += TEXT(" DLL文件");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_EXECUTABLE_IMAGE)
		m_vstr_fileTypeDescript += TEXT(" 可执行");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_RELOCS_STRIPPED)
		m_vstr_fileTypeDescript += TEXT(" 不存在重定位信息");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_LINE_NUMS_STRIPPED)
		m_vstr_fileTypeDescript += TEXT(" 行号信息已移除");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_LOCAL_SYMS_STRIPPED)
		m_vstr_fileTypeDescript += TEXT(" 符号信息已移除");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_32BIT_MACHINE)
		m_vstr_fileTypeDescript += TEXT(" 32平台使用");

	UpdateData(FALSE);
}


void CMy38PE文件解析技术Dlg::EnumurateSections()
{
	int nSectorCount = m_pNtHeader->FileHeader.NumberOfSections;
	USES_CONVERSION;
	CString temp;
	for (int i = 0; i < nSectorCount; i++)
	{
		//节名称，ASCII
		m_clist_peInfo.InsertItem(i, A2T((char *)m_pSectionHeader[i].Name)); 
		//节相对虚拟地址
		temp.Format(TEXT("%08x"),m_pSectionHeader[i].VirtualAddress);
		m_clist_peInfo.SetItemText(i, 1, temp);
		//节数据实际大小，不一定是对齐值
		temp.Format(TEXT("%08x"), m_pSectionHeader[i].Misc.VirtualSize);
		m_clist_peInfo.SetItemText(i, 2, temp);
		//节在磁盘上的偏移量
		temp.Format(TEXT("%08x"), m_pSectionHeader[i].PointerToRawData);
		m_clist_peInfo.SetItemText(i, 3, temp);
		//节在磁盘上的大小，一般就是对齐值
		temp.Format(TEXT("%08x"), m_pSectionHeader[i].SizeOfRawData);
		m_clist_peInfo.SetItemText(i, 4, temp);
		//节属性
		temp.Format(TEXT("%08x"), m_pSectionHeader[i].Characteristics);
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_CNT_CODE)
			temp += TEXT(" 含代码");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_MEM_SHARED)
			temp += TEXT(" 可共享");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_MEM_EXECUTE)
			temp += TEXT(" 可执行");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_MEM_READ)
			temp += TEXT(" 可读");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_MEM_WRITE)
			temp += TEXT(" 可写");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_CNT_INITIALIZED_DATA)
			temp += TEXT(" 已初始化数据");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_CNT_UNINITIALIZED_DATA)
			temp += TEXT(" 未初始化数据");

		m_clist_peInfo.SetItemText(i, 5, temp);

	}
}


void CMy38PE文件解析技术Dlg::OnDropFiles(HDROP hDropInfo)
{
	int count = DragQueryFile(hDropInfo,-1, NULL, 0);
	if (count > 0)
	{
		WCHAR filename[MAX_PATH];
		DragQueryFile(hDropInfo, 0, filename, MAX_PATH);
		m_vstr_peFile = filename;
		UpdateData(FALSE);
	}
	DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*实现简单的查壳程序
壳就是更改了默认的入口，
因此只要获取入口信息，根据入口的特征码匹配，即可给出壳的结果
*/
#define SHELL_NAME_LENGTH 20
#define SHELL_IDENTITY_CODE_LENGTH 32

typedef struct _ShellInfomation
{
	TCHAR shellName[SHELL_NAME_LENGTH];
	BYTE shellIdentityCode[SHELL_IDENTITY_CODE_LENGTH+1];
}ShellInfomation, *PShellInfomation;

#define GLO_SHELL_INFO_COUNT 7
ShellInfomation g_shellInfo[GLO_SHELL_INFO_COUNT] = {
	{
		TEXT("VC6"),
		"\x55\x8b\xec\x6a\xff\x68\x00\x65\x41\x40\x68\xe8\x2d\x40\x00\x64\xa1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xc4\x94"
	},
	{
		TEXT("ASPACK"),
		"\x60\xe8\x03\x00\x00\x00\xe9\xeb\x04\x5d\x45\x55\xc3\xe8\x10\x00\x00\x00\xe8\x5d\xbb\xed\xff\xff\xff\x03\xdd\x81\xeb\x00\xc0\x01"
	},
	{
		TEXT("MFC VS2013"),
		"\xe8\xa2\x73\x00\x00\xe9\x7f\xfe\xff\xff\x3b\x0d\xb0\x71\x49\x01\x75\x02\xf3\xc3\xe9\xbe\x43\x00\x00\x55\x8b\xec\x83\x7d\x08\x00"
	},
	{
		TEXT("MFC VC6"),
		"\x55\x8b\xec\x6a\xff\x68\x10\xa6\x60\x00\x68\xd4\x48\x44\x00\x64\xa1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xc4\xa4"
	},
	{
		TEXT("C# WinForm"),
		"\xff\x25\x00\x20\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	},
	{
		TEXT("QT 5 Widget"),
		"\x83\xec\x0c\xc7\x05\x4c\x40\x1f\x01\x01\x00\x00\x00\xe8\x6e\x26\x00\x00\x83\xc4\x0c\xe9\xa6\xfc\xff\xff\x8d\xb6\x00\x00\x00\x00"
	},
	{
		TEXT("Code Block STD C"),
		"\x83\xec\x1c\xc7\x04\x24\x01\x00\x00\x00\xff\x15\x08\x61\x40\x00\xe8\x6b\xfd\xff\xff\x8d\x74\x26\x00\x8d\xbc\x27\x00\x00\x00\x00"
	}
};


void CMy38PE文件解析技术Dlg::GetPeShellInfo()
{
	PBYTE pidCode = NULL;
	pidCode = (PBYTE)((DWORD)m_lpMapBase+m_pNtHeader->OptionalHeader.AddressOfEntryPoint);
	int bestIndex = -1;
	int bestCount = 0;
	for (int i = 0; i < GLO_SHELL_INFO_COUNT; i++)
	{
		for (int j = 0,trueCount=0; j < SHELL_IDENTITY_CODE_LENGTH; j++)
		{
			if (pidCode[j] == g_shellInfo[i].shellIdentityCode[j])
			{
				trueCount++;
				if (trueCount>bestCount)
				{
					bestCount = trueCount;
					bestIndex = i;
				}
					
			}
		}
	}
	if (bestCount == SHELL_IDENTITY_CODE_LENGTH)
	{
		m_vstr_peEntryInfo = g_shellInfo[bestIndex].shellName;
		return;
	}
	if (bestCount >= SHELL_IDENTITY_CODE_LENGTH/2.0)
	{
		m_vstr_peEntryInfo.Format(TEXT(">=%d%%疑似 %s"), (int)(bestCount*1.0 / SHELL_IDENTITY_CODE_LENGTH*100), g_shellInfo[bestIndex].shellName);
		return;
	}

	m_vstr_peEntryInfo = TEXT("未知特征码：");
	CString temp;
	for (int i = 0; i < SHELL_IDENTITY_CODE_LENGTH; i++)
	{
		temp.Format(TEXT("\\x%02x"), pidCode[i]);
		m_vstr_peEntryInfo += temp;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*PE地址转换

*/


void CMy38PE文件解析技术Dlg::OnBnClickedButtonCalculateaddress()
{
	UpdateData(TRUE);
	BOOL bRet = OpenFileAndCreateMappingView(m_vstr_peFile);
	if (bRet == FALSE)
	{
		MessageBox(TEXT("文件打开失败或创建文件内存映像失败,\n请检查文件名是否正确或选择可执行程序！！"));
		return;
	}

	bRet = IsPeFileAndGetSectorTablePointer();
	if (bRet == FALSE)
	{
		MessageBox(TEXT("文件不是PE文件，请选择可执行文件，例如：\n.exe .dll .sys .ocx .com！！"));
		return;
	}
	DWORD dwAddress = 0;
	//获取输入的地址
	dwAddress = GetInputAddressTranslate();
	if (dwAddress != 0)
	{
		//获取地址所在的节区
		int nInSectionIndex = GetAddressInSectorIndexTranslate(dwAddress);
		//计算地址并显示
		CalculateAddressTranslate(nInSectionIndex, dwAddress);
	}
	CloseFileHandles();
	UpdateData(FALSE);
}


DWORD CMy38PE文件解析技术Dlg::GetInputAddressTranslate()
{
	//获取选中的输入框
	int nSelect=GetRadioButtonCheckedIndex();
	//转换地址
	switch (nSelect)
	{
	case 1:
		return StringToInteger(m_vstr_virtualAddress,16);
		break;
	case 2:
		return StringToInteger(m_vstr_relativeVirtualAddress,16);
		break;
	case 3:
		return StringToInteger(m_vstr_fileOffsetAddress,16);
		break;
	}
	return 0;
}


int CMy38PE文件解析技术Dlg::GetAddressInSectorIndexTranslate(DWORD dwAddr)
{
	//获取选中的输入框、映像基址、节区数
	int nSelect = GetRadioButtonCheckedIndex();
	DWORD dwBaseImage = m_pNtHeader->OptionalHeader.ImageBase;
	int nSectorCount = m_pNtHeader->FileHeader.NumberOfSections;
	int i = 0;
	//遍历返回所在节区索引
	switch (nSelect)
	{
	case 1:
		for (i = 0; i < nSectorCount; i++)
		{
			if (dwAddr >= dwBaseImage + m_pSectionHeader[i].VirtualAddress
				&& dwAddr <= dwBaseImage+ m_pSectionHeader[i].VirtualAddress + m_pSectionHeader[i].Misc.VirtualSize)
			{
				return i;
			}
		}
		break;
	case 2:
		for (i = 0; i < nSectorCount; i++)
		{
			if (dwAddr >= m_pSectionHeader[i].VirtualAddress
				&& dwAddr <= m_pSectionHeader[i].VirtualAddress + m_pSectionHeader[i].Misc.VirtualSize)
			{
				return i;
			}
		}
		break;
	case 3:
		for (i = 0; i < nSectorCount; i++)
		{
			if (dwAddr >= m_pSectionHeader[i].PointerToRawData
				&& dwAddr <= m_pSectionHeader[i].PointerToRawData + m_pSectionHeader[i].SizeOfRawData)
			{
				return i;
			}
		}
		break;
	}
	return -1;
}


void CMy38PE文件解析技术Dlg::CalculateAddressTranslate(int nInSectorIndex, DWORD dwAddress)
{
	//计算之后的地址保存变量
	DWORD dwVirtualAddress = 0;
	DWORD dwRelativeVirtualAddress = 0;
	DWORD dwFileOffsetAddress = 0;
	//计算相应的地址
	int nSelect = GetRadioButtonCheckedIndex();
	switch (nSelect)
	{
	case 1:
		dwVirtualAddress = dwAddress;
		dwRelativeVirtualAddress = dwVirtualAddress - m_pNtHeader->OptionalHeader.ImageBase;
		dwFileOffsetAddress = m_pSectionHeader[nInSectorIndex].PointerToRawData + (dwRelativeVirtualAddress-m_pSectionHeader[nInSectorIndex].VirtualAddress);
		break;
	case 2:
		dwVirtualAddress = dwAddress + m_pNtHeader->OptionalHeader.ImageBase;
		dwRelativeVirtualAddress = dwAddress;
		dwFileOffsetAddress = m_pSectionHeader[nInSectorIndex].PointerToRawData + (dwRelativeVirtualAddress - m_pSectionHeader[nInSectorIndex].VirtualAddress);
		break;
	case 3:
		dwFileOffsetAddress = dwAddress;
		dwRelativeVirtualAddress = m_pSectionHeader[nInSectorIndex].VirtualAddress + (dwFileOffsetAddress-m_pSectionHeader[nInSectorIndex].PointerToRawData);
		dwVirtualAddress = dwRelativeVirtualAddress + m_pNtHeader->OptionalHeader.ImageBase;
		break;
	}
	//显示转换结果和地址所在节区名称
	m_vstr_virtualAddress.Format(TEXT("%08x"),dwVirtualAddress);
	m_vstr_relativeVirtualAddress.Format(TEXT("%08x"), dwRelativeVirtualAddress);
	m_vstr_fileOffsetAddress.Format(TEXT("%08x"), dwFileOffsetAddress);
	USES_CONVERSION;
	m_vstr_addressSector = A2T(((char *)m_pSectionHeader[nInSectorIndex].Name));
}


int CMy38PE文件解析技术Dlg::GetRadioButtonCheckedIndex()
{
	//获取选中的单选框下标
	if (IsDlgButtonChecked(IDC_RADIO_VIRTUALADDRESS) == 1)
	{
		return 1;
	}
	else if (IsDlgButtonChecked(IDC_RADIO_RELATIVEVRITUALADDRESS) == 1)
	{
		return 2;
	}
	else if (IsDlgButtonChecked(IDC_RADIO_FILEOFFSETADDRESS) == 1)
	{
		return 3;
	}
	return 0;
}


DWORD CMy38PE文件解析技术Dlg::StringToInteger(CString strNum, int baseHex)
{
	//将十六进制数转换为地址，其实这里支持到了36进制
	static TCHAR baseHexTable[] = {TEXT("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")};
	DWORD ret = 0;
	CString str = strNum.MakeUpper();
	int tableLength = lstrlen(baseHexTable);
	int count = str.GetLength();
	for (int i = 0; i < count;i++)
	{
		int value = -1;
		for (int j = 0; j < tableLength; j++)
		{
			if (str[i] == baseHexTable[j])
			{
				value = j;
				break;
			}
		}
		if (value == -1 || value>baseHex)
			continue;
		ret *= baseHex;
		ret += value;
	}
	return ret;
}

/////////////////////////////////////////////////////////////////////////////
/*添加节区

*/


void CMy38PE文件解析技术Dlg::OnBnClickedButtonAddnewsector()
{
	USES_CONVERSION;
	UpdateData(TRUE);
	char szSectorName[8] = { 0 };
	DWORD dwSectorSize = m_vdw_newSectorSize;
	strcpy(szSectorName,T2A(m_vstr_newSectorName));

	BOOL bRet = OpenFileAndCreateMappingView(m_vstr_peFile,false);
	if (bRet == FALSE)
	{
		MessageBox(TEXT("文件打开失败或创建文件内存映像失败,\n请检查文件名是否正确或选择可执行程序！！"));
		return;
	}

	bRet = IsPeFileAndGetSectorTablePointer();
	if (bRet == FALSE)
	{
		MessageBox(TEXT("文件不是PE文件，请选择可执行文件，例如：\n.exe .dll .sys .ocx .com！！"));
		return;
	}
	//添加节区
	AddSector(szSectorName, dwSectorSize);

	CloseFileHandles();
	//重新分析PE文件，实现实时更新显示
	AnalizePeFile();
	UpdateData(FALSE);
}


void CMy38PE文件解析技术Dlg::AddSector(char * szSectorName, DWORD dwSectorSize)
{
	//获取PE文件的节区数量、文件对齐和节区对齐
	int nSectorCount = m_pNtHeader->FileHeader.NumberOfSections;
	DWORD dwFileAlignment = m_pNtHeader->OptionalHeader.FileAlignment;
	DWORD dwSectorAlignment = m_pNtHeader->OptionalHeader.SectionAlignment;
	//新节头,由于存在对齐问题，因此实际上节表后面还是有一小段可用的空间的，一般来说能再容纳几个节头，因此复杂的就不考虑了，直接使用这点空间算了
	PIMAGE_SECTION_HEADER pNewSectorHeader = m_pSectionHeader + nSectorCount;
		
	//复制节名称
	strncpy((char *)pNewSectorHeader->Name,szSectorName,7);
	//节的内存大小
	pNewSectorHeader->Misc.VirtualSize = AlignmentSize(dwSectorSize, dwSectorAlignment);
	//节的内存起始位置
	pNewSectorHeader->VirtualAddress = m_pSectionHeader[nSectorCount - 1].VirtualAddress + AlignmentSize(m_pSectionHeader[nSectorCount-1].Misc.VirtualSize,dwSectorAlignment);
	//节的文件大小
	pNewSectorHeader->SizeOfRawData = AlignmentSize(dwSectorSize, dwFileAlignment);
	//节的文件起始位置
	pNewSectorHeader->PointerToRawData = m_pSectionHeader[nSectorCount - 1].PointerToRawData + AlignmentSize(m_pSectionHeader[nSectorCount-1].SizeOfRawData,dwSectorAlignment);
	//修正节数量
	m_pNtHeader->FileHeader.NumberOfSections++;
	//修正映像大小
	m_pNtHeader->OptionalHeader.SizeOfImage += pNewSectorHeader->Misc.VirtualSize;
	//刷写同步映像
	FlushViewOfFile(m_lpMapBase, 0);
	//添加节数据
	AddSectorData(pNewSectorHeader->SizeOfRawData);
}

DWORD CMy38PE文件解析技术Dlg::AlignmentSize(DWORD dwSectorSize,DWORD dwAlignment)
{
	//进行对齐
	if (dwSectorSize % dwAlignment != 0)
	{
		dwSectorSize = (dwSectorSize/dwAlignment+1)*dwAlignment;
	}
	return dwSectorSize;
}


void CMy38PE文件解析技术Dlg::AddSectorData(DWORD dwSectorSize)
{
	//申请空间
	PBYTE pByte = NULL;
	pByte = (PBYTE)malloc(dwSectorSize);
	ZeroMemory(pByte, dwSectorSize);
	//复制节数据
	StringHexToByteArray(m_vstr_newSectorFillData,pByte,dwSectorSize);
	
	//写入文件末尾
	DWORD dwwrited = 0;
	SetFilePointer(m_hFile, 0, 0, FILE_END);
	WriteFile(m_hFile, pByte, dwSectorSize, &dwwrited, NULL);
	FlushFileBuffers(m_hFile);
	//释放空间
	free(pByte);
}


void CMy38PE文件解析技术Dlg::OnBnClickedButtonViewFillData()
{
	//预览填充数据
	UpdateData(TRUE);
	PBYTE pByte = NULL;
	int bsize = m_vstr_newSectorFillData.GetLength()/2+1;
	pByte = (PBYTE)malloc(bsize);
	ZeroMemory(pByte, bsize);

	int fillCount = StringHexToByteArray(m_vstr_newSectorFillData, pByte, bsize);

	m_vstr_newSectorFillData = TEXT("");
	CString temp;
	for (int i = 0; i < fillCount; i++)
	{
		temp.Format(TEXT("%02x "),pByte[i]);
		m_vstr_newSectorFillData += temp;
	}
	UpdateData(FALSE);

	free(pByte);
}


int CMy38PE文件解析技术Dlg::StringHexToByteArray(CString str, BYTE * bytes, int sizeOfArray)
{
	//填充数据提取，按照输入的字符串，每2位合法和16进制字母，组成一个字节进行保存，返回实际保存的长度
	//定义进制字符表
	static TCHAR baseHexTable[] = { TEXT("0123456789ABCDEF") };
	//输入字符串转大写，便于比较
	CString sstr = str.MakeUpper();
	//获取表长度和字符长度
	int tableLength = lstrlen(baseHexTable);
	int count = sstr.GetLength();
	//定义字符串下标和保存字节下标
	int strIndex = 0;
	int byteIndex = 0;
	//已经获取的字符个数，每两个字符会合并为一个保存到temp字节中
	int counter = 0;
	BYTE temp = 0;
	//字节长度没用完并且字符串没扫描完
	while (byteIndex < sizeOfArray && strIndex<count)
	{
		//在字符表中寻找字符串字符
		for (int i = 0; i < tableLength; i++)
		{
			if (sstr[strIndex] == baseHexTable[i])
			{
				//转换字节数据
				temp *= 16;
				temp += i;
				counter++;
				if (counter == 2)//两个连续进制字符合并保存
				{
					bytes[byteIndex++] = temp;
					temp = 0;
					counter = 0;
				}
				break;
			}
		}
		strIndex++;
	}
	return byteIndex;
}
