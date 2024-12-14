/*
服务器端函数流程：
WSAStartup()->socket()->bind()->listen()->accept()->connect()->send()/recv()->closesocket()->WSACleanup()
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
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;// inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(1201);

	//绑定套接字
	bind(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	//监听端口
	listen(serverSock, SOMAXCONN);

	//获取客户端信息
	struct sockaddr_in clientAddr;
	int psize = sizeof(clientAddr);

	//接受客户端
	SOCKET clientSock = accept(serverSock, (SOCKADDR *)&clientAddr, &psize);

	//输出客户端IP：Port
	printf("Client=%s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	
	//发送消息
	char buffer[MAXBYTE] = { 0 };
	strcpy(buffer, "hello client");
	send(clientSock, buffer, strlen(buffer), 0);

	//接受信息
	recv(clientSock, buffer, MAXBYTE, 0);
	printf("Client say:%s\n", buffer);

	//清理
	closesocket(clientSock);
	closesocket(serverSock);

	WSACleanup();

	system("pause");
	return 0;
}