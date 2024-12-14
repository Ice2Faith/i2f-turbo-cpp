
// 16-编辑区使用Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMy16编辑区使用Dlg 对话框
class CMy16编辑区使用Dlg : public CDialogEx
{
// 构造
public:
	CMy16编辑区使用Dlg(CWnd* pParent = NULL);	// 标准构造函数

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
private:
	CEdit m_editfrom;
	CEdit m_editto;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_strfrom;
	CString m_strto;
};
