#ifndef _ALGO_CONTAINER_HPP_
#define _ALGO_CONTAINER_HPP_
/********************************************
* 模块：通用容器模块
* author：Ugex.Savelar
*********************************************/
#include<stdlib.h>
/*
列表容器，采用双向链表实现,包含一个尾指针
由于是模板类，如果要分离申明和实现的话
实现部分的函数也要指明参数列表
默认添加是尾部添加

实现：
带首尾指针的双向链表，内部包含一个动态维护的链表中间指针（及其下标）
这样就能够实现
元素的索引查找平均在链表总长度的四分之一，
直接元素查找能到达平均二分之一
从而提高查找效率

四分之一由来：
首指针		中间指针		尾指针
加入已知需要查找的下标在首指针和中间指针之间
那么计算目标下标距离首指针和中间指针哪一个更近
按照近的一方进行遍历查找元素，因此距离最近的话，最大也就是四分之一的总长度距离

二分之一由来：
同样，由于是元素需要逐个比较
因此，采用四个分组同时遍历，这样就能缩短大多数的元素查找时间
首指针到中间指针，中间指针到首指针，中间指针到尾指针，尾指针到中间指针
*/
template<typename T, typename E>
class AlgoList
{
protected:
	typedef struct _node
	{
		T data;
		struct _node * next;
		struct _node * previous;
	}Node;
public:
	AlgoList()
	{
		m_root = NULL;
		InitNode();
	}
	//复制构造和复制运算，一定要写上，不然连debug都可能找不到错在哪里
	//这是一个血的教训，报错：BLOCK_TYPE_IS_VALID(pHead->nBlockUse)
	AlgoList(const AlgoList & arr)
	{
		m_root = NULL;
		InitNode();

		Node * p = arr.m_root->next;
		while (p)
		{
			add(p->data);
			p = p->next;
		}
		
	}
	AlgoList & operator=(const AlgoList & arr)
	{
		this->clear();
		
		Node * p = arr.m_root->next;
		while (p)
		{
			add(p->data);
			p = p->next;
		}

		return *this;
	}
	AlgoList & operator+(T data)
	{
		add(data);
		return *this;
	}
	AlgoList & operator+(const AlgoList & arr)
	{
		addAll(arr);
		return *this;
	}
	AlgoList & operator+=(T data)
	{
		add(data);
		return *this;
	}
	AlgoList & operator+=(const AlgoList & arr)
	{
		addAll(arr);
		return *this;
	}
	AlgoList & addAll(const T * arr,E count)
	{
		for (E i = 0; i < count; i++)
		{
			add(arr[i]);
		}
		return *this;
	}
	template<typename FuncCmp>
	AlgoList & removeAllRepeat(FuncCmp cmp)
	{
		if (m_size <= 1)
			return *this;

		Node * cur = m_root->next;
		E len = 0;
		while (cur)
		{
			Node * np = cur->next;
			while (np)
			{
				if (cmp(cur->data, np->data) == 0)
				{
					Node * del = np;
					Node * dp = del->previous;
					Node * dc = del->next;

					delete del;
					dp->next = dc;
					if (dc)
						dc->previous = dp;

					np = dc;
				}
				else
				{
					np = np->next;
				}
			}
			m_tail = cur;
			cur = cur->next;
			len++;
		}

		m_size = len;
		directReCalculCenter();
		return *this;
	}
	AlgoList & addAll(const AlgoList & arr)
	{
		Node * cur = arr.m_root->next;
		while (cur)
		{
			add(cur->data);
			cur = cur->next;
		}
		return *this;
	}
	AlgoList & addRepeat(T data, E count)
	{
		if (count <= 0)
			return *this;
		for (E i = 0; i < count; i++)
		{
			add(data);
		}
		return *this;
	}
	AlgoList & add(T data)
	{
		Node * cur = createNode();
		cur->data = data;
		Node * end = m_tail;
		cur->previous = end;
		end->next = cur;
		m_tail = cur;
		++m_size;
		notifyUpdateCenter();
		return *this;
	}
	bool insert(E index, T data)
	{
		Node * p = getIndexNode(index);
		if (p == NULL)
			return false;
		Node * parent = p->previous;
		Node * child = p;
		Node * cur = createNode();
		cur->data = data;
		cur->previous = parent;
		parent->next = cur;
		cur->next = child;
		if (child != NULL)
			child->previous = cur;
		else
			m_tail = cur;
		++m_size;
		if (index <= m_centerIndex)
		{
			if (index == m_centerIndex)
				m_center = cur;
			else
				m_center = m_center->previous;
		}
		notifyUpdateCenter();
		return true;
	}
	T replace(E index, T data)
	{
		Node * p = getIndexNode(index);
		T ret = p->data;
		p->data = data;
		return ret;
	}
	T& get(E index)
	{
		Node * p = getIndexNode(index);
		return p->data;
	}
	E size()
	{
		return m_size;
	}
	bool remove(E index, T * delData)
	{
		Node * del = getIndexNode(index);
		if (del == NULL)
			return false;
		if (delData != NULL)
			*delData = del->data;
		Node * parent = del->previous;
		Node * child = del->next;
		parent->next = child;
		if (child != NULL)
			child->previous = parent;
		else
			m_tail = parent;
		if (index <= m_centerIndex)
		{
			if (index == m_centerIndex)
				m_center = child;
			else
				m_center = m_center->next;
		}
		delete del;
		--m_size;
		notifyUpdateCenter();
		return true;
	}
	template<typename FuncCmp>
	bool remove(T data, T * delData, FuncCmp cmp)
	{
		if (cmp == NULL)
			return false;
		E pindex = -1;
		Node * p = getDataNode(data, &pindex, cmp);
		if (p == NULL)
			return false;

		if (delData != NULL)
			*delData = p->data;
		Node * parent = p->previous;
		Node * child = p->next;
		parent->next = child;
		if (child != NULL)
			child->previous = parent;
		else
			m_tail = parent;
		if (pindex <= m_centerIndex)
		{
			if (pindex == m_centerIndex)
				m_center = child;
			else
				m_center = m_center->next;
		}
		delete p;
		--m_size;
		notifyUpdateCenter();
		return true;
	}
	AlgoList & clear()
	{
		Node * p = m_root->next;
		if (p)
		{
			while (p)
			{
				Node * np = p->next;
				delete p;
				p = np;
			}
		}
		m_root->next = NULL;
		m_size = 0;
		InitNode();
		notifyUpdateCenter();
		return *this;
	}
	bool setCursorToBegin()
	{
		m_cur = m_root->next;
		return true;
	}
	bool setCursorToEnd()
	{
		m_cur = m_tail;
		return true;
	}
	bool setCursorPos(E index)
	{
		Node * p = getIndexNode(index);
		if (p == NULL)
		{
			return false;
		}
		m_cur = p;
		return true;
	}
	bool hasPrevious()
	{
		if (m_cur == NULL || m_cur == m_root)
			return false;
		return true;
	}
	bool hasNext()
	{
		if (m_cur == NULL)
			return false;
		return true;
	}
	T & getCursorData()
	{
		return m_cur->data;
	}
	T & getPrevious()
	{
		Node * p = m_cur;
		m_cur = m_cur->previous;
		return p->data;
	}
	T & getNext()
	{
		Node * p = m_cur;
		m_cur = m_cur->next;
		return p->data;
	}
	bool clearCursor()
	{
		m_cur = NULL;
		return true;
	}
	template<typename FuncCmp>
	bool contains(T data, FuncCmp cmp) 
	{
		if (cmp == NULL)
			return false;
		E pindex = -1;
		Node * p = getDataNode(data, &pindex, cmp);
		if (p != NULL)
			return true;
		return false;
	}
	bool push(T data)
	{
		Node * end = m_tail;
		Node * cur = createNode();
		cur->data = data;
		cur->previous = end;
		end->next = cur;
		m_tail = cur;
		++m_size;
		notifyUpdateCenter();
		return true;
	}
	T pop()
	{
		Node * end = m_tail;
		T ret = end->data;
		Node * parent = end->previous;
		parent->next = NULL;
		if (m_center == m_tail)
		{
			m_center = parent;
			m_centerIndex--;
		}
		m_tail = parent;
		delete end;
		--m_size;
		notifyUpdateCenter();
		return ret;
	}
	T& top()
	{
		return m_tail->data;
	}
	virtual ~AlgoList()
	{
		this->clear();
		if (m_root != NULL)
		{
			delete m_root;
			m_root = NULL;
		}
		m_tail = m_root;
		m_cur = NULL;
		m_size = 0;
	}
	T * toArray(E * count)
	{
		*count = m_size;
		T * ret = new T[*count];
		E index = 0;
		Node * p = m_root->next;
		while (p)
		{
			ret[index++] = p->data;
			p = p->next;
		}
		return ret;
	}
	void freeArray(T * arr)
	{
		delete[] arr;
	}
	template<typename D,typename FuncSelGet>
	void addAll(D * data, E beginIndex, E endIndex, FuncSelGet selGet)
	{
		for (; beginIndex <= endIndex; beginIndex++)
		{
			Node * end = m_tail;
			Node * cur = createNode();
			cur->data = selGet(data, beginIndex);
			cur->previous = end;
			end->next = cur;
			m_tail = cur;
			++m_size;
			notifyUpdateCenter();
		}
	}
	bool enque(T data)
	{
		return push(data);
	}
	T deque()
	{
		T ret;
		remove(0, &ret);
		return ret;
	}
	bool isEmpty() const
	{
		return m_size == 0;
	}
	T& front()
	{
		return m_root->next->data;
	}
	T& back()
	{
		return m_tail->data;
	}
	bool pushFront(T data)
	{
		return insert(0, data);
	}
	bool pushBack(T data)
	{
		return push(data);
	}
	bool first2End()
	{
		if (m_size <= 1)
			return false;
		T data;
		remove(0, &data);
		add(data);
		return true;
	}
	bool end2First()
	{
		if (m_size <= 1)
			return false;
		T data;
		remove(m_size-1,&data);
		insert(0, data);
		return true;
	}
	template<typename FuncExec>
	AlgoList & range(FuncExec exec)
	{
		Node * p = m_root->next;
		while (p)
		{
			exec(p->data);
			p = p->next;
		}
		return *this;
	}
	template<typename FuncRange>
	AlgoList & rangePlus(FuncRange ran)
	{
		Node * p = m_root->next;
		E index = 0;
		while (p)
		{
			bool isFirst = false;
			bool isEnd = false;
			if (p == m_root->next)
				isFirst = true;
			if (p->next == NULL)
				isEnd = true;
			ran(p->data, index++, isFirst, isEnd);
			p = p->next;
		}
		return *this;
	}
	template<typename FuncFilter>
	AlgoList & addAllFilter(const AlgoList & lst, FuncFilter filter)
	{
		Node * p = lst.m_root->next;
		while (p)
		{
			if (filter(p->data) == true)
			{
				push(p->data);
			}
			p = p->next;
		}
		return *this;
	}
	template<typename FuncFilter>
	AlgoList & addAllFilter(const T * arr,E count, FuncFilter filter)
	{
		for (E i = 0; i < count;i++)
		{
			if (filter(arr[i]) == true)
			{
				push(arr[i]);
			}
		}
		return *this;
	}
protected:
	Node * m_root;
	Node * m_tail;
	Node * m_cur;
	E m_size;

