
// 16-ע������-���������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CMy16ע���������������Dlg �Ի���
class CMy16ע���������������Dlg : public CDialogEx
{
// ����
public:
	CMy16ע���������������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY16_DIALOG };

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
	CListCtrl m_list_bootload;
	void InitListControl();
	void UpdateBootRunList();
	afx_msg void OnBnClickedButtonAddboot();
	afx_msg void OnBnClickedButtonDelboot();
	afx_msg void OnBnClickedButtonCpkey();
};
