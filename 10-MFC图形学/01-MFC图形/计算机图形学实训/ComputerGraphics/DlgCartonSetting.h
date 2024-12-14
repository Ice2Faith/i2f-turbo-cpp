#if !defined(AFX_DLGCARTONSETTING_H__917AB997_8BF9_4442_9D1A_0E54BC03B27C__INCLUDED_)
#define AFX_DLGCARTONSETTING_H__917AB997_8BF9_4442_9D1A_0E54BC03B27C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCartonSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCartonSetting dialog

class DlgCartonSetting : public CDialog
{
// Construction
public:
	DlgCartonSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCartonSetting)
	enum { IDD = IDD_DLG_CARTONSETTING };
	BOOL	m_openCarton;
	BOOL	m_spinX;
	BOOL	m_spinY;
	BOOL	m_spinZ;
	int		m_spinXup;
	int		m_spinYup;
	int		m_spinZup;
	int		m_updataTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCartonSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgCartonSetting)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCARTONSETTING_H__917AB997_8BF9_4442_9D1A_0E54BC03B27C__INCLUDED_)
