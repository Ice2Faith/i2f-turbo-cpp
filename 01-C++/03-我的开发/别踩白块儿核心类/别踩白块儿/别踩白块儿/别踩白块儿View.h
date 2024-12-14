
// 别踩白块儿View.h : C别踩白块儿View 类的接口
//

#pragma once
#include"DontTouchIt.h"
class C别踩白块儿View : public CView
{
private:
	enum GameMode{GM_CLASS,GM_DBHAND,GM_KEYBORD};
	DontTouchIt * game;
	CRect rect;
	GameMode m_gameMode;
	long m_useTime;
	bool m_randomColor;
protected: // 仅从序列化创建
	C别踩白块儿View();
	DECLARE_DYNCREATE(C别踩白块儿View)

// 特性
public:
	C别踩白块儿Doc* GetDocument() const;

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
	virtual ~C别踩白块儿View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnStartGame();
	afx_msg void OnModeClass();
	afx_msg void OnModeDhand();
	afx_msg void OnModeKeybord();
	afx_msg void OnStaticColor();
	afx_msg void OnRandomColor();
	
	afx_msg void OnOpenFinishTips();
	afx_msg void OnCloseFinishTips();
	bool m_openFinishTips;
};

#ifndef _DEBUG  // 别踩白块儿View.cpp 中的调试版本
inline C别踩白块儿Doc* C别踩白块儿View::GetDocument() const
   { return reinterpret_cast<C别踩白块儿Doc*>(m_pDocument); }
#endif

