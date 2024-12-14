#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
/*
Lambda���ʽ��
[capture](params)opt->ret{body};
��⣺
capture ��������ò����б�,[]���������κΣ�,[&]�������ò��������ⲿ�������ڣ�,[=]����ֵ�����ⲿ�����������ڣ�
params ������
opt ѡ��mutable�������޸��ⲿ��������ò�������exception��˵���Ƿ��׳��쳣����attribute��˵�����ԣ�
ret ����ֵ���ͣ���β��������
body ������

    [�������ⲿ����](�����б�)mutable exception -> ����ֵ����{������}
    �����ģ�
    [](int v){}
    �������ⲿ���ã�
        =��ֵ���ݣ�
        &�����ô��ݣ�
        this����ǰ���еı�����
    mutable:
        [a] �൱�� [const a]
        ȥ��ֵ���ݽ�����[]���ڵ�const�޶���ʹ�ÿɸı�
    exception:
        �������Ƿ�Ҫ�׳��쳣
    ����ֵ���ͣ�
        []()->int{return 0;};
        ���ֻ��һ��return��䣬���Բ��ӣ�������ڶ��return��Ҫ���
        ������ӱ����������Զ������Ƶ�
    ʾ����
        int a,b;
        [a,&b](){}//��aֵ���ݣ�b���ô���
    һ��ʹ�ã�[=](...){...}



*/
void TLambda()
{
   int a=0;
   auto func=[=]{return 10+a;};//ֵ����
   cout << func()<<endl;
   auto afunc=[&]{return ++a;};//���ò���
   cout << afunc()<<endl;
   int b=-1,c=-1;
   auto exfun=[=,&c]()->int{return a+b+(++c);};//����c֮�ⶼ����ֵ����
   cout << exfun() <<endl;
   auto mufunc=[=]()mutable{return a++;};//ʹ�ù���mutableʹ��ֵ����Ҳ���Խ����޸�

   //ͳ�������д���5��Ԫ�صĸ���
   vector<int> vint{1,3,8,2,7,5,6};
   auto cunt=count_if(vint.begin(),vint.end(),[](auto x){return x>5;});
   cout << cunt<<endl;

   //������װ�����
   function<bool(int,int)> more=[](int x,int y){return x>y;};

   //ʹ��generate������������зŵ�������
   vector<int> vsqe(10);
   int i=0;
   generate(vsqe.begin(),vsqe.end(),[&i]{return i++;});

   //���б������
   for_each(vsqe.begin(),vsqe.end(),[](auto x){cout << x<<endl;});
}
int main()
{
    TLambda();
    return 0;
}
