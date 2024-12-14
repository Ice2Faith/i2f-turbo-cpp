
// 05-Bezier���߻���View.h : CMy05Bezier���߻���View ��Ľӿ�
//

#pragma once


class CMy05Bezier���߻���View : public CView
{
protected: // �������л�����
	CMy05Bezier���߻���View();
	DECLARE_DYNCREATE(CMy05Bezier���߻���View)

// ����
public:
	CMy05Bezier���߻���Doc* GetDocument() const;

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
	virtual ~CMy05Bezier���߻���View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_pointCount;
	CPoint m_points[1024];
	double Bernstein(int i, int n, double t);
	double BezierX(int n, double t, CPoint points[]);
	double BezierY(int n, double t, CPoint points[]);
	void DrawBezierLine();
	void ShowCtrlPoint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBezierBeginDraw();
	int m_state;
	afx_msg void OnBezierEditPoint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	bool m_isLDown;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int m_moveIndex;
};

#ifndef _DEBUG  // 05-Bezier���߻���View.cpp �еĵ��԰汾
inline CMy05Bezier���߻���Doc* CMy05Bezier���߻���View::GetDocument() const
   { return reinterpret_cast<CMy05Bezier���߻���Doc*>(m_pDocument); }
#endif

