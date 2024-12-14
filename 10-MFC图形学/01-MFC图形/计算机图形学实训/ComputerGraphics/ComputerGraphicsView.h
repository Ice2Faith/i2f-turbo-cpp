// ComputerGraphicsView.h : interface of the CComputerGraphicsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__COMPUTERGRAPGICS__INCLUDED_)
#define AFX_VIEW_H__COMPUTERGRAPGICS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//深度缓冲使用随机颜色
#include<stdlib.h>
#include<time.h>
//绘图核心函数和基本数据类型包含
#include"GData.h"
#include"GGrating.h"
#include"GHideZBuffer.h"
#include"GLighting.h"
#include"GProjection.h"
#include"GStereo.h"
#include"GTMFile.h"
#include"GTranglelized.h"
#include"GVary.h"
//对话框属性设置包含
#include"DlgColorSetting.h"
#include"DlgSizeSetting.h"
#include"DlgInputBox.h"
#include"DlgGraphVarySetting.h"
#include"DlgMaterialSetting.h"
#include"DlgLightSetting.h"
#include"DlgGeoModCreateSetting.h"
#include"DlgOperationTips.h"
#include"DlgCartonSetting.h"
#include"DlgBaseOperationHelp.h"
//绘图类型枚举
enum DrawType{DT_NULL,DT_POINT,DT_LINE,DT_CONLINE,
			DT_CIRCLE,DT_ELIPESE,DT_RECT,DT_ROUNDRECT,
			DT_ARC,DT_POLYGON,DT_POLYLINE,DT_BEZIER,
			DT_GON,DT_CLEANER,
			ST_BEZIER,ST_CTR_BEZIER,ST_DDALINE,ST_WUALIASLINE,ST_POLYLINE,
			ST_SEENDFILL,ST_TRANGLEFILL};
//三维图形显示模式枚举
enum ViewType{VT_NONE,VT_POINTCLOUD,VT_LINEAR,VT_FALT};
enum ProjType{PT_ORTHOGONAL,PT_MAINVIEW,PT_SIDEVIEW,PT_TOPVIEW,
			PT_OBLIQUE,PT_WORDTOSCREEN,PT_ONEPOINT,PT_TWOPOINT,
			PT_THREEPOINT,PT_DEEPSCREEN};
