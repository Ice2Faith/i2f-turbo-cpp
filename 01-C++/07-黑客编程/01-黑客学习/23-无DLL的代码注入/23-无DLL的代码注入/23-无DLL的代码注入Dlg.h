
// 23-��DLL�Ĵ���ע��Dlg.h : ͷ�ļ�
//

#pragma once


// CMy23��DLL�Ĵ���ע��Dlg �Ի���
class CMy23��DLL�Ĵ���ע��Dlg : public CDialogEx
{
// ����
public:
	CMy23��DLL�Ĵ���ע��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY23DLL_DIALOG };

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
	DWORD getProcessID(TCHAR * szProcessName);
	void InjectCode(DWORD dwpid);
};
