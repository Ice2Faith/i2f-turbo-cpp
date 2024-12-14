// ComputerGraphics.h : main header file for the ComputerGraphics application
//

#if !defined(AFX__H__COMPUTERGRAPHICS__INCLUDED_)
#define AFX__H__COMPUTERGRAPHICS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsApp:
// See ComputerGraphics.cpp for the implementation of this class
//

class CComputerGraphicsApp : public CWinApp
{
public:
	CComputerGraphicsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComputerGraphicsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CComputerGraphicsApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__H__COMPUTERGRAPHICS__INCLUDED_)
