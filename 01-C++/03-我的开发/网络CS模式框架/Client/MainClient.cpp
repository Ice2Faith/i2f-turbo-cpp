#include"Client.h"
void AcceptInfo(Client & client)
{
	char temp[2048] = { 0 };
	while (1)
	{
		if (client.AcceptMsg(temp, sizeof(temp), NULL))
		{
			printf("\nAccept: %s\n", temp);
		}
	}

}
void SendInfo(Client & client)
{
	char temp[2048] = { 0 };
	while (1)
	{
		printf("Send: ");
		gets(temp);
		if (strlen(temp) > 0)
		{
			client.SendMsg(temp, strlen(temp), NULL);
		}
	}
}
int main(int argc, char * argv[])
{
	Client myclient;
	if (!myclient.SetWSAStartup(2, 2))
	{
		printf("Э������ʧ��\n");
		return -1;
	}
	printf("Э������ɹ�\n");
	if (!myclient.CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
	{
		printf("��������ʧ��\n");
		return -1;
	}
	printf("�������ӳɹ�\n");
	char ip[256] = { "127.0.0.1" };
	unsigned short port = 12100;
	if (!myclient.SetIpPort(ip, port))
	{
		printf("����IP�˿�ʧ��\n");
		return -1;
	}
	printf("����IP�˿ڳɹ�\n");
	if (!myclient.ConnectServer())
	{
		printf("���ӷ�����ʧ��\n");
		return -1;
	}
	printf("���ӷ������ɹ�\n");
	printf("�ͻ��ˣ�%u\n", myclient.GetSocket());
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)AcceptInfo, (LPVOID)&myclient, NULL, NULL);
	SendInfo(myclient);
	system("pause");
	return 0;
}