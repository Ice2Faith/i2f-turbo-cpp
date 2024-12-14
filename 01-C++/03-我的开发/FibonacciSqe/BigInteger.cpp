#include"BigInteger.h"

BigInteger::BigInteger(unsigned int num)
{
	string temp;
	ostringstream sout;
	sout << num;
	temp = sout.str();
	for (int i = 0; i < temp.length(); i++)
	{
		this->m_num.push_front(temp[i]);
	}

}
BigInteger::BigInteger(string num)
{
	for (int i = 0; i < num.length(); i++)
	{
		if (num[i] >= '0'&&num[i] <= '9')
			this->m_num.push_front(num[i]);
	}
}
BigInteger::BigInteger(BigInteger & num)
{
	this->m_num = num.m_num;
}
BigInteger& BigInteger::operator=(unsigned int num)
{
	BigInteger temp((unsigned int)num);
	this->m_num = temp.m_num;
	return *this;
}
BigInteger& BigInteger::operator=(string num)
{
	BigInteger temp(num);
	this->m_num = temp.m_num;
	return *this;
}
BigInteger& BigInteger::operator=(BigInteger & num)
{
	this->m_num = num.m_num;
	return *this;
}
BigInteger BigInteger::operator+(BigInteger & num)
{
	BigInteger temp;
	temp.m_num.clear();
	int upper = 0;
	deque<char>::iterator self = this->m_num.begin();
	deque<char>::iterator out = num.m_num.begin();
	while (self != this->m_num.end() && out != num.m_num.end())
	{
		int sum = (*self - '0') + (*out - '0') + upper;
		upper = sum / 10;
		sum = sum % 10;
		temp.m_num.push_back(sum + '0');
		self++;
		out++;
	}
	while (self != this->m_num.end())
	{
		int sum = (*self - '0') + upper;
		upper = sum / 10;
		sum = sum % 10;
		temp.m_num.push_back(sum + '0');
		self++;
	}
	while (out != num.m_num.end())
	{
		int sum = (*out - '0') + upper;
		upper = sum / 10;
		sum = sum % 10;
		temp.m_num.push_back(sum + '0');
		out++;
	}
	if (upper != 0)
		temp.m_num.push_back(upper + '0');
	return temp;
}
bool BigInteger::operator!=(BigInteger & num)
{
	return !(*this == num);
}
bool BigInteger::operator==(BigInteger & num)
{
	if (this->m_num.size() != num.m_num.size())
		return false;
	int j = 0;
	for (deque<char>::iterator i = this->m_num.begin(); i != this->m_num.end(); i++)
	{
		if (*i != num.m_num[j++])
			return false;
	}
	return true;
}
ostream & operator<<(ostream &out, BigInteger & num)
{
	string temp;
	deque<char> ptp;
	int j = 0;
	for (deque<char>::iterator i = num.m_num.begin(); i != num.m_num.end(); i++)
	{
		ptp.push_front(*i);
		j++;
		if (j == 3)
		{
			j = 0;
			ptp.push_front(',');
		}
	}
	if (ptp.front() == ',')
		ptp.pop_front();
	for (deque<char>::iterator i = ptp.begin(); i != ptp.end(); i++)
	{
		temp.push_back(*i);
	}
	out << temp;
	return out;
}
BigInteger BigInteger::operator + (unsigned int  num)
{
	return *this + BigInteger(num);
}
BigInteger BigInteger::operator*(unsigned int  num)
{
	return *this*BigInteger(num);
}
BigInteger BigInteger::operator*(BigInteger & num)
{
	BigInteger result=0;
	result.m_num.resize(this->m_num.size()+num.m_num.size()+2,'0');
	for (int i = 0; i < num.m_num.size(); i++)
	{
		int upper = 0;
		int j = 0;
		for (j = 0; j < this->m_num.size(); j++)
		{
			int sum = (num.m_num[i]-'0') * (this->m_num[j]-'0') + upper+(result.m_num[i+j]-'0');
			upper = sum / 10;
			sum = sum % 10;
			result.m_num[i + j] = sum + '0';
		}
		if (upper != 0)
		{
			result.m_num[i + j] = upper + '0';
		}
	}
	string tps=result.toString();
	for (int i = 0; i < tps.length(); i++)
	{
		if (tps[i] != '0')
		{
			result.m_num.resize(result.m_num.size()-i);
			break;
		}	
	}
	return result;
}

