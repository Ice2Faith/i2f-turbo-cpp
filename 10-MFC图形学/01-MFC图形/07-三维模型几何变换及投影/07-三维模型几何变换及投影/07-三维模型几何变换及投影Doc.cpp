
// 07-��άģ�ͼ��α任��ͶӰDoc.cpp : CMy07��άģ�ͼ��α任��ͶӰDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "07-��άģ�ͼ��α任��ͶӰ.h"
#endif

#include "07-��άģ�ͼ��α任��ͶӰDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy07��άģ�ͼ��α任��ͶӰDoc

IMPLEMENT_DYNCREATE(CMy07��άģ�ͼ��α任��ͶӰDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy07��άģ�ͼ��α任��ͶӰDoc, CDocument)
END_MESSAGE_MAP()


// CMy07��άģ�ͼ��α任��ͶӰDoc ����/����

CMy07��άģ�ͼ��α任��ͶӰDoc::CMy07��άģ�ͼ��α任��ͶӰDoc()
{
	// TODO:  �ڴ����һ���Թ������

}

CMy07��άģ�ͼ��α任��ͶӰDoc::~CMy07��άģ�ͼ��α任��ͶӰDoc()
{
}

BOOL CMy07��άģ�ͼ��α任��ͶӰDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMy07��άģ�ͼ��α任��ͶӰDoc ���л�

void CMy07��άģ�ͼ��α任��ͶӰDoc::Serialize(CArchive& ar)
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
void CMy07��άģ�ͼ��α任��ͶӰDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMy07��άģ�ͼ��α任��ͶӰDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMy07��άģ�ͼ��α任��ͶӰDoc::SetSearchContent(const CString& value)
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

// CMy07��άģ�ͼ��α任��ͶӰDoc ���

#ifdef _DEBUG
void CMy07��άģ�ͼ��α任��ͶӰDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy07��άģ�ͼ��α任��ͶӰDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy07��άģ�ͼ��α任��ͶӰDoc ����
