
// 02_StartMFCView.h : CMy02_StartMFCView ��Ľӿ�
//

#pragma once


class CMy02_StartMFCView : public CView
{
protected: // �������л�����
	CMy02_StartMFCView();
	DECLARE_DYNCREATE(CMy02_StartMFCView)

// ����
public:
	CMy02_StartMFCDoc* GetDocument() const;

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
	virtual ~CMy02_StartMFCView();
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
};

#ifndef _DEBUG  // 02_StartMFCView.cpp �еĵ��԰汾
inline CMy02_StartMFCDoc* CMy02_StartMFCView::GetDocument() const
   { return reinterpret_cast<CMy02_StartMFCDoc*>(m_pDocument); }
#endif

