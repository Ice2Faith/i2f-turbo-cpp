#if !defined(AFX_DLGMATERIALSETTING_H__COMPUTERGRAPHICS__INCLUDED_)
#define AFX_DLGMATERIALSETTING_H__COMPUTERGRAPHICS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMaterialSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgMaterialSetting dialog
#include"GLighting.h"
class DlgMaterialSetting : public CDialog
{
	D3Material lg_mate;
// Construction
public:
	D3Material GetMaterial();
	DlgMaterialSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgMaterialSetting)
	enum { IDD = IDD_DLG_METERIAL };
	BOOL	m_gold;
	BOOL	m_greenstone;
	BOOL	m_redstone;
	BOOL	m_siver;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgMaterialSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgMaterialSetting)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMATERIALSETTING_H__COMPUTERGRAPHICS__INCLUDED_)
