/** Name: ʹ��ԭʼ�׽��ֹ���Ping����*/
#include<WinSock2.h>
#include<Windows.h>
#pragma comment(lib,"ws2_32")
#include<stdio.h>
/*
	��SOCK_RAWʱ������ȡֵ��
		IPPROTO_IP:
		IPPROTO_ICMP:
		IPPROTO_TCP:
		IPPROTO_UDP:
		IPPROTO_RAW:
		ʹ��ǰ4��ʱ���Զ�����IPͷ��������IPͷ���е��ϲ�Э���ֶΣ������IP_HDRINCLѡ��򲻻��Զ����IPͷ����������������Ҳ�����Զ�ȥ��IPͷ������Ҫ�������д���
		���ֱ��ʹ��IPPROTO_RAW��ϵͳ��ֱ�ӽ����ݰ���������㴫�䣬��Ҫ�Լ����IP�ײ�

	Ping���
		Ping�����һ��ICMP���Ա��ĸ�Ŀ�����������ȴ�����ICMO����Ӧ��
		һ����˵���������Pingͨ���Ͳ��ܺ���ͨ�ţ��������Ŀ�����������˻���������ô�ǿ���ͨ�ŵ�

		ICMP���ķ�װ��IP���ݱ��У�IP���ݱ�=IP�ײ�+ICMP����
		ICMP���ĸ�ʽ=8λ����+8λ����+16λУ���+ICMP���ݣ�����������ʹ��������

		Ping�����õ������������룺0��8��type=0&&code=0==>����Ӧ��type=8&&code=0==>�������

	ץ�����ߣ�Э��������ߣ���WireShark
*/
//ICMP����ͷ��
typedef struct _icmp_head
{
	unsigned char i_type;//��Ϣ����
	unsigned char i_code;//����
	unsigned short i_checkSum;//�����
	unsigned short i_id;//Ψһ��ʶ�������ID��һ������Ϊ����ID
	unsigned short i_sequence;//���к�
	unsigned long i_timeStamp;//ʱ���
}Icmp_Header,* PIcmp_Header;
#define ICMP_HEADER_SIZE sizeof(Icmp_Header)//ICMP���ĳ���
#define ICMP_ECHO_REQUEST 0x08//ICMP����������ʹ���
#define ICMP_ECHO_REPLY 0x00//ICMP�ظ��������ʹ���
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
	//��ʼ��WinSock��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	//����ԭʼ�׽���
	SOCKET rawSock = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	//���ý��ܳ�ʱ
	int timeout = 1000;
	setsockopt(rawSock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
	//����Ŀ���ַ
	struct sockaddr_in targetAddr;
	targetAddr.sin_family = AF_INET;
	targetAddr.sin_addr.S_un.S_addr = inet_addr(targetIp);
	targetAddr.sin_port = htons(0);
	//����ICMP��
	char buffer[ICMP_HEADER_SIZE + 32] = { 0 };
	PIcmp_Header picmp = (PIcmp_Header)buffer;
	picmp->i_type = ICMP_ECHO_REQUEST;
	picmp->i_code = 0;
	picmp->i_id = (USHORT)::GetCurrentProcessId();
	picmp->i_sequence = 0;
	picmp->i_timeStamp = 0;
	picmp->i_checkSum = 0;

	//����32�ֽ�����������Ϊ������
	memcpy((void *)(buffer + ICMP_HEADER_SIZE), "01234567890123456789012345678901", 32);

	//����У���
	picmp->i_checkSum = icmp_check_sum_func((PIcmp_Header)buffer, sizeof(buffer));
	//�������ݱ���
	sendto(rawSock, buffer, sizeof(buffer), 0, (SOCKADDR *)&targetAddr, sizeof(targetAddr));

	//����Ŀ���ַ
	struct sockaddr_in fromAddr;
	int psize = sizeof(fromAddr);
	//�������ݱ���
	char recvBuffer[1024] = { 0 };
	recvfrom(rawSock, recvBuffer, 1024, 0, (SOCKADDR *)&fromAddr, &psize);

	//�жϱ���
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
	printf("��������ҪPing��IP��ַ��\n>/ ");
	char ip[40] = { 0 };
	scanf("%s",ip);
	Ping(ip);
	system("pause");
	return 0;
}