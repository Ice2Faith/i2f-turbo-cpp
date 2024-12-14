/*
客户端函数流程：
WSAStartup()->socket()->connect()->send()/recv()->closesocket()->WSACleanup()
*/

//#include<winsock.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32")
#include<Windows.h>//注意，在使用WinSock时，包含头文件，Windows.h必须在WinSock.h/WinSock2.h之后，否则会有很多错误
#include<stdio.h>
#include<string.h>

int main(int argc, char * argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//填充sockaddr_in
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(1201);

	//链接服务器
	connect(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	//接受信息
	char buffer[MAXBYTE] = { 0 };
	recv(serverSock, buffer, MAXBYTE, 0);
	printf("Server say:%s\n", buffer);

	//发送消息
	strcpy(buffer, "hello server");
	send(serverSock, buffer, strlen(buffer), 0);

	//清理
	closesocket(serverSock);

	WSACleanup();
	system("pause");
	return 0;
}