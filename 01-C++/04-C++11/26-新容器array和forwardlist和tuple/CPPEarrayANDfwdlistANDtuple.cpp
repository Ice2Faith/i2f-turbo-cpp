#include<iostream>
#include<array>
#include<tuple>
#include<string>
using namespace std;
/*
array 是一个类似vector的容器，但是是保存在栈区的，因此性能更好，不能够隐式转换为指针
编译时创建固定大小数组，只需要指定类型和大小即可

*/
void Tarray()
{
    array<int,5> arr{1,2,3,4,5};//长度必须是常量或者常量表达式
    int * parr=&arr[0];
    parr=arr.data();
    parr=nullptr;//转换为指针的操作
    //forward_list<int> flist;
    //区别于list双向链表的单向链表，空间利用率和速率都更高
    /*
    新增两组无序容器：
    unordered_map
    unordered_multimap
    unordered_set
    unordered_multiset
    不同于set和map内部通过红黑树实现，而是hash表实现
    */
}
void Ttuple()
{
    //就像一个可以容纳不同类型的结构体
    tuple<int,double,string> tps(12,17.58,"pixel");
    auto tp=make_tuple(5,12.125,"hello");//构造元组，类型推断为tuple<int,double,string>
    cout << get<2>(tp)<<endl;//获取元素，无法使用变量下标
    int id;
    double bim;
    string item;
    tie(id,bim,item)=tp;//元组拆包
    cout << id<<" "<<bim<<" "<<item<<endl;
    auto ntp=tuple_cat(tps,tp);//元组的连接
    /*
    pair，一个两个成员的结构体
    */
    auto p1=make_pair(12,'c');
    pair<double,int> p2(12.125,17);
    cout << p2.first <<" "<<p2.second<<endl;
    p2=make_pair(1,1.2);
    p2=p1;//一个含有成员函数的结构体
    //pair可以使用typedef进行简化声明
}
int main()
{
    Tarray();
    Ttuple();
    return 0;
}