	Node * m_center;
	E m_centerIndex;
	/*直接重算中心位置，适用于大量元素操作之后，无法进行简单偏移完成时，使用量较少，或者不建议使用*/
	void directReCalculCenter()
	{
		if (m_size == 0)
		{
			m_center = NULL;
			m_centerIndex = -1;
		}
		else if (m_size == 1 || m_size == 2)
		{
			m_center = m_root->next;
			m_centerIndex = 0;
		}
		else
		{
			E newPos = (m_size - 1) / 2;
			m_centerIndex = 0;
			m_center = m_root->next;
			while (m_centerIndex <= newPos)
			{
				m_center = m_center->next;
				m_centerIndex++;
			}

		}
	}
	/*更新中心位置，针对单一或者少量明确元素操作之后，效率高，推荐使用*/
	void notifyUpdateCenter()
	{
		if (m_size == 0)
		{
			m_center = NULL;
			m_centerIndex = -1;
			return;
		}
		else if (m_size == 1 || m_size == 2)
		{
			m_center = m_root->next;
			m_centerIndex = 0;
			return;
		}

		E newPos = (m_size - 1) / 2;
		if (newPos == m_centerIndex)
			return;
		if (m_centerIndex < newPos)
		{
			while (m_centerIndex <= newPos)
			{
				m_center = m_center->next;
				m_centerIndex++;
			}
		}
		else
		{
			while (m_centerIndex >= newPos)
			{
				m_center = m_center->previous;
				m_centerIndex--;
			}
		}
	}

