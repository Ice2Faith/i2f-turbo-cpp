#ifndef _EVER_FILE_LOCKER_HPP_
#define _EVER_FILE_LOCKER_HPP_

#include"EverythingLocker.hpp"
#include<stdio.h>
#include<string.h>
/*
�ļ��ӽ��ܹ�����
�������������˵���Ƽ�ʹ��UTF8��������룬�����������ӿ�ƽ̨����ֲ��

��������������Ϊʲô���ἰ�أ�
��Ϊ������������������·��������ֻҪ�ҵõ�·�����У�����νʲô����
*/
class EveryFileLocker
{
public:
	EveryFileLocker()
	{
		InitEnv();
	}
	BOOL_T lock(const INT8_T * srcFileName, const INT8_T * drtFileName, const INT8_T * password)
	{
		if (srcFileName == NULL || drtFileName == NULL || password == NULL)
			return BOOL_FALSE;

		FILE * fsrc = fopen(srcFileName, "rb");
		if (fsrc == NULL)
			return BOOL_FALSE;

		FILE * fdrt = fopen(drtFileName, "wb");
		if (fdrt == NULL)
		{
			fclose(fsrc);
			return BOOL_FALSE;
		}
		
		if (writeHeader(fdrt, password) == BOOL_FALSE)
		{
			fclose(fdrt);
			fclose(fsrc);
			remove(drtFileName);
			return BOOL_FALSE;
		}

		INT32_T sizePass = strlen(password);
		locker.cleanLockCode();

		INT32_T sizeBuf = 1024;
		UINT8_T buf[1024];
		while (!feof(fsrc))
		{
			INT32_T rsize=fread(buf, sizeof(UINT8_T), sizeBuf, fsrc);
			locker.lock(buf, rsize, (UINT8_T *)password, sizePass, BOOL_TRUE);
			INT32_T wsize=fwrite(buf, sizeof(UINT8_T), rsize, fdrt);

			if (rsize != wsize)
			{
				fprintf(stderr, "д�����ݲ����������棡\n");
			}
			if (rsize != sizeBuf)
				break;
		}


		fclose(fsrc);
		fclose(fdrt);
		return BOOL_TRUE;
	}
	BOOL_T unlock(const INT8_T * srcFileName, const INT8_T * drtFileName, const INT8_T * password)
	{
		if (srcFileName == NULL || drtFileName == NULL || password == NULL)
			return BOOL_FALSE;

		FILE * fsrc = fopen(srcFileName, "rb");
		if (fsrc == NULL)
			return BOOL_FALSE;

		if (readHeader(fsrc, password) == BOOL_FALSE)
		{
			fclose(fsrc);
			return BOOL_FALSE;
		}

		FILE * fdrt = fopen(drtFileName, "wb");
		if (fdrt == NULL)
		{
			fclose(fsrc);
			return BOOL_FALSE;
		}

		INT32_T sizePass = strlen(password);
		locker.cleanUnlockCode();

		INT32_T sizeBuf = 1024;
		UINT8_T buf[1024];
		while (!feof(fsrc))
		{
			INT32_T rsize = fread(buf, sizeof(UINT8_T), sizeBuf, fsrc);
			locker.unlock(buf, rsize, (UINT8_T *)password, sizePass, BOOL_TRUE);
			INT32_T wsize = fwrite(buf, sizeof(UINT8_T), rsize, fdrt);

			if (rsize != wsize)
			{
				fprintf(stderr, "д�����ݲ����������棡\n");
			}
			if (rsize != sizeBuf)
				break;
		}


		fclose(fsrc);
		fclose(fdrt);
		return BOOL_TRUE;
	}
private:
	EverythingLocker locker;

	INT8_T inearKey[256];
	INT32_T sizeInearKey;
	void InitEnv()
	{
		locker.cleanLockAndUnlockCode();
		INT8_T ik[] = { 'E', 'v', 'e', 'r', 'y', 'F', 'i', 'l', 'e', 'L', 'o', 'c', 'k', 'e', 'r', '@', 'U', 'g', 'e', 'x', '.', 'S', 'a', 'v', 'e', 'l', 'a', 'r', 0};
		strcpy(inearKey,ik);
		sizeInearKey = strlen(inearKey);
	}
	BOOL_T writeHeader(FILE * fd, const INT8_T * password)
	{
		INT32_T sizePass = strlen(password);
		INT8_T * spass = new INT8_T[sizePass+1];
		strcpy(spass, password);
		locker.lock((UINT8_T *)spass, sizePass, (UINT8_T *)inearKey, sizeInearKey);
		fwrite("USEFL", sizeof(INT8_T), 5, fd);
		//��˷�ʽ���泤�ȵ��ļ�
		UINT32_T wrSizePass = sizePass;
		host2BigEndian(&wrSizePass, sizeof(INT32_T));
		fwrite(&wrSizePass, sizeof(INT32_T), 1, fd);

		fwrite(spass, sizeof(INT8_T), sizePass, fd);
		delete[] spass;
		return BOOL_TRUE;
	}
	BOOL_T readHeader(FILE * fd, const INT8_T * password)
	{
		INT8_T flg[8] = { 0 };
		int rf=fread(flg, sizeof(INT8_T), 5, fd);
		if (strcmp(flg, "USEFL") != 0)
		{
			return BOOL_FALSE;
		}
		INT32_T sizePass = 0;
		fread(&sizePass, sizeof(INT32_T), 1, fd);
		//��ȡ����֮�󣬻���Ϊ�����Ķ���ʽ
		bigEndian2Host(&sizePass, sizeof(INT32_T));
		if (sizePass <= 0 || sizePass!=strlen(password))
		{
			return BOOL_FALSE;
		}
		INT8_T spass[1024] = { 0 };
		memset(spass, 0, sizeof(spass));
		fread(spass, sizeof(INT8_T), sizePass, fd);
		locker.unlock((UINT8_T *)spass, sizePass, (UINT8_T *)inearKey, sizeInearKey);
		int pl = strlen(spass);
		if (strcmp(spass, password) != 0)
		{
			return BOOL_FALSE;
		}
		return BOOL_TRUE;
	}
};

#endif // _EVER_FILE_LOCKER_HPP_