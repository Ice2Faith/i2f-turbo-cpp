
// 15-AutoRun���߹���Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMy15AutoRun���߹���Dlg �Ի���
class CMy15AutoRun���߹���Dlg : public CDialogEx
{
// ����
public:
	CMy15AutoRun���߹���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY15AUTORUN_DIALOG };

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
	afx_msg void OnBnClickedCancel();

	CComboBox m_combox_drives;
	void InitComboxDrives();
	afx_msg void OnBnClickedButtonImmune();
	afx_msg void OnBnClickedButtonAntiimmune();
	afx_msg void OnBnClickedButtonCreatedir();
	afx_msg void OnBnClickedButtonDeletedir();
};
