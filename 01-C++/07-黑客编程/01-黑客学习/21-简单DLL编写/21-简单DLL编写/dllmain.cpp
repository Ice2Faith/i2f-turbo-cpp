#include<Windows.h>
//导出函数接口给外部调用，这是约定的写法
extern "C" __declspec(dllexport) VOID MsgBox(char * msg);
//真正的实现函数
VOID MsgBox(char * msg)
{
	char moduleName[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, moduleName, MAX_PATH);
	MessageBox(NULL, msg, moduleName, MB_OK);
}
/*
区别于C语言程序和Win32程序入口main(),WinMain(),这两个入口都不是运行时的真正入口，只是编程时的入口
而DllMain()如果不考虑dll被加载的时机，那么可以不要DllMain()，也就是可以不要入口

DLL的调用方式：
	方式1：
		预编译+声明方式：
			#pragma comment(lib,"DllFileName.lib")
			extern "C" VOID MsgBox(char * msg);
		这种方式，需要把编译出来的DLL的.lib文件复制到工程目录才能编译成功，
		运行的时候需要把.dll文件和编译出来的EXE文件放在一起才能运行
		因此一般DLL的发布，需要包含.dll .lib .h文件
	方式2：
		函数指针+DLL动态加载：
			HMODULE hmod=LoadLibrary("DllFileName.dll");
			if(hmod==NULL)
				return -1;
			typedef VOID (*FUNC)(char *);
			FUNC msgBox=(FUNC)GetProcAddress(hmod,"MsgBox");
			msgBox("hello");
		这种方式：编译时需要一个.dll文件在工程目录下，并且如果不会运行到这个代码，就算.dll文件丢失，也不会影响其他部分的运行
		具有很高的灵活性
	相关函数介绍：
		加载库函数：
			HMODULE LoadLibrary(LPCTSTR lpFileName);//参数:要加载的文件名，成功就返回一个模块句柄
		获取模块中的处理函数地址函数：
			FARPROC GetProcAddress(HMODULE hmod,LPCSTR lpProcName);//参数：模块句柄，模块中的函数名，返回一个地址，可通过函数指针进行转换
	DLL库导出查看工具：
		VS自带的Depends工具
		第三方的PEID，这是用来识别软件指纹信息（开发环境、版本、加壳信息等）的软件
*/
BOOL WINAPI DllMain(
	HINSTANCE hinstDll,//当前dll模块的句柄，本动态库的实例句柄
	DWORD fdwReason,//被调用的原因，四种情况：见主函数的switch
	LPVOID lpvReserved)//保留参数，不可用
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH://Dll被进程加载时，DllMain被调用
	{
								MsgBox("Simple Dll be process load.");
	}
		break;
	case DLL_PROCESS_DETACH://Dll被进程卸载时，DllMain被调用
	{
								MsgBox("Simple Dll be process unload.");
	}
		break;
	case DLL_THREAD_ATTACH://进程中有线程创建时，DllMain被调用
	{
							  // MsgBox("Simple Dll be thread load.");
	}
		break;
	case DLL_THREAD_DETACH://进程中有线程结束时，DllMain被调用
	{
							//   MsgBox("Simple Dll be thread unload.");
	}
		break;
	}
	return TRUE;
}