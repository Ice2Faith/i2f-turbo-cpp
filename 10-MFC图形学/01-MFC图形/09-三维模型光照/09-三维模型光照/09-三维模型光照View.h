
// 09-三维模型光照View.h : CMy09三维模型光照View 类的接口
//

#pragma once

#include"D3Graph.h"
#include"D3Light.h"
class CMy09三维模型光照View : public CView
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
	CMy09三维模型光照View();
	DECLARE_DYNCREATE(CMy09三维模型光照View)

// 特性
public:
	CMy09三维模型光照Doc* GetDocument() const;

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
	virtual ~CMy09三维模型光照View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 09-三维模型光照View.cpp 中的调试版本
inline CMy09三维模型光照Doc* CMy09三维模型光照View::GetDocument() const
   { return reinterpret_cast<CMy09三维模型光照Doc*>(m_pDocument); }
#endif

