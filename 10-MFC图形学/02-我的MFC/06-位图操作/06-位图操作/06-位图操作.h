
// 06-位图操作.h : 06-位图操作 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy06位图操作App:
// 有关此类的实现，请参阅 06-位图操作.cpp
//

class CMy06位图操作App : public CWinApp
{
public:
	CMy06位图操作App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy06位图操作App theApp;
