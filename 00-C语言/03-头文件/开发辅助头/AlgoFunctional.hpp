#ifndef _ALGO_FUNCTIONAL_HPP_
#define _ALGO_FUNCTIONAL_HPP_
/********************************************
* ģ�飺ͨ�ú���ģ��
* author��Ugex.Savelar
*********************************************/
#include"AlgoInterface.hpp"
#include<stdlib.h>
template<typename T>
void AlgoSwapInteger(T * a, T * b)
{
	(*a) = (*a) ^ (*b);
	(*b) = (*a) ^ (*b);
	(*a) = (*a) ^ (*b);
}
template<typename T>
void AlgoSwap(T * a, T * b)
{
	T tp = *a;
	*a = *b;
	*b = tp;
}
template<typename T>
void AlgoSwapMemory(void * a, void * b, T size)
{
	unsigned char * sp = (unsigned char *)a;
	unsigned char * dp = (unsigned char *)b;
	for (T i = 0; i < size; i++)
	{
		sp[i] = sp[i] ^ dp[i];
		dp[i] = sp[i] ^ dp[i];
		sp[i] = sp[i] ^ dp[i];
	}
}
/*
ǿ��ָ��ת��
*/
template<typename T, typename E>
E * AlgoVaryPointer(T * data)
{
	return (E *)((void *)data);
}
/*
ǿ��ȡ���ݵ�Bitλ,
��Ҫ��֤���޷��������������ܱ�֤���ݵĿɿ�����
needKeep���ᱣ��ȡ���ݵ�λ�ã������Զ���С��0Bitλ
*/
template<typename T>
T AlgoGetBitData(T data, int beginBit, int endBit, bool needKeep)
{
	int db = endBit - beginBit + 1;
	T tp = 0;
	for (int i = 0; i < db; i++)
	{
		tp = (tp << 1) | 1;
	}
	tp = tp << beginBit;
	if (needKeep)
		return data&tp;
	return (data&tp) >> beginBit;
}
/*
�������ݵ�Bitλ��
isAligned��ʾ�����Ƿ��Ѿ����滻λ�ã����򽫻��ƶ���ָ��Bit����λ��ʹ��
*/
template<typename T>
T AlgoSetBitData(T data, int beginBit, int endBit, T setData, bool isAligned)
{
	T tpv = 0, tpf = 0;
	int bitCount = sizeof(T)* 8;
	for (int i = bitCount - 1; i >= 0; i--)
	{
		if (i >= beginBit && i <= endBit)
		{
			tpv = (tpv << 1) | 0;
			tpf = (tpf << 1) | 1;
		}
		else
		{
			tpv = (tpv << 1) | 1;
			tpf = (tpf << 1) | 0;
		}
	}
	T td = tpv&data;
	T sd = isAligned ? setData : (setData << beginBit);
	sd = sd&tpf;
	return td | sd;
}


template<typename D, typename T, typename E,typename FuncCmp,typename FuncSelGet>
E AlgoCount(D * data, T target, E startIndex, E endIndex, FuncCmp cmp,FuncSelGet selGet)
{
	E count = 0;
	for (; startIndex <= endIndex; startIndex++)
	{
		if (cmp(selGet(data, startIndex), target) == 0)
		{
			count++;
		}
	}
	return count;
}
template<typename D, typename T, typename E, typename FuncSelGet>
T AlgoSum(D * data, E startIndex, E endIndex, FuncSelGet selGet)
{
	T sum = 0;
	for (; startIndex <= endIndex; startIndex++)
	{
		sum += selGet(data, startIndex);
	}
	return sum;
}
template<typename D, typename T, typename E, typename R, typename FuncSelGet>
R AlgoAvg(D * data, E startIndex, E endIndex, FuncSelGet selGet, R factor)
{
	E count = 0;
	T sum = 0;
	for (; startIndex <= endIndex; startIndex++)
	{
		sum += selGet(data, startIndex);
		count++;
	}
	return sum*factor / count;
}
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet>
T AlgoMax(D * data, E startIndex, E endIndex, FuncCmp cmp, FuncSelGet selGet, E * retIndex)
{
	T max = selGet(data, startIndex);
	E maxIndex = startIndex;
	startIndex++;
	for (; startIndex <= endIndex; startIndex++)
	{
		T cur = selGet(data, startIndex);
		if (cmp(cur, max) > 0)
		{
			max = cur;
			maxIndex = startIndex;
		}
	}
	if (retIndex != NULL)
		*retIndex = maxIndex;
	return max;
}
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet>
T AlgoMin(D * data, E startIndex, E endIndex, FuncCmp cmp, FuncSelGet selGet, E * retIndex)
{
	T min = selGet(data, startIndex);
	E minIndex = startIndex;
	startIndex++;
	for (; startIndex <= endIndex; startIndex++)
	{
		T cur = selGet(data, startIndex);
		if (cmp(cur, min) < 0)
		{
			min = cur;
			minIndex = startIndex;
		}
	}
	if (retIndex != NULL)
		*retIndex = minIndex;
	return min;
}

