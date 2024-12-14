#include<iostream>
#include<queue>
#include<iterator>
#include<algorithm>
using namespace std;
/**
queue容器：队列操作：push pop front back
不能遍历，没有迭代器，不能随机访问
*/
////////////////////////////////////////////////////////////////

void Test01()
{
    queue<int> que1,que2;
    queue<int> que3(que1);
    //初始化和赋值
    que1.push(1);
    que1.push(2);
    cout << que1.front() << " " <<que1.back()<<endl;
    que1.pop();
    //大小
    cout << que1.empty() <<endl;
    cout << que1.size() <<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