	void InitNode()
	{
		if (m_root != NULL)
		{
			delete[] m_root;
			m_root = NULL;
		}
		m_root = createNode();
		m_tail = m_root;
		m_cur = NULL;
		m_size = 0;
		notifyUpdateCenter();
	}
	Node * createNode()
	{
		Node * node = new Node;
		node->next = NULL;
		node->next = NULL;
		return node;
	}
	template<typename FuncCmp>
	Node * getDataNode(T & data, E * index, FuncCmp cmp)
	{
		if (m_center == NULL)
		{
			Node * present = m_root->next;
			E i = 0;
			while (present)
			{
				if (cmp(data, present->data) == 0)
				{
					*index = i;
					return present;
				}
				i++;
				present = present->next;
			}
			return NULL;
		}

		E left = 0;
		E leftMid = m_centerIndex;
		E right = m_size - 1;
		E rightMid = m_centerIndex + 1;

		Node * pleft = m_root->next;
		Node * pleftMid = m_center;
		Node * pright = m_tail;
		Node * prightMid = m_center->next;
		bool leftRun = true, rightRun = true;
		while (leftRun || rightRun)
		{
			leftRun = false;
			rightRun = false;

			if (left <= leftMid)
			{
				if (pleft)
				{
					if (cmp(data, pleft->data) == 0)
					{
						return pleft;
					}
				}
				pleft = pleft->next;
				left++;
				if (pleftMid)
				{
					if (cmp(data, pleftMid->data) == 0)
					{
						return pleftMid;
					}
				}
				pleftMid = pleftMid->previous;
				leftMid--;

				leftRun = true;
			}

			/////////////////////////

			if (rightMid <= right)
			{
				if (prightMid)
				{
					if (cmp(data, prightMid->data) == 0)
					{
						return prightMid;
					}
				}
				prightMid = prightMid->next;
				rightMid++;
				if (pright)
				{
					if (cmp(data, pright->data) == 0)
					{
						return pright;
					}
				}
				pright = pright->previous;
				right--;

				rightRun = true;
			}
		}
		return NULL;
	}
	Node * getIndexNode(E index)
	{
		if (index < 0 || index >= m_size)
			return NULL;
		if (index == 0)
			return m_root->next;
		if (index == m_size - 1)
			return m_tail;
		if (index == m_centerIndex)
			return m_center;

		if (m_center == NULL)
		{
			Node * present = m_root;
			E i = -1;
			while (present)
			{
				if (i == index)
				{
					return present;
				}
				i++;
				present = present->next;
			}
			return NULL;
		}

		bool isLeftRun = true;
		Node * p = NULL;
		Node * pout = NULL;
		E pi = -1;
		if (index < m_centerIndex)
		{
			isLeftRun = ((m_centerIndex - index)>(index));
			if (isLeftRun)
			{
				pi = 0;
				p = m_root->next;
				pout = m_center;
			}
			else
			{
				pi = m_centerIndex - 1;
				p = m_center->previous;
				pout = m_root;
			}

		}
		else
		{
			isLeftRun = ((m_size - index)>(index - m_centerIndex));
			if (isLeftRun)
			{
				pi = m_centerIndex;
				p = m_center;
				pout = NULL;
			}
			else
			{
				pi = m_size - 1;
				p = m_tail;
				pout = m_center->previous;
			}
		}
		while (p != pout)
		{
			if (pi == index)
			{
				return p;
			}
			if (isLeftRun)
			{
				p = p->next;
				pi++;
			}
			else
			{
				p = p->previous;
				pi--;
			}
		}
		return NULL;
	}
};
template<typename D, typename T, typename E>
T & AlgoListSelectGet(D * data, E index)
{
	return data->get(index);
}
template<typename D, typename T, typename E>
void AlgoListSelectSet(D * data, E index, T value)
{
	data->replace(index, value);
}
template<typename D, typename T, typename E>
void AlgoListSelectSwap(D * data, E indexA, E indexB)
{
	T pa = data->get(indexA);
	T pb = data->get(indexB);
	data->replace(indexA, pb);
	data->replace(indexB, pa);
}
template<typename T, typename E>
class AlgoArray
{
public:
	AlgoArray()
	{
		m_data = NULL;
		m_capital = 64;
		InitArray();
	}
	AlgoArray(E capital)
	{
		m_data = NULL;
		m_capital = capital;
		InitArray();
	}
	AlgoArray(const AlgoArray & arr)
	{
		m_data = NULL;
		m_capital = 64;
		InitArray();

		E nsize = arr.m_size;
		extendCapital(nsize + 1);
		for (E i = 0; i < nsize; i++)
		{
			m_data[i] = arr.m_data[i];
		}
	}
	AlgoArray & operator=(const AlgoArray & arr)
	{
		E nsize = arr.m_size;
		extendCapital(nsize + 1);
		for (E i = 0; i < nsize; i++)
		{
			m_data[i] = arr.m_data[i];
		}
		return *this;
	}
	AlgoArray & operator+(T data)
	{
		push(data);
		return *this;
	}
	AlgoArray & operator+=(T data)
	{
		push(data);
		return *this;
	}
	AlgoArray & operator+(const AlgoArray & arr)
	{
		for (E i = 0; i < arr.m_size; i++)
		{
			push(arr.m_data[i]);
		}
		return *this;
	}
	AlgoArray & operator+=(const AlgoArray & arr)
	{
		for (E i = 0; i < arr.m_size; i++)
		{
			push(arr.m_data[i]);
		}
		return *this;
	}
	AlgoArray & addAll(T * data, E count)
	{
		for (E i = 0; i < count; i++)
		{
			push(data[i]);
		}
		return *this;
	}
	AlgoArray & addRepeat(T data, E count)
	{
		if (count <= 0)
			return *this;

		for (E i = 0; i < count; i++)
			push(data);
		return *this;
	}
	template<typename D, typename FuncSelGet>
	AlgoArray & addAll(D * data, E beginIndex, E endIndex, FuncSelGet selGet)
	{
		for (; beginIndex <= endIndex; beginIndex++)
		{
			push(selGet(data, beginIndex));
		}
		return *this;
	}
	AlgoArray & push(T data)
	{
		extendCapital(m_size);
		m_data[m_size] = data;
		m_size++;
		return *this;
	}
	T pop()
	{
		E index = m_size - 1;
		m_size--;
		return m_data[index];
	}
	T& top()
	{
		return m_data[m_size - 1];
	}
	T& operator[](E index)
	{
		extendCapital(index);
		if (index >= m_size)
		{
			m_size = index + 1;
		}
		return m_data[index];
	}
	T* getData()
	{
		return m_data;
	}
	E size()
	{
		return m_size;
	}
	E capital()
	{
		return m_capital;
	}
	AlgoArray & setSize(E size)
	{
		if (size < 0)
			return *this;
		if (size>=m_capital)
			extendCapital(size-1);

		m_size = size;
		return *this;
	}
	AlgoArray & shrinkCapital()
	{
		E len = m_size;
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
		return *this;
	}
	AlgoArray & memorySet(T value,bool onlySize=false)
	{
		if (onlySize)
			return memorySet(0, m_size - 1, value);
		else
			return memorySet(0, m_capital - 1, value);
	}
	AlgoArray & memorySet(E startIndex, E endIndex, T value)
	{
		for (E i = startIndex; i <= endIndex; i++)
		{
			extendCapital(startIndex);
			m_data[startIndex] = value;
		}
		return *this;
	}
	virtual ~AlgoArray()
	{
		if (m_data != NULL)
		{
			delete[] m_data;
			m_data = NULL;
		}
		m_size = 0;
		m_capital = 0;
	}
protected:
	E m_size;
	E m_capital;
	T * m_data;

