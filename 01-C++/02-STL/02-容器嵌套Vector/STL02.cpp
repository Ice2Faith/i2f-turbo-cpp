#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
/**
������Ƕ��--vector����Ƕ��ʾ��
*/
////////////////////////////////////////////////////////////////

void Test01()
{
    //����Ƕ��
    vector<vector<int>> mapping;
    vector<vector<int>>::iterator e;
    //ģ��3*10��ά����
    //����
    for(int n=0; n<3; n++)
    {
        vector<int> t;
        mapping.push_back(t);
        e=mapping.begin();
        e+=n;
        for(int i=0; i<10; i++)
        {
            (*e).push_back(i);
        }
    }

    //����
    for(e=mapping.begin(); e!=mapping.end(); e++)
    {
        for(vector<int>::iterator i=(*e).begin(); i!=(*e).end(); i++)
        {
            cout << *i <<" ";//ʵ����ֻ��һ��ָ��
        }
        cout << endl;
    }
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
