#include<Windows.h>
//���������ӿڸ��ⲿ���ã�����Լ����д��
extern "C" __declspec(dllexport) VOID MsgBox(char * msg);
//������ʵ�ֺ���
VOID MsgBox(char * msg)
{
	char moduleName[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, moduleName, MAX_PATH);
	MessageBox(NULL, msg, moduleName, MB_OK);
}
/*
������C���Գ����Win32�������main(),WinMain(),��������ڶ���������ʱ��������ڣ�ֻ�Ǳ��ʱ�����
��DllMain()���������dll�����ص�ʱ������ô���Բ�ҪDllMain()��Ҳ���ǿ��Բ�Ҫ���

DLL�ĵ��÷�ʽ��
	��ʽ1��
		Ԥ����+������ʽ��
			#pragma comment(lib,"DllFileName.lib")
			extern "C" VOID MsgBox(char * msg);
		���ַ�ʽ����Ҫ�ѱ��������DLL��.lib�ļ����Ƶ�����Ŀ¼���ܱ���ɹ���
		���е�ʱ����Ҫ��.dll�ļ��ͱ��������EXE�ļ�����һ���������
		���һ��DLL�ķ�������Ҫ����.dll .lib .h�ļ�
	��ʽ2��
		����ָ��+DLL��̬���أ�
			HMODULE hmod=LoadLibrary("DllFileName.dll");
			if(hmod==NULL)
				return -1;
			typedef VOID (*FUNC)(char *);
			FUNC msgBox=(FUNC)GetProcAddress(hmod,"MsgBox");
			msgBox("hello");
		���ַ�ʽ������ʱ��Ҫһ��.dll�ļ��ڹ���Ŀ¼�£���������������е�������룬����.dll�ļ���ʧ��Ҳ����Ӱ���������ֵ�����
		���кܸߵ������
	��غ������ܣ�
		���ؿ⺯����
			HMODULE LoadLibrary(LPCTSTR lpFileName);//����:Ҫ���ص��ļ������ɹ��ͷ���һ��ģ����
		��ȡģ���еĴ�������ַ������
			FARPROC GetProcAddress(HMODULE hmod,LPCSTR lpProcName);//������ģ������ģ���еĺ�����������һ����ַ����ͨ������ָ�����ת��
	DLL�⵼���鿴���ߣ�
		VS�Դ���Depends����
		��������PEID����������ʶ�����ָ����Ϣ�������������汾���ӿ���Ϣ�ȣ������
*/
BOOL WINAPI DllMain(
	HINSTANCE hinstDll,//��ǰdllģ��ľ��������̬���ʵ�����
	DWORD fdwReason,//�����õ�ԭ���������������������switch
	LPVOID lpvReserved)//����������������
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH://Dll�����̼���ʱ��DllMain������
	{
								MsgBox("Simple Dll be process load.");
	}
		break;
	case DLL_PROCESS_DETACH://Dll������ж��ʱ��DllMain������
	{
								MsgBox("Simple Dll be process unload.");
	}
		break;
	case DLL_THREAD_ATTACH://���������̴߳���ʱ��DllMain������
	{
							  // MsgBox("Simple Dll be thread load.");
	}
		break;
	case DLL_THREAD_DETACH://���������߳̽���ʱ��DllMain������
	{
							//   MsgBox("Simple Dll be thread unload.");
	}
		break;
	}
	return TRUE;
}