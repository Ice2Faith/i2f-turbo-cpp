#include<iostream>
#include<string>
using namespace std;

/*
工厂方法模式：
改进简单工厂中因为工厂需要根据参数生产导致的不符合开闭原则现象
方法为将工厂也进行抽象，具体化实现为不同类型的工厂
虽然方便修改了，但是类的数量会成倍的增长，也造成了维护的困难
*/
//抽象层
class AbstractFruit
{
public:
    virtual void ShowName()=0;
};
//实现层
class Apple : public AbstractFruit
{
    public:
    virtual void ShowName()
    {
        cout << "this is Apple" <<endl;
    }
};
class Orange : public AbstractFruit
{
    public:
    virtual void ShowName()
    {
        cout << "this is Orange" <<endl;
    }
};
class Pear : public AbstractFruit
{
    public:
    virtual void ShowName()
    {
        cout << "this is Pear" <<endl;
    }
};
//生产抽象层
class AbstractFruitFactory
{
public:
    virtual AbstractFruit* CreateFruit()=0;
};
//生产实现层
class AppleFruitFactory :public AbstractFruitFactory
{
public:
    virtual AbstractFruit* CreateFruit()
    {
        return new Apple();
    }
};
class OrangeFruitFactory :public AbstractFruitFactory
{
public:
    virtual AbstractFruit* CreateFruit()
    {
        return new Orange();
    }
};
class PearFruitFactory :public AbstractFruitFactory
{
public:
    virtual AbstractFruit* CreateFruit()
    {
        return new Pear();
    }
};
//用户层
void test()
{
    AbstractFruitFactory * fac=new AppleFruitFactory();
    AbstractFruit* fruit=fac->CreateFruit();
    fruit->ShowName();
    delete fruit;
    fac=new PearFruitFactory();
    fruit=fac->CreateFruit();
    fruit->ShowName();
    delete fruit;
}
int main()
{
    test();
    return 0;
}
