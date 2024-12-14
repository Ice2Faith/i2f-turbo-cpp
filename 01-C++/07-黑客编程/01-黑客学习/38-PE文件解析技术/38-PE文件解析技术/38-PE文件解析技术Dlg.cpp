
// 38-PE�ļ���������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "38-PE�ļ���������.h"
#include "38-PE�ļ���������Dlg.h"
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


// CMy38PE�ļ���������Dlg �Ի���



CMy38PE�ļ���������Dlg::CMy38PE�ļ���������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy38PE�ļ���������Dlg::IDD, pParent)
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

void CMy38PE�ļ���������Dlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(CMy38PE�ļ���������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy38PE�ļ���������Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ANALIZE, &CMy38PE�ļ���������Dlg::OnBnClickedButtonAnalize)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_CALCULATEADDRESS, &CMy38PE�ļ���������Dlg::OnBnClickedButtonCalculateaddress)
	ON_BN_CLICKED(IDC_BUTTON_ADDNEWSECTOR, &CMy38PE�ļ���������Dlg::OnBnClickedButtonAddnewsector)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_FILL_DATA, &CMy38PE�ļ���������Dlg::OnBnClickedButtonViewFillData)
END_MESSAGE_MAP()


// CMy38PE�ļ���������Dlg ��Ϣ�������

