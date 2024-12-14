#if !defined(AFX_DLGGEOMODCREATESETTING_H__1F16396E_161D_4B13_B96D_B968B2FB4C1F__INCLUDED_)
#define AFX_DLGGEOMODCREATESETTING_H__1F16396E_161D_4B13_B96D_B968B2FB4C1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGeoModCreateSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGeoModCreateSetting dialog

class DlgGeoModCreateSetting : public CDialog
{
// Construction
public:
	DlgGeoModCreateSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGeoModCreateSetting)
	enum { IDD = IDD_DLG_GEOMODCREATE };
	double	m_a;
	int		m_bAngleCount;
	int		m_aAngleCount;
	double	m_h;
	int		m_hCount;
	double	m_r;
	int		m_rCount;
	double	m_r2;
	int		m_rAngleCount;
	int		m_Bezier_tCount;
	int		m_Bezier_rAngleCount;
	int		m_ballex_Level;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGeoModCreateSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGeoModCreateSetting)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGEOMODCREATESETTING_H__1F16396E_161D_4B13_B96D_B968B2FB4C1F__INCLUDED_)
