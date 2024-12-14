#include<iostream>
#include<list>
#include<iterator>
#include<algorithm>
using namespace std;
/**
list容器：链表：非连续内存组织形式；
push_front push_back pop_front pop_back clear remove erase insert
不支持随机迭代器
*/
////////////////////////////////////////////////////////////////

void Test01()
{
    int arr[]={0,1,2,3,4,5,4,8,5};
    list<int> lis1(arr,arr+sizeof(arr)/sizeof(arr[0])),lis2(10,2);
    list<int> lis3(lis1);
    //初始化和遍历
    for(list<int>::iterator i=lis1.begin();i!=lis1.end();i++)
    {
        cout << (*i)<<" ";
    }
    cout <<endl;
    //插入删除
    lis1.push_back(20);
    lis1.insert((lis1.begin()++)++,30);//不支持随机，只能++
    lis1.insert(lis1.begin(),10,2);//复制
    //insert 可以迭代器区间
    lis1.pop_back();
    lis1.erase(lis1.begin(),lis1.begin()++);//删除迭代器区间
    lis1.remove(5);//删除匹配所有数据
    //大小操作size empty resize
    //赋值，排序，反转
    lis2.assign(10,10);//赋值复制
    lis3=lis2;
    lis2.swap(lis3);
    cout << lis1.front() << " "<<lis1.back()<<endl;
    lis1.reverse();//反转
    lis1.sort();//排序--默认升序--可选参数规则：bool myrules(&,&)
    //成员排序原因是不支持随机访问迭代器，所以只能成员函数实现
    for(list<int>::iterator i=lis1.begin();i!=lis1.end();i++)
    {
        cout << (*i)<<" ";
    }
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
