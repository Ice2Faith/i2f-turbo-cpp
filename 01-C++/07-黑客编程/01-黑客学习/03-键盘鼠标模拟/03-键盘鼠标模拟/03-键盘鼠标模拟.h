
// 03-�������ģ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy03�������ģ��App: 
// �йش����ʵ�֣������ 03-�������ģ��.cpp
//

class CMy03�������ģ��App : public CWinApp
{
public:
	CMy03�������ģ��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy03�������ģ��App theApp;