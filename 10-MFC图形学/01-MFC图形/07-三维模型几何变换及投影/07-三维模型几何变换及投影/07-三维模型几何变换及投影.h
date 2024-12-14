
// 07-三维模型几何变换及投影.h : 07-三维模型几何变换及投影 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy07三维模型几何变换及投影App:
// 有关此类的实现，请参阅 07-三维模型几何变换及投影.cpp
//

class CMy07三维模型几何变换及投影App : public CWinApp
{
public:
	CMy07三维模型几何变换及投影App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy07三维模型几何变换及投影App theApp;
