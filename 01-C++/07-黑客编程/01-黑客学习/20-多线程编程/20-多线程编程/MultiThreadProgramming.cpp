/** Name: ���̱߳��*/
#include<stdio.h>
#include<Windows.h>
/*
�����̺߳�����
	HANDLE CreateThread(
		LPSECURITY_ATTRIBUTES lpThreadAttributes,//�����̵߳İ�ȫ���ԣ�һ��ȡNULL
		SIZE_T dwStackSize,//ָ���߳�ʹ�õ�ȱʡ��ջ��С��һ��ȡNULL���ֺ����߳�һ��
		LPTHREAD_START_ROUTINE lpStartAddress,//ָ���߳���ڣ��̺߳���
		LPVOID lpParameter,//���ݸ��̵߳Ĳ���ָ�룬����ָ�룬�������ʱ����ͨ���ṹ��ָ����
		DWORD dwCreationFlags,//ָ������֮����̵߳�״̬���������ִ������Ϊ0������ǵȴ�����ΪCREATE_SUSPENDED����Ҫִ��ʱ��ͨ��ResumeThread()����
		LPDWORD lpThreadId//�����´������̵߳��߳�ID
		);
	����ֵ���������߳̾��
	�̺߳���ԭ�ͣ�
		DWORD WINAPI ThreadProc(LPVOID lpParam);//���������ݸ��̵߳Ĳ�����ָ��
�ȴ������߳����н���������
	DWORD WaitForSingleObject(
		HANDLE hHandle,//��Ҫ�ȴ��Ķ�����
		DWORD dwMillisecond);//ָ���ȴ���ʱ�ĺ�������Ϊ0���������أ�ΪINFINITE���ʾһֱ�ȴ�����
	����ֵ��ʧ��WAIT_FAILED������״̬WAIT_OBJECT_0����ɼ���֮�䳬ʱ����WAIT_TIMEOUT
�ȴ�����߳����н���������
	DWORD WaitForMultipleObjects(
		DWORD nCount,//�ȴ����̵߳���������1-MAXIMUM_WAIT_OBJECTS֮��
		CONST HANDLE *lpHandles,//ָ��ȴ����������
		BOOL bWaitAll,//�Ƿ�ȴ�ȫ����ɣ�ΪTRUE��ȴ�ȫ�����
		DWORD dwMilliseconds//�뵥һ�ȴ�һ��
		);
�ٽ���������
	��ʼ�������룬�뿪��ɾ��
	������CRITICAL_SECTION�ṹ��ָ�룬�Ľṹ������Windows�Դ�������ٽ�������
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
//ȫ�����ֱ�����ȫ���ٽ������ƽṹ��
int glob_number = 0;
CRITICAL_SECTION glob_cs;
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	//������֤�ٽ�����Ч����ʱ����
	int tp;
	//ѭ��10�ˣ���ȫ�ֱ���+10
	for (int i = 0; i < 10; i++)
	{
		//�����ٽ���
		EnterCriticalSection(&glob_cs);

		//�ٽ��������
		tp = glob_number;
		tp++;
		Sleep(2);
		glob_number = tp;

		//�뿪�ٽ���
		LeaveCriticalSection(&glob_cs);
	}
	return 0;
}
int main(int argc, char * argv[])
{
	//��ʼ���ٽ�������
	InitializeCriticalSection(&glob_cs);
	//��ʼ��10���߳�ִ�к���
	HANDLE hThread[10] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		hThread[i] = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	}
	//�ȴ������߳̽���
	WaitForMultipleObjects(10,hThread,TRUE,INFINITE);
	//������ս�����ر������߳̾��
	printf("number:%d\n",glob_number);
	for (int i = 0; i < 10; i++)
	{
		CloseHandle(hThread[i]);
	}
	//ɾ���ٽ�������
	DeleteCriticalSection(&glob_cs);
	system("pause");
	return 0;
}