
// �ƽ���Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// C�ƽ���Dlg �Ի���
class C�ƽ���Dlg : public CDialogEx
{
// ����
public:
	C�ƽ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	CButton m_btn_creack;
	afx_msg void OnBnClickedButtonCreack();
};
