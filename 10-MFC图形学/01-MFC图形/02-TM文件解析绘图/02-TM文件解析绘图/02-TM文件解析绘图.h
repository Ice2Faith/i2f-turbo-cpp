
// 02-TM文件解析绘图.h : 02-TM文件解析绘图 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy02TM文件解析绘图App:
// 有关此类的实现，请参阅 02-TM文件解析绘图.cpp
//

class CMy02TM文件解析绘图App : public CWinApp
{
public:
	CMy02TM文件解析绘图App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy02TM文件解析绘图App theApp;
