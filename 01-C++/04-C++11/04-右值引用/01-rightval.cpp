#include<iostream>

using namespace::std;
/*
移动构造函数接受一个右值引用，这是一个临时变量，
将其临时变量的地址拷贝给自己，在把临时变量地址赋空，
实现窃取临时变量的内存，实现拷贝
*/
class MemMove
{
public:
    MemMove():p(new int(3)){};
    MemMove(MemMove & m):p(new int(*m.p)){};
    MemMove(MemMove && m):p(m.p){m.p=nullptr;};//移动构造函数，将临时变量指针置空
private:
    int * p;

};
int main()
{
   MemMove a=0>1?MemMove():MemMove();
    return 0;
}
