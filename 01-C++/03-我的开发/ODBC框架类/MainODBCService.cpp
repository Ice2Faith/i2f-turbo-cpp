#include"ODBCService.h"
/** Name: ODBC Class Test*/
#include<iostream>

using namespace std;

int main(int argc, char * argv[])
{
	ODBCService myodbc;
	myodbc.SetDsnName("myStuDB");
	myodbc.SetLoginName("sa");
	myodbc.SetLoginKey("ltb12315");
	if (!myodbc.ConnectDB())
		return -1;
	//定义数据接收单元
	char id[20] = { 0 };
	char name[50] = { 0 };
	char sex[4] = { 0 };
	char tel[20] = { 0 };
	char other[200] = { 0 };
	myodbc.AllocHandle();
	myodbc.BindColumn(1, id, sizeof(id));
	myodbc.BindColumn(2, name, sizeof(name));
	myodbc.BindColumn(3, sex, sizeof(sex));
	myodbc.BindColumn(4, tel, sizeof(tel));
	myodbc.BindColumn(5, other, sizeof(other));
	
	UCHAR sql[512] = { "select * from stuinfo" };
	myodbc.ExecDirect(sql, strlen((char *)sql));
	if (myodbc.RetHaveData())
	{
		printf("%8s  %20s  %2s  %11s  %s\n", "ID", "NAME", "SEX", "TEL", "OTHER");
		printf("%8s  %20s  %2s  %11s  %s\n", id, name, sex, tel, other);
		//获取所有数据并输出
		while (1)
		{
			myodbc.Fetch();
			if (!myodbc.RetHaveData())
				break;
			printf("%8s  %20s  %2s  %11s  %s\n", id, name, sex, tel, other);
		}
	}
	myodbc.FreeHandle();
	system("pause");


	myodbc.AllocHandle();
	UCHAR sql_pre[512] = { "select (?) from stuinfo" };
	char table[10] = { "name" };
	myodbc.Prepare(sql_pre,SQL_NTS);
	myodbc.BindParameter(1,512,&table);
	myodbc.BindColumn(1, id, sizeof(id));
	myodbc.BindColumn(2, name, sizeof(name));
	myodbc.BindColumn(3, sex, sizeof(sex));
	myodbc.BindColumn(4, tel, sizeof(tel));
	myodbc.BindColumn(5, other, sizeof(other));
	myodbc.Execute();
	//定义数据接收单元
	if (myodbc.RetHaveData())
	{
		printf("%8s  %20s  %2s  %11s  %s\n", "ID", "NAME", "SEX", "TEL", "OTHER");
		printf("%8s  %20s  %2s  %11s  %s\n", id, name, sex, tel, other);
		//获取所有数据并输出
		while (1)
		{
			myodbc.Fetch();
			if (!myodbc.RetHaveData())
				break;
			printf("%8s  %20s  %2s  %11s  %s\n", id, name, sex, tel, other);
		}
	}
	myodbc.FreeHandle();
	system("pause");
	return 0;
}