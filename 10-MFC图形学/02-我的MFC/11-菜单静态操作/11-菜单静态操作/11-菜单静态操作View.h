
// 11-菜单静态操作View.h : CMy11菜单静态操作View 类的接口
//

#pragma once


class CMy11菜单静态操作View : public CView
{
protected: // 仅从序列化创建
	CMy11菜单静态操作View();
	DECLARE_DYNCREATE(CMy11菜单静态操作View)

// 特性
public:
	CMy11菜单静态操作Doc* GetDocument() const;

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
	virtual ~CMy11菜单静态操作View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 11-菜单静态操作View.cpp 中的调试版本
inline CMy11菜单静态操作Doc* CMy11菜单静态操作View::GetDocument() const
   { return reinterpret_cast<CMy11菜单静态操作Doc*>(m_pDocument); }
#endif

