#pragma once
#include "afxwin.h"


// MyInputBox �Ի���

class MyInputBox : public CDialogEx
{
	DECLARE_DYNAMIC(MyInputBox)

public:
	MyInputBox(CWnd* pParent = NULL);   // ��׼���캯��
	MyInputBox(CString tips,CWnd* pParent = NULL);
	virtual ~MyInputBox();

// �Ի�������
	enum { IDD = IDD_DIALOG_INPUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CString m_tipsContext;
	CString m_inputContext;
	afx_msg void OnBnClickedOk();
	CEdit m_edit_input;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
