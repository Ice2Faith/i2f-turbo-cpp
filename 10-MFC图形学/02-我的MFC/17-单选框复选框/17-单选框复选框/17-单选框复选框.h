
// 17-��ѡ��ѡ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy17��ѡ��ѡ��App: 
// �йش����ʵ�֣������ 17-��ѡ��ѡ��.cpp
//

class CMy17��ѡ��ѡ��App : public CWinApp
{
public:
	CMy17��ѡ��ѡ��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy17��ѡ��ѡ��App theApp;