#include"HipsIL.h"

BOOL APIENTRY DllMain(
	HANDLE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
							  
							   OpenHooks(hModule);
							  
	}
		break;
	case DLL_PROCESS_DETACH:
	{
							   void CloseHooks();
							   
	}
		break;
	}
	return TRUE;
}
