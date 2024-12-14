#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<cstring>
#include<cstdlib>
#include<conio.h>
using namespace std;
void GetAsciiHEXCode(char * Text,char * SaveCode);
void GetStringFromShort(unsigned short *number,char * SaveString);
void GetControlCharCode(const char ch,char * SaveCode);
int IsChineseType(char * Text);
void StringToHexNum();
void HexNumtoString();
void SetTextColor(int ForeColor,int BackGroundColor);
int main(int argv,char * argc[])
{
    system("title ASCIICodeViewer Designed by Ice2Faith");
    system("color f5");
    if(argv>1)
    {
        char SaveCode[4096*4]= {'\0'};
        char Text[4096*2]= {'\0'};
        for(int i=1; i<argv; i++)
        {
            strcpy(Text,argc[i]);
            GetAsciiHEXCode(Text,SaveCode);
            SetTextColor(2,15);
            cout << "接受字符串" << i << ": " << argc[i] << endl;
            cout << "转换结果: " << SaveCode << "\a" << endl;
            strcpy(SaveCode,"\0");
        }

        system("pause");
    }
    while(1)
    {
        SetTextColor(1,15);
        cout << "\t欢迎使用字符编码双向转换器";
        SetTextColor(12,15);
        cout << "(支持中文)" << endl << endl;
        SetTextColor(0,15);
        cout << "1.字符串转十六进制编码" << endl;
        cout << "2.十六进制编码转字符串" << endl;
        SetTextColor(2,15);
        cout << "3.清空屏幕" << endl;
        SetTextColor(12,15);
        cout << "0.退出系统" << endl;
        SetTextColor(9,15);
        cout << "请选择\n>/ ";
        SetTextColor(5,15);
        char sel='*';
        while(sel<'0'||sel>'3')
            sel=getch();
        cout << sel << endl;
        if(sel=='0')
            break;
        else if(sel=='3')
            system("cls");
        else if(sel=='1')
            StringToHexNum();
        else if(sel=='2')
            HexNumtoString();
        cout << endl << endl;
        SetTextColor(5,15);
    }
    return 0;
}

void StringToHexNum()
{
    char SaveCode[4096*4]= {'\0'};
    char Text[4096*2]= {'\0'};
    SetTextColor(9,15);
    cout << "请输入字符串（换行结束）" << endl;
    cin.getline(Text,4096*2-1);
    GetAsciiHEXCode(Text,SaveCode);
    SetTextColor(2,15);
    cout << "您的转换结果：" << SaveCode << "\a" << endl;
}
void HexNumtoString()
{
    SetTextColor(9,15);
    cout << "请输入十六进制编码串（0结束）" <<endl;
    unsigned short number[4096*2]= {0};
    unsigned short tnum=0x3e;
    int i=0;
    while(tnum!=0)
    {
        number[i++]=tnum;
        scanf("%x",&tnum);
    }
    number[i]=0;
    char SaveString[4096*4]= {'\0'};
    GetStringFromShort(number,SaveString);
    SetTextColor(2,15);
    cout << "您的转换结果：" << SaveString << "\a" << endl;
}
void GetStringFromShort(unsigned short *number,char * SaveString)
{
    char temp[20]= {'\0'};
    int i=1;
    while(*(number+i)!=0)
    {
        unsigned short a=*(number+i),h,l;
        h=a>>8;
        l=a&255;
        if(h!=0)
            sprintf(temp,"%c%c\0",h,l);
        else
            sprintf(temp,"%c\0",l);
        strcat(SaveString,temp);
        i++;
    }

}
void GetAsciiHEXCode(char * Text,char * SaveCode)
{
    char temp[20]= {"Hex(%0x): "};
    strcat(SaveCode,temp);
    int i=0;
    while(*(Text+i))
    {
        if(*(Text+i)>=0&&*(Text+i)<32)
        {
            GetControlCharCode(*(Text+i),temp);
        }
        else if(*(Text+i)>=32&&*(Text+i)<128)
        {
            sprintf(temp,"%0x\0",*(Text+i));
        }
        else if(IsChineseType(Text+i))
        {
            sprintf(temp,"%0x%0x\0",(*(Text+i))&255,(*(Text+i+1))&255);
            i++;
        }
        else
        {
            sprintf(temp,"%0x\0",*(Text+i));
        }
        strcat(SaveCode,temp);
        strcat(SaveCode," ");
        i++;
    }
    strcat(SaveCode,"0");
}
void GetControlCharCode(const char ch,char * SaveCode)
{
    char Ascii[35][5]= {"NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL","BS","HT","LF","VT","FF","CR","SO","SI","DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB","CAN","EM","SUB","ESC","FS","GS","RS","US","SP"};
    if(ch>=0&&ch<32)
        sprintf(SaveCode,"%s\0",Ascii[(int)ch]);
}
int IsChineseType(char * Text)
{
    int ret=0;
    if((((*Text)&255)>=0xb0&&((*Text)&255)<=0xf7)&&(((*(Text+1))&255)>=0xa1&&((*(Text+1))&255)<=0xfe))//基本常见汉字范围
    {
        ret=1;
    }
    else if((((*Text)&255)>=0xa1&&((*Text)&255)<=0xfe)&&(((*(Text+1))&255)>=0xa1&&((*(Text+1))&255)<=0xfe)) // 基本常用全角符号编码范围
    {
        ret=1;
    }
    else if((((*Text)&255)>=0x81&&((*Text)&255)<=0xfe)&&(((*(Text+1))&255)>=0x80&&((*(Text+1))&255)<=0xfe)) //繁体字和一些非常见汉字
    {
        ret=1;
    }
    return ret;
}
void SetTextColor(int ForeColor,int BackGroundColor)
{
    if(ForeColor<0 ||ForeColor>15)
        ForeColor=15;
    if(BackGroundColor<0 ||BackGroundColor>15)
        BackGroundColor=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ForeColor+BackGroundColor*0x10);
}
