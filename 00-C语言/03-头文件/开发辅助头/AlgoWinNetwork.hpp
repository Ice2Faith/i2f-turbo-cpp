#ifndef _ALGO_WIN_NETWORK_HPP_
#define _ALGO_WIN_NETWORK_HPP_
#include<WinSock2.h>
#pragma comment(lib,"ws2_32")
#include<Windows.h>//ע�⣬��ʹ��WinSockʱ������ͷ�ļ���Windows.h������WinSock.h/WinSock2.h֮�󣬷�����кܶ����
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
	//TCP���
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
	//UDP���
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
	//�첽���
	//����Ϊ�첽Socketͨ�ŷ�ʽ
	/*
	ʹ���Զ�����Ϣ���գ�
	
	MFC �вο��ص���LRESULT CMyDlg::OnAsynSock(WPARAM wParam, LPARAM lParam)

	�ص������У�
	��Ҫ��������ȷ�ԣ�
	if (WSAGETSELECTERROR(lParam))
	{
		return 0;
	}
	Ȼ�����Ӧ����Ϣ��
	switch (WSAGETSELECTEVENT(lParam))
	{
		case FD_ACCEPT:
			struct sockaddr_in clientAddr;
			int psize = sizeof(clientAddr);
			clientSock = accept(serverSock, (SOCKADDR *)&clientAddr, &psize);
			//�½��ܵ��Ŀͻ���ҲҪ�����첽����������첽�к�����
			WSAAsyncSelect(clientSock, this->GetSafeHwnd(), UM_USER_SOCK, FD_READ | FD_CLOSE);
		break;
		case FD_READ:
			char buffer[2048] = { 0 };
			recv(clientSock, buffer, 2048, 0);
		break;
		...
	}
	�������ʵ�����Կ������ص������Ĳ���ֻ��������������ȷ�Ժ����͵�
	��SOCKET���������޹صģ�����ôʹ�û�����ôʹ��
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
	//UDP�������ӵ�ͨ�ţ�����첽��ʱ����û�в���ģ�ͨ����ֻ��ʹ��FD_READ
	static int SetAsynSockUsualUdpNotify(SOCKET sock, HWND procHwnd, unsigned int notifyMessage)
	{
		return SetAsynSockNotify(sock, procHwnd, notifyMessage, FD_READ);
	}
	static int SetAsynSockAllNotify(SOCKET sock, HWND procHwnd, unsigned int notifyMessage)
	{
		return SetAsynSockNotify(sock, procHwnd, notifyMessage, FD_ALL_EVENTS);
	}
	//�첽ͨ�Ű��
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