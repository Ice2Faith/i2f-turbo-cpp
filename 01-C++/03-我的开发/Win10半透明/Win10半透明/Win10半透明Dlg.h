
// Win10半透明Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#define ID_TIMER_LOOP 0x1001

// CWin10半透明Dlg 对话框
class CWin10半透明Dlg : public CDialogEx
{
// 构造
public:
	CWin10半透明Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WIN10_DIALOG };

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
	BOOL SetTransParent(HWND mHwnd, float alpha);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL m_ck_explorer;
	BOOL m_ck_ctrlcenter;
	BOOL m_ck_startmenu;
	BOOL m_ck_winsearch;
	BOOL m_ck_notifyicon;
	afx_msg void OnBnClickedButtonUse();
	CButton m_ck_all;
	afx_msg void OnBnClickedCheckCkall();
	BOOL m_ck_console;
	BOOL m_ck_notepad;
	BOOL m_ck_win7cal;
	BOOL m_ck_run;
};
