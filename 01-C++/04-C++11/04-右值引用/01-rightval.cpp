#include<iostream>

using namespace::std;
/*
�ƶ����캯������һ����ֵ���ã�����һ����ʱ������
������ʱ�����ĵ�ַ�������Լ����ڰ���ʱ������ַ���գ�
ʵ����ȡ��ʱ�������ڴ棬ʵ�ֿ���
*/
class MemMove
{
public:
    MemMove():p(new int(3)){};
    MemMove(MemMove & m):p(new int(*m.p)){};
    MemMove(MemMove && m):p(m.p){m.p=nullptr;};//�ƶ����캯��������ʱ����ָ���ÿ�
private:
    int * p;

};
int main()
{
   MemMove a=0>1?MemMove():MemMove();
    return 0;
}
