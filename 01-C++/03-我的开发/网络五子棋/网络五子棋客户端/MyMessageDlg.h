#pragma once


// MyMessageDlg 对话框
#define ID_TIMER_WAIT 0x1001
enum SelBtnType{MMD_NULL=0,MMD_YES=1,MMD_NO=2};
class MyMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MyMessageDlg)

public:
	MyMessageDlg(CWnd* pParent = NULL);   // 标准构造函数
	MyMessageDlg(CString Context,CString Title=L"",long msWaitTime=0,CWnd* pParent = NULL);
	virtual ~MyMessageDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_context;
	CString m_title;
	long startTime;
	SelBtnType SelBtnType;
	long msWaittime;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
