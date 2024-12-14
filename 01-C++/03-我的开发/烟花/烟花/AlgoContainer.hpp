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

#endif // _ALGO_CONTAINER_HPP_