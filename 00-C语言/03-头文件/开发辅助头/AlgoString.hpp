#ifndef _ALGO_STRING_HPP_
#define _ALGO_STRING_HPP_
/*
特别注意：
由于是泛型模板，因此需要注意的是：
字符，实际上会被隐式按照整型处理，也就会导致一些使用会报错误
比如构造时，使用字符作为构造参数，但是会和预设置内存容量发生不确定性，毕竟，两个实际上都是int参数
因此，需要显示说明类型：
AlgoString<char,int> str((char)'A');//如果不知名类型，将会被当做设置容量AlgoString(int)，而不是按照字符构造处理AlgoString(char)

另外，在运算符重载+时
str=(char)'A' + str;//同样，如果不强制指明类型，将会被当做int+AlgoString，而不是你希望的char+AlgoString
*/
/*
String类
索引操作保证不会下标越界，因此你需要自己控制你的下标，
由于动态大小调整，当下标越界时会自动扩容空间，发生一次拷贝
当你的使用空间较小时，会适当地压缩空间，也会发生一次拷贝
默认会分配64个字符空间，没有设置扩容函数，如果你需要扩容，
只需要下标索引到你想要的空间大小即可，这样的好处是能够减少复制
同样你如果需要节省空间，提供了缩容函数,并且提供了设置自动缩小状态设置
整体功能：
动态大小管理
永远不会下标越界（如果分配空间顺利）
运算符重载支持
增删改查（append/+/*,remove/clear,replace/[],find/first/last,indexOf...）
拆分与合并 join/split
常见字符串操作(compare,substring,endwith,startwith,...)

采用模板，模板参数说明：
T:字符，比如char,无符号限制
E:索引，计数，比如：int，需要带有符号，不能是无符号型
*/

//是否使用KMP算法查找字符串，这将会联动的决定其他的使用到查找的功能
#define USE_KMP_FIND_STR	

#include"AlgoContainer.hpp"
#define STRING_END_VALUE 0
template<typename T, typename E>
class AlgoString
{
	//静态成员函数 和 友元函数（非成员函数），不能加任何修饰符，比如：
	//static bool isA() const;
	//friend bool isB() const;
	//这两个函数的const修饰都是不能添加的
public:
	//C语言基本类型的拼接
	//整数类型：char，short,int,long,long long...
	//参数：val 整型值，base 显示的进制（2-16）
	//注意，均为带符号的现实，也就是说，即使你是16进制输出，也会被当做正数看待，独立出符号
	//因此，如果你需要保持输出，那么请事先转为无符号数
	template<typename INT_TYPE>
	AlgoString& appendInteger(INT_TYPE val, E base = 10)
	{
		if (base<2 || base>16)
		{
			return *this;
		}
		//不用字符串形式初始化，就是因为字符串的类型不确定
		//但是，字符的值都是一样的，无论什么编码格式下，都兼容ASCII值
		T numArr[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 0 };
		if (val == 0)
		{
			this->appendChar('0');
			return *this;
		}

		AlgoString temp;

		int len = 0;
		INT_TYPE num = val;
		if (num < 0)
		{
			this->appendChar('-');
			num = (INT_TYPE)(0 - num);
		}
		while (num != 0)
		{
			E index = num%base;
			temp.appendChar(numArr[index]);
			num = num / base;
			len++;
		}
		len--;
		while (len >= 0)
		{
			this->appendChar(temp[len]);
			len--;
		}
		return *this;
	}
	//浮点类型:float,double
	//参数：val 浮点值，decimal 小数位数
	template<typename FLOAT_TYPE>
	AlgoString& appendFloat(FLOAT_TYPE val, E decimal = 4)
	{
		long ipart = (long)val;
		FLOAT_TYPE fpart = val - ipart;
		if (fpart < 0)
			fpart = 0.0 - fpart;
		this->appendInteger<long>(ipart, 10);
		this->appendChar('.');

		FLOAT_TYPE dec_limit = 1;
		for (E i = 0; i < decimal; i++)
		{
			dec_limit *= 0.1;
		}
		if (fpart < dec_limit)
		{
			this->appendChar('0');
			return *this;
		}

		T numArr[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 0 };
		E len = 0;
		while (len < decimal)
		{
			long index = (long)(fpart * 10);
			if (len == decimal - 1)
				index = (long)((fpart * 10) + 0.5);
			this->appendChar(numArr[index]);
			fpart = (fpart * 10) - index;
			len++;
		}

		return *this;
	}
	//布尔类型：bool
	AlgoString& appendBool(bool val)
	{
		E i = getLength();
		T arrs[][6] = { { 't', 'r', 'u', 'e', 0 },
		{ 'f', 'a', 'l', 's', 'e', 0 }
		};
		extendCapital(i + 6);//false len is 5
		E iarr = 0;
		if (val)
		{
			iarr = 0;
		}
		else
		{
			iarr = 1;
		}
		E j = 0;
		while (arrs[iarr][j] != 0)
		{
			m_data[i + j] = arrs[iarr][j];
			j++;
		}
		notifyStringEnd(i + j);
		return *this;
	}
	//格式化字符串，仅支持占位符号：%c %d %f %b %s %x %o %n %p %g %%
	//10进制默认参数，占位符不区分大小写，如果出现未解析的占位符，将会直接保留源串内容，比如%# 也会保留为%#
	//格式化描述：字符型%c，整型%d，浮点数%f，布尔型%b,字符串型%s 十六进制整数%x 八进制整数%o 二进制整数%n 二位精度小数%p 八位小数精度%g 单个百分号%
	AlgoString& formatString(const T * format, ...)
	{
		if (format == NULL)
			return *this;

		va_list varList;
		va_start(varList, format);

		E i = 0;
		while (format[i] != STRING_END_VALUE)
		{
			if (format[i] == '%')
			{
				i++;
				T ch = format[i];
				if (ch >= 'A' && ch <= 'Z')
					ch |= 32;
				switch (ch)
				{
				case '%':
					this->appendChar(ch);
					break;
				case 'c':
					this->appendChar(va_arg(varList, T));
					break;
				case 'd':
					this->appendInteger(va_arg(varList, long));
					break;
				case 'f':
					this->appendFloat(va_arg(varList, double));
					break;
				case 'b':
					this->appendBool(va_arg(varList, bool));
					break;
				case 's':
					this->appendString(va_arg(varList, T*));
					break;
				case 'x':
					this->appendInteger(va_arg(varList, long), 16);
					break;
				case 'o':
					this->appendInteger(va_arg(varList, long), 8);
					break;
				case 'n':
					this->appendInteger(va_arg(varList, long), 2);
					break;
				case 'p':
					this->appendFloat(va_arg(varList, double), 2);
					break;
				case 'g':
					this->appendFloat(va_arg(varList, double), 8);
					break;
				default:
					this->appendChar('%');
					this->appendChar(format[i]);
					break;
				}
			}
			else
			{
				this->appendChar(format[i]);
			}
			i++;
		}

		va_end(varList);
		return *this;
	}

