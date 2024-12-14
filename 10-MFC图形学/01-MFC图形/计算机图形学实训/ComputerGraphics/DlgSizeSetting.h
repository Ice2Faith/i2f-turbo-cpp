#if !defined(AFX_DLGSIZESETTING_H__COMPUTERGRAPHICS__INCLUDED_)
#define AFX_DLGSIZESETTING_H__COMPUTERGRAPHICS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSizeSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSizeSetting dialog

class DlgSizeSetting : public CDialog
{
// Construction
public:
	int GetSize();
	int m_Size;
	DlgSizeSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSizeSetting)
	enum { IDD = IDD_DLG_SIZE };
	CSliderCtrl	m_scSize;
	int		m_size;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSizeSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSizeSetting)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSIZESETTING_H__COMPUTERGRAPHICS__INCLUDED_)
