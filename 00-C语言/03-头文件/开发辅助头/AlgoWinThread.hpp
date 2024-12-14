#ifndef _ALGO_WIN_THREAD_HPP_
#define _ALGO_WIN_THREAD_HPP_
#include<Windows.h>

class AlgoWinThread
{
public:
	static DWORD pauseThread(HANDLE hThread)
	{
		return SuspendThread(hThread);
	}
	static HANDLE openThread(DWORD threadId, DWORD needAccessPermission, BOOL isSupportInherit)
	{
		return OpenThread(needAccessPermission, isSupportInherit, threadId);
	}
	static DWORD continueThread(HANDLE hThread)
	{
		return ResumeThread(hThread);
	}

	//线程函数定义：DWORD WINAPI ThreadProc(LPVOID param);
	static HANDLE createThread(LPTHREAD_START_ROUTINE threadFunc, LPVOID threadFuncParam = NULL, DWORD createFlag = 0, LPDWORD saveThreadId = NULL, DWORD initStackSize = 0, LPSECURITY_ATTRIBUTES lpSecAttr = NULL)
	{
		return CreateThread(lpSecAttr, initStackSize, threadFunc, threadFuncParam, createFlag, saveThreadId);
	}
	static HANDLE createThreadWaitContinue(LPTHREAD_START_ROUTINE threadFunc, LPVOID threadFuncParam = NULL)
	{
		return CreateThread(NULL, 0, threadFunc, threadFuncParam, CREATE_SUSPENDED, NULL);
	}
	//等待线程执行完毕，在超时时间内，默认值将会一直等待直到结束，也就相当于没有超时时间
	static DWORD waitThreadEnd(HANDLE hThread, DWORD dwWaitMillSecondTimeout = INFINITE)
	{
		return WaitForSingleObject(hThread, dwWaitMillSecondTimeout);
	}
	static DWORD waitMultiThreadEnd(DWORD waitCount, const HANDLE * lpThreadHandles, BOOL waitAllEnd, DWORD dwWaitMillSecondTimeout)
	{
		return WaitForMultipleObjects(waitCount, lpThreadHandles, waitAllEnd, dwWaitMillSecondTimeout);
	}
	static bool isWaitFailure(DWORD waitReturn)
	{
		return waitReturn == WAIT_FAILED;
	}
	static bool isWaitRuning(DWORD waitReturn)
	{
		return waitReturn == WAIT_OBJECT_0;
	}
	static bool isWaitTimeout(DWORD waitReturn)
	{
		return waitReturn == WAIT_TIMEOUT;
	}


};

#endif // _ALGO_WIN_THREAD_HPP_