	template<typename INT_TYPE>
	static bool parseInteger(const T * str, INT_TYPE * retVal, E base = 10,E * useLen=NULL)
	{
		if (str == NULL || base<2 || base>16)
			return false;


		INT_TYPE val = 0;

		T ch = str[0];
		bool isNeg = false;

		E i = 0;
		if (ch == '-')
		{
			i = 1;
			isNeg = true;
		}
		if (ch == '+')
			i = 1;

		ch = str[i];
		if (getNumberIndex(ch, base))
		{

			while (true)
			{
				ch = str[i];
				E pv = getNumberIndex(ch, base);
				if (pv == -1)
				{
					if (isNeg)
						val = 0 - val;
					*retVal = val;
					if (useLen != NULL)
						*useLen = i;
					return true;
				}
				val *= base;
				val += pv;
				i++;
			}
		}
		else
		{
			return false;
		}
	}
	template<typename FLOAT_TYPE>
	static bool parseFloat(const T * str, FLOAT_TYPE * retVal, E * useLen = NULL)
	{
		if (str == NULL)
			return false;

		FLOAT_TYPE val = 0;

		T ch = str[0];
		bool isNeg = false;

		E i = 0;
		if (ch == '-')
		{
			i = 1;
			isNeg = true;
		}
		if (ch == '+')
			i = 1;

		ch = str[i];
		if (getNumberIndex(ch, 10))
		{

			while (true)
			{
				ch = str[i];
				E pv = getNumberIndex(ch, 10);
				if (pv == -1)
				{
					break;
				}
				val *= 10;
				val += pv;
				i++;
			}

			ch = str[i];
			if (ch == '.')
			{
				i++;
				FLOAT_TYPE dec = 0.1;
				while (true)
				{
					ch = str[i];
					E pv = getNumberIndex(ch, 10);
					if (pv == -1)
					{
						if (isNeg)
							val = 0 - val;
						*retVal = val;
						if (useLen != NULL)
							*useLen = i;
						return true;
					}
					val += pv*dec;
					i++;
					dec *= 0.1;
				}

			}
		}
		else
		{
			return false;
		}
	}
	static bool parseBool(const T * str, bool * retVal, E * useLen = NULL)
	{
		if (str == NULL)
			return false;
		T ch = str[0];
		if (isA2Z(ch))
			ch |= 32;
		if (ch != 't' && ch != 'f')
			return false;

		T arrs[][6] = { { 't', 'r', 'u', 'e', 0 },
		{ 'f', 'a', 'l', 's', 'e', 0 }
		};

		E iarr = 0;

		if (ch == 't')
		{
			iarr = 0;
		}
		else
		{
			iarr = 1;

		}

		int j = 0;
		while (arrs[iarr][j] != 0 && str[j] != 0)
		{
			ch = str[j];
			if (isA2Z(ch))
				ch |= 32;
			if (arrs[iarr][j] != ch)
			{
				return false;
			}
			j++;
		}
		if (useLen != NULL)
			*useLen = j;
		if (iarr == 0)
			*retVal = true;
		else
			*retVal = false;
		return true;
	}
public:
	//"aaa"+AlgoString
	friend AlgoString operator+(T ch, const AlgoString & str)
	{
		AlgoString ret = ch;
		ret += str;
		return ret;
	}
	friend AlgoString operator+(const T * str1, const AlgoString & str2)
	{
		AlgoString ret = str1;
		ret += str2;
		return ret;
	}
	friend AlgoString operator*(E repeat, const AlgoString & str2)
	{
		AlgoString ret = str2;
		ret *= repeat;
		return ret;
	}
public:
	AlgoString()
	{
		initString();
	}
	AlgoString(E capital)
	{
		initString(capital);
	}
	AlgoString(T ch)
	{
		initString();
		fromChar(ch);
	}
	AlgoString(const T * str)
	{
		initString();
		fromString(str);
	}
	AlgoString(const AlgoString & str)
	{
		initString();
		fromString(str.m_data);
	}
	AlgoString & operator=(const AlgoString & str)
	{
		return fromString(str.m_data);
	}
	AlgoString & operator=(const T * str)
	{
		return fromString(str);
	}
	AlgoString & operator=(T ch)
	{
		return fromChar(ch);
	}
	AlgoString & fromChar(T ch)
	{
		E i = 0;
		extendCapital(i + 2);
		m_data[i++] = ch;
		notifyStringEnd(i);

		return *this;
	}
	AlgoString & fromString(const T * str)
	{
		if (str == NULL)
		{
			notifyStringEnd(0);
			return *this;
		}


		const T *  data = str;
		E i = 0;
		for (i = 0; *data != STRING_END_VALUE; i++, data++)
		{
			extendCapital(i);
			m_data[i] = *data;
		}
		notifyStringEnd(i);

		return *this;
	}
	operator T *()const
	{
		return this->m_data;
	}
	//AlgoString+"aaa"
	AlgoString & operator+(const T * str)
	{
		return appendString(str);
	}
	AlgoString & operator+(const AlgoString & str)
	{
		return appendString(str.m_data);
	}
	AlgoString & operator+=(const AlgoString & str)
	{
		return appendString(str.m_data);
	}
	AlgoString & operator+=(const T * str)
	{
		return appendString(str);
	}
	AlgoString & operator+(T ch)
	{
		return appendChar(ch);
	}
	AlgoString & operator+=(T ch)
	{
		return appendChar(ch);
	}
	AlgoString & append(T ch)
	{
		return appendChar(ch, 1);
	}
	AlgoString & append(T ch, E count)
	{
		return appendChar(ch, count);
	}
	AlgoString & appendChar(T ch, E repeatCount = 1)
	{
		E i = this->getLength();
		for (E c = 0; c < repeatCount; c++)
		{
			extendCapital(i);
			m_data[i++] = ch;
			notifyStringEnd(i);
		}
		return *this;
	}
	AlgoString & append(const T * str)
	{
		return appendString(str);
	}
	AlgoString & append(const AlgoString & str)
	{
		return appendString(str.m_data);
	}
	AlgoString & appendString(const T * str)
	{
		if (str == NULL)
			return *this;

		E i = this->getLength();
		const T *  data = str;
		for (; *data != STRING_END_VALUE; i++, data++)
		{
			extendCapital(i);
			m_data[i] = *data;
		}
		notifyStringEnd(i);
		return *this;
	}
	AlgoString& insert(E index, const T * str)
	{
		E len = getLength();
		len += lengthString(str);
		extendCapital(len);
		insertString(m_data, index, str);
		return *this;
	}
	AlgoString& insert(E index, const AlgoString& str)
	{
		E len = getLength();
		len += str.getLength();
		extendCapital(len);
		insertString(m_data, index, str.m_data);
		return *this;
	}
	AlgoString & operator*(E repeat)
	{
		return repeatString(repeat);
	}
	AlgoString & operator*=(E repeat)
	{
		return repeatString(repeat);
	}
	AlgoString& repeatString(E repeat)
	{
		if (repeat <= 0)
		{
			notifyStringEnd(0);
			return *this;
		}
		E len = this->getLength();
		E j = len;
		for (E i = 0; i < repeat - 1; i++)
		{
			T *  data = this->m_data;
			for (E k = 0; k<len; j++, k++)
			{
				extendCapital(j);
				data = this->m_data;
				m_data[j] = data[k];
			}
		}
		notifyStringEnd(j);
		return *this;
	}
	bool operator==(const T * str)const
	{
		return cmpString(this->m_data, str) == 0;
	}
	bool operator==(const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data) == 0;
	}
	bool operator>(const T * str)const
	{
		return cmpString(this->m_data, str)>0;
	}
	bool operator>(const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data)>0;
	}
	bool operator<(const T * str)const
	{
		return cmpString(this->m_data, str)<0;
	}
	bool operator<(const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data)<0;
	}
	bool operator>=(const T * str)const
	{
		return cmpString(this->m_data, str) >= 0;
	}
	bool operator>=(const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data) >= 0;
	}
	bool operator<=(const T * str)const
	{
		return cmpString(this->m_data, str) <= 0;
	}
	bool operator<= (const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data) <= 0;
	}
	bool operator!=(const T * str)const
	{
		return cmpString(this->m_data, str) != 0;
	}
	bool operator!=(const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data) != 0;
	}
	E compareIgnoreCase(const T * str)const
	{
		String tp2(str);
		String tp1(this->m_data);
		tp1.toLowerCase();
		tp2.toLowerCase();
		return cmpString(tp1, tp2);
	}
	E compareIgnoreCase(const AlgoString & str)const
	{
		AlgoString tp2(str);
		AlgoString tp1(this->m_data);
		tp1.toLowerCase();
		tp2.toLowerCase();
		return cmpString(tp1, tp2);
	}
	E compare(const T * str)const
	{
		return cmpString(this->m_data, str);
	}
	bool equals(const AlgoString & str)const
	{
		return this->compare(str) == 0;
	}
	bool equalsIgnoreCase(const AlgoString & str)const
	{
		return this->compareIgnoreCase(str) == 0;
	}
	E compare(const AlgoString & str)const
	{
		return cmpString(this->m_data, str.m_data);
	}
	bool contains(const T * str)const
	{
		return containsString(this->m_data, str);
	}
	bool contains(const AlgoString & str)const
	{
		return containsString(this->m_data, str.m_data);
	}
	E lenCompare(const T * child)const
	{
		return ncmpString(this->m_data, child, lengthString(child));
	}
	E lenCompare(const T * str, E len)const
	{
		return ncmpString(this->m_data, str, len);
	}
	E lenCompare(const AlgoString & str, E len)const
	{
		return ncmpString(this->m_data, str.m_data, len);
	}
	E first(const T * str)const
	{
		return findString(this->m_data, str);
	}
	E first(const AlgoString & str)const
	{
		return findString(this->m_data, str.m_data);
	}
	E find(E beginIndex, const T * str)const
	{
		return findString(&(this->m_data[beginIndex]), str);
	}
	E find(E beginIndex, const AlgoString & str)const
	{
		return findString(&(this->m_data[beginIndex]), str.m_data);
	}
	E last(const T * str)const
	{
		return lastString(this->m_data, str);
	}
	E last(const AlgoString & str)const
	{
		return lastString(this->m_data, str.m_data);
	}
	E indexOf(const T * str)const
	{
		return findString(this->m_data, str);
	}
	E countOf(const T * str)const
	{
		if (str == NULL)
			return 0;

		E count = 0;
		E index = 0;
		E len = lengthString(str);
		E mlen = lengthString(m_data);
		while (index < mlen)
		{
			E pindex = findString(&m_data[index], str);
			if (pindex>0)
			{
				count++;
				index = index + pindex + len;
			}
			else
			{
				index++;
			}

		}

		return count;
	}
	E countOf(const AlgoString& str)const
	{
		return countOf(str.m_data);
	}
	bool startWith(const AlgoString & str)const
	{
		return startWithString(this->m_data, str.m_data)
	}
	bool startWith(const T * str)const
	{
		return startWithString(this->m_data, str);
	}
	bool endWith(const AlgoString & str)const
	{
		return endWithString(this->m_data, str.m_data);
	}
	bool endWith(const T * str)const
	{
		return endWithString(this->m_data, str);
	}
	AlgoString& toLowerCase()
	{
		toLowerCaseString(this->m_data);
		return *this;
	}
	AlgoString& toUpperCase()
	{
		toUpperCaseString(this->m_data);
		return *this;
	}
	AlgoString& replace(const AlgoString & srcStr, const AlgoString & drtStr, E maxReplaceCount)
	{
		return replace(srcStr.m_data, drtStr.m_data, maxReplaceCount);
	}
	AlgoString& replace(const T * srcStr, const T * drtStr, E maxRelapceCount)
	{
		if (srcStr == NULL || drtStr == NULL)
			return *this;

		if (maxRelapceCount == 0)
			return *this;
		T * orgData = m_data;
		initString();

		bool needReplace = true;
		E count = 0;
		E srcLen = lengthString(srcStr);
		E drtLen = lengthString(drtStr);
		E index = 0;
		E saveIndex = 0;
		while (orgData[index] != STRING_END_VALUE)
		{
			if (needReplace && ncmpString(&orgData[index], srcStr, srcLen) == 0)
			{
				count++;
				if (maxRelapceCount > 0)
				{
					if (count >= maxRelapceCount)
						needReplace = false;
				}

				E k = 0;
				while (drtStr[k] != STRING_END_VALUE)
				{
					extendCapital(saveIndex);
					m_data[saveIndex] = drtStr[k];
					saveIndex++;
					k++;
				}
				index += srcLen;
			}
			else
			{
				extendCapital(saveIndex);
				m_data[saveIndex] = orgData[index];
				saveIndex++;
				index++;
			}

		}
		delete[] orgData;
		notifyStringEnd(saveIndex);
		return *this;
	}
	AlgoString& join(const AlgoString & joinStr, AlgoArray<AlgoString<T, E>, E> & joinArray, bool headJoin = true)
	{
		for (E i = 0; i < joinArray.size(); i++)
		{
			if (headJoin && i == 0)
				this->appendString(joinStr.m_data);
			AlgoString str = joinArray[i];
			this->appendString(str.m_data);
			if (i != joinArray.size() - 1)
				this->appendString(joinStr.m_data);
		}
		return *this;
	}
	//使用此方法时，参数2可能需要类型装换一下：(const char **)
	AlgoString & joinString(const T * joinStr, const T * joinArray[], E arrCount, bool headJoin = true)
	{

		for (E i = 0; i < arrCount; i++)
		{
			if (headJoin && i == 0)
				this->appendString(joinStr);
			AlgoString str = joinArray[i];
			this->appendString(joinArray[i]);
			if (i != arrCount - 1)
				this->appendString(joinStr);
		}
		return *this;
	}
	AlgoArray<AlgoString<T, E>, E> & split(const AlgoString & splitStr, AlgoArray<AlgoString<T, E>, E> & saveArray, E maxSplitCount, bool removeEmpty = true)const
	{
		saveArray.setSize(0);
		if (splitStr == NULL)
			return saveArray;

		E clen = lengthString(splitStr.m_data);
		E index = 0;
		E tpi = 0;
		AlgoString tp;
		E count = 0;
		bool isNeedDo = true;
		while (m_data[index] != STRING_END_VALUE)
		{
			if (isNeedDo && ncmpString(&m_data[index], splitStr.m_data, clen) == 0)
			{
				count++;
				if (maxSplitCount > 0)
				{
					if (count >= maxSplitCount)
					{
						isNeedDo = false;
					}
				}
				if (removeEmpty)
				{
					if (tp.m_data[0] != STRING_END_VALUE)
						saveArray.push(tp);
				}
				else
				{
					saveArray.push(tp);
				}

				tp.clear();
				tpi = 0;
				index += clen;
			}
			else
			{
				tp.extendCapital(tpi);
				tp.m_data[tpi] = m_data[index];
				tp.notifyStringEnd(tpi + 1);
				index++;
				tpi++;
			}
		}
		if (tp.getLength() > 0)
			saveArray.push(tp);
		return saveArray;
	}
	//字符串拆分，当字符串在给定的字符串序列中时进行拆分，相邻的字符会被合并看待
	AlgoArray<AlgoString<T, E>, E> & splitWhen(const T * splitChars, AlgoArray<AlgoString<T, E>, E> & saveArray, E maxSplitCount, bool removeEmpty = true)const
	{
		saveArray.setSize(0);

		if (splitChars == NULL)
			return saveArray;


		E index = 0;
		E tpi = 0;
		AlgoString tp;
		E tplen = 0;
		E count = 0;
		bool isNeedDo = true;
		while (m_data[index] != STRING_END_VALUE)
		{
			T pch = m_data[index];
			bool isInChar = false;
			if (isNeedDo)
			{
				E k = 0;
				while (splitChars[k] != STRING_END_VALUE)
				{
					if (pch == splitChars[k])
					{
						isInChar = true;
						break;
					}
					k++;
				}

			}

			if (isInChar)
			{
				if (tplen > 0)
				{
					count++;
					if (maxSplitCount > 0)
					{
						if (count >= maxSplitCount)
						{
							isNeedDo = false;
						}
					}
					if (removeEmpty)
					{
						if (tp.m_data[0] != STRING_END_VALUE)
							saveArray.push(tp);
					}
					else
					{
						saveArray.push(tp);
					}
					tp.clear();
					tpi = 0;
					tplen = 0;
				}
			}
			else
			{
				tp.extendCapital(tpi);
				tp.m_data[tpi] = m_data[index];
				tp.notifyStringEnd(tpi + 1);
				tplen = tpi + 1;
				tpi++;
			}
			index++;
		}
		if (tp.getLength() > 0)
			saveArray.push(tp);
		return saveArray;
	}
	AlgoString subString(E index, E length)const
	{
		AlgoString ret;
		if (index < 0)
			return ret;

		ret.extendCapital(length);
		subtractString(m_data, index, length, ret.m_data);

		return ret;
	}
	AlgoString subStringIndex(E beginIndex, E endIndex)const
	{
		return subString(beginIndex, endIndex - beginIndex + 1);
	}
	AlgoString subLeft(E len)const
	{
		return subString(0, len);
	}
	AlgoString subRight(E len)const
	{
		return subString(getLength() - len, len);
	}
	AlgoString subUtil(E beginIndex, T utilChar, bool ignoreCase = false)const
	{
		AlgoString ret;
		T ch = m_data[beginIndex];
		if (ignoreCase)
		{
			utilChar = chToLower(utilChar);
			ch = chToLower(ch);
		}

		while (ch != utilChar  && ch != STRING_END_VALUE)
		{
			ret.appendChar(ch);
			beginIndex++;
			ch = m_data[beginIndex];
			if (ignoreCase)
			{
				ch = chToLower(ch);
			}
		}
		return ret;
	}
	AlgoString subUtilIn(E beginIndex,const T * utilChars, E countChars, bool ignoreCase = false)const
	{
		AlgoString ret;
		T ch = m_data[beginIndex];
		while (ch != STRING_END_VALUE)
		{
			bool isIns = false;
			for (E i = 0; i < countChars; i++)
			{
				T pch = ignoreCase ? chToLower(ch) : ch;
				T puch = ignoreCase ? chToLower(utilChars[i]) : utilChars[i];
				if (pch == puch)
				{
					isIns = true;
					break;
				}
			}
			if (isIns)
			{
				break;
			}
			ret.appendChar(ch);
			beginIndex++;
			ch = m_data[beginIndex];
		}
		return ret;
	}
	AlgoString& remove(const T * str, E maxRemoveCount)
	{
		if (str == NULL)
			return *this;

		if (maxRemoveCount == 0)
			return *this;
		T * orgData = m_data;
		initString();

		bool needRemove = true;
		E count = 0;
		E srcLen = lengthString(str);
		E index = 0;
		E saveIndex = 0;
		while (orgData[index] != STRING_END_VALUE)
		{
			if (needRemove && ncmpString(&orgData[index], str, srcLen) == 0)
			{
				count++;
				if (maxRemoveCount > 0)
				{
					if (count >= maxRemoveCount)
						needRemove = false;
				}
				index += srcLen;
			}
			else
			{
				extendCapital(saveIndex);
				m_data[saveIndex] = orgData[index];
				saveIndex++;
				index++;
			}

		}
		delete[] orgData;
		notifyStringEnd(saveIndex);
		return *this;
	}
	AlgoString& remove(const AlgoString & str, E maxRemoveCount)
	{
		return remove(str.m_data, maxRemoveCount);
	}
	AlgoString& trim()
	{
		E len = 0;
		while (isSpaceChar(m_data[len]))
			len++;
		E index = 0;
		while (m_data[index + len] != STRING_END_VALUE)
		{
			m_data[index] = m_data[index + len];
			index++;
		}
		index = index - 1;
		while (isSpaceChar(m_data[index]) && index >= 0)
			index--;
		notifyStringEnd(index + 1);
		return *this;
	}
	AlgoString& trimEnd()
	{
		E len = lengthString(this->m_data);
		E index = len - 1;
		while (isSpaceChar(m_data[index]) && index >= 0)
			index--;
		notifyStringEnd(index + 1);
		return *this;
	}
	AlgoString& trimBegin()
	{
		E len = 0;
		while (isSpaceChar(m_data[len]))
			len++;
		E index = 0;
		while (m_data[index + len] != STRING_END_VALUE)
		{
			m_data[index] = m_data[index + len];
			index++;
		}
		notifyStringEnd(index);
		return *this;
	}
	AlgoString& trimAll()
	{
		E curIndex = 0,saveIndex=0;
		while (m_data[curIndex] != STRING_END_VALUE)
		{
			if (isSpaceChar(m_data[curIndex]))
			{
				curIndex++;
			}
			else
			{
				m_data[saveIndex] = m_data[curIndex];
				curIndex++;
				saveIndex++;
			}
			
		}
		notifyStringEnd(saveIndex);
		return *this;
	}
	AlgoString& reverse()
	{
		reverseString(m_data, 0, getLength() - 1);
		return *this;
	}
	AlgoString& reverse(E beginIndex, E len)
	{
		reverseString(m_data, beginIndex, beginIndex + len);
		return *this;
	}
	AlgoString& clear()
	{
		notifyStringEnd(0);
		return *this;
	}
	T& operator[](E index)
	{
		extendCapital(index);
		return m_data[index];
	}
	T * getData()const
	{
		return m_data;
	}
	E getCapital()const
	{
		return m_capital;
	}
	void shrinkCapital()
	{
		E len = lengthString(m_data);
		E newCapital = m_capital;
		E ml = 1;
		while ((newCapital >> ml) > len)
		{
			ml++;
		}
		newCapital = newCapital >> (ml - 1);
		if (newCapital <= 1)
		{
			newCapital = 1;
		}
		T * buf = new T[newCapital];
		for (E i = 0; i < len; i++)
		{
			buf[i] = m_data[i];
		}
		delete[] m_data;
		m_data = buf;
		m_capital = newCapital;
		notifyStringEnd(len);
	}
	E getLength()const
	{
		return lengthString(this->m_data);
	}
	AlgoString& len2zero()
	{
		notifyStringEnd(0);
		return *this;
	}
	AlgoString& zeroMemory()
	{
		memorySet(0, m_capital - 1, STRING_END_VALUE);
		return *this;
	}
	AlgoString& memorySet(E beginIndex, E endIndex, T value)
	{
		extendCapital(endIndex);
		for (; beginIndex <= endIndex; beginIndex++)
		{
			m_data[beginIndex] = value;
		}
		return *this;
	}
	T * prepareMemery(E size)
	{
		extendCapital(size - 1);
		return m_data;
	}
	AlgoString& setAutoShinkState(bool open)
	{
		openAutoShrink = open;
		return *this;
	}
	bool isNullOrEmpty(bool needTrimed = false)const
	{
		return isNullOrEmpty(m_data, needTrimed);
	}
	virtual ~AlgoString()
	{
		if (m_data != NULL)
		{
			delete[] m_data;
			m_data = NULL;
		}
		m_capital = 0;
	}
