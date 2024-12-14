#ifndef _BASE64_H_
#define _BASE64_H_
#include<string.h>
#define BASE_MODE int
#define BASE_NORMAL_STR 0
#define BASE_URL 1
#define BASE_EXP 2
#define BASE_XML_NMTOKEN 3
#define BASE_XML_NAME 4
#define BASE_CHINA 5
/**
* int Base64(char * str,char * base64,int base64_size,int mode);
* str: is your string which to base64.
* base64: is your save base64 array.
* int Anti_Base64(char * base64,char * str,int str_size,int mode);
* base64: is your base64 which to string.
* str: is your save string array.
* *_size:
* use to check your save array size could save result,if not will return 0 and failure and cancel operation.
*/
int Base64(char * str,char * base64,int base64_size,BASE_MODE mode);
int Anti_Base64(char * base64,char * str,int str_size,BASE_MODE mode);

int Base64(char * str,char * base64,int base64_size,BASE_MODE mode)
{
    if(strlen(str)*4/3>=base64_size)
    {
        return 0;
    }
    char table[65]= {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\0"};
    char EndFill='=';
    if(mode==BASE_NORMAL_STR)
    {
        EndFill='=';
    }
    else if(mode==BASE_URL)
    {
        table[62]='-';
        table[63]='_';
        EndFill='=';
    }else if(mode==BASE_EXP)
    {
        table[62]='!';
        table[63]='-';
        EndFill='=';
    }
    else if(mode==BASE_XML_NMTOKEN)
    {
        table[62]='.';
        table[63]='-';
        EndFill='=';
    }
    else if(mode==BASE_XML_NAME)
    {
        table[62]='_';
        table[63]=':';
        EndFill='=';
    }
    else if(mode==BASE_CHINA)
    {
        table[62]='.';
        table[63]='_';
        EndFill='=';
    }

    unsigned char in[3]= {0};
    unsigned char out[4]= {0};
    int i=0,k=0;
    int end=0;
    int endspace=8;
    while(end==0)
    {
        for(int j=0; j<4; j++)
        {
            if(j<3)
                in[j]=0;
            out[j]=0;
        }
        for(int j=0; j<3; j++)
        {
            in[j]=str[i];
            i++;
            if(str[i]=='\0')
            {
                end=1;
                endspace=j+2;
                break;
            }
        }
        int temp=0;
        temp=(((int)in[0])<<(2*8))|(((int)in[1])<<(1*8))|((int)in[2]);
        out[0]=table[((temp&(63<<(6*3)))>>(6*3))];
        out[1]=table[((temp&(63<<(6*2)))>>(6*2))];
        out[2]=table[((temp&(63<<(6*1)))>>(6*1))];
        out[3]=table[(temp&63)];
        if(endspace<=0)
            out[0]=EndFill;
        if(endspace<=1)
            out[1]=EndFill;
        if(endspace<=2)
            out[2]=EndFill;
        if(endspace<=3)
            out[3]=EndFill;
        for(int j=0; j<4; j++)
        {
            base64[k]=out[j];
            k++;
        }

    }
    base64[k]='\0';
    return 1;
}
int Anti_Base64(char * base64,char * str,int str_size,BASE_MODE mode)
{
    if(strlen(base64)*3/4>=str_size)
    {
        return 0;
    }
    char table[65]= {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\0"};
    char EndFill='=';
    if(mode==BASE_NORMAL_STR)
    {
        EndFill='=';
    }
    else if(mode==BASE_URL)
    {
        table[62]='-';
        table[63]='_';
        EndFill='=';
    }else if(mode==BASE_EXP)
    {
        table[62]='!';
        table[63]='-';
        EndFill='=';
    }
    else if(mode==BASE_XML_NMTOKEN)
    {
        table[62]='.';
        table[63]='-';
        EndFill='=';
    }
    else if(mode==BASE_XML_NAME)
    {
        table[62]='_';
        table[63]=':';
        EndFill='=';
    }
    else if(mode==BASE_CHINA)
    {
        table[62]='.';
        table[63]='_';
        EndFill='=';
    }
    unsigned char in[4]= {0};
    int iin[4]= {0};
    unsigned char out[3]= {0};
    int i=0,k=0;
    int end=0;
    while(end==0)
    {
        for(int j=0; j<4; j++)
        {
            if(j<3)
                out[j]=0;
            in[j]=0;
            iin[j]=0;
        }
        for(int j=0; j<4; j++)
        {
            in[j]=base64[i];
            i++;
            if(base64[i]=='\0'||base64[i]==EndFill)
            {
                end=1;
                break;
            }
        }
        for(int j=0; table[j]!='\0'; j++)
        {
            if(in[0]==table[j])
                iin[0]=j;
            if(in[1]==table[j])
                iin[1]=j;
            if(in[2]==table[j])
                iin[2]=j;
            if(in[3]==table[j])
                iin[3]=j;
        }
        int temp=0;
        temp=((iin[0])<<(3*6))|((iin[1])<<(2*6))|((iin[2])<<(1*6))|(iin[3]);
        out[0]=((temp&(255<<(8*2)))>>(8*2));
        out[1]=((temp&(255<<(8*1)))>>(8*1));
        out[2]=(temp&255);
        for(int j=0; j<3; j++)
        {
            str[k]=out[j];
            k++;
        }

    }
    str[k]='\0';
    return 1;
}

#endif // _BASE64_H_
