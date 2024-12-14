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

#endif // _ALGO_CONTAINER_HPP_