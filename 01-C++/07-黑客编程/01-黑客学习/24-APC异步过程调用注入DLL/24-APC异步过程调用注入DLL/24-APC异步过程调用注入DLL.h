
// 24-APC异步过程调用注入DLL.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMy24APC异步过程调用注入DLLApp: 
// 有关此类的实现，请参阅 24-APC异步过程调用注入DLL.cpp
//

class CMy24APC异步过程调用注入DLLApp : public CWinApp
{
public:
	CMy24APC异步过程调用注入DLLApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMy24APC异步过程调用注入DLLApp theApp;