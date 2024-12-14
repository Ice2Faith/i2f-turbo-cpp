#if !defined(AFX_DLGLIGHTSETTING_H__COMPUTERGRAPHICS__INCLUDED_)
#define AFX_DLGLIGHTSETTING_H__COMPUTERGRAPHICS__INCLUDED_

#include "GLighting.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLightSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgLightSetting dialog

class DlgLightSetting : public CDialog
{
// Construction
public:
	D3Light GetLight();
	DlgLightSetting(CWnd* pParent = NULL);   // standard constructor
	D3Material lg_mate;
// Dialog Data
	//{{AFX_DATA(DlgLightSetting)
	enum { IDD = IDD_DLG_LIGHT };
	BOOL	m_gold;
	BOOL	m_greenstone;
	BOOL	m_redstone;
	BOOL	m_siver;
	double	m_c2;
	double	m_c1;
	double	m_c0;
	int		m_x;
	int		m_y;
	int		m_z;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgLightSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgLightSetting)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLIGHTSETTING_H__COMPUTERGRAPHICS__INCLUDED_)
