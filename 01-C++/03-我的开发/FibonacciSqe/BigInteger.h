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
		���ش����Ž���ַ���
	*/
	string Sub(BigInteger & num);
	//���º����ķ��Ž���������ʹ��ʱע�ⱻ�������ڵ��ڼ����жϣ�����ᵼ������5,4,3,2,1,0,1,0,1,0,1���޷�Ԥ�������н������
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
