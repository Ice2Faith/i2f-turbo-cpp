#include"Sqlite3Helper.h"
#include<stdio.h>
void Sqlite3Helper::InitEnv()
{
	db = NULL;
	errInfo = NULL;
	wasClosed = true;
}
void Sqlite3Helper::CleanErrInfo()
{
	if (errInfo != NULL)
	{
		sqlite3_free(errInfo);
		errInfo = NULL;
	}
}
Sqlite3Helper::Sqlite3Helper()
{
	InitEnv();
}
Sqlite3Helper::Sqlite3Helper(char * DbFileName)
{
	InitEnv();
	Open(DbFileName);
}
Sqlite3Helper::~Sqlite3Helper()
{
	if (wasClosed == false)
	{
		wasClosed = true;
		sqlite3_close(db);
	}
	CleanErrInfo();
}
int Sqlite3Helper::Open(char * DbFileName)
{
	wasClosed = true;
	int ret = sqlite3_open(DbFileName, &db);
	if (isOk(ret))
		wasClosed = false;
	return ret;
}
int Sqlite3Helper::ExecNoQuery(char * sql)
{
	CleanErrInfo();
	return sqlite3_exec(db, sql, NULL, NULL, &errInfo);
}
int Sqlite3Helper::ExecQuery(char * sql, SqlDataReadCallbackFunc callbackFunc)
{
	CleanErrInfo();
	return sqlite3_exec(db, sql, callbackFunc, NULL, &errInfo);
}
int SQLITE3_HEPLER_DEFAULT_CALL_BACK(void *data, int argCount, char ** argValues, char ** ColNames)
{
	std::vector<std::vector<std::string>> * sqlDataTable = (std::vector<std::vector<std::string>> *)data;
	if (sqlDataTable->size() == 0)
	{
		std::vector<std::string> header;
		std::vector<std::string> dataline;
		for (int i = 0; i < argCount; i++)
		{
			header.push_back(ColNames[i]);
			dataline.push_back(argValues[i]);
		}
		sqlDataTable->push_back(header);
		sqlDataTable->push_back(dataline);
	}
	else
	{
		std::vector<std::string> dataline;
		for (int i = 0; i < argCount; i++)
		{
			dataline.push_back(argValues[i]);
		}
		sqlDataTable->push_back(dataline);
	}
	return 0;
}
int Sqlite3Helper::ExecQueryTable(char * sql, SqlDataTable  & sqlTable)
{
	CleanErrInfo();
	for (int i = 0; i < sqlTable.size(); i++)
	{
		sqlTable[i].clear();
	}
	sqlTable.clear();
	return sqlite3_exec(db, sql, SQLITE3_HEPLER_DEFAULT_CALL_BACK, &sqlTable, &errInfo);
}
int Sqlite3Helper::Close()
{
	if (wasClosed == false)
	{
		wasClosed = true;
		return sqlite3_close(db);
	}
	return 0;
}
const char* Sqlite3Helper::ErrorMsg()
{
	return sqlite3_errmsg(db);
}
bool Sqlite3Helper::isOk(int code)
{
	return code == SQLITE_OK;
}
const sqlite3 * Sqlite3Helper::GetDB()
{
	return db;
}