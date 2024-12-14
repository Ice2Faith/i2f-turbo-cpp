
// 16-注册表操作-启动项管理Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CMy16注册表操作启动项管理Dlg 对话框
class CMy16注册表操作启动项管理Dlg : public CDialogEx
{
// 构造
public:
	CMy16注册表操作启动项管理Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY16_DIALOG };

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
	CListCtrl m_list_bootload;
	void InitListControl();
	void UpdateBootRunList();
	afx_msg void OnBnClickedButtonAddboot();
	afx_msg void OnBnClickedButtonDelboot();
	afx_msg void OnBnClickedButtonCpkey();
};
