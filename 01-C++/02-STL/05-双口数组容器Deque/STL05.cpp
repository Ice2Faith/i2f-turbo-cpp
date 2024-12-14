#include<iostream>
#include<deque>
#include<iterator>
#include<algorithm>
using namespace std;
/**
deque基本用法--双口容器实现双端操作
push_front pop_front push_back pop_back
实现在两端进行操作
分段连续空间管理方式
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
    //不适合直接进行排序操作,由于分段内存管理策略
    //初始化，赋值
    int arr[]= {0,1,2,3,4,5};
    //默认，迭代器，复制
    deque<int> deq1,deq2(arr,arr+sizeof(arr)/sizeof(arr[0])),deq3(10,3),deq4,deq5;
    deq1=deq2;
    deq1.swap(deq2);
    deq4.assign(10,4);
    deq5.assign(deq1.begin(),deq1.end());
    void (*printDeque)(deque<int> &)=&PrintDeque<deque<int>,deque<int>::iterator>;
    printDeque(deq1);
    //大小 size resize empty
    cout <<"Size:"<< deq1.size() <<endl;
    deq1.resize(4);//截断
    deq1.resize(20,4);//填充
    //插入，删除 push_front push_back pop_front pop_back
    deq1.push_front(20);
    deq1.push_back(60);
    printDeque(deq1);
    deq1.pop_front();//没有返回值，只删除
    int val=deq1.front();
    cout << val<<endl;
    //sort算法，参数：开始迭代器，结束迭代器，缺省（运算规则：就是一个自定义函数，传入两个值，返回bool值）
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
