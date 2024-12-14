#include<stdio.h>
const char HexTable[16][5]={
{"0000"},
{"0001"},
{"0010"},
{"0011"},
{"0100"},
{"0101"},
{"0110"},
{"0111"},
{"1000"},
{"1001"},
{"1010"},
{"1011"},
{"1100"},
{"1101"},
{"1110"},
{"1111"}
};
int main(int argc,char * argv[])
{
    rename(argv[0],"numbin.exe");
   if(argc<=1 || argv[1][0]=='?')
    {
        printf("? : get help\n");
        printf("number number number ... : display number binary to screen.\n");
    }
    else
    {
        int num=0;
        char hexnum[256];
        for(int i=1;i<argc;i++)
        {
          sscanf(argv[i],"%d",&num);
          sprintf(hexnum,"%0x\0",num);
          int j=0;
          while(hexnum[j])
          {
              if(hexnum[j]>='0'&&hexnum[j]<='9')
              {
                  printf("%s ",HexTable[hexnum[j]-'0']);
              }else
              {
                  printf("%s ",HexTable[hexnum[j]-'a'+10]);
              }
              j++;
          }
          printf("\n");
        }
    }
    return 0;
}
