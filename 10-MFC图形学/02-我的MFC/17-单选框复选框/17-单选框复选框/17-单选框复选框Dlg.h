
// 17-��ѡ��ѡ��Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMy17��ѡ��ѡ��Dlg �Ի���
class CMy17��ѡ��ѡ��Dlg : public CDialogEx
{
// ����
public:
	CMy17��ѡ��ѡ��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY17_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	CButton m_CKB_01;
	afx_msg void OnBnClickedButton2();
};
