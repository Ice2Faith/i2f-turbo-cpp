#ifndef _ALGO_ANY_LIST_HPP_
#define _ALGO_ANY_LIST_HPP_

/*
author��ugex
-----------------------------------
ʹ��C���Եķ�ʽ������һ��ͨ������
��������
�겿�֣�
ALGO_ANY_LIST_��ͷ
�������֣�
AlgoAnyList

����Ԫ����Ҫ׼�ع���dataָ���ַһ��Ҫ���ڶ��ϵ�
��ʱ����ȡ��ַ�ǲ��еģ���Ϊ�����Σ�գ�����Ұָ�룩
���⣬һ���ڵ�Ҳ�����Ƕ��ϵģ����������纯��������ʱ��
�ڵ���ܻᷢ��Σ�գ���������ͷŻ���Ұָ��
*/
#include<stdlib.h>
//�����������Ͷ��壬��Ҳ����ʹ���Լ��Ķ���
#define ALGO_ANY_LIST_DATA_TYPE_NULL	 0x00
#define ALGO_ANY_LIST_DATA_TYPE_CHAR	 0x01
#define ALGO_ANY_LIST_DATA_TYPE_SHORT	 0x02
#define ALGO_ANY_LIST_DATA_TYPE_INT		 0x03
#define ALGO_ANY_LIST_DATA_TYPE_LONG	 0x04
#define ALGO_ANY_LIST_DATA_TYPE_FLOAT	 0x05
#define ALGO_ANY_LIST_DATA_TYPE_DOUBLE	 0x06
#define ALGO_ANY_LIST_DATA_TYPE_LPCHAR	 0x07

//�û���������ֵ����ʼֵ
#define ALGO_ANY_LIST_DATA_TYPE_USER	 0x100

//�����������͵ĺ깹�죬���������ݣ��������ͣ�Լ�����ͣ����磺AlgoAnyListNode* node=ALGO_ANY_LIST_BASE_MAKE_NODE(12,int,ALGO_ANY_LIST_DATA_TYPE_INT)
//������������֧�֣���ֵ��malloc(sizeof(����))�ľ���
//��˶����鲢������
#define ALGO_ANY_LIST_BASE_MAKE_NODE(data,type,data_type) AlgoAnyList_makeNode(&((* (type*)malloc(sizeof(type)))  = data),data_type,sizeof(type))

//�ַ�������꣬������char * ���ַ������������ַ�����ַ������ڵ㣬���磺AlgoAnyListNode * node = NULL;ALGO_ANY_LIST_LPCHAR_MAKE_NODE("hello", node);
#define ALGO_ANY_LIST_LPCHAR_MAKE_NODE(data,psave) do{int size=sizeof(char)*(strlen(data)+1);char * buf=(char *)malloc(size);strcpy(buf,data);psave = AlgoAnyList_makeNode(buf, ALGO_ANY_LIST_DATA_TYPE_LPCHAR, size);} while (0)

//�ڴ�ռ乹�죬������һ���ڴ棬���Ҳ�������ַ������죬����������Դ��ַ�����ݴ�С��Լ������
#define ALGO_ANY_LIST_MEMORY_MAKE_NODE(pdata,psave,data_size,data_type) do{void * buf=(void *)malloc(data_size);memcpy(buf,pdata,data_size);psave = AlgoAnyList_makeNode(buf, data_type, data_size);}while(0)

//�ͷ����ڹ�������õ��Ŀռ䣬�����ڻ����������ͣ����������ַ���,��ʵ����malloc��Ե�free���ã��������ڵ��data,�������ͣ����磺ALGO_ANY_LIST_FREE_DATA(node->data,int)
//���ҪӦ�����ַ������ڶ�������ӦΪchar,������char*
#define ALGO_ANY_LIST_FREE_DATA(pdata,type) do{if(pdata){free((type *)pdata);pdata=NULL;}}while(0)

//�ͷ�һ���ڴ棬��������ַ��ָ������,���磺ALGO_ANY_LIST_FREE_DATA_MEMORY(node->data,char *)
#define ALGO_ANY_LIST_FREE_DATA_MEMORY(pdata,pointertype) do{if(pdata){free((pointertype)pdata);pdata=NULL;}}while(0)

