// myDlgIdentity.cpp : 实现文件
//

#include "stdafx.h"
#include "14-对话框引入.h"
#include "myDlgIdentity.h"
#include "afxdialogex.h"


// myDlgIdentity 对话框

IMPLEMENT_DYNAMIC(myDlgIdentity, CDialogEx)

myDlgIdentity::myDlgIdentity(CWnd* pParent /*=NULL*/)
	: CDialogEx(myDlgIdentity::IDD, pParent)
{

}

myDlgIdentity::~myDlgIdentity()
{
}

void myDlgIdentity::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(myDlgIdentity, CDialogEx)
END_MESSAGE_MAP()


// myDlgIdentity 消息处理程序
