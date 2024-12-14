#include<iostream>
#include<vector>
/*
auto 由编译器自动推导变量类型，这样说来C++可能是一个弱类型语言
decltype() 根据括号内值自动推导类型，用法类似sizeof
*/
using namespace::std;
void Tauto()
{
    auto a=12.125;//auto==double
    vector<int> vint;
    for(auto a=vint.begin();a!=vint.end();a++);//auto==vector<int>::iterator
    auto arr=new auto('a');//auto(arr)==char * cause of new
    int iarr[]={10,12,14};
    auto piarr=arr;//auto==int *
}
void Tdecltype()
{
    auto x=1;
    auto y=12.125;
    decltype(x+y) z;//decltype==double
    cout << z<<endl;
}
template<typename T,typename E>
auto add(T x,E y)->decltype(x+y)//利用auto与decltype结合进行模板编程
{//->decltype(x+y) 在C++14中甚至可以省略此句，编译器会完成
    return x+y;
}
int main()
{
   Tauto();
   Tdecltype();
   auto a=12;
   auto b=15.78;
   auto c=add(a,b);
   cout << c<<endl;
    return 0;
}
