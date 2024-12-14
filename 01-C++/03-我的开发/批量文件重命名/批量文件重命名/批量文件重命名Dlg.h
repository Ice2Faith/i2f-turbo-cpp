
// �����ļ�������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// C�����ļ�������Dlg �Ի���
class C�����ļ�������Dlg : public CDialogEx
{
// ����
public:
	C�����ļ�������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

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
	afx_msg void OnBnClickedCancel();
	CString m_str_newFileName;
	CButton m_ckb_addTime;
	CComboBox m_cmb_timeMode;
	CComboBox m_cmb_newFileMode;
	CComboBox m_cmb_splitOperator;
	CComboBox m_cmb_opeSpace;
	CString m_str_beginNumber;
	CButton m_ckb_unifySuffix;
	CString m_str_unifySuffix;
	CString m_str_addDirectoryAll;
	CListBox m_lsb_files;
	afx_msg void OnBnClickedButtonAddDirAll();
	afx_msg void OnBnClickedButtonCleanAll();
	afx_msg void OnBnClickedButtonStartRename();
	void initControls();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	bool m_b_isFirstDropFiles;
	afx_msg void OnBnClickedCheckTransparentTopmost();
	CButton m_ckb_useTransTopWnd;
	bool addItemToFileList(TCHAR * szStr, bool needUnique);
	CProgressCtrl m_pgs_operations;
	CComboBox m_cmb_timeFormat;
	CComboBox m_cmb_dateFormat;
	CString getFormatTime();
	CString getFormatDate();
	CString getSplitOperator();
	CString getUnifySuffix();
	int getBeginNumberAndFormatString(CString & formatStr);
	CString getFormatDateTime();
	CString getNumberPartStr(int num, const CString & formatStr);
	CString getTimePartStr(struct tm * loctime, const CString & formatStr);
	CString getDatePartStr(struct tm * loctime, const CString & formatStr);
	CString getDateTimePartStr(struct tm * loctime, const CString & formatStr);
	bool getIsUseNewFileName();
	bool getIsNumSpaceHead();
	bool getIsUseUnifySuffix();
	bool getIsUseTimePart();
	CString getUseableTimeStr();
	CString getNewFileNameStr();
	CButton m_ckb_cleanAllWhenDone;
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnBnClickedButtonRemove();
	bool svcStartRename();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool svcDeleteItem();
	CEdit m_edt_newFileName;
	bool svcCleanAllItem();
	CEdit m_edt_beginNumber;
	CEdit m_edt_unifySuffix;
	bool svcSwitchTranparentTopmostWnd(bool isUserClick=true);
	bool svcSwitchCleanAllWhenDone();
	bool svcSwitchUnifySuffix();
	bool svcSwitchAddTime();
};
