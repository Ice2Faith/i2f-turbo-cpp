
// 17-单选框复选框Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMy17单选框复选框Dlg 对话框
class CMy17单选框复选框Dlg : public CDialogEx
{
// 构造
public:
	CMy17单选框复选框Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY17_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	CButton m_CKB_01;
	afx_msg void OnBnClickedButton2();
};
