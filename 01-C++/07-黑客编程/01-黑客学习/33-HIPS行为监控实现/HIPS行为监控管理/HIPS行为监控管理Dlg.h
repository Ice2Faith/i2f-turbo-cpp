
// HIPS行为监控管理Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CHIPS行为监控管理Dlg 对话框
class CHIPS行为监控管理Dlg : public CDialogEx
{
// 构造
public:
	CHIPS行为监控管理Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HIPS_DIALOG };

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
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	void InitControls();
	CButton m_btn_spyon;
	CButton m_btn_spyoff;
	CListCtrl m_list_hips_log;
	afx_msg void OnBnClickedButtonSpyOn();
	afx_msg void OnBnClickedButtonSpyOff();
	afx_msg void OnBnClickedButtonClearLog();
	HMODULE m_hInst;
};
