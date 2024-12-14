#pragma once
#include"Client.h"
#include "afxwin.h"
// WelComeFace 对话框
enum UserOption{UP_NULL,UP_OFFLINE,UP_LOGIN,UP_REG};
class WelComeFace : public CDialogEx
{
	DECLARE_DYNAMIC(WelComeFace)

public:
	WelComeFace(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~WelComeFace();

// 对话框数据
	enum { IDD = IDD_DLG_WELCOMEFACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonExit();
	CString m_uName;
	CString m_uPwd;
	UserOption up;
	Client * client;
	bool isConnectServer;
	afx_msg void OnBnClickedButtonOffline();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonReg();
	virtual BOOL OnInitDialog();
	bool isFrist;
	CButton m_btn_login;
};
