
// 11-�˵���̬����.h : 11-�˵���̬���� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy11�˵���̬����App:
// �йش����ʵ�֣������ 11-�˵���̬����.cpp
//

class CMy11�˵���̬����App : public CWinApp
{
public:
	CMy11�˵���̬����App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy11�˵���̬����App theApp;
