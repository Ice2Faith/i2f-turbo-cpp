
// 20-�б�ؼ�Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CMy20�б�ؼ�Dlg �Ի���
class CMy20�б�ؼ�Dlg : public CDialogEx
{
// ����
public:
	CMy20�б�ؼ�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY20_DIALOG };

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
	CListCtrl m_lstc_list;
};
