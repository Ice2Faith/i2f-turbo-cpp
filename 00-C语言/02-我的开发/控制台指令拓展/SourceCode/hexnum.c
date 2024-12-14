#include<stdio.h>
int main(int argc,char * argv[])
{
    rename(argv[0],"hexnum.exe");
   if(argc<=1 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("hexNumber hexNumber hexNumber ... : display hexNumber dec mode to screen.\n");
    }
    else
    {
        for(int i=1;i<argc;i++)
        {
            int num=0;
            int j=0;
            while(argv[i][j])
            {
                if(argv[i][j]>='0'&&argv[i][j]<='9')
                {
                    num*=16;
                    num+=argv[i][j]-'0';
                }else if(argv[i][j]>='a'&&argv[i][j]<='z')
                {
                    num*=16;
                    num+=argv[i][j]-'a'+10;
                }else if(argv[i][j]>='A'&&argv[i][j]<='Z')
                {
                    num*=16;
                    num+=argv[i][j]-'A'+10;
                }else
                {
                    printf("Error! hex number.\n");
                }
                j++;
            }
            printf("%d\n",num);
        }
    }
    return 0;
}
