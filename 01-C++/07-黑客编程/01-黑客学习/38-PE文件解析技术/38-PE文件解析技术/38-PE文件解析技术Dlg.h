
// 38-PE�ļ���������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMy38PE�ļ���������Dlg �Ի���
class CMy38PE�ļ���������Dlg : public CDialogEx
{
// ����
public:
	CMy38PE�ļ���������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY38PE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_vstr_peFile;
	CString m_vstr_startPoint;
	CString m_vstr_fileAlign;
	CString m_vstr_mapBaseAddress;
	CString m_vstr_nodeCount;
	CString m_vstr_memoryAlign;
	CString m_vstr_linkerVersion;
	CListCtrl m_clist_peInfo;
	void InitControls();
	afx_msg void OnBnClickedButtonAnalize();
	void AnalizePeFile();
	LPVOID m_lpMapBase;
	HANDLE m_hMap;
	HANDLE m_hFile;
	PIMAGE_DOS_HEADER m_pDosHeader;
	PIMAGE_NT_HEADERS m_pNtHeader;
	PIMAGE_SECTION_HEADER m_pSectionHeader;
	BOOL OpenFileAndCreateMappingView(CString strFileName,bool useSecImage=true);
	void CloseFileHandles();
	BOOL IsPeFileAndGetSectorTablePointer();
	void ParseBasePeHeader();
	void EnumurateSections();
	CString m_vstr_targetCPUType;
	CString m_vstr_minOSVersion;
	CString m_vstr_fileStatusType;
	CString m_vstr_fileVersion;
	CString m_vstr_subsystemType;
	CString m_vstr_codeSectorSize;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	
	CString m_vstr_fileTypeDescript;
	CString m_vstr_peEntryInfo;
	void GetPeShellInfo();
	CString m_vstr_virtualAddress;
	CString m_vstr_relativeVirtualAddress;
	CString m_vstr_fileOffsetAddress;
	CString m_vstr_addressSector;
	CString m_vstr_newSectorName;
	DWORD m_vdw_newSectorSize;
	CString m_vstr_newSectorFillData;
	afx_msg void OnBnClickedButtonCalculateaddress();
	DWORD GetInputAddressTranslate();
	int GetAddressInSectorIndexTranslate(DWORD dwAddr);
	void CalculateAddressTranslate(int nInSectorIndex, DWORD dwAddress);
	int GetRadioButtonCheckedIndex();
	DWORD StringToInteger(CString strNum, int baseHex);
	afx_msg void OnBnClickedButtonAddnewsector();
	DWORD AlignmentSize(DWORD dwSectorSize, DWORD dwAlignment);
	void AddSectorData(DWORD dwSectorSize);
	void AddSector(char * szSectorName, DWORD dwSectorSize);
	afx_msg void OnBnClickedButtonViewFillData();
	int StringHexToByteArray(CString str, BYTE * bytes, int sizeOfArray);
};
