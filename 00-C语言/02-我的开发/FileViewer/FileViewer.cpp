#include<iostream>
#include<fstream>
#include<windows.h>
#include<cstring>
#include<cstdlib>
#include<conio.h>
#define FNAMELENGHT 2048
using namespace std;
char welcome();
void ViewTextFile(char Fname[]);
void ViewHexFile(char Fname[]);
void DisplayHex(char temp[],int i);
void Help();
void SetTextColor(int ForeColor,int BackGroundColor);
int IsChineseType(char * Text);
int main(int argv,char * argc[])
{
    system("title FileViewer Designed by Ice2Faith");
    system("color f5");
    char sel;
    char Fname[FNAMELENGHT];
    while(1)
    {
        sel=welcome();
        int aim=1;
        if(sel=='0')
            exit(0);
        if(sel=='3')
            Help();
        else
        {
            if(argv>2)
            {
                cout << "checked this file,please select:" << endl;
                for(int i=1; i<argv; i++)
                    cout << i << ": " << argc[i] <<endl;
                cout << ">/ ";
                cin >> aim;
                if(aim>argv)
                    aim=argv;
                if(aim<1)
                    aim=1;
                strcpy(Fname,argc[aim]);
            }
            else if(argv==1)
            {
                cout << "Please input a name of file:" << endl << ">/ ";
                cin >> Fname;
            }
            else if(argv==2)
            {
                strcpy(Fname,argc[1]);
            }
            switch(sel)
            {
            case '1':
                ViewTextFile(Fname);
                break;
            case '2':
                ViewHexFile(Fname);
                break;
            }
        }
        cin.clear();
        cin.sync();
        cout << endl << "Press any key continue" << endl;
        getch();
    }
    return 0;
}

char welcome()
{
    system("cls");
    cout << "------------------------------------------" << endl;
    system("color f5");
    cout << "\n\tFile Reader" << endl << endl;
    cout << "1.Open File by text mode" << endl << endl;
    cout << "2.Open File by HEX mode" << endl << endl;
    cout << "3.Help" << endl << endl;
    cout << "0.Exit" << endl << endl;
    cout << "------------------------------------------" << endl;
    char sel=getch();
    while(sel<'0'||sel>'3')
        sel=getch();
    return sel;
}

