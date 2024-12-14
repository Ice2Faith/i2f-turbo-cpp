#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
/**
���ò����㷨
find ����ֵ
binary_find ���ֲ��ҷ�
adjacent_find ���������ظ�
find_if �����������ҵ�һ��
count ͳ�Ƴ��ִ���
//count_if ��������ͳ�ƴ���
*/
////////////////////////////////////////////////////////////////
class Animal
{
public:
    Animal(int id,int age):id(id),age(age) {}
    bool operator==(const Animal& ani)const//��Ҫ���бȽ���Ҫ���������
    {
        return (this->id==ani.id && this->age==ani.age);
    }
    bool operator<(const Animal & ani)const//���ֲ��ҷ���Ҫ
    {
        return this->id<ani.id;
    }
    void show()
    {
        cout << this->id << " " <<this->age<<endl;
    }
private:
    int id;
    int age;
};
bool mycompare(Animal & ani)
{
    Animal tp(3,23);
    return tp==ani;
}
bool mysearch(Animal& ani)
{
    Animal tp(1,21);
    return tp==ani;
}
void Test01()
{
    //find ���ҷ���
    vector<Animal> anivec;
    for(int i=0; i<5; i++)
    {
        Animal ani(i,i+20);
        anivec.push_back(ani);
    }
    Animal ser(2,22);
    vector<Animal>::iterator it=find(anivec.begin(),anivec.end(),ser);
    if(it!=anivec.end())
        it->show();
    //binary_search ���ֲ��ҷ�
    if(true==binary_search(anivec.begin(),anivec.end(),ser) )
        cout << "Success Found Object!"<<endl;
    //adjacent_find ���������ظ�
    it=adjacent_find(anivec.begin(),anivec.end());
    if(it!=anivec.end())
        it->show();
    else
        cout << "������û���ҵ��ظ�Ԫ��!"<<endl;
    //find_if �����������ҵ�һ��
    it=find_if(anivec.begin(),anivec.end(),mycompare);
    if(it!=anivec.end())
        it->show();
    else
        cout << "������û���ҵ�Ԫ��!"<<endl;
    //count ͳ�Ƴ��ִ���
    Animal a4(4,24);
    int sum4=count(anivec.begin(),anivec.end(),a4);
    cout << sum4 <<endl;
    //count_if ��������ͳ�ƴ���
    int sum1=count(anivec.begin(),anivec.end(),a4);
    cout << sum4 <<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
