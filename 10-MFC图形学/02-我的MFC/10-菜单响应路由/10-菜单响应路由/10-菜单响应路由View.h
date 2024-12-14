
// 10-菜单响应路由View.h : CMy10菜单响应路由View 类的接口
//

#pragma once


class CMy10菜单响应路由View : public CView
{
protected: // 仅从序列化创建
	CMy10菜单响应路由View();
	DECLARE_DYNCREATE(CMy10菜单响应路由View)

// 特性
public:
	CMy10菜单响应路由Doc* GetDocument() const;

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
	virtual ~CMy10菜单响应路由View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnTestDemo();
};

#ifndef _DEBUG  // 10-菜单响应路由View.cpp 中的调试版本
inline CMy10菜单响应路由Doc* CMy10菜单响应路由View::GetDocument() const
   { return reinterpret_cast<CMy10菜单响应路由Doc*>(m_pDocument); }
#endif

