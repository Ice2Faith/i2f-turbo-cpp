
// 05-Bezier曲线绘制View.h : CMy05Bezier曲线绘制View 类的接口
//

#pragma once


class CMy05Bezier曲线绘制View : public CView
{
protected: // 仅从序列化创建
	CMy05Bezier曲线绘制View();
	DECLARE_DYNCREATE(CMy05Bezier曲线绘制View)

// 特性
public:
	CMy05Bezier曲线绘制Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy05Bezier曲线绘制View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // 05-Bezier曲线绘制View.cpp 中的调试版本
inline CMy05Bezier曲线绘制Doc* CMy05Bezier曲线绘制View::GetDocument() const
   { return reinterpret_cast<CMy05Bezier曲线绘制Doc*>(m_pDocument); }
#endif

