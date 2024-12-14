#ifndef _ALGO_ANY_LIST_HPP_
#define _ALGO_ANY_LIST_HPP_

/*
author：ugex
-----------------------------------
使用C语言的方式，构造一个通用链表
命名规则：
宏部分：
ALGO_ANY_LIST_开头
其他部分：
AlgoAnyList

链表元素需要准守规则，data指向地址一定要是在堆上的
临时变量取地址是不行的，因为这会有危险（导致野指针）
另外，一个节点也必须是堆上的，否则如果你跨函数操作的时候，
节点可能会发生危险，被错误的释放或者野指针
*/
#include<stdlib.h>
//基本数据类型定义，你也可以使用自己的定义
#define ALGO_ANY_LIST_DATA_TYPE_NULL	 0x00
#define ALGO_ANY_LIST_DATA_TYPE_CHAR	 0x01
#define ALGO_ANY_LIST_DATA_TYPE_SHORT	 0x02
#define ALGO_ANY_LIST_DATA_TYPE_INT		 0x03
#define ALGO_ANY_LIST_DATA_TYPE_LONG	 0x04
#define ALGO_ANY_LIST_DATA_TYPE_FLOAT	 0x05
#define ALGO_ANY_LIST_DATA_TYPE_DOUBLE	 0x06
#define ALGO_ANY_LIST_DATA_TYPE_LPCHAR	 0x07

//用户数据类型值，开始值
#define ALGO_ANY_LIST_DATA_TYPE_USER	 0x100

//基本数据类型的宏构造，参数：数据，数据类型，约定类型，例如：AlgoAnyListNode* node=ALGO_ANY_LIST_BASE_MAKE_NODE(12,int,ALGO_ANY_LIST_DATA_TYPE_INT)
//或者其他类型支持：赋值，malloc(sizeof(类型))的均可
//因此对数组并不适用
#define ALGO_ANY_LIST_BASE_MAKE_NODE(data,type,data_type) AlgoAnyList_makeNode(&((* (type*)malloc(sizeof(type)))  = data),data_type,sizeof(type))

//字符串构造宏，适用于char * 的字符串，参数：字符串地址，保存节点，例如：AlgoAnyListNode * node = NULL;ALGO_ANY_LIST_LPCHAR_MAKE_NODE("hello", node);
#define ALGO_ANY_LIST_LPCHAR_MAKE_NODE(data,psave) do{int size=sizeof(char)*(strlen(data)+1);char * buf=(char *)malloc(size);strcpy(buf,data);psave = AlgoAnyList_makeNode(buf, ALGO_ANY_LIST_DATA_TYPE_LPCHAR, size);} while (0)

//内存空间构造，适用于一块内存，因此也适用于字符串构造，参数：数据源地址，数据大小，约定类型
#define ALGO_ANY_LIST_MEMORY_MAKE_NODE(pdata,psave,data_size,data_type) do{void * buf=(void *)malloc(data_size);memcpy(buf,pdata,data_size);psave = AlgoAnyList_makeNode(buf, data_type, data_size);}while(0)

//释放用于构造宏所得到的空间，适用于基本数据类型，不适用于字符串,其实就是malloc配对的free调用，参数：节点的data,数据类型，例如：ALGO_ANY_LIST_FREE_DATA(node->data,int)
//如果要应用于字符串，第二个参数应为char,而不是char*
#define ALGO_ANY_LIST_FREE_DATA(pdata,type) do{if(pdata){free((type *)pdata);pdata=NULL;}}while(0)

//释放一块内存，参数：地址，指针类型,例如：ALGO_ANY_LIST_FREE_DATA_MEMORY(node->data,char *)
#define ALGO_ANY_LIST_FREE_DATA_MEMORY(pdata,pointertype) do{if(pdata){free((pointertype)pdata);pdata=NULL;}}while(0)

//宏取值，适用于基本数据类型，不适用于字符串，例如：ALGO_ANY_LIST_GET_DATA(cur->data, int)
#define ALGO_ANY_LIST_GET_DATA(pdata,type) (*(type*)pdata)

//宏取值，取内存数据，转换指针类型
#define ALGO_ANY_LIST_GET_DATA_MEMORY(pdata,pointertype) ((pointertype)pdata)

typedef struct __algo_any_list_node
{
	void * data;								//指向数据的指针
	long data_size;								//数据的大小，有时可能会用到
	int data_type;								//数据的类型
	struct __algo_any_list_node * previous;		//向前指针
	struct __algo_any_list_node * next;			//向后指针
}AlgoAnyListNode,*PAlgoAnyListNode;
typedef AlgoAnyListNode		AlgoAnyList;
typedef PAlgoAnyListNode	PAlgoAnyList;

