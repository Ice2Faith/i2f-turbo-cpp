#ifndef _ALGO_CONTAINER_HPP_
#define _ALGO_CONTAINER_HPP_
/********************************************
* ģ�飺ͨ������ģ��
* author��Ugex.Savelar
*********************************************/
#include<stdlib.h>
/*
�б�����������˫������ʵ��,����һ��βָ��
������ģ���࣬���Ҫ����������ʵ�ֵĻ�
ʵ�ֲ��ֵĺ���ҲҪָ�������б�
Ĭ�������β�����

ʵ�֣�
����βָ���˫�������ڲ�����һ����̬ά���������м�ָ�루�����±꣩
�������ܹ�ʵ��
Ԫ�ص���������ƽ���������ܳ��ȵ��ķ�֮һ��
ֱ��Ԫ�ز����ܵ���ƽ������֮һ
�Ӷ���߲���Ч��

�ķ�֮һ������
��ָ��		�м�ָ��		βָ��
������֪��Ҫ���ҵ��±�����ָ����м�ָ��֮��
��ô����Ŀ���±������ָ����м�ָ����һ������
���ս���һ�����б�������Ԫ�أ���˾�������Ļ������Ҳ�����ķ�֮һ���ܳ��Ⱦ���

����֮һ������
ͬ����������Ԫ����Ҫ����Ƚ�
��ˣ������ĸ�����ͬʱ�����������������̴������Ԫ�ز���ʱ��
��ָ�뵽�м�ָ�룬�м�ָ�뵽��ָ�룬�м�ָ�뵽βָ�룬βָ�뵽�м�ָ��
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
	//���ƹ���͸������㣬һ��Ҫд�ϣ���Ȼ��debug�������Ҳ�����������
	//����һ��Ѫ�Ľ�ѵ������BLOCK_TYPE_IS_VALID(pHead->nBlockUse)
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
	Cursor�庯����
		�ô���
			��������ʹ���±귽ʽ������������ʧ��ʹ���±귽ʽ��Ҫ���ϵı�������ȥ���Ҷ�Ӧ���±꣬�Ӷ����������ʧ
			��ʹ���α�ķ�ʽ�����������������ʧ����Ϊֻ��˫�������ָ��䶯�����漰�±��������
			����ʹ����˵��������ע���α걾������Ľṹ���͸������������ȥ���±������
		������
			��ֻ���޸Ļ���ɾ����������Ԫ�أ������ܽ�����Ӳ�����Ҳ��֪���������±�
			��Ȼ����������Ȼ�ܹ����в��루ʹ�����������������ǲ���Ӱ�쵽�±���ƶ�
			�Ͼ������α�֮ǰ�����֮����룬�����α���˵����ֻ�ǹ�ע�α걾��ǰ��ı仯����͸���ģ���Ӱ���
		ע�⣺
			�α����ʱ������ɾ�����ԣ���Ҫʹ���α��麯����ɾ��������ɾ���α�����Ԫ�أ�
			��Ȼ����Ȼ����ʹ������ɾ�����������ǿ��ܲ���ȫ���α���Ұָ�룩����������α���������������ȫ������������ȣ�
			�������ܹ�ȷ����ʹ����������ɾ����Ԫ�ز����㵱ǰ�α����ڵ�Ԫ��

			�����ֻ�������ɾ��һЩ��Ҫ��Ԫ�صĻ���elementFilter�����Ǹ��õ�ѡ��
		ʹ�ò��裺
			1.��ʼ�������㣺setCursorToBegin/setCursorToEnd...
			2.����
				2.1whileѭ����
					while(hasNext/hasPrevious)
					{
						getCursorData();
						//�˴������deleteCursorToNext/deleteCursorToPreviousɾ��Ԫ��
						nextCursor/previousCursor
					}
				2.2do-whileѭ��//����ʹ�ô˷������������Ԫ�ص�ɾ�������ᵼ��ĳЩԪ�ر������Ŀ����ԣ���˴˷���ѭ���ڣ���Ҫ�Ƴ�Ԫ��
					if(hasNext/hasPrevious)
					{
						do
						{
							getCursorData();
							//�˴��������ɾ��
						}while(nextCursor/previousCursor);
					}
					//���Ҫ�߱�ɾ����ԭ�����ɾ����ʱ���α��ǻᷢ���ƶ��ģ������������ôɾ���ƶ�һ�Σ�do-while�������ƶ�һ�Σ����һ��Ԫ���������
					if(hasNext/hasPrevious)
					{
						do
						{
							getCursorData();
							if(��Ҫɾ��)
								//�˴������deleteCursorToNext/deleteCursorToPreviousɾ��Ԫ��
							else
								//���û��ɾ������Ҫ�ƶ��α�nextCursor/previousCursor
						
						}while(hasNext/hasPrevious);
					}
					
			3.�����������˲�Ҳ����ʡ�ԣ�
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
	//������ʱɾ��Ԫ�أ�ɾ���α��α꣬�α�����ƶ�
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
	//��ǰ����ʱɾ��Ԫ�أ�ɾ�����α���ǰ�ƶ�
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
	Ԫ�ع���
	����Ҫ����Ԫ�ع��˵Ļص�����������Ҳ�����ǣ�const T & elem,���ֲ��������ڣ�Ԫ�ز���Ҫ�ͷ��κ���Դ�����
	ԭ�ͣ�bool FuncFilter(T & elem);
	����ֵΪtrue,�ͱ�ʾ��Ҫ���ˣ����˵���Ԫ�ؽ���ֱ���Ƴ���������������Ҫ�ͷ�Ԫ�ص���Դ�����ڹ��˺������ͷŷ���ֵΪtrue��Ӧ��Ԫ�ص���Դ
	����ֵΪfalse,��ʾ����Ԫ�أ���ˣ��㲻��Ҫ�����ͷ���Դ������
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
	/*ֱ����������λ�ã������ڴ���Ԫ�ز���֮���޷����м�ƫ�����ʱ��ʹ�������٣����߲�����ʹ��*/
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
	/*��������λ�ã���Ե�һ����������ȷԪ�ز���֮��Ч�ʸߣ��Ƽ�ʹ��*/
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
	//ע�⣬����Ĳ��룬������һ����ʱ�����Ĳ�����������Ƶ��ʹ�ã��ر���Ԫ����������ʱ
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
	//�����Ƴ�Ԫ�أ����ǻ�ı����Ԫ��˳��ԭ�������һ��Ԫ�طŵ�ɾ��Ԫ��λ�ý����滻��Ԫ�س��ȼ�1����
	//ֻҪ��Ԫ��λ��ûʲô��ϵʱ������ɾ�������Ǽ����Ƽ���
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
		Node * tp = m_root, *fp = m_root;// ��ǰ�ڵ�ָ�룬��ǰ�ڵ�ĸ��ڵ�ָ��
		while (tp != NULL)
		{
			if (comparator(data, tp->data) == 0)// ���ҳɹ�
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
		if (tp == NULL)//û�ҵ���Ӧ�ļ�
			return false;
		if (tp == m_root)//����ҵ��Ľڵ��Ǹ��ڵ�
		{
			if (tp->lchild != NULL) //������ڵ����������������������Ϊ�¸���������������Ϊ�¸�����û����ɾ����
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
		else if (tp == fp->lchild)//������ҽڵ����丸�ڵ��������
		{
			if (tp->lchild == NULL)//������ҽڵ��������Ϊ��
			{
				fp->lchild = tp->rchild; //���ҽڵ���������滻ɾ���ڵ�
				delete tp;
			}
			else
			{
				Node * mp, *up;//Ҫ�ƶ��Ľڵ㣬�����滻�Ľڵ�
				mp = tp->rchild;//���������������ô���ƶ��������ǲ��ҽڵ��������
				up = tp->lchild;
				fp->lchild = up;//���ҽڵ���������滻���ҽڵ��Ϊ���ڵ��������
				Node * rp = up->rchild, *frp = up;//���ҽڵ�����ҽڵ�ĸ��ڵ�
				while (rp != NULL)// �ҵ����ҽڵ�ĸ��ڵ�
				{
					frp = rp;
					rp = rp->rchild;
				}
				frp->rchild = mp;//���ҽڵ�ĸ��ڵ����������Ϊ�ƶ��Ľڵ�
				delete tp;
			}

		}
		else if (tp == fp->rchild)//������ҽڵ����丸�ڵ��������
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
				while (lp != NULL)// �ҵ�����ڵ�ĸ��ڵ�
				{
					flp = lp;
					lp = lp->lchild;
				}
				flp->lchild = mp;//����ڵ�ĸ��ڵ����������Ϊ�ƶ��Ľڵ�
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
����˫�������ܣ�
����һ���ڵ㣬Ҳ��һ������
����ÿ���ڵ㶼����new�ķ�ʽ����������mallocһ��
�������ܱ�֤����ʹ���ڼ䣬��Ľڵ㲻�ᷢ������
�����ҽ���֪����Ľڵ��ʱ�����٣������³���

��ˣ��ṩһ�鷽������ʹ�ã���ֹ��ʱ�����������з����쳣
��ˣ��Ƽ�ʹ�÷������������󣬶�����ֱ�ӹ���
��Ȼʹ��new�ķ�ʽҲ���ԣ������ṩ��Ҳ��new�ķ�ʽ
new delete make free ���Խ��л��ã���Ϊmake��freeʵ���Ͼ���new��delete

������Ϊ��̬�������������ڿ�ܺͷ��ʹ��������⣬
����㲻ϲ����������ô����԰ѷ���ȫ����ȡ��ȥ����C����һ��д
�����Ϊ�ṹ��ֻ����data���Ը�Ϊvoid* ���ͣ������ٿ������һ���ֶ�����ָ��void����������
���£�
typedef struct __list_node
{
	void * data;
	int data_type;
	struct __list_node * previous;
	struct __list_node * next;
}ListNode,*PListNode;
����Ҳ���Գ�Ϊһ����������ͨ�õ�������������void*��ͨ���ԣ���������֧��һ�������ڣ��߱���Ŷ����������͵�����
���е�data_type��Ҳ���Կ���ʹ��һ��ö������ʾ��
enum Elem_Data_Type{INT,CHAR,STRING,FLOAT,DOUBLE};
Elem_Data_Type data_type;
�������ɱ���ʹ��int,��Ϻ궨��һЩֵ������ʾҲ�ǲ����ѡ��
#define ELEM_TYPE_INT 1
...
�����ʵ�֣��ҽ������AlgoAnyList.hpp��ȥʵ��
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
	//ֱ��new��һ�������ָ��
	static AlgoBaseList* make()
	{
		return new AlgoBaseList();
	}
	static AlgoBaseList* make(T data)
	{
		return new AlgoBaseList(data);
	}
	//ɾ��һ���ڵ㣬������ΪNULL��������������������ĵ��ã�
	//node=node.free(node);
	//�����ǣ�node.free(node);node=NULL;
	static AlgoBaseList* free(AlgoBaseList * lstnode)
	{
		delete lstnode;
		return NULL;
	}
	//����һ���ڵ��ǰ��ָ��
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
	//�����������������ӣ�����ֵlist1=list1+list2
	//���list2ֻ��һ���ڵ㣬��ô���൱�����һ���ڵ�
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
	//�������б�list2���뵽�ڵ�lstnode֮��lstnode�ڵ�ԭ��֮���Ԫ�أ������õ�list2֮�󣬷���ֵlstnode0=lstnode0+list2+lstnode1+lstnode2+...
	//���list2ֻ��һ���ڵ㣬��ô���൱�ڲ���һ���ڵ�
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
	//ɾ��һ���ڵ�,����ɾ���Ľڵ㣬����Ҫ�Լ�����(��Ϊ��֪��������Ƿ���new�����ģ�����ֱ����ʱ����)
	//����ֵ��lstnode->previous
	//ɾ���ڵ�ĸ��ڵ�(���û�и��ڵ㣬��ô�ͷ��������ӽڵ�,���ӽڵ㶼û�У�����NULL)
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
	
	//������������һ���ڵ㣬�ҵ������ͷ�Ľڵ㣬�����Ū��ѭ�������ǾͲ�Ҫʹ�ô˷���
	static AlgoBaseList * getFirstNode(AlgoBaseList * lstnode)
	{
		AlgoBaseList * ret = lstnode;
		while (ret->previous != NULL)
		{
			ret = ret->previous;
		}
		return ret;
	}
	//������������һ���ڵ㣬�ҵ�������ĩβ�Ľڵ㣬�����Ū��ѭ�������ǾͲ�Ҫʹ�ô˷���
	static AlgoBaseList * getLastNode(AlgoBaseList * lstnode)
	{
		AlgoBaseList * ret = lstnode;
		while (ret->next != NULL)
		{
			ret = ret->next;
		}
		return ret;
	}
	//��飬���ָ���Ƿ񹹳���ѭ������
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
	//��飬��ǰָ���Ƿ񹹳���ѭ������
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