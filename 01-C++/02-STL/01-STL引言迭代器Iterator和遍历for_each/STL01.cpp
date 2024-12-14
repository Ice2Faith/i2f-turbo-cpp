#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
/**
����STL����ͱ����㷨��ʹ��--�������ļ�ʹ��
*/
//////////////////////////////////////////////////////////////
class Animal
{
public:
    virtual void speak()=0;
    virtual ~Animal(){};
};
class Cat:public Animal
{
public:
    virtual void speak()
    {
        std::cout << "Cat Speak" << std::endl;
    }
    virtual ~Cat(){};
};
class Dog:public Animal
{
public:
    virtual void speak()
    {
        std::cout << "Dog Speak" << std::endl;
    }
    virtual ~Dog(){};
};
//////////////////////////////////////////////////////////////////
void Test01()
{
    vector<Animal*> animal;
    animal.push_back(new Cat());
    animal.push_back(new Dog());
    vector<Animal*>::iterator i=animal.begin();
    for(;i!=animal.end();i++)
    {
        (*i)->speak();//i��ָ�룬*iȡ�������Ƕ���ָ��
        delete *i;
    }

}
////////////////////////////////////////////////////////////////////
void DoSpeak(Animal * p)
{
    p->speak();
    delete p;
}
void Test02()
{
    vector<Animal*> animal;
    animal.push_back(new Cat());
    animal.push_back(new Dog());
    for_each(animal.begin(),animal.end(),DoSpeak);
    //�����㷨����ʼ����β������Ӧλ�õ�ֵ���뺯��DoSpeak����
}
///////////////////////////////////////////////////////////////
int main()
{
    //Test01();
    //Test02();

    return 0;
}
