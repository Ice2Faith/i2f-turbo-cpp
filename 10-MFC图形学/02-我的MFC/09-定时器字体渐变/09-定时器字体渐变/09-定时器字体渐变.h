
// 09-定时器字体渐变.h : 09-定时器字体渐变 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy09定时器字体渐变App:
// 有关此类的实现，请参阅 09-定时器字体渐变.cpp
//

class CMy09定时器字体渐变App : public CWinApp
{
public:
	CMy09定时器字体渐变App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy09定时器字体渐变App theApp;
