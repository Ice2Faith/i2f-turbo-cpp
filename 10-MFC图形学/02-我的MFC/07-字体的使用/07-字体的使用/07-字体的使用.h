
// 07-�����ʹ��.h : 07-�����ʹ�� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy07�����ʹ��App:
// �йش����ʵ�֣������ 07-�����ʹ��.cpp
//

class CMy07�����ʹ��App : public CWinApp
{
public:
	CMy07�����ʹ��App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy07�����ʹ��App theApp;
