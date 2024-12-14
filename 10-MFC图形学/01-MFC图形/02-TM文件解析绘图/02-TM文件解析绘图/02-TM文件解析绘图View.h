
// 02-TM文件解析绘图View.h : CMy02TM文件解析绘图View 类的接口
//

#pragma once


class CMy02TM文件解析绘图View : public CView
{
protected: // 仅从序列化创建
	CMy02TM文件解析绘图View();
	DECLARE_DYNCREATE(CMy02TM文件解析绘图View)

// 特性
public:
	CMy02TM文件解析绘图Doc* GetDocument() const;

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
	virtual ~CMy02TM文件解析绘图View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

private:
	void ResetCenterOrg(CDC * pDC);
	void DrawOrgLine(CDC * pDC);
	bool LoadTMFile(char * filename);
	void InitDraw();
	void ClearDrawData();
	void ReLoadDrawData(char * filename);
	void DrawVPolygon(CDC* pDC);
	int m_pointcount;
	int m_tranglecount;
	double ** m_points;
	int ** m_trangle;
	bool m_isload;
	int m_drawtype;
	int m_shrink;
	bool m_viewOrgLine;
	bool m_centerOrg;
	bool m_openeye;
public:
	afx_msg void OnSelectCenterOrg();
	afx_msg void OnSelectViewOrgLine();
	afx_msg void OnSelectViewMode();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelectShrink();
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSelectResetShrink();
	afx_msg void OnSelectEyeView();
};

#ifndef _DEBUG  // 02-TM文件解析绘图View.cpp 中的调试版本
inline CMy02TM文件解析绘图Doc* CMy02TM文件解析绘图View::GetDocument() const
   { return reinterpret_cast<CMy02TM文件解析绘图Doc*>(m_pDocument); }
#endif

