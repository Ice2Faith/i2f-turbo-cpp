#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
/**
遍历算法：
transform 将容器1区间的每个值执行完操作之后放入容器2
for_each 对指定容器中每个值执行操作
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
    //transform 将一个容器中元素搬运到另一个容器中
    vector<int> vec1,vec2;
    for(int i=0;i<5;i++)
    {
        vec1.push_back(i);
    }
    vec2.resize(vec1.size());
    myPlus mp;
    //将容器1区间的每个值执行完操作之后放入容器2
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
