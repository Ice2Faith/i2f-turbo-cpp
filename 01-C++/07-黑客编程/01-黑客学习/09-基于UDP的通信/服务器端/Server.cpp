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
	SOCKET serverSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//����ַ��Ϣ
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(1021);

	//���׽��ֵ�ַ
	bind(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	//������Ϣ
	char buffer[MAXBYTE] = { 0 };
	struct sockaddr_in clientAddr;
	int psize = sizeof(clientAddr);
	recvfrom(serverSock, buffer, MAXBYTE, 0,(SOCKADDR *) &clientAddr, &psize);
	printf("Client %s:%d Say:%s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buffer);

	//������Ϣ
	strcpy(buffer, "Hello Client!");
	sendto(serverSock, buffer, strlen(buffer) + 1, 0, (SOCKADDR *)&clientAddr, sizeof(clientAddr));

	//����
	closesocket(serverSock);

	WSACleanup();

	system("pause");
	return 0;
}