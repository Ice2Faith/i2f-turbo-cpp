
// 16-�༭��ʹ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy16�༭��ʹ��App: 
// �йش����ʵ�֣������ 16-�༭��ʹ��.cpp
//

class CMy16�༭��ʹ��App : public CWinApp
{
public:
	CMy16�༭��ʹ��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy16�༭��ʹ��App theApp;