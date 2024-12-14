// ComputerGraphicsView.h : interface of the CComputerGraphicsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__COMPUTERGRAPGICS__INCLUDED_)
#define AFX_VIEW_H__COMPUTERGRAPGICS__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//��Ȼ���ʹ�������ɫ
#include<stdlib.h>
#include<time.h>
//��ͼ���ĺ����ͻ����������Ͱ���
#include"GData.h"
#include"GGrating.h"
#include"GHideZBuffer.h"
#include"GLighting.h"
#include"GProjection.h"
#include"GStereo.h"
#include"GTMFile.h"
#include"GTranglelized.h"
#include"GVary.h"
//�Ի����������ð���
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
//��ͼ����ö��
enum DrawType{DT_NULL,DT_POINT,DT_LINE,DT_CONLINE,
			DT_CIRCLE,DT_ELIPESE,DT_RECT,DT_ROUNDRECT,
			DT_ARC,DT_POLYGON,DT_POLYLINE,DT_BEZIER,
			DT_GON,DT_CLEANER,
			ST_BEZIER,ST_CTR_BEZIER,ST_DDALINE,ST_WUALIASLINE,ST_POLYLINE,
			ST_SEENDFILL,ST_TRANGLEFILL};
//��άͼ����ʾģʽö��
enum ViewType{VT_NONE,VT_POINTCLOUD,VT_LINEAR,VT_FALT};
enum ProjType{PT_ORTHOGONAL,PT_MAINVIEW,PT_SIDEVIEW,PT_TOPVIEW,
			PT_OBLIQUE,PT_WORDTOSCREEN,PT_ONEPOINT,PT_TWOPOINT,
			PT_THREEPOINT,PT_DEEPSCREEN};
