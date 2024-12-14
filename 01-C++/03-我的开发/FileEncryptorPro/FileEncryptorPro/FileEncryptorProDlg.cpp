
// FileEncryptorProDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileEncryptorPro.h"
#include "FileEncryptorProDlg.h"
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


// CFileEncryptorProDlg �Ի���



CFileEncryptorProDlg::CFileEncryptorProDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileEncryptorProDlg::IDD, pParent)
	, m_str_Password(_T(""))
	, m_str_SavePath(_T(""))
	, m_str_OpenFile(_T(""))
	, m_isRunning(false)
	, m_pEncrypteInfo(NULL)
	, m_str_process_info(_T("�϶��ļ�������������ļ���֧�������ļ��м��ܣ������ļ���׺Ϊ.flcl�����μ����� ,���F9�鿴����"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileEncryptorProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WORK_LIST, m_lb_WorkList);
	DDX_Control(pDX, IDC_BUTTON_START_WORK, m_btn_StartWork);
	DDX_Control(pDX, IDC_BUTTON_CLEAR_ALL_ITEM, m_btn_ClearAllItem);
	DDX_Control(pDX, IDC_BUTTON_REMOVE_SELECT_ITEM, m_btn_RemoveSelectItem);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_str_Password);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_SAVE_PATH, m_str_SavePath);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_OPEN_FILE, m_str_OpenFile);
	DDX_Control(pDX, IDC_BUTTON_OPEN_FILE, m_btn_OpenFile);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_OPEN_FILE, m_edit_OpenFile);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_SAVE_PATH, m_edit_SavePath);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edit_Password);
	DDX_Control(pDX, IDC_CHECK_NOT_ADD_SUFFIX, m_ckbtn_AddDefSuffix);
	DDX_Control(pDX, IDC_CHECK_DELETE_SOURCE_FILE, m_ckbtn_DeleteSourceFile);
	DDX_Control(pDX, IDC_PROGRESS_BAR, m_pro_Process);
	DDX_Text(pDX, IDC_STATIC_PROCESS_INFO, m_str_process_info);
}

BEGIN_MESSAGE_MAP(CFileEncryptorProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFileEncryptorProDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CFileEncryptorProDlg::OnBnClickedButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_SAVE_PATH, &CFileEncryptorProDlg::OnBnClickedButtonOpenSavePath)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_SELECT_ITEM, &CFileEncryptorProDlg::OnBnClickedButtonRemoveSelectItem)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_ALL_ITEM, &CFileEncryptorProDlg::OnBnClickedButtonClearAllItem)
	ON_BN_CLICKED(IDC_BUTTON_START_WORK, &CFileEncryptorProDlg::OnBnClickedButtonStartWork)
	ON_WM_DROPFILES()
	ON_MESSAGE(UM_THREAD_PROCESS_INFO, EncryptMsgProc)
END_MESSAGE_MAP()


// CFileEncryptorProDlg ��Ϣ�������

BOOL CFileEncryptorProDlg::OnInitDialog()
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

void CFileEncryptorProDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileEncryptorProDlg::OnPaint()
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
HCURSOR CFileEncryptorProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileEncryptorProDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
/*��ʼ���ؼ�*/
void CFileEncryptorProDlg::InitControls()
{
	((CButton*)GetDlgItem(IDC_RADIO_ENCRYPTE))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO_DECRYTE))->SetCheck(0);
	m_pro_Process.SetRange(0,100);
	m_pro_Process.SetStep(1);
	m_lb_WorkList.SetHorizontalExtent(U_MAX_PATH_SIZE);
}

/*���ѡ���ļ����б��*/
void CFileEncryptorProDlg::OnBnClickedButtonOpenFile()
{
	AddOpenFileToList();
}

/*�򿪱����ļ��У���ϵͳ��ʽ*/
void CFileEncryptorProDlg::OnBnClickedButtonOpenSavePath()
{
	UpdateData(TRUE);
	ShellExecute(NULL, TEXT("open"), m_str_SavePath, NULL, NULL, SW_SHOW);
}

/*ɾ��ѡ����*/
void CFileEncryptorProDlg::OnBnClickedButtonRemoveSelectItem()
{
	RemoveSelectListItem();
}

