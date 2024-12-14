#include<stdio.h>
#include<WinSock2.h>//Windows网络编程头文件
#pragma comment(lib,"ws2_32")
#include<Windows.h>
#include<mstcpip.h>//SIO_RCVALL 定义的头文件
#pragma comment(lib,"Advapi32.lib")
/*
嗅探技术：
	共享方式下的以太网会将数据发送给同一网段内的所以计算机网卡，
	接收到数据的网卡会将与自己MAC地址不匹配的数据包丢弃，
	因为共享以太网会将别人的数据也发给自己，而当网卡工作在混杂模式下
	就可以不丢弃所有接收到的数据，然后自己解析的方式，进行嗅探
	因此需要知道常见协议的首部，比如IP、TCP、UDP、ICMP
	分类：
		主动嗅探：
			依赖ARP欺骗或者MAC欺骗，诱导数据发送过来
		被动嗅探：
			网卡设置为混杂模式，然后接受通过网卡的所有数据
开发嗅探器就是改变网卡的工作方式为混杂模式，
并解析收到的数据包
通过ioctlsocket的控制参数SIO_RCVALL实现改变
*/

void DecodeIpPacket(char * pData);
void DecodeTcpPacket(char * pData, char * szSrcIp, char * szDstIp);
void DecodeUdpPacket(char * pData, char * szSrcIp, char * szDstIp);
void DecodeIcmpPacket(char * pData, char * szSrcIp, char * szDstIp);
int main(int argc, char * argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);

	//创建原始套接字
	SOCKET sockRaw = socket(AF_INET, SOCK_RAW, IPPROTO_IP);

	//获取本地IP
	char szHostName[256] = { 0 };
	struct sockaddr_in addrIn;
	struct hostent * pHostent;
	gethostname(szHostName, 256 - 1);
	
	pHostent = (struct hostent *)gethostbyname(szHostName);
	if (pHostent == NULL)
	{
		printf("Sys:Error %d Get Host IP Failure!!\r\n", GetLastError());
		return -1;
	}
	//填充绑定IP数据，截取IP数据报，无端口说
	addrIn.sin_family = AF_INET;
	addrIn.sin_port = htons(0);

	//检查是否命令行传入监听的IP地址
	if (argc >= 2)
	{
		addrIn.sin_addr.S_un.S_addr = inet_addr(argv[1]);
	}
	else
	{
		memcpy(&addrIn.sin_addr.S_un.S_addr, pHostent->h_addr_list[0], pHostent->h_length);
	}
	
	//绑定监听IP数据报
	printf("Sys:Binding to network interface:%s\r\n",::inet_ntoa(addrIn.sin_addr));
	if (bind(sockRaw, (SOCKADDR*)&addrIn, sizeof(addrIn)) == SOCKET_ERROR)
	{
		printf("Sys:Error %d Bind Failure!\r\n", GetLastError());
		return -1;
	}
	//设置接收控制代码，以监听所有IP数据报
	printf("Sys:Setting Socket IO Recive All Packet to Receive ALL IP Packet\r\n");
	DWORD dwValue = 1;
	if (ioctlsocket(sockRaw, SIO_RCVALL, &dwValue) != 0)
	{
		printf("Sys:Error %d Set Receive ALL IP Packet Failure!\r\n", GetLastError());
		return -1;
	}
	//接收IP数据封包
	printf("Sys:Start Receive IP Packet\r\n");
	char buffer[2048] = { 0 };
	int ret;
	while (TRUE)
	{
		ret = recv(sockRaw, buffer, 2048, 0);
		if (ret > 0)
		{
			//解析IP数据报
			DecodeIpPacket(buffer);
		}
	}
	closesocket(sockRaw);

	WSACleanup();
	return 0;
}
typedef struct _IpHeader //定义IP报文

