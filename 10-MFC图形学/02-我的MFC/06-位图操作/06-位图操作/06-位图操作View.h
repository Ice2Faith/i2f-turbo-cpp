
// 06-λͼ����View.h : CMy06λͼ����View ��Ľӿ�
//

#pragma once


class CMy06λͼ����View : public CView
{
protected: // �������л�����
	CMy06λͼ����View();
	DECLARE_DYNCREATE(CMy06λͼ����View)

// ����
public:
	CMy06λͼ����Doc* GetDocument() const;

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
	virtual ~CMy06λͼ����View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 06-λͼ����View.cpp �еĵ��԰汾
inline CMy06λͼ����Doc* CMy06λͼ����View::GetDocument() const
   { return reinterpret_cast<CMy06λͼ����Doc*>(m_pDocument); }
#endif

