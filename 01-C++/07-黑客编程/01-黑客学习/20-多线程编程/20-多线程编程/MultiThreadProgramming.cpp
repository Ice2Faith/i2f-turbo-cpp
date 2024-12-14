/** Name: 多线程编程*/
#include<stdio.h>
#include<Windows.h>
/*
创建线程函数：
	HANDLE CreateThread(
		LPSECURITY_ATTRIBUTES lpThreadAttributes,//创建线程的安全属性，一般取NULL
		SIZE_T dwStackSize,//指定线程使用的缺省堆栈大小，一般取NULL保持和主线程一致
		LPTHREAD_START_ROUTINE lpStartAddress,//指定线程入口，线程函数
		LPVOID lpParameter,//传递给线程的参数指针，万能指针，多个参数时可以通过结构体指针解决
		DWORD dwCreationFlags,//指明创建之后的线程的状态，如果立即执行设置为0，如果是等待设置为CREATE_SUSPENDED，需要执行时在通过ResumeThread()启动
		LPDWORD lpThreadId//返回新穿件的线程的线程ID
		);
	返回值：创建的线程句柄
	线程函数原型：
		DWORD WINAPI ThreadProc(LPVOID lpParam);//参数：传递给线程的参数的指针
等待单个线程运行结束函数：
	DWORD WaitForSingleObject(
		HANDLE hHandle,//需要等待的对象句柄
		DWORD dwMillisecond);//指定等待超时的毫秒数，为0就立即返回，为INFINITE则表示一直等待结束
	返回值：失败WAIT_FAILED，激发状态WAIT_OBJECT_0，变成激发之间超时结束WAIT_TIMEOUT
等待多个线程运行结束函数：
	DWORD WaitForMultipleObjects(
		DWORD nCount,//等待的线程的数量，在1-MAXIMUM_WAIT_OBJECTS之间
		CONST HANDLE *lpHandles,//指向等待句柄的数组
		BOOL bWaitAll,//是否等待全部完成，为TRUE则等待全部完成
		DWORD dwMilliseconds//与单一等待一样
		);
临界区函数：
	初始化，进入，离开、删除
	参数：CRITICAL_SECTION结构体指针，改结构体用于Windows对代码进行临界区保护
	VOID InitializeCriticalSection(
		LPCRITICAL_SECTION lpCriticalSection
		);
	VOID EnterCriticalSection(
		LPCRITICAL_SECTION lpCriticalSection
		);
	VOID LeaveCriticalSection(
		LPCRITICAL_SECTION lpCriticalSection
		);
	VOID DeleteCriticalSection(
		LPCRITICAL_SECTION lpCriticalSection
		);
*/
//全局数字变量，全局临界区控制结构体
int glob_number = 0;
CRITICAL_SECTION glob_cs;
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	//用于验证临界区有效的临时变量
	int tp;
	//循环10此，给全局变量+10
	for (int i = 0; i < 10; i++)
	{
		//进入临界区
		EnterCriticalSection(&glob_cs);

		//临界区代码块
		tp = glob_number;
		tp++;
		Sleep(2);
		glob_number = tp;

		//离开临界区
		LeaveCriticalSection(&glob_cs);
	}
	return 0;
}
int main(int argc, char * argv[])
{
	//初始化临界区对象
	InitializeCriticalSection(&glob_cs);
	//初始化10个线程执行函数
	HANDLE hThread[10] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		hThread[i] = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	}
	//等待所有线程结束
	WaitForMultipleObjects(10,hThread,TRUE,INFINITE);
	//输出最终结果并关闭所有线程句柄
	printf("number:%d\n",glob_number);
	for (int i = 0; i < 10; i++)
	{
		CloseHandle(hThread[i]);
	}
	//删除临界区对象
	DeleteCriticalSection(&glob_cs);
	system("pause");
	return 0;
}