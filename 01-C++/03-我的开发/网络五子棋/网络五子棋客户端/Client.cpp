#include"stdafx.h"
#include"Client.h"
Client::Client()
{
	memset(&this->wsaData, 0, sizeof(this->wsaData));
	this->Socketaf = 0;
	this->Sockettype = 0;
	this->Socketprotocol = 0;
	memset(this->IP, 0, sizeof(char)* 512);
	this->Port = 0;
	memset(&this->serverAddr, 0, sizeof(this->serverAddr));
	memset(&this->clientSocket, 0, sizeof(this->clientSocket));
}

Client::~Client()
{
	closesocket(clientSocket);
	WSACleanup();
}
bool Client::SetWSAStartup(int lPart, int hPart)
{
	WSAStartup(MAKEWORD(lPart, hPart), &this->wsaData);//Ð­Òé°æ±¾
	if (HIBYTE(this->wsaData.wVersion) != hPart || LOBYTE(this->wsaData.wVersion) != lPart)
	{
		return false;
	}
	return true;
}
bool Client::CreateSocket(int af, int type, int protocol)
{
	this->Socketaf = af;
	this->Sockettype = type;
	this->Socketprotocol = protocol;
	clientSocket = socket(this->Socketaf, this->Sockettype, this->Socketprotocol);
	if (clientSocket == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}
bool Client::SetIpPort(char * ip, unsigned short port)
{
	int one = 0, two = 0, thr = 0, fou = 0;
	sscanf(ip, "%d.%d.%d.%d", &one, &two, &thr, &fou);
	if (one<0 || one>255 || two<0 || two>255 || thr<0 || thr>255 || fou<0 || fou>255)
		return false;
	if (port<0 || port>65535)
		return false;
	strcpy(this->IP, ip);
	this->Port = port;
	serverAddr.sin_family = this->Socketaf;
	serverAddr.sin_addr.S_un.S_addr = inet_addr(this->IP);
	serverAddr.sin_port = htons(this->Port);
	return true;
}
bool Client::ConnectServer()
{
	int rFlag = connect(this->clientSocket, (sockaddr *)&this->serverAddr, sizeof(this->serverAddr));
	if (rFlag == -1)
	{
		return false;
	}
	return true;
}
void Client::SendMsg(char * msg, int msgLen, int Flags)
{
	send(this->clientSocket, msg, msgLen, Flags);
}
bool Client::AcceptMsg(char * save, int saveMaxLen, int Flags)
{
	int rFlag = recv(this->clientSocket, save, saveMaxLen - 1, Flags);
	if (rFlag > 0)
	{
		save[rFlag] = '\0';
		return true;
	}
	return false;
}
SOCKET Client::GetSocket()
{
	return clientSocket;
}
SOCKADDR_IN Client::GetAddr()
{
	return serverAddr;
}
void Client::clear()
{
	closesocket(clientSocket);
	WSACleanup();
	memset(&this->wsaData, 0, sizeof(this->wsaData));
	this->Socketaf = 0;
	this->Sockettype = 0;
	this->Socketprotocol = 0;
	memset(this->IP, 0, sizeof(char)* 512);
	this->Port = 0;
	memset(&this->serverAddr, 0, sizeof(this->serverAddr));
	memset(&this->clientSocket, 0, sizeof(this->clientSocket));
}