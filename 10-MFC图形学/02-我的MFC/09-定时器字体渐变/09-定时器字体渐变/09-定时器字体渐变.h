
// 09-��ʱ�����彥��.h : 09-��ʱ�����彥�� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy09��ʱ�����彥��App:
// �йش����ʵ�֣������ 09-��ʱ�����彥��.cpp
//

class CMy09��ʱ�����彥��App : public CWinApp
{
public:
	CMy09��ʱ�����彥��App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy09��ʱ�����彥��App theApp;
