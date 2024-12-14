#include<iostream>
using namespace std;
/*
����ԭ��
ͨ��ֻ���Ӵ���ķ�ʽ�����޸Ĵ��빦�ܣ�����չ���ţ����޸Ĺر�
����Ķ����еĴ��빦�ܶ�����
��ͨ����̬�ķ�ʽʵ�ֳ����ࣨ�ӿڣ�
*/
/*
ʾ�����룺
������������ֻͨ����Ӵ���ķ�ʽʵ���µĹ���
ͨ��������ķ�ʽʵ��
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
