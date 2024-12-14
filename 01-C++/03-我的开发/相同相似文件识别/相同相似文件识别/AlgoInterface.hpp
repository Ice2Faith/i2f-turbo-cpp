#ifndef _ALGO_INTERFACE_HPP_
#define _ALGO_INTERFACE_HPP_
/********************************************
* ģ�飺ͨ�ýӿ�ģ���һЩĬ�Ͻӿ�ʵ��
* author��Ugex.Savelar
*********************************************/
//#include"AlgoFunctional.hpp"

#include<Windows.h>
/*
������Ҫ���һ�»�������,��Щ�������������ں���Ĵ���ģ�庯����ʹ��
�����ЩĬ�Ϻ������������Ϊ����ģ��Ĳο�ʹ�ã�ʵ�����Լ���ʵ�ֺ���
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FuncCmp �ȽϺ���
#define ALGO_FUNC_CMP(type) int (*)(const type &,const type &)
template<typename T>
int AlgoDefaultCmpFunc(const T & t1, const T & t2)
{
	if (t1 == t2)
		return 0;
	if (t1 > t2)
		return 1;
	if (t1 < t2)
		return -1;
}
int AlgoCharStringCmpFunc(const char * str1, const char * str2)
{
	if (str1 == str2)
		return 0;
	if (str1 == NULL && str2)
		return -1;
	if (str1 && str2 == NULL)
		return 1;
	return strcmp(str1,str2);
}
int AlgoTcharStringCmpFunc(const TCHAR * str1, const TCHAR * str2)
{
	if (str1 == str2)
		return 0;
	if (str1 == NULL && str2)
		return -1;
	if (str1 && str2 == NULL)
		return 1;
	return lstrcmp(str1, str2);
}
//α����
template<typename T>
class AlgoDefaultComparator
{
public:
	int operator()(const T & t1, const T & t2)
	{
		if (t1 == t2)
			return 0;
		if (t1 > t2)
			return 1;
		if (t1 < t2)
			return -1;
	}
};
/*
����Ƚϵ�ֵ���ᱻȡ��ַ���бȽϣ�ע�����
*/
template<typename T,typename E>
class AlgoDefaultMemoryComparator
{
private:
	E size;
public:
	AlgoDefaultMemoryComparator(E size)
	{
		this->size = size;
	}
	int operator()(const T & t1, const T & t2)
	{
		unsigned char * pstr1 = (unsigned char *)(void *)&t1;
		unsigned char * pstr2 = (unsigned char *)(void *)&t2;
		for (E i = 0; i < size; i++)
		{
			if (pstr1[i]>pstr2[i])
				return 1;
			if (pstr1[i] < pstr2[i])
				return -1;
		}
		return 0;
	}
};
/*
����Ƚϵ�ֵ����Ҫ��ָ�����ͣ������ָ��ƫ�Ʋ���
*/
template<typename T>
class AlgoDefaultStringComparator
{
public:
	int operator()(const T & t1, const T & t2)
	{
		if (str1 == str2)
			return 0;
		if (str1 == NULL && str2)
			return -1;
		if (str1 && str2 == NULL)
			return 1;

		int i = 0;
		while (t1[i] != 0 && t2[i]!=0)
		{
			if (t1[i]>t2[i])
				return 1;
			if (t1[i] < t2[i])
				return -1;
		}
		if (t1[i] == 0 && t2[i] == 0)
			return 0;
		if (t1[i] != 0)
			return 1;
		else
			return -1;
	}
};
//FuncSelGet Ԫ�ػ�ȡ����
#define ALGO_FUNC_SEL_GET(containertype,datatype,indextype) datatype & (*)(containertype *,indextype)
template<typename D, typename T, typename E>
T & AlgoArraySelectGet(D * data, E index)
{
	return data[index];
}
//FuncSelSet Ԫ�����ú���
#define ALGO_FUNC_SEL_SET(containertype,datatype,indextype) void (*) (containertype *,indextype,const datatype &)
template<typename D, typename T, typename E>
void AlgoArraySelectSet(D * data, E index, const T & target)
{
	data[index] = target;
}
//FuncSelSwap Ԫ�ؽ�������
#define ALGO_FUNC_SEL_SWAP(containertype,datatype,indextype) void (*) (containertype *,indextype,indextype)
template<typename D, typename T, typename E>
void AlgoArraySelectSwap(D * data, E indexA, E indexB)
{
	T tp = data[indexA];
	data[indexA] = data[indexB];
	data[indexB] = tp;
}
//FuncExec ִ�к���
#define ALGO_FUNC_EXEC(datatype) void(*)(datatype &)
template<typename T>
void AlgoExecFunc(T & t)
{
}
//FuncOn ������
#define ALGO_FUNC_ON void(*)()
void AlgoOnFunc()
{
}

//FuncRange ��������
#define ALGO_FUNC_RANGE(datatype,indextype) void(*)(datatype &,indextype,bool,bool)
template<typename T,typename E>
void AlgoRangeFunc(T & elem, E index, bool isFirst, bool isEnd)
{

}

//FuncFilter ���˺���
#define ALGO_FUNC_FILTER(type) bool(*)(const type &)
template<typename T>
bool AlgoDefaultFilterFunc(const T & elem)
{
	return true;
}
#endif // _ALGO_INTERFACE_HPP_