//创建一个链表节点
AlgoAnyListNode* AlgoAnyList_makeNode()
{
	AlgoAnyListNode* ret = (AlgoAnyListNode*)malloc(sizeof(AlgoAnyListNode));
	ret->data = NULL;
	ret->data_type = ALGO_ANY_LIST_DATA_TYPE_NULL;
	ret->data_size = 0;
	ret->previous = NULL;
	ret->next = NULL; 
	return ret;
}
//带数据创建一个链表节点
AlgoAnyListNode* AlgoAnyList_makeNode(void * data, int data_type, long data_size/*=0*/)
{
	AlgoAnyListNode* ret = AlgoAnyList_makeNode();
	ret->data = data;
	ret->data_type = data_type;
	ret->data_size = data_size;
	return ret;
}
//删除一个节点，返回永为NULL，这样方便你进行这样的调用：
//node=node.free(node);
//而不是：node.free(node);node=NULL;
AlgoAnyListNode* AlgoAnyList_freeNode(AlgoAnyListNode * node)
{
	if (node)
		free(node);
	return NULL;
}
//重置节点，因此，你需要提前处理data段，是否需要释放内存
AlgoAnyListNode* AlgoAnyList_resetNode(AlgoAnyListNode * ret)
{
	ret->data = NULL;
	ret->data_type = ALGO_ANY_LIST_DATA_TYPE_NULL;
	ret->data_size = 0;
	ret->previous = NULL;
	ret->next = NULL;
	return ret;
}
//重置一个节点的前后指针
AlgoAnyListNode* AlgoAnyList_resetPointers(AlgoAnyListNode * node)
{
	if (node)
	{
		node->previous = NULL;
		node->next = NULL;
	}
	return node;
}

//将两个完整链表连接：返回值list1=list1+list2
//如果list2只有一个节点，那么就相当于添加一个节点
AlgoAnyListNode* AlgoAnyList_appendList(AlgoAnyListNode * list1, AlgoAnyListNode * list2)
{
	AlgoAnyListNode * list1_last = list1;
	while (list1_last->next != NULL)
	{
		list1_last = list1_last->next;
	}
	AlgoAnyListNode * list2_last = list2;
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
AlgoAnyListNode* AlgoAnyList_insertList(AlgoAnyListNode * lstnode, AlgoAnyListNode * list2)
{
	AlgoAnyListNode * lstnode_next = lstnode->next;
	AlgoAnyListNode * list2_last = list2;
	while (list2_last->next != NULL)
	{
		list2_last = list2_last->next;
	}

	lstnode->next = list2;

	if (lstnode_next != NULL)
		lstnode_next->previous = list2_last;

	list2->previous = lstnode;

	list2_last->next = lstnode_next;

	return lstnode;
}
//删除一个节点,至于删除的节点，你需要自己处理(因为不知道传入的是否是new出来的，还是直接临时对象)
//返回值：lstnode->previous
//删除节点的父节点(如果没有父节点，那么就返回它的子节点,父子节点都没有，返回NULL)
AlgoAnyListNode* AlgoAnyList_deleteNode(AlgoAnyListNode * lstnode)
{
	AlgoAnyListNode * parent = lstnode->previous;
	AlgoAnyListNode * child = lstnode->next;

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
AlgoAnyListNode * AlgoAnyList_getFirstNode(AlgoAnyListNode * lstnode)
{
	AlgoAnyListNode * ret = lstnode;
	while (ret->previous != NULL)
	{
		ret = ret->previous;
	}
	return ret;
}
//根据链表其中一个节点，找到链表最末尾的节点，如果你弄成循环链表，那就不要使用此方法
AlgoAnyListNode * AlgoAnyList_getLastNode(AlgoAnyListNode * lstnode)
{
	AlgoAnyListNode * ret = lstnode;
	while (ret->next != NULL)
	{
		ret = ret->next;
	}
	return ret;
}
//检查，向后指针是否构成了循环链表
bool AlgoAnyList_isLoopNextList(AlgoAnyListNode * lstnode)
{
	AlgoAnyListNode * ret = lstnode;
	while (ret->next != NULL)
	{
		ret = ret->next;
		if (ret == lstnode)
			return true;
	}
	return false;
}
//检查，向前指针是否构成了循环链表
bool AlgoAnyList_isLoopPreviousList(AlgoAnyListNode * lstnode)
{
	AlgoAnyListNode * ret = lstnode;
	while (ret->previous != NULL)
	{
		ret = ret->previous;
		if (ret == lstnode)
			return true;
	}
	return false;
}
#endif // _ALGO_ANY_LIST_HPP_
