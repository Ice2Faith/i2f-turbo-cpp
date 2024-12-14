
// HIPS��Ϊ��ع���Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CHIPS��Ϊ��ع���Dlg �Ի���
class CHIPS��Ϊ��ع���Dlg : public CDialogEx
{
// ����
public:
	CHIPS��Ϊ��ع���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HIPS_DIALOG };

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
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	void InitControls();
	CButton m_btn_spyon;
	CButton m_btn_spyoff;
	CListCtrl m_list_hips_log;
	afx_msg void OnBnClickedButtonSpyOn();
	afx_msg void OnBnClickedButtonSpyOff();
	afx_msg void OnBnClickedButtonClearLog();
	HMODULE m_hInst;
};
