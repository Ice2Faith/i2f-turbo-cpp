#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void ModifyButtom(int count,char * paths[],char * buttom);
void help()
{
    printf("\tnewtail string string ...\n");
    printf("\t\tnewtail : new file tail\n");
    printf("\t\tstring : a file path\n");
    printf("\tsuch as:\n");
    printf("\t\trentail jpg 001.png 002.ico\n");
    printf("\t\trentail txt 001.c 002.cpp 003.htm\n");
}
int main(int argc,char * argv[])
{
    rename(argv[0],"rentail.exe");
    if(argc>1)
    {
        if(argv[1][0]=='?')
        {
            help();
            return 0;
        }
    }
    if(argc<3)
        return 0;
    if(strlen(argv[1])>19)
        return 0;
    for(int i=2;i<argc;i++)
    {
        ModifyButtom(argc-2,&argv[2],argv[1]);
    }
    return 0;
}
void ModifyButtom(int count,char * paths[],char * buttom)
{
    char  strs[4096]= {0};
    char  newpath[4096]= {0};
    int len=0;
    for(int i=0; i<count; i++)
    {
        FILE * file=fopen(paths[i],"r");
        if(!file)
            continue;
        else
            fclose(file);
        strcpy(strs,paths[i]);
        len=strlen(strs);
        int j=len-1;
        while(strs[j]!='.'&&strs[j]!='\\'&&j>0)
        {
            j--;
        }
        int k=j;
        if(strs[j]=='.')
            strs[j]=0;
        int success=1;
        int errortimes=0;
        while(0!=success)
        {
            strcpy(newpath,strs);
            if(errortimes!=0)
            {
                char temp[20]={0};
                sprintf(temp,"%d\0",errortimes);
                strcat(newpath,temp);
            }
            if(buttom[0]=='.')
                strcat(newpath,buttom);
            else
            {
                strcat(newpath,".");
                strcat(newpath,buttom);
            }
            success=rename(paths[i],newpath);
            errortimes++;
        }
    }
}
