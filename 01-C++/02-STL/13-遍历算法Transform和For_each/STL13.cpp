#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
/**
�����㷨��
transform ������1�����ÿ��ִֵ�������֮���������2
for_each ��ָ��������ÿ��ִֵ�в���
*/
////////////////////////////////////////////////////////////////
class myPlus{
public:
    int operator()(int val)
    {
        return val;
    }
};
void Test01()
{
    //transform ��һ��������Ԫ�ذ��˵���һ��������
    vector<int> vec1,vec2;
    for(int i=0;i<5;i++)
    {
        vec1.push_back(i);
    }
    vec2.resize(vec1.size());
    myPlus mp;
    //������1�����ÿ��ִֵ�������֮���������2
    transform(vec1.begin(),vec1.end(),vec2.begin(),mp);
    for(vector<int>::iterator i=vec2.begin();i!=vec2.end();i++)
    {
        cout << *i <<" ";
    }
    cout <<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
