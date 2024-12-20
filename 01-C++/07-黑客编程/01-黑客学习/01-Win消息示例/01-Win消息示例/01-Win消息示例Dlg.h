
// 01-Win消息示例Dlg.h : 头文件
//

#pragma once


// CMy01Win消息示例Dlg 对话框
class CMy01Win消息示例Dlg : public CDialogEx
{
// 构造
public:
	CMy01Win消息示例Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY01WIN_DIALOG };

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
	afx_msg void OnBnClickedButtonCloseNotepad();
	afx_msg void OnBnClickedButtonOpenNotepad();
	afx_msg void OnBnClickedButtonSetNotepadTitle();
	afx_msg void OnBnClickedButtonGetNotepadTitle();
	CString m_title;
};