BOOL CMy38PE�ļ���������Dlg::OnInitDialog()
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
	InitControls();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy38PE�ļ���������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy38PE�ļ���������Dlg::OnPaint()
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
HCURSOR CMy38PE�ļ���������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy38PE�ļ���������Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
PE�ļ��ṹ��
	DOSͷ IMAGE_DOS_HEADER
	DOS������� һ��������ʾ������������DOS�µļ�����ʾ������ɾ�˻����������
	PEͷ IMAGE_NT_HEADERS
	�ڱ� ��������ڱ��IMAGE_SECTION_HEADER��
	������

	��ϸ�ṹ˵����
	�����ֽṹ����64λ�汾��������32λ�汾���н��ܣ�64λ�汾��һЩ��չ��
	typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
    WORD   e_magic;                     // Magic number��DOSͷ��ǣ�ֵΪ��x5a4d == MZ == IMAGE_DOS_SIGNATURE
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
    LONG   e_lfanew;                    // File address of new exe header,����PEͷ����ʼλ��
  } IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

  typedef struct _IMAGE_NT_HEADERS {
  DWORD Signature;//PE��ʶ����ֵΪ��0x00004550 ==PE\0\0 == IMAGE_NT_SIGNATURE
  IMAGE_FILE_HEADER FileHeader;//�ļ�ͷ
  IMAGE_OPTIONAL_HEADER32 OptionalHeader;//������ѡͷ
  } IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

  typedef struct _IMAGE_SECTION_HEADER {
  BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];//�ڱ������� ASCII
  union {
  DWORD   PhysicalAddress;
  DWORD   VirtualSize;//����ʵ�ʵĽڱ����С����һ���Ƕ���ֵ
  } Misc;
  DWORD   VirtualAddress;//�ýڱ���װ�����ڴ�֮�����������ַ���ڴ�����
  DWORD   SizeOfRawData;//�ڱ����ڴ����ϵĴ�С��һ��Ϊ����ֵ
  DWORD   PointerToRawData;//�ڱ����ڴ����ϵ�ƫ�Ƶ�ַFileOffset
  DWORD   PointerToRelocations;
  DWORD   PointerToLinenumbers;
  WORD    NumberOfRelocations;
  WORD    NumberOfLinenumbers;
  DWORD   Characteristics;//�ڱ�������ԣ����� IMAGE_SCN_CNT_CODE Ϊ��
  } IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

  typedef struct _IMAGE_FILE_HEADER {
  WORD    Machine;//��ִ���ļ���Ŀ��CPU���ͣ����� IMAGE_FILE_MACHINE_I386 Ϊ��
  WORD    NumberOfSections;//��ʶPE�Ľ�������
  DWORD   TimeDateStamp;//�ļ��Ĵ���ʱ�䣬��������1970-1-1����
  DWORD   PointerToSymbolTable;//
  DWORD   NumberOfSymbols;//
  WORD    SizeOfOptionalHeader;//������ѡͷ�Ĵ�С��Ҳ����˵������ѡͷ�Ĵ�С���ܷ����仯
  WORD    Characteristics;//ָ���ļ������� ���� IMAGE_FILE_EXECUTABLE_IMAGE Ϊ��
  } IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

  typedef struct _IMAGE_OPTIONAL_HEADER {
  //
  // Standard fields.
  //

  WORD    Magic;//�ļ�״̬���� ���� IMAGE_NT_OPTIONAL_HDR_MAGIC Ϊ��
  BYTE    MajorLinkerVersion;//�������������汾��
  BYTE    MinorLinkerVersion;
  DWORD   SizeOfCode;//����ڵ��ܴ�С
  DWORD   SizeOfInitializedData;//�ѳ�ʼ����δ��ʼ�������ݴ�С
  DWORD   SizeOfUninitializedData;
  DWORD   AddressOfEntryPoint;//����ִ�е���ڵ�ַ
  DWORD   BaseOfCode;//����ε���ʼ���λ��
  DWORD   BaseOfData;//���ݶε���ʼѡ��λ��

  //
  // NT additional fields.
  //

  DWORD   ImageBase;//��װ�����ڴ�֮��Ľ���װ�ص�ַ��exeһ�����װ�ص�ַ��dll�ͺܿ��ܲ�����
  DWORD   SectionAlignment;//�ڱ�װ���ڴ��Ķ���ֵ��һ��Ϊ0x1000��Ҳ����4k����
  DWORD   FileAlignment;//�ڱ����ļ��еĶ���ֵ��һ��Ϊx1000����0x200��4k/512byte,ֵΪ0x1000װ�ؿ飬��x200ʡ���̿ռ�
  WORD    MajorOperatingSystemVersion;//����������е�ϵͳ�汾��
  WORD    MinorOperatingSystemVersion;
  WORD    MajorImageVersion;//��ִ���ļ��������汾��
  WORD    MinorImageVersion;
  WORD    MajorSubsystemVersion;//��ϵͳ�������汾��
  WORD    MinorSubsystemVersion;
  DWORD   Win32VersionValue;//����
  DWORD   SizeOfImage;//��ִ���ļ�װ���ڴ����ܴ�С�����ڴ����
  DWORD   SizeOfHeaders;//����PEͷ�����ܴ�С������DOSͷ��PEͷ���ڱ�
  DWORD   CheckSum;//У��ͣ�����exeһ��Ϊ0�����Ƕ�������sys������һ��У��ֵ
  WORD    Subsystem;//��ִ���ļ�����ϵͳ���ͣ����� IMAGE_SUBSYSTEM_WINDOWS_GUI Ϊ��
  WORD    DllCharacteristics;//ָ��DLL�ļ����ԣ�һ��Ϊ0
  DWORD   SizeOfStackReserve;//Ϊ�̱߳�����ջ��С
  DWORD   SizeOfStackCommit;//Ϊ�߳����ύ��ջ��С
  DWORD   SizeOfHeapReserve;//Ϊ�̱߳����ĶѴ�С
  DWORD   SizeOfHeapCommit;//Ϊ�߳����ύ�ĶѴ�С
  DWORD   LoaderFlags;//�Ѿ������������޸����ֵ���𵽷����Ե�����
  DWORD   NumberOfRvaAndSizes;//����Ŀ¼��ĸ�����IMAGE_NUMBEROF_DIRECTORY_ENTRIES == 16
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];//�ض�������ӵ���ض��ĺ��壬����
  } IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

  #define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory��������
  #define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory�������
  #define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory����Դ
  #define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table���ض�λ��
  #define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table�������ַ��IAT

  typedef struct _IMAGE_DATA_DIRECTORY {
  DWORD   VirtualAddress;//��Ŀ¼�����������ַ��ʼֵ
  DWORD   Size;//��Ŀ¼��ĳ���
  } IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

  �����ļ�ӳ����غ�����
  ����һ���ڴ�ӳ��ľ��
  HANDLE
  WINAPI
  CreateFileMapping(
  _In_ HANDLE hFile,//�ļ������ͨ��CreateFile�򿪻��ߴ�����
  _In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,//��ȫ���ԣ�һ��NULL
  _In_ DWORD flProtect,//�����ļ�ӳ��֮������ԣ�ͨ���ɶ���д PAGE_READWRITE ���������Ҫӳ�����ڴ�Ļ�����Ҫ SEC_IMAGE
  _In_ DWORD dwMaximumSizeHigh,//һ��0
  _In_ DWORD dwMaximumSizeLow,//һ��0
  _In_opt_ LPCTSTR lpName//�����Ҫ����̹���Ļ�������һ�����ƣ���������������ҵ�
  );

  ����һ���ڴ�ӳ����ڴ��ַ
  LPVOID
  WINAPI
  MapViewOfFile(
  _In_ HANDLE hFileMappingObject,//�ڴ�ӳ��ľ����CreateFileMapping�����ķ���ֵ
  _In_ DWORD dwDesiredAccess,//��Ҫ��õķ���Ȩ�ޣ�һ��Ҳ�ǿɶ���д FILE_MAP_READ | FILE_SHARE_WRITE
  _In_ DWORD dwFileOffsetHigh,//��ʣ������������һ��0
  _In_ DWORD dwFileOffsetLow,
  _In_ SIZE_T dwNumberOfBytesToMap
  );

  //�ͷ��ڴ�ӳ����ڴ��ַ
  BOOL
  WINAPI
  UnmapViewOfFile(
  _In_ LPCVOID lpBaseAddress//�ڴ�ӳ����ڴ��ַ��MapViewOfFile�ķ���ֵ
  );
