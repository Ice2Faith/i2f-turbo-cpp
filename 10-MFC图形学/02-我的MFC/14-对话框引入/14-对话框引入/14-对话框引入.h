
// 14-�Ի�������.h : 14-�Ի������� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy14�Ի�������App:
// �йش����ʵ�֣������ 14-�Ի�������.cpp
//

class CMy14�Ի�������App : public CWinAppEx
{
public:
	CMy14�Ի�������App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy14�Ի�������App theApp;