public:
	//提供给上层成员函数调用，这些函数的缓冲区大小需要事先分配，否则操作将是不安全的，但是你依然可以进行使用
	//仅仅只包含部分底层调用，不是完整的整个服务层，需要注意，也就是说，想要使用完整的类功能，这些底层部分是不能够完全提供的
	//但是不建议直接进行使用，入口指针参数均适用const修饰，未被const修饰的指针参数为出口参数【同时也可能是入口参数】，需要你分配足够的空间
	//return=str+str1
	static T * appendString(T * str, const T * str1)
	{
		if (str == NULL || str1 == NULL)
			return str;

		E len_str = lengthString(str);

		E i = 0;
		while (str1[i]!= STRING_END_VALUE)
		{
			str[len_str + i] = str1[i];
			i++;
		}
		str[len_str + i] = STRING_END_VALUE;

		return str;
	}
	//return=substr
	static T * subtractString(const T * str, E index, E length, T * subStr)
	{
		if (str == NULL || subStr == NULL)
			return subStr;

		if (index < 0 || length==0)
		{
			subStr[0] = STRING_END_VALUE;
			return subStr;
		}
			

		if (length > 0)
		{
			E i = 0;
			while (i < length)
			{
				subStr[i] = str[index + i];
				subStr[i + 1] = STRING_END_VALUE;
				if (str[index + i] == STRING_END_VALUE)
					break;
				i++;
			}
		}
		else
		{
			E i = 0;
			while (str[index + i] != STRING_END_VALUE)
			{
				subStr[i] = str[index + i];
				subStr[i + 1] = STRING_END_VALUE;
				i++;
			}
		}
		return subStr;
	}
	//return=str
	static T * insertString(T * str,E index, const T * subStr)
	{
		if (str == NULL || index < 0 || subStr == NULL)
			return str;

		E len_str = lengthString(str);
		E len_substr = lengthString(subStr);
		
		E i = len_str;
		while (i >= index)
		{
			str[i + len_substr] = str[i];
			i--;
		}
		for (i = 0; i < len_substr; i++)
		{
			str[index + i] = subStr[i];
		}
		return str;
	}
	static E cmpString(const T * str1, const T * str2)
	{
		if (str1 == str2)
			return 0;
		if (str1 == NULL && str2)
			return -1;
		if (str1 && str2 == NULL)
			return 1;

		while (*str1 != STRING_END_VALUE && *str2 != STRING_END_VALUE)
		{
			if (*str1 > *str2)
			{
				return 1;
			}
			else if (*str1 < *str2)
			{
				return -1;
			}
			str1++;
			str2++;
		}
		if (*str1 == STRING_END_VALUE && *str2 == STRING_END_VALUE)
			return 0;
		if (*str1 == STRING_END_VALUE)
			return -1;
		if (*str2 == STRING_END_VALUE)
			return 1;
	}
	static bool containsString(const T * str, const T * child)
	{
		return findString(str, child) != -1;
	}
	static E ncmpString(const T * str1, const T * str2, E len)
	{
		if (str1 == str2)
			return 0;
		if (str1 == NULL && str2)
			return -1;
		if (str1 && str2 == NULL)
			return 1;

		for (E i = 0; i < len; i++, str1++, str2++)
		{
			if (*str1 == STRING_END_VALUE && *str2 == STRING_END_VALUE)
				return 0;
			if (*str1 == STRING_END_VALUE)
				return -1;
			if (*str2 == STRING_END_VALUE)
				return 1;
			if (*str1 > *str2)
				return 1;
			if (*str1 < *str2)
				return -1;
		}
		return 0;
	}
	static E firstString(const T * str, const T * child)
	{
		return findString(str, child);
	}
	static E lastString(const T * str, const T * child)
	{
		if (str == NULL || child == NULL)
			return -1;

		E clen = lengthString(child);
		if (clen == 0)
			return -1;
		E mlen = lengthString(str);
		if (clen > mlen)
			return -1;
		E i = mlen - 1;
		while ((i - clen) >= 0)
		{
			if (str[i] == child[0] && str[i + clen - 1] == child[clen - 1])
			{
				if (ncmpString(&str[i], child, clen) == 0)
				{
					return i;
				}

			}
			i--;
		}
		return -1;
	}
