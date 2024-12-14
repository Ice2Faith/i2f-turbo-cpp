
// U盘防护精灵Dlg.h : 头文件
//

#pragma once


// CU盘防护精灵Dlg 对话框
class CU盘防护精灵Dlg : public CDialogEx
{
// 构造
public:
	CU盘防护精灵Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_U_DIALOG };

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

	//afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);//手动添加设备变化响应函数个消息映射
	afx_msg LRESULT OnDeviceChange(WPARAM nEventType, LPARAM dwData);

	afx_msg void OnBnClickedButtonSafeOpen();
	afx_msg void OnBnClickedButtonImmuneAutorun();
	afx_msg void OnBnClickedExitPro();
	afx_msg void OnBnClickedHideToBack();

	char GetDriverDisk(DWORD dwData);
	void ShowWindowInDeskRightDown(bool fullDisplay=true);
	void DeleteAutoRunOpenFile(CString autorunDirPath);
	CString m_SafeOpenPath;
	char m_curDiskFlag;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPlugoutUdisk();
	afx_msg void OnBnClickedButtonChoicePlugDevice();
};
