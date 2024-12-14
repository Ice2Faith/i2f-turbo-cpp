#include<iostream>
#include<vector>
using namespace std;
class Rect
{
public:
    Rect():Rect(0,0){}//使用委托构造后不能在使用参数列表
    Rect(int w):Rect(w,0){}
    Rect(int w,int h):width(w),height(h){};
private:
    int width;
    int height;
};
class TraRect:Rect
{
public:
    TraRect(int w,int h):Rect(w,h){}//传统的参数透传是没有什么意义的
};
class ExtRect:Rect
{
public:
    using Rect::Rect;//继承父类构造函数，避免透传
};
int main()
{
    Rect rect;
    TraRect trect(12,10);
    ExtRect erect;
    return 0;
}
