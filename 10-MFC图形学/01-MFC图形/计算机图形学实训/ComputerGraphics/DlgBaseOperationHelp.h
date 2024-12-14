#if !defined(AFX_DLGBASEOPERATIONHELP_H__F1718182_1EA7_4196_AB85_D2D153DB4944__INCLUDED_)
#define AFX_DLGBASEOPERATIONHELP_H__F1718182_1EA7_4196_AB85_D2D153DB4944__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBaseOperationHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgBaseOperationHelp dialog

class DlgBaseOperationHelp : public CDialog
{
// Construction
public:
	DlgBaseOperationHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgBaseOperationHelp)
	enum { IDD = IDD_DLG_BASEOPE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgBaseOperationHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgBaseOperationHelp)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBASEOPERATIONHELP_H__F1718182_1EA7_4196_AB85_D2D153DB4944__INCLUDED_)
