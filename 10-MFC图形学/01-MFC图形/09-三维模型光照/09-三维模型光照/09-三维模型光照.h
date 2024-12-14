
// 09-三维模型光照.h : 09-三维模型光照 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy09三维模型光照App:
// 有关此类的实现，请参阅 09-三维模型光照.cpp
//

class CMy09三维模型光照App : public CWinApp
{
public:
	CMy09三维模型光照App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy09三维模型光照App theApp;
