// ComputerGraphicsDoc.cpp : implementation of the CComputerGraphicsDoc class
//

#include "stdafx.h"
#include "ComputerGraphics.h"

#include "ComputerGraphicsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsDoc

IMPLEMENT_DYNCREATE(CComputerGraphicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CComputerGraphicsDoc, CDocument)
	//{{AFX_MSG_MAP(CComputerGraphicsDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsDoc construction/destruction

CComputerGraphicsDoc::CComputerGraphicsDoc()
{
	// TODO: add one-time construction code here

}

CComputerGraphicsDoc::~CComputerGraphicsDoc()
{
}

BOOL CComputerGraphicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsDoc serialization

void CComputerGraphicsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsDoc diagnostics

#ifdef _DEBUG
void CComputerGraphicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CComputerGraphicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CComputerGraphicsDoc commands

void CComputerGraphicsDoc::SetTitle(LPCTSTR lpszTitle) 
{
	CDocument::SetTitle("Computer Graphics v1.0.0.1");
}