#if defined USE_KMP_FIND_STR
	static void getPrefixTable(const T * str, E * prefix)
	{
		if (str == NULL || prefix == NULL)
			return;

		E j = 0, i = 1;
		prefix[j] = 0;
		while (str[i + 1] != 0)
		{
			if (str[i] == str[j])
			{
				prefix[i] = j + 1;
				i++;
				j++;
			}
			else
			{
				if (j == 0)
				{
					prefix[i] = 0;
					i++;
				}
				else
				{
					j = prefix[j - 1];
				}
			}
		}

		while (i > 0)
		{
			prefix[i] = prefix[i - 1];
			i--;
		}
		prefix[0] = -1;
	}
	static int kmp_find(const T * str, const T * substr)
	{
		if (str == NULL || substr == NULL)
			return -1;

		E sublen = strlen(substr);
		if (sublen <= 0)
			return -1;
		if (sublen == 1)
		{
			E i = 0;
			while (str[i] != STRING_END_VALUE)
			{
				if (str[i] == substr[0])
					return i;
				i++;
			}
			return -1;
		}

		E * prefix = (E *)malloc(sizeof(E)*sublen);
		getPrefixTable(substr, prefix);

		E i = 0, j = 0;
		while (str[i] != STRING_END_VALUE)
		{
			if (j == sublen - 1 && str[i] == substr[j])
			{
				free(prefix);
				return i - j;
				//j = profix[j];
			}
			if (str[i] == substr[j])
			{
				i++;
				j++;
			}
			else
			{
				j = prefix[j];
				if (j == -1)
				{
					i++, j++;
				}
			}
		}
		free(prefix);
		return -1;
	}
