
// 08-���������ʹ��.h : 08-���������ʹ�� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy08���������ʹ��App:
// �йش����ʵ�֣������ 08-���������ʹ��.cpp
//

class CMy08���������ʹ��App : public CWinApp
{
public:
	CMy08���������ʹ��App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy08���������ʹ��App theApp;
