
// 12-��̬ͼ��View.h : CMy12��̬ͼ��View ��Ľӿ�
//

#pragma once


class CMy12��̬ͼ��View : public CView
{
protected: // �������л�����
	CMy12��̬ͼ��View();
	DECLARE_DYNCREATE(CMy12��̬ͼ��View)

// ����
public:
	CMy12��̬ͼ��Doc* GetDocument() const;

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
	virtual ~CMy12��̬ͼ��View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 12-��̬ͼ��View.cpp �еĵ��԰汾
inline CMy12��̬ͼ��Doc* CMy12��̬ͼ��View::GetDocument() const
   { return reinterpret_cast<CMy12��̬ͼ��Doc*>(m_pDocument); }
#endif

