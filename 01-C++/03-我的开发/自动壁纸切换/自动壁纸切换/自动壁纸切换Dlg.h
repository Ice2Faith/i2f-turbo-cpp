
// 自动壁纸切换Dlg.h : 头文件
//

#pragma once
#include "afxeditbrowsectrl.h"
#include<time.h>
#include<stdlib.h>
#include <comdef.h>
#include <objbase.h>
#include <shlobj.h>
#include "afxwin.h"
#define MAX_LEVEL 10
#define ID_TIMER_NEXT_PIC 0x1001
// C自动壁纸切换Dlg 对话框
class C自动壁纸切换Dlg : public CDialogEx
{
// 构造
public:
	C自动壁纸切换Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

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
	CMFCEditBrowseCtrl m_EBPicView;
	CComboBox m_CBWPStyle;
	CComboBox m_CBWTime;
	CButton m_CBBanPower;
	afx_msg void OnBnClickedCheckBanpower();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL SetWallpaper(WCHAR * strPicFile, DWORD dwStyle);
	bool LoadImgFilesInfo(TCHAR * dir);
	bool ProcessFile(TCHAR * file);
	int m_WPStyle;
	int m_WPWaitTime;
	CListBox m_LBImgList;
	bool m_isLoadFile;
};
