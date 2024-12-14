
// 35-端口扫描技术Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMy35端口扫描技术Dlg 对话框
class CMy35端口扫描技术Dlg : public CDialogEx
{
// 构造
public:
	CMy35端口扫描技术Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY35_DIALOG };

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
	CButton m_btnScan;
	CIPAddressCtrl m_ipAddrStart;
	CIPAddressCtrl m_ipAddrEnd;
	CString m_strHostName;
	CIPAddressCtrl m_ipAddrTranlated;
	int m_iportStart;
	int m_iportEnd;
	CTreeCtrl m_tree_info;
	afx_msg void OnBnClickedButtonTranslate();
	afx_msg void OnBnClickedButtonScan();

	void InitControls();
	int m_iTimeout;
};
