
// 16-ע������-���������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy16ע���������������App: 
// �йش����ʵ�֣������ 16-ע������-���������.cpp
//

class CMy16ע���������������App : public CWinApp
{
public:
	CMy16ע���������������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy16ע���������������App theApp;