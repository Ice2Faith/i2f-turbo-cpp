
// Win10��͸��Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#define ID_TIMER_LOOP 0x1001

// CWin10��͸��Dlg �Ի���
class CWin10��͸��Dlg : public CDialogEx
{
// ����
public:
	CWin10��͸��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WIN10_DIALOG };

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
	BOOL SetTransParent(HWND mHwnd, float alpha);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL m_ck_explorer;
	BOOL m_ck_ctrlcenter;
	BOOL m_ck_startmenu;
	BOOL m_ck_winsearch;
	BOOL m_ck_notifyicon;
	afx_msg void OnBnClickedButtonUse();
	CButton m_ck_all;
	afx_msg void OnBnClickedCheckCkall();
	BOOL m_ck_console;
	BOOL m_ck_notepad;
	BOOL m_ck_win7cal;
	BOOL m_ck_run;
};
