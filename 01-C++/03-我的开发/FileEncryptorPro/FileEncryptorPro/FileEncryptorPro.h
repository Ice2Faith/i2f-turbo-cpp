
// FileEncryptorPro.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileEncryptorProApp: 
// �йش����ʵ�֣������ FileEncryptorPro.cpp
//

class CFileEncryptorProApp : public CWinApp
{
public:
	CFileEncryptorProApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileEncryptorProApp theApp;