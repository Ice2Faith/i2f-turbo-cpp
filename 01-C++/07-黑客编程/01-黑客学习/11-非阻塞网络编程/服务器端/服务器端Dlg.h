
// ��������Dlg.h : ͷ�ļ�
//

#pragma once
//�û����첽����ͨ�Ŵ�����Ϣ
#define UM_USER_SOCK (WM_USER+0x101)
#include<WinSock2.h>
#include "afxwin.h"
#define HELPINFO "Use Guide:\
	Support all cmd command exec."
//��Ϣ����
#define TYPE_TEXT 't'
#define TYPE_DATA 'b'
typedef struct _service_data
{
	BYTE s_type;//������Text�ı����ͣ�����Data�����ƽṹ����
	BYTE s_class;//�����Data���ͣ���ָ������һ���ṹ������������
	TCHAR s_value[2048];//���������ݱ��棬������ʲô����
}SERVICE_DATA,* PSERVICE_DATA;

// C��������Dlg �Ի���
class C��������Dlg : public CDialogEx
{
// ����
public:
	C��������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	SOCKET serverSock;
	SOCKET clientSock;
	void ProcessMsgData(char * buffer);
	CString ExecuteCmd(CString str);

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnUserSock(WPARAM wParam, LPARAM lParam);//�����Ϣӳ��
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	CListBox m_listinfo;
};
