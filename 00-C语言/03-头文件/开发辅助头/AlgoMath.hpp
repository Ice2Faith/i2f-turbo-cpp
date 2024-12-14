#ifndef _ALGO_MATH_HPP_
#define _ALGO_MATH_HPP_
/********************************************
* ģ�飺ͨ����ѧ����ģ��
* author��Ugex.Savelar
*********************************************/

/*
�ж�Ŀ���������ȷ���������ڣ��������ұ߽�
������
*/
template<typename T>
bool AlgoIsBetweenBothAnd(T left, T target, T right)
{
	return (target) >= (left) && (target) <= (right);
}
/*
��������ҿ�����
���ǵ���������ֻ�Ƚ϶�
*/
template<typename T>
bool AlgoIsBetweenUtil(T left, T target, T right)
{
	return (target) >= (left) && (target) < (right);
}

template<typename T>
bool AlgoNotBetween(T left, T target, T right)
{
	return target<left || target>right;
}
/*
��ԭʼ����ȡģ��ָ�������ڣ�������������
*/
template<typename T>
T AlgoModBetweenBothAnd(T src, T left, T right)
{
	return src % (right - left + 1) + left;
}
template<typename T,typename E>
T AlgoAdd(E count,T begin, ...)
{
	va_list list;
	va_start(list, count);
	T ret = 0;
	E i = 0;
	while (i < count)
	{
		ret += va_arg(list, T);
		i++;
	}
	va_end(list);
	return ret;
}
template<typename T, typename E>
T AlgoMul(E count, T begin, ...)
{
	va_list list;
	va_start(list, count);
	T ret = 1;
	E i = 0;
	while (i < count)
	{
		ret *= va_arg(list, T);
		i++;
	}
	va_end(list);
	return ret;
}
template<typename T, typename E,typename FuncCmp>
bool AlgoGatherAll(T target, FuncCmp cmp, E count, T begin, ...)
{
	va_list list;
	va_start(list, count);
	E i = 0;
	while (i < count)
	{
		T arg= va_arg(list, T);
		if (cmp(target, arg) <= 0)
			return false;

		i++;
	}
	va_end(list);
	return true;
}
template<typename T, typename E, typename FuncCmp>
bool AlgoLessAll(T target, FuncCmp cmp, E count, T begin, ...)
{
	va_list list;
	va_start(list, count);
	E i = 0;
	while (i < count)
	{
		T arg = va_arg(list, T);
		if (cmp(target, arg) >= 0)
			return false;

		i++;
	}
	va_end(list);
	return true;
}

#endif // _ALGO_MATH_HPP_