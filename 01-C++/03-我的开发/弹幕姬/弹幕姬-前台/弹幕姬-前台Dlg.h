
// 弹幕姬-前台Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// C弹幕姬前台Dlg 对话框
class C弹幕姬前台Dlg : public CDialogEx
{
// 构造
public:
	C弹幕姬前台Dlg(CWnd* pParent = NULL);	// 标准构造函数

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
	CString m_strFoText;
	afx_msg void OnBnClickedButtonShootFt();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_btnShoot;
	CEdit m_edt_inMsg;
	afx_msg void OnBnClickedButtonExitbgservice();
	CButton m_btnOpenMsg;
	CButton m_btnCloseMsg;
	CButton m_btnClearMsg;
	CButton m_btnShowMsgWnd;
	CButton m_btnHideMsgWnd;
	BOOL m_bRandomSize;
	BOOL m_bRandomColor;
	BOOL m_bRandomSpeed;
	CSliderCtrl m_scSize;
	CSliderCtrl m_scCRed;
	CSliderCtrl m_scCGreen;
	CSliderCtrl m_scCBlue;
	CSliderCtrl m_scSpeed;
	afx_msg void OnBnClickedButtonOpenmsg();
	afx_msg void OnBnClickedButtonClosemsg();
	afx_msg void OnBnClickedButtonClearmsg();
	afx_msg void OnBnClickedButtonShowmsgwnd();
	afx_msg void OnBnClickedButtonHidemsgwnd();
	afx_msg void OnBnClickedCheckRandomsize();
	afx_msg void OnBnClickedCheckRandomcolor();
	afx_msg void OnBnClickedCheckRandomspeed();
};
