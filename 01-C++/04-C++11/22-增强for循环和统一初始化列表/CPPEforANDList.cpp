#include<iostream>
#include<vector>
#include<initializer_list>
/*
for(auto i:vint) �������� ����������������
*/
using namespace::std;

void Tfor()
{
    vector<int> vint(5,10);
    for(auto & i:vint)//����ʹ�������ô��ݼ��ٸ��ƿ���
    {
        cout << i<<endl;
    }
}
class MyTest
{
public:
    MyTest(initializer_list<int> listval){};//ʹ�ù��캯��Ҳ����ʹ�ó�ʼ���б�
};
void TInitList()
{
    struct A
    {
        int a;
        double b;
    };
    struct B
    {
        B(int a,double b):a(a),b(b){}
    private:
        int a;
        double b;

    };
    //ͳһ��ʹ�ó�ʼ���������ʽ���в����б��ʼ��
    A a{1,1.1};
    B b{2,2.5};
    cout << a.b;
    MyTest myc={1,2,3,4,5};
    vector<int> vint={1,2,3,4,5};
}
int main()
{
    Tfor();
    TInitList();
    return 0;
}