/*����б������*/
void CFileEncryptorProDlg::OnBnClickedButtonClearAllItem()
{
	m_lb_WorkList.ResetContent();
}


/*�Ƴ�ѡ�е��б����*/
void CFileEncryptorProDlg::RemoveSelectListItem()
{
	int selIndex = m_lb_WorkList.GetCurSel();
	if (selIndex == -1)
		return;
	m_lb_WorkList.DeleteString(selIndex);
}


/*���һ��·�����б��*/
void CFileEncryptorProDlg::AddOnePathToList(TCHAR * path)
{
	//�ж�Ҫ��ӵ��ļ��Ƿ��Ѿ������б����
	bool exist = false;
	int count = m_lb_WorkList.GetCount();
	CString str;
	for (int i = 0; i < count; i++)
	{
		m_lb_WorkList.GetText(i, str);
		if (str == path)
		{
			exist = true;
			break;
		}
	}
	//����������б���������
	if (exist == false)
	{
		//����ļ����ԣ�û���������ļ����ļ��в�����
		DWORD dwAttr = GetFileAttributes(path);
		if (dwAttr == -1)
			return;
		//�ж����ļ������ļ���
		if ((dwAttr&FILE_ATTRIBUTE_DIRECTORY)==0)
		{
			m_lb_WorkList.AddString(path);
		}
		else if ((dwAttr&FILE_ATTRIBUTE_DIRECTORY))
		{
			//���Ҫ����ļ��У�������ʾ��ͬ������
			CString temp;
			temp.Format(TEXT("��⵽����ļ���:\n\n\t%s\n\n\t��ע�⡿�����ļ����Ƿǳ���ʱ�Ĳ������ر�����ļ����ر��ʱ\n\n\t�Ƿ�ȷ�ϵ�����ļ��У�"), path);
			if (MessageBox(temp, NULL, MB_OKCANCEL) == IDOK)
				m_lb_WorkList.AddString(path);
		}
	}
}
/*�ļ����봦��*/
void CFileEncryptorProDlg::OnDropFiles(HDROP hDropInfo)
{
	//�����ļ�ʱ����ڣ�������ǰ���ṩ���õ�����
	this->SetActiveWindow();
	this->SetForegroundWindow();
	//���������ļ�����ӵ��б��
	int nDropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	for (int i = 0; i< nDropCount; i++)
	{
		WCHAR szPath[MAX_PATH];
		DragQueryFile(hDropInfo, i, szPath, U_MAX_PATH_SIZE);
		AddOnePathToList(szPath);
	}
	DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}


