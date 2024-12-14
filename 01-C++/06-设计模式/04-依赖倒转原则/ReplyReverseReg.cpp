#include<iostream>

using namespace std;

/*
������תԭ��
��������̣��ײ�ʵ��ȥʵ�ֳ���ӿڣ��в㣩���߲��߼�ȥʹ�ó���ӿڡ�
ʵ��˫��ĳ�����������̣��ı����������϶��µ����߼�����ȷʵ��֮��Ĺ�ϵ����
ͨ��������Ͷ�̬ʵ��
*/
//�в�����
class AbstractBankWork
{
public:
    virtual void DoWork()=0;
};
class SaveBankWork : public AbstractBankWork
{
    public:
    virtual void DoWork()
    {
        cout << "Bank Save Work" <<endl;
    }
};
//�ײ�ʵ�ֲ�
class PayBankWork : public AbstractBankWork
{
    public:
    virtual void DoWork()
    {
        cout << "Bank Pay Work" <<endl;
    }
};
class TransferBankWork : public AbstractBankWork
{
    public:
    virtual void DoWork()
    {
        cout << "Bank Transfer Work" <<endl;
    }
};
//�߲�ҵ���
void DoBankWork(AbstractBankWork * work)
{
    work->DoWork();
    delete work;
}
//�û�ʹ�ò�
void test()
{
    DoBankWork(new SaveBankWork());
    DoBankWork(new PayBankWork());
    DoBankWork(new TransferBankWork());
}
int main()
{
    test();
    return 0;
}
