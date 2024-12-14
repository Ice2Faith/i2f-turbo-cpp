#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace::std;
/*
���������㷨��
merge�㷨������������ͬһ�������кϲ�Ϊһ������
random_shuffle�㷨�����������������Ҫ֧���������
reverse�㷨����ת�������ݣ���Ҫ֧���������
*/
/*
����ģ�壺   merges����д��
���ܣ�       ����������1����������2�ϲ�Ϊ��������3
����Ҫ��   ����1,2,3�Ĵ�����Ҫһ��������Ҫ������߽���
                ����3���ÿռ������ڵ�������1,2�ĺ�
����˵��������1ʼĩ������������2ʼĩ������������3ʼ������
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
    //merge ��������ͬ��д
    vector<int> vec4;
    vec4.resize(vec3.size());
    //��ѡ����������ʽ��������
    merge(vec1.begin(),vec1.end(),\
            vec2.begin(),vec2.end(),\
            vec4.begin());
    PrintVectorInt(vec4.begin(),vec4.end());
    //��������random_shuffle
    random_shuffle(vec4.begin(),vec4.end());
    PrintVectorInt(vec4.begin(),vec4.end());
    //reverse��ת��������
    reverse(vec3.begin(),vec3.end());
    PrintVectorInt(vec3.begin(),vec3.end());

}
int main(int argc,char * argv[])
{
    test01();

    return 0;
}
