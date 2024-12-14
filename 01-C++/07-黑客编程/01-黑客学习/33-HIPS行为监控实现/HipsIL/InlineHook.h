#ifndef _CINLINEHOOK_H_
#define _CINLINEHOOK_H_
#include<Windows.h>
class CInlineHook
{
public:
	CInlineHook();
	~CInlineHook();
	//开始HOOK
	BOOL Hook(LPTSTR pszModuleName,//HOOK的模块名称
		LPSTR pszFuncName,//HOOK的函数名称
		PROC pfcHookFunc);//要替换的函数地址
	BOOL UnHook();//取消HOOK
	BOOL ReHook();//重新HOOK
private:
	VOID InitHook();
	PROC m_pfnOrigin;//函数地址
	BYTE m_bOldBytes[5];//函数入口代码
	BYTE m_bNewBytes[5];//Inline代码
};
#endif // _CINLINEHOOK_H_
