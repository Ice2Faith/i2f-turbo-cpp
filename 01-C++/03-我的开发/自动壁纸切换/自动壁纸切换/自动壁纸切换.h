
// 自动壁纸切换.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// C自动壁纸切换App: 
// 有关此类的实现，请参阅 自动壁纸切换.cpp
//

class C自动壁纸切换App : public CWinApp
{
public:
	C自动壁纸切换App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C自动壁纸切换App theApp;