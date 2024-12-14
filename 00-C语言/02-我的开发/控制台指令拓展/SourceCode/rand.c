#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void help()
{
    printf("\t? : get help\n");
    printf("\td num [c count] : get random num between 0 and num\n");
    printf("\tb num1 num2 [c count] : get random num between num1 and num2\n");
    printf("\t[c count] : get amount count random num\n");
    printf("\tsuch as:\n");
    printf("\trand d 100\n");
    printf("\trand d 100 c 5\n");
    printf("\trand b 50 100 c 20\n");
}
int main(int argc,char * argv[])
{
    rename(argv[0],"rand.exe");
    srand((unsigned int )time(NULL));
    srand(rand()+rand()%1000);
    int num1=0,num2=100;
    if(argc<=1)
    {
        printf("%d\n",rand()%100);
    }else
    {
        if(argv[1][0]=='?')
        {
            help();
        }else
        {
            if(argv[1][0]=='d'||argv[1][0]=='D')
            {
                if(sscanf(argv[2],"%d",&num1)==EOF)
                {
                    printf("error value(s),please input \"rand ?\"\n");
                    return 0;
                }
                if(argc>=5)
                {
                    if(argv[3][0]=='C'||argv[3][0]=='c')
                    {
                        int loop=1;
                        if(sscanf(argv[4],"%d",&loop)!=EOF)
                        {
                            for(int i=0;i<loop;i++)
                            {
                                printf("%d ",rand()%(num1+1));
                            }
                            return 0;
                        }
                    }

                }
                printf("%d ",rand()%(num1+1));
            }else if(argv[1][0]=='b'||argv[1][0]=='B')
            {
                if(argc<4)
                    return 0;
                if(sscanf(argv[2],"%d",&num1)==EOF || sscanf(argv[3],"%d",&num2)==EOF)
                {
                    printf("error value(s),please input \"rand ?\"\n");
                    return 0;
                }
                if(num2<num1)
                {
                    num1^=num2;
                    num2^=num1;
                    num1^=num2;
                }
                if(argc>=6)
                {
                    if(argv[4][0]=='C'||argv[4][0]=='c')
                    {
                        int loop=1;
                        if(sscanf(argv[5],"%d",&loop)!=EOF)
                        {
                            for(int i=0;i<loop;i++)
                            {
                                printf("%d ",rand()%(num2-num1+1)+num1);
                            }
                            return 0;
                        }
                    }

                }

                printf("%d ",rand()%(num2-num1+1)+num1);
            }
        }
    }
    return 0;
}