void ViewTextFile(char Fname[])
{
    system("cls");
    system("mode con cols=92");
    cin.clear();
    cin.sync();
    ifstream SFile(Fname);
    if(!SFile)
    {
        cout << "System >> Error!! File not found,which is named: \"" << Fname << "\"." << endl;
        SFile.close();
        return;
    }
    cout << "System >> Open File Name: " << Fname << endl << endl;
    cout << "----------------------------------------START----------------------------------------------" << endl;
    SFile.unsetf(ios::skipws);
    char temp;
    int lines=0;
    int prepage=1;
    int jump=0;
    int page=1;
    int cn=0;
    char exit='0';
    cout << ">>>>>>>>>>>>>>>>>>>>>> PAGE " << page++ << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    while(!SFile.eof())
    {
        SFile >> temp;
        //cout << temp;
        if(cn)
        {
            cout << temp;
            cn=0;
        }
        else if(temp=='\n'||temp=='\t')
            cout << temp;
        else if(temp=='\r')
            continue;
        else
        {
            if((int)temp>=32 && (int)temp<=127)
                cout << temp;
            else if((int)temp<0)
            {
                cn=1;
                cout << temp;

            }
            else
                cout << ".";
        }


        if(temp=='\n')
        {
            lines++;
        }
        if(lines==30)
        {
            lines=0;
            cout << "-------------------------------------------------------------------------------------------" << endl;
            cout<< endl << "Press \"1\" jump to aim page, \"*\" end view, else continue >/ ";
            if(!jump)
            {
                exit=getch();
                if(exit=='*')
                    return;
                if(exit=='1')
                {
                    cout << "1 Aim page:";
                    cin >> prepage;
                    if(prepage<page)
                        prepage=page;
                    jump=1;
                }
                else
                    prepage++;
            }

            if(prepage==page && jump)
            {
                cin.get();
                jump=0;
            }

            cout<< endl;
            system("cls");
            cout << ">>>>>>>>>>>>>>>>>>>>>> PAGE " << page++ << endl;
            cout << "-------------------------------------------------------------------------------------------" << endl;
        }

    }
    SFile.close();
    cout << endl << endl << "System >> End of read File: " << Fname << endl;
    cout << "-----------------------------------------END-----------------------------------------------" << endl;
}
void ViewHexFile(char Fname[])
{
    system("cls");
    system("mode con cols=138");
    cin.clear();
    cin.sync();
    ifstream SFile;
    SFile.open(Fname,ios_base::binary);
    if(!SFile)
    {
        cout << "System >> Error!! File not found,which is named: \"" << Fname << "\"." << endl;
        SFile.close();
        return;
    }
    char temp[17];
    char tmp;
    int i;
    int lines=0;
    int page=1;
    int prepage=1;
    int jump=0;
    char exit='0';
    i=0;
    cout << "System >> Open File Name: " << Fname << endl << endl;
    cout << "-------------------------------------------------------------------START------------------------------------------------------------------" << endl;
    cout << "---------------------------------HEX----------------------------------------------------------ASCII---------------------------------------" << endl;
    cout << ">>>>>>>>>>>>>>>>>>>>>> PAGE " << page++ << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while(!SFile.eof())
    {
        SFile.read((char *)&tmp,sizeof tmp);
        temp[i++]=tmp;
        if(i>=16)
        {
            DisplayHex(temp,i);
            i=0;
            lines++;
            if(lines==32)
            {
                lines=0;
                cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                cout<< endl << "Press \"1\" jump to aim page, \"*\" end view, else continue >/ ";
                if(!jump)
                {
                    exit=getch();
                    if(exit=='*')
                        return;
                    if(exit=='1')
                    {
                        cout << "1 Aim page:";
                        cin >> prepage;
                        if(prepage<page)
                            prepage=page;
                        jump=1;
                    }
                    else
                        prepage++;
                }

                if(prepage==page && jump)
                {
                    cin.get();
                    jump=0;
                }
                cout<< endl;
                system("cls");
                cout << ">>>>>>>>>>>>>>>>>>>>>> PAGE " << page++ << endl;
                cout << "------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
        }
    }
    DisplayHex(temp,i);
    SFile.close();
    cout << endl << endl << "System >> End of read File: " << Fname << endl;
    cout << "-----------------------------------------END----------------------------------------------------------------------------------------------" << endl;
}
void DisplayHex(char temp[],int i)
{
    cout << "|";
    int counter=0;
    int cn=0;
    while(i<16)
    {
        temp[i++]='\0';
    }
    counter=0;
    for(i=0; i<16; i++)
    {
        cout << " ";
        int a=(char)temp[i]&255;
        if(a>=0&&a<16)
            cout << "0";
        cout << hex << a << " ";


        if(counter==7)
            cout << "| ";
        counter++;
    }
    cout << "   |   ";
    char Ascii[35][5]= {"NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL","BS","HT","LF","VT","FF","CR","SO","SI","DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB","CAN","EM","SUB","ESC","FS","GS","RS","US","SP"};
    for(i=0; i<16; i++)
    {

        if((int)temp[i]>32 && (int)temp[i]<128)
        {
            SetTextColor(2,7);
            cout << " " << temp[i] <<" ";
        }
        else if((int)temp[i]>=0 && (int)temp[i]<=32)
        {
            SetTextColor(0,7);
            if(strlen(Ascii[(int)temp[i]])==2)
                cout << " ";
            cout << Ascii[(int)temp[i]];
        }else if(IsChineseType(&temp[i]))
        {
            SetTextColor(4,7);
            cout << "  " << temp[i]<<temp[i+1] << "   ";
            i++;
        }
        else
        {
            SetTextColor(1,7);
            cout << "...";
        }
        SetTextColor(5,15);
        if(i!=15)
            cout << " ";
    }
    cout << "|";
    cout << endl;
}

void Help()
{
    cin.clear();
    cin.sync();
    system("cls");
    cout << "-------------------------------------------------------------" << endl << endl;
    cout << "Name:\tFile Viewer" << endl << endl;
    cout << "Version:\tV1.0.0" << endl << endl;
    cout << "Operate lead:" << endl << endl;
    cout << "You can input file name(*:\\*\\*.*) and route." << endl << endl;
    cout << "If in present contend you can only input the name(*.*)." << endl << endl;
    cout << "And you can pull file(s) on the icon boot to open." << endl << endl;
    cout << "You can use \"1\" to jump aim page." << endl << endl;
    cout << "You can use \"*\" end view present file." << endl << endl;
    cout << "Others will come into next page." << endl << endl;
    cout << "-------------------------------------------------------------" << endl << endl;
}
void SetTextColor(int ForeColor,int BackGroundColor)
{
    if(ForeColor<0 ||ForeColor>15)
        ForeColor=15;
    if(BackGroundColor<0 ||BackGroundColor>15)
        BackGroundColor=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ForeColor+BackGroundColor*0x10);
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
