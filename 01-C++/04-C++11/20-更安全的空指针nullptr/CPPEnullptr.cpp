#include<iostream>
/*
NULL ������Ϊ��0����ʱ���NULL��������ʱ����Ϊ0�������ò���ȫ
nullptr ר���������ֿ�ָ���0�����Ӱ�ȫ
*/
using namespace::std;

int main()
{
    int * a=nullptr;
    nullptr_t b;
    if(a==b)
        cout << "NUll Ptr"<<endl;
    return 0;
}
