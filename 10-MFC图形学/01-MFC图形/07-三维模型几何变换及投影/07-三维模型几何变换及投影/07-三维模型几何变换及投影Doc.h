
// 07-��άģ�ͼ��α任��ͶӰDoc.h : CMy07��άģ�ͼ��α任��ͶӰDoc ��Ľӿ�
//


#pragma once


class CMy07��άģ�ͼ��α任��ͶӰDoc : public CDocument
{
protected: // �������л�����
	CMy07��άģ�ͼ��α任��ͶӰDoc();
	DECLARE_DYNCREATE(CMy07��άģ�ͼ��α任��ͶӰDoc)

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
	virtual ~CMy07��άģ�ͼ��α任��ͶӰDoc();
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