template<typename T, typename FuncCmp>
bool AlgoIn(T target, int count, FuncCmp cmp, T data, ...)
{
	va_list varList;
	va_start(varList, data);
	//��Ҫע�⣬���ǵ�һ������data��λ�ã������һ�ε���va_arg�����Ѿ�ָ����һ��������
	//�������ͻᵼ�µ�һ������ȡ����
	//��˽�����������֣���һ�־��������ַ�������һ���������������ڶ��־���va_start�Ĳ���ȡ��ǰһ��cmp
	T arg = data;
	bool ret = false;
	int i = 0;
	while (i<count)
	{
		if (cmp(target, arg) == 0)
		{
			ret = true;
			break;
		}
		arg= va_arg(varList, T);
		i++;
	}
	va_end(varList);
	return ret;
}
/*
�ж�Ŀ���Ƿ���������
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet>
bool AlgoIsIn(T target, D * data, E count, FuncCmp cmp, FuncSelGet selGet)
{
	bool ret = false;
	for (E i = 0; i < count; i += 1)
	{
		if (cmp(target, selGet(data, i)) == 0){
			ret = true;
			break;
		}
	}
	return ret;
}

template<typename D, typename T, typename E, typename FuncExec, typename FuncSelGet,typename FuncOn>
void AlgoForeach(D * data, E count, FuncExec exec, FuncSelGet selGet,FuncOn onBegin,FuncOn onEnd)
{
	onBegin();
	AlgoForeach(data,count,exec,selGet);
	onEnd();
}
template<typename D, typename T, typename E,typename FuncExec,typename FuncSelGet>
void AlgoForeach(D * data, E count, FuncExec exec, FuncSelGet selGet)
{
	for (E i = 0; i < count; i += 1)
	{
		exec(selGet(data, i));
	}
}

/*
��ת����
*/
template<typename D, typename T, typename E, typename FuncSelSwap>
void AlgoReverse(D * data, E startIndex, E endIndex, FuncSelSwap selSwap)
{
	while (startIndex < endIndex)
	{
		selSwap(data,startIndex, endIndex);
		startIndex++;
		endIndex--;
	}
}


