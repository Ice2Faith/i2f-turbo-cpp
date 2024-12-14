
// 15-AutoRun免疫工具Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMy15AutoRun免疫工具Dlg 对话框
class CMy15AutoRun免疫工具Dlg : public CDialogEx
{
// 构造
public:
	CMy15AutoRun免疫工具Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY15AUTORUN_DIALOG };

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

	CComboBox m_combox_drives;
	void InitComboxDrives();
	afx_msg void OnBnClickedButtonImmune();
	afx_msg void OnBnClickedButtonAntiimmune();
	afx_msg void OnBnClickedButtonCreatedir();
	afx_msg void OnBnClickedButtonDeletedir();
};
