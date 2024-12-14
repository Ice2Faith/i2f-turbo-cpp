#ifndef _FILE_JOIN_H_
#define _FILE_JOIN_H_
/*  */
#include"AlgoTypes32.hpp"
#include<stdio.h>
#include<stdlib.h>
//合并一批文件，这些都只能是文件，不能包含文件夹，文件夹将被跳过
//拆分时，这批文件将会被解压到同一个目录，因此你需要保证文件名不重复
//如果重复文件名将会被覆盖，注意
//文件名重复概念：不同目录下重复文件也算是重复
class FileJoin //: public Object
{
public:
	FileJoin()
	{
		Init();
	}
	
	//参数：文件个数 文件目录数组 目标文件
	BOOL_T join(INT32_T count,char * srcFiles[], char * drtFile)
	{
		FILE * dfp = NULL, *sfp = NULL;
		for (INT32_T i = 0; i < count; i++)
		{
			sfp = NULL;
			sfp = fopen(srcFiles[i], "rb");
			if (sfp == NULL)
			{
				continue;
			}
			else
			{
				if (dfp == NULL)
				{
					dfp = fopen(drtFile,"wb");
					if (dfp == NULL)
					{
						if (sfp)
						{
							fclose(sfp);
						}
						return BOOL_FALSE;
					}
					writeHeader(dfp);
				}
			}
			fseek(sfp, 0, SEEK_END);
			UINT32_T end = ftell(sfp);
			rewind(sfp);
			UINT32_T begin = ftell(sfp);

			char * name = getFileNameInPath(srcFiles[i]);
			UINT16_T name_len = 0;
			while (name[name_len] != 0)
			{
				name_len++;
			}
			UINT16_T wname_len = name_len;
			AlgoHost2BigEndian(&wname_len, sizeof(UINT16_T));
			fwrite(&wname_len, sizeof(UINT16_T), 1, dfp);
			fwrite(name, sizeof(char), name_len, dfp);

			UINT32_T file_len = end - begin;
			AlgoHost2BigEndian(&file_len, sizeof(UINT32_T));
			fwrite(&file_len,sizeof(UINT32_T),1,dfp);
			
			BYTE_T curch = 0;
			while (!feof(sfp))            /*8位无符号字符位于0-255之间*/
			{
				fread(&curch, sizeof(BYTE_T), 1, sfp);    /*获取对应字符的数量、频数*/
				if (feof(sfp))
					break;
				fwrite(&curch, sizeof(BYTE_T), 1, dfp);
			}

			fclose(sfp);
		}

		fclose(dfp);
		return BOOL_TRUE;
	}
	BOOL_T split(char * srcFile, char * drtPath)
	{
		FILE * dfp = NULL, *sfp = NULL;
		sfp = fopen(srcFile,"rb");
		if (sfp == NULL)
		{
			return BOOL_FALSE;
		}
		if (readHeader(sfp)==BOOL_FALSE)
		{
			fclose(sfp);
			return BOOL_FALSE;
		}
		
		while (1)
		{
			UINT16_T pname_zie = 0;
			char pname[256] = { 0 };

			fread(&pname_zie, sizeof(UINT16_T), 1, sfp);
			if (feof(sfp))
				break;
			AlgoBigEndian2Host(&pname_zie, sizeof(UINT16_T));
			fread(pname, sizeof(char), pname_zie, sfp);
			pname[pname_zie] = 0;
			
			char drtFile[2048] = { 0 };
			INT32_T i = 0;
			while (drtPath[i] != 0)
			{
				drtFile[i] = drtPath[i];
				i++;
			}
			INT32_T j = 0;
			while (pname[j] != 0)
			{
				drtFile[i] = pname[j];
				i++;
				j++;
			}
			drtFile[i] = 0;

			dfp = NULL;
			dfp = fopen(drtFile, "wb");
			if (dfp == NULL)
			{
				fclose(sfp);
				return BOOL_FALSE;
			}

			
			UINT32_T psize = 0, rsize = 0;
			fread(&psize, sizeof(UINT32_T), 1, sfp);
			AlgoBigEndian2Host(&psize, sizeof(UINT32_T));

			BYTE_T temp = 0;
			while (rsize < psize)
			{
				fread(&temp, sizeof(BYTE_T), 1, sfp);
				fwrite(&temp, sizeof(BYTE_T), 1, dfp);
				rsize++;
			}

			fclose(dfp);

		}

		fclose(sfp);
		return BOOL_TRUE;
	}
	virtual ~FileJoin()
	{

	}
protected:

private:

	void Init()
	{

	}
	char * getFileNameInPath(char * path,INT32_T * index=NULL)
	{
		INT32_T i = 0;
		while (path[i] != 0)
		{
			i++;
		}
		i--;
		//匹配适应Windows/Linux平台
		while (i>0 && path[i] != '/' && path[i] != '\\' && path[i] != ':')
		{
			i--;
		}
		if (i!=0)
			i++;
		if (index != NULL)
			*index = i;
		return &path[i];
	}
	BOOL_T writeHeader(FILE * fp)
	{
		BYTE_T flgs[] = { 'F', 'J', 'S', 0 };
		fwrite(flgs, sizeof(BYTE_T), 3, fp);
		return BOOL_TRUE;
	}
	BOOL_T readHeader(FILE * fp)
	{
		BYTE_T flgs[] = { 'F', 'J', 'S', 0 };
		BYTE_T rflg[8] = { 0 };
		fread(rflg, sizeof(BYTE_T), 3, fp);
		INT32_T i = 0;
		while (flgs[i] != 0)
		{
			if (flgs[i] != rflg[i])
			{
				return BOOL_FALSE;
			}
			i++;
		}
		return BOOL_TRUE;
	}

};


#endif // _FILE_JOIN_H_