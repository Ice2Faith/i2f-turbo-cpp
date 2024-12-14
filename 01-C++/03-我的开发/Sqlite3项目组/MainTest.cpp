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
        printf("�����ݿ�ʧ�ܣ���\n");
        return;
    }
    //������
    char sql[1024];
    strcpy(sql,"create table passwordkey(account varchar(20),password varchar(20),info varchar(120));");
	if (!sqlHelper.isOk(sqlHelper.ExecNoQuery(sql)))
    {
        printf("����ʧ�ܣ���\n");
		sqlHelper.Close();
        return;
    }
    //ִ�зǲ�ѯ���
    strcpy(sql,"insert into passwordkey values('30110111100','rppvscddk','QQ Login');\
    insert into passwordkey values('19221000012','11112547','WeChat Login');");
	if (!sqlHelper.isOk(sqlHelper.ExecNoQuery(sql)))
    {
        printf("����ʧ�ܣ���\n");
		sqlHelper.Close();
        return;
    }
    //ִ�в�ѯ���
    strcpy(sql,"select * from passwordkey;");
	vector<vector<string>> dataTable;
	if (!sqlHelper.isOk(sqlHelper.ExecQueryTable(sql,dataTable)))
    {
        printf("��ѯʧ�ܣ���\n");
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
    //�ر����ݿ�
	sqlHelper.Close();
}
int main(int argc,char * argv[])
{
    Sqlite3Test();
	system("pause");
    return 0;
}
