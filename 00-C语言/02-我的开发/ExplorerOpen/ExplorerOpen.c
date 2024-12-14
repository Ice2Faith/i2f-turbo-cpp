#include<stdio.h>
#include<stdlib.h>

int main(int count,char * path[])
{
    rename(path[0],"ExplorerOpen.exe");
    char mind[2048]={0};
    for(int i=1;i<count;i++)
    {
        sprintf(mind,"explorer %s\0",path[i]);
        system(mind);
    }
    return 0;
}
