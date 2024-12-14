
// �ͻ���Dlg.h : ͷ�ļ�
//

#pragma once
#define UM_USER_SOCK (WM_USER+0x101)
#include<WinSock2.h>
#include "afxwin.h"
#define TYPE_TEXT 't'
#define TYPE_DATA 'b'
typedef struct _service_data
{
	BYTE s_type;
	BYTE s_class;
	TCHAR s_value[2048];
}SERVICE_DATA, *PSERVICE_DATA;

// C�ͻ���Dlg �Ի���
class C�ͻ���Dlg : public CDialogEx
{
// ����
public:
	C�ͻ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	SOCKET clientSock;
	void ProcessMsgData(PSERVICE_DATA data);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnUserSock(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnClose();
	CListBox m_listinfo;
};
