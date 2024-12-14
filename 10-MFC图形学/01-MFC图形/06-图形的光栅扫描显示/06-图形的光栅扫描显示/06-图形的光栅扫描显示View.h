
// 06-图形的光栅扫描显示View.h : CMy06图形的光栅扫描显示View 类的接口
//

#pragma once
#include "atltypes.h"


class CMy06图形的光栅扫描显示View : public CView
{
public:
	CPoint p0;	//直线起点
	CPoint p1;	//直线终点
	COLORREF m_lineColor;	//直线颜色
	COLORREF m_FillColor;	//填充颜色
	bool m_isAntiAlias;	//绘制直线方式，是否反走样
	// DDA数值微分算法画直线
	void DDALine(CPoint p1, CPoint p2, COLORREF color);
	// 反走样直线绘制
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
protected: // 仅从序列化创建
	CMy06图形的光栅扫描显示View();
	DECLARE_DYNCREATE(CMy06图形的光栅扫描显示View)

// 特性
public:
	CMy06图形的光栅扫描显示Doc* GetDocument() const;

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
	virtual ~CMy06图形的光栅扫描显示View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 06-图形的光栅扫描显示View.cpp 中的调试版本
inline CMy06图形的光栅扫描显示Doc* CMy06图形的光栅扫描显示View::GetDocument() const
   { return reinterpret_cast<CMy06图形的光栅扫描显示Doc*>(m_pDocument); }
#endif

