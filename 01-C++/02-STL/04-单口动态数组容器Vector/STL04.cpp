#include<iostream>
#include<vector>
#include<iterator>
using namespace std;
/**
vector容器--动态数组--单口容器，通常在尾部进行操作
*/
////////////////////////////////////////////////////////////////
//定义输出Vector的函数模板，T标识类型，TI标识该类型的迭代器类型
template<class T,class TI>
void PrintVector(T & vec)
{
    cout <<"[";
    for(TI i=vec.begin();i!=vec.end();i++)
    {
        cout << (*i);
        if(i+1!=vec.end())
            cout<<",";
    }
    cout <<"]"<<endl;
}
void Test01()
{
    //提供push_back 和 pop_back 方法
    //迭代器begin指向第一个，end指向最后一个的后一个
    //rbegin,rend反向迭代器
    //insert方法在指定位置插入
    //初始化
    int arr[]={0,1,2,3,4,5};
    //迭代器方式，填充10个3
    vector<int> vec1(arr,arr+sizeof(arr)/sizeof(int));
    vector<int> vec2(10,3);
    vector<int> vec3(vec1.begin(),vec1.end());
    vector<int>::iterator tp=vec1.begin();
    //构建函数指针方便书写
    void (*printVector)(vector<int> &)=&PrintVector<vector<int>,vector<int>::iterator>;
    printVector(vec1);
    printVector(vec2);
    printVector(vec3);
    //赋值
    vec2.assign(vec1.begin(),vec1.end());
    vec2.assign(10,3);
    vec2=vec3;
    //交换
    vec2.swap(vec3);//指针进行交换--相当于数组指针
    //大小操作
    //size返回个数，resize改变容器大小，empty判空，capacity容量
    cout <<"Size:"<< vec1.size() <<endl;
    cout << "IsEmpty:"<< (vec1.empty()?"NULL":"NotNULL") <<endl;
    vec1.resize(3);//参数：个数，默认值，比当前小则截断
    printVector(vec1);
    vec1.resize(8,1);//填充1
    printVector(vec1);
    cout<< vec1.capacity() <<endl;//计算最大容量>size
    //容量存在意义：减少申请空间次数和拷贝次数，增加运行速度
    //一般情况下成倍增长
    //存取操作
    cout << "存取控制"<<vec1.at(4) <<endl;  //拥有异常抛出机制
    vec1.at(4)=4;
    cout << vec1[4]<<endl;
    //front back 返回第一个和最后一个
    cout << vec1.front() << " " << vec1.back() <<endl;
    //插入和删除
    //insert push_back pop_back erase clear
    vec1.insert(vec1.begin()+2,60);//支持随机访问（支持[]形式或迭代器支持+num ）vector,可以加2
    vec1.push_back(80);
    printVector(vec1);
    vec1.erase(vec1.begin(),vec1.begin()+2);//删除前2个,单个参数删除单个值
    printVector(vec1);
    //巧用swap缩减空间，删除并不会缩减空间
    vec1.resize(6);
    vector<int>(vec1).swap(vec1);//巧用匿名对象交换，执行完后匿名对象自动化释放
    //reserve预留空间
    //判断是否重新申请空间
    int count=0;
    int * addr=NULL;
    vector<int> vec4;
    //vec4.reserve(101);//可以有效减少申请空间和复制数据次数
    for(int i=0;i<100;i++)
    {
        vec4.push_back(i);
        if(addr!=&(vec4[0]))
        {
            count++;
            addr=&(vec4[0]);
        }
    }
    cout <<"申请"<<count<<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
