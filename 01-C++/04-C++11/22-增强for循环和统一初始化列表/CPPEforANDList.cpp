#include<iostream>
#include<vector>
#include<initializer_list>
/*
for(auto i:vint) 变量类型 变量名：迭代对象
*/
using namespace::std;

void Tfor()
{
    vector<int> vint(5,10);
    for(auto & i:vint)//这里使用了引用传递减少复制开销
    {
        cout << i<<endl;
    }
}
class MyTest
{
public:
    MyTest(initializer_list<int> listval){};//使得构造函数也可以使用初始化列表
};
void TInitList()
{
    struct A
    {
        int a;
        double b;
    };
    struct B
    {
        B(int a,double b):a(a),b(b){}
    private:
        int a;
        double b;

    };
    //统一的使用初始化数组的形式进行参数列表初始化
    A a{1,1.1};
    B b{2,2.5};
    cout << a.b;
    MyTest myc={1,2,3,4,5};
    vector<int> vint={1,2,3,4,5};
}
int main()
{
    Tfor();
    TInitList();
    return 0;
}
