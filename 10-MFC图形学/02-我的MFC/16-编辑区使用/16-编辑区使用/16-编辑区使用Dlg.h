
// 16-�༭��ʹ��Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMy16�༭��ʹ��Dlg �Ի���
class CMy16�༭��ʹ��Dlg : public CDialogEx
{
// ����
public:
	CMy16�༭��ʹ��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
private:
	CEdit m_editfrom;
	CEdit m_editto;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_strfrom;
	CString m_strto;
};
