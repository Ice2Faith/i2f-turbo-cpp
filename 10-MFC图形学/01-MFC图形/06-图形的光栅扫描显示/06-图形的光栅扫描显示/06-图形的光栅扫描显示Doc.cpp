
// 06-ͼ�εĹ�դɨ����ʾDoc.cpp : CMy06ͼ�εĹ�դɨ����ʾDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "06-ͼ�εĹ�դɨ����ʾ.h"
#endif

#include "06-ͼ�εĹ�դɨ����ʾDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy06ͼ�εĹ�դɨ����ʾDoc

IMPLEMENT_DYNCREATE(CMy06ͼ�εĹ�դɨ����ʾDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy06ͼ�εĹ�դɨ����ʾDoc, CDocument)
END_MESSAGE_MAP()


// CMy06ͼ�εĹ�դɨ����ʾDoc ����/����

CMy06ͼ�εĹ�դɨ����ʾDoc::CMy06ͼ�εĹ�դɨ����ʾDoc()
{
	// TODO:  �ڴ����һ���Թ������

}

CMy06ͼ�εĹ�դɨ����ʾDoc::~CMy06ͼ�εĹ�դɨ����ʾDoc()
{
}

BOOL CMy06ͼ�εĹ�դɨ����ʾDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMy06ͼ�εĹ�դɨ����ʾDoc ���л�

void CMy06ͼ�εĹ�դɨ����ʾDoc::Serialize(CArchive& ar)
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
void CMy06ͼ�εĹ�դɨ����ʾDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMy06ͼ�εĹ�դɨ����ʾDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMy06ͼ�εĹ�դɨ����ʾDoc::SetSearchContent(const CString& value)
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

// CMy06ͼ�εĹ�դɨ����ʾDoc ���

#ifdef _DEBUG
void CMy06ͼ�εĹ�դɨ����ʾDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy06ͼ�εĹ�դɨ����ʾDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy06ͼ�εĹ�դɨ����ʾDoc ����
