
// 10-�˵���Ӧ·��Doc.h : CMy10�˵���Ӧ·��Doc ��Ľӿ�
//


#pragma once


class CMy10�˵���Ӧ·��Doc : public CDocument
{
protected: // �������л�����
	CMy10�˵���Ӧ·��Doc();
	DECLARE_DYNCREATE(CMy10�˵���Ӧ·��Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMy10�˵���Ӧ·��Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	//afx_msg void OnTestDemo();
};
