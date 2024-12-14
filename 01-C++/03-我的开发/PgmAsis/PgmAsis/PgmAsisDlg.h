
// PgmAsisDlg.h : ͷ�ļ�
//

#pragma once


// CPgmAsisDlg �Ի���
class CPgmAsisDlg : public CDialogEx
{
// ����
public:
	CPgmAsisDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PGMASIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonDoit();
	CString m_str_input;
	CString m_str_output;
	void InitControls();
	void makeCHeader();
	void makeInPath();
	void makeOutPath();
	void makeInText();
	void makeOutText();
	void makeGetSetMethod();
	void makeClass();
	void makeSwitch();
	void makeIfElseIf();
	void makeStrToArray();
	void makeValueArray();
	afx_msg void OnBnClickedButtonClean();
};
