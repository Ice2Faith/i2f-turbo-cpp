
// 02-TM�ļ�������ͼDoc.h : CMy02TM�ļ�������ͼDoc ��Ľӿ�
//


#pragma once


class CMy02TM�ļ�������ͼDoc : public CDocument
{
protected: // �������л�����
	CMy02TM�ļ�������ͼDoc();
	DECLARE_DYNCREATE(CMy02TM�ļ�������ͼDoc)

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
	virtual ~CMy02TM�ļ�������ͼDoc();
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