BigInteger& BigInteger::operator++()
{
	*this = (*this) + BigInteger(1);
	return *this;
}
BigInteger BigInteger::operator++(int)
{
	BigInteger ret = *this;
	*this = *this + BigInteger(1);
	return ret;
}
string BigInteger::toString()
{
	string temp;
	deque<char> ptp;
	for (deque<char>::iterator i = this->m_num.begin(); i != this->m_num.end(); i++)
	{
		ptp.push_front(*i);
	}
	for (deque<char>::iterator i = ptp.begin(); i != ptp.end(); i++)
	{
		temp.push_back(*i);
	}
	return temp;
}
BigInteger BigInteger::pow(BigInteger & n)
{
	BigInteger bresult = 1;
	for (BigInteger i = 0; i < n; i++)
	{
		bresult *= (*this);
	}
	return bresult;
}
BigInteger BigInteger::pow(unsigned int  n)
{
	return pow(BigInteger(n));
}
BigInteger BigInteger::factorial()
{
	BigInteger bresult = 1;
	for (BigInteger i = 1; i <=*this; i ++)
	{
		bresult *= i;
	}
	return bresult;
}
bool BigInteger::operator>(BigInteger & num)
{
	string pthis = this->toString();
	string pnum = num.toString();
	if (pthis.length() > pnum.length())
		return true;
	else if (pthis.length() < pnum.length())
		return false;
	else
	{
		for (int i = 0; i < pthis.length(); i++)
		{
			if (pthis[i]>pnum[i])
				return true;
			else if (pthis[i] < pnum[i])
				return false;
		}
		return false;
	}
}
bool BigInteger::operator<(BigInteger & num)
{
	string pthis = this->toString();
	string pnum = num.toString();
	if (pthis.length() < pnum.length())
		return true;
	else if (pthis.length() > pnum.length())
		return false;
	else
	{
		for (int i = 0; i < pthis.length(); i++)
		{
			if (pthis[i]<pnum[i])
				return true;
			else if (pthis[i] > pnum[i])
				return false;
		}
		return false;
	}

}
bool BigInteger::operator>=(BigInteger & num)
{
	string pthis = this->toString();
	string pnum = num.toString();
	if (pthis.length() > pnum.length())
		return true;
	else if (pthis.length() < pnum.length())
		return false;
	else
	{
		for (int i = 0; i < pthis.length(); i++)
		{
			if (pthis[i]>pnum[i])
				return true;
			else if (pthis[i] < pnum[i])
				return false;
		}
		return true;

	}
	
}
bool BigInteger::operator<=(BigInteger & num)
{
	string pthis = this->toString();
	string pnum = num.toString();
	if (pthis.length() < pnum.length())
		return true;
	else if (pthis.length() > pnum.length())
		return false;
	else
	{
		for (int i = 0; i < pthis.length(); i++)
		{
			if (pthis[i]<pnum[i])
				return true;
			else if (pthis[i] > pnum[i])
				return false;
		}
		return true;

	}
}
bool BigInteger::operator==(unsigned int num)
{
	return *this == BigInteger(num);
}
bool BigInteger::operator!=(unsigned int num)
{
	return *this != BigInteger(num);
}
bool BigInteger::operator>(unsigned int num)
{
	return *this > BigInteger(num);
}
bool BigInteger::operator<(unsigned int num)
{
	return *this < BigInteger(num);
}
bool BigInteger::operator>=(unsigned int num)
{
	return *this >= BigInteger(num);
}
bool BigInteger::operator<=(unsigned int num)
{
	return *this <= BigInteger(num);
}
BigInteger& BigInteger::operator+=(BigInteger & num)
{
	*this = *this + num;
	return *this;
}
BigInteger& BigInteger::operator+=(unsigned int  num)
{
	*this = *this + BigInteger(num);
	return *this;
}
BigInteger& BigInteger::operator*=(BigInteger & num)
{
	*this = *this * num;
	return *this;
}
BigInteger& BigInteger::operator*=(unsigned int  num)
{
	*this = *this * BigInteger(num);
	return *this;
}
int BigInteger::toInt()
{
	int num = 0;
	string pnum = this->toString();
	for (int i = 0; i < pnum.length(); i++)
	{
		num *= 10;
		num += pnum[i] - '0';
	}
	return num;
}
double BigInteger::toDouble()
{
	double num = 0;
	string pnum = this->toString();
	for (int i = 0; i < pnum.length(); i++)
	{
		num *= 10;
		num += pnum[i] - '0';
	}
	return num;
}
BigInteger BigInteger::operator << (BigInteger & num)
{
	BigInteger ret = *this;
	for (BigInteger i = 0; i < num; i++)
	{
		ret.m_num.push_front('0');
	}
	return ret;
}
BigInteger BigInteger::operator<<(unsigned int num)
{
	BigInteger ret = *this;
	for (int i = 0; i < num; i++)
	{
		ret.m_num.push_front('0');
	}
	return ret;
}

