
// 03-������εĻ���View.h : CMy03������εĻ���View ��Ľӿ�
//

#pragma once


class CMy03������εĻ���View : public CView
{
private:
	void ResetCenterOrg(CDC * pDC);	//������������ϵ
	void DrawOrgLine(CDC * pDC);	//���ƺ�ɫ������
	void AllocMemery();	//����ռ䱣������
	bool BuildData();	//�������ݵ���
	void CreateTetrahedron();	//����������������
	void CreateHexahedron();
	void CreateOctahedron();
	void CreateDodecahedron();
	void CreateIcosahedron();
	void CreateBall();	//������ת������
	void CreateCylinder();
	void CreateCone();
	void CreateTorus();
	COLORREF PointColor;	//������ɫ�Ͱ�������ɫ
	COLORREF LineColor;
	void ( CMy03������εĻ���View::*func)();	//����ָ�룬ָ��������Щ�����������ݵĺ���
	void InitDraw();	//��ʼ����ͼ����
	void ClearDrawData();	//��յ�ǰ��ͼ����
	void DrawVPolygon(CDC* pDC);	//���ջ�ͼģʽ��ͼ
	int m_pointcount;	//����
	int m_tranglecount;	//����
	double ** m_points;	//��������ָ��
	int ** m_trangle;	//������ָ��
	int m_vectorNum;	//ÿ����ı��������ƻ�ͼʱ��
	bool m_isload;	//�����Ƿ��Ѿ�����
	int m_drawtype;	//��ͼ���� 0 ���� 1 ������ 2 �����
	int m_shrink;	//���ű���*10
	bool m_viewOrgLine;	//�Ƿ���ʾ������
	bool m_openeye;	//�Ƿ�ʹ���淨�������ƶ����
public:
	afx_msg void OnDrawTetrahedron();
	afx_msg void OnDrawHexahedron();
	afx_msg void OnDrawOctahedron();
	afx_msg void OnDrawDodecahedron();
	afx_msg void OnDrawIcosahedron();
	afx_msg void OnDrawBall();
	afx_msg void OnDrawCylinder();
	afx_msg void OnDrawCone();
	afx_msg void OnDrawTorus();
	afx_msg void OnPointRed();
	afx_msg void OnPointGreen();
	afx_msg void OnPointBlue();
	afx_msg void OnPointBlack();
	afx_msg void OnLineRed();
	afx_msg void OnLineGreen();
	afx_msg void OnLineBlue();
	afx_msg void OnLineBlack();
	afx_msg void OnOrgLineShow();
	afx_msg void OnOrgLineHide();
protected: // �������л�����
	CMy03������εĻ���View();
	DECLARE_DYNCREATE(CMy03������εĻ���View)

// ����
public:
	CMy03������εĻ���Doc* GetDocument() const;

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
	virtual ~CMy03������εĻ���View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	
};

#ifndef _DEBUG  // 03-������εĻ���View.cpp �еĵ��԰汾
inline CMy03������εĻ���Doc* CMy03������εĻ���View::GetDocument() const
   { return reinterpret_cast<CMy03������εĻ���Doc*>(m_pDocument); }
#endif

