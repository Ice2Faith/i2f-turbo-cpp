
// 14-�Ի�������View.h : CMy14�Ի�������View ��Ľӿ�
//

#pragma once


class CMy14�Ի�������View : public CView
{
protected: // �������л�����
	CMy14�Ի�������View();
	DECLARE_DYNCREATE(CMy14�Ի�������View)

// ����
public:
	CMy14�Ի�������Doc* GetDocument() const;

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
	virtual ~CMy14�Ի�������View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 14-�Ի�������View.cpp �еĵ��԰汾
inline CMy14�Ի�������Doc* CMy14�Ի�������View::GetDocument() const
   { return reinterpret_cast<CMy14�Ի�������Doc*>(m_pDocument); }
#endif

