
// 04-事件作业.h : 04-事件作业 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy04事件作业App:
// 有关此类的实现，请参阅 04-事件作业.cpp
//

class CMy04事件作业App : public CWinAppEx
{
public:
	CMy04事件作业App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy04事件作业App theApp;
