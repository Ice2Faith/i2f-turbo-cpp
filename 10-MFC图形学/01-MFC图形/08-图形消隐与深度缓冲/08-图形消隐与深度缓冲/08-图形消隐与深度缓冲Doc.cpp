
// 08-图形消隐与深度缓冲Doc.cpp : CMy08图形消隐与深度缓冲Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "08-图形消隐与深度缓冲.h"
#endif

#include "08-图形消隐与深度缓冲Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy08图形消隐与深度缓冲Doc

IMPLEMENT_DYNCREATE(CMy08图形消隐与深度缓冲Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy08图形消隐与深度缓冲Doc, CDocument)
END_MESSAGE_MAP()


// CMy08图形消隐与深度缓冲Doc 构造/析构

CMy08图形消隐与深度缓冲Doc::CMy08图形消隐与深度缓冲Doc()
{
	// TODO:  在此添加一次性构造代码

}

CMy08图形消隐与深度缓冲Doc::~CMy08图形消隐与深度缓冲Doc()
{
}

BOOL CMy08图形消隐与深度缓冲Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMy08图形消隐与深度缓冲Doc 序列化

void CMy08图形消隐与深度缓冲Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy08图形消隐与深度缓冲Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CMy08图形消隐与深度缓冲Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMy08图形消隐与深度缓冲Doc::SetSearchContent(const CString& value)
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

// CMy08图形消隐与深度缓冲Doc 诊断

#ifdef _DEBUG
void CMy08图形消隐与深度缓冲Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy08图形消隐与深度缓冲Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy08图形消隐与深度缓冲Doc 命令
