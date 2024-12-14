
// 07-��άģ�ͼ��α任��ͶӰView.h : CMy07��άģ�ͼ��α任��ͶӰView ��Ľӿ�
//

#pragma once
#include"ConfigureValueDlg.h"
enum ProjType{ PT_Null, PT_Orthogonal, PT_MainView, PT_SideView, PT_TopView, PT_Oblique, PT_WorldOrgToScreenOrg, PT_OnePoint, PT_TwoPoint, PT_ThreePoint, PT_ViewOrgToDeepScreenD3Org };
enum VaryType{ VT_Null=0, VT_Move=1, VT_Scale=2, VT_Spin=4, VT_Reflact=8, VT_FlatReflact=16, VT_Miscut=32 };
class CMy07��άģ�ͼ��α任��ͶӰView : public CView
{
private:
	ConfigureValueDlg dlg;
	void ResetCenterOrg(CDC * pDC);
	void DrawGraph(CDC * pDC);
	void ProjToScreen(double * rx, double * ry, double vz);
	bool LoadTMFile(char * filename);
	void ReLoadDrawData(char * filename);
	void ClearDrawData();
	int m_pointcount;
	int m_tranglecount;
	double ** m_points;
	int ** m_trangle;
	bool m_isload;
	ProjType m_projType;
	COLORREF m_pointColor;
	double m_aAngle;
	double m_bAngle;
	double m_R;
	double m_d;
	double m_Near;
	double m_Far;
	int m_varyType;
	double m_move_x, m_move_y, m_move_z;
	double m_scale_x, m_scale_y, m_scale_z;
	double m_spin_x, m_spin_y, m_spin_z;
	bool m_reflact_x, m_reflact_y, m_reflact_z;
	bool m_flat_refalct_xoy, m_flat_refalct_yoz, m_flat_refalct_xoz;
	double m_miscut_xgz, m_miscut_xdy, m_miscut_yhz, m_miscut_ybx, m_miscut_zfy, m_miscut_zcx;
protected: // �������л�����
	CMy07��άģ�ͼ��α任��ͶӰView();
	DECLARE_DYNCREATE(CMy07��άģ�ͼ��α任��ͶӰView)

// ����
public:
	CMy07��άģ�ͼ��α任��ͶӰDoc* GetDocument() const;

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
	virtual ~CMy07��άģ�ͼ��α任��ͶӰView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnProjOrthogonal();
	afx_msg void OnProjMainView();
	afx_msg void OnProjSideView();
	afx_msg void OnProjTopView();
	afx_msg void OnProjOblique();
	afx_msg void OnProjWorldOrgToScreenOrg();
	afx_msg void OnProjOnePoint();
	afx_msg void OnProjTwoPoint();
	afx_msg void OnProjThreePoint();
	afx_msg void OnViewOrgToDeepScreenD3Org();
	afx_msg void OnMenuSetting();
	int m_drawType;
	afx_msg void OndrawTypePoint();
	afx_msg void OndrawTypeLine();
};

#ifndef _DEBUG  // 07-��άģ�ͼ��α任��ͶӰView.cpp �еĵ��԰汾
inline CMy07��άģ�ͼ��α任��ͶӰDoc* CMy07��άģ�ͼ��α任��ͶӰView::GetDocument() const
   { return reinterpret_cast<CMy07��άģ�ͼ��α任��ͶӰDoc*>(m_pDocument); }
#endif

