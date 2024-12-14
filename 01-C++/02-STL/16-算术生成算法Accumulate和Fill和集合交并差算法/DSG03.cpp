#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<numeric>
using namespace::std;
/*
�������������㷨�ͼ����㷨��
accumulate ��ͣ�������ʼĩ����������ʼ��͵ĳ�ֵ
fill ��䣬������ʼĩ�����������ֵ
set_intersection �󽻼�������������1ʼĩ������������2ʼĩ������������3ʼ������������ֵ������λ��
set_union �󲢼�������������1ʼĩ������������2ʼĩ������������3ʼ������������ֵ������λ��
set_difference ��������������1ʼĩ������������2ʼĩ������������3ʼ������������ֵ������λ��
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
    //accumulate ��ͣ�������ʼĩ����������ʼ��͵ĳ�ֵ
   int sum= accumulate(vec1.begin(),vec1.end(),0);
    cout << sum <<endl;
    //fill ��䣬������ʼĩ�����������ֵ
    vec2.resize(10);
    fill(vec2.begin(),vec2.end(),10);
    PrintVector(vec2.begin(),vec2.end());
    cout << "-------------------"<<endl;
    vector<int> vec4;
    vec4.resize(20);
    //set_intersection �󽻼�������������1ʼĩ������������2ʼĩ������������3ʼ������������ֵ������λ��
    vector<int>::iterator endit=set_intersection(vec1.begin(),vec1.end(),vec3.begin(),vec3.end(),vec4.begin());
    PrintVector(vec4.begin(),endit);
    //set_union �󲢼�������������1ʼĩ������������2ʼĩ������������3ʼ������������ֵ������λ��
    endit=set_union(vec1.begin(),vec1.end(),vec3.begin(),vec3.end(),vec4.begin());
    PrintVector(vec4.begin(),endit);
    //set_difference ��������������1ʼĩ������������2ʼĩ������������3ʼ������������ֵ������λ��
    endit=set_difference(vec1.begin(),vec1.end(),vec3.begin(),vec3.end(),vec4.begin());
    PrintVector(vec4.begin(),endit);
}
int main(int argc,char * argv[])
{
    test01();

    return 0;
}
