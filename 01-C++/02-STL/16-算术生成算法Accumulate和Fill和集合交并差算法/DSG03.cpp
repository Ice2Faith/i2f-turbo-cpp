#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<numeric>
using namespace::std;
/*
常用算数生成算法和集合算法：
accumulate 求和，参数：始末迭代器，开始求和的初值
fill 填充，参数：始末迭代器，填充值
set_intersection 求交集，参数：容器1始末迭代器，容器2始末迭代器，容器3始迭代器，返回值结束的位置
set_union 求并集，参数：容器1始末迭代器，容器2始末迭代器，容器3始迭代器，返回值结束的位置
set_difference 求差集，参数：容器1始末迭代器，容器2始末迭代器，容器3始迭代器，返回值结束的位置
*/
template<class T>
void PrintVector(T vbegin,T vend)
{
    cout << "[ ";
    for(T i=vbegin; i!=vend; i++)
    {
        cout << *i ;
        if(i!=(vend-1))
            cout << ",";
    }
    cout << " ]"<<endl;
}
void test01()
{
    vector<int> vec1,vec2,vec3;
    for(int i=0;i<10;i++)
    {
        if(i<5)
            vec1.push_back(i);
        if(i>3)
            vec3.push_back(i);
    }
    //accumulate 求和，参数：始末迭代器，开始求和的初值
   int sum= accumulate(vec1.begin(),vec1.end(),0);
    cout << sum <<endl;
    //fill 填充，参数：始末迭代器，填充值
    vec2.resize(10);
    fill(vec2.begin(),vec2.end(),10);
    PrintVector(vec2.begin(),vec2.end());
    cout << "-------------------"<<endl;
    vector<int> vec4;
    vec4.resize(20);
    //set_intersection 求交集，参数：容器1始末迭代器，容器2始末迭代器，容器3始迭代器，返回值结束的位置
    vector<int>::iterator endit=set_intersection(vec1.begin(),vec1.end(),vec3.begin(),vec3.end(),vec4.begin());
    PrintVector(vec4.begin(),endit);
    //set_union 求并集，参数：容器1始末迭代器，容器2始末迭代器，容器3始迭代器，返回值结束的位置
    endit=set_union(vec1.begin(),vec1.end(),vec3.begin(),vec3.end(),vec4.begin());
    PrintVector(vec4.begin(),endit);
    //set_difference 求差集，参数：容器1始末迭代器，容器2始末迭代器，容器3始迭代器，返回值结束的位置
    endit=set_difference(vec1.begin(),vec1.end(),vec3.begin(),vec3.end(),vec4.begin());
    PrintVector(vec4.begin(),endit);
}
int main(int argc,char * argv[])
{
    test01();

    return 0;
}
