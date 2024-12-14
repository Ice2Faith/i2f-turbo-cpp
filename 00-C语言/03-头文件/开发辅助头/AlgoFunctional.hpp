#ifndef _ALGO_FUNCTIONAL_HPP_
#define _ALGO_FUNCTIONAL_HPP_
/********************************************
* 模块：通用函数模块
* author：Ugex.Savelar
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
强制指针转换
*/
template<typename T, typename E>
E * AlgoVaryPointer(T * data)
{
	return (E *)((void *)data);
}
/*
强制取数据的Bit位,
需要保证是无符号数传进来才能保证数据的可靠返回
needKeep将会保留取数据的位置，不会自动归小到0Bit位
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
设置数据的Bit位，
isAligned表示数据是否已经在替换位置，否则将会移动到指定Bit后再位置使用
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
	//需要注意，这是第一个参数data的位置，后面第一次调用va_arg，就已经指向下一个参数了
	//处理不当就会导致第一个参数取不到
	//因此解决方法有两种，第一种就是我这种方案，第一个参数独立处理，第二种就是va_start的参数取向前一个cmp
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
判断目标是否在容器中
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
翻转容器
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
打乱容器
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
选择排序
把整个分成两部分，前半部分是排序好的，后半部分是乱序的
首先前半部分没有数据，当然有序
然后每次从后半部分找一个最小的放到前半部分的最后一个位置，
也就是说，后半部分的第一个数据和后半部分的最小数据交换
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet,typename FuncSelSwap>
void AlgoSortSelect(D * data, E size, FuncCmp cmp, FuncSelGet selGet,FuncSelSwap selSwap, bool asc)
{
	E minIndex = 0;
	for (E i = 0; i < size; i++)
	{
		minIndex = i; //假设目前最小数据就是后半部分的第一个
		for (E j = i; j < size; j++)
		{
			if ((cmp(selGet(data, j), selGet(data, minIndex)) < 0) == asc)//扫描后半部分，得到真正最小的数据
			{
				minIndex = j;
			}
		}
		selSwap(data, minIndex, i);//交换最小和后半部分第一个数据
	}
}
/*
冒泡排序
每次都比较相邻的两个数据，如果大小顺序不一样就调换
那么一次扫描就能将一个数据放到最后面（假设升序排序）
这样大的数据不断往后面冒，后面已经冒了的部分就已经有序了（可以不用冒了）
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSwap>
void AlgoSortBubble(D * data, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSwap selSwap, bool asc)
{
	if (size <= 1)
		return;
	for (E i = 0; i < size; i++)
	{
		//判断是否发生了交换，一遍结束，没有发生交换，那就已经有序了
		bool swap = false;
		for (E j = 0; j < size - 1 - i; j++)//前面说过，一次就能得到一个最大的，因此-i就能避免把排序好的再排，这个没必要
		{
			if ((cmp(selGet(data, j), selGet(data, j + 1))>0) == asc)//相邻的大小不满足就交换
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
插入排序
从第一个数据开始，这个时候，第一个数据及之前的数据都是有序的，毕竟就一个数据
然后，一次从后面拿一个数据，插入到前面有序的数据对应的位置，因此会设计到移动数据（插入导致的）
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void AlgoSortInsert(D * data, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSet selSet, bool asc)
{
	if (size <= 1)
		return;
	//总体循环一遍
	for (E i = 1; i < size; i++)
	{
		//去有序的部分找现在的这个数据该放置的位置
		for (E j = 0; j < i; j++)
		{
			if ((cmp(selGet(data, i), selGet(data, j))<0) == asc)
			{
				//找到位置之后，把前面的数据挪向后一个位置
				T ti = selGet(data, i);
				for (E k = i; k >j; k--)
				{
					selSet(data, k, selGet(data, k - 1));
				}
				//将数据插入
				selSet(data, j, ti);
				break;
			}
		}
	}
}
/*
快速排序
每次递归，不断将区间一分为二，同时得到定位的数据的位置，这个位置将不会再改变
直到递归区间为1为止，也就是开始下标》=结束下标
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void AlgoSortQuick(D * data, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSet selSet, bool asc)
{
	AlgoSortQuick<D, T, E>(data, 0, size - 1, cmp, selGet,selSet, asc);
}
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void AlgoSortQuick(D * data, E headIndex, E endIndex, FuncCmp cmp, FuncSelGet selGet, FuncSelSet selSet, bool asc)
{
#if 0	//这里不使用递归，否则数据量过多会栈溢出，这里使用队列+循环进行处理，如果需要使用递归处理，请将这里的0改为非0值
	//开始下标小于结束小标就没结束
	if (headIndex < endIndex)
	{
		//定位一个数据的位置
		E mid = _AlgoSortQuickNext(data, headIndex, endIndex, cmp, selGet,selSet, asc);
		//按照定位数据位置的两端进行递归定位
		if (AlgoIsBetweenBothAnd<E>(headIndex, mid - 1, endIndex))
			AlgoSortQuick(data, headIndex, mid - 1, cmp, selGet,selSet, asc);
		if (AlgoIsBetweenBothAnd<E>(headIndex, mid + 1, endIndex))
			AlgoSortQuick(data, mid + 1, endIndex, cmp, selGet,selSet, asc);
	}
	/*
	使用递归排序1万数据已经栈溢出

	非递归效率
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
		//定位一个数据的位置
		E mid = _AlgoSortQuickNext<D,T,E>(data, head, end, cmp, selGet, selSet, asc);
		//按照定位数据位置的两端进行递归定位
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
	//保存开始下标数据，因为不采用交换的方式，找到之后就覆盖上一次的脚步，最后把现在保存的覆盖最后一个脚印，那就是完整数据
	T phead = selGet(data, head);
	//分别从左右两个方向，将大于和小于开始数据的数据不断放置两边，一次结束之后，最后的位置就是开始位置的真正位置
	//这样一次循环结束，就把数据分为大于的一半和小于的一半
	do
	{
		//向左找大于的（第一个）
		while (i < j && (cmp(selGet(data, j), phead) >= 0) == asc)
			j--;
		if (i < j)
		{
			selSet(data, i, selGet(data, j));
			i++;
		}
		//向右找小于的
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
二路归并排序
把相邻的两个有序划分区域进行合并成为一个有序区域，直到划分区域大小达到最大排序大小
那么，当划分区域一开始为1时，一个数据是绝对有序的
那么一次翻倍区间大小进行归并即可
*/
template<typename D, typename T, typename E, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void AlgoSortMerge(D * data, E size, FuncCmp cmp, FuncSelGet selGet, FuncSelSet selSet, bool asc)
{
	//初始化单一数据归并，绝对有序
	E len = 1;
	T * buf = (T *)malloc(sizeof(T)*(size));//保证空间是2n大小，这样才满足二路归并基本要求
	//size-1 对齐数据，采用下标进行归并
	E maxIndex = size - 1;

	void * src = data;
	void * drt = buf;
	while (len < size)//直到每次的归并长度达到总长度也就归并完毕
	{
		//两次归并，第一次从源数据到缓存，第二次缓存回来
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
			//依次归并每个完整子区间
			E j = 0;
			while (j + 2 * len < size)
			{
				if (isSrcToBuf)
					_AlgoMerge<D, T, E, T>((D *)src, j, j + len - 1, j + 2 * len - 1, selGet, (T *)drt, AlgoArraySelectSet<T,T,E>, cmp, asc);
				else
					_AlgoMerge<T, T, E, D>((T *)src, j, j + len - 1, j + 2 * len - 1, AlgoArraySelectGet<T, T, E>, (D *)drt, selSet, cmp, asc);
				j += 2 * len;
			}
			//归并剩余的不等长不完整区间
			if (j + len < size)
			{
				if (isSrcToBuf)	
					_AlgoMerge<D, T, E, T>((D *)src, j, j + len - 1, maxIndex, selGet, (T *)drt, AlgoArraySelectSet<T, T, E>, cmp, asc);
				else
					_AlgoMerge<T, T, E, D>((T *)src, j, j + len - 1, maxIndex, AlgoArraySelectGet<T, T, E>, (D *)drt, selSet, cmp, asc);
			}
			else
			{
				//拷贝剩余空间
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
//将start-mid和mid-end两段有序数据合并为一个完整有序的数据
template<typename D, typename T, typename E, typename F, typename FuncCmp, typename FuncSelGet, typename FuncSelSet>
void _AlgoMerge(D * srcData, E start, E mid, E end, FuncSelGet selGetSrc, F * drtData, FuncSelSet selSetDrt, FuncCmp cmp, bool asc)
{
	E i = start, j = mid + 1, k = start;
	//复制数据，直到其中任何一段结束
	while (i <= mid && j <= end)
	{
		//比较数据，谁小谁先来
		if ((cmp(selGetSrc(srcData, i), selGetSrc(srcData, j)) < 0) == asc)
		{
			selSetDrt(drtData, k++, selGetSrc(srcData, i++));
		}
		else
		{
			selSetDrt(drtData, k++, selGetSrc(srcData, j++));
		}
	}
	//把剩余的那一段的数据复制过去
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
堆排序
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
顺序查找
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
二分查找
每次将查找域减少一半，
但是要求被查找域有序
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
		//斐波那契查找，改为0.5比例为0.618，即：//mid=low+0.618*(height-low);
		//插值查找，仅仅适用于数字类型的查找，也就是根据查找值的大致比例，逐渐逼近进行查找，即：中间值位置=最低位置+预估位置比例*总长度//mid=low+	((target-selGet(data,low))/(selGet(data,height)-selGet(data,low)))	*(height-low);
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
斐波那契查找--黄金分割查找
每次将查找域减少一半，
但是要求被查找域有序
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
		//斐波那契查找，又称为黄金分割查找，改为0.5比例为0.618，即：//mid=low+0.618*(height-low);
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
插值查找
仅仅适用于元素支持运算：相减，相除，乘以浮点数，得到浮点数
那么就可以使用本查找算法

否则就不适用

此算法针对C语言中的基本数据类型均有效：int short byte long double float ...
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
		//插值查找，仅仅适用于数字类型的查找，也就是根据查找值的大致比例，逐渐逼近进行查找，即：中间值位置=最低位置+预估位置比例*总长度
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