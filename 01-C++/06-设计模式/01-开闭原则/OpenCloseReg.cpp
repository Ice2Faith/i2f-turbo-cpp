#include<iostream>
using namespace std;
/*
开闭原则：
通过只增加代码的方式进行修改代码功能，多扩展开放，对修改关闭
避免改动已有的代码功能而出错
即通过多态的方式实现抽象类（接口）
*/
/*
示例代码：
计算器，可以只通过添加代码的方式实现新的功能
通过抽象类的方式实现
*/
class AbstractCalculator
{
public:
    virtual int getRusult()=0;
    virtual void setOpratorNumber(int a,int b)=0;
};
class AddCalcultor:public AbstractCalculator
{
public:
    virtual int getRusult()
    {
        return ma+mb;
    }
    virtual void setOpratorNumber(int a,int b)
    {
        ma=a;
        mb=b;
    }
public:
    int ma;
    int mb;
};
class SubCalcultor:public AbstractCalculator
{
public:
    virtual int getRusult()
    {
        return ma-mb;
    }
    virtual void setOpratorNumber(int a,int b)
    {
        ma=a;
        mb=b;
    }
public:
    int ma;
    int mb;
};
void test()
{
    AbstractCalculator * cal=new AddCalcultor();
    cal->setOpratorNumber(10,20);
    cout << cal->getRusult() << endl;
    delete cal;
    cal=new SubCalcultor();
    cal->setOpratorNumber(10,20);
    cout << cal->getRusult() << endl;
}
int main()
{
    test();
    return 0;
}
