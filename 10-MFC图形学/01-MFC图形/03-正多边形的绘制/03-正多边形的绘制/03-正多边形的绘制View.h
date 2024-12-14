
// 03-正多边形的绘制View.h : CMy03正多边形的绘制View 类的接口
//

#pragma once


class CMy03正多边形的绘制View : public CView
{
private:
	void ResetCenterOrg(CDC * pDC);	//设置中央坐标系
	void DrawOrgLine(CDC * pDC);	//绘制红色坐标线
	void AllocMemery();	//申请空间保存数据
	bool BuildData();	//创建数据调用
	void CreateTetrahedron();	//创建正多面体数据
	void CreateHexahedron();
	void CreateOctahedron();
	void CreateDodecahedron();
	void CreateIcosahedron();
	void CreateBall();	//创建旋转体数据
	void CreateCylinder();
	void CreateCone();
	void CreateTorus();
	COLORREF PointColor;	//点云颜色和包络线颜色
	COLORREF LineColor;
	void ( CMy03正多边形的绘制View::*func)();	//函数指针，指向上面这些创建立体数据的函数
	void InitDraw();	//初始化绘图环境
	void ClearDrawData();	//清空当前绘图数据
	void DrawVPolygon(CDC* pDC);	//按照绘图模式绘图
	int m_pointcount;	//点数
	int m_tranglecount;	//面数
	double ** m_points;	//顶点数组指针
	int ** m_trangle;	//面数组指针
	int m_vectorNum;	//每个面的边数，控制绘图时用
	bool m_isload;	//数据是否已经加载
	int m_drawtype;	//绘图类型 0 点云 1 包络线 2 多边形
	int m_shrink;	//缩放倍数*10
	bool m_viewOrgLine;	//是否显示坐标线
	bool m_openeye;	//是否使用面法向量绘制多边形
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
protected: // 仅从序列化创建
	CMy03正多边形的绘制View();
	DECLARE_DYNCREATE(CMy03正多边形的绘制View)

// 特性
public:
	CMy03正多边形的绘制Doc* GetDocument() const;

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
	virtual ~CMy03正多边形的绘制View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	
};

#ifndef _DEBUG  // 03-正多边形的绘制View.cpp 中的调试版本
inline CMy03正多边形的绘制Doc* CMy03正多边形的绘制View::GetDocument() const
   { return reinterpret_cast<CMy03正多边形的绘制Doc*>(m_pDocument); }
#endif

