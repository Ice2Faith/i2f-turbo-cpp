
// 快捷重启Dlg.h : 头文件
//

#pragma once


// C快捷重启Dlg 对话框
class C快捷重启Dlg : public CDialogEx
{
// 构造
private:
	char disk;
	short OpeMode;
	short TimeMode;
	int TimeCount;
	WCHAR COpeMode[2][20];
	WCHAR CTimeMode[3][20];
	void HideSystem(char * mind);
public:
	C快捷重启Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	void UpdateDisplay();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonShutdown();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonReboot();
	afx_msg void OnBnClickedButtonLock();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonStartope();
	afx_msg void OnBnClickedButtonTimemode();
	afx_msg void OnBnClickedButtonMode();
	afx_msg void OnBnClickedButtonCmd();
	afx_msg void OnBnClickedButtonPowershell();
	afx_msg void OnBnClickedButtonRegedit();
	afx_msg void OnBnClickedButtonImmuautorun();
	afx_msg void OnBnClickedButtonUpdisk();
	afx_msg void OnBnClickedButtonDowndisk();
};
