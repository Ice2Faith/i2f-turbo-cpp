#include<iostream>
#include<vector>
/*
auto �ɱ������Զ��Ƶ��������ͣ�����˵��C++������һ������������
decltype() ����������ֵ�Զ��Ƶ����ͣ��÷�����sizeof
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
auto add(T x,E y)->decltype(x+y)//����auto��decltype��Ͻ���ģ����
{//->decltype(x+y) ��C++14����������ʡ�Դ˾䣬�����������
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
