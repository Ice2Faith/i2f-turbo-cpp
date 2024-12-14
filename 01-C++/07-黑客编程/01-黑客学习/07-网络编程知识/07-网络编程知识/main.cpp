#include<Windows.h>
#include<winsock.h>
#include<WinSock2.h>
#include<stdio.h>
void WinSockInitAndRelease()
{
	//1.WinSock的初始化和释放
	WORD wVersionRequest = MAKEWORD(2, 2);
	WSADATA wsaData;
	//WinSock初始化函数：int WSAStartup(WORD wVersionRequired,LPWSADATA lpWSAData);
	//参数：需要初始化WinSock库的版本号（常用2.2），指向WSADATA的指针
	//返回值：返回0则正常，否则其他错误
	int err = WSAStartup(wVersionRequest, &wsaData);
	if (err != 0)
	{
		return;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return;
	}
	// WinSock释放函数：int WSACleanUp();
	//在程序结束处直接调用释放即可
	WSACleanup();
}

void SocketCreateAndClose()
{
	//2.套接字的创建与关闭
	//套接字创建函数：SOCKET socket(int af, int type, int protocol);
	//参数：指定地址族（真正可使用的只有两个AF_INET（Address Family）和PF_INET（Protocol Family），尽量使用后者，在WinSock2中定义实际上值是一样的：2，其他系统中则不同），
	//指定新套接字描述符的类型（通常使用SOCK_STREAM（流套接字）、SOCK_DGRAM（数据报套接字）、SOCK_RAW（原始协议接口）），
	//指定应用程序使用的通信协议（可选IPPROTO_TCP、IPPROTO_UDP、IPPROTO_ICMP，改值根据参数二选择，STREAM-TCP,DGRAM-UDP,STREAM/DGRAM-默认0，RAW-必须指定不能为0）
	//返回值：新的套接字描述符（失败则返回INVALID_SOCKET，失败原因可函数查询：WSAGetLastError()得到错误码，未初始化WinSock成功之前不能调用）

	//套接字的关闭：int closesocket(SOCKET sock);
	//参数：就是需要关闭的套接字描述符
}

