
// 17-������ر��-���������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CMy17������ر�̷��������Dlg �Ի���
class CMy17������ر�̷��������Dlg : public CDialogEx
{
// ����
public:
	CMy17������ر�̷��������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CListCtrl m_list_service;
	afx_msg void OnBnClickedRadioWinapp();
	afx_msg void OnBnClickedRadioDrive();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonBan();
	unsigned long m_display_type;
	void InitView();
	void UpdateList(unsigned long serviceType);
	afx_msg void OnBnClickedRadioAllsvc();
	afx_msg void OnLvnColumnclickListService(NMHDR *pNMHDR, LRESULT *pResult);
};
