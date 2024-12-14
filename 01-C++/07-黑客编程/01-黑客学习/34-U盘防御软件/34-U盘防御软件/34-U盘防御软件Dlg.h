
// 34-U盘防御软件Dlg.h : 头文件
//

#pragma once
#define TIMER_FRIST_LOAD 0x101

// CMy34U盘防御软件Dlg 对话框
class CMy34U盘防御软件Dlg : public CDialogEx
{
// 构造
public:
	CMy34U盘防御软件Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY34U_DIALOG };

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
	//afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);//手动添加设备变化响应函数个消息映射
	afx_msg LRESULT OnDeviceChange(WPARAM nEventType, LPARAM dwData);
	char GetDriverDisk(DWORD dwData);
	afx_msg void OnBnClickedButtonSafeOpen();
	CString m_SafeOpenPath;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ShowWindowInDeskRightDown();
	afx_msg void OnBnClickedButtonTrulyClose();
	afx_msg void OnBnClickedButtonHidewnd();
	void DeleteAutoRunOpenFile(CString autorunDirPath);
};
