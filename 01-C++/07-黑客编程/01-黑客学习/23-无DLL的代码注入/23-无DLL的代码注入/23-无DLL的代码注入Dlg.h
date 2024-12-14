
// 23-无DLL的代码注入Dlg.h : 头文件
//

#pragma once


// CMy23无DLL的代码注入Dlg 对话框
class CMy23无DLL的代码注入Dlg : public CDialogEx
{
// 构造
public:
	CMy23无DLL的代码注入Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY23DLL_DIALOG };

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
	afx_msg void OnBnClickedButtonInject();
	DWORD getProcessID(TCHAR * szProcessName);
	void InjectCode(DWORD dwpid);
};
