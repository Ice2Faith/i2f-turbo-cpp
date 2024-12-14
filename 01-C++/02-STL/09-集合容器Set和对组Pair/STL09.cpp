#include<iostream>
#include<set>
#include<iterator>
#include<algorithm>
using namespace std;
/**
set/multiset��������������������ƽ�����������ڶ�����Ϊ�ײ�ԭ��
Ӧ�ö�������ͼ
set:�������ظ�ֵ
multiset:�����ظ�ֵ
�ṩ��������������ͨ���������޸�ֵ
Ĭ����������
������insert

pair���飬������ֵ�ϳ�һ��ֵ�������ǲ�ͬ��������
*/
////////////////////////////////////////////////////////////////
class compareperson;
class person
{
private:
    int age;
    friend class compareperson;
public:
    person(int age):age(age){};
};
class compareperson{
public:
    bool operator()(const person& v1,const person& v2) const
    {
        return v1.age>v2.age;
    }
};

//�º���
class mycompare{
public:
    bool operator()(int v1,int v2)
    {
        return v1>v2;
    }
};

void Test01()
{
    //��ʼ���͸�ֵ
	set<int> set1;
	set1.insert(1);
	set1.insert(7);
	set1.insert(3);
	set1.insert(2);
	for(set<int>::iterator i=set1.begin();i!=set1.end();i++)
    {
        cout << (*i) <<" ";
    }
    cout<<endl;
    //��ֵ�ʹ�С = clear erase
    set<int> set2=set1;
    set2.erase(set2.begin());//ɾ��������λ��
    set2.erase(2);//ɾ��ָ��ֵ
    set2.erase(set2.begin(),set2.begin()++);//ɾ������������--�����ı����й�
    //����
    set2.clear();
    set2=set1;
    set2.insert(3);
    set2.insert(4);
    set2.insert(6);
   // set2.swap(set1);
    for(set<int>::iterator i=set1.begin();i!=set1.end();i++)
    {
        cout << (*i) <<" ";
    }
    cout<<endl;
    set<int>::iterator ret=set2.find(5);//���ҷ��ص�����
    if(ret==set2.end())
        cout << "Not Found"<<endl;

    //lower_bound() ���ص�һ��key���ڵ���ֵ�ĵ�����
    ret=set2.lower_bound(3);
    //upper_bound() ���ص�һ������ֵ�ĵ�����
    ret=set2.upper_bound(3);
    //equal_range() ����lower_bound �� upper_bound ��ֵ
    pair<set<int>::iterator,set<int>::iterator> mypair=set2.equal_range(3);
    if(mypair.first==set2.end())
         cout << "Not Found"<<endl;
    if(mypair.second==set2.end())
         cout << "Not Found"<<endl;

    //�ı�Ĭ���������,ʹ�÷º�����
    set<int,mycompare> set4;
    set4.insert(5);
    set4.insert(3);
    set4.insert(6);
    for(set<int>::iterator i=set4.begin();i!=set4.end();i++)
    {
        cout << (*i) <<" ";
    }
    cout<<endl;

    set<person,compareperson> set5;
    person p1(5),p2(8),p3(3);
    set5.insert(p1);
    set5.insert(p2);
    set5.insert(p3);
}
void test02()
{
    //���飬������ֵ�ϳ�һ��ֵ�������ǲ�ͬ��������
    //��ʼ���͸�ֵ
    pair<int,char> pai1(10,'5');
    cout << pai1.first << " " <<pai1.second <<endl;

    pair<int,char> pai2=make_pair(10,'5');
    pair<int,char> pai3=pai2;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();
    test02();
    return 0;
}
