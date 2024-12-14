
// 18-列表框Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMy18列表框Dlg 对话框
class CMy18列表框Dlg : public CDialogEx
{
// 构造
public:
	CMy18列表框Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY18_DIALOG };

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
	CString m_edt_str;
	CListBox m_lsb_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton3();
	CComboBox m_cbb_box;
	afx_msg void OnBnClickedButton4();
};
