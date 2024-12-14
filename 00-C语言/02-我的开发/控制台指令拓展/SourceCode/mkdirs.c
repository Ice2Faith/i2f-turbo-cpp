#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
void help()
{
    printf("\tstring string ...\n");
    printf("\t\tstring : a path string\n");
    printf("\tsuch as:\n");
    printf("\t\tmkdirs 001\\002\\006\n");
    printf("\t\tmkdirs \"001\\003\\te st\\doc\" 001/002\n");
    printf("\t\n");
}

int main(int argc,char * argv[])
{
    rename(argv[0],"mkdirs.exe");
    if(argc>1)
    {
        if(argv[1][0]=='?')
        {
            help();
            return 0;
        }
    }
    char temp[8192]= {0};
    char md[8192]= {0};
    for(int i=1; i<argc; i++)
    {
        strcpy(temp,argv[i]);
        int j=0,k=0;
        int pt=0;
        while(temp[pt]!=0)
        {
            if(temp[pt]=='/')
                temp[pt]='\\';
            pt++;
        }
        printf("md : %s\n",temp);
        while(1)
        {
            while(temp[j]!='\0' && temp[j]!='\\')
            {
                md[k]=temp[j];
                k++;
                j++;
            }
            md[k]=0;
            mkdir(md);
            if(temp[j]=='\0')
                break;
            md[k]=temp[j];
            k++;
            j++;
        }

    }
    return 0;
}
