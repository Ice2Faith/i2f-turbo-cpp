
// 客户端Dlg.h : 头文件
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

// C客户端Dlg 对话框
class C客户端Dlg : public CDialogEx
{
// 构造
public:
	C客户端Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	SOCKET clientSock;
	void ProcessMsgData(PSERVICE_DATA data);
	// 生成的消息映射函数
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
