
// UDiskSpider.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDiskSpiderApp: 
// �йش����ʵ�֣������ UDiskSpider.cpp
//

class CUDiskSpiderApp : public CWinApp
{
public:
	CUDiskSpiderApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUDiskSpiderApp theApp;