#ifndef _ALGO_WIN_STRIN_HPP_
#define _ALGO_WIN_STRIN_HPP_
#include<Windows.h>
#include"AlgoString.hpp"
class AlgoWinString
{
public:

	static int getRequireSize4Unicode2Ascii(wchar_t * wstr)
	{
		return WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	}
	static int getRequireSize4Ascii2Unicode(char * astr)
	{
		return MultiByteToWideChar(CP_ACP, 0, astr, -1, NULL, 0);
	}
	static char * Unicode2Ascii(wchar_t * wstr, char * astr)
	{
		int size = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, wstr, -1, astr, size, NULL, NULL);
		return astr;
	}
	static wchar_t * Ascii2Unicode(char * astr, wchar_t * wstr)
	{
		int size = MultiByteToWideChar(CP_ACP, 0, astr, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, astr, -1, wstr, size);
		return wstr;
	}
	static AlgoString<char, int> Unicode2Ascii(AlgoString<wchar_t, int>& wstr)
	{
		int size = WideCharToMultiByte(CP_ACP, 0, wstr.getData(), -1, NULL, 0, NULL, NULL);
		AlgoString<char, int> astr;
		astr.prepareMemery(size);
		WideCharToMultiByte(CP_ACP, 0, wstr.getData(), -1, astr.getData(), size, NULL, NULL);
		return astr;
	}
	static AlgoString<wchar_t, int> Ascii2Unicode(AlgoString<char, int>& astr)
	{
		int size = MultiByteToWideChar(CP_ACP, 0, astr.getData(), -1, NULL, 0);
		AlgoString<wchar_t, int> wstr;
		wstr.prepareMemery(size);
		MultiByteToWideChar(CP_ACP, 0, astr.getData(), -1, wstr.getData(), size);
		return wstr;
	}

	/////////////////////////////////////////////////////////////////////////
	static int getRequireSize4Unicode2Utf8(wchar_t * wstr)
	{
		return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	}
	static int getRequireSize4Utf82Unicode(char * astr)
	{
		return MultiByteToWideChar(CP_UTF8, 0, astr, -1, NULL, 0);
	}
	static char * Unicode2Utf8(wchar_t * wstr, char * astr)
	{
		int size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, astr, size, NULL, NULL);
		return astr;
	}
	static wchar_t * Utf82Unicode(char * astr, wchar_t * wstr)
	{
		int size = MultiByteToWideChar(CP_UTF8, 0, astr, -1, NULL, 0);
		MultiByteToWideChar(CP_UTF8, 0, astr, -1, wstr, size);
		return wstr;
	}
	static AlgoString<char, int> Unicode2Utf8(AlgoString<wchar_t, int>& wstr)
	{
		int size = WideCharToMultiByte(CP_UTF8, 0, wstr.getData(), -1, NULL, 0, NULL, NULL);
		AlgoString<char, int> astr;
		astr.prepareMemery(size);
		WideCharToMultiByte(CP_UTF8, 0, wstr.getData(), -1, astr.getData(), size, NULL, NULL);
		return astr;
	}
	static AlgoString<wchar_t, int> Utf82Unicode(AlgoString<char, int>& astr)
	{
		int size = MultiByteToWideChar(CP_UTF8, 0, astr.getData(), -1, NULL, 0);
		AlgoString<wchar_t, int> wstr;
		wstr.prepareMemery(size);
		MultiByteToWideChar(CP_UTF8, 0, astr.getData(), -1, wstr.getData(), size);
		return wstr;
	}
};

#endif // _ALGO_WIN_STRIN_HPP_