
// 21-��¼����ԭ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy21��¼����ԭ��App: 
// �йش����ʵ�֣������ 21-��¼����ԭ��.cpp
//

class CMy21��¼����ԭ��App : public CWinApp
{
public:
	CMy21��¼����ԭ��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy21��¼����ԭ��App theApp;