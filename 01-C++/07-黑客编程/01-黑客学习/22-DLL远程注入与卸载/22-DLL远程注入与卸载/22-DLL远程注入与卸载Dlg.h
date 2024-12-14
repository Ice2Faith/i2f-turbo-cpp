
// 22-DLL远程注入与卸载Dlg.h : 头文件
//

#pragma once


// CMy22DLL远程注入与卸载Dlg 对话框
class CMy22DLL远程注入与卸载Dlg : public CDialogEx
{
// 构造
public:
	CMy22DLL远程注入与卸载Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY22DLL_DIALOG };

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
	afx_msg void OnBnClickedButtonEnterdll();
	afx_msg void OnBnClickedButtonLeavedll();
	DWORD GetProcessId(TCHAR * szProcessName);
	VOID InjectDLL(DWORD dwpid, char * szDllName);
	void UnInjectDll(DWORD dwpid, TCHAR * szDLLName);
};
