
// 09-��ʱ�����彥��View.h : CMy09��ʱ�����彥��View ��Ľӿ�
//

#pragma once


class CMy09��ʱ�����彥��View : public CView
{
protected: // �������л�����
	CMy09��ʱ�����彥��View();
	DECLARE_DYNCREATE(CMy09��ʱ�����彥��View)

// ����
public:
	CMy09��ʱ�����彥��Doc* GetDocument() const;

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
	virtual ~CMy09��ʱ�����彥��View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // 09-��ʱ�����彥��View.cpp �еĵ��԰汾
inline CMy09��ʱ�����彥��Doc* CMy09��ʱ�����彥��View::GetDocument() const
   { return reinterpret_cast<CMy09��ʱ�����彥��Doc*>(m_pDocument); }
#endif

