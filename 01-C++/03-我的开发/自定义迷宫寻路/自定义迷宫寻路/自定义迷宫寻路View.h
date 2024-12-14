
// �Զ����Թ�Ѱ·View.h : C�Զ����Թ�Ѱ·View ��Ľӿ�
//

#pragma once
#include"AutoRouterCore.h"
#include "atltypes.h"

enum EditType{ET_Null,ET_Map,ET_Point,ET_Block};
class C�Զ����Թ�Ѱ·View : public CView
{
public:
	AutoRouterCore autoRouter;
	double blockWid;
	double blockHei;
	EditType editType;
	bool isRouting;
	bool isOpenAnimate;
	int TIMER_SLEEP;
	bool isDrawAllRoute;

	CRect lastUpdateArea;

protected: // �������л�����
	C�Զ����Թ�Ѱ·View();
	DECLARE_DYNCREATE(C�Զ����Թ�Ѱ·View)

// ����
public:
	C�Զ����Թ�Ѱ·Doc* GetDocument() const;

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
	virtual ~C�Զ����Թ�Ѱ·View();
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
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	bool isLbtnDown;
	bool isRbtnDown;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditMap();
	afx_msg void OnEditPoint();
	afx_msg void OnEditStart();
	afx_msg void OnClean();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize20x20();
	afx_msg void OnSize50x50();
	afx_msg void OnSize80x80();
	afx_msg void OnSize100x100();
	afx_msg void OnSize200x200();
	afx_msg void OnSize300x300();
	afx_msg void OnAnimaOpen();
	afx_msg void OnAnimaClose();
	afx_msg void OnHelpView();
	afx_msg void OnDirect4();
	afx_msg void OnDirect8();
	afx_msg void OnEditRandommap();
	afx_msg void OnSleep16();
	afx_msg void OnSleep22();
	afx_msg void OnSleep33();
	afx_msg void OnSleep41();
	afx_msg void OnSleep83();
	afx_msg void OnSleep8();
	afx_msg void OnStepRound();
	afx_msg void OnStepStep();
	afx_msg void OnSleep333();
	afx_msg void OnSleep1000();
	afx_msg void OnShowAllani();
	afx_msg void OnShowBorderani();
	afx_msg void OnFileLoadimg();
	void LoadImgFileAsMap(TCHAR * fileName);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnFileSaveimg();
	afx_msg void OnEditBlock();
	CPoint downPoint;
	bool isDirectGrayPic;
	afx_msg void OnFileGrayhalf();
	afx_msg void OnFileBorderload();
};

#ifndef _DEBUG  // �Զ����Թ�Ѱ·View.cpp �еĵ��԰汾
inline C�Զ����Թ�Ѱ·Doc* C�Զ����Թ�Ѱ·View::GetDocument() const
   { return reinterpret_cast<C�Զ����Թ�Ѱ·Doc*>(m_pDocument); }
#endif