/*
��������
*/
template<typename D, typename T, typename E, typename FuncSelSwap>
void AlgoShuffle(D * data, E startIndex, E endIndex, FuncSelSwap selSwap)
{
	E count = endIndex - startIndex + 1;
	if (count>2)
		count = rand() % (count / 2) + (count / 2);
	E i = 0;
	while (i<count)
	{
		E bindex = rand() % count + startIndex;
		E eindex = rand() % count + startIndex;
		if (bindex != eindex)
			selSwap(data,bindex,eindex);
		i++;
	}
}
/*
ѡ������
�������ֳ������֣�ǰ�벿��������õģ���벿���������
����ǰ�벿��û�����ݣ���Ȼ����
Ȼ��ÿ�δӺ�벿����һ����С�ķŵ�ǰ�벿�ֵ����һ��λ�ã�
Ҳ����˵����벿�ֵĵ�һ�����ݺͺ�벿�ֵ���С���ݽ���
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet,typename FuncSelSwap>
void AlgoSortSelect(D * data, E size, FuncCmp cmp, FuncSelGet selGet,FuncSelSwap selSwap, bool asc)
{
	E minIndex = 0;
	for (E i = 0; i < size; i++)
	{
		minIndex = i; //����Ŀǰ��С���ݾ��Ǻ�벿�ֵĵ�һ��
		for (E j = i; j < size; j++)
		{
			if ((cmp(selGet(data, j), selGet(data, minIndex)) < 0) == asc)//ɨ���벿�֣��õ�������С������
			{
				minIndex = j;
			}
		}
		selSwap(data, minIndex, i);//������С�ͺ�벿�ֵ�һ������
	}
}
/*
ð������
ÿ�ζ��Ƚ����ڵ��������ݣ������С˳��һ���͵���
��ôһ��ɨ����ܽ�һ�����ݷŵ�����棨������������
����������ݲ���������ð�������Ѿ�ð�˵Ĳ��־��Ѿ������ˣ����Բ���ð�ˣ�
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSwap>
void AlgoSortBubble(D * data, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSwap selSwap, bool asc)
{
	if (size <= 1)
		return;
	for (E i = 0; i < size; i++)
	{
		//�ж��Ƿ����˽�����һ�������û�з����������Ǿ��Ѿ�������
		bool swap = false;
		for (E j = 0; j < size - 1 - i; j++)//ǰ��˵����һ�ξ��ܵõ�һ�����ģ����-i���ܱ��������õ����ţ����û��Ҫ
		{
			if ((cmp(selGet(data, j), selGet(data, j + 1))>0) == asc)//���ڵĴ�С������ͽ���
			{
				selSwap(data, j, j + 1);
				swap = true;
			}
		}
		if (swap == false)
		{
			break;
		}
	}
}

/*
��������
�ӵ�һ�����ݿ�ʼ�����ʱ�򣬵�һ�����ݼ�֮ǰ�����ݶ�������ģ��Ͼ���һ������
Ȼ��һ�δӺ�����һ�����ݣ����뵽ǰ����������ݶ�Ӧ��λ�ã���˻���Ƶ��ƶ����ݣ����뵼�µģ�
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void AlgoSortInsert(D * data, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSet selSet, bool asc)
{
	if (size <= 1)
		return;
	//����ѭ��һ��
	for (E i = 1; i < size; i++)
	{
		//ȥ����Ĳ��������ڵ�������ݸ÷��õ�λ��
		for (E j = 0; j < i; j++)
		{
			if ((cmp(selGet(data, i), selGet(data, j))<0) == asc)
			{
				//�ҵ�λ��֮�󣬰�ǰ�������Ų���һ��λ��
				T ti = selGet(data, i);
				for (E k = i; k >j; k--)
				{
					selSet(data, k, selGet(data, k - 1));
				}
				//�����ݲ���
				selSet(data, j, ti);
				break;
			}
		}
	}
}
/*
��������
ÿ�εݹ飬���Ͻ�����һ��Ϊ����ͬʱ�õ���λ�����ݵ�λ�ã����λ�ý������ٸı�
ֱ���ݹ�����Ϊ1Ϊֹ��Ҳ���ǿ�ʼ�±꡷=�����±�
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void AlgoSortQuick(D * data, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSet selSet, bool asc)
{
	AlgoSortQuick<D, T, E>(data, 0, size - 1, cmp, selGet,selSet, asc);
}
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void AlgoSortQuick(D * data, E headIndex, E endIndex, FuncCmp cmp, FuncSelGet selGet, FuncSelSet selSet, bool asc)
{
#if 0	//���ﲻʹ�õݹ飬���������������ջ���������ʹ�ö���+ѭ�����д��������Ҫʹ�õݹ鴦���뽫�����0��Ϊ��0ֵ
	//��ʼ�±�С�ڽ���С���û����
	if (headIndex < endIndex)
	{
		//��λһ�����ݵ�λ��
		E mid = _AlgoSortQuickNext(data, headIndex, endIndex, cmp, selGet,selSet, asc);
		//���ն�λ����λ�õ����˽��еݹ鶨λ
		if (AlgoIsBetweenBothAnd<E>(headIndex, mid - 1, endIndex))
			AlgoSortQuick(data, headIndex, mid - 1, cmp, selGet,selSet, asc);
		if (AlgoIsBetweenBothAnd<E>(headIndex, mid + 1, endIndex))
			AlgoSortQuick(data, mid + 1, endIndex, cmp, selGet,selSet, asc);
	}
	/*
	ʹ�õݹ�����1�������Ѿ�ջ���

	�ǵݹ�Ч��
	listSize:10000
	shuffle time:0
	shuffled
	:1103 533 2 3422 1912 955 141 2937 3821 63 3969 4046 4734 2446 2331 733 16 1269 4648 4237
	sort time:74
	sorted
	:0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
	reverse time:0
	reversed
	:9999 9998 9997 9996 9995 9994 9993 9992 9991 9990 9989 9988 9987 9986 9985 9984 9983 9982 9981 9980
	*/