*/

void CMy38PE�ļ���������Dlg::InitControls()
{
	//������չ��ʽ���������ߺ�ѡ��һ����
	m_clist_peInfo.SetExtendedStyle(m_clist_peInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//������
	m_clist_peInfo.InsertColumn(0, TEXT("��  ��  ��"));
	m_clist_peInfo.InsertColumn(1, TEXT("RVA.  ƫ  ��"));
	m_clist_peInfo.InsertColumn(2, TEXT("RVA.  ��  С"));
	m_clist_peInfo.InsertColumn(3, TEXT("FOS.  ƫ  ��"));
	m_clist_peInfo.InsertColumn(4, TEXT("FOS.  ��  С"));
	m_clist_peInfo.InsertColumn(5, TEXT("��                                 ־"));
	//�����Զ��п�
	m_clist_peInfo.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	m_clist_peInfo.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);

	((CButton*)GetDlgItem(IDC_RADIO_VIRTUALADDRESS))->SetCheck(1);

	m_vstr_peFile = TEXT("��ѡ��һ��PE�ļ����������ļ���exe,dll,sys...");
	m_vstr_newSectorName = ("�7�ֽڣ�������.��ͷ");
	m_vstr_newSectorFillData = TEXT("������һ��ʮ�����ƴ������ᰴ��ÿ��λ16�����ַ�����ת����������Ƚ���Ԥ�� ���磺\\x34 gfenk26\\x35o77 ת��Ϊ��34 fe 26 35 77");
	UpdateData(FALSE);
}


void CMy38PE�ļ���������Dlg::OnBnClickedButtonAnalize()
{
	AnalizePeFile();
}
void CMy38PE�ļ���������Dlg::AnalizePeFile()
{
	UpdateData(TRUE);
	BOOL bRet = OpenFileAndCreateMappingView(m_vstr_peFile);
	if (bRet == FALSE)
	{
		MessageBox(TEXT("�ļ���ʧ�ܻ򴴽��ļ��ڴ�ӳ��ʧ��,\n�����ļ����Ƿ���ȷ��ѡ���ִ�г��򣡣�"));
		return;
	}

	bRet = IsPeFileAndGetSectorTablePointer();
	if (bRet == FALSE)
	{
		MessageBox(TEXT("�ļ�����PE�ļ�����ѡ���ִ���ļ������磺\n.exe .dll .sys .ocx .com����"));
		return;
	}
	GetPeShellInfo();
	m_clist_peInfo.DeleteAllItems();
	//������ö�ٽڱ�
	ParseBasePeHeader();
	EnumurateSections();
	//�ͷ���Դ������
	CloseFileHandles();
	UpdateData(FALSE);
}


