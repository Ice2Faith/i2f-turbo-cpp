
// 04-�¼���ҵView.h : CMy04�¼���ҵView ��Ľӿ�
//

#pragma once


class CMy04�¼���ҵView : public CView
{
protected: // �������л�����
	CMy04�¼���ҵView();
	DECLARE_DYNCREATE(CMy04�¼���ҵView)

// ����
public:
	CMy04�¼���ҵDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMy04�¼���ҵView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // 04-�¼���ҵView.cpp �еĵ��԰汾
inline CMy04�¼���ҵDoc* CMy04�¼���ҵView::GetDocument() const
   { return reinterpret_cast<CMy04�¼���ҵDoc*>(m_pDocument); }
#endif

