#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
/**
基本STL引入和遍历算法简单使用--迭代器的简单使用
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
        (*i)->speak();//i是指针，*i取出来的是对象指针
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
    //遍历算法，开始到结尾，将对应位置的值传入函数DoSpeak运行
}
///////////////////////////////////////////////////////////////
int main()
{
    //Test01();
    //Test02();

    return 0;
}
