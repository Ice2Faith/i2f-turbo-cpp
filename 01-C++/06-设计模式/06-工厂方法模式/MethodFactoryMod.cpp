#include<iostream>
#include<string>
using namespace std;

/*
��������ģʽ��
�Ľ��򵥹�������Ϊ������Ҫ���ݲ����������µĲ����Ͽ���ԭ������
����Ϊ������Ҳ���г��󣬾��廯ʵ��Ϊ��ͬ���͵Ĺ���
��Ȼ�����޸��ˣ��������������ɱ���������Ҳ�����ά��������
*/
//�����
class AbstractFruit
{
public:
    virtual void ShowName()=0;
};
//ʵ�ֲ�
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
//���������
class AbstractFruitFactory
{
public:
    virtual AbstractFruit* CreateFruit()=0;
};
//����ʵ�ֲ�
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
//�û���
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
