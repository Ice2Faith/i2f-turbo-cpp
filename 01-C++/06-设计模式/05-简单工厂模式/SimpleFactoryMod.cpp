#include<iostream>
#include<string>
using namespace std;

/*
�򵥹���ģʽ��
ͨ��һ�������̣����������û�������Ҫ������������Ĳ�Ʒ�����󣩣������û��Լ�������������������
������ķ����������ڲ���ʵ���ϣ��������ڣ�
ȱ�㣺������Ҫ���ݲ����������ж��޸Ĵ��룬�����Ͽ���ԭ����˲�����
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
//������
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
//�û���
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
