/*
�ͻ��˺������̣�
WSAStartup()->socket()->connect()->send()/recv()->closesocket()->WSACleanup()
*/

//#include<winsock.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32")
#include<Windows.h>//ע�⣬��ʹ��WinSockʱ������ͷ�ļ���Windows.h������WinSock.h/WinSock2.h֮�󣬷�����кܶ����
#include<stdio.h>
#include<string.h>

int main(int argc, char * argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���sockaddr_in
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(1201);

	//���ӷ�����
	connect(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	//������Ϣ
	char buffer[MAXBYTE] = { 0 };
	recv(serverSock, buffer, MAXBYTE, 0);
	printf("Server say:%s\n", buffer);

	//������Ϣ
	strcpy(buffer, "hello server");
	send(serverSock, buffer, strlen(buffer), 0);

	//����
	closesocket(serverSock);

	WSACleanup();
	system("pause");
	return 0;
}