#include<iostream>
using namespace std;

class A;
typedef A TA;
class B
{
public:
    //������Ԫ���ʱ������Ҫ���class�ؼ��֣���������ʹ�������ı���typedef
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
    void fun() final;//ֻҪ����������Ϊvirtual�������Ͳ�����Ҫvirtual
    void meth() override;//���ظ���virtual���ε��麯�����
};
class drive:public base
{
public:
    //void fun();//�����Ѿ�����Ϊfinal���Ͳ�������д
    void meth();
};
//ģ�庯������������Ĭ�����ͣ������Զ������Ƶ�
template<typename T=int,typename E>
void func(E e=0,T t=0);
//����ʹ����ʽʵ�����ķ�ʽ����һ���ⲿģ�庯��
//extern template void funct<int>(int);
//����ʹ�þֲ�������������Ϊģ���ʵ��
//template <typename T> class X{};
//struct A{} a;
//X<A> x1;

//�̳и��๹�캯��
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
    //ʹ��using���̳и���Ĺ��캯��
};

//ί�ɹ��캯��
class Info
{
public:
    Info():Info(1,'a'){};
    Info(int x):Info(){m=x;};//���ܼ�ʹ��ί�ɹ��캯����ʹ�ó�ʼ���б�
    Info(char e):Info(1,e){};//���Խ����������캯��ʵ��
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
