#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Sqlite3Helper.h"
using namespace std;
int QueryProc(void *data,int argc,char ** argv,char **azColName)
{
    for(int i=0;i<argc;i++)
    {
        printf("%s\t",azColName[i]);
    }
	printf("\n");
    for(int i=0;i<argc;i++)
    {
        printf("%s\t",argv[i]);
    }
	return 0;
}
void Sqlite3Test()
{
	Sqlite3Helper sqlHelper;
	if(!sqlHelper.isOk(sqlHelper.Open("testDB.db")))
    {
        printf("打开数据库失败！！\n");
        return;
    }
    //创建表
    char sql[1024];
    strcpy(sql,"create table passwordkey(account varchar(20),password varchar(20),info varchar(120));");
	if (!sqlHelper.isOk(sqlHelper.ExecNoQuery(sql)))
    {
        printf("建表失败！！\n");
		sqlHelper.Close();
        return;
    }
    //执行非查询语句
    strcpy(sql,"insert into passwordkey values('30110111100','rppvscddk','QQ Login');\
    insert into passwordkey values('19221000012','11112547','WeChat Login');");
	if (!sqlHelper.isOk(sqlHelper.ExecNoQuery(sql)))
    {
        printf("插入失败！！\n");
		sqlHelper.Close();
        return;
    }
    //执行查询语句
    strcpy(sql,"select * from passwordkey;");
	vector<vector<string>> dataTable;
	if (!sqlHelper.isOk(sqlHelper.ExecQueryTable(sql,dataTable)))
    {
        printf("查询失败！！\n");
		sqlHelper.Close();
        return;
    }
	else
	{
		for (int i = 0; i < dataTable.size(); i++)
		{
			for (int j = 0; j < dataTable[i].size(); j++)
			{
				printf("%s\t", (dataTable[i])[j].c_str());
			}
			printf("\n");
		}
	}
    //关闭数据库
	sqlHelper.Close();
}
int main(int argc,char * argv[])
{
    Sqlite3Test();
	system("pause");
    return 0;
}
