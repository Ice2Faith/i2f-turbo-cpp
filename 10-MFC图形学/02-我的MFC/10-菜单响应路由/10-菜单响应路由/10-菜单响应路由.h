
// 10-�˵���Ӧ·��.h : 10-�˵���Ӧ·�� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy10�˵���Ӧ·��App:
// �йش����ʵ�֣������ 10-�˵���Ӧ·��.cpp
//

class CMy10�˵���Ӧ·��App : public CWinApp
{
public:
	CMy10�˵���Ӧ·��App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTestDemo();
};

extern CMy10�˵���Ӧ·��App theApp;
