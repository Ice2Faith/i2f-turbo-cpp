
// 31-Ŀ¼��ع���Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMy31Ŀ¼��ع���Dlg �Ի���
class CMy31Ŀ¼��ع���Dlg : public CDialogEx
{
// ����
public:
	CMy31Ŀ¼��ع���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY31_DIALOG };

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
	CString m_strSpyPath;
	CListCtrl m_list_spy_log;
	afx_msg void OnBnClickedButtonSpyOn();
	afx_msg void OnBnClickedButtonSpyOff();
	void InitFaceControl();
	HANDLE hThread;
	CButton m_btn_spyon;
	CButton m_btn_spyoff;
	afx_msg void OnBnClickedButtonClearList();
};
