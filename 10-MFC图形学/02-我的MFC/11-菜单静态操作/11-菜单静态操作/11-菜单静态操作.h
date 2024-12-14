
// 11-菜单静态操作.h : 11-菜单静态操作 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy11菜单静态操作App:
// 有关此类的实现，请参阅 11-菜单静态操作.cpp
//

class CMy11菜单静态操作App : public CWinApp
{
public:
	CMy11菜单静态操作App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy11菜单静态操作App theApp;
