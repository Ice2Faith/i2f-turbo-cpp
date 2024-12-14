#include<iostream>
using namespace std;

class A;
typedef A TA;
class B
{
public:
    //声明友元类的时候不在需要添加class关键字，甚至可以使用类名的别名typedef
    friend TA;

};

class baseinter
{
public:
    virtual void fun()=0;
    virtual void meth()=0;
};
class base:public baseinter
{
public:
    void fun() final;//只要父类型声明为virtual，子类型不在需要virtual
    void meth() override;//重载父类virtual修饰的虚函数标记
};
class drive:public base
{
public:
    //void fun();//父类已经声明为final，就不能在重写
    void meth();
};
//模板函数甚至可以有默认类型，依赖自动类型推到
template<typename T=int,typename E>
void func(E e=0,T t=0);
//可以使用显式实例化的方式申明一个外部模板函数
//extern template void funct<int>(int);
//可以使用局部和匿名类型作为模板的实参
//template <typename T> class X{};
//struct A{} a;
//X<A> x1;

//继承父类构造函数
class exbase
{
public:
    exbase(int p):a(p){};
private:
    int a;
};
class sexbase:exbase
{
public:
    using exbase::exbase;
    //使用using，继承父类的构造函数
};

//委派构造函数
class Info
{
public:
    Info():Info(1,'a'){};
    Info(int x):Info(){m=x;};//不能即使用委派构造函数又使用初始化列表
    Info(char e):Info(1,e){};//可以借助其他构造函数实现
private:
    Info(int x,char e):m(x),c(e){};
    int m;
    char c;
};

int main()
{
    B b;
    sexbase psb(12);
    return 0;
}
