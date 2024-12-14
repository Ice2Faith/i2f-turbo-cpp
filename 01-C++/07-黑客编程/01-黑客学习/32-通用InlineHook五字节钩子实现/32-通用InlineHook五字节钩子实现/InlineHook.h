#ifndef _CINLINEHOOK_H_
#define _CINLINEHOOK_H_
#include<Windows.h>
class CInlineHook
{
public:
	CInlineHook();
	~CInlineHook();
	//��ʼHOOK
	BOOL Hook(LPTSTR pszModuleName,//HOOK��ģ������
		LPSTR pszFuncName,//HOOK�ĺ�������
		PROC pfcHookFunc);//Ҫ�滻�ĺ�����ַ
	BOOL UnHook();//ȡ��HOOK
	BOOL ReHook();//����HOOK
private:
	VOID InitHook();
	PROC m_pfnOrigin;//������ַ
	BYTE m_bOldBytes[5];//������ڴ���
	BYTE m_bNewBytes[5];//Inline����
};
#endif // _CINLINEHOOK_H_
