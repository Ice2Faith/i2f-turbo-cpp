#include<stdio.h>
int main(int argc,char * argv[])
{
    rename(argv[0],"hexview.exe");
    if(argc<=1 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("path : view file with hex mode\n");
    }
    else
    {
        FILE * fp=fopen(argv[1],"rb");
        if(fp==NULL)
        {
            printf("view file failure.path not exist or other.\n");
        }
        int index=0;
        char buffer[32];
        int count=-1;
        while(!feof(fp))
        {
            char ch;
            fscanf(fp,"%c",&ch);
            buffer[index]=ch;
            if(feof(fp))break;
            index++;
            printf("%02x ",(unsigned short)(unsigned char)ch);
            count=(count+1)%32;
            if(count==15)
                printf("| ");
            if(count==31)
            {
                for(int j=0;j<index;j++)
                {
                    if(j==16)
                        printf(" | ");
                    if(buffer[j]>32&&buffer[j]<128)
                        printf("%c",buffer[j]);
                    else
                        printf(".");
                }
               printf("\n");
               index=0;
            }
        }
        fclose(fp);
        if(count<32)
        {
            for(;count<32-1;count++)
            {
                printf("   ");
            }
            for(int j=0;j<index;j++)
            {
                if(j==16)
                    printf(" | ");
                if(buffer[j]>32&&buffer[j]<128)
                    printf("%c",buffer[j]);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
    return 0;
}
