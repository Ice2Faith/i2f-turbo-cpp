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
	SOCKET clientSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//����ַ��Ϣ
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(1021);


	//������Ϣ
	char buffer[MAXBYTE] = { 0 };
	strcpy(buffer, "Hello Server!");
	sendto(clientSock, buffer, strlen(buffer) + 1, 0, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	//������Ϣ
	int psize = sizeof(serverAddr);
	recvfrom(clientSock, buffer, MAXBYTE, 0, (SOCKADDR *)&serverAddr, &psize);
	printf("Client %s:%d Say:%s\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port), buffer);

	

	//����
	closesocket(clientSock);

	WSACleanup();

	system("pause");
	return 0;
}