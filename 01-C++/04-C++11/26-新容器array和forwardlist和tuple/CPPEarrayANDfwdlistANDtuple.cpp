#include<iostream>
#include<array>
#include<tuple>
#include<string>
using namespace std;
/*
array ��һ������vector�������������Ǳ�����ջ���ģ�������ܸ��ã����ܹ���ʽת��Ϊָ��
����ʱ�����̶���С���飬ֻ��Ҫָ�����ͺʹ�С����

*/
void Tarray()
{
    array<int,5> arr{1,2,3,4,5};//���ȱ����ǳ������߳������ʽ
    int * parr=&arr[0];
    parr=arr.data();
    parr=nullptr;//ת��Ϊָ��Ĳ���
    //forward_list<int> flist;
    //������list˫������ĵ��������ռ������ʺ����ʶ�����
    /*
    ������������������
    unordered_map
    unordered_multimap
    unordered_set
    unordered_multiset
    ��ͬ��set��map�ڲ�ͨ�������ʵ�֣�����hash��ʵ��
    */
}
void Ttuple()
{
    //����һ���������ɲ�ͬ���͵Ľṹ��
    tuple<int,double,string> tps(12,17.58,"pixel");
    auto tp=make_tuple(5,12.125,"hello");//����Ԫ�飬�����ƶ�Ϊtuple<int,double,string>
    cout << get<2>(tp)<<endl;//��ȡԪ�أ��޷�ʹ�ñ����±�
    int id;
    double bim;
    string item;
    tie(id,bim,item)=tp;//Ԫ����
    cout << id<<" "<<bim<<" "<<item<<endl;
    auto ntp=tuple_cat(tps,tp);//Ԫ�������
    /*
    pair��һ��������Ա�Ľṹ��
    */
    auto p1=make_pair(12,'c');
    pair<double,int> p2(12.125,17);
    cout << p2.first <<" "<<p2.second<<endl;
    p2=make_pair(1,1.2);
    p2=p1;//һ�����г�Ա�����Ľṹ��
    //pair����ʹ��typedef���м�����
}
int main()
{
    Tarray();
    Ttuple();
    return 0;
}
