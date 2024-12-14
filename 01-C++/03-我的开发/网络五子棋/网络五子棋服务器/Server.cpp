#include"Server.h"
Server::Server()
{
	memset(&this->wsaData, 0, sizeof(this->wsaData));
	this->Socketaf = 0;
	this->Sockettype = 0;
	this->Socketprotocol = 0;
	memset(this->IP, 0, sizeof(char)* 512);
	this->Port = 0;
	memset(&this->serverSocket, 0, sizeof(this->serverSocket));
	memset(&this->serverAddr, 0, sizeof(this->serverAddr));
	memset(&this->clientAddr, 0, sizeof(this->clientAddr));
#if INLINE_SOCKET_MODE
	SocketQueue.clear();
#endif //INLINE_SOCKET_MODE
}

Server::~Server()
{
#if INLINE_SOCKET_MODE
	while (!SocketQueue.empty())
	{
		closesocket(SocketQueue.front());
		SocketQueue.pop_front();
	}
#endif //INLINE_SOCKET_MODE
	closesocket(this->serverSocket);
	WSACleanup();
}
bool Server::SetWSAStartup(int lPart, int hPart)
{
	WSAStartup(MAKEWORD(lPart, hPart), &this->wsaData);//Ð­Òé°æ±¾
	if (HIBYTE(this->wsaData.wVersion) != hPart || LOBYTE(this->wsaData.wVersion) != lPart)
	{
		return false;
	}
	return true;
}
bool Server::CreateSocket(int af, int type, int protocol)
{
	this->Socketaf = af;
	this->Sockettype = type;
	this->Socketprotocol = protocol;
	serverSocket = socket(this->Socketaf, this->Sockettype, this->Socketprotocol);
	if (serverSocket == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}
bool Server::SetIpPort(char * ip, unsigned short port)
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
bool Server::Bind()
{
	int rFlag = bind(this->serverSocket, (sockaddr *)&this->serverAddr, sizeof(this->serverAddr));
	if (rFlag == -1)
	{
		return false;
	}
	return true;
}
bool Server::Listen(int backlog)
{
	int rFlag = listen(this->serverSocket, backlog);
	if (rFlag == -1)
	{
		return false;
	}
	return true;
}
bool Server::AcceptClient(SOCKET * socket)
{
	int len = sizeof(this->clientAddr);
	*socket = accept(this->serverSocket, (sockaddr *)&this->clientAddr, &len);
	if (*socket == SOCKET_ERROR)
	{
		return false;
	}
#if INLINE_SOCKET_MODE
	SocketQueue.push_back(*socket);
#endif //INLINE_SOCKET_MODE
	return true;
}
bool Server::ReciveMsg(SOCKET socket, char * save, int saveMaxLen, int Flags)
{
	int rFlag = recv(socket, save, saveMaxLen - 1, Flags);
	if (rFlag > 0)
	{
		save[rFlag] = '\0';
		return true;
	}
	return false;
}
void Server::SendMsg(SOCKET socket, char * msg, int msgLen, int Flags)
{
	send(socket, msg, msgLen, Flags);
}
void Server::clear()
{
	memset(&this->wsaData, 0, sizeof(this->wsaData));
	this->Socketaf = 0;
	this->Sockettype = 0;
	this->Socketprotocol = 0;
	memset(this->IP, 0, sizeof(char)* 512);
	this->Port = 0;
	memset(&this->serverSocket, 0, sizeof(this->serverSocket));
	memset(&this->serverAddr, 0, sizeof(this->serverAddr));
	memset(&this->clientAddr, 0, sizeof(this->clientAddr));
#if INLINE_SOCKET_MODE
	while (!SocketQueue.empty())
	{
		closesocket(SocketQueue.front());
		SocketQueue.pop_front();
	}
	SocketQueue.clear();
#endif //INLINE_SOCKET_MODE

}
#if INLINE_SOCKET_MODE
std::deque<SOCKET>& Server::GetSocketDeque()
{
	return SocketQueue;
}
SOCKET & Server::operator[](const int index)
{
	return SocketQueue[index];
}
std::deque<SOCKET>::iterator Server::At(const int index)
{
	if (index >= SocketQueue.size() || index < 0)
		return SocketQueue.end();
	return SocketQueue.begin() + index;
}
std::deque<SOCKET>::iterator Server::begin()
{
	return SocketQueue.begin();
}
std::deque<SOCKET>::iterator Server::end()
{
	return SocketQueue.end();
}
void Server::Broadcast(char * msg, int msgLen, int Flags)
{
	for (auto i = begin(); i != end(); i++)
	{
		SendMsg(*i, msg, msgLen, Flags);
	}
}
#endif //INLINE_SOCKET_MODE