
// 17-服务相关编程-服务管理器Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CMy17服务相关编程服务管理器Dlg 对话框
class CMy17服务相关编程服务管理器Dlg : public CDialogEx
{
// 构造
public:
	CMy17服务相关编程服务管理器Dlg(CWnd* pParent = NULL);	// 标准构造函数

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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CListCtrl m_list_service;
	afx_msg void OnBnClickedRadioWinapp();
	afx_msg void OnBnClickedRadioDrive();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonBan();
	unsigned long m_display_type;
	void InitView();
	void UpdateList(unsigned long serviceType);
	afx_msg void OnBnClickedRadioAllsvc();
	afx_msg void OnLvnColumnclickListService(NMHDR *pNMHDR, LRESULT *pResult);
};
