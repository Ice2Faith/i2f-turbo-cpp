#pragma once


// CBootItemAdder �Ի���

class CBootItemAdder : public CDialogEx
{
	DECLARE_DYNAMIC(CBootItemAdder)

public:
	CBootItemAdder(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBootItemAdder();

// �Ի�������
	enum { IDD = IDD_DLG_BOOTINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_bootkey;
	CString m_bootvalue;
};
