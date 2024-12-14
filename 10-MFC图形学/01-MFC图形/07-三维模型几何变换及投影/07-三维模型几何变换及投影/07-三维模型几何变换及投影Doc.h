
// 07-三维模型几何变换及投影Doc.h : CMy07三维模型几何变换及投影Doc 类的接口
//


#pragma once


class CMy07三维模型几何变换及投影Doc : public CDocument
{
protected: // 仅从序列化创建
	CMy07三维模型几何变换及投影Doc();
	DECLARE_DYNCREATE(CMy07三维模型几何变换及投影Doc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMy07三维模型几何变换及投影Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
