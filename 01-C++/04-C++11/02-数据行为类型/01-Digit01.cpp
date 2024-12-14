#include<iostream>
#include<cstdio>
#include<cassert>
using namespace std;

void content01()
{
    //C++11中将char和wchar_t字符串连接时，会自动转换为wchar_t进行连接
    //至少要求64位
    long long a=99999999999999LL;//long long类型，大数后面加LL，和long long int,signed long long等等价
    a=0x7fffffffffffffff;
    printf("a=%lld\n",a);//输出long long 类型用lld或者llu
    //另外编译器可以自己实现拓展的整型，只要拥有有符号和无符号等长的位数即可
    int64_t b=0x7fffffffffffffff;
    printf("b=%lld\n",b);
}
void content02()
{
    int n=-1;
    assert(n>0);//断言语句，要求括号内条件表达式为真，否则进行断言报错
    //可以定义宏#define NDEBUG来禁用断言语句
    //静态断言static_assert，在编译时期就进行报错检查，判断表达式需要能在编译时期得到值
    //即常量表达式
    static_assert(-3>0,"this n cannot lower than 0.");
}
//标识修饰的函数不会抛出异常，括号内为true不会抛出异常，否则会抛出，括号内为常量表达式
//也可以只写noexcept,默认就为true
//可以有效的组织异常的扩散与传播，在C++11中析构函数默认也是noexcept的
void content03() noexcept(true)
{
    throw 2;
}
void content04()
{
    //C++11中允许就地对非静态成员进行初始化，通过等号或者花括号的方式
    //类成员变量也适用
    struct init
    {
        int a=1;
        double b{12.125};
    };
    //允许sizeof作用于非静态变量
    cout << "size b:"<<sizeof(init::b)<<endl;
}
int main(int argc,char * argv[])
{
    content01();
    //content02();
    try
    {
        content03();
    }catch(...)
    {
        cout << "Found Throw 2."<<endl;
    }
    content04();
    return 0;
}
