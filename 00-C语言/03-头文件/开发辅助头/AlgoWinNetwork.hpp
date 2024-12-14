#ifndef _ALGO_WIN_NETWORK_HPP_
#define _ALGO_WIN_NETWORK_HPP_
#include<WinSock2.h>
#pragma comment(lib,"ws2_32")
#include<Windows.h>//注意，在使用WinSock时，包含头文件，Windows.h必须在WinSock.h/WinSock2.h之后，否则会有很多错误
class AlgoWinNetWork
{
public:
	static int StartUp( int majorVersion = 2,  int secondVersion = 2)
	{
		WSADATA wsaData;
		return WSAStartup(MAKEWORD(majorVersion, secondVersion), &wsaData);
	}
	static int CleanUp()
	{
		return WSACleanup();
	}
	static SOCKET CreateSocket(int af, int type, int protocol)
	{
		return socket(af, type, protocol);
	}
	static int CloseSocket(SOCKET sock)
	{
		return closesocket(sock);
	}
	//TCP版块
	static SOCKET CreateTcpSocket()
	{
		return socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	}
	static SOCKET DirectCreateTcpServerSocketToAccept(const char * bindAddress, short bindPort)
	{
		SOCKET serverSock = CreateTcpSocket();
		int ret = Bind(serverSock, bindAddress, bindPort);
		ret = Listen(serverSock);
		return serverSock;
	}
	static SOCKET DirectCreateTcpClientToSend(const char * targetServerAddress, short targetServerPort)
	{
		SOCKET clientSock = CreateTcpSocket();
		int ret = Connect(clientSock, targetServerAddress, targetServerPort);
		return clientSock;
	}
	static int Bind(SOCKET serverSock, const char * bindAddress, short bindPort)
	{
		struct sockaddr_in serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.S_un.S_addr = inet_addr(bindAddress);
		serverAddr.sin_port = htons(bindPort);
		return bind(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	}
	static int Bind(SOCKET serverSock, short bindPort)
	{
		struct sockaddr_in serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
		serverAddr.sin_port = htons(bindPort);
		return bind(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	}
	static int Listen(SOCKET serverSock, int maxAcceptClientCount)
	{
		return listen(serverSock, maxAcceptClientCount);
	}
	static int Listen(SOCKET serverSock)
	{
		return listen(serverSock, SOMAXCONN);
	}
	static SOCKET Accept(SOCKET serverSock,  char * saveClientAddr=NULL,  short * saveClientPort=NULL)
	{
		struct sockaddr_in clientAddr;
		int size = sizeof(clientAddr);
		SOCKET clientSock = accept(serverSock, (SOCKADDR *)&clientAddr, &size);
		if (saveClientAddr != NULL)
			strcpy(saveClientAddr, inet_ntoa(clientAddr.sin_addr));
		if (saveClientPort != NULL)
			*saveClientPort = ntohs(clientAddr.sin_port);
		return clientSock;
	}
	static int Send(SOCKET targetClientSock, const char * buf, int bufSize,  int flag = 0)
	{
		return send(targetClientSock, buf, bufSize, flag);
	}
	static int Recv(SOCKET targetClientSock, char * saveBuf, int saveBufMaxSize,  int flag = 0)
	{
		return recv(targetClientSock, saveBuf, saveBufMaxSize, flag);
	}
	static int Connect(SOCKET clientSock, const char * targetServerAddress, short targetServerPort)
	{
		struct sockaddr_in serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.S_un.S_addr = inet_addr(targetServerAddress);
		serverAddr.sin_port = htons(targetServerPort);
		return connect(clientSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	}
	//UDP版块
	static SOCKET CreateUdpSocket()
	{
		return socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	}
	static SOCKET DirectCreateUdpServerToRecv(const char * address, short port)
	{
		SOCKET serverSock = CreateUdpSocket();
		int ret = Bind(serverSock, address, port);
		return serverSock;
	}
	static SOCKET DirectCreateUdpClientToSend()
	{
		return CreateUdpSocket();
	}
	static int RecvFrom(SOCKET bindSock, char * saveBuf, int saveBufMaxSize,  int flag = 0,  char * saveFromAddress = NULL,  short * saveFromPort = NULL)
	{
		struct sockaddr_in fromAddr;
		int size = sizeof(fromAddr);
		int ret = recvfrom(bindSock, saveBuf, saveBufMaxSize, flag, (SOCKADDR *)&fromAddr, &size);
		if (saveFromAddress != NULL)
			strcpy(saveFromAddress,inet_ntoa(fromAddr.sin_addr));
		if (saveFromPort != NULL)
			*saveFromPort =ntohs(fromAddr.sin_port);
		return ret;
	}
	static int SendTo(SOCKET bindSock, const char * buf, int bufSize, const char * targetAddress, short targetPort,  int flag=0)
	{
		struct sockaddr_in targetAddr;
		targetAddr.sin_family = AF_INET;
		targetAddr.sin_addr.S_un.S_addr - inet_addr(targetAddress);
		targetAddr.sin_port = htons(targetPort);
		return sendto(bindSock, buf, bufSize, flag, (SOCKADDR *)&targetAddr, sizeof(targetAddr));
	}
	//异步版块
	//设置为异步Socket通信方式
	/*
	使用自定义消息接收，
	
	MFC 中参考回调：LRESULT CMyDlg::OnAsynSock(WPARAM wParam, LPARAM lParam)

	回调函数中：
	需要检查参数正确性：
	if (WSAGETSELECTERROR(lParam))
	{
		return 0;
	}
	然后处理对应的消息：
	switch (WSAGETSELECTEVENT(lParam))
	{
		case FD_ACCEPT:
			struct sockaddr_in clientAddr;
			int psize = sizeof(clientAddr);
			clientSock = accept(serverSock, (SOCKADDR *)&clientAddr, &psize);
			//新接受到的客户端也要设置异步，否则你的异步有何意义
			WSAAsyncSelect(clientSock, this->GetSafeHwnd(), UM_USER_SOCK, FD_READ | FD_CLOSE);
		break;
		case FD_READ:
			char buffer[2048] = { 0 };
			recv(clientSock, buffer, 2048, 0);
		break;
		...
	}
	由上面的实例可以看出，回调函数的参数只是用来检查参数正确性和类型的
	和SOCKET的数据是无关的，该怎么使用还是怎么使用
	*/
	static int SetAsynSockNotify(SOCKET sock, HWND procHwnd, unsigned int notifyMessage, long listenEvent)
	{
		return WSAAsyncSelect(sock, procHwnd, notifyMessage, listenEvent);
	}
	static int SetAsynSockUsualTcpServerNotify(SOCKET sock, HWND procHwnd, unsigned int notifyMessage)
	{
		return SetAsynSockNotify(sock, procHwnd, notifyMessage, FD_READ | FD_ACCEPT | FD_CLOSE);
	}
	static int SetAsynSockUsualTcpClientNotify(SOCKET sock, HWND procHwnd, unsigned int notifyMessage)
	{
		return SetAsynSockNotify(sock, procHwnd, notifyMessage, FD_READ | FD_CONNECT | FD_CLOSE);
	}
	//UDP是无连接的通信，因此异步的时候，是没有差异的，通常都只是使用FD_READ
	static int SetAsynSockUsualUdpNotify(SOCKET sock, HWND procHwnd, unsigned int notifyMessage)
	{
		return SetAsynSockNotify(sock, procHwnd, notifyMessage, FD_READ);
	}
	static int SetAsynSockAllNotify(SOCKET sock, HWND procHwnd, unsigned int notifyMessage)
	{
		return SetAsynSockNotify(sock, procHwnd, notifyMessage, FD_ALL_EVENTS);
	}
	//异步通信版块
	static SOCKET DirectCreateAsynTcpServerSocketToAccept(const char * bindAddress, short bindPort,HWND procHwnd,unsigned int notifyMessage)
	{
		SOCKET serverSock = CreateTcpSocket();
		int ret=SetAsynSockUsualTcpServerNotify(serverSock, procHwnd, notifyMessage);
		ret = Bind(serverSock, bindAddress, bindPort);
		ret = Listen(serverSock);
		return serverSock;
	}
	static SOCKET DirectCreateAsynUdpServerToRecv(const char * address, short port, HWND procHwnd, unsigned int notifyMessage)
	{
		SOCKET serverSock = CreateUdpSocket();
		int ret = SetAsynSockUsualUdpNotify(serverSock, procHwnd, notifyMessage);
		ret = Bind(serverSock, address, port);
		return serverSock;
	}
	static SOCKET DirectCreateAsynTcpClientToSend(const char * targetServerAddress, short targetServerPort, HWND procHwnd, unsigned int notifyMessage)
	{
		SOCKET clientSock = CreateTcpSocket();
		int ret = SetAsynSockUsualTcpClientNotify(clientSock, procHwnd, notifyMessage);
		ret = Connect(clientSock, targetServerAddress, targetServerPort);
		return clientSock;
	}
	static SOCKET DirectCreateAsynUdpClientToSend(HWND procHwnd, unsigned int notifyMessage)
	{
		SOCKET sock= CreateUdpSocket();
		int ret = SetAsynSockUsualUdpNotify(sock, procHwnd, notifyMessage);
		return sock;
	}
};

#endif //_ALGO_WIN_NETWORK_HPP_