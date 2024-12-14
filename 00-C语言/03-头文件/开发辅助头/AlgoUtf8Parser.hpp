#ifndef _ALGO_UTF8_PARSER_HPP_
#define _ALGO_UTF8_PARSER_HPP_
/*  */
#include"AlgoTypes32.hpp"
#include<stdio.h>
/*
UTF8编码规则：
一个字节表示的，最高位为0，剩余7位是字面值，这也是兼容ASCII
多个字节表示的，首字节的最高n位为1，就标识一共用几个字节表示，其余字节最高位均为10开头
也就是如下所示，因此可以看出，最多有31位进行表示31=5*6+1,
【注意】：
	因此我们使用全部的UNICODE编码来建立我们的转换模型
	也就意味着我们的UNICODE字符将占用4字节，和大多数只是用2个字节表示的系统可能不会兼容（2-->4可以无条件变换 4-->2 可能出现部分错误）
	大部分场景下，使用2字节表示的UNICODE已经完全够用了，那么为什么会用到4字节呢？
	原因是，一些符号，表情，这类极少使用的符号，便不被编入大多数系统支持中，从而会产生部分乱码

1字节 0xxxxxxx
2字节 110xxxxx 10xxxxxx
3字节 1110xxxx 10xxxxxx 10xxxxxx
4字节 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
5字节 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
6字节 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

UNICODE编码规则：
简单说，就是在UTF编码的基础上，去掉规则前缀，剩下的连起来就是UNICODE值
例如：
UTF8:110+11011  10+001100
对应：
UNICODE：11011+001100 == 110 11001100

GB2312/GBK和UNICODE编码没有任何关系，因此只能直接查表映射，这个需要注意
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
		if ((*srcStr) < 0x80)//首字节为0，1字节表示
		{
			tpun = (0 | ((*srcStr) & 0x7f));

			byteCount = 1;
			
		}
		else if (((*srcStr) & 0xfc) == 0xfc)//首字节为111111，6字节表示
		{
			tpun = (0 | ((*srcStr) & 0x01));

			byteCount = 6;
		}
		else if (((*srcStr) & 0xf8) == 0xf8)//首字节为11111，5字节表示
		{
			tpun = (0 | ((*srcStr) & 0x03));

			byteCount = 5;
		}
		else if (((*srcStr) & 0xf0) == 0xf0)//首字节为1111，4字节表示
		{
			tpun = (0 | ((*srcStr) & 0x07));

			byteCount = 4;
		}
		else if (((*srcStr) & 0xe0) == 0xe0)//首字节为111，3字节表示
		{
			tpun = (0 | ((*srcStr) & 0x0f));

			byteCount = 3;
		}
		else if (((*srcStr) & 0xc0) == 0xc0)//首字节为11，2字节表示
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
		if (bitCount <= 7)//1字节表示，
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
			if (bitCount <= 11)//2字节表示：((2-1)*6)+(8-(2+1)),以后的都准从这个规律
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