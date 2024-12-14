#include<iostream>
#include<vector>
using namespace std;

template<typename T,typename E>
class point
{
public:
    point(T x,E y):x(x),y(y){}
private:
    T x;
    E y;
};
template<typename T>
using DBPOINT=point<T,double>;//为类设置一个别名，并且指明了一个类型

void Thand()
{
    //template class vector<bool>;//强行实例化
    //extern template class vector<int>;//不在该编译文件中实例化，在外部实例化
    vector<vector<int>> b;//>>不在不在会当做右移符号

    DBPOINT<int> ax(12,12.125);
}
template<typename T=int,typename E=int>//指定默认类型
auto add(T x,E y)->decltype(x+y)
{
    return x+y;
}
void TDefType()
{
    cout << add(12,15)<<endl;
}
int main()
{
    Thand();
    TDefType();
    return 0;
}
