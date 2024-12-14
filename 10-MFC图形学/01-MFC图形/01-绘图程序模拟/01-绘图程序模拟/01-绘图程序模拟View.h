
// 01-绘图程序模拟View.h : CMy01绘图程序模拟View 类的接口
//

#pragma once
#include "atltypes.h"


class CMy01绘图程序模拟View : public CView
{
protected: // 仅从序列化创建
	CMy01绘图程序模拟View();
	DECLARE_DYNCREATE(CMy01绘图程序模拟View)

// 特性
public:
	CMy01绘图程序模拟Doc* GetDocument() const;

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
	virtual ~CMy01绘图程序模拟View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // 01-绘图程序模拟View.cpp 中的调试版本
inline CMy01绘图程序模拟Doc* CMy01绘图程序模拟View::GetDocument() const
   { return reinterpret_cast<CMy01绘图程序模拟Doc*>(m_pDocument); }
#endif

