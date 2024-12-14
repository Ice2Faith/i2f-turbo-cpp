#ifndef _ALGO_UTF8_PARSER_HPP_
#define _ALGO_UTF8_PARSER_HPP_
/*  */
#include"AlgoTypes32.hpp"
#include<stdio.h>
/*
UTF8�������
һ���ֽڱ�ʾ�ģ����λΪ0��ʣ��7λ������ֵ����Ҳ�Ǽ���ASCII
����ֽڱ�ʾ�ģ����ֽڵ����nλΪ1���ͱ�ʶһ���ü����ֽڱ�ʾ�������ֽ����λ��Ϊ10��ͷ
Ҳ����������ʾ����˿��Կ����������31λ���б�ʾ31=5*6+1,
��ע�⡿��
	�������ʹ��ȫ����UNICODE�������������ǵ�ת��ģ��
	Ҳ����ζ�����ǵ�UNICODE�ַ���ռ��4�ֽڣ��ʹ����ֻ����2���ֽڱ�ʾ��ϵͳ���ܲ�����ݣ�2-->4�����������任 4-->2 ���ܳ��ֲ��ִ���
	�󲿷ֳ����£�ʹ��2�ֽڱ�ʾ��UNICODE�Ѿ���ȫ�����ˣ���ôΪʲô���õ�4�ֽ��أ�
	ԭ���ǣ�һЩ���ţ����飬���༫��ʹ�õķ��ţ��㲻����������ϵͳ֧���У��Ӷ��������������

1�ֽ� 0xxxxxxx
2�ֽ� 110xxxxx 10xxxxxx
3�ֽ� 1110xxxx 10xxxxxx 10xxxxxx
4�ֽ� 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
5�ֽ� 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
6�ֽ� 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

UNICODE�������
��˵��������UTF����Ļ����ϣ�ȥ������ǰ׺��ʣ�µ�����������UNICODEֵ
���磺
UTF8:110+11011  10+001100
��Ӧ��
UNICODE��11011+001100 == 110 11001100

GB2312/GBK��UNICODE����û���κι�ϵ�����ֻ��ֱ�Ӳ��ӳ�䣬�����Ҫע��
*/
//8421 8421
//A10 B11 C12 D13 E14 F15
INT32_T AlgoUtf8ToUnicode32(UINT8_T * u8str,UINT32_T * un32str)
{
	INT32_T retSize = 0;
	UINT8_T * srcStr = u8str;
	UINT32_T tpun = 0;
	while ((*srcStr) != 0)
	{
		INT32_T byteCount = 0;
		UINT8_T pch = (*srcStr);
		if ((*srcStr) < 0x80)//���ֽ�Ϊ0��1�ֽڱ�ʾ
		{
			tpun = (0 | ((*srcStr) & 0x7f));

			byteCount = 1;
			
		}
		else if (((*srcStr) & 0xfc) == 0xfc)//���ֽ�Ϊ111111��6�ֽڱ�ʾ
		{
			tpun = (0 | ((*srcStr) & 0x01));

			byteCount = 6;
		}
		else if (((*srcStr) & 0xf8) == 0xf8)//���ֽ�Ϊ11111��5�ֽڱ�ʾ
		{
			tpun = (0 | ((*srcStr) & 0x03));

			byteCount = 5;
		}
		else if (((*srcStr) & 0xf0) == 0xf0)//���ֽ�Ϊ1111��4�ֽڱ�ʾ
		{
			tpun = (0 | ((*srcStr) & 0x07));

			byteCount = 4;
		}
		else if (((*srcStr) & 0xe0) == 0xe0)//���ֽ�Ϊ111��3�ֽڱ�ʾ
		{
			tpun = (0 | ((*srcStr) & 0x0f));

			byteCount = 3;
		}
		else if (((*srcStr) & 0xc0) == 0xc0)//���ֽ�Ϊ11��2�ֽڱ�ʾ
		{
			tpun = (0 | ((*srcStr) & 0x1f));

			byteCount = 2;

		}


		srcStr++;

		for (INT32_T i = 1; i < byteCount; i++)
		{
			if ((*srcStr) == 0)
			{
				return -1;
			}
			tpun = (tpun << 6) | ((*srcStr) & 0x3f);

			srcStr++;
		}

		if (un32str != NULL)
		{
			AlgoBigEndian2Host(&tpun, sizeof(UINT32_T));
			*(un32str + retSize) = tpun;
		}
		retSize++;
	}
	if (un32str != NULL)
	{
		*(un32str + retSize) = 0;
	}
	return retSize;
}

INT32_T AlgoUnicode32ToUtf8(UINT32_T * un32str, UINT8_T * u8str)
{
	INT32_T retSize = 0;
	UINT32_T * srcStr = un32str;
	while ((*srcStr) != 0)
	{
		UINT32_T ch = (*srcStr);
		AlgoHost2BigEndian(&ch, sizeof(UINT32_T));

		UINT32_T tpmask = 0x80000000;
		INT32_T spaceCount = 0;
		while (1)
		{
			if ((tpmask&ch)!=0)
				break;
			spaceCount++;
			tpmask = (tpmask >> 1) ;
		}

		INT32_T bitCount = 32 - spaceCount;
		if (bitCount <= 7)//1�ֽڱ�ʾ��
		{
			if (u8str!=NULL)
				*(u8str + retSize) = (UINT8_T)(ch&0x7f);
			retSize++;
		}
		else
		{
			INT32_T leftCount = bitCount % 6;
			INT32_T byteCount = bitCount / 6;
			UINT32_T leftMask = 0;
			for (INT32_T i = 0; i < leftCount; i++)
			{
				leftMask = (leftMask << 1) | 1;
			}

			UINT8_T curCh = 0;
			if (bitCount <= 11)//2�ֽڱ�ʾ��((2-1)*6)+(8-(2+1)),�Ժ�Ķ�׼���������
			{
				curCh = (UINT8_T)(0xc0 | (((leftMask << (6 * 1))&ch) >> (6 * 1)));

			}
			else if (bitCount <= 16)
			{
				curCh = (UINT8_T)(0xe0 | (((leftMask << (6 * 2))&ch) >> (6 * 2)));

			}
			else if (bitCount <= 21)
			{
				curCh = (UINT8_T)(0xf0 | (((leftMask << (6 * 3))&ch) >> (6 * 3)));
			}
			else if (bitCount <= 26)
			{
				curCh = (UINT8_T)(0xf8 | (((leftMask << (6 * 4))&ch) >> (6 * 4)));

			}
			else if (bitCount <= 31)
			{
				curCh = (UINT8_T)(0xfc | (((leftMask << (6 * 5))&ch) >> (6 * 5)));

			}

			if (u8str != NULL)
			{
				*(u8str + retSize + 0) = curCh;
			}

			retSize++;

			if(u8str != NULL)
			{
				for (INT32_T i = 0; i < byteCount; i++)
				{
					*(u8str + retSize + (byteCount - 1 - i)) = (UINT8_T)(0x80 | ((0x3f << (i * 6))&ch) >> (i * 6));
				}
			}
			

			retSize += byteCount;

		}
		
		srcStr++;
	}

	if (u8str != NULL)
	{
		*(u8str + retSize) = 0;
	}
	return retSize;
}

#endif // _ALGO_UTF8_PARSER_HPP_