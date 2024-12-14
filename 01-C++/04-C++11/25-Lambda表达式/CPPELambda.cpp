#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
/*
Lambda表达式：
[capture](params)opt->ret{body};
详解：
capture 捕获的引用参数列表,[]（不捕获任何）,[&]（按引用捕获所有外部作用域内）,[=]（按值捕获外部所有作用域内）
params 参数表
opt 选填mutable（可以修改外部捕获的引用参数），exception（说明是否抛出异常），attribute（说明属性）
ret 返回值类型，拖尾返回类型
body 函数体

    [函数体外部引用](参数列表)mutable exception -> 返回值类型{函数体}
    常见的：
    [](int v){}
    函数体外部引用：
        =（值传递）
        &（引用传递）
        this（当前类中的变量）
    mutable:
        [a] 相当于 [const a]
        去除值传递进来的[]号内的const限定，使得可改变
    exception:
        决定了是否要抛出异常
    返回值类型：
        []()->int{return 0;};
        如果只有一个return语句，可以不加，如果存在多个return就要添加
        如果不加编译器不能自动类型推到
    示例：
        int a,b;
        [a,&b](){}//对a值传递，b引用传递
    一般使用：[=](...){...}



*/
void TLambda()
{
   int a=0;
   auto func=[=]{return 10+a;};//值捕获
   cout << func()<<endl;
   auto afunc=[&]{return ++a;};//引用捕获
   cout << afunc()<<endl;
   int b=-1,c=-1;
   auto exfun=[=,&c]()->int{return a+b+(++c);};//除了c之外都是用值传递
   cout << exfun() <<endl;
   auto mufunc=[=]()mutable{return a++;};//使用功能mutable使得值传递也可以进行修改

   //统计容器中大于5的元素的个数
   vector<int> vint{1,3,8,2,7,5,6};
   auto cunt=count_if(vint.begin(),vint.end(),[](auto x){return x>5;});
   cout << cunt<<endl;

   //函数包装器结合
   function<bool(int,int)> more=[](int x,int y){return x>y;};

   //使用generate配合来生成数列放到容器中
   vector<int> vsqe(10);
   int i=0;
   generate(vsqe.begin(),vsqe.end(),[&i]{return i++;});

   //进行遍历输出
   for_each(vsqe.begin(),vsqe.end(),[](auto x){cout << x<<endl;});
}
int main()
{
    TLambda();
    return 0;
}
