
// 24-APC�첽���̵���ע��DLLDlg.h : ͷ�ļ�
//

#pragma once


// CMy24APC�첽���̵���ע��DLLDlg �Ի���
class CMy24APC�첽���̵���ע��DLLDlg : public CDialogEx
{
// ����
public:
	CMy24APC�첽���̵���ע��DLLDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY24APCDLL_DIALOG };

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
	afx_msg void OnBnClickedButtonInject();
	DWORD GetProcessId(TCHAR * szProcessName);
	void InjectDLL(DWORD dwpid, char * szDllName);
};
