
class myApp :public CWinApp
{
public:
	virtual BOOL InitInstance();
};
class myButton :public CButton
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClicked();
};
class myEdit :public CEdit
{
public:

};
class myListBox :public CListBox
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
class myWindow :public CFrameWnd
{
private:
	friend class myButton;
	friend class myEdit;
	friend class myListBox;
	int m_wWid;
	int m_wHei;
	
public:
	myButton * m_enter;
	myEdit * m_edit;
	myListBox * m_listbox;
	myWindow();
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};