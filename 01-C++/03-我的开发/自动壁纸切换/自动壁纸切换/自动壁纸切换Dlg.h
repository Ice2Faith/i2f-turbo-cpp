
// �Զ���ֽ�л�Dlg.h : ͷ�ļ�
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
// C�Զ���ֽ�л�Dlg �Ի���
class C�Զ���ֽ�л�Dlg : public CDialogEx
{
// ����
public:
	C�Զ���ֽ�л�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
