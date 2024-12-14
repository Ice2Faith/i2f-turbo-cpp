#ifndef _BIGINTEGER_H_
#define _BIGINTEGER_H_
#include<deque>
#include<iterator>
#include<sstream>
#include<iostream>
using namespace std;
class BigInteger
{
public:
	BigInteger(unsigned int num = 0);
	BigInteger(string num);
	BigInteger(BigInteger & num);

	BigInteger& operator=(BigInteger & num);
	BigInteger& operator=(unsigned int num);
	BigInteger& operator=(string num);

	BigInteger operator+(BigInteger & num);
	BigInteger operator+(unsigned int  num);

	BigInteger operator*(BigInteger & num);
	BigInteger operator*(unsigned int  num);

	bool operator==(BigInteger & num);
	bool operator==(unsigned int num);

	bool operator!=(BigInteger & num);
	bool operator!=(unsigned int num);

	bool operator>(BigInteger & num);
	bool operator>(unsigned int num);

	bool operator<(BigInteger & num);
	bool operator<(unsigned int num);

	bool operator>=(BigInteger & num);
	bool operator>=(unsigned int num);

	bool operator<=(BigInteger & num);
	bool operator<=(unsigned int num);

	BigInteger operator<<(BigInteger & num);
	BigInteger operator<<(unsigned int num);

	BigInteger operator>>(BigInteger & num);
	BigInteger operator>>(unsigned int num);

	BigInteger operator~();

	BigInteger& operator++();
	BigInteger operator++(int);

	BigInteger& operator+=(BigInteger & num);
	BigInteger& operator+=(unsigned int  num);
	BigInteger& operator*=(BigInteger & num);
	BigInteger& operator*=(unsigned int  num);

	BigInteger pow(BigInteger & n);
	BigInteger pow(unsigned int  n);

	BigInteger factorial();

	int toInt();
	double toDouble();
	string toString();

	friend ostream & operator<<(ostream &out, BigInteger & num);
	/*
		返回带符号结果字符串
	*/
	string Sub(BigInteger & num);
	//以下函数的符号将被丢弃，使用时注意被减数大于等于减数判断，否则会导致例如5,4,3,2,1,0,1,0,1,0,1等无法预估的序列结果产生
	BigInteger operator-(BigInteger & num);
	BigInteger operator-(unsigned int num);
	BigInteger& operator-=(BigInteger & num);
	BigInteger& operator-=(unsigned int num);
	BigInteger& operator--();
	BigInteger operator--(int);
private:
	deque<char> m_num;
	char dona;
};

#endif // !_BIGINTEGER_H_
