
// 服务器端Dlg.h : 头文件
//

#pragma once
//用户的异步网络通信触发消息
#define UM_USER_SOCK (WM_USER+0x101)
#include<WinSock2.h>
#include "afxwin.h"
#define HELPINFO "Use Guide:\
	Support all cmd command exec."
//消息类型
#define TYPE_TEXT 't'
#define TYPE_DATA 'b'
typedef struct _service_data
{
	BYTE s_type;//区分是Text文本类型，还是Data二进制结构类型
	BYTE s_class;//如果是Data类型，则指明是哪一个结构或者数据类型
	TCHAR s_value[2048];//真正的数据保存，不管是什么类型
}SERVICE_DATA,* PSERVICE_DATA;

// C服务器端Dlg 对话框
class C服务器端Dlg : public CDialogEx
{
// 构造
public:
	C服务器端Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	SOCKET serverSock;
	SOCKET clientSock;
	void ProcessMsgData(char * buffer);
	CString ExecuteCmd(CString str);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnUserSock(WPARAM wParam, LPARAM lParam);//添加消息映射
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	CListBox m_listinfo;
};
