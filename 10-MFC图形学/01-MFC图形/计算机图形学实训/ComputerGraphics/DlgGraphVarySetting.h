#if !defined(AFX_DLGGRAPHVARYSETTING_H__COMPUTERGRAPHICS__INCLUDED_)
#define AFX_DLGGRAPHVARYSETTING_H__COMPUTERGRAPHICS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGraphVarySetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGraphVarySetting dialog

class DlgGraphVarySetting : public CDialog
{
// Construction
public:
	DlgGraphVarySetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGraphVarySetting)
	enum { IDD = IDD_DLG_GVARY };
	BOOL	m_FlatRef_xoy;
	BOOL	m_FlatRef_xoz;
	BOOL	m_FlatRef_yoz;
	BOOL	m_Reflact_x;
	BOOL	m_Reflact_y;
	BOOL	m_Reflact_z;
	int		m_Miscut_xdy;
	int		m_Miscut_xgz;
	int		m_Miscut_ybx;
	int		m_Miscut_yhz;
	int		m_Miscut_zfy;
	int		m_Miscut_zcx;
	int		m_Move_x;
	int		m_Move_y;
	int		m_Move_z;
	double	m_Scale_x;
	double	m_Scale_y;
	double	m_Scale_z;
	int		m_Spin_x;
	int		m_Spin_y;
	int		m_Spin_z;
	int		m_aAngle;
	int		m_bAngle;
	int		m_d;
	int		m_Far;
	int		m_R;
	int		m_Near;
	BOOL	m_Switch_Miscut;
	BOOL	m_Switch_Move;
	BOOL	m_Switch_Reflact;
	BOOL	m_Switch_Scale;
	BOOL	m_Switch_Spin;
	BOOL	m_Switch_FlatRef;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGraphVarySetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGraphVarySetting)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGRAPHVARYSETTING_H__COMPUTERGRAPHICS__INCLUDED_)
