
// 08-光标插入符的使用.h : 08-光标插入符的使用 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy08光标插入符的使用App:
// 有关此类的实现，请参阅 08-光标插入符的使用.cpp
//

class CMy08光标插入符的使用App : public CWinApp
{
public:
	CMy08光标插入符的使用App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy08光标插入符的使用App theApp;
