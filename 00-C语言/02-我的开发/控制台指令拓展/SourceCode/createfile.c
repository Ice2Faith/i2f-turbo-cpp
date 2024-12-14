#include<stdio.h>
int main(int argc,char * argv[])
{
    rename(argv[0],"createfile.exe");
    if(argc<=1 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("filename contextLine contextLine contextLine : create a file and input all of contextLine\n");
        printf("if filename is existed , it will be clear all context.\n");
    }
    else
    {
        FILE * fp=fopen(argv[1],"w");
        if(fp==NULL)
        {
            printf("create file failure.\n");
        }
        for(int i=2;i<argc;i++)
        {
            fprintf(fp,"%s\n",argv[i]);
        }
        fclose(fp);
    }
    return 0;
}
