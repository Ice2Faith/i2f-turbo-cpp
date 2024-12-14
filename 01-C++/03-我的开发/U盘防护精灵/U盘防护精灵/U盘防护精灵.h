
// U盘防护精灵.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CU盘防护精灵App: 
// 有关此类的实现，请参阅 U盘防护精灵.cpp
//

class CU盘防护精灵App : public CWinApp
{
public:
	CU盘防护精灵App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CU盘防护精灵App theApp;