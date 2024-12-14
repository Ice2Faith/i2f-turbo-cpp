
// 06-图形的光栅扫描显示.h : 06-图形的光栅扫描显示 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy06图形的光栅扫描显示App:
// 有关此类的实现，请参阅 06-图形的光栅扫描显示.cpp
//

class CMy06图形的光栅扫描显示App : public CWinApp
{
public:
	CMy06图形的光栅扫描显示App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy06图形的光栅扫描显示App theApp;
