
// 01-��ͼ����ģ��View.h : CMy01��ͼ����ģ��View ��Ľӿ�
//

#pragma once
#include "atltypes.h"


class CMy01��ͼ����ģ��View : public CView
{
protected: // �������л�����
	CMy01��ͼ����ģ��View();
	DECLARE_DYNCREATE(CMy01��ͼ����ģ��View)

// ����
public:
	CMy01��ͼ����ģ��Doc* GetDocument() const;

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
	virtual ~CMy01��ͼ����ģ��View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	CPoint m_Point;
	bool isLDown;
	bool canDraw;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	int drawType;
	CPoint m_points[300];
	CPoint m_cirhu[3];
public:
	afx_msg void OnSelectPoint();
	afx_msg void OnSelectRecttangle();
	afx_msg void OnSelectElispe();
	afx_msg void OnSelectCircleLine();
	afx_msg void OnSelectLine();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSelectClearLine();
	afx_msg void OnSelectPolygon();
private:
	int pslen;
public:
	afx_msg void OnSelectRadiate();
	afx_msg void OnSelectHu();
	afx_msg void OnSelectClear();
	afx_msg void OnSelectRoundRect();
private:
	int m_hulen;
public:
	afx_msg void OnSelectBrush();
	afx_msg void OnSelectBigPoint();
	afx_msg void OnSelectStar();
};

#ifndef _DEBUG  // 01-��ͼ����ģ��View.cpp �еĵ��԰汾
inline CMy01��ͼ����ģ��Doc* CMy01��ͼ����ģ��View::GetDocument() const
   { return reinterpret_cast<CMy01��ͼ����ģ��Doc*>(m_pDocument); }
#endif

