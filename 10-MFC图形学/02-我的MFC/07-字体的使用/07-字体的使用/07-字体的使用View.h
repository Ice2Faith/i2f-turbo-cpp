
// 07-�����ʹ��View.h : CMy07�����ʹ��View ��Ľӿ�
//

#pragma once


class CMy07�����ʹ��View : public CView
{
protected: // �������л�����
	CMy07�����ʹ��View();
	DECLARE_DYNCREATE(CMy07�����ʹ��View)

// ����
public:
	CMy07�����ʹ��Doc* GetDocument() const;

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
	virtual ~CMy07�����ʹ��View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 07-�����ʹ��View.cpp �еĵ��԰汾
inline CMy07�����ʹ��Doc* CMy07�����ʹ��View::GetDocument() const
   { return reinterpret_cast<CMy07�����ʹ��Doc*>(m_pDocument); }
#endif

