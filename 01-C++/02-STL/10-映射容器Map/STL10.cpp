#include<iostream>
#include<map>
#include<iterator>
#include<algorithm>
using namespace std;
/**
map��������Ƚ�set������key��value���Զ�����������key,key�����ظ�
key���ɸ��ģ�value���Ը���
multimap��key�����ظ���
map����ʹ�ö��鷽ʽ
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
    //��ʼ���͸�ֵ
    //key value
    map<int,char> map1;
    //����,ʹ��pair���룬pair.firstΪkey
    pair<int,char> temp(2,'A');
    map1.insert(temp);
    pair<map<int,char>::iterator,bool> ret=map1.insert(pair<int,char>(3,'B'));
    if(ret.second==false)
        cout << "����ʧ��"<<endl;//�������key�Ѵ��������ʧ��
    map1.insert(make_pair(4,'C'));
    map1.insert(map<int,char>::value_type(5,'D'));
    map1[6]='E';//�˷���key�������򴴽����������޸�value
    //���ŷ�ʽ���ʵ������ڵ�key����Ὣ�����map�У�value����Ĭ��ֵ�����ʱע��
    //����
    for(map<int,char>::iterator i=map1.begin();i!=map1.end();i++)
    {//ȡ���Ļ��Ƕ���pair
        cout << "key:"<<(*i).first << "," << "value:"<<(*i).second<<endl;
    }
    map<int,char> map2(map1);
    //
    map2.find(2);
    cout << "Range"<<endl;
    pair<map<int,char>::iterator,map<int,char>::iterator> tpret=map2.equal_range(2);
    cout << "key:" << tpret.first->first<<",value:"<<tpret.first->second<<endl;
    cout << "key:" << tpret.second->first<<",value:"<<tpret.second->second<<endl;
    //����
    map<mykey,int,mykeycompare> map3;
    map3.insert(make_pair(mykey(3),12));
}

void test02()
{
    //multimap������Ա�����ࣨ�����ţ�����Ƽ������źţ�ֵ��Ա����Ϣ���ࣩ��

}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
