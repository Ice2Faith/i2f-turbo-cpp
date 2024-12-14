#include<stdio.h>
#include<windows.h>
void Bell(int times)
{
    for(int i=0;i<times;i++)
    {
        printf("\a");
        Sleep(200);
    }
}
int main(int argc,char * argv[])
{
    rename(argv[0],"bell.exe");
    if(argc==1)
    {
        Bell(1);
    }else
    {
        if(argv[1][0]=='?')
        {
            printf("?: get help\n");
            printf("null : bell once\n");
            printf("number : bell number times\n");
        }else
        {
            int times;
            sscanf(argv[1],"%d",&times);
            Bell(times);
        }

    }
}
