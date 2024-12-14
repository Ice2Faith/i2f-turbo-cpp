#ifndef _SQLITE3HELPER_H_
#define _SQLITE3HELPER_H_
#include<vector>
#include<string>
#include"sqlite3.h"
#pragma comment(lib,"sqlite3.lib")
typedef std::vector<std::vector<std::string>> SqlDataTable;
typedef int(*SqlDataReadCallbackFunc)(void *data, int argCount, char ** argValues, char ** ColNames);
class Sqlite3Helper
{
private:
	sqlite3 * db;
	char * errInfo;
	bool wasClosed;
	void InitEnv();
	void CleanErrInfo();
public:
	Sqlite3Helper();
	Sqlite3Helper(char * DbFileName);
	virtual ~Sqlite3Helper();
	int Open(char * DbFileName);
	int ExecNoQuery(char * sql);
	int ExecQuery(char * sql, SqlDataReadCallbackFunc callbackFunc);
	int ExecQueryTable(char * sql, SqlDataTable  & sqlTable);
	int Close();
	const char* ErrorMsg();
	bool isOk(int code);
};
#endif // _SQLITE3HELPER_H_