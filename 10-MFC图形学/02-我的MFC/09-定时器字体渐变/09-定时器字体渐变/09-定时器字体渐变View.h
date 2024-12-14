
// 09-定时器字体渐变View.h : CMy09定时器字体渐变View 类的接口
//

#pragma once


class CMy09定时器字体渐变View : public CView
{
protected: // 仅从序列化创建
	CMy09定时器字体渐变View();
	DECLARE_DYNCREATE(CMy09定时器字体渐变View)

// 特性
public:
	CMy09定时器字体渐变Doc* GetDocument() const;

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
	virtual ~CMy09定时器字体渐变View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // 09-定时器字体渐变View.cpp 中的调试版本
inline CMy09定时器字体渐变Doc* CMy09定时器字体渐变View::GetDocument() const
   { return reinterpret_cast<CMy09定时器字体渐变Doc*>(m_pDocument); }
#endif

