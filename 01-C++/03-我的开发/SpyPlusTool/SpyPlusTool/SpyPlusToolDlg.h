
// SpyPlusToolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#define ID_TIMER_FINDWINDOW 0x1001
// CSpyPlusToolDlg 对话框
class CSpyPlusToolDlg : public CDialogEx
{
// 构造
public:
	CSpyPlusToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SPYPLUSTOOL_DIALOG };

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
	CComboBox m_CMB_ExPoewr;
	CButton m_BTN_ExPower;
	CButton m_BTN_Spy;
	CButton m_BTN_Size;
	CButton m_BTN_Pos;
	CButton m_BTN_Help;
	CButton m_BTN_Copy;
	CButton m_CKB_PmsSetTransprt;
	CEdit m_EDT_Hand;
	CEdit m_EDT_Title;
	CEdit m_EDT_Class;
	CEdit m_DET_Rect;
	CEdit m_EDT_Style;
	CEdit m_EDT_ExStyle;
	CEdit m_EDT_Size;
	CEdit m_EDT_Pos;
	CSliderCtrl m_SDC_Transparent;
	bool m_allow_SetTransparent;
	bool m_is_FindWindow;
	CWnd * m_DrtWnd;
	CString wHand;
	CString wTitle;
	CString wClass;
	CString wRect;
	CString wStyle;
	CString wExStyle;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetWndTransparent(HWND hwnd, float alpha);
	afx_msg void OnNMCustomdrawSliderTransparent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonSize();
	afx_msg void OnBnClickedButtonPos();
	afx_msg void OnBnClickedButtonExpower();
	afx_msg void OnBnClickedCheckPmssettransparent();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonCopy();
	CListCtrl m_lst_spyHistory;
	void InitControls();
	afx_msg void OnBnClickedButtonLoadSel();
	afx_msg void OnBnClickedButtonTerminalProcess();
	afx_msg void OnBnClickedButtonEnumWindows();
	afx_msg void OnBnClickedButtonDesktopWindow();
	void ShowDrtWindowInfoToView();
	bool AdjustCurrentProcessPrivaligeToSEDebug();
};
