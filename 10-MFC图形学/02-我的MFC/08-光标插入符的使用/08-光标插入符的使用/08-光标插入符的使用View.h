
// 08-���������ʹ��View.h : CMy08���������ʹ��View ��Ľӿ�
//

#pragma once
#include "atltypes.h"


class CMy08���������ʹ��View : public CView
{
protected: // �������л�����
	CMy08���������ʹ��View();
	DECLARE_DYNCREATE(CMy08���������ʹ��View)

// ����
public:
	CMy08���������ʹ��Doc* GetDocument() const;

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
	virtual ~CMy08���������ʹ��View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	CPoint m_myPoint;
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	CString m_string;
};

#ifndef _DEBUG  // 08-���������ʹ��View.cpp �еĵ��԰汾
inline CMy08���������ʹ��Doc* CMy08���������ʹ��View::GetDocument() const
   { return reinterpret_cast<CMy08���������ʹ��Doc*>(m_pDocument); }
#endif

