#if !defined(AFX_DLGINPUTBOX_H__COMPUTERGRAPHICS__INCLUDED_)
#define AFX_DLGINPUTBOX_H__COMPUTERGRAPHICS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInputBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgInputBox dialog

class DlgInputBox : public CDialog
{
// Construction
public:
	CString GetInputText();
	DlgInputBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgInputBox)
	enum { IDD = IDD_DLG_INPUTBOX };
	CString	m_strInputTips;
	CString	m_strInputText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgInputBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgInputBox)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINPUTBOX_H__COMPUTERGRAPHICS__INCLUDED_)
