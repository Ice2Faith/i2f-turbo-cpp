
// �������Dlg.h : ͷ�ļ�
//

#pragma once


// C�������Dlg �Ի���
class C�������Dlg : public CDialogEx
{
// ����
private:
	char disk;
	short OpeMode;
	short TimeMode;
	int TimeCount;
	WCHAR COpeMode[2][20];
	WCHAR CTimeMode[3][20];
	void HideSystem(char * mind);
public:
	C�������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	void UpdateDisplay();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonShutdown();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonReboot();
	afx_msg void OnBnClickedButtonLock();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonStartope();
	afx_msg void OnBnClickedButtonTimemode();
	afx_msg void OnBnClickedButtonMode();
	afx_msg void OnBnClickedButtonCmd();
	afx_msg void OnBnClickedButtonPowershell();
	afx_msg void OnBnClickedButtonRegedit();
	afx_msg void OnBnClickedButtonImmuautorun();
	afx_msg void OnBnClickedButtonUpdisk();
	afx_msg void OnBnClickedButtonDowndisk();
};