/*ǰ����Ϣ��������������������*/
BOOL CFileEncryptorProDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)//�����ȫ�ְ���
	{
		switch (pMsg->wParam)
		{
		case VK_F9://F9��ô˰�����Ϣ
			MessageBox(TEXT("������ʾ��\n\
\t����ļ�����ѡȡ��ӣ�Ҳ���������ļ�\n\
\t�س��������Զ�������һ�������\n\
\t���·�������������л������\n\
\t���ҷ���������л��ӽ��ܷ�ʽ\n\
\tDelete������ɾ��������е� ����\n\
\tHome�����Թ�ѡȡ��ʹ��Ĭ�Ϻ�׺\n\
\tEnd�����Թ�ѡȡ��ɾ��Դ�ļ�\n\
\tF12�����Կ�ʼ���У��͵����ʼ��ťһ��\n\
\tF4����������б�򣬺������ťһ��\n\
\n\t\tDev: Ugex.Savelar\
"),0,MB_OK|MB_ICONINFORMATION);

			break;
		}
	}
	if (m_isRunning)
	{
		return CDialogEx::PreTranslateMessage(pMsg);
	}
	if (pMsg->hwnd == m_lb_WorkList.GetSafeHwnd())//�б�򰴼�
	{
		int selIndex = m_lb_WorkList.GetCurSel();
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
			case VK_DELETE://Delete��ɾ����ǰѡ����
				RemoveSelectListItem();
				break;
			case VK_UP://���¼��л���ǰѡ����
				m_lb_WorkList.SetCurSel(selIndex + 1);
				break;
			case VK_DOWN:
				m_lb_WorkList.SetCurSel(selIndex - 1 < -1 ? -1 : selIndex - 1);
				break;
			}
		}
	}
	if (pMsg->hwnd == m_edit_OpenFile.GetSafeHwnd())//�ļ�����򰴼�
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
			case VK_DELETE://Delete������ļ�ѡ��
				m_str_OpenFile = "";
				UpdateData(FALSE);
				break;
			case VK_RETURN://�س�������ļ���������ݵ��б��
				AddOpenFileToList();
				break;
			case VK_UP://�������¼��л������
				m_edit_Password.SetFocus();
				break;
			case VK_DOWN:
				m_edit_SavePath.SetFocus();
				break;
			}
		}
	}
	if (pMsg->hwnd == m_edit_SavePath.GetSafeHwnd())//����·������򰴼�
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
			case VK_DELETE://Delete����ձ���·����
				m_str_SavePath = "";
				UpdateData(FALSE);
				break;
			case VK_RETURN://�س����������л������������
				m_edit_Password.SetFocus();
				break;
			case VK_UP://�������¼��л������
				m_edit_OpenFile.SetFocus();
				break;
			case VK_DOWN:
				m_edit_Password.SetFocus();
				break;
			}
		}
	}
	if (pMsg->hwnd == m_edit_Password.GetSafeHwnd())//��������򰴼�
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
			case VK_DELETE://Delete����������
				m_str_Password = "";
				UpdateData(FALSE);
				break;
			case VK_RETURN://�س������ʼ��ť������û������
				m_btn_StartWork.SetActiveWindow();
				break;
			case VK_UP://�������¼��л������
				m_edit_SavePath.SetFocus();
				break;
			case VK_DOWN:
				m_edit_OpenFile.SetFocus();
				break;
			}
		}
	}
	if (pMsg->message == WM_KEYDOWN)//Ӧ����ȫ�ְ���
	{
		switch (pMsg->wParam)
		{
		case VK_F12://F12��ʼ�����Ϳ�ʼ��ťһ��
			StartWorkProcess();
			break;
		case VK_F4://F4����б�򣬺���հ�ťһ��
			m_lb_WorkList.ResetContent();
			break;
		case VK_LEFT://�������ѡ�м��ܵ�ѡ��
			((CButton*)GetDlgItem(IDC_RADIO_ENCRYPTE))->SetCheck(1);
			((CButton*)GetDlgItem(IDC_RADIO_DECRYTE))->SetCheck(0);
			break;
		case VK_RIGHT://�����Ҽ�ѡ�н��ܵ�ѡ��
			((CButton*)GetDlgItem(IDC_RADIO_ENCRYPTE))->SetCheck(0);
			((CButton*)GetDlgItem(IDC_RADIO_DECRYTE))->SetCheck(1);
			break;
		case VK_HOME://Home��ѡ�С�ȡ����ʹ��Ĭ�Ϻ�׺��ѡ��
			if (IsDlgButtonChecked(IDC_CHECK_NOT_ADD_SUFFIX) == 1)
				((CButton*)GetDlgItem(IDC_CHECK_NOT_ADD_SUFFIX))->SetCheck(0);
			else
				((CButton*)GetDlgItem(IDC_CHECK_NOT_ADD_SUFFIX))->SetCheck(1);
			break;
		case VK_END://End��ѡ�С�ȡ��ɾ��Դ�ļ���ѡ��
			if (IsDlgButtonChecked(IDC_CHECK_DELETE_SOURCE_FILE) == 1)
				((CButton*)GetDlgItem(IDC_CHECK_DELETE_SOURCE_FILE))->SetCheck(0);
			else
				((CButton*)GetDlgItem(IDC_CHECK_DELETE_SOURCE_FILE))->SetCheck(1);
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

/*��Ӵ��ļ�������б�*/
void CFileEncryptorProDlg::AddOpenFileToList()
{
	UpdateData(TRUE);
	m_str_OpenFile = m_str_OpenFile.Trim();//ȥ����β�ո�
	AddOnePathToList(m_str_OpenFile.GetBuffer());
	m_str_OpenFile = "";//������ÿ�
	UpdateData(FALSE);
}
/*����ļ�����ʼ�±��·��*/
int GetFileNameIndexFromPath(char * path,char pathSpliter)
{
	int index = strlen(path)-1;
	while (index > 0 && path[index] != pathSpliter)
		index--;
	return index+1;
}
/*����ļ���׺��ʼ�±��·��*/
int GetSuffixIndexFromPath(char * path, char pathSpliter)
{
	int index = strlen(path) - 1;
	while (index > 0 && path[index] != pathSpliter && path[index]!='.')
		index--;
	return index;
}
/*�ַ���ת��Ϊ��д*/
void StringToUpper(char * str)
{
	while (*str)
	{
		if (*str >= 'a'&&*str <= 'z')
			*str &= ~32;
		str++;
	}
	
}
/*�ַ���ת��ΪСд*/
void StringToLower(char * str)
{
	while (*str)
	{
		if (*str >= 'A'&&*str <= 'Z')
			*str |= 32;
		str++;
	}
}
/*�����༶Ŀ¼UNICODE�棬ע�ͼ�ASCII��*/
void CreateMultiDirectoryW(WCHAR * path, WCHAR pathSpliter)
{
	WCHAR temp[U_MAX_PATH_SIZE] = { 0 };
	int index = 0;
	while (path[index])
	{
		memset(temp, 0, sizeof(temp));
		while (path[index] && path[index]!=pathSpliter)
			index++;
		memcpy(temp, path, index*sizeof(WCHAR));
		CreateDirectoryW(temp,NULL);
		index++;
	}
}
/*�����༶Ŀ¼ASCII��*/
void CreateMultiDirectoryA(char * path, char pathSpliter)
{
	//��ʱ���洴����·��
	char temp[U_MAX_PATH_SIZE] = { 0 };
	int index = 0;
	while (path[index])
	{
		//�����ʱ·��
		memset(temp, 0, sizeof(temp));
		while (path[index] && path[index] != pathSpliter)//ֱ����ȡ����һ��·���ָ������߽���λ��
			index++;
		memcpy(temp, path, index*sizeof(char));//����ĿǰҪ������·��
		CreateDirectoryA(temp, NULL);//����·��
		index++;//������һ��·���ָ���
	}
}
void CFileEncryptorProDlg::OnBnClickedButtonStartWork()
{
	StartWorkProcess();
}
/*�ļ��д�����*/
void EncryptDirectoryProc(PEncrypteInfomation info,PProcessInfo pinfo,char * path)
{
	//���ݱ���·��
	char szParentPath[U_MAX_PATH_SIZE];
	strcpy(szParentPath, path);
	//׼������Ŀ¼����
	WIN32_FIND_DATAA FindFileData;
	HANDLE hListFile;
	//��������ļ�Ŀ��������
	char szFilePath[U_MAX_PATH_SIZE];
	strcpy(szFilePath, szParentPath);
	strcat(szFilePath, "\\*");
	//��ʼ��������ñ������
	hListFile = FindFirstFileA(szFilePath, &FindFileData);
	//���������ʼ�ɹ���ִ�б���
	if (hListFile != INVALID_HANDLE_VALUE)
	{
		//���峣����·���ָ�����Ĭ�Ϻ�׺
		static const char pathSpliter = '\\';
		static const char lockFileSuffix[] = { ".flcl" };
		//�����µ�Ŀ��·��
		CreateMultiDirectoryA(info->szSavePath, pathSpliter);
		//����Ŀ���ļ�Դ�ļ��洢
		static char szSrcFileName[U_MAX_PATH_SIZE] = { 0 };
		static char szDstFileName[U_MAX_PATH_SIZE] = { 0 };
		do
		{
			if (!strcmp(FindFileData.cFileName, ".") == 0 &&
				!strcmp(FindFileData.cFileName, "..") == 0 )//����ѭ�����������˵���·���͸�·��
			{
				//��ȡ�������ļ�������·��
				sprintf(szSrcFileName, "%s%c%s\0", szParentPath, pathSpliter, FindFileData.cFileName);
				//��ʼ����Ŀ��·��
				int fni = GetFileNameIndexFromPath(szSrcFileName, pathSpliter);
				if (info->bisEncrypte)
				{
					sprintf(szDstFileName, "%s%c%s%s\0", info->szSavePath, pathSpliter, &szSrcFileName[fni], (info->bisNoSuffix ? "" : lockFileSuffix));
				}
				else
				{
					sprintf(szDstFileName, "%s%c%s\0", info->szSavePath, pathSpliter, &szSrcFileName[fni]);
					int sfi = GetSuffixIndexFromPath(szDstFileName, pathSpliter);
					char suffix[20] = { 0 };
					if (strlen(&szDstFileName[sfi]) < 20)//��ֹһЩ��׺�����ģ�ֱ���������ɣ���������Ĭ�Ϻ�׺
					{
						strcpy(suffix, &szDstFileName[sfi]);
						StringToLower(suffix);
						if (strcmp(suffix, lockFileSuffix) == 0)
						{
							szDstFileName[sfi] = 0;
						}
					}
					
				}
				//��䴦����Ϣ
				sprintf(pinfo->szSrcFileName, "%s\0", &szSrcFileName[fni]);
				sprintf(pinfo->szDstFileName, "%s\0", &szDstFileName[GetFileNameIndexFromPath(szDstFileName, pathSpliter)]);
				//�Ƿ����ļ���
				if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					//�ļ��й����µĴ�����Ϣ���еݹ�
					EncrypteInfomation nextDirInfo = { 0 };
					memcpy(&nextDirInfo, info, sizeof(EncrypteInfomation));
					strcpy(nextDirInfo.szSavePath, szDstFileName);
					EncryptDirectoryProc(&nextDirInfo,pinfo, szSrcFileName);
				}
				else
				{
					//���ݲ������ʹ����ļ�����ȡ������
					bool ret = true;
					if (info->bisEncrypte)
						ret = info->locker->lock(szSrcFileName, szDstFileName, info->szPassword);
					else
						ret = info->locker->unlock(szSrcFileName, szDstFileName, info->szPassword);
					//��䴦����Ϣ
					if (ret == true)
					{
						pinfo->nSuccessCount++;
						pinfo->bisSuccess = true;
					}
					else
					{
						pinfo->nFailureCount++;
						pinfo->bisSuccess = false;
					}
					//���ڵݹ������һ��ʼû�л�ȡ�ܹ����ļ������������������
					pinfo->nProcessCount++;
					//�����Ҫɾ��Դ�ļ���ɾ��
					if (info->bisDelSource && ret)
						DeleteFileA(szSrcFileName);
					//���ʹ���������Ϣ
					SendMessage(info->hWnd, UM_THREAD_PROCESS_INFO, 
						(WPARAM)(int)((pinfo->nSuccessCount+pinfo->nFailureCount)*1.0/pinfo->nProcessCount*100), 
						(LPARAM)pinfo);
				}

			}
			//������һ�α���
		} while (FindNextFileA(hListFile, &FindFileData));
	}
}
/*
�����̺߳���
*/
DWORD WINAPI EncryptThreadProc( LPVOID lpThreadParameter )
{
	//����·���ָ�����Ĭ�Ϻ�׺
	const char pathSpliter = '\\';
	const char lockFileSuffix[] = { ".flcl" };
	//ת��ָ�벢����Ŀ��·��
	PEncrypteInfomation info = (PEncrypteInfomation)lpThreadParameter;
	CreateMultiDirectoryA(info->szSavePath, pathSpliter);
	USES_CONVERSION;
	//����Դ�ļ�Ŀ���ļ�·���������
	char szSrcFileName[U_MAX_PATH_SIZE] = { 0 };
	char szDstFileName[U_MAX_PATH_SIZE] = { 0 };
	//����б������
	int native_list_count = info->pWorkList->GetCount();
	//���崦����Ϣ����ʼ��
	static ProcessInfo pinfo = { 0 };
	pinfo.nSuccessCount = 0;
	pinfo.nFailureCount = 0;
	pinfo.nProcessCount = native_list_count;
	//���Ϳ�ʼ������Ϣ֮��ʼ����
	SendMessage(info->hWnd, UM_THREAD_PROCESS_INFO, (WPARAM)0, (LPARAM)&pinfo);
	for (int i = 0; i < native_list_count; i++)
	{
		//ѡ�����ڴ���������һ��������ʾ
		info->pWorkList->SetCurSel(i);
		//�ÿ�����
		ZeroMemory(szSrcFileName, U_MAX_PATH_SIZE);
		ZeroMemory(szDstFileName, U_MAX_PATH_SIZE);
		//��ȡ�б���ַ�����ת���ַ�����
		TCHAR str[U_MAX_PATH_SIZE] = { 0 };
		info->pWorkList->GetText(i,str);
		strcpy(szSrcFileName,T2A(str));
		//����ļ����±��·��
		int fni = GetFileNameIndexFromPath(szSrcFileName, pathSpliter);
		//���ݲ������ͣ�����ƴ��Ŀ��·��
		if (info->bisEncrypte)
		{
			sprintf(szDstFileName, "%s%c%s%s\0", info->szSavePath, pathSpliter, &szSrcFileName[fni], (info->bisNoSuffix ? "" : lockFileSuffix));
		}
		else
		{
			sprintf(szDstFileName, "%s%c%s\0", info->szSavePath, pathSpliter, &szSrcFileName[fni]);
			//��ȡĿ��·����׺���ж��Ƿ���ʹ��Ĭ�Ϻ�׺���ļ����������ȥ��Ĭ�Ϻ�׺
			int sfi = GetSuffixIndexFromPath(szDstFileName, pathSpliter);
			char suffix[20] = { 0 };
			strcpy(suffix, &szDstFileName[sfi]);
			StringToLower(suffix);
			if (strcmp(suffix, lockFileSuffix) == 0)
			{
				szDstFileName[sfi] = 0;
			}
		}
		//д�봦����Ϣ�����Դ��Ŀ��
		sprintf(pinfo.szSrcFileName, "%s\0", &szSrcFileName[fni]);
		sprintf(pinfo.szDstFileName, "%s\0", &szDstFileName[GetFileNameIndexFromPath(szDstFileName, pathSpliter)]);
		//�ж��Ƿ����ļ��У�������ش���
		int ret = true;
		if (GetFileAttributes(str)&FILE_ATTRIBUTE_DIRECTORY)
		{
			//�����µĴ��������Ŀ¼����ʹ�ã���������������һ������ֱ���ڴ濽������
			EncrypteInfomation nextDirInfo = { 0 };
			memcpy(&nextDirInfo, info, sizeof(EncrypteInfomation));
			strcpy(nextDirInfo.szSavePath, szDstFileName);//�����µı���·��
			EncryptDirectoryProc(&nextDirInfo,&pinfo, szSrcFileName);//��ʼĿ¼�ݹ鴦��
			ret = true;//��ֹɾ��Դ�ļ�
		}
		else
		{
			if (info->bisEncrypte)//���ݲ������ͽ����ļ��ӽ���
				ret = info->locker->lock(szSrcFileName, szDstFileName, info->szPassword);
			else
				ret = info->locker->unlock(szSrcFileName, szDstFileName, info->szPassword);
		}
		
		//�жϲ����ô�����Ϣ
		if (ret == true)
		{
			pinfo.nSuccessCount++;
			pinfo.bisSuccess = true;
		}
		else
		{
			pinfo.nFailureCount++;
			pinfo.bisSuccess = false;
		}
		//�ж��Ƿ���Ҫɾ��Դ�ļ����ڲ����ɹ�ʱ����ɾ��
		if (info->bisDelSource && ret)
			DeleteFileA(szSrcFileName);
		//���ʹ�����Ϣ
		SendMessage(info->hWnd, UM_THREAD_PROCESS_INFO, (WPARAM)(int)(i*1.0 / pinfo.nProcessCount * 100), (LPARAM)&pinfo);
	}
	//���ͽ���������Ϣ
	SendMessage(info->hWnd, UM_THREAD_PROCESS_INFO, (WPARAM)100, (LPARAM)&pinfo);

	return 0;
}
/*�Զ�����Ϣ����*/
LRESULT CFileEncryptorProDlg::EncryptMsgProc(WPARAM wParam, LPARAM lParam)
{
	int process = (int)wParam;
	m_pro_Process.SetPos(process);
	if (process == 0)
	{
		//��ʼ����ʱ�ͽ��ÿؼ�
		disableControls();
	}
	if (process==100)
	{
		//��������ʱ�����ù���
		enableControls();
		delete m_pEncrypteInfo;
		m_pEncrypteInfo = NULL;
	}
	//ת������ʾ������Ϣ
	PProcessInfo pinfo = (PProcessInfo)lParam;
	USES_CONVERSION;
	m_str_process_info.Format(TEXT("״̬��%s %d%% ��/��/��:%d/%d/%d %s ����:%s --> %s"),
		(pinfo->bisSuccess?TEXT("�ɹ�"):TEXT("ʧ��")),
		process,
		pinfo->nSuccessCount,
		pinfo->nFailureCount,
		pinfo->nProcessCount,
		(process==100?TEXT("����������ɣ���"):TEXT("")),
		A2T(pinfo->szSrcFileName),
		A2T(pinfo->szDstFileName)
		);
	UpdateData(FALSE);
	return 0;
}

/*
��ʼ����
*/
void CFileEncryptorProDlg::StartWorkProcess()
{
	char szSavePath[U_MAX_PATH_SIZE] = { 0 };
	char szPassword[MAXBYTE*2] = { 0 };
	UpdateData(TRUE);
	//��ȡ������Ϣ�������ж�
	m_str_SavePath = m_str_SavePath.Trim();
	m_str_Password = m_str_Password.Trim();
	if (m_str_SavePath.GetLength() == 0)
	{
		MessageBox(TEXT("���󣡱���·������Ϊ��"));
		return;
	}

	if (m_str_Password.GetLength() == 0)
	{
		MessageBox(TEXT("�������벻��Ϊ��"));
		return;
	}

	if (m_lb_WorkList.GetCount() == 0)
	{
		MessageBox(TEXT("����������Ӵ�������"));
		return;
	}
	//ת���ֽڱ���
	USES_CONVERSION;
	strcpy(szSavePath, T2A(m_str_SavePath));
	//strcpy(szPassword, T2A(m_str_Password));
	WCHAR wstr[MAXBYTE] = { 0 };
	lstrcpy(wstr, m_str_Password);
	int size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, szPassword, size, NULL, NULL);

	
	UpdateData(FALSE);
	//����������Ϣ
	m_pEncrypteInfo = new EncrypteInfomation();
	m_pEncrypteInfo->locker = &m_locker;
	m_pEncrypteInfo->hWnd = this->GetSafeHwnd();
	strcpy(m_pEncrypteInfo->szSavePath, szSavePath);
	strcpy(m_pEncrypteInfo->szPassword, szPassword);
	m_pEncrypteInfo->pWorkList = &m_lb_WorkList;
	m_pEncrypteInfo->bisEncrypte = ((IsDlgButtonChecked(IDC_RADIO_ENCRYPTE) == 1) ? true : false);
	m_pEncrypteInfo->bisNoSuffix = ((IsDlgButtonChecked(IDC_CHECK_NOT_ADD_SUFFIX) == 1) ? true : false);
	m_pEncrypteInfo->bisDelSource = ((IsDlgButtonChecked(IDC_CHECK_DELETE_SOURCE_FILE) == 1) ? true : false);
	//�����̣߳����д���
	m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)EncryptThreadProc, (LPVOID)m_pEncrypteInfo, 0, NULL);

}

