#if !defined(AFX_DLGCOLORSETTING_H__DAD3A940_EA5F_47E4_97B5_125EFAD13C0E__INCLUDED_)
#define AFX_DLGCOLORSETTING_H__DAD3A940_EA5F_47E4_97B5_125EFAD13C0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgColorSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgColorSetting dialog

class DlgColorSetting : public CDialog
{
// Construction
public:
	COLORREF GetColor();
	DlgColorSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgColorSetting)
	enum { IDD = IDD_DLG_COLOR };
	CSliderCtrl	m_scBlue;
	CSliderCtrl	m_scGreen;
	CSliderCtrl	m_scRed;
	int		m_blue;
	int		m_green;
	int		m_red;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgColorSetting)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgColorSetting)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOLORSETTING_H__DAD3A940_EA5F_47E4_97B5_125EFAD13C0E__INCLUDED_)
