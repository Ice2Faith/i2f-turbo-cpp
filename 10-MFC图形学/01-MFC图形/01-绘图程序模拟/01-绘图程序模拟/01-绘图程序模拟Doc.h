
// 01-��ͼ����ģ��Doc.h : CMy01��ͼ����ģ��Doc ��Ľӿ�
//


#pragma once


class CMy01��ͼ����ģ��Doc : public CDocument
{
protected: // �������л�����
	CMy01��ͼ����ģ��Doc();
	DECLARE_DYNCREATE(CMy01��ͼ����ģ��Doc)

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
	virtual ~CMy01��ͼ����ģ��Doc();
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
};
