
// 17-������ر��-���������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy17������ر�̷��������App: 
// �йش����ʵ�֣������ 17-������ر��-���������.cpp
//

class CMy17������ر�̷��������App : public CWinApp
{
public:
	CMy17������ر�̷��������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy17������ر�̷��������App theApp;