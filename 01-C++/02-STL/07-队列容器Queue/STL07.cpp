#include<iostream>
#include<queue>
#include<iterator>
#include<algorithm>
using namespace std;
/**
queue���������в�����push pop front back
���ܱ�����û�е������������������
*/
////////////////////////////////////////////////////////////////

void Test01()
{
    queue<int> que1,que2;
    queue<int> que3(que1);
    //��ʼ���͸�ֵ
    que1.push(1);
    que1.push(2);
    cout << que1.front() << " " <<que1.back()<<endl;
    que1.pop();
    //��С
    cout << que1.empty() <<endl;
    cout << que1.size() <<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
