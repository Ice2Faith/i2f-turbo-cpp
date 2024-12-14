#include<stdio.h>
#include<stdlib.h>

void help()
{
    printf("\tstring string ...\n");
    printf("\t\tstring : any type file path\n");
    printf("\tsuch as:\n");
    printf("\t\temptyfile 001.txt 002.txt\n");
}
int main(int argc,char * argv[])
{
    rename(argv[0],"emptyfile.exe");
    if(argc>1)
    {
        if(argv[1][0]=='?')
        {
            help();
            return 0;
        }
    }
    FILE * fp=NULL;
    for(int i=1;i<argc;i++)
    {
        fp=fopen(argv[i],"wb");
        if(!fp)
            continue;
        fclose(fp);
    }
    return 0;
}
