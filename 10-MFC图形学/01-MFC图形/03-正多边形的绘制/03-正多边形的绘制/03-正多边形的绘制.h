
// 03-正多边形的绘制.h : 03-正多边形的绘制 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy03正多边形的绘制App:
// 有关此类的实现，请参阅 03-正多边形的绘制.cpp
//

class CMy03正多边形的绘制App : public CWinApp
{
public:
	CMy03正多边形的绘制App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy03正多边形的绘制App theApp;
