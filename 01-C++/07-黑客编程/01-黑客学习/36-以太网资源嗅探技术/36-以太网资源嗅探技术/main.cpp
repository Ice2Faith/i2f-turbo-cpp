#include<stdio.h>
#include<WinSock2.h>//Windows������ͷ�ļ�
#pragma comment(lib,"ws2_32")
#include<Windows.h>
#include<mstcpip.h>//SIO_RCVALL �����ͷ�ļ�
#pragma comment(lib,"Advapi32.lib")
/*
��̽������
	����ʽ�µ���̫���Ὣ���ݷ��͸�ͬһ�����ڵ����Լ����������
	���յ����ݵ������Ὣ���Լ�MAC��ַ��ƥ������ݰ�������
	��Ϊ������̫���Ὣ���˵�����Ҳ�����Լ����������������ڻ���ģʽ��
	�Ϳ��Բ��������н��յ������ݣ�Ȼ���Լ������ķ�ʽ��������̽
	�����Ҫ֪������Э����ײ�������IP��TCP��UDP��ICMP
	���ࣺ
		������̽��
			����ARP��ƭ����MAC��ƭ���յ����ݷ��͹���
		������̽��
			��������Ϊ����ģʽ��Ȼ�����ͨ����������������
������̽�����Ǹı������Ĺ�����ʽΪ����ģʽ��
�������յ������ݰ�
ͨ��ioctlsocket�Ŀ��Ʋ���SIO_RCVALLʵ�ָı�
*/

void DecodeIpPacket(char * pData);
void DecodeTcpPacket(char * pData, char * szSrcIp, char * szDstIp);
void DecodeUdpPacket(char * pData, char * szSrcIp, char * szDstIp);
void DecodeIcmpPacket(char * pData, char * szSrcIp, char * szDstIp);
int main(int argc, char * argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);

	//����ԭʼ�׽���
	SOCKET sockRaw = socket(AF_INET, SOCK_RAW, IPPROTO_IP);

	//��ȡ����IP
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
	//����IP���ݣ���ȡIP���ݱ����޶˿�˵
	addrIn.sin_family = AF_INET;
	addrIn.sin_port = htons(0);

	//����Ƿ������д��������IP��ַ
	if (argc >= 2)
	{
		addrIn.sin_addr.S_un.S_addr = inet_addr(argv[1]);
	}
	else
	{
		memcpy(&addrIn.sin_addr.S_un.S_addr, pHostent->h_addr_list[0], pHostent->h_length);
	}
	
	//�󶨼���IP���ݱ�
	printf("Sys:Binding to network interface:%s\r\n",::inet_ntoa(addrIn.sin_addr));
	if (bind(sockRaw, (SOCKADDR*)&addrIn, sizeof(addrIn)) == SOCKET_ERROR)
	{
		printf("Sys:Error %d Bind Failure!\r\n", GetLastError());
		return -1;
	}
	//���ý��տ��ƴ��룬�Լ�������IP���ݱ�
	printf("Sys:Setting Socket IO Recive All Packet to Receive ALL IP Packet\r\n");
	DWORD dwValue = 1;
	if (ioctlsocket(sockRaw, SIO_RCVALL, &dwValue) != 0)
	{
		printf("Sys:Error %d Set Receive ALL IP Packet Failure!\r\n", GetLastError());
		return -1;
	}
	//����IP���ݷ��
	printf("Sys:Start Receive IP Packet\r\n");
	char buffer[2048] = { 0 };
	int ret;
	while (TRUE)
	{
		ret = recv(sockRaw, buffer, 2048, 0);
		if (ret > 0)
		{
			//����IP���ݱ�
			DecodeIpPacket(buffer);
		}
	}
	closesocket(sockRaw);

	WSACleanup();
	return 0;
}
typedef struct _IpHeader //����IP����

{
	unsigned char Version_HeaderLength; //4λ�ײ�����+4λIP�汾��
	unsigned char serviceType; //8λ��������TOS
	unsigned short totalLength; //16λ�ܳ��ȣ��ֽڣ�
	unsigned short identifer; //16λ��ʶ
	unsigned short Flag_FragmentedOffset; //3λ��־λ,4λFlag��12λFragment Offset
	unsigned char timeToLive; //8λ����ʱ�� TTL
	unsigned char protocol; //8λЭ�� (TCP, UDP ������)
	unsigned short checksum; //16λIP�ײ�У���
	unsigned int ipSource; //32λԴIP��ַ
	unsigned int ipDestination; //32λĿ��IP��ַ
	//unsigned int Option_Filling;//24λ��ѡ������8λ�������
}IPHeader, *PIPHeader;
typedef struct _TcpHeader//����TCP���ݱ���
{
	unsigned short portSource;//16λԴ�˿�
	unsigned short portDestination;//16λĿ��˿�
	unsigned int SEQNumber;//32λ���к�
	unsigned int ACKNumber;//32λȷ�Ϻ�
	unsigned char dataOffset;//��4λ��ʶ����ƫ�ƣ��м�ʣ���6λ����λ
	unsigned char flags;//��6λ��־λ
	unsigned short slideWindowSize;//16λ�������ڴ�С
	unsigned short checksum;//16λУ���
	unsigned short urgentDataOffset;//16λ��������ƫ����
	//unsigned int Option_Filling;//24λ��ѡ������8λ�������
}TCPHeader,*PTCPHeader;
typedef struct _UdpHeader
{
	unsigned short portSource;//16λԴPort
	unsigned short portDestination;//16λĿ��Port
	unsigned short totalLength; //16λ�ܳ��ȣ��ֽڣ�
	unsigned short checksum;//16λUDP�ײ�У���
}UDPHeader, *PUDPHeader;
typedef struct _IcmpHeader
{
	unsigned char type;//8λ����
	unsigned char code;//8λ�����ʶ
	unsigned short checksum;//16λУ���
	unsigned int other;//32λ�ײ�����������
	/*�������֣�
		�����������л��ַ����������Ӧ���з�Ϊ��
			16λ��ʶ��
			16λ���
		·����ͨ���з�Ϊ��
			8λ��ַ��
			8λ��ַ��С
			16λ����
	*/
}ICMPHeader, *PICMPHeader;
void DecodeIpPacket(char * pData)
{
	PIPHeader  pIpHeader = (PIPHeader)pData;

	struct sockaddr_in source, dest;
	char szSourceIp[32], szDestIp[32];

	//��ȡԭ��ַĿ���ַ
	source.sin_addr.S_un.S_addr = pIpHeader->ipSource;
	dest.sin_addr.S_un.S_addr = pIpHeader->ipDestination;
	strcpy(szSourceIp, inet_ntoa(source.sin_addr));
	strcpy(szDestIp, inet_ntoa(dest.sin_addr));
	//��ȡIPͷ������
	int headerLen = (pIpHeader->Version_HeaderLength & 0xf)*sizeof(ULONG);
	//�ж�IP��������
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