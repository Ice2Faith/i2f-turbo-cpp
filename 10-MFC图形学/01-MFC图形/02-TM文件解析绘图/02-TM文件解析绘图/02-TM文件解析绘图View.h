
// 02-TM�ļ�������ͼView.h : CMy02TM�ļ�������ͼView ��Ľӿ�
//

#pragma once


class CMy02TM�ļ�������ͼView : public CView
{
protected: // �������л�����
	CMy02TM�ļ�������ͼView();
	DECLARE_DYNCREATE(CMy02TM�ļ�������ͼView)

// ����
public:
	CMy02TM�ļ�������ͼDoc* GetDocument() const;

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
	virtual ~CMy02TM�ļ�������ͼView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

private:
	void ResetCenterOrg(CDC * pDC);
	void DrawOrgLine(CDC * pDC);
	bool LoadTMFile(char * filename);
	void InitDraw();
	void ClearDrawData();
	void ReLoadDrawData(char * filename);
	void DrawVPolygon(CDC* pDC);
	int m_pointcount;
	int m_tranglecount;
	double ** m_points;
	int ** m_trangle;
	bool m_isload;
	int m_drawtype;
	int m_shrink;
	bool m_viewOrgLine;
	bool m_centerOrg;
	bool m_openeye;
public:
	afx_msg void OnSelectCenterOrg();
	afx_msg void OnSelectViewOrgLine();
	afx_msg void OnSelectViewMode();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelectShrink();
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSelectResetShrink();
	afx_msg void OnSelectEyeView();
};

#ifndef _DEBUG  // 02-TM�ļ�������ͼView.cpp �еĵ��԰汾
inline CMy02TM�ļ�������ͼDoc* CMy02TM�ļ�������ͼView::GetDocument() const
   { return reinterpret_cast<CMy02TM�ļ�������ͼDoc*>(m_pDocument); }
#endif

