#include<iostream>
#include<vector>
using namespace std;

template<typename T,typename E>
class point
{
public:
    point(T x,E y):x(x),y(y){}
private:
    T x;
    E y;
};
template<typename T>
using DBPOINT=point<T,double>;//Ϊ������һ������������ָ����һ������

void Thand()
{
    //template class vector<bool>;//ǿ��ʵ����
    //extern template class vector<int>;//���ڸñ����ļ���ʵ���������ⲿʵ����
    vector<vector<int>> b;//>>���ڲ��ڻᵱ�����Ʒ���

    DBPOINT<int> ax(12,12.125);
}
template<typename T=int,typename E=int>//ָ��Ĭ������
auto add(T x,E y)->decltype(x+y)
{
    return x+y;
}
void TDefType()
{
    cout << add(12,15)<<endl;
}
int main()
{
    Thand();
    TDefType();
    return 0;
}
