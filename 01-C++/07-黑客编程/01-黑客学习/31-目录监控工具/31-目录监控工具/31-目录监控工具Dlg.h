
// 31-目录监控工具Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMy31目录监控工具Dlg 对话框
class CMy31目录监控工具Dlg : public CDialogEx
{
// 构造
public:
	CMy31目录监控工具Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY31_DIALOG };

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
	CString m_strSpyPath;
	CListCtrl m_list_spy_log;
	afx_msg void OnBnClickedButtonSpyOn();
	afx_msg void OnBnClickedButtonSpyOff();
	void InitFaceControl();
	HANDLE hThread;
	CButton m_btn_spyon;
	CButton m_btn_spyoff;
	afx_msg void OnBnClickedButtonClearList();
};
