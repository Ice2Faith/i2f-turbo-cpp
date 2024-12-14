
// 08-图形消隐与深度缓冲View.h : CMy08图形消隐与深度缓冲View 类的接口
//

#pragma once
#define ID_TIMER_KARTON 0x1001
#include"D3Graph.h"
class CMy08图形消隐与深度缓冲View : public CView
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
protected: // 仅从序列化创建
	CMy08图形消隐与深度缓冲View();
	DECLARE_DYNCREATE(CMy08图形消隐与深度缓冲View)

// 特性
public:
	CMy08图形消隐与深度缓冲Doc* GetDocument() const;

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
	virtual ~CMy08图形消隐与深度缓冲View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	double m_roundAngle;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 08-图形消隐与深度缓冲View.cpp 中的调试版本
inline CMy08图形消隐与深度缓冲Doc* CMy08图形消隐与深度缓冲View::GetDocument() const
   { return reinterpret_cast<CMy08图形消隐与深度缓冲Doc*>(m_pDocument); }
#endif

