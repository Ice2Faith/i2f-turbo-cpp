
// 13-定时器图片移动View.h : CMy13定时器图片移动View 类的接口
//

#pragma once


class CMy13定时器图片移动View : public CView
{
protected: // 仅从序列化创建
	CMy13定时器图片移动View();
	DECLARE_DYNCREATE(CMy13定时器图片移动View)

// 特性
public:
	CMy13定时器图片移动Doc* GetDocument() const;

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
	virtual ~CMy13定时器图片移动View();
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
private:
	CBitmap m_bitmap[3];
	int px[3];
public:
	afx_msg void OnReStart();
};

#ifndef _DEBUG  // 13-定时器图片移动View.cpp 中的调试版本
inline CMy13定时器图片移动Doc* CMy13定时器图片移动View::GetDocument() const
   { return reinterpret_cast<CMy13定时器图片移动Doc*>(m_pDocument); }
#endif