#endif
	static E findString(const T * str, const T * child)
	{
		if (str == NULL || child == NULL)
			return -1;

#if defined USE_KMP_FIND_STR
		return kmp_find(str, child);
#else
		E clen = lengthString(child);
		if (clen == 0)
			return -1;
		E i = 0;
		while (str[i] != STRING_END_VALUE)
		{
			if (str[i] == child[0] && str[i + clen - 1] == child[clen - 1])
			{
				if (ncmpString(&str[i], child, clen) == 0)
				{
					return i;
				}

			}
			i++;
			if (str[i + clen] == STRING_END_VALUE)
			{
				break;
			}
		}

		return -1;
#endif
	}
	static bool startWithString(const T * str1, const T * str2)
	{
		if (str1 == NULL || str2 == NULL)
			return false;

		if (ncmpString(str1, str2, lengthString(str2)) == 0)
			return true;
		return false;
	}
	static bool endWithString(const T * str1, const T * str2)
	{
		if (str1 == NULL || str2 == NULL)
			return false;

		E clen = lengthString(str2);
		E mlen = lengthString(str1);
		if (clen > mlen)
			return false;
		if (ncmpString(&str1[mlen - clen], str2, clen) == 0)
			return true;
		return false;
	}
	//return=str
	static T * toLowerCaseString(T * str)
	{
		if (str == NULL)
			return str;

		while (*str != STRING_END_VALUE)
		{
			if (isA2Z(*str))
			{
				(*str) |= 32;
			}
			*str++;
		}
		return str;
	}
	//return=str
	static T * toUpperCaseString(T * str)
	{
		if (str == NULL)
			return str;

		while (*str != STRING_END_VALUE)
		{
			if (isa2z(*str))
			{
				(*str) -= 32;
			}
			*str++;
		}
		return str;
	}
	static bool isAsciiChar(T ch)
	{
		return ch >= 0 && ch < 128;
	}
	static T chToUpper(T ch)
	{
		if (isa2z(ch))
			return 'A' + (ch - 'a');
		return ch;
	}
	static T chToLower(T ch)
	{
		if (isA2Z(ch))
			return 'a' + (ch - 'A');
		return ch;
	}
	static bool isA2Z(T ch)
	{
		return ch >= 'A' && ch <= 'Z';
	}
	static bool isa2z(T ch)
	{
		return ch >= 'a' && ch <= 'z';
	}
	static bool isAlphabet(T ch)
	{
		return (ch >= 'a' && ch <= 'z') || (ch >= 'A'&&ch <= 'Z');
	}
	static bool isNumber(T ch)
	{
		return ch >= '0' && ch <= '9';
	}
	//判断字符是否是2-16进制中的数字字符
	static bool isBaseNumber(T ch, E base = 10)
	{
		if (base<2 || base>16)
			return false;

		static T map[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
		for (E i = 0; i<base; i++)
		{
			if (ch == map[i])
				return true;
		}
		return false;
	}
	//获取2-16进制数字字符的字面值0-16，失败返回-1
	static E getBaseNumberValue(T ch,E base)
	{
		if (base<2 || base>16)
			return -1;

		static T map[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
		for (E i = 0; i<base; i++)
		{
			if (ch == map[i])
				return i;
		}
		return -1;
	}
	static bool isControlChar(T ch)
	{
		return ch > 0 && ch < 32;
	}
	static bool isSpaceChar(T ch)
	{
		return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v';
	}
	//return=str
	static T * reverseString(T * str, E beginIndex, E endIndex)
	{
		if (str == NULL || beginIndex < 0 || endIndex < beginIndex)
			return str;

		while (beginIndex < endIndex)
		{
			T ch = str[beginIndex];
			str[beginIndex] = str[endIndex];
			str[endIndex] = ch;
			beginIndex++;
			endIndex--;
		}
		return str;
	}
	static E lengthString(const T * str)
	{
		if (str == NULL)
			return 0;

		E len = 0;
		while (str[len] != STRING_END_VALUE)
			len++;
		return len;
	}
	static bool isNullOrEmpty(const T * str, bool needTrimed = false)
	{
		if (str == NULL)
			return true;
		AlgoString tp = str;
		if (needTrimed)
			tp.trim();
		if (tp.getLength() == 0)
			return true;
		return false;
	}
protected:
	T * m_data;
	E  m_capital;
	bool openAutoShrink;

	void initString(E capital = 64)
	{
		openAutoShrink = false;
		if (capital > 64)
			m_capital = capital;
		else
			m_capital = 64;
		m_data = new T[m_capital];
		zeroMemory();
		notifyStringEnd(0);
	}
	void notifyStringEnd(E index)
	{
		if (index<0)
			return;

		extendCapital(index);
		m_data[index] = STRING_END_VALUE;
		if (openAutoShrink && index>16 && index * 4 < m_capital && m_capital >= 256)
		{
			shrinkCapital();
		}
	}
	void extendCapital(E index)
	{
		if (index < 0)
			return;

		if (index >= m_capital)
		{
			E bufSize = m_capital << 1;
			if (bufSize <= index)
				bufSize = index + 1 + 16;
			T * buf = new T[bufSize];
			for (E i = 0; i <m_capital; i++)
			{
				buf[i] = m_data[i];
			}
			delete[] m_data;
			m_capital = bufSize;
			m_data = buf;

		}
	}
	static E getNumberIndex(T ch, E base = 10)
	{
		if (base<2 || base>16)
			return -1;

		T numArr[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 0 };
		E ret = -1;
		if (isA2Z(ch))
			ch |= 32;

		E j = 0;
		while (j < base)
		{
			if (numArr[j] == ch)
			{
				ret = j;
				break;
			}
			j++;
		}

		return ret;
	}
};


#endif // _ALGO_STRING_HPP_