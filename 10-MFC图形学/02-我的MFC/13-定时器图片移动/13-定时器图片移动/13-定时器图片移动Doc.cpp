
// 13-��ʱ��ͼƬ�ƶ�Doc.cpp : CMy13��ʱ��ͼƬ�ƶ�Doc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "13-��ʱ��ͼƬ�ƶ�.h"
#endif

#include "13-��ʱ��ͼƬ�ƶ�Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy13��ʱ��ͼƬ�ƶ�Doc

IMPLEMENT_DYNCREATE(CMy13��ʱ��ͼƬ�ƶ�Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy13��ʱ��ͼƬ�ƶ�Doc, CDocument)
END_MESSAGE_MAP()


// CMy13��ʱ��ͼƬ�ƶ�Doc ����/����

CMy13��ʱ��ͼƬ�ƶ�Doc::CMy13��ʱ��ͼƬ�ƶ�Doc()
{
	// TODO:  �ڴ����һ���Թ������

}

CMy13��ʱ��ͼƬ�ƶ�Doc::~CMy13��ʱ��ͼƬ�ƶ�Doc()
{
}

BOOL CMy13��ʱ��ͼƬ�ƶ�Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMy13��ʱ��ͼƬ�ƶ�Doc ���л�

void CMy13��ʱ��ͼƬ�ƶ�Doc::Serialize(CArchive& ar)
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
void CMy13��ʱ��ͼƬ�ƶ�Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMy13��ʱ��ͼƬ�ƶ�Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMy13��ʱ��ͼƬ�ƶ�Doc::SetSearchContent(const CString& value)
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

// CMy13��ʱ��ͼƬ�ƶ�Doc ���

#ifdef _DEBUG
void CMy13��ʱ��ͼƬ�ƶ�Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy13��ʱ��ͼƬ�ƶ�Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy13��ʱ��ͼƬ�ƶ�Doc ����
