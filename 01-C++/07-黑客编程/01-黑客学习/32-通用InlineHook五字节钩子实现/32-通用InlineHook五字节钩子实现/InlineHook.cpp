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
	//��ȡָ��ģ����ָ�������ĵ�ַ
	m_pfnOrigin = (PROC)GetProcAddress(
		GetModuleHandle(pszModuleName),
		pszFuncName);
	if (m_pfnOrigin != NULL)
	{
		DWORD dwNum = 0;
		//����õ�ַ��5�ֽڵ����ݣ�����ַ4�ֽ�+��ת����1�ֽ�
		bret=ReadProcessMemory(
			GetCurrentProcess(),
			m_pfnOrigin,
			m_bOldBytes,
			5, &dwNum);
		if (bret == FALSE)
			return bret;
		//������ת����JMP
		m_bNewBytes[0] = '\xe9';
		//ʣ��4�ֽڵ�ַ����
		*(DWORD *)(m_bNewBytes + 1) = (DWORD)pfcHookFunc - (DWORD)m_pfnOrigin - 5;
		//д����ת��Ŀ���ַ
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
		//д��ԭ������ת��ַ
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
		//����д���µ���ת���
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