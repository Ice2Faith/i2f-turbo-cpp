
// 08-ͼ����������Ȼ���View.h : CMy08ͼ����������Ȼ���View ��Ľӿ�
//

#pragma once
#define ID_TIMER_KARTON 0x1001
#include"D3Graph.h"
class CMy08ͼ����������Ȼ���View : public CView
{
private:
	void ResetCenterOrg(CDC * pDC);
	void DrawGraph(CDC * pDC);
	bool LoadTMFile(char * filename);
	int m_pointcount;
	int m_tranglecount;
	D3Point* m_points;
	int ** m_trangle;
	bool m_isload;
	int m_drawType;
protected: // �������л�����
	CMy08ͼ����������Ȼ���View();
	DECLARE_DYNCREATE(CMy08ͼ����������Ȼ���View)

// ����
public:
	CMy08ͼ����������Ȼ���Doc* GetDocument() const;

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
	virtual ~CMy08ͼ����������Ȼ���View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	double m_roundAngle;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 08-ͼ����������Ȼ���View.cpp �еĵ��԰汾
inline CMy08ͼ����������Ȼ���Doc* CMy08ͼ����������Ȼ���View::GetDocument() const
   { return reinterpret_cast<CMy08ͼ����������Ȼ���Doc*>(m_pDocument); }
#endif

