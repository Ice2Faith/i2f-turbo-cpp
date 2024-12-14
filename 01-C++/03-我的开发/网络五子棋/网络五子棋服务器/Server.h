#ifndef _SERVER_H_
#define _SERVER_H_
#define USE_INLINE_SOCKET 1
#define NOT_USE_INLINE_SOCKET 0
#define INLINE_SOCKET_MODE USE_INLINE_SOCKET
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") 
#include<windows.h>
#if INLINE_SOCKET_MODE
#include<deque>
#include<iterator>
#endif //INLINE_SOCKET_MODE
class Server
{
public:
	Server();
	~Server();
	bool SetWSAStartup(int hPart = 2, int lPart = 2);
	bool CreateSocket(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	bool SetIpPort(char * ip, unsigned short port);
	bool Bind();
	bool Listen(int backlog = 10);
	bool AcceptClient(SOCKET * socket);
	bool ReciveMsg(SOCKET socket, char * save, int saveMaxLen, int Flags = NULL);
	void SendMsg(SOCKET socket, char * msg, int msgLen, int Flags = NULL);
	void clear();

#if INLINE_SOCKET_MODE
	std::deque<SOCKET>& GetSocketDeque();
	SOCKET & operator[](const int index);
	std::deque<SOCKET>::iterator At(const int index);
	std::deque<SOCKET>::iterator begin();
	std::deque<SOCKET>::iterator end();
	void Broadcast(char * msg, int msgLen, int Flags = NULL);
#endif //INLINE_SOCKET_MODE
private:
	WSADATA wsaData;

	int Socketaf;
	int Sockettype;
	int Socketprotocol;

	char IP[512];
	unsigned short Port;

	SOCKET serverSocket;
	SOCKADDR_IN serverAddr;

	SOCKADDR_IN clientAddr;

#if INLINE_SOCKET_MODE
	std::deque<SOCKET> SocketQueue;
#endif //INLINE_SOCKET_MODE
};
#endif // !_SERVER_H_
