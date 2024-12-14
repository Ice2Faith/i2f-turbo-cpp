#ifndef _ALGO_WIN_ODBC_HPP_
#define _ALGO_WIN_ODBC_HPP_
#include"AlgoString.hpp"

#include<windows.h>
#include<sql.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<odbcinst.h>
#include<odbcss.h>

class AlgoWinOdbc
{
public:
	static SQLRETURN allocHandle(SQLSMALLINT sqlType,SQLHANDLE inHandle,SQLHANDLE * outHandle)
	{
		return SQLAllocHandle(sqlType, inHandle, outHandle);
	}
	static SQLRETURN allocEnvironmentHandle(SQLHANDLE * outEnvHandle, SQLHANDLE inHandle = SQL_NULL_HENV)
	{
		return SQLAllocHandle(SQL_HANDLE_ENV, inHandle, outEnvHandle);
	}
	static SQLRETURN allocLinkHandle(SQLHANDLE *outLnkHandle, SQLHANDLE inEnvHandle)
	{
		return SQLAllocHandle(SQL_HANDLE_DBC, inEnvHandle, outLnkHandle);
	}
	static SQLRETURN allocExecSqlHandle(SQLHANDLE * outExecSqlHandle, SQLHANDLE inLnkHandle)
	{
		return SQLAllocHandle(SQL_HANDLE_STMT, inLnkHandle, outExecSqlHandle);
	}
	static SQLRETURN freeHandle(SQLSMALLINT sqlType, SQLHANDLE inHandle)
	{
		return SQLFreeHandle(sqlType, inHandle);
	}
	static SQLRETURN freeEnvironmentHandle(SQLHANDLE inEnvHandle)
	{
		return SQLFreeHandle(SQL_HANDLE_ENV, inEnvHandle);
	}
	static SQLRETURN freeLinkHandle(SQLHANDLE inLnkHandle)
	{
		return SQLFreeHandle(SQL_HANDLE_DBC, inLnkHandle);
	}
	static SQLRETURN freeExecSqlHandle(SQLHANDLE inExecSqlHandle)
	{
		return SQLFreeHandle(SQL_HANDLE_STMT, inExecSqlHandle);
	}
	static SQLRETURN setEnvironmentAttribute(SQLHANDLE inEnvHandle,SQLINTEGER attrType,SQLPOINTER attrValue, SQLINTEGER attrValueType)
	{
		return SQLSetEnvAttr(inEnvHandle, attrType, attrValue, attrValueType);
	}
	static SQLRETURN setEnvAttrOdbcVersion(SQLHANDLE inEnvHandle, unsigned long version = SQL_OV_ODBC3)
	{
		return SQLSetEnvAttr(inEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)version, SQL_IS_INTEGER);
	}
	static SQLRETURN connect(SQLHANDLE inLnkHandle, 
		SQLTCHAR * dsnName,SQLSMALLINT dsnNameLen,
		SQLTCHAR * odbcLoginUserName,SQLSMALLINT loginNameLen,
		SQLTCHAR * loginPassword,SQLSMALLINT loginPassLen)
	{
		return SQLConnect(inLnkHandle, dsnName, dsnNameLen, odbcLoginUserName, loginNameLen, loginPassword, loginPassLen);
	}
	static SQLRETURN connect(SQLHANDLE inLnkHandle, SQLTCHAR * dsnName, SQLTCHAR * loginName, SQLTCHAR * loginPassword)
	{
		return SQLConnect(inLnkHandle, dsnName, SQL_NTS, loginName, SQL_NTS, loginPassword, SQL_NTS);
	}
	static bool directToConnectedOdbcVer3(SQLHANDLE * outEnvHandle,
		SQLHANDLE * outLnkHandle,
		SQLTCHAR * dsnName, SQLTCHAR * loginName, SQLTCHAR * loginPassword)
	{
		SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HENV, outEnvHandle);
		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			return false;
		}
		ret = SQLSetEnvAttr(*outEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			return false;
		}
		ret = SQLAllocHandle(SQL_HANDLE_DBC, *outEnvHandle, outLnkHandle);
		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			return false;
		}
		ret = SQLConnect(*outLnkHandle, dsnName, SQL_NTS, loginName, SQL_NTS, loginPassword, SQL_NTS);
		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			return false;
		}
		return true;
	}
	static bool isRetSuccess(SQLRETURN retCode)
	{
		if (retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO)
		{
			return false;
		}
		return true;
	}
	static SQLRETURN execSql(SQLHANDLE inExecSqlHandle,SQLTCHAR * sql,SQLINTEGER sqlLen=SQL_NTS)
	{
		return SQLExecDirect(inExecSqlHandle, sql, sqlLen);
	}
	static bool execSqlHaveData(SQLHANDLE inExecSqlHandle, SQLTCHAR * sql, SQLINTEGER sqlLen = SQL_NTS)
	{
		return SQLExecDirect(inExecSqlHandle, sql, sqlLen)!=SQL_NO_DATA;
	}
	static SQLRETURN bindColData(SQLHANDLE inExecSqlHandle,SQLUSMALLINT colNumber,SQLSMALLINT needDataType,
		SQLPOINTER saveDataPointer, SQLINTEGER saveDataSize, SQLINTEGER * strLenOrLndptr=NULL)
	{
		return SQLBindCol(inExecSqlHandle, colNumber, needDataType, saveDataPointer, saveDataSize, strLenOrLndptr);
	}
	static SQLRETURN bindColString(SQLHANDLE inExecSqlHandle, SQLUSMALLINT colNumber,
		SQLPOINTER saveStringBuf, SQLINTEGER saveBufSize)
	{
		return SQLBindCol(inExecSqlHandle, colNumber, SQL_C_CHAR, saveStringBuf, saveBufSize, NULL);
	}
	static SQLRETURN bindColInteger(SQLHANDLE inExecSqlHandle, SQLUSMALLINT colNumber,
		SQLPOINTER saveIntegerBuf, SQLINTEGER saveIntSize)
	{
		return SQLBindCol(inExecSqlHandle, colNumber, SQL_C_LONG, saveIntegerBuf, saveIntSize, NULL);
	}
	static SQLRETURN bindColFloatNumber(SQLHANDLE inExecSqlHandle, SQLUSMALLINT colNumber,
		SQLPOINTER saveFloatBuf, SQLINTEGER saveFloatSize)
	{
		return SQLBindCol(inExecSqlHandle, colNumber, SQL_C_DOUBLE, saveFloatBuf, saveFloatSize, NULL);
	}
	static SQLRETURN fetch(SQLHANDLE inExecSqlHandle)
	{
		return SQLFetch(inExecSqlHandle);
	}
	static bool fetchHaveData(SQLHANDLE inExecSqlHandle)
	{
		return SQLFetch(inExecSqlHandle) != SQL_NO_DATA;
	}
	static SQLRETURN disconnect(SQLHANDLE inLnkHandle)
	{
		return SQLDisconnect(inLnkHandle);
	}
	static bool directDisconnectAndFree(SQLHANDLE inLnkHandle,SQLHANDLE inEnvHandle)
	{
		SQLRETURN ret = SQLDisconnect(inLnkHandle);
		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			return false;
		}
		ret = SQLFreeHandle(SQL_HANDLE_DBC, inLnkHandle);
		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			return false;
		}
		ret = SQLFreeHandle(SQL_HANDLE_ENV, inEnvHandle);
		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			return false;
		}
		return true;
	}
	static SQLRETURN prepareSql(SQLHANDLE inExecSqlHandle, SQLTCHAR * sqlPre, SQLINTEGER sqlPreLen)
	{
		return SQLPrepare(inExecSqlHandle, sqlPre, sqlPreLen=SQL_NTS);
	}
	static SQLRETURN bindPrepareSqlParam(SQLHANDLE inExecSqlHandle,SQLUSMALLINT paramSpaceNumber,
		SQLSMALLINT clangValueType,SQLSMALLINT sqlValueParamType,
		SQLULEN colSize,SQLSMALLINT decimalDigits,SQLPOINTER paramValueBufPtr,SQLLEN bufSize,
		SQLSMALLINT inputOutputTypeFlag = SQL_PARAM_INPUT,SQLLEN * strLenOrLndPtr = NULL)
	{
		return SQLBindParameter(inExecSqlHandle, paramSpaceNumber, inputOutputTypeFlag, clangValueType, sqlValueParamType, colSize, decimalDigits, paramValueBufPtr, bufSize, strLenOrLndPtr);
	}
	static SQLRETURN bindPrepareSqlStringParam(SQLHANDLE inExecSalHandle, SQLUSMALLINT paramSpaceNumber,
		SQLPOINTER paramValueBufPtr,SQLULEN colSize)
	{
		return SQLBindParameter(inExecSalHandle, paramSpaceNumber, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, colSize, 0, paramValueBufPtr, 0, NULL);
	}
	static SQLRETURN bindPrepareSqlIntegerParam(SQLHANDLE inExecSalHandle, SQLUSMALLINT paramSpaceNumber,
		SQLPOINTER paramValueBufPtr, SQLULEN colSize)
	{
		return SQLBindParameter(inExecSalHandle, paramSpaceNumber, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, colSize, 0, paramValueBufPtr, 0, NULL);
	}
	static SQLRETURN bindPrepareSqlFloatNumberParam(SQLHANDLE inExecSalHandle, SQLUSMALLINT paramSpaceNumber,
		SQLPOINTER paramValueBufPtr, SQLULEN colSize)
	{
		return SQLBindParameter(inExecSalHandle, paramSpaceNumber, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, colSize, 0, paramValueBufPtr, 0, NULL);
	}
	static SQLRETURN execPrepareSql(HANDLE inExecSqlHandle)
	{
		return SQLExecute(inExecSqlHandle);
	}
	static AlgoArray<AlgoString<TCHAR, int>, int> & getAllStringColumeData(SQLHANDLE inExecSqlHandle, int maxStringLen, SQLSMALLINT colNum, AlgoArray<AlgoString<TCHAR, int>, int> & saveArr)
	{
		AlgoString<TCHAR, int> buf;
		buf[maxStringLen] = 0;
		bindColString(inExecSqlHandle, colNum, buf.getData(), buf.getCapital());
		while (fetchHaveData(inExecSqlHandle)!=SQL_NO_DATA)
		{
			saveArr.push(buf);
		}
		return saveArr;
	}
	template<typename T>
	static AlgoArray<T, int> & getAllSimpleDataColumeData(SQLHANDLE inExecSqlHandle, SQLSMALLINT colNum, AlgoArray<T, int> & saveArr)
	{
		T buf;
		bindColString(inExecSqlHandle, colNum, &buf,sizeof(int));
		while (fetchHaveData(inExecSqlHandle) != SQL_NO_DATA)
		{
			saveArr.push(buf);
		}
		return saveArr;
	}
};

#endif // _ALGO_WIN_ODBC_HPP_