
// 24-APC�첽���̵���ע��DLL.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy24APC�첽���̵���ע��DLLApp: 
// �йش����ʵ�֣������ 24-APC�첽���̵���ע��DLL.cpp
//

class CMy24APC�첽���̵���ע��DLLApp : public CWinApp
{
public:
	CMy24APC�첽���̵���ע��DLLApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy24APC�첽���̵���ע��DLLApp theApp;