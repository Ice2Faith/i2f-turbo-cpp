
// 04-�Զ�����Ϣ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy04�Զ�����ϢApp: 
// �йش����ʵ�֣������ 04-�Զ�����Ϣ.cpp
//

class CMy04�Զ�����ϢApp : public CWinApp
{
public:
	CMy04�Զ�����ϢApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy04�Զ�����ϢApp theApp;