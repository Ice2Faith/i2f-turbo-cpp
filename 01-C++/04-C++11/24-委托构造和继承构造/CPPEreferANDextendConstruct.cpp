#include<iostream>
#include<vector>
using namespace std;
class Rect
{
public:
    Rect():Rect(0,0){}//ʹ��ί�й��������ʹ�ò����б�
    Rect(int w):Rect(w,0){}
    Rect(int w,int h):width(w),height(h){};
private:
    int width;
    int height;
};
class TraRect:Rect
{
public:
    TraRect(int w,int h):Rect(w,h){}//��ͳ�Ĳ���͸����û��ʲô�����
};
class ExtRect:Rect
{
public:
    using Rect::Rect;//�̳и��๹�캯��������͸��
};
int main()
{
    Rect rect;
    TraRect trect(12,10);
    ExtRect erect;
    return 0;
}
