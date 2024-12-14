#include<iostream>
/*
NULL 被定义为了0，有时候对NULL进行引用时会因为0的意义变得不安全
nullptr 专门用来区分空指针和0，更加安全
*/
using namespace::std;

int main()
{
    int * a=nullptr;
    nullptr_t b;
    if(a==b)
        cout << "NUll Ptr"<<endl;
    return 0;
}
