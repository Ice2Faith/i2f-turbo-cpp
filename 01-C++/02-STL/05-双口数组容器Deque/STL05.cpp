#include<iostream>
#include<deque>
#include<iterator>
#include<algorithm>
using namespace std;
/**
deque�����÷�--˫������ʵ��˫�˲���
push_front pop_front push_back pop_back
ʵ�������˽��в���
�ֶ������ռ����ʽ
*/
////////////////////////////////////////////////////////////////
template<typename T,typename TI>
void PrintDeque(T & deq)
{
    cout <<"[";
    for(TI i=deq.begin(); i!=deq.end(); i++)
    {
        cout <<(*i)<<",";
    }
    cout <<"]"<<endl;
}
void Test01()
{
    //���ʺ�ֱ�ӽ����������,���ڷֶ��ڴ�������
    //��ʼ������ֵ
    int arr[]= {0,1,2,3,4,5};
    //Ĭ�ϣ�������������
    deque<int> deq1,deq2(arr,arr+sizeof(arr)/sizeof(arr[0])),deq3(10,3),deq4,deq5;
    deq1=deq2;
    deq1.swap(deq2);
    deq4.assign(10,4);
    deq5.assign(deq1.begin(),deq1.end());
    void (*printDeque)(deque<int> &)=&PrintDeque<deque<int>,deque<int>::iterator>;
    printDeque(deq1);
    //��С size resize empty
    cout <<"Size:"<< deq1.size() <<endl;
    deq1.resize(4);//�ض�
    deq1.resize(20,4);//���
    //���룬ɾ�� push_front push_back pop_front pop_back
    deq1.push_front(20);
    deq1.push_back(60);
    printDeque(deq1);
    deq1.pop_front();//û�з���ֵ��ֻɾ��
    int val=deq1.front();
    cout << val<<endl;
    //sort�㷨����������ʼ��������������������ȱʡ��������򣺾���һ���Զ��庯������������ֵ������boolֵ��
    /*
    bool myrule(&,&)
    {
    return %1<%2;
    }
    sort(begin,end,myrule);
    */
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
