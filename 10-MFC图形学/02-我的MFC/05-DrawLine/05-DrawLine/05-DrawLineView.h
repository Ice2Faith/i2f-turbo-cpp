
// 05-DrawLineView.h : CMy05DrawLineView ��Ľӿ�
//

#pragma once
#include "atltypes.h"


class CMy05DrawLineView : public CView
{
protected: // �������л�����
	CMy05DrawLineView();
	DECLARE_DYNCREATE(CMy05DrawLineView)

// ����
public:
	CMy05DrawLineDoc* GetDocument() const;

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
	virtual ~CMy05DrawLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

private:
	/*ѡ�������࣬�Ҽ�����ӱ���*/
	CPoint m_myPoint;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	bool m_isPress;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 05-DrawLineView.cpp �еĵ��԰汾
inline CMy05DrawLineDoc* CMy05DrawLineView::GetDocument() const
   { return reinterpret_cast<CMy05DrawLineDoc*>(m_pDocument); }
#endif

