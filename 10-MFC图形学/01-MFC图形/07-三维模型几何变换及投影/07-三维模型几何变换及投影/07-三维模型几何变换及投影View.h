
// 07-三维模型几何变换及投影View.h : CMy07三维模型几何变换及投影View 类的接口
//

#pragma once
#include"ConfigureValueDlg.h"
enum ProjType{ PT_Null, PT_Orthogonal, PT_MainView, PT_SideView, PT_TopView, PT_Oblique, PT_WorldOrgToScreenOrg, PT_OnePoint, PT_TwoPoint, PT_ThreePoint, PT_ViewOrgToDeepScreenD3Org };
enum VaryType{ VT_Null=0, VT_Move=1, VT_Scale=2, VT_Spin=4, VT_Reflact=8, VT_FlatReflact=16, VT_Miscut=32 };
class CMy07三维模型几何变换及投影View : public CView
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
protected: // 仅从序列化创建
	CMy07三维模型几何变换及投影View();
	DECLARE_DYNCREATE(CMy07三维模型几何变换及投影View)

// 特性
public:
	CMy07三维模型几何变换及投影Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy07三维模型几何变换及投影View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // 07-三维模型几何变换及投影View.cpp 中的调试版本
inline CMy07三维模型几何变换及投影Doc* CMy07三维模型几何变换及投影View::GetDocument() const
   { return reinterpret_cast<CMy07三维模型几何变换及投影Doc*>(m_pDocument); }
#endif