//��ȡֵ�������ڻ����������ͣ����������ַ��������磺ALGO_ANY_LIST_GET_DATA(cur->data, int)
#define ALGO_ANY_LIST_GET_DATA(pdata,type) (*(type*)pdata)

//��ȡֵ��ȡ�ڴ����ݣ�ת��ָ������
#define ALGO_ANY_LIST_GET_DATA_MEMORY(pdata,pointertype) ((pointertype)pdata)

typedef struct __algo_any_list_node
{
	void * data;								//ָ�����ݵ�ָ��
	long data_size;								//���ݵĴ�С����ʱ���ܻ��õ�
	int data_type;								//���ݵ�����
	struct __algo_any_list_node * previous;		//��ǰָ��
	struct __algo_any_list_node * next;			//���ָ��
}AlgoAnyListNode,*PAlgoAnyListNode;
typedef AlgoAnyListNode		AlgoAnyList;
typedef PAlgoAnyListNode	PAlgoAnyList;

//����һ������ڵ�
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
//�����ݴ���һ������ڵ�
AlgoAnyListNode* AlgoAnyList_makeNode(void * data, int data_type, long data_size/*=0*/)
{
	AlgoAnyListNode* ret = AlgoAnyList_makeNode();
	ret->data = data;
	ret->data_type = data_type;
	ret->data_size = data_size;
	return ret;
}
//ɾ��һ���ڵ㣬������ΪNULL��������������������ĵ��ã�
//node=node.free(node);
//�����ǣ�node.free(node);node=NULL;
AlgoAnyListNode* AlgoAnyList_freeNode(AlgoAnyListNode * node)
{
	if (node)
		free(node);
	return NULL;
}
//���ýڵ㣬��ˣ�����Ҫ��ǰ����data�Σ��Ƿ���Ҫ�ͷ��ڴ�
AlgoAnyListNode* AlgoAnyList_resetNode(AlgoAnyListNode * ret)
{
	ret->data = NULL;
	ret->data_type = ALGO_ANY_LIST_DATA_TYPE_NULL;
	ret->data_size = 0;
	ret->previous = NULL;
	ret->next = NULL;
	return ret;
}
//����һ���ڵ��ǰ��ָ��
AlgoAnyListNode* AlgoAnyList_resetPointers(AlgoAnyListNode * node)
{
	if (node)
	{
		node->previous = NULL;
		node->next = NULL;
	}
	return node;
}

//�����������������ӣ�����ֵlist1=list1+list2
//���list2ֻ��һ���ڵ㣬��ô���൱�����һ���ڵ�
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
//�������б�list2���뵽�ڵ�lstnode֮��lstnode�ڵ�ԭ��֮���Ԫ�أ������õ�list2֮�󣬷���ֵlstnode0=lstnode0+list2+lstnode1+lstnode2+...
//���list2ֻ��һ���ڵ㣬��ô���൱�ڲ���һ���ڵ�
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
//ɾ��һ���ڵ�,����ɾ���Ľڵ㣬����Ҫ�Լ�����(��Ϊ��֪��������Ƿ���new�����ģ�����ֱ����ʱ����)
//����ֵ��lstnode->previous
//ɾ���ڵ�ĸ��ڵ�(���û�и��ڵ㣬��ô�ͷ��������ӽڵ�,���ӽڵ㶼û�У�����NULL)
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

//������������һ���ڵ㣬�ҵ������ͷ�Ľڵ㣬�����Ū��ѭ�������ǾͲ�Ҫʹ�ô˷���
AlgoAnyListNode * AlgoAnyList_getFirstNode(AlgoAnyListNode * lstnode)
{
	AlgoAnyListNode * ret = lstnode;
	while (ret->previous != NULL)
	{
		ret = ret->previous;
	}
	return ret;
}
//������������һ���ڵ㣬�ҵ�������ĩβ�Ľڵ㣬�����Ū��ѭ�������ǾͲ�Ҫʹ�ô˷���
AlgoAnyListNode * AlgoAnyList_getLastNode(AlgoAnyListNode * lstnode)
{
	AlgoAnyListNode * ret = lstnode;
	while (ret->next != NULL)
	{
		ret = ret->next;
	}
	return ret;
}
//��飬���ָ���Ƿ񹹳���ѭ������
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
//��飬��ǰָ���Ƿ񹹳���ѭ������
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