BigInteger BigInteger::operator>>(BigInteger & num)
{
	BigInteger ret = *this;
	for (BigInteger i = 0; i < num; i++)
	{
		if (ret.m_num.empty())
		{
			ret.m_num.push_front('0');
			break;
		}
		ret.m_num.pop_front();
	}
	return ret;
}
BigInteger BigInteger::operator>>(unsigned int num)
{
	BigInteger ret = *this;
	for (int i = 0; i < num; i++)
	{
		if (ret.m_num.empty())
		{
			ret.m_num.push_front('0');
			break;
		}
		ret.m_num.pop_front();
	}
	return ret;
}
BigInteger BigInteger::operator~()
{
	BigInteger ret = *this;
	for (deque<char>::iterator i = ret.m_num.begin(); i != ret.m_num.end(); i++)
	{
		*i = (9 - (*i - '0')) + '0';
	}
	return ret;
}
BigInteger  BigInteger::operator-(BigInteger & num)
{
	return BigInteger(Sub(num));
}
string BigInteger::Sub(BigInteger & num)
{
	string pthis = this->toString();
	string pnum = num.toString();
	BigInteger mthis = *this;
	BigInteger mnum = num;
	if (pthis.length() > pnum.length())
	{
		for (int i = 0; i < pthis.length() - pnum.length(); i++)
		{
			mnum.m_num.push_back('0');
		}
	}
	else if (pthis.length() < pnum.length())
	{
		for (int i = 0; i < pnum.length() - pthis.length(); i++)
		{
			mthis.m_num.push_back('0');
		}
	}
	mthis.m_num.push_back('0');
	mnum = ~mnum;
	mnum.m_num.push_back('1');
	mnum++;
	BigInteger sum = mthis + mnum;
	int maxlen = pthis.length() > pnum.length() ? pthis.length() : pnum.length();
	char dona = '+';
	if ((sum.m_num[maxlen] - '0') % 2 == 0)
		dona = sum.m_num[maxlen] = '+';
	else
	{
		sum = ~sum + 1;
		dona = sum.m_num[maxlen] = '-';
	}
	while (true)
	{
		if (sum.m_num.empty())
		{
			sum.m_num.push_back('0');
			break;
		}
		if (sum.m_num.back() == '+' || sum.m_num.back() == '-')
		{
			sum.m_num.pop_back();
		}
		if (sum.m_num.back() != '0')
		{
			break;
		}
		else
		{
			sum.m_num.pop_back();
		}

	}
	sum.m_num.push_back(dona);
	return sum.toString();
}
BigInteger BigInteger::operator-(unsigned int num)
{
	return *this - BigInteger(num);
}
BigInteger& BigInteger::operator-=(BigInteger & num)
{
	*this=*this - num;
	return *this;
}
BigInteger& BigInteger::operator-=(unsigned int num)
{
	*this = *this - num;
	return *this;
}
BigInteger& BigInteger::operator--()
{
	*this = *this - BigInteger(1);
	return *this;
}
BigInteger BigInteger::operator--(int)
{
	BigInteger ret = *this;
	*this = *this - BigInteger(1);
	return ret;
}