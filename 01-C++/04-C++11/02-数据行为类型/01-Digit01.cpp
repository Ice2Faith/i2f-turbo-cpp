#include<iostream>
#include<cstdio>
#include<cassert>
using namespace std;

void content01()
{
    //C++11�н�char��wchar_t�ַ�������ʱ�����Զ�ת��Ϊwchar_t��������
    //����Ҫ��64λ
    long long a=99999999999999LL;//long long���ͣ����������LL����long long int,signed long long�ȵȼ�
    a=0x7fffffffffffffff;
    printf("a=%lld\n",a);//���long long ������lld����llu
    //��������������Լ�ʵ����չ�����ͣ�ֻҪӵ���з��ź��޷��ŵȳ���λ������
    int64_t b=0x7fffffffffffffff;
    printf("b=%lld\n",b);
}
void content02()
{
    int n=-1;
    assert(n>0);//������䣬Ҫ���������������ʽΪ�棬������ж��Ա���
    //���Զ����#define NDEBUG�����ö������
    //��̬����static_assert���ڱ���ʱ�ھͽ��б����飬�жϱ��ʽ��Ҫ���ڱ���ʱ�ڵõ�ֵ
    //���������ʽ
    static_assert(-3>0,"this n cannot lower than 0.");
}
//��ʶ���εĺ��������׳��쳣��������Ϊtrue�����׳��쳣��������׳���������Ϊ�������ʽ
//Ҳ����ֻдnoexcept,Ĭ�Ͼ�Ϊtrue
//������Ч����֯�쳣����ɢ�봫������C++11����������Ĭ��Ҳ��noexcept��
void content03() noexcept(true)
{
    throw 2;
}
void content04()
{
    //C++11������͵ضԷǾ�̬��Ա���г�ʼ����ͨ���ȺŻ��߻����ŵķ�ʽ
    //���Ա����Ҳ����
    struct init
    {
        int a=1;
        double b{12.125};
    };
    //����sizeof�����ڷǾ�̬����
    cout << "size b:"<<sizeof(init::b)<<endl;
}
int main(int argc,char * argv[])
{
    content01();
    //content02();
    try
    {
        content03();
    }catch(...)
    {
        cout << "Found Throw 2."<<endl;
    }
    content04();
    return 0;
}
