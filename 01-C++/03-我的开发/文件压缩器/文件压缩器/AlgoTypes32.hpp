#ifndef __ALGO_TYPES_32_HPP_
#define __ALGO_TYPES_32_HPP_
//base type bit len not equals on int and long,else is equals
#define ALGO_BIT_WIN32

#if defined ALGO_BIT_WIN32
typedef		char				CHAR_T;
typedef		unsigned char		UCHAR_T;
typedef		UCHAR_T				BYTE_T;
typedef		char				INT8_T;
typedef		unsigned char		UINT8_T;
typedef		short				INT16_T;
typedef		unsigned short		UINT16_T;
typedef		int					INT32_T;//long
typedef		unsigned int		UINT32_T;//unsigned int
typedef		long long			INT64_T;
typedef		unsigned long long	UINT64_T;

typedef		INT32_T				INT_T;

typedef		float				FLOAT32_T;
typedef		double				FLOAT64_T;

typedef		char				BOOL_T;
#define		BOOL_TRUE			1
#define		BOOL_FALSE			0
#endif // ALGO_BIT_WIN32

#if defined ALGO_BIT_WIN64
typedef		char				CHAR_T;
typedef		unsigned char		UCHAR_T;
typedef		UCHAR_T				BYTE_T;
typedef		char				INT8_T;
typedef		unsigned char		UINT8_T;
typedef		short				INT16_T;
typedef		unsigned short		UINT16_T;
typedef		int					INT32_T;
typedef		unsigned int		UINT32_T;
typedef		long				INT64_T;
typedef		unsigned long		UINT64_T;

typedef		INT32_T				INT_T;

typedef		float				FLOAT32_T;
typedef		double				FLOAT64_T;

typedef		char				BOOL_T;
#define		BOOL_TRUE			1
#define		BOOL_FALSE			0
#endif // ALGO_BIT_WIN64

#if defined ALGO_BIT_AS64_JNI
typedef		char				CHAR_T;
typedef		unsigned char		UCHAR_T;
typedef		UCHAR_T				BYTE_T;
typedef 	int8_t				INT8_T;
typedef 	uint8_t				UINT8_T;
typedef		int16_t				INT16_T;
typedef		uint16_t			UINT16_T;
typedef		int32_t				INT32_T;
typedef		uint32_t			UINT32_T;
typedef		int64_t				INT64_T;
typedef		uint64_t			UINT64_T;

typedef		INT32_T				INT_T;

typedef		float				FLOAT32_T;
typedef		double				FLOAT64_T;

typedef		char				BOOL_T;
#define		BOOL_TRUE			1
#define		BOOL_FALSE			0
#endif // ALGO_BIT_AS64_JNI

#define ALGO_TOBOOL(a) (((a))==0?BOOL_FALSE:BOOL_TRUE)

UINT8_T AlgoHostIsBigEndian()
{
	static UINT8_T hadCmp = 0;
	static UINT8_T isBig = 0;
	if (hadCmp == 0)
	{
		hadCmp = 1;

		UINT32_T pnum = 0x01020304;
		UINT8_T low = pnum & 0x0ff;
		UINT8_T * cpnum = (UINT8_T*)(void *)&pnum;
		INT32_T nsize = sizeof(UINT32_T);
		if (cpnum[nsize - 1] == low)
		{
			isBig = 1;
		}
		else
		{
			isBig = 0;
		}
	}
	return isBig;
}
UINT8_T AlgoHostIsLittleEndian()
{
	static UINT8_T hadCmp = 0;
	static UINT8_T isLittle = 0;
	if (hadCmp == 0)
	{
		hadCmp = 1;

		UINT32_T pnum = 0x01020304;
		UINT8_T low = pnum & 0x0ff;
		UINT8_T * cpnum = (UINT8_T*)(void *)&pnum;
		INT32_T nsize = sizeof(UINT32_T);
		if (cpnum[0] == low)
		{
			isLittle = 1;
		}
		else
		{
			isLittle = 0;
		}
	}
	return isLittle;
}
void * AlgoSwapEndianSort(void * val, INT32_T size)
{
	UINT8_T * cpval = (UINT8_T *)val;
	for (INT32_T i = 0; i < size / 2; i++)
	{
		/*UINT8_T tmp = cpval[i];
		cpval[i] = cpval[size - 1 - i];
		cpval[size - 1 - i] = tmp;*/

		//equals code method
		cpval[i] = cpval[i]^cpval[size - 1 - i];
		cpval[size - 1 - i] = cpval[i] ^ cpval[size - 1 - i];
		cpval[i] = cpval[i] ^ cpval[size - 1 - i];
	}

	return val;
}
void * AlgoHost2BigEndian(void * val, INT32_T size)
{
	if (AlgoHostIsBigEndian())
		return val;

	return AlgoSwapEndianSort(val, size);
}

void * AlgoHost2LittleEndian(void * val, INT32_T size)
{
	if (AlgoHostIsLittleEndian())
		return val;

	return AlgoSwapEndianSort(val, size);
}


void * AlgoBigEndian2Host(void * val, INT32_T size)
{
	if (AlgoHostIsBigEndian())
		return val;
	return AlgoSwapEndianSort(val, size);
}
void * AlgoLittleEndian2Host(void * val, INT32_T size)
{
	if (AlgoHostIsLittleEndian())
		return val;
	return AlgoSwapEndianSort(val, size);
}
#endif // __ALGO_TYPES_32_HPP_