	void InitArray()
	{
		if (m_capital <= 1)
			m_capital = 1;
		if (m_data != NULL)
		{
			delete[] m_data;
			m_data = NULL;
		}
		m_size = 0;
		m_data = new T[m_capital];
	}
	bool extendCapital(E index)
	{
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
			return true;
		}
		return false;
	}
};
template<typename T,typename FuncCmp>
class AlgoSortTree
{
private:
	typedef struct _node
	{
		T data;
		struct _node * lchild;
		struct _node * rchild;
	}Node;
public:
	AlgoSortTree(FuncCmp cmp)
	{
		m_root = NULL;
		comparator = cmp;
		InitTree();
	}
	AlgoSortTree(const AlgoSortTree & arr)
	{
		this->clear();

		copyToThis(arr.m_root);
	}
	AlgoSortTree & operator=(const AlgoSortTree & arr)
	{
		this->clear();

		copyToThis(arr.m_root);

		return *this;
	}
	bool add(T data)
	{
		if (m_root == NULL)
		{
			m_root = createNode();
			m_root->data = data;
			return true;
		}
		Node * tp = m_root, *fp = m_root;
		bool isLeft = true;
		while (tp)
		{
			if (comparator(data, tp->data) == 0)
			{
				return false;
			}
			else
			{
				fp = tp;
				if (comparator(data, tp->data) < 0)
				{
					tp = tp->lchild;
					isLeft = true;
				}
				else
				{
					tp = tp->rchild;
					isLeft = false;
				}
			}
		}
		Node * cur = createNode();
		cur->data = data;
		if (isLeft)
		{
			fp->lchild = cur;
		}
		else
		{
			fp->rchild = cur;
		}
		return true;
	}
	bool remove(T data)
	{
		Node * tp = m_root, *fp = m_root;// 当前节点指针，当前节点的父节点指针
		while (tp != NULL)
		{
			if (comparator(data, tp->data) == 0)// 查找成功
			{
				break;
			}
			else
			{
				fp = tp;
				if (comparator(data, tp->data) < 0)
					tp = tp->lchild;
				else
					tp = tp->rchild;
			}
		}
		if (tp == NULL)//没找到相应的键
			return false;
		if (tp == m_root)//如果找到的节点是根节点
		{
			if (tp->lchild != NULL) //如果根节点存在左子树则让左子树成为新根，否则右子树成为新根，都没有则删除树
			{
				tp = m_root;
				Node * mp, *up;
				mp = tp->rchild;
				up = tp->lchild;
				m_root = up;
				Node * rp = up->rchild, *frp = up;
				while (rp != NULL)
				{
					frp = rp;
					rp = rp->rchild;
				}
				frp->rchild = mp;
				delete tp;
			}
			else if (tp->rchild != NULL)
			{
				tp = m_root;
				Node * mp, *up;
				mp = tp->lchild;
				up = tp->rchild;
				m_root = up;
				Node * lp = up->lchild, *flp = up;
				while (lp != NULL)
				{
					flp = lp;
					lp = lp->lchild;
				}
				flp->lchild = mp;
				delete tp;
			}
			else
			{
				delete m_root;
				m_root = NULL;
			}
		}
		else if (tp == fp->lchild)//如果查找节点是其父节点的左子树
		{
			if (tp->lchild == NULL)//如果查找节点的左子树为空
			{
				fp->lchild = tp->rchild; //查找节点的右子树替换删除节点
				delete tp;
			}
			else
			{
				Node * mp, *up;//要移动的节点，往上替换的节点
				mp = tp->rchild;//如果是左子树，那么把移动子树就是查找节点的右子树
				up = tp->lchild;
				fp->lchild = up;//查找节点的左子树替换查找节点成为父节点的右子树
				Node * rp = up->rchild, *frp = up;//最右节点和最右节点的父节点
				while (rp != NULL)// 找到最右节点的父节点
				{
					frp = rp;
					rp = rp->rchild;
				}
				frp->rchild = mp;//最右节点的父节点的右子树变为移动的节点
				delete tp;
			}

		}
		else if (tp == fp->rchild)//如果查找节点是其父节点的右子树
		{
			if (tp->rchild == NULL)
			{
				fp->rchild = tp->lchild;
				delete tp;
			}
			else
			{
				Node * mp, *up;
				mp = tp->lchild;
				up = tp->rchild;
				fp->rchild = up;
				Node * lp = up->lchild, *flp = up;
				while (lp != NULL)// 找到最左节点的父节点
				{
					flp = lp;
					lp = lp->lchild;
				}
				flp->lchild = mp;//最左节点的父节点的左子树变为移动的节点
				delete tp;
			}
		}
		return true;
	}
	bool contians(T data)
	{
		Node * tp = m_root;
		while (tp)
		{
			if (comparator(data, tp->data) == 0)
			{
				return true;
			}
			else
			{
				if (comparator(data, tp->data) < 0)
					tp = tp->lchild;
				else
					tp = tp->rchild;
			}
		}
		return false;
	}
	template<typename FuncExec,typename FuncOn>
	void range(FuncExec exec,FuncOn onBegin,FuncOn onEnd)
	{
		onBegin();
		tranform(m_root, exec);
		onEnd();
	}
	bool clear()
	{
		Node * node = m_root;
		m_root = NULL;
		clearAll(node);
		return true;
	}
	~AlgoSortTree()
	{
		this->clear();
	}
protected:
	Node * m_root;
	FuncCmp comparator;
	void copyToThis(Node* tree)
	{
		if (tree == NULL)
			return;
		add(tree->data);
		copyToThis(tree->lchild);
		copyToThis(tree->rchild);
	}
	void clearAll(Node * node)
	{
		if (node == NULL)
			return;
		Node * lc = node->lchild;
		Node * rc = node->rchild;
		delete node;
		clearAll(lc);
		clearAll(rc);
	}
	template<typename FuncExec>
	void tranform(Node * node, FuncExec exec)
	{
		if (node == NULL)
			return;
		tranform(node->lchild, exec);
		exec(node->data);
		tranform(node->rchild, exec);
	}
	Node * createNode()
	{
		Node * node = new Node();
		node->lchild = NULL;
		node->rchild = NULL;
		return node;
	}
	void InitTree()
	{
		if (m_root != NULL)
		{
			delete m_root;
			m_root = NULL;
		}
		m_root = NULL;
	}
};