#else
	AlgoList<E, int> lstQue;
	lstQue.push(headIndex);
	lstQue.push(endIndex);
	while (lstQue.size()>0)
	{
		E head, end;
		bool ret1 = lstQue.remove(0, &head);
		bool ret2 = lstQue.remove(0, &end);
		//��λһ�����ݵ�λ��
		E mid = _AlgoSortQuickNext<D,T,E>(data, head, end, cmp, selGet, selSet, asc);
		//���ն�λ����λ�õ����˽��еݹ鶨λ
		if (AlgoIsBetweenBothAnd<E>(head, mid - 1, end))
		{
			lstQue.push(head);
			lstQue.push(mid - 1);
		}
		if (AlgoIsBetweenBothAnd<E>(head, mid + 1, end))
		{
			lstQue.push(mid + 1);
			lstQue.push(end);
		}
	}
#endif
}
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
E _AlgoSortQuickNext(D * data, E head, E end, FuncCmp cmp, FuncSelGet selGet, FuncSelSet selSet, bool asc)
{
	E i = head, j = end;
	//���濪ʼ�±����ݣ���Ϊ�����ý����ķ�ʽ���ҵ�֮��͸�����һ�εĽŲ����������ڱ���ĸ������һ����ӡ���Ǿ�����������
	T phead = selGet(data, head);
	//�ֱ�������������򣬽����ں�С�ڿ�ʼ���ݵ����ݲ��Ϸ������ߣ�һ�ν���֮������λ�þ��ǿ�ʼλ�õ�����λ��
	//����һ��ѭ���������Ͱ����ݷ�Ϊ���ڵ�һ���С�ڵ�һ��
	do
	{
		//�����Ҵ��ڵģ���һ����
		while (i < j && (cmp(selGet(data, j), phead) >= 0) == asc)
			j--;
		if (i < j)
		{
			selSet(data, i, selGet(data, j));
			i++;
		}
		//������С�ڵ�
		while (i < j && (cmp(selGet(data, i), phead) <= 0) == asc)
			i++;
		if (i < j)
		{
			selSet(data, j, selGet(data, i));
			j--;
		}
	} while (i<j);
	selSet(data, j, phead);
	return i;
}
/*
��·�鲢����
�����ڵ��������򻮷�������кϲ���Ϊһ����������ֱ�����������С�ﵽ��������С
��ô������������һ��ʼΪ1ʱ��һ�������Ǿ��������
��ôһ�η��������С���й鲢����
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void AlgoSortMerge(D * data, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSet selSet, bool asc)
{
	//��ʼ����һ���ݹ鲢����������
	E len = 1;
	T * buf = (T *)malloc(sizeof(T)*(size));//��֤�ռ���2n��С�������������·�鲢����Ҫ��
	//size-1 �������ݣ������±���й鲢
	E maxIndex = size - 1;

	void * src = data;
	void * drt = buf;
	while (len < size)//ֱ��ÿ�εĹ鲢���ȴﵽ�ܳ���Ҳ�͹鲢���
	{
		//���ι鲢����һ�δ�Դ���ݵ����棬�ڶ��λ������
		for (E i = 0; i < 2; i++)
		{
			bool isSrcToBuf = false;
			if (i == 0)
			{
				src = data;
				drt = buf;
				isSrcToBuf = true;
			}
			else
			{
				src = buf;
				drt = data;
				isSrcToBuf = false;
			}
			//���ι鲢ÿ������������
			E j = 0;
			while (j + 2 * len < size)
			{
				if (isSrcToBuf)
					_AlgoMerge<D, T, E, T>((D *)src, j, j + len - 1, j + 2 * len - 1, selGet, (T *)drt, AlgoArraySelectSet<T,T,E>, cmp, asc);
				else
					_AlgoMerge<T, T, E, D>((T *)src, j, j + len - 1, j + 2 * len - 1, AlgoArraySelectGet<T, T, E>, (D *)drt, selSet, cmp, asc);
				j += 2 * len;
			}
			//�鲢ʣ��Ĳ��ȳ�����������
			if (j + len < size)
			{
				if (isSrcToBuf)	
					_AlgoMerge<D, T, E, T>((D *)src, j, j + len - 1, maxIndex, selGet, (T *)drt, AlgoArraySelectSet<T, T, E>, cmp, asc);
				else
					_AlgoMerge<T, T, E, D>((T *)src, j, j + len - 1, maxIndex, AlgoArraySelectGet<T, T, E>, (D *)drt, selSet, cmp, asc);
			}
			else
			{
				//����ʣ��ռ�
				while (j < size)
				{
					if (isSrcToBuf)
						AlgoArraySelectSet<D,T,E>((T *)drt, j, selGet((D *)src, j));
					else
						selSet((D *)drt, j, AlgoArraySelectGet<D, T, E>((T *)src, j));
					j++;
				}
			}

			len *= 2;
		}
	}
	free(buf);
}
//��start-mid��mid-end�����������ݺϲ�Ϊһ���������������
template<typename D, typename T, typename E, typename F, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void _AlgoMerge(D * srcData, E start, E mid, E end, FuncSelGet selGetSrc, F * drtData, FuncSelSet selSetDrt, FuncCmp cmp, bool asc)
{
	E i = start, j = mid + 1, k = start;
	//�������ݣ�ֱ�������κ�һ�ν���
	while (i <= mid && j <= end)
	{
		//�Ƚ����ݣ�˭С˭����
		if ((cmp(selGetSrc(srcData, i), selGetSrc(srcData, j)) < 0) == asc)
		{
			selSetDrt(drtData, k++, selGetSrc(srcData, i++));
		}
		else
		{
			selSetDrt(drtData, k++, selGetSrc(srcData, j++));
		}
	}
	//��ʣ�����һ�ε����ݸ��ƹ�ȥ
	while (i <= mid)
	{
		selSetDrt(drtData, k++, selGetSrc(srcData, i++));
	}
	while (j <= end)
	{
		selSetDrt(drtData, k++, selGetSrc(srcData, j++));
	}
}
/*
������
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSwap>
void AlgoSortHeap(D * data, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSwap selSwap, bool asc)
{
	for (E i = size / 2 - 1; i >= 0; i--)
	{
		_AlgoHeapAdjust<D,T,E>(data, i, size,cmp,selGet,selSwap,asc);
	}

	for (E i = size - 1; i > 0; i--)
	{
		selSwap(data, 0,i);
		_AlgoHeapAdjust<D, T, E>(data, 0, i, cmp, selGet, selSwap, asc);
	}
}
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSwap>
void _AlgoHeapAdjust(D * data, E pIndex, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSwap selSwap, bool asc)
{
	int j = 0;
	while (2 * pIndex + 1 < size)
	{
		j= 2 * pIndex + 1;
		if (j + 1 < size)
		{
			if ((cmp(selGet(data, j), selGet(data, j + 1)) < 0) == asc)
			{
				j++;
			}
		}
		if ((cmp(selGet(data, pIndex), selGet(data, j)) < 0) == asc)
		{
			selSwap(data, pIndex, j);
			pIndex = j;
		}
		else
			break;
	}
}
/*
˳�����
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet>
E AlgoSearchOrder(D * data, E size, T target, FuncCmp cmp, FuncSelGet selGet, bool order)
{
	E begin = 0, end = size, step = 1;
	if (order == false)
	{
		begin = size - 1;
		end = -1;
		step = -1;
	}
	for (; begin != end; begin += step)
	{
		if (cmp(selGet(data, begin), target) == 0)
		{
			return begin;
		}
	}
	return -1;
}

/*
���ֲ���
ÿ�ν����������һ�룬
����Ҫ�󱻲���������
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet>
E AlgoSearchHalf(D * data, E size, T target, FuncCmp cmp, FuncSelGet selGet)
{
	if (size <= 0)
		return -1;
	E low = 0, mid, height = size - 1;
	bool isUpSort = true;
	if (cmp(selGet(data, 0), selGet(data, height)) > 0)
	{
		isUpSort = false;
	}
	while (low < height)
	{
		mid = (low + height) / 2;
		//쳲��������ң���Ϊ0.5����Ϊ0.618������//mid=low+0.618*(height-low);
		//��ֵ���ң������������������͵Ĳ��ң�Ҳ���Ǹ��ݲ���ֵ�Ĵ��±������𽥱ƽ����в��ң������м�ֵλ��=���λ��+Ԥ��λ�ñ���*�ܳ���//mid=low+	((target-selGet(data,low))/(selGet(data,height)-selGet(data,low)))	*(height-low);
		T md = selGet(data, mid);
		if (cmp(md, target) == 0)
		{
			return mid;
		}
		if (cmp(md, target) < 0)
		{
			if (isUpSort)
				low = mid + 1;
			else
				height = mid;
		}
		else
		{
			if (isUpSort)
				height = mid;
			else
				low = mid + 1;
		}
	}
	return -1;
}
/*
쳲���������--�ƽ�ָ����
ÿ�ν����������һ�룬
����Ҫ�󱻲���������
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet>
E AlgoSearchFibonacci(D * data, E size, T target, FuncCmp cmp, FuncSelGet selGet)
{
	if (size <= 0)
		return -1;
	E low = 0, mid, height = size - 1;
	bool isUpSort = true;
	if (cmp(selGet(data, 0), selGet(data, height)) > 0)
	{
		isUpSort = false;
	}
	bool isNag = false;
	while (low < height)
	{
		double rate = 0.61826;
		if (isNag)
		{
			rate = 1.0 - rate;
		}
		isNag = !isNag;

		mid = low + rate*(height - low);
		//쳲��������ң��ֳ�Ϊ�ƽ�ָ���ң���Ϊ0.5����Ϊ0.618������//mid=low+0.618*(height-low);
		T md = selGet(data, mid);
		if (cmp(md, target) == 0)
		{
			return mid;
		}
		if (cmp(md, target) < 0)
		{
			if (isUpSort)
				low = mid + 1;
			else
				height = mid;
		}
		else
		{
			if (isUpSort)
				height = mid;
			else
				low = mid + 1;
		}
	}
	return -1;
}
/*
��ֵ����
����������Ԫ��֧�����㣺�������������Ը��������õ�������
��ô�Ϳ���ʹ�ñ������㷨

����Ͳ�����

���㷨���C�����еĻ����������;���Ч��int short byte long double float ...
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet>
E AlgoSearchInsert(D * data, E size, T target, FuncCmp cmp, FuncSelGet selGet)
{
	if (size <= 0)
		return -1;

	E low = 0, mid, height = size - 1;
	bool isUpSort = true;
	if (cmp(selGet(data, 0), selGet(data, height)) > 0)
	{
		isUpSort = false;
	}
	while (low < height)
	{
		double rate = ((target*1.0 - selGet(data, low)) / (selGet(data, height) - selGet(data, low)));
		if (rate<0.0 || rate>1.0)
			return -1;
		mid = low + 	rate*(height*1.0 - low);
		//��ֵ���ң������������������͵Ĳ��ң�Ҳ���Ǹ��ݲ���ֵ�Ĵ��±������𽥱ƽ����в��ң������м�ֵλ��=���λ��+Ԥ��λ�ñ���*�ܳ���
		T md = selGet(data, mid);
		if (cmp(md, target) == 0)
		{
			return mid;
		}
		if (cmp(md, target) < 0)
		{
			if (isUpSort)
				low = mid + 1;
			else
				height = mid;
		}
		else
		{
			if (isUpSort)
				height = mid;
			else
				low = mid + 1;
		}
	}
	return -1;
}
#endif // _ALGO_FUNCTIONAL_HPP_