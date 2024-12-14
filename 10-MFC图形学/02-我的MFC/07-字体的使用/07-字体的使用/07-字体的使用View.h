
// 07-字体的使用View.h : CMy07字体的使用View 类的接口
//

#pragma once


class CMy07字体的使用View : public CView
{
protected: // 仅从序列化创建
	CMy07字体的使用View();
	DECLARE_DYNCREATE(CMy07字体的使用View)

// 特性
public:
	CMy07字体的使用Doc* GetDocument() const;

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
	virtual ~CMy07字体的使用View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 07-字体的使用View.cpp 中的调试版本
inline CMy07字体的使用Doc* CMy07字体的使用View::GetDocument() const
   { return reinterpret_cast<CMy07字体的使用Doc*>(m_pDocument); }
#endif

