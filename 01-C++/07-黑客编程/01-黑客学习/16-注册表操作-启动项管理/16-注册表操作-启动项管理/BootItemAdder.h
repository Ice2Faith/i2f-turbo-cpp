#pragma once


// CBootItemAdder 对话框

class CBootItemAdder : public CDialogEx
{
	DECLARE_DYNAMIC(CBootItemAdder)

public:
	CBootItemAdder(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBootItemAdder();

// 对话框数据
	enum { IDD = IDD_DLG_BOOTINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_bootkey;
	CString m_bootvalue;
};