BOOL CMy38PE�ļ���������Dlg::OpenFileAndCreateMappingView(CString strFileName, bool useSecImage)
{
	//�����ڴ��ļ�ӳ����Ϊ�˸�����Ľ����ļ���������ʣ����ý���SetFilePointer�����ļ�ָ��λ��
	//�����ܹ�������ڴ�һ���������
	BOOL bRet = FALSE;
	//���ļ�
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
	//�����ڴ�ӳ��
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
	//��ȡ�ڴ�ӳ��ָ��
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


void CMy38PE�ļ���������Dlg::CloseFileHandles()
{
	//�رմ򿪵������Դ
	UnmapViewOfFile(m_lpMapBase);
	CloseHandle(m_hMap);
	CloseHandle(m_hFile);
}


BOOL CMy38PE�ļ���������Dlg::IsPeFileAndGetSectorTablePointer()
{
	BOOL bRet = FALSE;
	//�ж��Ƿ���DOSͷ
	m_pDosHeader = (PIMAGE_DOS_HEADER)m_lpMapBase;
	if (m_pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return bRet;
	//��ȡPEͷλ��
	m_pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)m_lpMapBase+m_pDosHeader->e_lfanew);
	//�ж��Ƿ���PEͷ:PE\0\0
	if (m_pNtHeader->Signature != IMAGE_NT_SIGNATURE)
		return bRet;
	//��ȡ�ڱ�ͷָ��
	m_pSectionHeader = (PIMAGE_SECTION_HEADER)(((DWORD)&(m_pNtHeader->OptionalHeader)+m_pNtHeader->FileHeader.SizeOfOptionalHeader));
	
	bRet = TRUE;
	return bRet;
}