//隐藏片面算法枚举
enum HideType{HT_NONE,HT_BLANK,HT_ZBUFFER};
//灯光状态枚举
enum LightType{LT_NONE,LT_OPEN};
//基本绘图的控制点控制
#define MAXPOINTCOUNT 128
//动画定时器ID定义
#define ID_TIMER_CARTON 0x101
class CComputerGraphicsView : public CView
{
public:
	bool isXDown,isYDown,isZDown;//X，Y，Z按键是否按下
	bool isShiftDown;//Shift按键是否按下
	bool needShowOrgLine;//需要绘制坐标线
	bool needShowCtrlPoint;//需要显示控制点
	//定义当前使用的画笔，画刷的大小和颜色及指针
	COLORREF penColor;
	COLORREF brushColor;
	int penSize;
	CPen * penDraw;
	CBrush * brushDraw;
	//定义使用到的对话框指针
	DlgColorSetting * colorDlg;
	DlgSizeSetting * sizeDlg;
	DlgInputBox * inputDlg;
	DlgGraphVarySetting * varyDlg;
	DlgMaterialSetting * metaDlg;
	DlgLightSetting * lightDlg;
	DlgGeoModCreateSetting * geomodDlg;
	DlgOperationTips * opetipDlg;
	DlgCartonSetting * cartonDlg;
	DlgBaseOperationHelp * baseOpeDlg;
	//绘图类型识别
	DrawType drawType;
	DrawType editBakDrawType;
	//基本绘图时用到的点数组和当前点的数量
	CPoint * pointArr;
	int prePointCount;
	//鼠标左右键的按下状态监视
	bool isLBtnDown;
	bool isRBtnDown;
	//用于双缓冲绘图在第一次加载窗口时初始化mdc
	bool isFristLoad;
	//双缓冲绘图用到的mdc和对应的位图
	CDC * mdc;
	CBitmap * mdimg;
	//存放三维顶点和片面数据的对象
	GD3DataGroup  gddata;
	//模型显示方式监视
	ViewType viewType;
	//是否需要清空缓冲内容监视
	bool needCleanPainter;
	//对Bezier曲线控制点编辑时的下标跟踪
	int stbmoveIndex;
	//投影类型监视
	ProjType projType;
	//隐面算法监视
	HideType hideType;
	//灯光监视
	LightType lightType;
	//材质结构
	D3Material lg_mate;
	//灯光结构
	D3Light lg_light;
	//视点对象
	GD3Point lg_viewPoint;
	//环境光结构
	D3Ambient lg_amb;
// Implementation
public:
	// 深度缓冲绘图函数
	void ZBufferDrawGraph();
	// 将三维顶点按照设置的变换和投影进行转换为屏幕上的二维坐标
	GD3Point VaryProjGD3Point(GD3Point point);
	// 将三维坐标去掉Z轴为二维坐标
	CPoint GD3PointToCPoint(GD3Point & p);
	// 重置MDC坐标为默认坐标
	void ResetOrg(CRect pdcRect);
	// 将MDC坐标放到视图中心
	void CentralOrg(CRect pdcRect);
	// 根据绘图模式绘制三维模型
	void DrawD3Graph();
	virtual ~CComputerGraphicsView();
protected: // create from serialization only
	CComputerGraphicsView();
	DECLARE_DYNCREATE(CComputerGraphicsView)

// Attributes
public:
	CComputerGraphicsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComputerGraphicsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CComputerGraphicsView)
	afx_msg void OnPenColor();// 设置画笔颜色，像素点也使用
	afx_msg void OnPenSize();// 设置画笔粗度
	afx_msg void OnBrushColor();// 设置画刷颜色
	afx_msg void OnDrawPoint();// 画点菜单
	afx_msg void OnDrawLine();// 画线菜单
	afx_msg void OnDrawGon();// 画喷枪菜单
	afx_msg void OnDrawElipese();// 画椭圆菜单
	afx_msg void OnDrawConline();// 画连续线菜单
	afx_msg void OnDrawCleaner();// 画橡皮菜单
	afx_msg void OnDrawCircle();// 画圆菜单
	afx_msg void OnDrawBezierline();// 画Bezier曲线菜单
	afx_msg void OnDrawArc();// 画弧线菜单
	afx_msg void OnDrawPolygon();// 画填充多边形菜单
	afx_msg void OnDrawPolyline();// 画多边形菜单
	afx_msg void OnDrawRectangle();// 画矩形菜单
	afx_msg void OnDrawNull();// 画指针菜单
	afx_msg void OnDrawRoundrect();// 画圆角矩形菜单
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);// 无效，废弃
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTmfileOpen();// 打开TM文件菜单
	afx_msg void OnTmfileSave();// 保存为TM文件菜单
	afx_msg void OnDismodFlat();// 模型显示为片面菜单
	afx_msg void OnDismodLinear();// 模型显示为线框菜单
	afx_msg void OnDismodPointcloud();// 模型显示为点云菜单
	afx_msg void OnDismodCleanpainter();// 清空绘图重绘窗口菜单
	afx_msg void OnGeomodBall();// 创建球形点云数据菜单
	afx_msg void OnGeomodCone();// 创建圆锥点云数据菜单
	afx_msg void OnGeomodCylinder();// 创建圆柱点云数据菜单
	afx_msg void OnGeomodDodec();// 创建十二面体菜单
	afx_msg void OnGeomodHex();// 创建六面体菜单
	afx_msg void OnGeomodIcos();// 创建二十面体菜单
	afx_msg void OnGeomodOct();// 创建八面体菜单
	afx_msg void OnGeomodTetr();// 创建四面体菜单
	afx_msg void OnGeomodTorus();// 创建环体点云数据菜单
	afx_msg void OnTranglelized();// 三角花点云菜单
	afx_msg void OnLinemodeBezier();// 使用自定义的高阶Bezier绘制菜单
	afx_msg void OnLinemodEdit();// 编辑Bezier控制点菜单
	afx_msg void OnScandisDdaline();// DDA直线绘制菜单
	afx_msg void OnScandisAntialiasline();// 反走样直线绘制菜单
	afx_msg void OnScanSeedfill();// 种子填充算法菜单
	afx_msg void OnScanTranglefill();// 三角形填充算法菜单
	afx_msg void OnGraphVary();// 模型变换菜单
	afx_msg void OnProjDeepscreen();// 带深度的屏幕透视投影菜单
	afx_msg void OnProjMainview();// 主视图菜单
	afx_msg void OnProjOblique();// 斜投影菜单
	afx_msg void OnProjOnepoint();// 一点透视菜单
	afx_msg void OnProjOrthogonal();// 正交投影菜单
	afx_msg void OnProjSideview();// 侧视图菜单
	afx_msg void OnProjThreepoint();// 三点透视菜单
	afx_msg void OnProjTopview();// 俯视图菜单
	afx_msg void OnProjTwopoint();// 两点透视菜单
	afx_msg void OnProjWordtoscreen();// 直接转换投影菜单
	afx_msg void OnModhideBackremove();// 背面剔除算法菜单
	afx_msg void OnModhideDeepbuff();// 深度缓冲算法菜单
	afx_msg void OnModhideNone();// 不使用背面和深度缓冲菜单
	afx_msg void OnModlightFlat();// 平面光照菜单
	afx_msg void OnModlightNone();// 不使用光照菜单
	afx_msg void OnModlightMateriaex();// 材质选择菜单
	afx_msg void OnModlightLight();// 光照设置菜单
	afx_msg void OnOperationTips();// 帮助提示
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);// 键盘按键处理--变换处理
	afx_msg void OnCartonSetting();// 动画设置对话框
	afx_msg void OnTimer(UINT nIDEvent);// 动画设置定时器
	afx_msg void OnDismodNone();// 不显示模型对话框
	afx_msg void OnLinemodBezieryspin();// 绕Y轴产生Bezier旋转体
	afx_msg void OnShowOrgline();// 显示坐标线菜单
	afx_msg void OnHideOrgline();// 隐藏坐标线菜单
	afx_msg void OnLinemodBezierxspin();// 绕X轴产生Bezier旋转体菜单
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);// 鼠标滚动时间处理--缩放，旋转
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);// 按键释放处理
	afx_msg void OnOperationBaseope();
	afx_msg void OnGeomodBallex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLinemodePolyline();
};

#ifndef _DEBUG  // debug version in ComputerGraphicsView.cpp
inline CComputerGraphicsDoc* CComputerGraphicsView::GetDocument()
   { return (CComputerGraphicsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__COMPUTERGRAPGICS__INCLUDED_)
