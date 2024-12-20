
// PgmAsisDlg.h : 头文件
//

#pragma once


// CPgmAsisDlg 对话框
class CPgmAsisDlg : public CDialogEx
{
// 构造
public:
	CPgmAsisDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PGMASIS_DIALOG };

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
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonDoit();
	CString m_str_input;
	CString m_str_output;
	void InitControls();
	void makeCHeader();
	void makeInPath();
	void makeOutPath();
	void makeInText();
	void makeOutText();
	void makeGetSetMethod();
	void makeClass();
	void makeSwitch();
	void makeIfElseIf();
	void makeStrToArray();
	void makeValueArray();
	afx_msg void OnBnClickedButtonClean();
};
