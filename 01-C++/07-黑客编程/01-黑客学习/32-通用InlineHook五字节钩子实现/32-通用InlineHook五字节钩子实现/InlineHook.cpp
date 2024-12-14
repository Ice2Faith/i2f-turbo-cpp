#include "InlineHook.h"

VOID CInlineHook::InitHook()
{
	m_pfnOrigin = NULL;
	ZeroMemory(m_bOldBytes, 5);
	ZeroMemory(m_bNewBytes, 5);
}
CInlineHook::CInlineHook()
{
	InitHook();
}


CInlineHook::~CInlineHook()
{
	UnHook();
	InitHook();
}
BOOL CInlineHook::Hook(LPTSTR pszModuleName,
	LPSTR pszFuncName,
	PROC pfcHookFunc)
{
	BOOL bret = FALSE;
	//获取指定模块中指定函数的地址
	m_pfnOrigin = (PROC)GetProcAddress(
		GetModuleHandle(pszModuleName),
		pszFuncName);
	if (m_pfnOrigin != NULL)
	{
		DWORD dwNum = 0;
		//保存该地址处5字节的内容，即地址4字节+跳转符号1字节
		bret=ReadProcessMemory(
			GetCurrentProcess(),
			m_pfnOrigin,
			m_bOldBytes,
			5, &dwNum);
		if (bret == FALSE)
			return bret;
		//构造跳转命令JMP
		m_bNewBytes[0] = '\xe9';
		//剩余4字节地址填入
		*(DWORD *)(m_bNewBytes + 1) = (DWORD)pfcHookFunc - (DWORD)m_pfnOrigin - 5;
		//写入跳转的目标地址
		bret=WriteProcessMemory(
			GetCurrentProcess(),
			m_pfnOrigin,
			m_bNewBytes,
			5, 
			&dwNum);
		if (bret == FALSE)
			return bret;
		bret = TRUE;
	}
	return bret;
}
BOOL CInlineHook::UnHook()
{
	if (m_pfnOrigin != 0)
	{
		DWORD dwNUm = 0;
		//写回原来的跳转地址
		BOOL bret = WriteProcessMemory(
			GetCurrentProcess(),
			m_pfnOrigin,
			m_bOldBytes,
			5,
			&dwNUm);
		return bret;
	}
	return TRUE;
}
BOOL CInlineHook::ReHook()
{
	if (m_pfnOrigin != 0)
	{
		DWORD dwNUm = 0;
		//重新写入新的跳转语句
		BOOL bret = WriteProcessMemory(
			GetCurrentProcess(),
			m_pfnOrigin,
			m_bNewBytes,
			5,
			&dwNUm);
		return bret;
	}
	return FALSE;
}