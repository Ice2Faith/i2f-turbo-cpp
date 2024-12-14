
// 04-事件作业View.h : CMy04事件作业View 类的接口
//

#pragma once


class CMy04事件作业View : public CView
{
protected: // 仅从序列化创建
	CMy04事件作业View();
	DECLARE_DYNCREATE(CMy04事件作业View)

// 特性
public:
	CMy04事件作业Doc* GetDocument() const;

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
	virtual ~CMy04事件作业View();
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
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // 04-事件作业View.cpp 中的调试版本
inline CMy04事件作业Doc* CMy04事件作业View::GetDocument() const
   { return reinterpret_cast<CMy04事件作业Doc*>(m_pDocument); }
#endif

