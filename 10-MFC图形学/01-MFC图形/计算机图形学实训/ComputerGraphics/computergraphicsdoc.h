// ComputerGraphicsDoc.h : interface of the CComputerGraphicsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOC_H__COMPUTERGRAPHICS__INCLUDED_)
#define AFX_DOC_H__COMPUTERGRAPHICS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CComputerGraphicsDoc : public CDocument
{
protected: // create from serialization only
	CComputerGraphicsDoc();
	DECLARE_DYNCREATE(CComputerGraphicsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComputerGraphicsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComputerGraphicsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CComputerGraphicsDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOC_H__COMPUTERGRAPHICS__INCLUDED_)
