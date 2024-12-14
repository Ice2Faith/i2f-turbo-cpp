#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"EveryFileLocker.hpp"

int main(int argc, char * argv[])
{
	char helpInfo[] = {"���������ģʽ Դ�ļ��� ���ļ��� ���� [-d]\n\
\t-d:ָ�������ɹ�ɾ��Դ�ļ�����ѡ����\n\
\tģʽѡ�lock/unlock\n\
\t���磺lock D:\\aaa.zip D:\\aaa.zip.flcl hello -d\n\
\t���ڼ��ܺ���ļ���������Ӻ�׺��.flcl,����������ʶ��\n\
"};
	if (argc < 5)
	{
		printf(helpInfo);
		system("pause");
		return 0;
	}
	bool modeLock = true;
	if (strcmp(argv[1], "lock") == 0)
		modeLock = true;
	else if (strcmp(argv[1], "unlock") == 0)
		modeLock = false;
	else
	{
		printf("�ؼ�ģʽ��������ȷ����鿴����\n");
		printf(helpInfo);
		system("pause");
		return 0;
	}
	char * srcFile = argv[2];
	char * drtFile = argv[3];
	char * password = argv[4];
	bool needDelSrc = false;
	if (argc >= 6)
	{
		if (strcmp(argv[5], "-d") == 0)
			needDelSrc = true;
		else
		{
			printf("��⵽��Ч�������ѱ����ԣ�%s\n",argv[5]);
		}
	}

	EveryFileLocker locker;
	BOOL_T isSuccess = BOOL_FALSE;
	if (modeLock)
		isSuccess = locker.lock(srcFile, drtFile, password);
	else
		isSuccess = locker.unlock(srcFile, drtFile, password);

	if (isSuccess)
	{
		if (needDelSrc)
		{
			remove(srcFile);
		}
		printf("�ļ� %s �ɹ���%s --> %s by password:%s\n",(modeLock==true?"����":"����"),srcFile,drtFile,password);
	}
	else
	{
		printf("�ļ� %s ʧ�ܣ�%s �����ļ��Ƿ���ڻ�����ԭ��\n", (modeLock == true ? "����" : "����"), srcFile);
	}

	return 0;
}