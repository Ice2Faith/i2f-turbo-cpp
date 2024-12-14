#include<iostream>
#include<string>
using namespace std;

/*
简单工厂模式：
通过一个生厂商（工厂）给用户生产需要（传入参数）的产品（对象），减少用户自己创建对象而出错的想象
将错误的发生限制在内部的实现上（工厂以内）
缺点：由于需要根据参数传递来判断修改代码，不符合开闭原则，因此并不好
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
//生产层
class FruitFactory
{
public:
    static AbstractFruit* CreateFruit(string name)
    {
        if(name=="apple")
            return new Apple();
        if(name=="orange")
            return new Orange();
        if(name=="pear")
            return new Pear();
        return NULL;
    }
};
//用户层
void test()
{
    AbstractFruit* fruit= FruitFactory::CreateFruit("apple");
    fruit->ShowName();
    delete fruit;
    fruit= FruitFactory::CreateFruit("orange");
    fruit->ShowName();
    delete fruit;
}
int main()
{
    test();
    return 0;
}
