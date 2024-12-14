#ifndef _CLIENT_H_
#define _CLIENT_H_
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") 
#include<windows.h>
class Client
{
public:
	Client();
	~Client();
	bool SetWSAStartup(int hPart = 2, int lPart = 2);
	bool CreateSocket(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	bool SetIpPort(char * ip, unsigned short port);
	bool ConnectServer();
	void SendMsg(char * msg, int msgLen, int Flags = NULL);
	bool AcceptMsg(char * save, int saveMaxLen, int Flags = NULL);
	SOCKET GetSocket();
	SOCKADDR_IN GetAddr();
	void clear();
private:
	WSADATA wsaData;

	int Socketaf;
	int Sockettype;
	int Socketprotocol;

	char IP[512];
	unsigned short Port;

	SOCKET clientSocket;
	SOCKADDR_IN serverAddr;
};

#endif // !_CLIENT_H_
