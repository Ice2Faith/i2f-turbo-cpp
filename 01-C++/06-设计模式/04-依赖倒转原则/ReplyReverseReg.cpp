#include<iostream>

using namespace std;

/*
依赖倒转原则：
面向抽象编程，底层实现去实现抽象接口（中层），高层逻辑去使用抽象接口。
实现双向的抽象，面向抽象编程，改变以往的自上而下调用逻辑，明确实例之间的关系过重
通过抽象类和多态实现
*/
//中层抽象层
class AbstractBankWork
{
public:
    virtual void DoWork()=0;
};
class SaveBankWork : public AbstractBankWork
{
    public:
    virtual void DoWork()
    {
        cout << "Bank Save Work" <<endl;
    }
};
//底层实现层
class PayBankWork : public AbstractBankWork
{
    public:
    virtual void DoWork()
    {
        cout << "Bank Pay Work" <<endl;
    }
};
class TransferBankWork : public AbstractBankWork
{
    public:
    virtual void DoWork()
    {
        cout << "Bank Transfer Work" <<endl;
    }
};
//高层业务层
void DoBankWork(AbstractBankWork * work)
{
    work->DoWork();
    delete work;
}
//用户使用层
void test()
{
    DoBankWork(new SaveBankWork());
    DoBankWork(new PayBankWork());
    DoBankWork(new TransferBankWork());
}
int main()
{
    test();
    return 0;
}
