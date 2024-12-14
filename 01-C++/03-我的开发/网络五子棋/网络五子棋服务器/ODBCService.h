#ifndef _ODBCSERVICE_H_
#define _ODBCSERVICE_H_
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<sql.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<odbcinst.h>
#include<odbcss.h>
class ODBCService
{
public:
	ODBCService();
	~ODBCService();
	void SetDsnName(char * dsnname);
	void SetLoginName(char * logname);
	void SetLoginKey(char * logkey);
	bool ConnectDB();
	SQLRETURN AllocHandle(SQLHANDLE * OutputHandle = NULL);
	SQLRETURN ExecDirect(SQLCHAR * SQLStateText, SQLINTEGER TextLen, SQLHSTMT StateHandle = NULL);
	SQLRETURN BindColumn(SQLUSMALLINT ColumnNumber, SQLPOINTER TargetValue, SQLINTEGER BufferLen, SQLHSTMT StateHandle = NULL, SQLSMALLINT TargetType = SQL_C_CHAR, SQLINTEGER * StrLen_Or_Ind = NULL);
	SQLRETURN Fetch(SQLHSTMT StateHandle = NULL);
	SQLRETURN FreeHandle(SQLHSTMT StateHandle = NULL);
	bool RetHaveData(SQLRETURN retcode = NULL);
	SQLHSTMT GetStateHandle();
	RETCODE GetSQLRetCode();
	SQLRETURN Prepare(SQLCHAR * SQLStateText, SQLINTEGER TextLen, SQLHSTMT StateHandle = NULL);
	SQLRETURN BindParameter(SQLUSMALLINT ParameterNumber, SQLULEN ColumnSize, SQLPOINTER ParameterValuePtr, \
		SQLSMALLINT InputOutputType = SQL_PARAM_INPUT, SQLSMALLINT  ValueType = SQL_C_CHAR, \
		SQLSMALLINT ParameterType = SQL_CHAR, SQLSMALLINT DecimalDigits = 0, \
		SQLHSTMT StateHandle = NULL, SQLLEN BufferLength = 0, SQLLEN * StrLen_or_IndPtr = NULL);
	SQLRETURN Execute(SQLHSTMT StateHandle = NULL);
private:
	SQLHENV mHenv;//»·¾³¾ä±ú
	SQLHDBC mHdbc;//Á´½Ó¾ä±ú
	SQLHSTMT mHstmt;//Óï¾ä¾ä±ú

	RETCODE retcode;//·µ»Ø´úÂë
	UCHAR szDSN[SQL_MAX_DSN_LENGTH + 1]; //ODBC DSN Ãû³Æ
	UCHAR szUID[MAXNAME];					//ODBC µÇÂ¼ÓÃ»§Ãû
	UCHAR szAuthStr[MAXNAME];			//µÇÂ¼ÃÜÂë
};

#endif // !_ODBCSERVICE_H_