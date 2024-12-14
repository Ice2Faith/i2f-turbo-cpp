
// 06-ͼ�εĹ�դɨ����ʾView.h : CMy06ͼ�εĹ�դɨ����ʾView ��Ľӿ�
//

#pragma once
#include "atltypes.h"


class CMy06ͼ�εĹ�դɨ����ʾView : public CView
{
public:
	CPoint p0;	//ֱ�����
	CPoint p1;	//ֱ���յ�
	COLORREF m_lineColor;	//ֱ����ɫ
	COLORREF m_FillColor;	//�����ɫ
	bool m_isAntiAlias;	//����ֱ�߷�ʽ���Ƿ�����
	// DDA��ֵ΢���㷨��ֱ��
	void DDALine(CPoint p1, CPoint p2, COLORREF color);
	// ������ֱ�߻���
	void AntialiasLine(CPoint p1, CPoint p2, COLORREF fgc, COLORREF bgc);
	void SeedFillPoly(CPoint seed, COLORREF bgc, COLORREF flc);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClrLineRed();
	afx_msg void OnClrLineGreen();
	afx_msg void OnClrLineBlue();
	afx_msg void OnClrLineBalck();
	afx_msg void OnClrFillRed();
	afx_msg void OnClrFillGreen();
	afx_msg void OnClrFillBlue();
	afx_msg void OnClrFillBlack();
	afx_msg void OnClrLineWhite();
	afx_msg void OnClrFillWhite();
	afx_msg void OnStlDda();
	afx_msg void OnStlAntialias();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPanelClean();
protected: // �������л�����
	CMy06ͼ�εĹ�դɨ����ʾView();
	DECLARE_DYNCREATE(CMy06ͼ�εĹ�դɨ����ʾView)

// ����
public:
	CMy06ͼ�εĹ�դɨ����ʾDoc* GetDocument() const;

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
	virtual ~CMy06ͼ�εĹ�դɨ����ʾView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 06-ͼ�εĹ�դɨ����ʾView.cpp �еĵ��԰汾
inline CMy06ͼ�εĹ�դɨ����ʾDoc* CMy06ͼ�εĹ�դɨ����ʾView::GetDocument() const
   { return reinterpret_cast<CMy06ͼ�εĹ�դɨ����ʾDoc*>(m_pDocument); }
#endif

