#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<functional>
using namespace std;
/**
�º�����������bind1st bind2nd ��������
not1 not2 ȡ����һԪ����Ԫ
unary_function һԪ�̳���
binary_function ��Ԫ�̳���
find_if ���ҵ�һ������������
ptr_fun ��ͨ����ת�º������а�
ʹ�ö����ṩ�ĺ���
mem_fun_ref  ʹ�ö�������ʱ
mem_fun  ʹ�ö���ָ��ʱ
*/
////////////////////////////////////////////////////////////////
class myPrint:public binary_function<int,int,void>//ʹ��������������м̳�
{
    //�����������ͺͷ���ֵ����
public:
    void operator()(int a,int b=0)const//��ҪΪconst
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
    //����Ԫ��������ת��ΪһԪ��������
    //��Ϊ�ڶ�������
    for_each(myvec.begin(),myvec.end(),bind2nd(PrintInt,10));
    //��Ϊ��һ������
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
    //�Զ�Ԫν��ȡ����not2,һԪ��not1
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
    //���ҵ�һ������������
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
    //ptr_fun ��ͨ����ת�º������а�
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
    //ʹ�ö����ṩ�ĺ���
    //mem_fun_ref  ʹ�ö�������ʱ
    //mem_fun  ʹ�ö���ָ��ʱ
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
