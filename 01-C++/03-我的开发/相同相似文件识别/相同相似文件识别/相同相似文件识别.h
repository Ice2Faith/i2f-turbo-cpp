
// ��ͬ�����ļ�ʶ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C��ͬ�����ļ�ʶ��App: 
// �йش����ʵ�֣������ ��ͬ�����ļ�ʶ��.cpp
//

class C��ͬ�����ļ�ʶ��App : public CWinApp
{
public:
	C��ͬ�����ļ�ʶ��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C��ͬ�����ļ�ʶ��App theApp;