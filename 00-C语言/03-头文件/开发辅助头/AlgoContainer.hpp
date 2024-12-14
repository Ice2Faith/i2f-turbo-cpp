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
	T & operator[](E index)
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
	/*
	Cursor族函数：
		好处：
			不会由于使用下标方式带来的性能损失，使用下标方式需要不断的遍历链表去查找对应的下标，从而造成性能损失
			而使用游标的方式，将不会造成性能损失，因为只是双向链表的指针变动，不涉及下标遍历查找
			对于使用来说，仅仅关注了游标本身，链表的结构变得透明起来，不用去管下标等事情
		坏处：
			你只能修改或者删除遍历到的元素，并不能进行添加操作，也不知道操作的下标
			虽然过程中你依然能够进行插入（使用其他函数），但是不会影响到下标的移动
			毕竟你在游标之前插入和之后插入，对于游标来说，都只是关注游标本身，前后的变化都是透明的，无影响的
		注意：
			游标操作时，对于删除而言，需要使用游标组函数的删除函数来删除游标所在元素，
			虽然你依然可以使用其他删除函数，但是可能不安全（游标变成野指针），或者造成游标错误结束而不能完全遍历整个链表等，
			除非你能够确定你使用其他函数删除的元素不是你当前游标所在的元素

			如果你只是想遍历删除一些不要的元素的话，elementFilter函数是更好的选择
		使用步骤：
			1.初始化遍历点：setCursorToBegin/setCursorToEnd...
			2.遍历
				2.1while循环：
					while(hasNext/hasPrevious)
					{
						getCursorData();
						//此处可添加deleteCursorToNext/deleteCursorToPrevious删除元素
						nextCursor/previousCursor
					}
				2.2do-while循环//但是使用此方法，如果进行元素的删除，将会导致某些元素被跳过的可能性，因此此方法循环内，不要移除元素
					if(hasNext/hasPrevious)
					{
						do
						{
							getCursorData();
							//此处不能添加删除
						}while(nextCursor/previousCursor);
					}
					//如果要具备删除，原因就是删除的时候，游标是会发生移动的，如果不处理，那么删除移动一次，do-while条件再移动一次，造成一个元素跳过检查
					if(hasNext/hasPrevious)
					{
						do
						{
							getCursorData();
							if(需要删除)
								//此处可添加deleteCursorToNext/deleteCursorToPrevious删除元素
							else
								//如果没有删除，需要移动游标nextCursor/previousCursor
						
						}while(hasNext/hasPrevious);
					}
					
			3.结束遍历（此步也可以省略）
				clearCursor
	*/
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
		{
			return false;
		}
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
	//向后遍历时删除元素，删除游标游标，游标向后移动
	T deleteCursorToNext()
	{
		Node * del = m_cur;
		m_cur = m_cur->next;
		Node * parent = del->previous;
		Node * child = del->next;
		parent->next = child;
		if (child!=NULL)
			child->previous = parent;
		if (del == m_center)
		{
			m_center = child;
		}
		T ret = del->data;
		delete del;
		m_size--;
		notifyUpdateCenter();
		return ret;
	}
	//向前遍历时删除元素，删除，游标向前移动
	T deleteCursorToPrevious()
	{
		Node * del = m_cur;
		m_cur = m_cur->previous;
		Node * parent = del->previous;
		Node * child = del->next;
		parent->next = child;
		if (child != NULL)
			child->previous = parent;
		if (del == m_center)
		{
			m_center = child;
		}
		T ret = del->data;
		delete del;
		m_size--;
		notifyUpdateCenter();
		return ret;
	}
	bool nextCursor()
	{
		if (m_cur == NULL)
			return false;
		m_cur = m_cur->next;
		if (m_cur == NULL)
			return false;
		return true;
	}
	bool previousCursor()
	{
		if (m_cur == NULL || m_cur==m_root)
			return false;
		m_cur = m_cur->previous;
		if (m_cur == NULL || m_cur == m_root)
			return false;
		return true;
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
			if (filter(p->data) == false)
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
			if (filter(arr[i]) == false)
			{
				push(arr[i]);
			}
		}
		return *this;
	}
	/*
	元素过滤
	你需要给定元素过滤的回调函数，参数也可以是：const T & elem,这种参数适用于，元素不需要释放任何资源的情况
	原型：bool FuncFilter(T & elem);
	返回值为true,就表示需要过滤，过滤掉的元素将被直接移除丢弃，因此如果需要释放元素的资源，请在过滤函数中释放返回值为true对应的元素的资源
	返回值为false,表示保留元素，因此，你不需要考虑释放资源的问题
	*/
	template<typename FuncFilter>
	AlgoList & elementFilter(FuncFilter filter)
	{
		Node * srcRoot = m_root->next;
		m_root->next = NULL;
		m_tail = m_root;
		m_cur = NULL;
		m_size = 0;
		notifyUpdateCenter();

		
		while (srcRoot)
		{
			Node * cur = srcRoot;
			srcRoot = srcRoot->next;

			if (filter(cur->data) == false)
			{
				pushBackNode(cur);
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

	void pushBackNode(Node * node)
	{
		node->next = m_tail->next;
		m_tail->next = node;
		node->previous = m_tail;

		m_tail = node;

		m_size++;
		notifyUpdateCenter();
	}
	void InitNode()
	{
		if (m_root != NULL)
		{
			delete m_root;
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
	//注意，数组的插入，将会是一个耗时费力的操作，不建议频繁使用，特别是元素数量过多时
	AlgoArray& insert(E index, T data)
	{
		if (index < 0 || index >= m_size)
			return *this;

		for (E i = m_size; i > index; i--)
		{
			m_data[i] = m_data[i-1];
		}

		m_data[index] = data;

		m_size++;
		return *this;
	}
	AlgoArray & remove(E index)
	{
		if (index < 0 || index >= m_size)
			return *this;

		for (E i = index; i < m_size; i++)
		{
			m_data[i] = m_data[i + 1];
		}

		m_size--;
		return *this;
	}
	//快速移除元素，但是会改变既有元素顺序，原理：将最后一个元素放到删除元素位置进行替换，元素长度减1即可
	//只要和元素位置没什么关系时，这种删除方法是及其推荐的
	AlgoArray & removeFast(E index)
	{
		if (index < 0 || index >= m_size)
			return *this;
		T end = m_data[m_size - 1];
		m_data[index] = end;

		m_size--;
		return *this;
	}
	template<typename FuncCmp>
	AlgoArray & removeAll(T data, FuncCmp cmp)
	{
		E psize=0;
		for (E i = 0; i < m_size; i++)
		{
			if (cmp(m_data[i], data)!=0)
			{
				m_data[psize] = m_data[i];
				psize++;
			}
		}
		m_size = psize;
		return *this;
	}
	template<typename FuncFilter>
	AlgoArray & elementFilter(FuncFilter filter)
	{
		E psize = 0;
		for (E i = 0; i < m_size; i++)
		{
			if (filter(m_data[i])==false)
			{
				m_data[psize] = m_data[i];
				psize++;
			}
		}
		m_size = psize;
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
	T& get(E index)
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

template<typename T,typename E>
class AlgoVector
{
public:
	AlgoVector(E capital)
	{
		m_data = NULL;
		InitVector(capital);
	}
	AlgoVector(const AlgoVector& vec)
	{
		m_data = NULL;
		copyFromVector(vec);
	}
	AlgoVector& operator=(const AlgoVector& vec)
	{
		copyFromVector(vec);
		return *this;
	}
	T& operator[](E index)
	{
		return m_data[(m_head+1 + index) % m_capital];
	}
	AlgoVector& push(T data)
	{
		m_tial = (m_tial+1) % m_capital;
		m_data[m_tial] = data;
		return *this;
	}
	T pop()
	{
		m_tial=(m_tial-1+m_capital)%m_capital;
		return m_data[m_tial];
	}
	T& top()const
	{
		return m_data[m_tial];
	}

	bool isFull() const
	{
		return (m_tial + 1) % m_capital == m_head;
	}
	bool isEmpty() const
	{
		return m_tial == m_head;
	}

	AlgoVector& enque(T data)
	{
		m_tial = (m_tial + 1) % m_capital;
		m_data[m_tial] = data;
		return *this;
	}
	T deque()
	{
		m_head = (m_head+1) % m_capital;
		return  m_data[m_head];
	}

	T& head()const
	{
		return m_data[(m_head + 1)%m_capital];
	}
	T& tial()const
	{
		return m_data[m_tial];
	}
	E size()const
	{
		return (m_tial + m_capital - m_head) % m_capital;
	}
	E capital() const
	{
		return m_capital;
	}
	AlgoVector& clear()
	{
		m_head = 0;
		m_tial = 0;
		return *this;
	}
	bool setCapital(E capital)
	{
		if (capital == 0)
			return false;

		if (capital < size())
			return false;

		++capital;
		T * srcData = m_data;
		E srcHead = m_head;
		E srcTial = m_tial;
		E srcCapital = m_capital;

		m_capital = capital;
		m_data = new T[capital];
		m_head = 0;
		m_tial = 0;


		while (true)
		{
			if (srcHead == srcTial)
				break;
			srcHead = (1 + srcHead) % srcCapital;
			m_tial = (1 + m_tial) % m_capital;
			m_data[m_tial] = srcData[srcHead];
		}

		delete[] srcData;

		return true;
	}
private:
	T * m_data;
	E m_capital;

	E m_head;
	E m_tial;
	void copyFromVector(const AlgoVector & vec)
	{
		E srcHead = vec.m_head;
		E srcTial = vec.m_tial;
		
		if (m_data!=NULL)
			delete[] m_data;

		m_capital = vec.m_capital;
		m_data = new T[vec.m_capital];
		m_head = 0;
		m_tial = 0;


		while (true)
		{
			if (srcHead == srcTial)
				break;
			srcHead = (1 + srcHead) % vec.m_capital;
			m_tial=(1+m_tial) % m_capital;
			m_data[m_tial] = vec.m_data[srcHead];
		}
	}
	void InitVector(E capital = 64)
	{
		if (m_data != NULL)
		{
			delete[] m_data;
			m_data = NULL;
		}
		capital++;
		m_data = new T[capital];
		m_head = 0;
		m_tial = 0;
		m_capital = capital;
	}
};

/*
基础双向链表框架，
类是一个节点，也是一个链表
建议每个节点都是用new的方式创建，就像malloc一样
除非你能保证在你使用期间，你的节点不会发生析构
否则我将不知道你的节点何时会销毁，而导致出错

因此，提供一组方法给你使用，防止临时对象在链表中发生异常
因此，推荐使用方法来创建对象，而不是直接构造
当然使用new的方式也可以，方法提供的也是new的方式
new delete make free 可以进行混用，因为make和free实际上就是new和delete

方法均为静态方法，这是由于框架和泛型带来的问题，
如果你不喜欢这样，那么你可以把方法全部提取出去，想C语言一样写
而类改为结构，只不过data属性改为void* 类型，可以再考虑添加一个字段用来指明void的数据类型
如下：
typedef struct __list_node
{
	void * data;
	int data_type;
	struct __list_node * previous;
	struct __list_node * next;
}ListNode,*PListNode;
这样也可以成为一个任意类型通用的链表，并且由于void*的通用性，甚至可以支持一个链表内，具备存放多种数据类型的能力
其中的data_type你也可以考虑使用一个枚举来表示：
enum Elem_Data_Type{INT,CHAR,STRING,FLOAT,DOUBLE};
Elem_Data_Type data_type;
或者依旧保持使用int,结合宏定义一些值，来表示也是不错的选择
#define ELEM_TYPE_INT 1
...
这个的实现，我将会放在AlgoAnyList.hpp中去实现
*/
template<typename T>
class  AlgoBaseList
{
public:
	AlgoBaseList()
	{
		previous = NULL;
		next = NULL;
	}
	AlgoBaseList(T data)
	{
		this->data = data;
		previous = NULL;
		next = NULL;
	}
	
public:
	T data;
	AlgoBaseList * previous;
	AlgoBaseList * next;
	//直接new出一个对象的指针
	static AlgoBaseList* make()
	{
		return new AlgoBaseList();
	}
	static AlgoBaseList* make(T data)
	{
		return new AlgoBaseList(data);
	}
	//删除一个节点，返回永为NULL，这样方便你进行这样的调用：
	//node=node.free(node);
	//而不是：node.free(node);node=NULL;
	static AlgoBaseList* free(AlgoBaseList * lstnode)
	{
		delete lstnode;
		return NULL;
	}
	//重置一个节点的前后指针
	static AlgoBaseList* resetPointers(AlgoBaseList * lstnode)
	{
		lstnode->previous = NULL;
		lstnode->next = NULL;
		return lstnode;
	}
	AlgoBaseList* appendList(AlgoBaseList * list2)
	{
		appendList(this, list2);
		return this;
	}
	//将两个完整链表连接：返回值list1=list1+list2
	//如果list2只有一个节点，那么就相当于添加一个节点
	static AlgoBaseList* appendList(AlgoBaseList * list1, AlgoBaseList * list2)
	{
		AlgoBaseList * list1_last = list1;
		while (list1_last->next != NULL)
		{
			list1_last = list1_last->next;
		}
		AlgoBaseList * list2_last = list2;
		while (list2_last->next != NULL)
		{
			list2_last = list2_last->next;
		}

		list1_last->next = list2;

		list2->previous = list1_last;
		
		
		return list1;
	}
	//将完整列表list2插入到节点lstnode之后，lstnode节点原来之后的元素，被放置到list2之后，返回值lstnode0=lstnode0+list2+lstnode1+lstnode2+...
	//如果list2只有一个节点，那么就相当于插入一个节点
	static AlgoBaseList* insertList(AlgoBaseList * lstnode, AlgoBaseList * list2)
	{
		AlgoBaseList * lstnode_next = lstnode->next;
		AlgoBaseList * list2_last = list2;
		while (list2_last->next != NULL)
		{
			list2_last = list2_last->next;
		}

		lstnode->next = list2;

		if (lstnode_next!=NULL)
			lstnode_next->previous = list2_last;

		list2->previous = lstnode;

		list2_last->next = lstnode_next;

		return lstnode;
	}
	//删除一个节点,至于删除的节点，你需要自己处理(因为不知道传入的是否是new出来的，还是直接临时对象)
	//返回值：lstnode->previous
	//删除节点的父节点(如果没有父节点，那么就返回它的子节点,父子节点都没有，返回NULL)
	static AlgoBaseList* deleteNode(AlgoBaseList * lstnode)
	{
		AlgoBaseList * parent = lstnode->previous;
		AlgoBaseList * child = lstnode->next;

		lstnode->previous = NULL;
		lstnode->next = NULL;

		if (parent == NULL && child == NULL)
		{
			return NULL;
		}

		if (parent == NULL)
		{
			child->previous = parent;
			return child;
		}
		if (child == NULL)
		{
			parent->next = child;
			return parent;
		}
		child->previous = parent;
		parent->next = child;
		return parent;
	}
	
	//根据链表其中一个节点，找到链表最开头的节点，如果你弄成循环链表，那就不要使用此方法
	static AlgoBaseList * getFirstNode(AlgoBaseList * lstnode)
	{
		AlgoBaseList * ret = lstnode;
		while (ret->previous != NULL)
		{
			ret = ret->previous;
		}
		return ret;
	}
	//根据链表其中一个节点，找到链表最末尾的节点，如果你弄成循环链表，那就不要使用此方法
	static AlgoBaseList * getLastNode(AlgoBaseList * lstnode)
	{
		AlgoBaseList * ret = lstnode;
		while (ret->next != NULL)
		{
			ret = ret->next;
		}
		return ret;
	}
	//检查，向后指针是否构成了循环链表
	static bool isLoopNextList(AlgoBaseList * lstnode)
	{
		AlgoBaseList * ret = lstnode;
		while (ret->next != NULL)
		{
			ret = ret->next;
			if (ret == lstnode)
				return true;
		}
		return false;
	}
	//检查，向前指针是否构成了循环链表
	static bool isLoopPreviousList(AlgoBaseList * lstnode)
	{
		AlgoBaseList * ret = lstnode;
		while (ret->previous != NULL)
		{
			ret = ret->previous;
			if (ret == lstnode)
				return true;
		}
		return false;
	}
};

#endif // _ALGO_CONTAINER_HPP_