void CMy38PE�ļ���������Dlg::ParseBasePeHeader()
{
	//����������Ϣ
	//������ڵ�
	m_vstr_startPoint.Format(TEXT("%08x"),m_pNtHeader->OptionalHeader.AddressOfEntryPoint);
	//ӳ���ַ
	m_vstr_mapBaseAddress.Format(TEXT("%08x"),m_pNtHeader->OptionalHeader.ImageBase);
	//�������汾
	m_vstr_linkerVersion.Format(TEXT("%d.%d"),m_pNtHeader->OptionalHeader.MajorLinkerVersion,
		m_pNtHeader->OptionalHeader.MinorLinkerVersion);
	//������
	m_vstr_nodeCount.Format(TEXT("%02x"),m_pNtHeader->FileHeader.NumberOfSections);
	
	/*
	��������ַ�ļ��㣺
		RVA=VA-ImageBase
		RVA:��������ַ
		VA�������ַ
		ImageBase��IMAGE_OPTIONAL_HEADER.ImageBase
	�ļ�ƫ�Ƶļ��㣺
		ĳ���ݵ��ļ�ƫ��=���������ڽڵ���ʼ�ļ�λ��+�������ݵ�RVA-���������ڽڵ���ʼλ��RVA��
		��==��ĳ���ݵ��ļ�ƫ��=���������ڽڵ���ʼ�ļ�λ��+RVA�µ�ƫ��
		Ҳ����������ڽڵ���ʼλ�õ�ƫ��ȥ���㣬���Ҿ������ݽ��в�ͬ�Ķ��룬�������ǵ���������ַ֮���ƫ���ǲ���ģ����ļ�ƫ��һ��
	�ڴ������ļ�����һ��ʱ���ļ�ƫ�ƾ͵�����������ַ
	*/
	//�ļ����䣬Ϊ0x1000����0x200,ǰ�߼����ٶȿ죬���߽�ʡ���̿ռ�
	m_vstr_fileAlign.Format(TEXT("%08x"),m_pNtHeader->OptionalHeader.FileAlignment);
	//�ڴ����
	m_vstr_memoryAlign.Format(TEXT("%08x"), m_pNtHeader->OptionalHeader.SectionAlignment);
	//Ŀ��CPUƽ̨
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
	//�ļ�״̬����
	switch (m_pNtHeader->OptionalHeader.Magic)
	{
	case IMAGE_NT_OPTIONAL_HDR_MAGIC:
		m_vstr_fileStatusType = TEXT("��ִ���ļ�");
		break;
	case IMAGE_ROM_OPTIONAL_HDR_MAGIC:
		m_vstr_fileStatusType = TEXT("ROM�ļ�");
		break;
	}
	//���֧��ϵͳ�汾
	m_vstr_minOSVersion.Format(TEXT("%d.%d"),m_pNtHeader->OptionalHeader.MajorOperatingSystemVersion,
		m_pNtHeader->OptionalHeader.MinorOperatingSystemVersion);
	//�ļ��汾
	m_vstr_fileVersion.Format(TEXT("%d.%d"), m_pNtHeader->OptionalHeader.MajorImageVersion,
		m_pNtHeader->OptionalHeader.MinorImageVersion);
	//��ϵͳ����
	switch (m_pNtHeader->OptionalHeader.Subsystem)
	{
	case IMAGE_SUBSYSTEM_UNKNOWN:
		m_vstr_subsystemType = TEXT("δ֪");
		break;
	case IMAGE_SUBSYSTEM_NATIVE:
		m_vstr_subsystemType = TEXT("����Ҫ");
		break;
	case IMAGE_SUBSYSTEM_WINDOWS_CUI:
		m_vstr_subsystemType = TEXT("����̨");
		break;
	case IMAGE_SUBSYSTEM_WINDOWS_GUI:
		m_vstr_subsystemType = TEXT("ͼ�ν���");
		break;
	case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
		m_vstr_subsystemType = TEXT("CE ͼ��");
		break;
	}
	//����ڴ�С�������ж������ڣ���Ҳ���ܴ���ڴ�С
	m_vstr_codeSectorSize.Format(TEXT("%08x"), m_pNtHeader->OptionalHeader.SizeOfCode);

	//�ļ�����
	m_vstr_fileTypeDescript.Format(TEXT("���ͣ�%d"), m_pNtHeader->FileHeader.Characteristics);
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_SYSTEM)
			m_vstr_fileTypeDescript += TEXT(" ϵͳ�ļ�");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_DLL)
			m_vstr_fileTypeDescript += TEXT(" DLL�ļ�");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_EXECUTABLE_IMAGE)
		m_vstr_fileTypeDescript += TEXT(" ��ִ��");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_RELOCS_STRIPPED)
		m_vstr_fileTypeDescript += TEXT(" �������ض�λ��Ϣ");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_LINE_NUMS_STRIPPED)
		m_vstr_fileTypeDescript += TEXT(" �к���Ϣ���Ƴ�");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_LOCAL_SYMS_STRIPPED)
		m_vstr_fileTypeDescript += TEXT(" ������Ϣ���Ƴ�");
	if ((m_pNtHeader->FileHeader.Characteristics)&IMAGE_FILE_32BIT_MACHINE)
		m_vstr_fileTypeDescript += TEXT(" 32ƽ̨ʹ��");

	UpdateData(FALSE);
}


