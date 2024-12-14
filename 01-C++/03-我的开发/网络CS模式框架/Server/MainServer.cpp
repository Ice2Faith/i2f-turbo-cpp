#include"Server.h"
Server myserver;
int pclientNum = 0;
void SocketService(int clientFlag)
{
	char temp[2048] = { 0 };
	char ret[2060] = { 0 };
	while (1)
	{
		if (myserver.ReciveMsg(*(myserver.begin() + clientFlag), temp, sizeof(temp), NULL))
		{
			printf("%u:%s\n", *(myserver.begin() + clientFlag), temp);
			sprintf(ret, "%u:%s\0", *(myserver.begin() + clientFlag), temp);
			myserver.Broadcast(ret, strlen(ret), NULL);
		}
	}
}
int main(int argc, char * argv[])
{
	if (!myserver.SetWSAStartup(2, 2))
	{
		printf("�汾����ʧ��\n"); return -1;
	}
	printf("�汾����ɹ�\n");
	if (!myserver.CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
	{
		printf("��������ʧ��\n"); return -1;
	}
	printf("�������ӳɹ�\n");
	char ip[80] = { "127.0.0.1" };
	unsigned short port = 12100;
	if (!myserver.SetIpPort(ip, port))
	{
		printf("����IP�˿�ʧ��\n"); return -1;
	}
	printf("����IP�˿ڳɹ�\n");
	if (!myserver.Bind())
	{
		printf("��ʧ��\n"); return -1;
	}
	printf("�󶨳ɹ�\n");
	if (!myserver.Listen())
	{
		printf("����ʧ��\n"); return -1;
	}
	printf("�����ɹ�\n");
	while (1)
	{
		SOCKET soctemp;
		if (myserver.AcceptClient(&soctemp))
		{
			printf("�ͻ��ˣ�%u\n", soctemp);
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SocketService, (LPVOID)pclientNum, NULL, NULL);
			pclientNum++;
		}

	}
	system("pause");
	return 0;
}