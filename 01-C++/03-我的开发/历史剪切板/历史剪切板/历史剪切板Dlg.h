
// 历史剪切板Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#define ID_SPYCLIPBOARD 101
#define SPY_TIME_MILSEC 30
// C历史剪切板Dlg 对话框
class C历史剪切板Dlg : public CDialogEx
{
// 构造
public:
	C历史剪切板Dlg(CWnd* pParent = NULL);	// 标准构造函数

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
private:
	CListBox m_listbox;
public:
	afx_msg void OnBnClickedCheckTransparent();
	afx_msg void OnBnClickedCheckTopWindow();
	afx_msg void OnBnClickedCheckBanPower();
	afx_msg void OnBnClickedButtonClearAll();
	afx_msg void OnBnClickedButtonCopyItem();
	void CopyItemNToClipboard(int n);
private:
	bool m_isTransparent;
	bool m_isTopMost;
	bool m_isBanPower;
	CButton m_BtnTransparent;
	CButton m_BtnTopMost;
	CButton m_BtnBanPower;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonRemoveItem();
	afx_msg void OnBnClickedHideWindow();
};
