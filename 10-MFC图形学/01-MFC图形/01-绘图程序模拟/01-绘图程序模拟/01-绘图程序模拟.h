
// 01-��ͼ����ģ��.h : 01-��ͼ����ģ�� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy01��ͼ����ģ��App:
// �йش����ʵ�֣������ 01-��ͼ����ģ��.cpp
//

class CMy01��ͼ����ģ��App : public CWinAppEx
{
public:
	CMy01��ͼ����ģ��App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy01��ͼ����ģ��App theApp;
