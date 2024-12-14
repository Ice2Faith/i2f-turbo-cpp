
// 19-���̹�����Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMy19���̹�����Dlg �Ի���
class CMy19���̹�����Dlg : public CDialogEx
{
// ����
public:
	CMy19���̹�����Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY19_DIALOG };

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
	CListCtrl m_list_processes;
	CListCtrl m_list_dlls;
	void UpdateProcesses();
	void UpdateModules();
	void InitListControl();
	int GetSelectPID();
	afx_msg void OnBnClickedButtonViewDll();
	void UpgradeProcessPrivilege();
	afx_msg void OnBnClickedButtonWaitProcess();
	afx_msg void OnBnClickedButtonRecoveryProcess();
	afx_msg void OnBnClickedButtonStopProcess();
	CString m_create_process_path;
	afx_msg void OnBnClickedButtonCreateProcess();
	afx_msg void OnBnClickedButtonRefresh();
	CButton m_ckbox_image_redirect;
	afx_msg void OnBnClickedCheckImageredirect();
};
