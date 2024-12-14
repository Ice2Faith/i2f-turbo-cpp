
// 19-进程管理器Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMy19进程管理器Dlg 对话框
class CMy19进程管理器Dlg : public CDialogEx
{
// 构造
public:
	CMy19进程管理器Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY19_DIALOG };

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
	CListCtrl m_list_processes;
	CListCtrl m_list_dlls;
	void UpdateProcesses();
	void UpdateModules();
	void InitListControl();
	int GetSelectPID();
	afx_msg void OnBnClickedButtonViewDll();
	void UpgradeProcessPrivilege();
	afx_msg void OnBnClickedButtonWaitProcess();
	afx_msg void OnBnClickedButtonRecoveryProcess();
	afx_msg void OnBnClickedButtonStopProcess();
	CString m_create_process_path;
	afx_msg void OnBnClickedButtonCreateProcess();
	afx_msg void OnBnClickedButtonRefresh();
	CButton m_ckbox_image_redirect;
	afx_msg void OnBnClickedCheckImageredirect();
};
