
// 34-U盘防御软件.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMy34U盘防御软件App: 
// 有关此类的实现，请参阅 34-U盘防御软件.cpp
//

class CMy34U盘防御软件App : public CWinApp
{
public:
	CMy34U盘防御软件App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMy34U盘防御软件App theApp;