template<typename T,typename E>
class AlgoPair
{
public:
	AlgoPair(){}
	AlgoPair(T key, E value)
	{
		this->key = key;
		this->value = value;
	}
	AlgoPair(const AlgoPair & pair)
	{
		this->key = pair.key;
		this->value = pair.value;
	}
	AlgoPair& operator=(const AlgoPair & pair)
	{
		this->key = pair.key;
		this->value = pair.value;
		return *this;
	}
	T key;
	E value;
};

template<typename T, typename E,typename FuncCmp>
class AlgoMap
{
public:
	AlgoMap(FuncCmp keyCmp)
	{
		cmpKey = keyCmp;
		InitMap();
	}
	AlgoMap(const AlgoMap & arr)
	{
		this->clear();

		for (E i = 0; i < arr.m_data->size(); i++)
		{
			m_data.add(arr.m_data->get(i));
		}
	}
	AlgoMap & operator=(const AlgoMap & arr)
	{
		this->clear();

		for (E i = 0; i < arr.m_data->size(); i++)
		{
			m_data.add(arr.m_data->get(i));
		}

		return *this;
	}
	bool put(T key, E value)
	{
		int front = 0, back = m_data.size() - 1;
		while (front <= back)
		{
			AlgoPair<T, E> node = m_data.get(front);
			if (cmpKey(node.key, key) == 0)
			{
				node.value = value;
				m_data.replace(front, node);
				return true;
			}
			node = m_data.get(back);
			if (cmpKey(node.key, key) == 0)
			{
				node.value = value;
				m_data.replace(back, node);
				return true;
			}
			front++;
			back--;
		}
		AlgoPair<T, E> node(key,value);
		m_data.add(node);
		return true;
	}
	E& get(T key)
	{
		int front = 0, back = m_data.size() - 1;
		while (front <= back)
		{
			AlgoPair<T,E> node = m_data.get(front);
			if (cmpKey(m_data.get(front).key, key) == 0)
			{
				return m_data.get(front).value;
			}
			node = m_data.get(back);
			if (cmpKey(m_data.get(back).key, key) == 0)
			{
				return m_data.get(back).value;
			}
			front++;
			back--;
		}
	}
	bool remove(T key)
	{
		int front = 0, back = m_data.size() - 1;
		while (front <= back)
		{
			AlgoPair<T, E> node = m_data.get(front);
			if (cmpKey(m_data.get(front).key, key) == 0)
			{
				m_data.remove(front, NULL);
				return true;
			}
			node = m_data.get(back);
			if (cmpKey(m_data.get(back).key, key) == 0)
			{
				m_data.remove(back, NULL);
				return true;
			}
			front++;
			back--;
		}
		return false;
	}
	int size()
	{
		return m_data.size();
	}
	AlgoPair<T, E> getIndexPair(int index)
	{
		return m_data.get(index);
	}
	T getIndexKey(int index)
	{
		return m_data.get(index).key;
	}
	T& getIndexValue(int index)
	{
		return m_data.get(index).value;
	}
	void clear()
	{
		m_data.clear();
	}
	~AlgoMap()
	{
		m_data.clear();
	}
protected:
	AlgoList<AlgoPair<T,E>, int> m_data;
	FuncCmp cmpKey;

	void InitMap()
	{
		m_data.clear();
	}
};

#endif // _ALGO_CONTAINER_HPP_