
// 13-��ʱ��ͼƬ�ƶ�Doc.h : CMy13��ʱ��ͼƬ�ƶ�Doc ��Ľӿ�
//


#pragma once


class CMy13��ʱ��ͼƬ�ƶ�Doc : public CDocument
{
protected: // �������л�����
	CMy13��ʱ��ͼƬ�ƶ�Doc();
	DECLARE_DYNCREATE(CMy13��ʱ��ͼƬ�ƶ�Doc)

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
	virtual ~CMy13��ʱ��ͼƬ�ƶ�Doc();
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
