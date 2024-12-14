#pragma once


// CAdminWnd 对话框

class CAdminWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminWnd)

public:
	CAdminWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdminWnd();

// 对话框数据
	enum { IDD = IDD_DLG_ADMINWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString m_str_tips;
	bool m_retCode;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_timer_display;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	int m_waitTime;
	int m_prewaittime;
};
