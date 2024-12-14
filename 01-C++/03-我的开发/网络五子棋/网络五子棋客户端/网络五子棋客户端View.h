
// 网络五子棋客户端View.h : C网络五子棋客户端View 类的接口
//

#pragma once
#include"Client.h"
#include"Gobang.h"
#include"WelComeFace.h"
#define WM_USER_ACCEPTMSG (WM_USER+101)
class C网络五子棋客户端View : public CView
{
public:
	afx_msg LRESULT OnUserAcceptMsg(WPARAM wParam, LPARAM lParam);
	Client *client;
	Gobang * game;
	bool OfflineGame;
	void DrawChess(int xIndex, int yIndex, COLORREF color);
	bool m_isTrunBlack;
protected: // 仅从序列化创建
	C网络五子棋客户端View();
	DECLARE_DYNCREATE(C网络五子棋客户端View)

// 特性
public:
	C网络五子棋客户端Doc* GetDocument() const;

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
	virtual ~C网络五子棋客户端View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNewGame();
	afx_msg void OnUndoGame();
	afx_msg void OnExitGame();
	afx_msg void OnSendTextMsg();
	afx_msg void OnBroadcastPlayer();
};

#ifndef _DEBUG  // 网络五子棋客户端View.cpp 中的调试版本
inline C网络五子棋客户端Doc* C网络五子棋客户端View::GetDocument() const
   { return reinterpret_cast<C网络五子棋客户端Doc*>(m_pDocument); }
#endif

