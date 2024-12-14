#pragma once
#include "afxwin.h"


// MyInputBox 对话框

class MyInputBox : public CDialogEx
{
	DECLARE_DYNAMIC(MyInputBox)

public:
	MyInputBox(CWnd* pParent = NULL);   // 标准构造函数
	MyInputBox(CString tips,CWnd* pParent = NULL);
	virtual ~MyInputBox();

// 对话框数据
	enum { IDD = IDD_DIALOG_INPUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CString m_tipsContext;
	CString m_inputContext;
	afx_msg void OnBnClickedOk();
	CEdit m_edit_input;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
