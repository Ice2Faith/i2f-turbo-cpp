
// 04-���������ǻ�View.h : CMy04���������ǻ�View ��Ľӿ�
//

#pragma once
typedef struct NNODE
{
	int prePointIndex;
	int linearPointIndexs[3];
}MAPNODE, *PMAPNODE;
typedef struct MTXNODE
{
	int drtPointIndex;
	double distance;
}MATRIXNODE, *PMATRIXNODE;

class CMy04���������ǻ�View : public CView
{
private:
	PMAPNODE m_matrix;//�ڽӾ���ÿ����������ڽӵ㣩
	void BulidLinearMatrix();
	///////////////
	void ResetCenterOrg(CDC * pDC);	//������������ϵ
	void DrawOrgLine(CDC * pDC);	//���ƺ�ɫ������
	void AllocMemery();	//����ռ䱣������
	bool BuildData();	//�������ݵ���
	void CreateBall();	//������ת������
	void CreateCylinder();
	void CreateCone();
	void CreateTorus();
	COLORREF PointColor;	//������ɫ�Ͱ�������ɫ
	COLORREF LineColor;
	void (CMy04���������ǻ�View::*func)();	//����ָ�룬ָ��������Щ�����������ݵĺ���
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
protected: // �������л�����
	CMy04���������ǻ�View();
	DECLARE_DYNCREATE(CMy04���������ǻ�View)

// ����
public:
	CMy04���������ǻ�Doc* GetDocument() const;

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
	virtual ~CMy04���������ǻ�View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawBall();
	afx_msg void OnDrawCylinder();
	afx_msg void OnDrawCone();
	afx_msg void OnDrawTorus();
	afx_msg void OnModePoint();
	afx_msg void OnModeLine();
	afx_msg void OnModeTrangle();
};

#ifndef _DEBUG  // 04-���������ǻ�View.cpp �еĵ��԰汾
inline CMy04���������ǻ�Doc* CMy04���������ǻ�View::GetDocument() const
   { return reinterpret_cast<CMy04���������ǻ�Doc*>(m_pDocument); }
#endif

