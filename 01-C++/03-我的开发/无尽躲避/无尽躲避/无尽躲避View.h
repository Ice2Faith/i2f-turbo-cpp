
// 无尽躲避View.h : C无尽躲避View 类的接口
//

#pragma once
#include"EvadeEndless.h"
#define ID_TIMER_GAME_FLUSH 0x101
class C无尽躲避View : public CView
{
private:
	EvadeEndless * game;
protected: // 仅从序列化创建
	C无尽躲避View();
	DECLARE_DYNCREATE(C无尽躲避View)

// 特性
public:
	C无尽躲避Doc* GetDocument() const;

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
	virtual ~C无尽躲避View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGameStart();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGameContinue();
};

#ifndef _DEBUG  // 无尽躲避View.cpp 中的调试版本
inline C无尽躲避Doc* C无尽躲避View::GetDocument() const
   { return reinterpret_cast<C无尽躲避Doc*>(m_pDocument); }
#endif

