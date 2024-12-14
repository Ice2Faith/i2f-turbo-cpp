#include <iostream>

using namespace std;
/*
抽象工厂模式：
产品生产地（产地）不同，工厂又生产不同产品（产品）时
针对产地进行抽象工厂，让不同的抽象工厂去生产多种产品
*/
class AbstractApple
{
public:
    virtual void showName()=0;
};
class AbstractOrange
{
public:
    virtual void showName()=0;
};
class AbstractFactory
{
public:
    virtual AbstractApple * CreateApple()=0;
    virtual AbstractOrange * CreateOrange()=0;
};
class CNApple :public AbstractApple
{
public:
    virtual void showName()
    {
        cout << "this is China apple"<<endl;
    }
};
class CNOrange :public AbstractOrange
{
public:
    virtual void showName()
    {
        cout << "this is China orange"<<endl;
    }
};
class USApple :public AbstractApple
{
public:
    virtual void showName()
    {
        cout << "this is American apple"<<endl;
    }
};
class USOrange :public AbstractOrange
{
public:
    virtual void showName()
    {
        cout << "this is American orange"<<endl;
    }
};

class ChinaFactory :public AbstractFactory
{
public:
    virtual AbstractApple * CreateApple()
    {
        return new CNApple();
    }

    virtual AbstractOrange * CreateOrange()
    {
        return new CNOrange();
    }
};
class AmericanFactory :public AbstractFactory
{
public:
    virtual AbstractApple * CreateApple()
    {
        return new USApple();
    }

    virtual AbstractOrange * CreateOrange()
    {
        return new USOrange();
    }
};
void test()
{
    AbstractFactory * fac=new ChinaFactory();
    AbstractApple * apple=fac->CreateApple();
    apple->showName();
    delete apple;
    delete fac;
    fac=new AmericanFactory();
    AbstractOrange * orange=fac->CreateOrange();
    orange->showName();
    delete orange;
    delete fac;
}

int main()
{
    test();
    return 0;
}

