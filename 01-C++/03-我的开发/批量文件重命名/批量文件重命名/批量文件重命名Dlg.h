
// 批量文件重命名Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// C批量文件重命名Dlg 对话框
class C批量文件重命名Dlg : public CDialogEx
{
// 构造
public:
	C批量文件重命名Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
