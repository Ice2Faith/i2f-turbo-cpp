
// 38-PE�ļ���������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy38PE�ļ���������App: 
// �йش����ʵ�֣������ 38-PE�ļ���������.cpp
//

class CMy38PE�ļ���������App : public CWinApp
{
public:
	CMy38PE�ļ���������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy38PE�ļ���������App theApp;