
// 08-图形消隐与深度缓冲.h : 08-图形消隐与深度缓冲 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy08图形消隐与深度缓冲App:
// 有关此类的实现，请参阅 08-图形消隐与深度缓冲.cpp
//

class CMy08图形消隐与深度缓冲App : public CWinApp
{
public:
	CMy08图形消隐与深度缓冲App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy08图形消隐与深度缓冲App theApp;
