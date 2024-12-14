#pragma once


// myDlgIdentity 对话框

class myDlgIdentity : public CDialogEx
{
	DECLARE_DYNAMIC(myDlgIdentity)

public:
	myDlgIdentity(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~myDlgIdentity();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
