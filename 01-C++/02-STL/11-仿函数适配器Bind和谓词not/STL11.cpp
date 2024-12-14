#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<functional>
using namespace std;
/**
仿函数适配器：bind1st bind2nd 绑定适配器
not1 not2 取反，一元，二元
unary_function 一元继承类
binary_function 二元继承类
find_if 查找第一个满足条件的
ptr_fun 普通函数转仿函数进行绑定
使用对象提供的函数
mem_fun_ref  使用对象引用时
mem_fun  使用对象指针时
*/
////////////////////////////////////////////////////////////////
class myPrint:public binary_function<int,int,void>//使用适配器必须进行继承
{
    //两个参数类型和返回值类型
public:
    void operator()(int a,int b=0)const//需要为const
    {
        cout << a<<" "<<(b) <<" ";
    }
};
void Test01()
{
    vector<int> myvec;
    for(int i=0; i<5; i++)
        myvec.push_back(i);
    myPrint PrintInt;
    for_each(myvec.begin(),myvec.end(),PrintInt);
    cout << endl;
    //将二元函数对象转换为一元函数对象
    //绑定为第二个参数
    for_each(myvec.begin(),myvec.end(),bind2nd(PrintInt,10));
    //绑定为第一个参数
    cout << endl;
    for_each(myvec.begin(),myvec.end(),bind1st(PrintInt,10));
}
//////////////////////
class myCompare:public binary_function<int,int,bool>
{
public:
    bool operator()(int v1,int v2)const
    {
        return v1>v2;
    }
};
void test02()
{
    vector<int> myvec;
    for(int i=0; i<5; i++)
        myvec.push_back(i);
    myCompare MyCmp;
    sort(myvec.begin(),myvec.end(),MyCmp);
    //对二元谓词取反用not2,一元用not1
    sort(myvec.begin(),myvec.end(),not2(MyCmp));
    myPrint PrintInt;
    for_each(myvec.begin(),myvec.end(),PrintInt);
}
///////////////////
class myFindMore:public unary_function<int,bool>
{
public:
    bool operator()(int v1)const
    {
        return v1>3;
    }
};
void test03()
{
    //find_if
    vector<int> myvec;
    for(int i=0; i<5; i++)
        myvec.push_back(i);
    myFindMore findmore;
    //查找第一个满足条件的
    vector<int>::iterator it=find_if(myvec.begin(),myvec.end(),not1(findmore));
    cout << *it <<endl;
}
/////////////////////
void printint(int val,int val2)
{
    cout << val <<" "<<val2<< " ";
}
void test04()
{
    //ptr_fun 普通函数转仿函数进行绑定
   vector<int> myvec;
    for(int i=0; i<5; i++)
        myvec.push_back(i);
    for_each(myvec.begin(),myvec.end(),bind2nd(ptr_fun(printint),10));
}
/////////////////
class Animal
{
public:
    Animal(int a):age(a){}
    void show()
    {
        cout << age <<" ";
    }
private:
    int age;
};
void test05()
{
    //使用对象提供的函数
    //mem_fun_ref  使用对象引用时
    //mem_fun  使用对象指针时
   vector<Animal> myvec;
    for(int i=0; i<5; i++)
    {
        Animal a(i);
         myvec.push_back(a);
    }

    for_each(myvec.begin(),myvec.end(),mem_fun_ref(&Animal::show));

    cout <<endl;
    vector<Animal*> pmyvec;
    for(int i=0; i<5; i++)
    {
        Animal* a=new Animal(i);
         pmyvec.push_back(a);
    }

    for_each(pmyvec.begin(),pmyvec.end(),mem_fun(&Animal::show));
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();
    cout << endl<<"---------------------"<<endl;
    test02();
    cout << endl<<"---------------------"<<endl;
    test03();
    cout << endl<<"---------------------"<<endl;
    test04();
    cout << endl<<"---------------------"<<endl;
    test05();
    return 0;
}
