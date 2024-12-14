#include<stdio.h>
#include<stdlib.h>
void help()
{
    printf("\tstring string string ...\n");
    printf("\t\tstring : a file/dir path\n");
    printf("\tsuch as:\n");
    printf("\t\topenfile C:\\n");
    printf("\t\topenfile cmd.exe\n");
    printf("\t\topenfile 001.txt\n");
}
int main(int argc,char * argv[])
{
    rename(argv[0],"openfile.exe");
    if(argc>1)
    {
        if(argv[1][0]=='?')
        {
            help();
            return 0;
        }
    }
    char temp[8192]= {0};
    for(int i=1; i<argc; i++)
    {
        sprintf(temp,"explorer %s\0",argv[i]);
        system(temp);
    }
    return 0;
}
