#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace::std;
/*
常用排序算法：
merge算法：对两个有序（同一种序）序列合并为一个序列
random_shuffle算法：随机打乱容器，需要支持随机访问
reverse算法：反转容器内容，需要支持随机访问
*/
/*
函数模板：   merges（自写）
功能：       将有序容器1和有序容器2合并为有序容器3
容器要求：   容器1,2,3的次序都需要一样，都需要升序或者降序，
                容器3可用空间必须大于等于容器1,2的和
参数说明：容器1始末迭代器，容器2始末迭代器，容器3始迭代器
*/
template<class T>
void merges(T fstbegin,T fstend,\
            T sndbegin,T sndend,\
            T thrbegin)
{
    T t1=fstbegin;
    T t2=sndbegin;
    T t3=thrbegin;
    if(*t1<=*(fstend-1))
    {
        while(t1!=fstend && t2!=sndend)
        {
            if(*t1<*t2)
            {
                *t3=*t1;
                t1++;
                t3++;
            }
            else
            {
                *t3=*t2;
                t2++;
                t3++;
            }

        }
    }
    else
    {
        while(t1!=fstend && t2!=sndend)
        {
            if(*t1>*t2)
            {
                *t3=*t1;
                t1++;
                t3++;
            }
            else
            {
                *t3=*t2;
                t2++;
                t3++;
            }

        }
    }
    while(t1!=fstend)
    {
        *t3=*t1;
        t1++;
        t3++;
    }
    while(t2!=sndend)
    {
        *t3=*t2;
        t2++;
        t3++;
    }
}
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
    for(int i=0; i<10; i++)
    {
        if(i%2)
        {
            vec1.push_back(i);
        }
        else
        {
            vec2.push_back(i);
        }
    }
    vec3.resize(vec1.size()+vec2.size());
    void (*PrintVectorInt)(vector<int>::iterator,vector<int>::iterator)\
                                =&PrintVector<vector<int>::iterator>;
    PrintVectorInt(vec1.begin(),vec1.end());
    PrintVectorInt(vec2.begin(),vec2.end());
    merges<vector<int>::iterator>(vec1.begin(),vec1.end(),\
                                  vec2.begin(),vec2.end(),\
                                  vec3.begin());
    PrintVectorInt(vec3.begin(),vec3.end());
    cout << "----------------------"<<endl;
    //merge 参数功能同自写
    vector<int> vec4;
    vec4.resize(vec3.size());
    //可选参数，排序方式添加在最后
    merge(vec1.begin(),vec1.end(),\
            vec2.begin(),vec2.end(),\
            vec4.begin());
    PrintVectorInt(vec4.begin(),vec4.end());
    //打乱容器random_shuffle
    random_shuffle(vec4.begin(),vec4.end());
    PrintVectorInt(vec4.begin(),vec4.end());
    //reverse反转容器内容
    reverse(vec3.begin(),vec3.end());
    PrintVectorInt(vec3.begin(),vec3.end());

}
int main(int argc,char * argv[])
{
    test01();

    return 0;
}
