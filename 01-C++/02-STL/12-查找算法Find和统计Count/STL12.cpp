#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
/**
常用查找算法
find 查找值
binary_find 二分查找法
adjacent_find 查找相邻重复
find_if 根据条件查找第一个
count 统计出现次数
//count_if 根据条件统计次数
*/
////////////////////////////////////////////////////////////////
class Animal
{
public:
    Animal(int id,int age):id(id),age(age) {}
    bool operator==(const Animal& ani)const//需要进行比较需要重载运算符
    {
        return (this->id==ani.id && this->age==ani.age);
    }
    bool operator<(const Animal & ani)const//二分查找法需要
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
    //find 查找方法
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
    //binary_search 二分查找法
    if(true==binary_search(anivec.begin(),anivec.end(),ser) )
        cout << "Success Found Object!"<<endl;
    //adjacent_find 查找相邻重复
    it=adjacent_find(anivec.begin(),anivec.end());
    if(it!=anivec.end())
        it->show();
    else
        cout << "区间内没有找到重复元素!"<<endl;
    //find_if 根据条件查找第一个
    it=find_if(anivec.begin(),anivec.end(),mycompare);
    if(it!=anivec.end())
        it->show();
    else
        cout << "区间内没有找到元素!"<<endl;
    //count 统计出现次数
    Animal a4(4,24);
    int sum4=count(anivec.begin(),anivec.end(),a4);
    cout << sum4 <<endl;
    //count_if 根据条件统计次数
    int sum1=count(anivec.begin(),anivec.end(),a4);
    cout << sum4 <<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
