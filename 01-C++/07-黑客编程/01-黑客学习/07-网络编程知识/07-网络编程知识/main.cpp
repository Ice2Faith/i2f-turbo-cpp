#include<Windows.h>
#include<winsock.h>
#include<WinSock2.h>
#include<stdio.h>
void WinSockInitAndRelease()
{
	//1.WinSock�ĳ�ʼ�����ͷ�
	WORD wVersionRequest = MAKEWORD(2, 2);
	WSADATA wsaData;
	//WinSock��ʼ��������int WSAStartup(WORD wVersionRequired,LPWSADATA lpWSAData);
	//��������Ҫ��ʼ��WinSock��İ汾�ţ�����2.2����ָ��WSADATA��ָ��
	//����ֵ������0��������������������
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
	// WinSock�ͷź�����int WSACleanUp();
	//�ڳ��������ֱ�ӵ����ͷż���
	WSACleanup();
}

void SocketCreateAndClose()
{
	//2.�׽��ֵĴ�����ر�
	//�׽��ִ���������SOCKET socket(int af, int type, int protocol);
	//������ָ����ַ�壨������ʹ�õ�ֻ������AF_INET��Address Family����PF_INET��Protocol Family��������ʹ�ú��ߣ���WinSock2�ж���ʵ����ֵ��һ���ģ�2������ϵͳ����ͬ����
	//ָ�����׽��������������ͣ�ͨ��ʹ��SOCK_STREAM�����׽��֣���SOCK_DGRAM�����ݱ��׽��֣���SOCK_RAW��ԭʼЭ��ӿڣ�����
	//ָ��Ӧ�ó���ʹ�õ�ͨ��Э�飨��ѡIPPROTO_TCP��IPPROTO_UDP��IPPROTO_ICMP����ֵ���ݲ�����ѡ��STREAM-TCP,DGRAM-UDP,STREAM/DGRAM-Ĭ��0��RAW-����ָ������Ϊ0��
	//����ֵ���µ��׽�����������ʧ���򷵻�INVALID_SOCKET��ʧ��ԭ��ɺ�����ѯ��WSAGetLastError()�õ������룬δ��ʼ��WinSock�ɹ�֮ǰ���ܵ��ã�

	//�׽��ֵĹرգ�int closesocket(SOCKET sock);
	//������������Ҫ�رյ��׽���������
}

