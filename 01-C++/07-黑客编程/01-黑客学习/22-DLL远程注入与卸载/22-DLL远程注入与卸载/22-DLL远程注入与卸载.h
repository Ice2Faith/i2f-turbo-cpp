
// 22-DLLԶ��ע����ж��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy22DLLԶ��ע����ж��App: 
// �йش����ʵ�֣������ 22-DLLԶ��ע����ж��.cpp
//

class CMy22DLLԶ��ע����ж��App : public CWinApp
{
public:
	CMy22DLLԶ��ע����ж��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy22DLLԶ��ע����ж��App theApp;