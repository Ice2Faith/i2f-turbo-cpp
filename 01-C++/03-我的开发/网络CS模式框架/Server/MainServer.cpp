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
		printf("版本请求失败\n"); return -1;
	}
	printf("版本请求成功\n");
	if (!myserver.CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
	{
		printf("创建连接失败\n"); return -1;
	}
	printf("创建连接成功\n");
	char ip[80] = { "127.0.0.1" };
	unsigned short port = 12100;
	if (!myserver.SetIpPort(ip, port))
	{
		printf("设置IP端口失败\n"); return -1;
	}
	printf("设置IP端口成功\n");
	if (!myserver.Bind())
	{
		printf("绑定失败\n"); return -1;
	}
	printf("绑定成功\n");
	if (!myserver.Listen())
	{
		printf("监听失败\n"); return -1;
	}
	printf("监听成功\n");
	while (1)
	{
		SOCKET soctemp;
		if (myserver.AcceptClient(&soctemp))
		{
			printf("客户端：%u\n", soctemp);
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SocketService, (LPVOID)pclientNum, NULL, NULL);
			pclientNum++;
		}

	}
	system("pause");
	return 0;
}