#if !defined(AFX_DLGOPERATIONTIPS_H__COMPUTERGRAPHICS__INCLUDED_)
#define AFX_DLGOPERATIONTIPS_H__COMPUTERGRAPHICS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOperationTips.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgOperationTips dialog

class DlgOperationTips : public CDialog
{
// Construction
public:
	DlgOperationTips(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgOperationTips)
	enum { IDD = IDD_DLG_OPERATIONTIPS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgOperationTips)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgOperationTips)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPERATIONTIPS_H__COMPUTERGRAPHICS__INCLUDED_)
