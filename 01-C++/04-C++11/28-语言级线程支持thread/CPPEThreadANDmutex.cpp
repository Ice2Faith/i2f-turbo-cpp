#include<iostream>
#include<thread>//主要thread类，this_thread命名空间
#include<atomic>//主要两个原子操作类：atomic atomic_flag
#include<mutex>//主要互斥量相关的：mutex lock_guard unique_lock
#include<future>//主要声明：promise package_task 两个provider类
#include<chrono>//线程等待命名空间
#include<cstdarg>//可变参数
//以及future shared_future 两个类，async()也在其中
#include<condition_variable>//条件变量相关：condition_variable condition_varc
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
    拷贝构造函数被禁用，不可进行拷贝
    move（=重载）构造函数，剥夺原有线程所有权，赋予新线程
    可悲joinable的线程被销毁之前被主线程设置为join或者detached
    */
    cout << "Core:"<<thread::hardware_concurrency()<<endl;//获取CPU核心数
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
                      //线程等待，线程睡眠
                      this_thread::sleep_for(chrono::milliseconds(90));
                  }
              }
            ,slt//转换为引用传递
              );
    t2.detach();//脱离主线程，成为孤儿进程，主线程结束，子线程不报错，执行完自动退出
    //线程之间无法通信

    slt=100;
    thread t1([](int& beg)
              {
                  for(int i=0;i<5;i++)
                  {
                      cout << beg+i<<" "<<endl;
                      //线程等待，线程睡眠
                      this_thread::sleep_for(chrono::seconds(1));
                  }
              }
            ,ref(slt)//转换为引用传递
              );
    t1.join();//同步线程，等待线程结束
    t.join();

}
void Tmutex()
{
    mutex m;//使用信号量，防止线程之间进行不安全操作，但是加锁解锁耗时
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
    atomic_int sum{0};//使用原子变量，保证线程安全，计算速度一般，注意变量声明和初始化方式
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
    t1.join();//使用join，依次线程进行等待，线程安全，速度也很不错
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
                      this_thread::yield();//线程礼让，让CPU执行其他线程
                      sum++;
                  }
                  this_thread::sleep_for(chrono::seconds(2));//线程睡眠等待
                  cout << this_thread::get_id()<<endl;//线程id
              });
    t1.join();
    clock_t endt=clock();
    cout <<"SUM:"<< sum << " TIME:"<<endt-startt<<"ms"<<endl;

}
void Tmultivalue()
{
    thread t1([](const char * arg,...)
              {
                  va_list parg;//参数列表指针实质是 char *
                  va_start(parg,arg);//开始指针
                  //cout << va_arg(parg,int)<<endl;//按int大小取出一个值（实际为弹栈）
                  vprintf(arg,parg);//调用输出参数列表内容
                  va_end(parg);//置空指针
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
    swap(t1,t2);//交换线程
    thread t3=move(t1);//线程移动，t3获得管理权，t1销毁
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
