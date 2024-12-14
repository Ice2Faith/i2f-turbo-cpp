
// QQ消息轰炸Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include<time.h>
#include<stdlib.h>
#include "atltypes.h"
#define ID_STOP_LOOP_ACCE (WM_USER+0x102)
#define ID_TIMER_NEXT_LOOP 0x1001
#define ID_TIMER_FIND_WND 0x1002
#define ID_TIMER_FIND_INPOS 0x1003
// CQQ消息轰炸Dlg 对话框
class CQQ消息轰炸Dlg : public CDialogEx
{
// 构造
public:
	CQQ消息轰炸Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QQ_DIALOG };

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
	CListBox m_MsgList;
	afx_msg void OnBnClickedButtonAddmsg();
	CEdit m_MsgInput;
	afx_msg void OnBnClickedButtonRmmsg();
	afx_msg void OnBnClickedButtonCleanmsg();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_SendTime;
	CComboBox m_WaitTime;
	afx_msg void OnBnClickedButtonRun();
	int m_VWaitTime;
	int m_VSendTime;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_PreTime;
	void SendMsgProc();
	CWnd * m_DrtWnd;
	bool m_IsFindWnd;
	CButton m_FindWndBtn;
	CListBox m_FindWindLB;
	afx_msg void OnBnClickedButtonSetwnd();
	CEdit m_DrtWndTitleIn;
	CComboBox m_SendTypeCB;
	void PressSendKey();
	afx_msg void OnBnClickedButtonHelp();
	CButton m_FromClipBoard;
	int m_SdMsgIndex;
	CButton m_RandSend;
	bool m_israndindex;
	afx_msg void OnBnClickedCheckRandsend();
	CButton m_OnlyCheck;
	bool m_isOnlySel;
	afx_msg void OnBnClickedCheckOnlysel();
	BOOL m_ck_findpos;
	CString m_edt_pos;
	afx_msg void OnBnClickedCheckInputpos();
	CButton m_btn_getpos;
	CPoint m_input_pos;
	CPoint m_backup_pos;
	afx_msg void OnDestroy();
	afx_msg  LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedCheckSendForeever();
	bool m_isSendForeever;
};
