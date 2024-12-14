
// 08-光标插入符的使用View.h : CMy08光标插入符的使用View 类的接口
//

#pragma once
#include "atltypes.h"


class CMy08光标插入符的使用View : public CView
{
protected: // 仅从序列化创建
	CMy08光标插入符的使用View();
	DECLARE_DYNCREATE(CMy08光标插入符的使用View)

// 特性
public:
	CMy08光标插入符的使用Doc* GetDocument() const;

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
	virtual ~CMy08光标插入符的使用View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // 08-光标插入符的使用View.cpp 中的调试版本
inline CMy08光标插入符的使用Doc* CMy08光标插入符的使用View::GetDocument() const
   { return reinterpret_cast<CMy08光标插入符的使用Doc*>(m_pDocument); }
#endif

