
// 13-��ʱ��ͼƬ�ƶ�.h : 13-��ʱ��ͼƬ�ƶ� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy13��ʱ��ͼƬ�ƶ�App:
// �йش����ʵ�֣������ 13-��ʱ��ͼƬ�ƶ�.cpp
//

class CMy13��ʱ��ͼƬ�ƶ�App : public CWinAppEx
{
public:
	CMy13��ʱ��ͼƬ�ƶ�App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy13��ʱ��ͼƬ�ƶ�App theApp;
