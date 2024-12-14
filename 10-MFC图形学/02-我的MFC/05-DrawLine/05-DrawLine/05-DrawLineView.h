
// 05-DrawLineView.h : CMy05DrawLineView 类的接口
//

#pragma once
#include "atltypes.h"


class CMy05DrawLineView : public CView
{
protected: // 仅从序列化创建
	CMy05DrawLineView();
	DECLARE_DYNCREATE(CMy05DrawLineView)

// 特性
public:
	CMy05DrawLineDoc* GetDocument() const;

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
	virtual ~CMy05DrawLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

private:
	/*选中所属类，右键，添加变量*/
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

#ifndef _DEBUG  // 05-DrawLineView.cpp 中的调试版本
inline CMy05DrawLineDoc* CMy05DrawLineView::GetDocument() const
   { return reinterpret_cast<CMy05DrawLineDoc*>(m_pDocument); }
#endif

