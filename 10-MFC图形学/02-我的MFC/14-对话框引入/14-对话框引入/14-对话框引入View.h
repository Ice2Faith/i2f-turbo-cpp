
// 14-对话框引入View.h : CMy14对话框引入View 类的接口
//

#pragma once


class CMy14对话框引入View : public CView
{
protected: // 仅从序列化创建
	CMy14对话框引入View();
	DECLARE_DYNCREATE(CMy14对话框引入View)

// 特性
public:
	CMy14对话框引入Doc* GetDocument() const;

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
	virtual ~CMy14对话框引入View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 14-对话框引入View.cpp 中的调试版本
inline CMy14对话框引入Doc* CMy14对话框引入View::GetDocument() const
   { return reinterpret_cast<CMy14对话框引入Doc*>(m_pDocument); }
#endif

