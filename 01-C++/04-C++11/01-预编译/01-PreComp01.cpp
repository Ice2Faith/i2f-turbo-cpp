#include<iostream>
using namespace std;
//利用__VA_ARGS__变长参数宏和__FILE__,__LINE__实现编译日志打印
#define LOG(...){\
    fprintf(stderr,"%s: Line %d:\t",__FILE__,__LINE__);\
    fprintf(stderr,__VA_ARGS__);\
    fprintf(stderr,"\n");\
}
void content01()
{
    cout << "Standard Clib:"<< __STDC_HOSTED__<<endl;//是否包含完整C库
    cout << "Standard C:"<< __STDC__<<endl;//是否与C标准一致
    //cout << "C Standard Version:"<<__STDC_VERSION__ endl;//所支持的C标准版本
    //cout << "ISO/IEC:"<<__STDC_ISO_10646__<<endl;//C++编译环境符合的ISO标准
    cout << "Function Name:"<<__func__<<endl;//所在函数的函数名
    _Pragma("once")//功能类似#pragma，使用类似sizeof()
    LOG("x=%d",3);
    //使用__cplusplus宏约束使用高于C++11的编译器才能使用
    #if __cplusplus <201103L
        #error "Should use C++11 implementation."
    #endif // __cplusplus
}
int main(int argc,char * argv[])
{
    content01();
    return 0;
}
