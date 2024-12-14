#include"PrimeTable.h"
bool PrimeTable::IsPrimeNumber(int num)
{
	if (num <= 3)
	{
		if (num >= 2)
			return true;
		else
			return false;
	}
	if (num % 2 == 0)
		return false;
	if (num % 3 == 0)
		return false;
	for (int i = 5; i*i <= num; i += 6)
	{
		if (num%i == 0 || num % (i + 2) == 0)
			return false;
	}
	return true;
}
PrimeTable::PrimeTable(int Length)
{
	int i = 0;
	int count = 0;
	while (count < Length)
	{
		if (IsPrimeNumber(i))
		{
			this->m_table.push_back(i);
			count++;
		}
		i++;
		if (i < 0)
		{
			break;
		}
	}
}
PrimeTable::PrimeTable(int start, int end)
{
	int pstart = start;
	int pend = end;
	if (pstart < 0)
		pstart = 0;
	if (pend < 0)
		pend = 100;
	if (pstart < pend)
	{
		int ptemp = pstart;
		pstart = pend;
		pend = ptemp;
	}
	for (int i = pstart; i < pend; i++)
	{
		if (IsPrimeNumber(i))
		{
			this->m_table.push_back(i);
		}
	}
}
PrimeTable::PrimeTable(PrimeTable & table)
{
	this->m_table.clear();
	this->m_table = table.m_table;
}
PrimeTable& PrimeTable::operator=(PrimeTable & table)
{
	this->m_table.clear();
	this->m_table = table.m_table;
	return *this;
}
int PrimeTable::operator[](int index)
{
	if (index < 0 || index >= this->m_table.size())
		return -1;
	return this->m_table[index];
}
int PrimeTable::Size()
{
	return this->m_table.size();
}
int PrimeTable::Back()
{
	return this->m_table.back();
}
int PrimeTable::Front()
{
	return this->m_table.front();
}
void PrimeTable::Pop_front()
{
	if (!this->m_table.empty())
		this->m_table.pop_front();
}
void PrimeTable::Pop_back()
{
	if (!this->m_table.empty())
		this->m_table.pop_back();
}
bool PrimeTable::Empty()
{
	return this->m_table.empty();
}
void PrimeTable::Clear()
{
	this->m_table.clear();
}
void PrimeTable::ReSize(int size)
{
	if (size > 0)
	{
		if (size < this->m_table.size())
		{
			this->m_table.resize(size);
		}
		else
		{
			int tail = this->m_table.back()+1;
			int count = size - (this->m_table.size());
			int i = 0;
			while (i < count)
			{
				if (IsPrimeNumber(tail))
				{
					i++;
					this->m_table.push_back(tail);
				}
				tail++;
				if (tail < 0)
				{
					return;
				}
			}
		}
	}
}
void PrimeTable::ReStart(int start)
{
	if (start < 0)
		return;
	int psize = this->m_table.size();
	int pnum = start;
	int i = 0;
	while (i < psize)
	{
		if (IsPrimeNumber(pnum))
		{
			this->m_table[i] = pnum;
			i++;
		}
		pnum++;
		if (pnum < 0)
		{
			this->m_table.resize(i);
			break;
		}
	}
}
bool PrimeTable::In(int num)
{
	if (num < 0 || this->Empty())
		return false;
	if (IsPrimeNumber(num))
	{
		if (num >= this->Front() && num <= this->Back())
			return true;
		else
			return false;
	}
	else
		return false;
}
int PrimeTable::ValueAtIndex(int index)
{
	return (*this)[index];
}
int PrimeTable::IndexAtValue(int num)
{
	int i = 0;
	while ((*this)[i] != num)
	{
		i++;
		if ((*this)[i] == -1)
		{
			i = -1;
			break;
		}	
	}
	return i;
}