{
	unsigned char Version_HeaderLength; //4位首部长度+4位IP版本号
	unsigned char serviceType; //8位服务类型TOS
	unsigned short totalLength; //16位总长度（字节）
	unsigned short identifer; //16位标识
	unsigned short Flag_FragmentedOffset; //3位标志位,4位Flag和12位Fragment Offset
	unsigned char timeToLive; //8位生存时间 TTL
	unsigned char protocol; //8位协议 (TCP, UDP 或其他)
	unsigned short checksum; //16位IP首部校验和
	unsigned int ipSource; //32位源IP地址
	unsigned int ipDestination; //32位目的IP地址
	//unsigned int Option_Filling;//24位可选参数和8位填充数据
}IPHeader, *PIPHeader;
typedef struct _TcpHeader//定义TCP数据报文
{
	unsigned short portSource;//16位源端口
	unsigned short portDestination;//16位目标端口
	unsigned int SEQNumber;//32位序列号
	unsigned int ACKNumber;//32位确认号
	unsigned char dataOffset;//高4位标识数据偏移，中间剩余的6位保留位
	unsigned char flags;//低6位标志位
	unsigned short slideWindowSize;//16位滑动窗口大小
	unsigned short checksum;//16位校验和
	unsigned short urgentDataOffset;//16位紧急数据偏移量
	//unsigned int Option_Filling;//24位可选参数和8位填充数据
}TCPHeader,*PTCPHeader;
typedef struct _UdpHeader
{
	unsigned short portSource;//16位源Port
	unsigned short portDestination;//16位目标Port
	unsigned short totalLength; //16位总长度（字节）
	unsigned short checksum;//16位UDP首部校验和
}UDPHeader, *PUDPHeader;
typedef struct _IcmpHeader
{
	unsigned char type;//8位类型
	unsigned char code;//8位代码标识
	unsigned short checksum;//16位校验和
	unsigned int other;//32位首部的其他部分
	/*其他部分：
		回显请求报文中或地址掩码请求与应答中分为：
			16位标识符
			16位序号
		路由器通告中分为：
			8位地址号
			8位地址大小
			16位寿命
	*/
}ICMPHeader, *PICMPHeader;
void DecodeIpPacket(char * pData)
{
	PIPHeader  pIpHeader = (PIPHeader)pData;

	struct sockaddr_in source, dest;
	char szSourceIp[32], szDestIp[32];

	//获取原地址目标地址
	source.sin_addr.S_un.S_addr = pIpHeader->ipSource;
	dest.sin_addr.S_un.S_addr = pIpHeader->ipDestination;
	strcpy(szSourceIp, inet_ntoa(source.sin_addr));
	strcpy(szDestIp, inet_ntoa(dest.sin_addr));
	//获取IP头部长度
	int headerLen = (pIpHeader->Version_HeaderLength & 0xf)*sizeof(ULONG);
	//判定IP报文类型
	switch (pIpHeader->protocol)
	{
	case IPPROTO_TCP:
		DecodeTcpPacket(pData+headerLen,szSourceIp,szDestIp);
		break;
	case IPPROTO_UDP:
		DecodeUdpPacket(pData + headerLen, szSourceIp, szDestIp);
		break;
	case IPPROTO_ICMP:
		DecodeIcmpPacket(pData + headerLen, szSourceIp, szDestIp);
		break;
	}
}
void DecodeTcpPacket(char * pData,char * szSrcIp,char * szDstIp)
{
	PTCPHeader ptcpHeader = (PTCPHeader)pData;

	unsigned short destPort = ntohs(ptcpHeader->portDestination);
	printf("BEGIN-----------TCP----------------\n");
	printf("IP:Port is %s:%d --> %s:%d\n",szSrcIp,ntohs(ptcpHeader->portSource),
		szDstIp, destPort);

	char * tcpData = pData + sizeof(TCPHeader);

	switch (destPort)
	{
	case 20:
	case 21://FTP
		printf("BEGIN-----------FTP----------------\n");

		if (strncmp(tcpData, "USER ", 5) == 0)
		{
			printf("FTP UserName:%s\n",tcpData+4);
		}
		if (strncmp(tcpData, "PASS ", 5) == 0)
		{
			printf("FTP Password:%s\n", tcpData + 4);
		}
		printf("END-------------FTP----------------\n");
			break;
	case 80:
	case 8080://HTTP
		printf("BEGIN-----------HTTP----------------\n");
		printf("Data:\n%s\n",tcpData);
		printf("END-------------HTTP----------------\n");
		break;
	case 23://TELNET
		printf("BEGIN-----------TELNET----------------\n");
		printf("Data:\n%s\n", tcpData);
		printf("END-------------TELNET----------------\n");
		break;
	case 25://SMTP
		printf("BEGIN-----------SMTP----------------\n");
		printf("Data:\n%s\n", tcpData);
		printf("END-------------SMTP----------------\n");
		break;
	case 53://DNS
		printf("BEGIN-----------DNS----------------\n");
		printf("Data:\n%s\n", tcpData);
		printf("END-------------DNS----------------\n");
		break;
	case 443://HTTPS
		printf("BEGIN-----------HTTPS----------------\n");
		printf("Data:\n%s\n", tcpData);
		printf("END-------------HTTPS----------------\n");
		break;
	}
	printf("Data:\n%s\n", tcpData);
	printf("END-------------TCP----------------\n");
}
void DecodeUdpPacket(char * pData, char * szSrcIp, char * szDstIp)
{
	PUDPHeader pudpHeader = (PUDPHeader)pData;

	unsigned short destPort = ntohs(pudpHeader->portDestination);
	printf("BEGIN-----------UDP----------------\n");
	printf("IP:Port is %s:%d --> %s:%d\n", szSrcIp, ntohs(pudpHeader->portSource),
		szDstIp, destPort);
	printf("total length:%d\n",pudpHeader->totalLength);
	char * udpData = pData + sizeof(PUDPHeader);

	switch (destPort)
	{
	case 53://DNS
		printf("BEGIN-----------DNS----------------\n");
		printf("Data:\n%s\n", udpData);
		printf("END-------------DNS----------------\n");
		break;
	case 69://TFTP
		printf("BEGIN-----------TFTP----------------\n");
		printf("Data:\n%s\n", udpData);
		printf("END-------------TPTP----------------\n");
		break;
	case 161://SNMP
		printf("BEGIN-----------SNMP----------------\n");
		printf("Data:\n%s\n", udpData);
		printf("END-------------SNMP----------------\n");
		break;
	default:
		break;
	}
	
	printf("Data:\n%s\n", udpData);
	printf("END-------------UDP----------------\n");
}
void DecodeIcmpPacket(char * pData, char * szSrcIp, char * szDstIp)
{
	PICMPHeader picmpHeader = (PICMPHeader)pData;

	printf("BEGIN-----------ICMP----------------\n");
	printf("IP is %s --> %s\n", szSrcIp, szDstIp);
	printf("type:%d code:%d other:%08x", picmpHeader->type, picmpHeader->code, picmpHeader->other);

	char * icmpData = pData + sizeof(PICMPHeader);

	printf("Data:\n%s\n", icmpData);
	printf("END-------------ICMP----------------\n");
}