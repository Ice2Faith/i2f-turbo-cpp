#ifndef _ALGO_PATH_HPP_
#define _ALGO_PATH_HPP_
#include"AlgoString.hpp"
class AlgoPath
{
public:
	template<typename T>
	static AlgoString<T, int> getParent(const AlgoString<T, int> & path, T pathSplit)
	{
		AlgoString<T, int> ret(path);
		int len = ret.getLength()-1;
		if (ret[len] == pathSplit)
			len--;
		while (len > 0 && ret[len] != pathSplit)
			len--;
		ret[len] = STRING_END_VALUE;
		return ret;
	}
	template<typename T>
	static AlgoString<T, int> getSuffix(const AlgoString<T, int> & path, T suffixSplit, T pathSplit)
	{
		int len = path.getLength();
		int index = len - 1;
		while (index > 0 && path[index]!=suffixSplit && path[index] != pathSplit)
		{
			index--;
		}
		int suflen = 0;
		if (path[index] == suffixSplit)
		{
			suflen = len - index;
			return path.subString(index+1, suflen-1);
		}
		return AlgoString<T, int>();
	}
	template<typename T>
	static AlgoString<T, int> getName(const AlgoString<T, int> & path, T pathSplit)
	{
		int len = path.getLength();
		int index = len - 1;
		while (index > 0 && path[index] != pathSplit)
			index--;
		if (path[index] == pathSplit)
		{
			index++;
		}
		len = len - index;
		return path.subString(index, len);
	}
	//MkdirFunc要求：接受一个参数，可以是T*类型或者 String<T, int>类型
	template<typename T,typename MkdirFunc>
	static void makeDirs(const AlgoString<T, int> & path, T pathSplit, MkdirFunc mkdf)
	{
		int len = path.getLength();
		int index = 0;
		while (index < len)
		{
			if (path[index] == pathSplit)
			{
				mkdf(path.subString(0, index));
			}
			index++;
		}
		mkdf(path);
	}
};

#endif // _ALGO_PATH_HPP_