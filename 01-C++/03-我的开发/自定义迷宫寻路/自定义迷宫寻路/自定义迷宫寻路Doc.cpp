
// �Զ����Թ�Ѱ·Doc.cpp : C�Զ����Թ�Ѱ·Doc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "�Զ����Թ�Ѱ·.h"
#endif

#include "�Զ����Թ�Ѱ·Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// C�Զ����Թ�Ѱ·Doc

IMPLEMENT_DYNCREATE(C�Զ����Թ�Ѱ·Doc, CDocument)

BEGIN_MESSAGE_MAP(C�Զ����Թ�Ѱ·Doc, CDocument)
END_MESSAGE_MAP()


// C�Զ����Թ�Ѱ·Doc ����/����

C�Զ����Թ�Ѱ·Doc::C�Զ����Թ�Ѱ·Doc()
{
	// TODO:  �ڴ����һ���Թ������

}

C�Զ����Թ�Ѱ·Doc::~C�Զ����Թ�Ѱ·Doc()
{
}

BOOL C�Զ����Թ�Ѱ·Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// C�Զ����Թ�Ѱ·Doc ���л�

void C�Զ����Թ�Ѱ·Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void C�Զ����Թ�Ѱ·Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void C�Զ����Թ�Ѱ·Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void C�Զ����Թ�Ѱ·Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// C�Զ����Թ�Ѱ·Doc ���

#ifdef _DEBUG
void C�Զ����Թ�Ѱ·Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void C�Զ����Թ�Ѱ·Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// C�Զ����Թ�Ѱ·Doc ����
