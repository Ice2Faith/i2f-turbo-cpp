
// 35-�˿�ɨ�輼��Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMy35�˿�ɨ�輼��Dlg �Ի���
class CMy35�˿�ɨ�輼��Dlg : public CDialogEx
{
// ����
public:
	CMy35�˿�ɨ�輼��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY35_DIALOG };

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
	CButton m_btnScan;
	CIPAddressCtrl m_ipAddrStart;
	CIPAddressCtrl m_ipAddrEnd;
	CString m_strHostName;
	CIPAddressCtrl m_ipAddrTranlated;
	int m_iportStart;
	int m_iportEnd;
	CTreeCtrl m_tree_info;
	afx_msg void OnBnClickedButtonTranslate();
	afx_msg void OnBnClickedButtonScan();

	void InitControls();
	int m_iTimeout;
};
