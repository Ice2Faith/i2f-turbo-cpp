
// 11-�˵���̬����View.h : CMy11�˵���̬����View ��Ľӿ�
//

#pragma once


class CMy11�˵���̬����View : public CView
{
protected: // �������л�����
	CMy11�˵���̬����View();
	DECLARE_DYNCREATE(CMy11�˵���̬����View)

// ����
public:
	CMy11�˵���̬����Doc* GetDocument() const;

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
	virtual ~CMy11�˵���̬����View();
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

#ifndef _DEBUG  // 11-�˵���̬����View.cpp �еĵ��԰汾
inline CMy11�˵���̬����Doc* CMy11�˵���̬����View::GetDocument() const
   { return reinterpret_cast<CMy11�˵���̬����Doc*>(m_pDocument); }
#endif

