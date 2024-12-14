
// 无尽躲避.h : 无尽躲避 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// C无尽躲避App:
// 有关此类的实现，请参阅 无尽躲避.cpp
//

class C无尽躲避App : public CWinApp
{
public:
	C无尽躲避App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C无尽躲避App theApp;
