#include<stdlib.h>
#include<windows.h>
#include<stdio.h>
void help()
{
    printf("\t ? : get help\n");
    printf("\t [num] : cmd sleep num(ms)\n");
    printf("\tsuch as:\n");
    printf("\tsleep\n");
    printf("\tsleep 500\n");
}
int main(int argc,char * argv[])
{
    rename(argv[0],"sleep.exe");
    int sleept=1000;
    if(argc<=1)
    {
        Sleep(sleept);
    }else
    {
        if(argv[1][0]=='?')
            help();
        else
        {
            sscanf(argv[1],"%d",&sleept);
            if(sleept<0)
                sleept=0-sleept;
            Sleep(sleept);
        }
    }
    return 0;
}
