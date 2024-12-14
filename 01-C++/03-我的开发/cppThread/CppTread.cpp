#include<iostream>
#include<thread>
#include<string.h>
#include<windows.h>

using namespace std;

void OutputInt(char a)
{
    cout << a ;
}

int main(int argc,char * argv[])
{

    int endt=0;
    thread tp([]
    {
        int count=0;
        char ch[24]={"123456789\0"};
        for(int i=0; ch[i]; i++)
        {

            thread run(OutputInt,ch[i]);
            run.detach();
            count++;
        }
        while(count<strlen(ch));
    }

             );
    tp.join();

    cout << "@@\n";
    return 0;
}
