#include<iostream>
#include<stack>
#include<iterator>
using namespace std;
/**
Stack容器：push pop top,不提供迭代器，不能遍历，不能随机存取

*/
////////////////////////////////////////////////////////////////

void Test01()
{
    stack<int> sta1,sta2;
    //初始化和赋值
    sta1.push(4);
    sta1.push(5);
    sta1.push(6);
    sta2=sta1;
    stack<int> sta3(sta2);
    cout << sta1.top() <<endl;
    sta1.pop();
    //大小
    cout << sta1.size() <<endl;
    cout << sta1.empty() <<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