void FaceToProtocolFunctionTCP()
{
	//3.����Э��ĺ�����TCP��
	//�����������У�bind,listen,accept
	//int bind(SOCKET sock,const struct sockaddr FAR * name,int namelen);//�׽����������͵�ַ�˿ڰ�
	//�������׽�����������sockaddr�ṹ��ָ�루�ṩIP:Port),sockaddr�Ĵ�С���ֽڣ���ʹ��sizeof)
	/*struct sockaddr{
	u_short sa_family;
	char sa_data[14];
	}
	�ڸýṹ��֮ǰʹ�õ���sockaddr_in
	struct sockadd_in{
	short sin_family;
	u_short sin_port; //��ʶ�˿ڣ���β��ʽ�洢����Intel x86�ж�����Сβ�洢������TCP/IP�ж��Ǵ�β�洢����Ȼ��Щ�ܹ�����������ֽ�����ͬ������Ϊ����ֲ�ԣ�����ʹ��
	//Winsock2.h���ṩ��ת������(host to network)��u_short htons(u_short hostshort); u_long htonl(u_long hsotlong);
	//��ת������(network to host)��u_short ntohs(u_short hostshort); u_long ntohl(u_long hsotlong);
	struct in_addr sin_addr;
	char sin_zero[8];
	}
	���϶���Ϊ�˼���
	��sockaddr_in�ṹ���л���һ���ṹ��in_addr����WinSock2.h�ж���
	struct in_addr{
	union{
	struct { u_char s_b1,s_b2,s_b3,s_b4;} S_un_b;
	struct {u_short s_w1,s_w2;} S_un_w;
	u_long S_addr;
	} S_un;
	}

	�����ʮ���Ƶ�IP��ַת��Ϊin_addr���ܵ�����(in_addr�������u_long S_addr)��ת��������
	unsigned long inet_addr(const char FAR * cp);

	ͬ��Ҳ������ת����������in_addr�ṹ��ת��Ϊ���ʮ���Ƶ�IP��ַ����
	char  FAR * inet_ntoa(struct in_addr in);
	*/
	//�׽��ִ����Ͱ󶨺���ʹ��ʾ��
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//���ڷ������˶��ԣ���ʹ��INADDR_ANY�꣬�÷������Լ�ѡһ��IP�Ϳͻ��˽���ͨ��
	serverAddr.sin_port = htons(1201);

	bind(sock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	//��������:int listen(SOCKET sock, int backlog);//���Ѿ��󶨵��׽��ִ��ڼ���״̬
	//�������������׽������������������������е������������ֵΪSOMAXCONN��

	//���ܺ�����SOCKET accept(SOCKET sock,struct sockaddr FAR * addr,int FAR * addrlen);//��ȡ���Ӷ��У��������׽����Ա�Ϳͻ���ͨ��
	//�������Ѿ��ڼ������׽������������������ؿͻ��˵�ַ��Ϣ�Ľṹ�壬�ṹ��Ĵ�С��ͬ��sizeof�ṹ�弴�ɡ���
	//����ֵ���½��ܵĿͻ����׽�������������Ҫ�ǵùر�����ͻ����׽���closesocket()

	//�ͻ������У�connect
	//���Ӻ�����int connect(SOCKET sock,const struct sockaddr FAR * addr,int addlen);
	//�������Ѿ������õ��׽��������������������IP��Port��Ϣ�Ľṹ�壬�ṹ��Ĵ�С��ͬ��sizeof���ɣ�

	//ͨ�÷���ͻ���ͨ�ţ�send,recv
	//���ͺ�����int  send(SOCKET sock,const char FAR * buffer,int bufferLen,int flags);
	//������Ŀ���׽��������������ڷ��������ǿͻ��ˣ����ڿͻ��˾���socket�����ģ��������������������ȣ���־��ͨ��Ϊ0��

	//���ܺ�����int recv(SOCKET sock,char FAR * buffer,int len,int flags);
	//����ͬsend

}

void UnFaceProtocolFunctionUDP()
{
	//4.������Э��ĺ�����UDP��
	//�������˲�����ҪTCP�е�listen,accept
	//�ͻ��˲�����ҪTCP�е�connect
	//ȡ����֮����sendto,recvfrom

	//���ͺ�����int sendto(SOCKET sock,const char FAR * buffer,int bufferLen,int flags,const struct sockaddr FAR * targetAddr,int addrSize);
	//�������׽��֣����ݻ��壬���峤�ȣ���־��0����������Ϣ�ĵ�ַ�ṹָ�룬�ṹ��С��ͬ��sizeof��

	//���ܺ�����int recvfrom(SOCKET sock,char FAR * buffer,int len,int flags,struct sockaddr FAR * sourceAddr,int FAR * addrSize);
	//��������sendtoһ��
}

void ByteSortInfo()
{
	//5.�ֽ������
	/*
		����CPU�ļܹ���ͬ������ֽ�����ܻ��в��죬�����Ĵ�β�������ֽ��򣩺�Сβ������CPU�ܹ���
		���磺0x01020304 ���ڴ�洢
		��β��01 02 03 04 �ڴ��λ��ַ��ŵ�λ�ֽ�
		Сβ��04 03 02 01 �ڴ��λ��ַ��Ÿ�λ�ֽ�

		�����ֽ���Windows���ݵ�CPUΪСβ��Unix����Linux�����ݵĴ󲿷�Ϊ��β
		�����ֽ��򣺴�β��ʽ

		�ֽ���ת��������
			ת������(host to network)��u_short htons(u_short hostshort); u_long htonl(u_long hsotlong);
			��ת������(network to host)��u_short ntohs(u_short hostshort); u_long ntohl(u_long hsotlong);
			���ǻ�����ֽڵ��ֽ������ת������������������Ƽ������ã��Ա���ֲ

	*/
	//�ж������ֽ���
	//ȡֵ�ȽϷ���
	DWORD num = 0x01020304;
	if (*(BYTE *)&num == 0x04)
	{
		printf("Сβ\n");
	}
	else
	{
		printf("��β\n");
	}
	//ֱ��ת���ȽϷ�
	num = 0x01020304;
	if (num == htonl(num))
	{
		printf("��β\n");
	}
	else
	{
		printf("Сβ\n");
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