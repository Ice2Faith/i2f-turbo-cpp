/** Name: 使用原始套接字构造Ping命令*/
#include<WinSock2.h>
#include<Windows.h>
#pragma comment(lib,"ws2_32")
#include<stdio.h>
/*
	当SOCK_RAW时，常用取值：
		IPPROTO_IP:
		IPPROTO_ICMP:
		IPPROTO_TCP:
		IPPROTO_UDP:
		IPPROTO_RAW:
		使用前4种时会自动加上IP头部并设置IP头部中的上层协议字段（如果有IP_HDRINCL选项，则不会自动添加IP头部），接受数据是也不会自动去除IP头部，需要程序自行处理
		如果直接使用IPPROTO_RAW，系统就直接将数据包丢到网络层传输，需要自己添加IP首部

	Ping命令：
		Ping命令发送一份ICMP回显报文给目标主机，并等待返回ICMO回显应答。
		一般来说，如果不能Ping通，就不能和其通信，但是如果目标主机屏蔽了回显请求，那么是可以通信的

		ICMP报文封装在IP数据报中：IP数据报=IP首部+ICMP报文
		ICMP报文格式=8位类型+8位代码+16位校验和+ICMP内容（依据类型码和代码而定）

		Ping命令用到了两个类型码：0和8，type=0&&code=0==>回显应答，type=8&&code=0==>请求回显

	抓包工具（协议分析工具）：WireShark
*/
//ICMP报文头部
typedef struct _icmp_head
{
	unsigned char i_type;//消息类型
	unsigned char i_code;//代码
	unsigned short i_checkSum;//检验和
	unsigned short i_id;//唯一标识此请求的ID，一般设置为进程ID
	unsigned short i_sequence;//序列号
	unsigned long i_timeStamp;//时间戳
}Icmp_Header,* PIcmp_Header;
#define ICMP_HEADER_SIZE sizeof(Icmp_Header)//ICMP报文长度
#define ICMP_ECHO_REQUEST 0x08//ICMP请求回显类型代码
#define ICMP_ECHO_REPLY 0x00//ICMP回复回显类型代码
unsigned short icmp_check_sum_func(PIcmp_Header header, int len)
{
	long sum = 0;
	unsigned short * tpic = (unsigned short *)header;
	while (len > 1)
	{
		sum += *(tpic++);
		if (sum & 0x80000000)
		{
			sum = (sum & 0xffff) + (sum>>16);
		}
		len -= 2;
	}
	if (len)
	{
		sum += (unsigned short)(*(unsigned char *)tpic);
	}
	while (sum >> 16)
	{
		sum = (sum & 0xffff) + (sum>>16);
	}
	return (unsigned short)~sum;
}
bool Ping(char * targetIp)
{
	bool ret = true;
	//初始化WinSock库
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	//创建原始套接字
	SOCKET rawSock = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	//设置接受超时
	int timeout = 1000;
	setsockopt(rawSock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
	//设置目标地址
	struct sockaddr_in targetAddr;
	targetAddr.sin_family = AF_INET;
	targetAddr.sin_addr.S_un.S_addr = inet_addr(targetIp);
	targetAddr.sin_port = htons(0);
	//构造ICMP包
	char buffer[ICMP_HEADER_SIZE + 32] = { 0 };
	PIcmp_Header picmp = (PIcmp_Header)buffer;
	picmp->i_type = ICMP_ECHO_REQUEST;
	picmp->i_code = 0;
	picmp->i_id = (USHORT)::GetCurrentProcessId();
	picmp->i_sequence = 0;
	picmp->i_timeStamp = 0;
	picmp->i_checkSum = 0;

	//拷贝32字节随意数据作为包内容
	memcpy((void *)(buffer + ICMP_HEADER_SIZE), "01234567890123456789012345678901", 32);

	//计算校验和
	picmp->i_checkSum = icmp_check_sum_func((PIcmp_Header)buffer, sizeof(buffer));
	//发送数据报文
	sendto(rawSock, buffer, sizeof(buffer), 0, (SOCKADDR *)&targetAddr, sizeof(targetAddr));

	//接受目标地址
	struct sockaddr_in fromAddr;
	int psize = sizeof(fromAddr);
	//接受数据报文
	char recvBuffer[1024] = { 0 };
	recvfrom(rawSock, recvBuffer, 1024, 0, (SOCKADDR *)&fromAddr, &psize);

	//判断报文
	if (strcmp(inet_ntoa(fromAddr.sin_addr), targetIp) != 0)
	{
		ret = false;
	}
	else
	{
		PIcmp_Header tp = (PIcmp_Header)(recvBuffer+20);
		printf("Recv:%s\n", inet_ntoa(fromAddr.sin_addr));
	}


	WSACleanup();
	return ret;
}
int main(int argc, char * argv[])
{
	printf("请输入你要Ping的IP地址：\n>/ ");
	char ip[40] = { 0 };
	scanf("%s",ip);
	Ping(ip);
	system("pause");
	return 0;
}