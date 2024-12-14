
// 12-动态图标View.h : CMy12动态图标View 类的接口
//

#pragma once


class CMy12动态图标View : public CView
{
protected: // 仅从序列化创建
	CMy12动态图标View();
	DECLARE_DYNCREATE(CMy12动态图标View)

// 特性
public:
	CMy12动态图标Doc* GetDocument() const;

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
	virtual ~CMy12动态图标View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 12-动态图标View.cpp 中的调试版本
inline CMy12动态图标Doc* CMy12动态图标View::GetDocument() const
   { return reinterpret_cast<CMy12动态图标Doc*>(m_pDocument); }
#endif

