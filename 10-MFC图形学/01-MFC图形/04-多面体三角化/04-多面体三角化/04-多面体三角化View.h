
// 04-多面体三角化View.h : CMy04多面体三角化View 类的接口
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

class CMy04多面体三角化View : public CView
{
private:
	PMAPNODE m_matrix;//邻接矩阵（每个点的三个邻接点）
	void BulidLinearMatrix();
	///////////////
	void ResetCenterOrg(CDC * pDC);	//设置中央坐标系
	void DrawOrgLine(CDC * pDC);	//绘制红色坐标线
	void AllocMemery();	//申请空间保存数据
	bool BuildData();	//创建数据调用
	void CreateBall();	//创建旋转体数据
	void CreateCylinder();
	void CreateCone();
	void CreateTorus();
	COLORREF PointColor;	//点云颜色和包络线颜色
	COLORREF LineColor;
	void (CMy04多面体三角化View::*func)();	//函数指针，指向上面这些创建立体数据的函数
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
protected: // 仅从序列化创建
	CMy04多面体三角化View();
	DECLARE_DYNCREATE(CMy04多面体三角化View)

// 特性
public:
	CMy04多面体三角化Doc* GetDocument() const;

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
	virtual ~CMy04多面体三角化View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // 04-多面体三角化View.cpp 中的调试版本
inline CMy04多面体三角化Doc* CMy04多面体三角化View::GetDocument() const
   { return reinterpret_cast<CMy04多面体三角化Doc*>(m_pDocument); }
#endif

