/** Name: URL Downloader*/
#include<stdio.h>
#include<conio.h>

#include<Windows.h>
#include<urlmon.h>
#pragma comment(lib,"urlmon")

/*
����һ�����̺�����
	UINT WinExec(LPCSTR lpCmdLine,//�����в�����ֱ�Ӹ���ִ�г���·��Ҳ��
		UINT uCmdShow);//�������к��״̬�����õ�SW_SHOW��ʾ���У�SW_HIDE��������

URL�ļ����غ�����
	HRESULT URLDownloadToFile(LPUNKOWN pCaller,
		LPCSTR szURL,//ָ������ԴURL
		LPCSTR szFileName,//ָ�����ص����ص��ļ�λ��
		DWORD dwReserved,
		LPBINDSTATUSCALLBACK lpfnCB);
	//����������0��NULL����
*/
int main(int argc, char * argv[])
{
	if (argc >= 3)
	{
		printf("�ļ�����������...\n");
		URLDownloadToFile(NULL, argv[1], argv[2], 0, NULL);
		printf("�ļ�������ϣ���\n");
		printf("�Ƿ�����ص��ļ���1���� else����\n>/ ");
		if (getch() == '1')
			WinExec(argv[2], SW_SHOW);
	}
	else
	{
		printf("��������ȷ����\n");
		printf("������\n");
		printf("\tԶ���ļ�URL��ַ ���ر����ļ�����");
		printf("���磺\n");
		printf("\thttps://www.baidu.com/ baidu.html");
	}
	return 0;
}