void CMy38PE�ļ���������Dlg::EnumurateSections()
{
	int nSectorCount = m_pNtHeader->FileHeader.NumberOfSections;
	USES_CONVERSION;
	CString temp;
	for (int i = 0; i < nSectorCount; i++)
	{
		//�����ƣ�ASCII
		m_clist_peInfo.InsertItem(i, A2T((char *)m_pSectionHeader[i].Name)); 
		//����������ַ
		temp.Format(TEXT("%08x"),m_pSectionHeader[i].VirtualAddress);
		m_clist_peInfo.SetItemText(i, 1, temp);
		//������ʵ�ʴ�С����һ���Ƕ���ֵ
		temp.Format(TEXT("%08x"), m_pSectionHeader[i].Misc.VirtualSize);
		m_clist_peInfo.SetItemText(i, 2, temp);
		//���ڴ����ϵ�ƫ����
		temp.Format(TEXT("%08x"), m_pSectionHeader[i].PointerToRawData);
		m_clist_peInfo.SetItemText(i, 3, temp);
		//���ڴ����ϵĴ�С��һ����Ƕ���ֵ
		temp.Format(TEXT("%08x"), m_pSectionHeader[i].SizeOfRawData);
		m_clist_peInfo.SetItemText(i, 4, temp);
		//������
		temp.Format(TEXT("%08x"), m_pSectionHeader[i].Characteristics);
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_CNT_CODE)
			temp += TEXT(" ������");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_MEM_SHARED)
			temp += TEXT(" �ɹ���");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_MEM_EXECUTE)
			temp += TEXT(" ��ִ��");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_MEM_READ)
			temp += TEXT(" �ɶ�");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_MEM_WRITE)
			temp += TEXT(" ��д");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_CNT_INITIALIZED_DATA)
			temp += TEXT(" �ѳ�ʼ������");
		if ((m_pSectionHeader[i].Characteristics)&IMAGE_SCN_CNT_UNINITIALIZED_DATA)
			temp += TEXT(" δ��ʼ������");

		m_clist_peInfo.SetItemText(i, 5, temp);

	}
}


void CMy38PE�ļ���������Dlg::OnDropFiles(HDROP hDropInfo)
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
/*ʵ�ּ򵥵Ĳ�ǳ���
�Ǿ��Ǹ�����Ĭ�ϵ���ڣ�
���ֻҪ��ȡ�����Ϣ��������ڵ�������ƥ�䣬���ɸ����ǵĽ��
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


void CMy38PE�ļ���������Dlg::GetPeShellInfo()
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
		m_vstr_peEntryInfo.Format(TEXT(">=%d%%���� %s"), (int)(bestCount*1.0 / SHELL_IDENTITY_CODE_LENGTH*100), g_shellInfo[bestIndex].shellName);
		return;
	}

	m_vstr_peEntryInfo = TEXT("δ֪�����룺");
	CString temp;
	for (int i = 0; i < SHELL_IDENTITY_CODE_LENGTH; i++)
	{
		temp.Format(TEXT("\\x%02x"), pidCode[i]);
		m_vstr_peEntryInfo += temp;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*PE��ַת��

*/


void CMy38PE�ļ���������Dlg::OnBnClickedButtonCalculateaddress()
{
	UpdateData(TRUE);
	BOOL bRet = OpenFileAndCreateMappingView(m_vstr_peFile);
	if (bRet == FALSE)
	{
		MessageBox(TEXT("�ļ���ʧ�ܻ򴴽��ļ��ڴ�ӳ��ʧ��,\n�����ļ����Ƿ���ȷ��ѡ���ִ�г��򣡣�"));
		return;
	}

	bRet = IsPeFileAndGetSectorTablePointer();
	if (bRet == FALSE)
	{
		MessageBox(TEXT("�ļ�����PE�ļ�����ѡ���ִ���ļ������磺\n.exe .dll .sys .ocx .com����"));
		return;
	}
	DWORD dwAddress = 0;
	//��ȡ����ĵ�ַ
	dwAddress = GetInputAddressTranslate();
	if (dwAddress != 0)
	{
		//��ȡ��ַ���ڵĽ���
		int nInSectionIndex = GetAddressInSectorIndexTranslate(dwAddress);
		//�����ַ����ʾ
		CalculateAddressTranslate(nInSectionIndex, dwAddress);
	}
	CloseFileHandles();
	UpdateData(FALSE);
}


