
// ��¼��֤ģ���ƽ�Dlg.h : ͷ�ļ�
//

#pragma once
#include"DlgLogin.h"

// C��¼��֤ģ���ƽ�Dlg �Ի���
class C��¼��֤ģ���ƽ�Dlg : public CDialogEx
{
private:
	DlgLogin logindlg;
// ����
public:
	C��¼��֤ģ���ƽ�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	CString m_loginInfo;
	afx_msg void OnBnClickedButtonRollonce();
	CString m_resultRoll;
};
