#include<stdio.h>
int main(int argc,char * argv[])
{
    rename(argv[0],"addtofile.exe");
    if(argc<=1 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("filename contextLine contextLine contextLine : for a file add all of contextLine\n");
        printf("if filename not existed , it will be create the file and add contextLine.\n");
    }
    else
    {
        FILE * fp=fopen(argv[1],"a");
        if(fp==NULL)
        {
            printf("open file failure.\n");
        }
        for(int i=2;i<argc;i++)
        {
            fprintf(fp,"%s\n",argv[i]);
        }
        fclose(fp);
    }
    return 0;
}
