
// ��Ȱ׿��View.h : C��Ȱ׿��View ��Ľӿ�
//

#pragma once
#include"DontTouchIt.h"
class C��Ȱ׿��View : public CView
{
private:
	enum GameMode{GM_CLASS,GM_DBHAND,GM_KEYBORD};
	DontTouchIt * game;
	CRect rect;
	GameMode m_gameMode;
	long m_useTime;
	bool m_randomColor;
protected: // �������л�����
	C��Ȱ׿��View();
	DECLARE_DYNCREATE(C��Ȱ׿��View)

// ����
public:
	C��Ȱ׿��Doc* GetDocument() const;

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
	virtual ~C��Ȱ׿��View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // ��Ȱ׿��View.cpp �еĵ��԰汾
inline C��Ȱ׿��Doc* C��Ȱ׿��View::GetDocument() const
   { return reinterpret_cast<C��Ȱ׿��Doc*>(m_pDocument); }
#endif

