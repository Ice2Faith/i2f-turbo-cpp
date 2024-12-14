
// ����������ͻ���View.h : C����������ͻ���View ��Ľӿ�
//

#pragma once
#include"Client.h"
#include"Gobang.h"
#include"WelComeFace.h"
#define WM_USER_ACCEPTMSG (WM_USER+101)
class C����������ͻ���View : public CView
{
public:
	afx_msg LRESULT OnUserAcceptMsg(WPARAM wParam, LPARAM lParam);
	Client *client;
	Gobang * game;
	bool OfflineGame;
	void DrawChess(int xIndex, int yIndex, COLORREF color);
	bool m_isTrunBlack;
protected: // �������л�����
	C����������ͻ���View();
	DECLARE_DYNCREATE(C����������ͻ���View)

// ����
public:
	C����������ͻ���Doc* GetDocument() const;

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
	virtual ~C����������ͻ���View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // ����������ͻ���View.cpp �еĵ��԰汾
inline C����������ͻ���Doc* C����������ͻ���View::GetDocument() const
   { return reinterpret_cast<C����������ͻ���Doc*>(m_pDocument); }
#endif