DWORD CMy38PE�ļ���������Dlg::GetInputAddressTranslate()
{
	//��ȡѡ�е������
	int nSelect=GetRadioButtonCheckedIndex();
	//ת����ַ
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


int CMy38PE�ļ���������Dlg::GetAddressInSectorIndexTranslate(DWORD dwAddr)
{
	//��ȡѡ�е������ӳ���ַ��������
	int nSelect = GetRadioButtonCheckedIndex();
	DWORD dwBaseImage = m_pNtHeader->OptionalHeader.ImageBase;
	int nSectorCount = m_pNtHeader->FileHeader.NumberOfSections;
	int i = 0;
	//�����������ڽ�������
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


void CMy38PE�ļ���������Dlg::CalculateAddressTranslate(int nInSectorIndex, DWORD dwAddress)
{
	//����֮��ĵ�ַ�������
	DWORD dwVirtualAddress = 0;
	DWORD dwRelativeVirtualAddress = 0;
	DWORD dwFileOffsetAddress = 0;
	//������Ӧ�ĵ�ַ
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
	//��ʾת������͵�ַ���ڽ�������
	m_vstr_virtualAddress.Format(TEXT("%08x"),dwVirtualAddress);
	m_vstr_relativeVirtualAddress.Format(TEXT("%08x"), dwRelativeVirtualAddress);
	m_vstr_fileOffsetAddress.Format(TEXT("%08x"), dwFileOffsetAddress);
	USES_CONVERSION;
	m_vstr_addressSector = A2T(((char *)m_pSectionHeader[nInSectorIndex].Name));
}


int CMy38PE�ļ���������Dlg::GetRadioButtonCheckedIndex()
{
	//��ȡѡ�еĵ�ѡ���±�
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


DWORD CMy38PE�ļ���������Dlg::StringToInteger(CString strNum, int baseHex)
{
	//��ʮ��������ת��Ϊ��ַ����ʵ����֧�ֵ���36����
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
/*��ӽ���

*/


void CMy38PE�ļ���������Dlg::OnBnClickedButtonAddnewsector()
{
	USES_CONVERSION;
	UpdateData(TRUE);
	char szSectorName[8] = { 0 };
	DWORD dwSectorSize = m_vdw_newSectorSize;
	strcpy(szSectorName,T2A(m_vstr_newSectorName));

	BOOL bRet = OpenFileAndCreateMappingView(m_vstr_peFile,false);
	if (bRet == FALSE)
	{
		MessageBox(TEXT("�ļ���ʧ�ܻ򴴽��ļ��ڴ�ӳ��ʧ��,\n�����ļ����Ƿ���ȷ��ѡ���ִ�г��򣡣�"));
		return;
	}

	bRet = IsPeFileAndGetSectorTablePointer();
	if (bRet == FALSE)
	{
		MessageBox(TEXT("�ļ�����PE�ļ�����ѡ���ִ���ļ������磺\n.exe .dll .sys .ocx .com����"));
		return;
	}
	//��ӽ���
	AddSector(szSectorName, dwSectorSize);

	CloseFileHandles();
	//���·���PE�ļ���ʵ��ʵʱ������ʾ
	AnalizePeFile();
	UpdateData(FALSE);
}


void CMy38PE�ļ���������Dlg::AddSector(char * szSectorName, DWORD dwSectorSize)
{
	//��ȡPE�ļ��Ľ����������ļ�����ͽ�������
	int nSectorCount = m_pNtHeader->FileHeader.NumberOfSections;
	DWORD dwFileAlignment = m_pNtHeader->OptionalHeader.FileAlignment;
	DWORD dwSectorAlignment = m_pNtHeader->OptionalHeader.SectionAlignment;
	//�½�ͷ,���ڴ��ڶ������⣬���ʵ���Ͻڱ���滹����һС�ο��õĿռ�ģ�һ����˵�������ɼ�����ͷ����˸��ӵľͲ������ˣ�ֱ��ʹ�����ռ�����
	PIMAGE_SECTION_HEADER pNewSectorHeader = m_pSectionHeader + nSectorCount;
		
	//���ƽ�����
	strncpy((char *)pNewSectorHeader->Name,szSectorName,7);
	//�ڵ��ڴ��С
	pNewSectorHeader->Misc.VirtualSize = AlignmentSize(dwSectorSize, dwSectorAlignment);
	//�ڵ��ڴ���ʼλ��
	pNewSectorHeader->VirtualAddress = m_pSectionHeader[nSectorCount - 1].VirtualAddress + AlignmentSize(m_pSectionHeader[nSectorCount-1].Misc.VirtualSize,dwSectorAlignment);
	//�ڵ��ļ���С
	pNewSectorHeader->SizeOfRawData = AlignmentSize(dwSectorSize, dwFileAlignment);
	//�ڵ��ļ���ʼλ��
	pNewSectorHeader->PointerToRawData = m_pSectionHeader[nSectorCount - 1].PointerToRawData + AlignmentSize(m_pSectionHeader[nSectorCount-1].SizeOfRawData,dwSectorAlignment);
	//����������
	m_pNtHeader->FileHeader.NumberOfSections++;
	//����ӳ���С
	m_pNtHeader->OptionalHeader.SizeOfImage += pNewSectorHeader->Misc.VirtualSize;
	//ˢдͬ��ӳ��
	FlushViewOfFile(m_lpMapBase, 0);
	//��ӽ�����
	AddSectorData(pNewSectorHeader->SizeOfRawData);
}

DWORD CMy38PE�ļ���������Dlg::AlignmentSize(DWORD dwSectorSize,DWORD dwAlignment)
{
	//���ж���
	if (dwSectorSize % dwAlignment != 0)
	{
		dwSectorSize = (dwSectorSize/dwAlignment+1)*dwAlignment;
	}
	return dwSectorSize;
}


void CMy38PE�ļ���������Dlg::AddSectorData(DWORD dwSectorSize)
{
	//����ռ�
	PBYTE pByte = NULL;
	pByte = (PBYTE)malloc(dwSectorSize);
	ZeroMemory(pByte, dwSectorSize);
	//���ƽ�����
	StringHexToByteArray(m_vstr_newSectorFillData,pByte,dwSectorSize);
	
	//д���ļ�ĩβ
	DWORD dwwrited = 0;
	SetFilePointer(m_hFile, 0, 0, FILE_END);
	WriteFile(m_hFile, pByte, dwSectorSize, &dwwrited, NULL);
	FlushFileBuffers(m_hFile);
	//�ͷſռ�
	free(pByte);
}


void CMy38PE�ļ���������Dlg::OnBnClickedButtonViewFillData()
{
	//Ԥ���������
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


int CMy38PE�ļ���������Dlg::StringHexToByteArray(CString str, BYTE * bytes, int sizeOfArray)
{
	//���������ȡ������������ַ�����ÿ2λ�Ϸ���16������ĸ�����һ���ֽڽ��б��棬����ʵ�ʱ���ĳ���
	//��������ַ���
	static TCHAR baseHexTable[] = { TEXT("0123456789ABCDEF") };
	//�����ַ���ת��д�����ڱȽ�
	CString sstr = str.MakeUpper();
	//��ȡ���Ⱥ��ַ�����
	int tableLength = lstrlen(baseHexTable);
	int count = sstr.GetLength();
	//�����ַ����±�ͱ����ֽ��±�
	int strIndex = 0;
	int byteIndex = 0;
	//�Ѿ���ȡ���ַ�������ÿ�����ַ���ϲ�Ϊһ�����浽temp�ֽ���
	int counter = 0;
	BYTE temp = 0;
	//�ֽڳ���û���겢���ַ���ûɨ����
	while (byteIndex < sizeOfArray && strIndex<count)
	{
		//���ַ�����Ѱ���ַ����ַ�
		for (int i = 0; i < tableLength; i++)
		{
			if (sstr[strIndex] == baseHexTable[i])
			{
				//ת���ֽ�����
				temp *= 16;
				temp += i;
				counter++;
				if (counter == 2)//�������������ַ��ϲ�����
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
