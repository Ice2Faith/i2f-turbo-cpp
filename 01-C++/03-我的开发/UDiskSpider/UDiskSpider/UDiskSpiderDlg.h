
// UDiskSpiderDlg.h : 头文件
//

#pragma once
#include<Dbt.h>
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#define MAX_LEVEL 10
// CUDiskSpiderDlg 对话框
class CUDiskSpiderDlg : public CDialogEx
{
// 构造
public:
	CUDiskSpiderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UDISKSPIDER_DIALOG };

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
private:
	TCHAR GetDiskCharFuMask(DWORD uMask);
	void ProcessNewMoveDisk(TCHAR disk);
	void ProcessDir(TCHAR * dir);
	void MakeDirs(CString path);
public:
	bool ProcessFile(TCHAR * file);
	afx_msg BOOL OnDeviceChange(UINT nEventType,DWORD dwData);
	afx_msg void OnBnClickedOk();
	CComboBox m_CBtype;
	CListBox m_LBtype;
	afx_msg void OnBnClickedButtonInserttype();
	CMFCEditBrowseCtrl m_EBCviewdir;
	afx_msg void OnCbnSelchangeComboFiletype();
	CEdit m_ECUserType;
	afx_msg void OnBnClickedButtonRemovetype();
	CString m_CSUserType;
	afx_msg void OnBnClickedButtonCleartype();
	CButton m_CKBanPower;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListBox m_LBRunLog;
	afx_msg void OnBnClickedCheckAllfiles();
	CButton m_CKAllFiles;
	CButton m_BTAdd;
	CButton m_BTRemove;
	CComboBox m_CBjumpSize;
	afx_msg void OnBnClickedButtonHideWnd();
	afx_msg void OnCbnSelchangeComboJumpSize();
	int m_jumpSize;
};
