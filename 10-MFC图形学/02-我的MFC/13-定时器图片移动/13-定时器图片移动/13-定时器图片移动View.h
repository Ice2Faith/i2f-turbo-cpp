
// 13-��ʱ��ͼƬ�ƶ�View.h : CMy13��ʱ��ͼƬ�ƶ�View ��Ľӿ�
//

#pragma once


class CMy13��ʱ��ͼƬ�ƶ�View : public CView
{
protected: // �������л�����
	CMy13��ʱ��ͼƬ�ƶ�View();
	DECLARE_DYNCREATE(CMy13��ʱ��ͼƬ�ƶ�View)

// ����
public:
	CMy13��ʱ��ͼƬ�ƶ�Doc* GetDocument() const;

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
	virtual ~CMy13��ʱ��ͼƬ�ƶ�View();
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
private:
	CBitmap m_bitmap[3];
	int px[3];
public:
	afx_msg void OnReStart();
};

#ifndef _DEBUG  // 13-��ʱ��ͼƬ�ƶ�View.cpp �еĵ��԰汾
inline CMy13��ʱ��ͼƬ�ƶ�Doc* CMy13��ʱ��ͼƬ�ƶ�View::GetDocument() const
   { return reinterpret_cast<CMy13��ʱ��ͼƬ�ƶ�Doc*>(m_pDocument); }
#endif

