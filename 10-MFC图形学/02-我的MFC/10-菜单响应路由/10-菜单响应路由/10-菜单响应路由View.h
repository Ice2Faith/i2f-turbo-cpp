
// 10-�˵���Ӧ·��View.h : CMy10�˵���Ӧ·��View ��Ľӿ�
//

#pragma once


class CMy10�˵���Ӧ·��View : public CView
{
protected: // �������л�����
	CMy10�˵���Ӧ·��View();
	DECLARE_DYNCREATE(CMy10�˵���Ӧ·��View)

// ����
public:
	CMy10�˵���Ӧ·��Doc* GetDocument() const;

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
	virtual ~CMy10�˵���Ӧ·��View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnTestDemo();
};

#ifndef _DEBUG  // 10-�˵���Ӧ·��View.cpp �еĵ��԰汾
inline CMy10�˵���Ӧ·��Doc* CMy10�˵���Ӧ·��View::GetDocument() const
   { return reinterpret_cast<CMy10�˵���Ӧ·��Doc*>(m_pDocument); }
#endif

