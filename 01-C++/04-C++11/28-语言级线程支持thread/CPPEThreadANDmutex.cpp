#include<iostream>
#include<thread>//��Ҫthread�࣬this_thread�����ռ�
#include<atomic>//��Ҫ����ԭ�Ӳ����ࣺatomic atomic_flag
#include<mutex>//��Ҫ��������صģ�mutex lock_guard unique_lock
#include<future>//��Ҫ������promise package_task ����provider��
#include<chrono>//�̵߳ȴ������ռ�
#include<cstdarg>//�ɱ����
//�Լ�future shared_future �����࣬async()Ҳ������
#include<condition_variable>//����������أ�condition_variable condition_varc
using namespace std;
/*
std::thread
std::mutex/std::unique_lock
std::future/std::packaged_task
std::condition_variable
*/
void Tthread()
{
    /*
    �������캯�������ã����ɽ��п���
    move��=���أ����캯��������ԭ���߳�����Ȩ���������߳�
    �ɱ�joinable���̱߳�����֮ǰ�����߳�����Ϊjoin����detached
    */
    cout << "Core:"<<thread::hardware_concurrency()<<endl;//��ȡCPU������
    thread t([]{
            for(int i=0;i<5;i++)
            {
                cout << i<<" "<<endl;
                this_thread::sleep_for(chrono::milliseconds(30));
            }
    });

    int slt=1000;
    thread t2([](int beg)
              {
                  for(int i=0;i<5;i++)
                  {
                      cout << beg+i<<" "<<endl;
                      //�̵߳ȴ����߳�˯��
                      this_thread::sleep_for(chrono::milliseconds(90));
                  }
              }
            ,slt//ת��Ϊ���ô���
              );
    t2.detach();//�������̣߳���Ϊ�¶����̣����߳̽��������̲߳�����ִ�����Զ��˳�
    //�߳�֮���޷�ͨ��

    slt=100;
    thread t1([](int& beg)
              {
                  for(int i=0;i<5;i++)
                  {
                      cout << beg+i<<" "<<endl;
                      //�̵߳ȴ����߳�˯��
                      this_thread::sleep_for(chrono::seconds(1));
                  }
              }
            ,ref(slt)//ת��Ϊ���ô���
              );
    t1.join();//ͬ���̣߳��ȴ��߳̽���
    t.join();

}
void Tmutex()
{
    mutex m;//ʹ���ź�������ֹ�߳�֮����в���ȫ���������Ǽ���������ʱ
    int n=100;
    int sum=0;
    clock_t startt=clock();
    thread t1([n,&sum,&m]
              {
                  for(int i=0;i<n;i++)
                  {
                      m.lock();
                      sum++;
                      m.unlock();
                  }
              });
    thread t2([n,&sum,&m]
              {
                  for(int i=0;i<n;i++)
                  {
                      m.lock();
                      sum++;
                      m.unlock();
                  }
              });
    t1.join();
    t2.join();
    clock_t endt=clock();
    cout <<"SUM:"<< sum << " TIME:"<<endt-startt<<"ms"<<endl;

}
void Tatomic()
{
    int n=100;
    atomic_int sum{0};//ʹ��ԭ�ӱ�������֤�̰߳�ȫ�������ٶ�һ�㣬ע����������ͳ�ʼ����ʽ
    clock_t startt=clock();
    thread t1([n,&sum]
              {
                  for(int i=0;i<n;i++)
                  {
                      sum++;
                  }
              });
    thread t2([n,&sum]
              {
                  for(int i=0;i<n;i++)
                  {
                      sum++;
                  }
              });
    t1.join();
    t2.join();
    clock_t endt=clock();
    cout <<"SUM:"<< sum << " TIME:"<<endt-startt<<"ms"<<endl;

}
void Tjoin()
{
    int n=100;
    int sum=0;
    clock_t startt=clock();
    thread t1([n,&sum]
              {
                  for(int i=0;i<n;i++)
                  {
                      sum++;
                  }
              });
    t1.join();//ʹ��join�������߳̽��еȴ����̰߳�ȫ���ٶ�Ҳ�ܲ���
    thread t2([n,&sum]
              {
                  for(int i=0;i<n;i++)
                  {
                      sum++;
                  }
              });

    t2.join();
    clock_t endt=clock();
    cout <<"SUM:"<< sum << " TIME:"<<endt-startt<<"ms"<<endl;

}
void Tyield()
{
    int n=100;
    int sum=0;
    clock_t startt=clock();
    thread t1([n,&sum]
              {
                  for(int i=0;i<n;i++)
                  {
                      this_thread::yield();//�߳����ã���CPUִ�������߳�
                      sum++;
                  }
                  this_thread::sleep_for(chrono::seconds(2));//�߳�˯�ߵȴ�
                  cout << this_thread::get_id()<<endl;//�߳�id
              });
    t1.join();
    clock_t endt=clock();
    cout <<"SUM:"<< sum << " TIME:"<<endt-startt<<"ms"<<endl;

}
void Tmultivalue()
{
    thread t1([](const char * arg,...)
              {
                  va_list parg;//�����б�ָ��ʵ���� char *
                  va_start(parg,arg);//��ʼָ��
                  //cout << va_arg(parg,int)<<endl;//��int��Сȡ��һ��ֵ��ʵ��Ϊ��ջ��
                  vprintf(arg,parg);//������������б�����
                  va_end(parg);//�ÿ�ָ��
              },"%d %s %f %c\n",12,"hello",12.125,'A');
    t1.join();
}
void Tswapmove()
{
    thread t1([]
              {
                    cout << "t1 "<<endl;
              });
    thread t2([]
              {
                    cout << "t2 "<<endl;
              });
    swap(t1,t2);//�����߳�
    thread t3=move(t1);//�߳��ƶ���t3��ù���Ȩ��t1����
    t3.join();
    t2.join();
}
int main()
{
    Tthread();
    Tmutex();
    Tatomic();
    Tjoin();
    Tyield();
    Tmultivalue();
    Tswapmove();
    return 0;
}