/*
������ع��ܹ����û�ʹ��
*/
void CFileEncryptorProDlg::enableControls()
{
	m_isRunning = false;
	m_btn_StartWork.EnableWindow(TRUE);
	m_btn_ClearAllItem.EnableWindow(TRUE);
	m_btn_RemoveSelectItem.EnableWindow(TRUE);
	m_btn_OpenFile.EnableWindow(TRUE);
	m_edit_SavePath.EnableWindow(TRUE);
	m_edit_Password.EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_ENCRYPTE))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_DECRYTE))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_DELETE_SOURCE_FILE))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_NOT_ADD_SUFFIX))->EnableWindow(TRUE);
}

/*
������ع��ܣ�����Ӱ���̴߳���
*/
void CFileEncryptorProDlg::disableControls()
{
	m_isRunning = true;
	m_btn_StartWork.EnableWindow(FALSE);
	m_btn_ClearAllItem.EnableWindow(FALSE);
	m_btn_RemoveSelectItem.EnableWindow(FALSE);
	m_btn_OpenFile.EnableWindow(FALSE);
	m_edit_SavePath.EnableWindow(FALSE);
	m_edit_Password.EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_ENCRYPTE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_DECRYTE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_DELETE_SOURCE_FILE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_NOT_ADD_SUFFIX))->EnableWindow(FALSE);
}

