#pragma once


// myDlgIdentity �Ի���

class myDlgIdentity : public CDialogEx
{
	DECLARE_DYNAMIC(myDlgIdentity)

public:
	myDlgIdentity(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~myDlgIdentity();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