//����Ƭ���㷨ö��
enum HideType{HT_NONE,HT_BLANK,HT_ZBUFFER};
//�ƹ�״̬ö��
enum LightType{LT_NONE,LT_OPEN};
//������ͼ�Ŀ��Ƶ����
#define MAXPOINTCOUNT 128
//������ʱ��ID����
#define ID_TIMER_CARTON 0x101
class CComputerGraphicsView : public CView
{
public:
	bool isXDown,isYDown,isZDown;//X��Y��Z�����Ƿ���
	bool isShiftDown;//Shift�����Ƿ���
	bool needShowOrgLine;//��Ҫ����������
	bool needShowCtrlPoint;//��Ҫ��ʾ���Ƶ�
	//���嵱ǰʹ�õĻ��ʣ���ˢ�Ĵ�С����ɫ��ָ��
	COLORREF penColor;
	COLORREF brushColor;
	int penSize;
	CPen * penDraw;
	CBrush * brushDraw;
	//����ʹ�õ��ĶԻ���ָ��
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
	//��ͼ����ʶ��
	DrawType drawType;
	DrawType editBakDrawType;
	//������ͼʱ�õ��ĵ�����͵�ǰ�������
	CPoint * pointArr;
	int prePointCount;
	//������Ҽ��İ���״̬����
	bool isLBtnDown;
	bool isRBtnDown;
	//����˫�����ͼ�ڵ�һ�μ��ش���ʱ��ʼ��mdc
	bool isFristLoad;
	//˫�����ͼ�õ���mdc�Ͷ�Ӧ��λͼ
	CDC * mdc;
	CBitmap * mdimg;
	//�����ά�����Ƭ�����ݵĶ���
	GD3DataGroup  gddata;
	//ģ����ʾ��ʽ����
	ViewType viewType;
	//�Ƿ���Ҫ��ջ������ݼ���
	bool needCleanPainter;
	//��Bezier���߿��Ƶ�༭ʱ���±����
	int stbmoveIndex;
	//ͶӰ���ͼ���
	ProjType projType;
	//�����㷨����
	HideType hideType;
	//�ƹ����
	LightType lightType;
	//���ʽṹ
	D3Material lg_mate;
	//�ƹ�ṹ
	D3Light lg_light;
	//�ӵ����
	GD3Point lg_viewPoint;
	//������ṹ
	D3Ambient lg_amb;
// Implementation
public:
	// ��Ȼ����ͼ����
	void ZBufferDrawGraph();
	// ����ά���㰴�����õı任��ͶӰ����ת��Ϊ��Ļ�ϵĶ�ά����
	GD3Point VaryProjGD3Point(GD3Point point);
	// ����ά����ȥ��Z��Ϊ��ά����
	CPoint GD3PointToCPoint(GD3Point & p);
	// ����MDC����ΪĬ������
	void ResetOrg(CRect pdcRect);
	// ��MDC����ŵ���ͼ����
	void CentralOrg(CRect pdcRect);
	// ���ݻ�ͼģʽ������άģ��
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
	afx_msg void OnPenColor();// ���û�����ɫ�����ص�Ҳʹ��
	afx_msg void OnPenSize();// ���û��ʴֶ�
	afx_msg void OnBrushColor();// ���û�ˢ��ɫ
	afx_msg void OnDrawPoint();// ����˵�
	afx_msg void OnDrawLine();// ���߲˵�
	afx_msg void OnDrawGon();// ����ǹ�˵�
	afx_msg void OnDrawElipese();// ����Բ�˵�
	afx_msg void OnDrawConline();// �������߲˵�
	afx_msg void OnDrawCleaner();// ����Ƥ�˵�
	afx_msg void OnDrawCircle();// ��Բ�˵�
	afx_msg void OnDrawBezierline();// ��Bezier���߲˵�
	afx_msg void OnDrawArc();// �����߲˵�
	afx_msg void OnDrawPolygon();// ��������β˵�
	afx_msg void OnDrawPolyline();// ������β˵�
	afx_msg void OnDrawRectangle();// �����β˵�
	afx_msg void OnDrawNull();// ��ָ��˵�
	afx_msg void OnDrawRoundrect();// ��Բ�Ǿ��β˵�
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);// ��Ч������
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTmfileOpen();// ��TM�ļ��˵�
	afx_msg void OnTmfileSave();// ����ΪTM�ļ��˵�
	afx_msg void OnDismodFlat();// ģ����ʾΪƬ��˵�
	afx_msg void OnDismodLinear();// ģ����ʾΪ�߿�˵�
	afx_msg void OnDismodPointcloud();// ģ����ʾΪ���Ʋ˵�
	afx_msg void OnDismodCleanpainter();// ��ջ�ͼ�ػ洰�ڲ˵�
	afx_msg void OnGeomodBall();// �������ε������ݲ˵�
	afx_msg void OnGeomodCone();// ����Բ׶�������ݲ˵�
	afx_msg void OnGeomodCylinder();// ����Բ���������ݲ˵�
	afx_msg void OnGeomodDodec();// ����ʮ������˵�
	afx_msg void OnGeomodHex();// ����������˵�
	afx_msg void OnGeomodIcos();// ������ʮ����˵�
	afx_msg void OnGeomodOct();// ����������˵�
	afx_msg void OnGeomodTetr();// ����������˵�
	afx_msg void OnGeomodTorus();// ��������������ݲ˵�
	afx_msg void OnTranglelized();// ���ǻ����Ʋ˵�
	afx_msg void OnLinemodeBezier();// ʹ���Զ���ĸ߽�Bezier���Ʋ˵�
	afx_msg void OnLinemodEdit();// �༭Bezier���Ƶ�˵�
	afx_msg void OnScandisDdaline();// DDAֱ�߻��Ʋ˵�
	afx_msg void OnScandisAntialiasline();// ������ֱ�߻��Ʋ˵�
	afx_msg void OnScanSeedfill();// ��������㷨�˵�
	afx_msg void OnScanTranglefill();// ����������㷨�˵�
	afx_msg void OnGraphVary();// ģ�ͱ任�˵�
	afx_msg void OnProjDeepscreen();// ����ȵ���Ļ͸��ͶӰ�˵�
	afx_msg void OnProjMainview();// ����ͼ�˵�
	afx_msg void OnProjOblique();// бͶӰ�˵�
	afx_msg void OnProjOnepoint();// һ��͸�Ӳ˵�
	afx_msg void OnProjOrthogonal();// ����ͶӰ�˵�
	afx_msg void OnProjSideview();// ����ͼ�˵�
	afx_msg void OnProjThreepoint();// ����͸�Ӳ˵�
	afx_msg void OnProjTopview();// ����ͼ�˵�
	afx_msg void OnProjTwopoint();// ����͸�Ӳ˵�
	afx_msg void OnProjWordtoscreen();// ֱ��ת��ͶӰ�˵�
	afx_msg void OnModhideBackremove();// �����޳��㷨�˵�
	afx_msg void OnModhideDeepbuff();// ��Ȼ����㷨�˵�
	afx_msg void OnModhideNone();// ��ʹ�ñ������Ȼ���˵�
	afx_msg void OnModlightFlat();// ƽ����ղ˵�
	afx_msg void OnModlightNone();// ��ʹ�ù��ղ˵�
	afx_msg void OnModlightMateriaex();// ����ѡ��˵�
	afx_msg void OnModlightLight();// �������ò˵�
	afx_msg void OnOperationTips();// ������ʾ
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);// ���̰�������--�任����
	afx_msg void OnCartonSetting();// �������öԻ���
	afx_msg void OnTimer(UINT nIDEvent);// �������ö�ʱ��
	afx_msg void OnDismodNone();// ����ʾģ�ͶԻ���
	afx_msg void OnLinemodBezieryspin();// ��Y�����Bezier��ת��
	afx_msg void OnShowOrgline();// ��ʾ�����߲˵�
	afx_msg void OnHideOrgline();// ���������߲˵�
	afx_msg void OnLinemodBezierxspin();// ��X�����Bezier��ת��˵�
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);// ������ʱ�䴦��--���ţ���ת
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);// �����ͷŴ���
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
