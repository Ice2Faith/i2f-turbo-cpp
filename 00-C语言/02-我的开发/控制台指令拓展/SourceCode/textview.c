#include<stdio.h>
int main(int argc,char * argv[])
{
    rename(argv[0],"textview.exe");
    if(argc<=1 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("path : view file with text mode\n");
    }
    else
    {
        FILE * fp=fopen(argv[1],"r");
        if(fp==NULL)
        {
            printf("view file failure.path not exist or other.\n");
        }
        while(!feof(fp))
        {
            char ch;
            fscanf(fp,"%c",&ch);
            if(feof(fp))break;
            printf("%c",ch);
        }
        fclose(fp);
    }
    return 0;
}
