
#include"ODBCService.h"
ODBCService::ODBCService()
{
	this->mHenv = SQL_NULL_HENV;
	this->mHdbc = SQL_NULL_HDBC;
	this->mHstmt = SQL_NULL_HSTMT;
}

ODBCService::~ODBCService()
{
	//断开与数据源的链接
	SQLDisconnect(this->mHdbc);
	//释放连接句柄
	SQLFreeHandle(SQL_HANDLE_DBC, this->mHdbc);
	//释放环境句柄
	SQLFreeHandle(SQL_HANDLE_ENV, this->mHenv);
}

bool ODBCService::ConnectDB()
{
	//环境句柄
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &mHenv);
	retcode = SQLSetEnvAttr(mHenv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	//链接句柄
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, mHenv, &mHdbc);
	retcode = SQLConnect(mHdbc, \
		szDSN, strlen((const char *)szDSN), \
		szUID, strlen((const char *)szUID), \
		szAuthStr, strlen((const char *)szAuthStr));
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		return false;
	}
	return true;
}
void ODBCService::SetDsnName(char * dsnname)
{
	strcpy((char *)this->szDSN, dsnname);
}
void ODBCService::SetLoginName(char * logname)
{
	strcpy((char *)this->szUID, logname);
}
void ODBCService::SetLoginKey(char * logkey)
{
	strcpy((char *)this->szAuthStr, logkey);
}
SQLRETURN ODBCService::AllocHandle(SQLHANDLE * OutputHandle)
{
	SQLHANDLE * phand = OutputHandle;
	if (phand == NULL)
		phand = &this->mHstmt;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, mHdbc, phand);
	return retcode;
}
SQLRETURN ODBCService::ExecDirect(SQLCHAR * SQLStateText, SQLINTEGER TextLen, SQLHSTMT StateHandle)
{
	SQLHANDLE phand = StateHandle;
	if (phand == NULL)
		phand = this->mHstmt;
	retcode = SQLExecDirect(phand, SQLStateText, TextLen);
	return retcode;
}
SQLRETURN ODBCService::BindColumn(SQLUSMALLINT ColumnNumber, SQLPOINTER TargetValue, SQLINTEGER BufferLen,\
	SQLHSTMT StateHandle, SQLSMALLINT TargetType, SQLINTEGER * StrLen_Or_Ind)
{
	SQLHANDLE phand = StateHandle;
	if (phand == NULL)
		phand = this->mHstmt;
	retcode = SQLBindCol(phand, ColumnNumber, TargetType, TargetValue, BufferLen, StrLen_Or_Ind);
	return retcode;
}
SQLRETURN ODBCService::Fetch(SQLHSTMT StateHandle)
{
	SQLHANDLE phand = StateHandle;
	if (phand == NULL)
		phand = this->mHstmt;
	retcode = SQLFetch(phand);
	return retcode;
}
SQLRETURN ODBCService::FreeHandle(SQLHSTMT StateHandle)
{
	SQLHANDLE phand = StateHandle;
	if (phand == NULL)
		phand = this->mHstmt;
	retcode = SQLCloseCursor(phand);
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, phand);
	return retcode;
}
bool ODBCService::RetHaveData(SQLRETURN retcode)
{
	SQLRETURN pretcode = retcode;
	if (pretcode == NULL)
		pretcode = this->retcode;
	return (!(pretcode == SQL_NO_DATA));
}
SQLHSTMT ODBCService::GetStateHandle()
{
	return this->mHstmt;
}
RETCODE ODBCService::GetSQLRetCode()
{
	return this->retcode;
}
SQLRETURN ODBCService::Execute(SQLHSTMT StateHandle)
{
	SQLHANDLE phand = StateHandle;
	if (phand == NULL)
		phand = this->mHstmt;
	retcode = SQLExecute(phand);
	return retcode;
}
SQLRETURN ODBCService::Prepare(SQLCHAR * SQLStateText, SQLINTEGER TextLen, SQLHSTMT StateHandle)
{
	SQLHANDLE phand = StateHandle;
	if (phand == NULL)
		phand = this->mHstmt;
	retcode = SQLPrepare(phand, SQLStateText, TextLen);
	return retcode;
}
SQLRETURN ODBCService::BindParameter(SQLUSMALLINT ParameterNumber, SQLULEN ColumnSize, SQLPOINTER ParameterValuePtr, \
	SQLSMALLINT InputOutputType, SQLSMALLINT  ValueType, \
	SQLSMALLINT ParameterType, SQLSMALLINT DecimalDigits, \
	SQLHSTMT StateHandle, SQLLEN BufferLength, SQLLEN * StrLen_or_IndPtr)
{
	SQLHANDLE phand = StateHandle;
	if (phand == NULL)
		phand = this->mHstmt;
	retcode = SQLBindParameter(phand, ParameterNumber, InputOutputType, ValueType, ParameterType, \
		ColumnSize, DecimalDigits, ParameterValuePtr, BufferLength, StrLen_or_IndPtr);
	return retcode;
}