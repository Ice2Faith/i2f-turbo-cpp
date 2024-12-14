#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
/**
string容器--字符串操作容器
*/
////////////////////////////////////////////////////////////////

void Test01()
{
    string str1,str2,str3;
    //c风格互转
    str1="abcdefg";
    str2="cde";
    char temp[1024]={0};
    sprintf(temp,"%s\0",str1.c_str());
    cout <<"风格转换"<<temp<<endl;
    //带异常检查
    try
    {
        str1.at(100)='A';
    }catch(...)
    {
        cout << "访问越界"<<endl;
    }
    //查找
    //首次
    cout <<"首次匹配"<< str1.find("cd") <<endl;
    //最后一次
    cout <<"最后一次匹配"<< str1.rfind("cd") <<endl;
    //替换
    //0位置开始2个字符替换为222
    str1.replace(0,2,"222");
    cout <<"替换后"<< str1<<endl;
    //比较
    cout <<"比较"<< str1.compare(str2)<<endl;
    //截取子串
    //截取0开始的3个
    str3=str1.substr(0,3);
    cout <<"子串"<<str3<<endl;
    //插入
    //2位置插入串
    str1.insert(2,"aaa");
    cout <<"插入"<<str1<<endl;
    //删除
    //从2开始3个
    str1.erase(2,3);
    cout <<"删除"<<str1<<endl;
}
////////////////////////////////////////////////////////////////
int main()
{
    Test01();

    return 0;
}
