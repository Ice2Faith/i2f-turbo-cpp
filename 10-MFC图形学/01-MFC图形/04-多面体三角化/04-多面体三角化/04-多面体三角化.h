
// 04-多面体三角化.h : 04-多面体三角化 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy04多面体三角化App:
// 有关此类的实现，请参阅 04-多面体三角化.cpp
//

class CMy04多面体三角化App : public CWinApp
{
public:
	CMy04多面体三角化App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy04多面体三角化App theApp;