void FaceToProtocolFunctionTCP()
{
	//3.面向协议的函数（TCP）
	//服务器端特有：bind,listen,accept
	//int bind(SOCKET sock,const struct sockaddr FAR * name,int namelen);//套接字描述符和地址端口绑定
	//参数：套接字描述符，sockaddr结构体指针（提供IP:Port),sockaddr的大小（字节，可使用sizeof)
	/*struct sockaddr{
	u_short sa_family;
	char sa_data[14];
	}
	在该结构体之前使用的是sockaddr_in
	struct sockadd_in{
	short sin_family;
	u_short sin_port; //标识端口，大尾方式存储，在Intel x86中都适用小尾存储，而在TCP/IP中都是大尾存储，虽然有些架构网络和主机字节序相同，但是为了移植性，还是使用
	//Winsock2.h中提供了转换函数(host to network)：u_short htons(u_short hostshort); u_long htonl(u_long hsotlong);
	//逆转换函数(network to host)：u_short ntohs(u_short hostshort); u_long ntohl(u_long hsotlong);
	struct in_addr sin_addr;
	char sin_zero[8];
	}
	以上都是为了兼容
	在sockaddr_in结构体中还有一个结构体in_addr，在WinSock2.h中定义
	struct in_addr{
	union{
	struct { u_char s_b1,s_b2,s_b3,s_b4;} S_un_b;
	struct {u_short s_w1,s_w2;} S_un_w;
	u_long S_addr;
	} S_un;
	}

	将点分十进制的IP地址转换为in_addr接受的类型(in_addr共用体的u_long S_addr)，转换函数：
	unsigned long inet_addr(const char FAR * cp);

	同样也有逆向转换函数，将in_addr结构体转换为点分十进制的IP地址串：
	char  FAR * inet_ntoa(struct in_addr in);
	*/
	//套接字创建和绑定函数使用示例
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//对于服务器端而言，可使用INADDR_ANY宏，让服务器自己选一个IP和客户端进行通信
	serverAddr.sin_port = htons(1201);

	bind(sock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	//监听函数:int listen(SOCKET sock, int backlog);//将已经绑定的套接字处于监听状态
	//参数：监听的套接字描述符，允许进入请求队列的数量（其最大值为SOMAXCONN）

	//接受函数：SOCKET accept(SOCKET sock,struct sockaddr FAR * addr,int FAR * addrlen);//获取连接队列，创建新套接字以便和客户端通信
	//参数：已经在监听的套接字描述符，用来返回客户端地址信息的结构体，结构体的大小（同样sizeof结构体即可。）
	//返回值：新接受的客户端套接字描述符，需要记得关闭这个客户端套接字closesocket()

	//客户端特有：connect
	//连接函数：int connect(SOCKET sock,const struct sockaddr FAR * addr,int addlen);
	//参数：已经创建好的套接字描述符，保存服务器IP：Port信息的结构体，结构体的大小（同样sizeof即可）

	//通用服务客户端通信：send,recv
	//发送函数：int  send(SOCKET sock,const char FAR * buffer,int bufferLen,int flags);
	//参数：目标套接字描述符（对于服务器就是客户端，对于客户端就是socket创建的），缓冲区，缓冲区长度，标志（通常为0）

	//接受函数：int recv(SOCKET sock,char FAR * buffer,int len,int flags);
	//参数同send

}

void UnFaceProtocolFunctionUDP()
{
	//4.非面向协议的函数（UDP）
	//服务器端不在需要TCP中的listen,accept
	//客户端不再需要TCP中的connect
	//取而代之的是sendto,recvfrom

	//发送函数：int sendto(SOCKET sock,const char FAR * buffer,int bufferLen,int flags,const struct sockaddr FAR * targetAddr,int addrSize);
	//参数：套接字，数据缓冲，缓冲长度，标志（0），接受消息的地址结构指针，结构大小（同样sizeof）

	//接受函数：int recvfrom(SOCKET sock,char FAR * buffer,int len,int flags,struct sockaddr FAR * sourceAddr,int FAR * addrSize);
	//参数：和sendto一样
}

void ByteSortInfo()
{
	//5.字节序基础
	/*
		由于CPU的架构不同，因此字节序可能会有差异，常见的大尾（网络字节序）和小尾（部分CPU架构）
		比如：0x01020304 的内存存储
		大尾：01 02 03 04 内存高位地址存放低位字节
		小尾：04 03 02 01 内存低位地址存放高位字节

		主机字节序：Windows兼容的CPU为小尾，Unix（和Linux）兼容的大部分为大尾
		网络字节序：大尾方式

		字节序转换函数：
			转换函数(host to network)：u_short htons(u_short hostshort); u_long htonl(u_long hsotlong);
			逆转换函数(network to host)：u_short ntohs(u_short hostshort); u_long ntohl(u_long hsotlong);
			他们会根据字节的字节序进行转换，因此在网络编程中推荐都适用，以便移植

	*/
	//判断主机字节序：
	//取值比较法：
	DWORD num = 0x01020304;
	if (*(BYTE *)&num == 0x04)
	{
		printf("小尾\n");
	}
	else
	{
		printf("大尾\n");
	}
	//直接转换比较法
	num = 0x01020304;
	if (num == htonl(num))
	{
		printf("大尾\n");
	}
	else
	{
		printf("小尾\n");
	}
}
void WinSockKnowledge()
{
	WinSockInitAndRelease();
	SocketCreateAndClose();
	FaceToProtocolFunctionTCP();
	UnFaceProtocolFunctionUDP();
	ByteSortInfo();
}

int main(int argc, char * argv[])
{

	return 0;
}