#include"Base64.h"
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 2048
#define BASE_EXC_MODE int
#define BASE_S2B 0
#define BASE_B2S 1
#define MAXLINE 4096
void StringBase64();
void FileBase64(char * path,BASE_EXC_MODE mode);
int main(int argc,char * argv[])
{
    if(argc>1)
    {
        BASE_EXC_MODE mode;
        printf("please select running mode:1 to base64,0 to string\n>/ ");
        char msel=0;
        while(msel<'0'||msel>'1')
            msel=getch();
        printf("%c\n",msel);
        if(msel=='0')
            mode=BASE_B2S;
        else
            mode=BASE_S2B;
        for(int i=1; i<argc; i++)
        {
            FileBase64(argv[i],mode);
        }
        return 0;
    }
    printf("\t   Base64 Tool\n\n");
    printf("\t1.from input\n");
    printf("\t2.from file\n");
    printf("\t0.exit\n");
    printf("please select\n>/ ");
    char sel='\0';
    while(sel<'0'||sel>'2')
        sel=getch();
    printf("%c\n",sel);
    switch(sel)
    {
    case '1':
        StringBase64();
        break;
    case '2':
    {

        char path[1024]= {0};
        printf("please input file path\n>/ ");
        scanf("%s",&path);
        BASE_EXC_MODE mode;
        printf("please select running mode:1 to base64,0 to string\n>/ ");
        char msel=0;
        while(msel<'0'||msel>'1')
            msel=getch();
        printf("%c\n",msel);
        if(msel=='0')
            mode=BASE_B2S;
        else
            mode=BASE_S2B;
        FileBase64(path,mode);
        break;
    }

    case '0':
        exit(0);
        break;

    }

    return 0;
}
void FileBase64(char * path,BASE_EXC_MODE mode)
{
    FILE * SI=fopen(path,"r");
    if(!SI)
        return;
    char savepath[1024]= {0};
    strcpy(savepath,path);
    if(mode==BASE_S2B)
    {
        strcat(savepath,"_b64.txt");
    }
    else if(mode==BASE_B2S)
    {
        strcat(savepath,".txt");
    }
    else
        return;
    FILE * DI=fopen(savepath,"w");
    char strtemp[MAXLINE]= {0};
    char base64temp[MAXLINE*4/3]= {0};
    while(!feof(SI))
    {
        if(mode==BASE_S2B)
        {
            if(fgets(strtemp,MAXLINE-1,SI)==0)
                break;
            strtemp[strlen(strtemp)-1]='\0';
            Base64(strtemp,base64temp,sizeof(base64temp),BASE_NORMAL_STR);
            fprintf(DI,"%s\n",base64temp);

        }
        else
        {
            if(fgets(base64temp,MAXLINE*4/3-1,SI)==0)
                break;
            base64temp[strlen(base64temp)-1]='\0';
            Anti_Base64(base64temp,strtemp,sizeof(strtemp),BASE_NORMAL_STR);
            fprintf(DI,"%s\n",strtemp);

        }
    }
    fclose(SI);
    fclose(DI);
}
void StringBase64()
{
    char str[MAX]= {"\0"};
    char save[MAX*4/3+5];
    system("color f1");
    system("title Base64 transvertor dev Ice2Fath");
    BASE_MODE mode;
    printf("\t  Base64 transvertor\n\n");
    printf("\t1.Normal string\n");
    printf("\t2.URL string\n");
    printf("\t3.EXP string\n");
    printf("\t4.XML NmToken\n");
    printf("\t5.XML Name\n");
    printf("\t6.China string\n");
    printf("\t0.exit\n\n");
    printf("\tPlease select base64 type\n>/ ");
    char sel='\0';
    while(sel<'0'||sel>'6')
        sel=getch();
    printf("%c\n",sel);
    switch(sel)
    {
    case '1':
        mode=BASE_NORMAL_STR;
        break;
    case '2':
        mode=BASE_URL;
        break;
    case '3':
        mode=BASE_EXP;
        break;
    case '4':
        mode=BASE_XML_NMTOKEN;
        break;
    case '5':
        mode=BASE_XML_NAME;
        break;
    case '6':
        mode=BASE_CHINA;
        break;
    case '0':
        exit(0);
        break;
    }
    while(1)
    {
        printf("\t   Base64 transvertor\n\n");
        printf("\t1. string to base64\n");
        printf("\t2. base64 to string\n");
        printf("\t0. exit\n");
        char sel='\0';
        while(sel<'0'||sel>'2')
            sel=getch();
        printf("%c\n",sel);
        if(sel=='0')
            exit(0);
        printf("please input string:\n>/ ");
        gets(str);
        if(sel=='1')
            Base64(str,save,sizeof(save),mode);
        else
            Anti_Base64(str,save,sizeof(str),mode);
        printf("Result:%s\n\n",save);
        system("pause");
        system("cls");
    }
}

