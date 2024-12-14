
// 登录验证模拟破解Dlg.h : 头文件
//

#pragma once
#include"DlgLogin.h"

// C登录验证模拟破解Dlg 对话框
class C登录验证模拟破解Dlg : public CDialogEx
{
private:
	DlgLogin logindlg;
// 构造
public:
	C登录验证模拟破解Dlg(CWnd* pParent = NULL);	// 标准构造函数

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
	CString m_loginInfo;
	afx_msg void OnBnClickedButtonRollonce();
	CString m_resultRoll;
};
