
// 09-��άģ�͹���.h : 09-��άģ�͹��� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy09��άģ�͹���App:
// �йش����ʵ�֣������ 09-��άģ�͹���.cpp
//

class CMy09��άģ�͹���App : public CWinApp
{
public:
	CMy09��άģ�͹���App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy09��άģ�͹���App theApp;
