#include"Server.h"
#include"ODBCService.h"
#include<iostream>
#include<thread>
#include<deque>
using namespace std;
ODBCService myodbc;
deque<SOCKET> allPlayer;
Server myserver;
void SocketService(pair<SOCKET, SOCKET>* gamer);//接受两个套接字，在套接字之间进行通信转发
int BuildServer(char * ip, unsigned short port);//建立服务器服务
void AcceptClient();//接受客户端连接循环
void GetServerConfig(char * ip, unsigned short * port)
{
	FILE * fconfig = fopen("GobangServer.config","r");
	bool IsError = false;
	if (!fconfig)
	{
		sprintf(ip, "127.0.0.1\0");
		*port = 12100;
		return;
	}
	char tempip[256];
	if (1 != fscanf(fconfig, "ServerIP=%s\n", tempip))
		IsError = true;
	else
		strcpy(ip, tempip);
	int tempport=12100;
	if (1 != fscanf(fconfig, "ServerPort=%d\n", &tempport))
		IsError = true;
	else
		*port = tempport;
	fclose(fconfig);
	if (IsError)
	{
		sprintf(ip, "127.0.0.1\0");
		*port = 12100;
	}
}
int ConnectDB()
{
	myodbc.SetDsnName("GoBangDB");
	myodbc.SetLoginName("sa");
	myodbc.SetLoginKey("ltb12315");
	if (!myodbc.ConnectDB())
		return -1;
}
void ExecSelectAllUserSql()
{
	//定义数据接收单元
	char name[50] = { 0 };
	char pwd[50] = { 0 };
	myodbc.AllocHandle();
	myodbc.BindColumn(1, name, sizeof(name));
	myodbc.BindColumn(2, pwd, sizeof(pwd));

	UCHAR sql[] = "select pname,ppwd from Player;";
	myodbc.ExecDirect((UCHAR *)sql, strlen((char *)sql));
	if (myodbc.RetHaveData())
	{
		printf("%20s  %20s\n","NAME", "PWD");
		printf("%20s  %20s\n",  name, pwd);
		//获取所有数据并输出
		while (1)
		{
			myodbc.Fetch();
			if (!myodbc.RetHaveData())
				break;
			printf("%20s  %20s\n",name, pwd);
		}
	}
	myodbc.FreeHandle();
}
int UserContainPlayer(char * uname,char * upwd)
{
	//定义数据接收单元
	char name[50] = { 0 };
	char pwd[50] = { 0 };
	myodbc.AllocHandle();
	myodbc.BindColumn(1, name, sizeof(name));
	myodbc.BindColumn(2, pwd, sizeof(pwd));

	UCHAR sql[1024] = {0};
	sprintf((char *)sql, "select pname, ppwd from Player where pname=\'%s\' ; ",uname);
	myodbc.ExecDirect((UCHAR *)sql, strlen((char *)sql));
	bool contain = false;
	if (myodbc.RetHaveData())
	{
		myodbc.Fetch();
		contain = true;
	}
	myodbc.FreeHandle();
	if (contain)
	{
		if (strcmp(pwd, upwd) == 0)
		{
			return 1;
		}
		else
			return 0;
	}
	else
	{
		return -1;
	}
}
int UserRegister(char * uname,char * upwd)
{
	if (UserContainPlayer(uname, upwd) != -1)
	{
		return -1;
	}
	myodbc.AllocHandle();
	UCHAR sql[1024] = { 0 };
	sprintf((char*)sql, "insert into Player(pName,PPwd) values(\'%s\',\'%s\');\0",uname,upwd);
	myodbc.ExecDirect((UCHAR *)sql, strlen((char *)sql));
	myodbc.FreeHandle();
	return 0;
}
int main(int argc, char * argv[])
{
	/*ConnectDB();
	UserRegister("acumit","789");
	ExecSelectAllUserSql();
	UserContainPlayer("jelly","123");*/
	system("mode con cols=50");
	system("color f1");
	char ip[80] = { "127.0.0.1" };
	unsigned short port = 12100;
	GetServerConfig(ip,&port);
	if (BuildServer(ip, port) == -1)
		return -1;
	AcceptClient();
	system("pause");
	//myodbc.FreeHandle();
	return 0;
}
void AcceptClient()
{
	while (1)
	{
		SOCKET soctemp;
		if (myserver.AcceptClient(&soctemp))
		{
			printf("客户端：%u\n", soctemp);
			allPlayer.push_back(soctemp);
			if (myserver.GetSocketDeque().size() >= 2)
			{
				pair<SOCKET, SOCKET> gamer;
				gamer.first = myserver.GetSocketDeque().front();
				myserver.GetSocketDeque().pop_front();
				gamer.second = myserver.GetSocketDeque().front();
				myserver.GetSocketDeque().pop_front();
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SocketService, (LPVOID)&gamer, NULL, NULL);
			}
		}
		Sleep(10);
	}
}
int BuildServer(char * ip, unsigned short port)
{
	if (!myserver.SetWSAStartup(2, 2))
	{
		printf("版本请求失败\n"); return -1;
	}
	printf("版本请求成功\n");
	if (!myserver.CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
	{
		printf("创建连接失败\n"); return -1;
	}
	printf("创建连接成功\n");
	
	if (!myserver.SetIpPort(ip, port))
	{
		printf("设置IP端口失败\n"); return -1;
	}
	printf("设置IP端口成功\n");
	if (!myserver.Bind())
	{
		printf("绑定失败\n"); return -1;
	}
	printf("绑定成功\n");
	if (!myserver.Listen())
	{
		printf("监听失败\n"); return -1;
	}
	printf("监听成功\n");
	return 0;
}
void SocketService(pair<SOCKET, SOCKET>* gamer)
{
	pair<SOCKET, SOCKET> player;
	player.first = gamer->first;
	player.second = gamer->second;
	cout << "pair:" << player.first << " " << player.second << endl;
	myserver.SendMsg(player.first, "frist true ", strlen("frist true "), NULL);
	myserver.SendMsg(player.second, "frist false ", strlen("frist false "), NULL);
	char temp[2048] = { 0 };
	char tp2[2048] = { 0 };
	while (1)
	{
		char flag[80] = { 0 };
		if (myserver.ReciveMsg(player.first, temp, sizeof(temp), NULL))
		{
			printf("%u:%s\n", player.first, temp);
			sscanf(temp,"%s ",flag);
			if (strcmp(flag,"login")==0)
			{
				myserver.SendMsg(player.first, "login success ", strlen("login success "), NULL);
			}
			else if (strcmp(flag, "broad") == 0)
			{
				for (int i = 0; i < allPlayer.size(); i++)
				{
					myserver.SendMsg(allPlayer[i],temp,strlen(temp));
				}
			}
			else
			{
				if (strcmp(temp, "client close") == 0)
				{
					closesocket(player.first);
					closesocket(player.second);
					break;
				}
				myserver.SendMsg(player.second, temp, strlen(temp), NULL);
			}
			
		}
		if (myserver.ReciveMsg(player.second, tp2, sizeof(tp2), NULL))
		{
			printf("%u:%s\n", player.second, tp2);
			sscanf(tp2, "%s ", flag);
			if (strcmp(flag, "login") == 0)
			{
				myserver.SendMsg(player.second, "login success ", strlen("login success "), NULL);
			}
			else if (strcmp(flag, "broad") == 0)
			{
				for (int i = 0; i < allPlayer.size(); i++)
				{
					myserver.SendMsg(allPlayer[i], tp2, strlen(tp2));
				}
			}
			else
			{
				if (strcmp(tp2, "client close") == 0)
				{
					closesocket(player.first);
					closesocket(player.second);
					break;
				}
				myserver.SendMsg(player.first, tp2, strlen(tp2), NULL);
			}
			
		}
		Sleep(10);
	}
}