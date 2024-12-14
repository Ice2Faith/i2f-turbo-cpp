#include<iostream>
#include<set>
#include<iterator>
#include<algorithm>
using namespace std;
/**
set/multiset容器：关联容器，基于平衡二叉树、红黑二叉树为底层原理
应用二叉树，图
set:不允许重复值
multiset:允许重复值
提供迭代器，不允许通过迭代器修改值
默认排序，升序
方法：insert

pair对组，把两个值合成一个值，可以是不同数据类型
*/
////////////////////////////////////////////////////////////////
class compareperson;
class person
{
private:
    int age;
    friend class compareperson;
public:
    person(int age):age(age){};
};
class compareperson{
public:
    bool operator()(const person& v1,const person& v2) const
    {
        return v1.age>v2.age;
    }
};

//仿函数
class mycompare{
public:
    bool operator()(int v1,int v2)
    {
        return v1>v2;
    }
};

void Test01()
{
    //初始化和赋值
	set<int> set1;
	set1.insert(1);
	set1.insert(7);
	set1.insert(3);
	set1.insert(2);
	for(set<int>::iterator i=set1.begin();i!=set1.end();i++)
    {
        cout << (*i) <<" ";
    }
    cout<<endl;
    //赋值和大小 = clear erase
    set<int> set2=set1;
    set2.erase(set2.begin());//删除迭代器位置
    set2.erase(2);//删除指定值
    set2.erase(set2.begin(),set2.begin()++);//删除迭代器区间--和树的遍历有关
    //查找
    set2.clear();
    set2=set1;
    set2.insert(3);
    set2.insert(4);
    set2.insert(6);
   // set2.swap(set1);
    for(set<int>::iterator i=set1.begin();i!=set1.end();i++)
    {
        cout << (*i) <<" ";
    }
    cout<<endl;
    set<int>::iterator ret=set2.find(5);//查找返回迭代器
    if(ret==set2.end())
        cout << "Not Found"<<endl;

    //lower_bound() 返回第一个key大于等于值的迭代器
    ret=set2.lower_bound(3);
    //upper_bound() 返回第一个大于值的迭代器
    ret=set2.upper_bound(3);
    //equal_range() 返回lower_bound 和 upper_bound 的值
    pair<set<int>::iterator,set<int>::iterator> mypair=set2.equal_range(3);
    if(mypair.first==set2.end())
         cout << "Not Found"<<endl;
    if(mypair.second==set2.end())
         cout << "Not Found"<<endl;

    //改变默认排序规则,使用仿函数类
    set<int,mycompare> set4;
    set4.insert(5);
    set4.insert(3);
    set4.insert(6);
    for(set<int>::iterator i=set4.begin();i!=set4.end();i++)
    {
        cout << (*i) <<" ";
    }
    cout<<endl;

    set<person,compareperson> set5;
    person p1(5),p2(8),p3(3);
    set5.insert(p1);
    set5.insert(p2);
    set5.insert(p3);
}
void test02()
{
    //对组，把两个值合成一个值，可以是不同数据类型
    //初始化和赋值
    pair<int,char> pai1(10,'5');
    cout << pai1.first << " " <<pai1.second <<endl;

    pair<int,char> pai2=make_pair(10,'5');
    pair<int,char> pai3=pai2;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();
    test02();
    return 0;
}
