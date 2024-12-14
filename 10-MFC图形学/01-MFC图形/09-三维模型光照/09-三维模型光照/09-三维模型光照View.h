
// 09-��άģ�͹���View.h : CMy09��άģ�͹���View ��Ľӿ�
//

#pragma once

#include"D3Graph.h"
#include"D3Light.h"
class CMy09��άģ�͹���View : public CView
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
	CMy09��άģ�͹���View();
	DECLARE_DYNCREATE(CMy09��άģ�͹���View)

// ����
public:
	CMy09��άģ�͹���Doc* GetDocument() const;

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
	virtual ~CMy09��άģ�͹���View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 09-��άģ�͹���View.cpp �еĵ��԰汾
inline CMy09��άģ�͹���Doc* CMy09��άģ�͹���View::GetDocument() const
   { return reinterpret_cast<CMy09��άģ�͹���Doc*>(m_pDocument); }
#endif

