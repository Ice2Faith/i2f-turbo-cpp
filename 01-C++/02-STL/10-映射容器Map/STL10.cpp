#include<iostream>
#include<map>
#include<iterator>
#include<algorithm>
using namespace std;
/**
map容器：相比较set，具有key和value，自动排序，排序按照key,key不能重复
key不可更改，value可以更改
multimap的key可以重复，
map插入使用对组方式
*/
////////////////////////////////////////////////////////////////
class mykey
{
public:
    int mkey;
    mykey(int key):mkey(key){};
};
class mykeycompare
{
public:
    bool operator()(const mykey & v1,const mykey & v2)const
    {
        return v1.mkey>v2.mkey;
    }
};
void Test01()
{
    //初始化和赋值
    //key value
    map<int,char> map1;
    //插入,使用pair插入，pair.first为key
    pair<int,char> temp(2,'A');
    map1.insert(temp);
    pair<map<int,char>::iterator,bool> ret=map1.insert(pair<int,char>(3,'B'));
    if(ret.second==false)
        cout << "插入失败"<<endl;//如果主键key已存在则插入失败
    map1.insert(make_pair(4,'C'));
    map1.insert(map<int,char>::value_type(5,'D'));
    map1[6]='E';//此方法key不存在则创建，存在则修改value
    //括号方式访问到不存在的key，则会将其插入map中，value给定默认值，输出时注意
    //遍历
    for(map<int,char>::iterator i=map1.begin();i!=map1.end();i++)
    {//取出的还是对组pair
        cout << "key:"<<(*i).first << "," << "value:"<<(*i).second<<endl;
    }
    map<int,char> map2(map1);
    //
    map2.find(2);
    cout << "Range"<<endl;
    pair<map<int,char>::iterator,map<int,char>::iterator> tpret=map2.equal_range(2);
    cout << "key:" << tpret.first->first<<",value:"<<tpret.first->second<<endl;
    cout << "key:" << tpret.second->first<<",value:"<<tpret.second->second<<endl;
    //补充
    map<mykey,int,mykeycompare> map3;
    map3.insert(make_pair(mykey(3),12));
}

void test02()
{
    //multimap案例：员工分类（按部门），设计键（部门号）值（员工信息（类））

}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
