#ifndef _EVER_FILE_LOCKER_HPP_
#define _EVER_FILE_LOCKER_HPP_

#include"EverythingLocker.hpp"
#include<stdio.h>
#include<string.h>
class EveryFileLocker
{
public:
	EveryFileLocker()
	{
		InitEnv();
	}
	bool lock(const char * srcFileName, const char * drtFileName, const char * password)
	{
		if (srcFileName == NULL || drtFileName == NULL || password == NULL)
			return false;

		FILE * fsrc = fopen(srcFileName, "rb");
		if (fsrc == NULL)
			return false;

		FILE * fdrt = fopen(drtFileName, "wb");
		if (fdrt == NULL)
		{
			fclose(fsrc);
			return false;
		}
		
		if (writeHeader(fdrt, password) == false)
		{
			fclose(fdrt);
			fclose(fsrc);
			remove(drtFileName);
			return false;
		}

		long sizePass = strlen(password);
		locker.cleanLockCode();

		long sizeBuf = 1024;
		unsigned char buf[1024];
		while (!feof(fsrc))
		{
			long rsize=fread(buf, sizeof(unsigned char), sizeBuf, fsrc);
			locker.lock(buf, rsize, (unsigned char *)password, sizePass, true);
			long wsize=fwrite(buf, sizeof(unsigned char), rsize, fdrt);

			if (rsize != wsize)
			{
				fprintf(stderr, "写入数据不完整，警告！\n");
			}
			if (rsize != sizeBuf)
				break;
		}


		fclose(fsrc);
		fclose(fdrt);
		return true;
	}
	bool unlock(const char * srcFileName, const char * drtFileName, const char * password)
	{
		if (srcFileName == NULL || drtFileName == NULL || password == NULL)
			return false;

		FILE * fsrc = fopen(srcFileName, "rb");
		if (fsrc == NULL)
			return false;

		if (readHeader(fsrc, password) == false)
		{
			fclose(fsrc);
			return false;
		}

		FILE * fdrt = fopen(drtFileName, "wb");
		if (fdrt == NULL)
		{
			fclose(fsrc);
			return false;
		}

		long sizePass = strlen(password);
		locker.cleanUnlockCode();

		long sizeBuf = 1024;
		unsigned char buf[1024];
		while (!feof(fsrc))
		{
			long rsize = fread(buf, sizeof(unsigned char), sizeBuf, fsrc);
			locker.unlock(buf, rsize, (unsigned char *)password, sizePass, true);
			long wsize = fwrite(buf, sizeof(unsigned char), rsize, fdrt);

			if (rsize != wsize)
			{
				fprintf(stderr, "写入数据不完整，警告！\n");
			}
			if (rsize != sizeBuf)
				break;
		}


		fclose(fsrc);
		fclose(fdrt);
		return true;
	}
private:
	EverythingLocker locker;

	char inearKey[256];
	long sizeInearKey;
	void InitEnv()
	{
		locker.cleanLockAndUnlockCode();
		char ik[] = {"EveryFileLocker@Ugex.Savelar"};
		strcpy(inearKey,ik);
		sizeInearKey = strlen(inearKey);
	}
	bool writeHeader(FILE * fd, const char * password)
	{
		long sizePass = strlen(password);
		char * spass = new char[sizePass+1];
		strcpy(spass, password);
		locker.lock((unsigned char *)spass, sizePass, (unsigned char *)inearKey, sizeInearKey);
		fwrite("EFL", sizeof(char), 3, fd);
		fwrite(&sizePass, sizeof(long), 1, fd);
		fwrite(spass, sizeof(char), sizePass, fd);
		delete[] spass;
		return true;
	}
	bool readHeader(FILE * fd, const char * password)
	{
		char flg[5] = { 0 };
		int rf=fread(flg, sizeof(char), 3, fd);
		if (strcmp(flg, "EFL") != 0)
		{
			return false;
		}
		long sizePass = 0;
		fread(&sizePass, sizeof(long), 1, fd);
		if (sizePass <= 0 || sizePass!=strlen(password))
		{
			return false;
		}
		char spass[1024] = { 0 };
		memset(spass, 0, sizePass);
		fread(spass, sizeof(char), sizePass, fd);
		locker.unlock((unsigned char *)spass, sizePass, (unsigned char *)inearKey, sizeInearKey);
		int pl = strlen(spass);
		if (strcmp(spass, password) != 0)
		{
			return false;
		}
		return true;
	}
};

#endif // _EVER_FILE_LOCKER_HPP_