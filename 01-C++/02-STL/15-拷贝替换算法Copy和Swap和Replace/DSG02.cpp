#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace::std;
/*
���õĿ����滻�㷨��
copy ����,����������1ʼĩ������������2ʼ������
swap �����㷨,��������������
replace �滻ֵ��������ʼĩ��������λ�ã���ֵ
replace_if �������滻��������ʼĩ���������滻��������ֵ
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
class mycompare
{
public:
    bool operator()(const int a)const
    {
        return a>7;
    }

};
void test01()
{
    vector<int> vec1,vec2,vec3;
    for(int i=0;i<10;i++)
    {
        if(i<5)
            vec1.push_back(i);
        else
            vec3.push_back(i);
    }
    PrintVector(vec1.begin(),vec1.end());
    //copy ����,����������1ʼĩ������������2ʼ������
    vec2.resize(vec1.size());
    copy(vec1.begin(),vec1.end(),vec2.begin());
    PrintVector(vec2.begin(),vec2.end());
    //swap �����㷨,��������������
    swap(vec1,vec3);
    PrintVector(vec3.begin(),vec3.end());
    cout << "--------------------"<<endl;
    PrintVector(vec1.begin(),vec1.end());
    //replace �滻ֵ��������ʼĩ��������λ�ã���ֵ
    replace(vec1.begin(),vec1.end(),8,20);
    PrintVector(vec1.begin(),vec1.end());
    //replace_if �������滻��������ʼĩ���������滻��������ֵ
    replace_if(vec1.begin(),vec1.end(),mycompare(),30);
    PrintVector(vec1.begin(),vec1.end());
}
int main(int argc,char * argv[])
{
    test01();

    return 0;
}
