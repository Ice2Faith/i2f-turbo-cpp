
// 网络五子棋客户端.h : 网络五子棋客户端 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// C网络五子棋客户端App:
// 有关此类的实现，请参阅 网络五子棋客户端.cpp
//

class C网络五子棋客户端App : public CWinApp
{
public:
	C网络五子棋客户端App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C网络五子棋客户端App theApp;
