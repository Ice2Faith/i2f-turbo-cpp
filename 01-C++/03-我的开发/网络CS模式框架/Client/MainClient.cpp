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
		printf("协议申请失败\n");
		return -1;
	}
	printf("协议申请成功\n");
	if (!myclient.CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
	{
		printf("创建连接失败\n");
		return -1;
	}
	printf("创建连接成功\n");
	char ip[256] = { "127.0.0.1" };
	unsigned short port = 12100;
	if (!myclient.SetIpPort(ip, port))
	{
		printf("设置IP端口失败\n");
		return -1;
	}
	printf("设置IP端口成功\n");
	if (!myclient.ConnectServer())
	{
		printf("连接服务器失败\n");
		return -1;
	}
	printf("连接服务器成功\n");
	printf("客户端：%u\n", myclient.GetSocket());
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)AcceptInfo, (LPVOID)&myclient, NULL, NULL);
	SendInfo(myclient);
	system("pause");
	return 0;
}