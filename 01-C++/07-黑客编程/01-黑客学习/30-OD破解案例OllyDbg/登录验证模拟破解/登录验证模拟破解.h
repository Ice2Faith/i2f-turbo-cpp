
// ��¼��֤ģ���ƽ�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C��¼��֤ģ���ƽ�App: 
// �йش����ʵ�֣������ ��¼��֤ģ���ƽ�.cpp
//

class C��¼��֤ģ���ƽ�App : public CWinApp
{
public:
	C��¼��֤ģ���ƽ�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C��¼��֤ģ���ƽ�App theApp;