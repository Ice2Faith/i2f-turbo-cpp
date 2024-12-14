#ifndef _SIMPLE_ZIP_H_
#define _SIMPLE_ZIP_H_
/*  */
#include<stdio.h>
#include"AlgoTypes32.hpp"
#include<stdlib.h>
/*
�������ַ������������ظ��ȸߵ��ļ�����ѹ�������磺
�ļ����ݣ�aaaabbbb
��ô���ᱻѹ��Ϊ��5a4b
�����������ļ������ǣ�abab
��ô�Ͳ���ѹ���ˣ����������ˣ�1a1b1a1b
���ԣ�����ѹ����ʽ�Ǿ�������Ե�
*/
class SimpleZip //: public Object
{
public:
	SimpleZip()
	{
		Init();
	}
	BOOL_T ZipFile(char * srcName, char * drtName)
	{
		FILE * sfp = NULL, *dfp = NULL;
		sfp = fopen(srcName, "rb");
		if (sfp == NULL)
		{
			return BOOL_FALSE;
		}
		dfp = fopen(drtName, "wb");
		if (dfp == NULL)
		{
			fclose(sfp);
			return BOOL_FALSE;
		}
		writeHeader(dfp);

		BYTE_T curch = 0, lastch = 0;
		BYTE_T count = 0;
		while (!feof(sfp))            /*8λ�޷����ַ�λ��0-255֮��*/
		{
			fread(&curch, sizeof(BYTE_T), 1, sfp);    /*��ȡ��Ӧ�ַ���������Ƶ��*/
			if (feof(sfp))
				break;
			if (count == 0)
			{
				lastch = curch;
			}
			if (curch == lastch)
			{
				count++;
				if (count == 255)
				{
					fwrite(&count, sizeof(BYTE_T), 1, dfp);
					fwrite(&curch, sizeof(BYTE_T), 1, dfp);
				}
			}
			else
			{
				fwrite(&count, sizeof(BYTE_T), 1, dfp);
				fwrite(&lastch, sizeof(BYTE_T), 1, dfp);
				count = 1;
				lastch = curch;
			}
		}
		fwrite(&count, sizeof(BYTE_T), 1, dfp);
		fwrite(&curch, sizeof(BYTE_T), 1, dfp);

		fclose(sfp);
		fclose(dfp);
		return BOOL_TRUE;
	}
	BOOL_T UnzipFile(char * srcName, char * drtName)
	{
		FILE * sfp = NULL, *dfp = NULL;
		sfp = fopen(srcName, "rb");
		if (sfp == NULL)
		{
			return BOOL_FALSE;
		}
		dfp = fopen(drtName, "wb");
		if (dfp == NULL)
		{
			fclose(sfp);
			return BOOL_FALSE;
		}
		if (readHeader(sfp) == BOOL_FALSE)
		{
			fclose(sfp);
			fclose(dfp);
			return BOOL_FALSE;
		}

		BYTE_T curch = 0;
		BYTE_T count = 0;
		while (!feof(sfp))            /*8λ�޷����ַ�λ��0-255֮��*/
		{
			fread(&count, sizeof(BYTE_T), 1, sfp);
			fread(&curch, sizeof(BYTE_T), 1, sfp);    /*��ȡ��Ӧ�ַ���������Ƶ��*/
			if (feof(sfp))
				break;
			for (BYTE_T i = 0; i < count; i++)
			{
				fwrite(&curch, sizeof(BYTE_T), 1, dfp);
			}
		}

		fclose(sfp);
		fclose(dfp);
		return BOOL_TRUE;
	}
	virtual ~SimpleZip()
	{

	}
protected:

private:

	void Init()
	{

	}
	BOOL_T writeHeader(FILE * fp)
	{
		BYTE_T flgs[] = { 'S', 'Z', 'P', 0 };
		fwrite(flgs, sizeof(BYTE_T), 3, fp);
		return BOOL_TRUE;
	}
	BOOL_T readHeader(FILE * fp)
	{
		BYTE_T flgs[] = { 'S', 'Z', 'P', 0 };
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


#endif // _SIMPLE_ZIP_H_
