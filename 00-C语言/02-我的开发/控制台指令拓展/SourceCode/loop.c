#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char * argv[])
{
    rename(argv[0],"loop.exe");
    if(argc<=1)
    {
        printf("? : get help\n");
        printf("number command command command ... : loop times to do command list\n");
        printf("example: loop 3 \"color f1\" \"title hello\"");
    }
    else
    {
        if(argv[1][0]=='?')
        {
            printf("? : get help\n");
            printf("number command command command ... : loop times to do command list\n");
            printf("example: loop 3 \"color f1\" \"title hello\"");
        }
        else
        {
            int times=0;
            sscanf(argv[1],"%d",&times);
            char * command=NULL;
            int len=0;
            for(int i=2;i<argc;i++)
            {
                len+=strlen(argv[i]);
                if(i>2)
                    len+=4;
            }
            ++len;
            command=(char *)malloc(sizeof(char)*len);
            strcpy(command,argv[2]);
            for(int i=3;i<argc;i++)
            {
                strcat(command," && ");
                strcat(command,argv[i]);
            }
            for(int i=0;i<times;i++)
            {
                system(command);
            }
            free(command);
        }
    }
    return 0;
}
