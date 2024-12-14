#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
/**
容器的嵌套--vector容器嵌套示例
*/
////////////////////////////////////////////////////////////////

void Test01()
{
    //容器嵌套
    vector<vector<int>> mapping;
    vector<vector<int>>::iterator e;
    //模拟3*10二维数组
    //创建
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

    //遍历
    for(e=mapping.begin(); e!=mapping.end(); e++)
    {
        for(vector<int>::iterator i=(*e).begin(); i!=(*e).end(); i++)
        {
            cout << *i <<" ";//实质上只有一层指针
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
