
// 22-DLLԶ��ע����ж��Dlg.h : ͷ�ļ�
//

#pragma once


// CMy22DLLԶ��ע����ж��Dlg �Ի���
class CMy22DLLԶ��ע����ж��Dlg : public CDialogEx
{
// ����
public:
	CMy22DLLԶ��ע����ж��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY22DLL_DIALOG };

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
	afx_msg void OnBnClickedButtonEnterdll();
	afx_msg void OnBnClickedButtonLeavedll();
	DWORD GetProcessId(TCHAR * szProcessName);
	VOID InjectDLL(DWORD dwpid, char * szDllName);
	void UnInjectDll(DWORD dwpid, TCHAR * szDLLName);
};
