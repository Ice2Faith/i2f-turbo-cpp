/*
�������˺������̣�
WSAStartup()->socket()->bind()->listen()->accept()->connect()->send()/recv()->closesocket()->WSACleanup()
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
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;// inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(1201);

	//���׽���
	bind(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	//�����˿�
	listen(serverSock, SOMAXCONN);

	//��ȡ�ͻ�����Ϣ
	struct sockaddr_in clientAddr;
	int psize = sizeof(clientAddr);

	//���ܿͻ���
	SOCKET clientSock = accept(serverSock, (SOCKADDR *)&clientAddr, &psize);

	//����ͻ���IP��Port
	printf("Client=%s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	
	//������Ϣ
	char buffer[MAXBYTE] = { 0 };
	strcpy(buffer, "hello client");
	send(clientSock, buffer, strlen(buffer), 0);

	//������Ϣ
	recv(clientSock, buffer, MAXBYTE, 0);
	printf("Client say:%s\n", buffer);

	//����
	closesocket(clientSock);
	closesocket(serverSock);

	WSACleanup();

	system("pause");
	return 0;
}