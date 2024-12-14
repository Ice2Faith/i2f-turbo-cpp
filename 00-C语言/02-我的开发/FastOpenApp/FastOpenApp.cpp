#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#define MAXNAME 1024
#define INFOFILENAME "BootInfo.txt"
using namespace std;
int FastOpenApp(int argv,char * argc[]);
int ReadBootInfoFile();
void help();
int main(int argv,char * argc[])
{
    system("color f5");
    system("title FastBootApp Dev Ice2Faith");
    if(argv>1)
    {
        FastOpenApp(argv,&argc[0]);



    }
    else if(!ReadBootInfoFile())
    {
        help();
        cout << "Press any Key continue." << endl;
        getch();
    }
}

int FastOpenApp(int argv,char * argc[])
{
    if(argv<=1)
        return 0;
    char Mind[MAXNAME];
    for(int i=1; i<argv; i++)
    {
        sprintf(Mind,"start \"\" \"%s\"\0",argc[i]);
        system(Mind);
    }
    return 1;
}

int ReadBootInfoFile()
{
    ifstream SF;
    SF.open(INFOFILENAME,fstream::in);
    if(!SF)
        return 0;
    char Name[MAXNAME];
    char Mind[MAXNAME];
    while(!SF.eof())
    {
        SF.getline(Name,MAXNAME);
        if(Name[0]=='\0'||Name[0]=='#'||Name[0]==' ')
            continue;
        if(Name[0]!='\"')
            sprintf(Mind,"start \"\" \"%s\"\0",Name);
        else
            sprintf(Mind,"start \"\" %s\0",Name);
        system(Mind);
    }
    SF.close();
    return 1;
}
void help()
{
    ofstream SF(INFOFILENAME);
    SF.close();
    cout << "Not Found Any boot Info come here." << endl;
    cout << "Not Found Info File \"BootInfo.txt\"" << endl;
    cout << "Created \"BootInfo.txt\"." << endl << endl;
    cout << "Tips" << endl;
    cout << "Please Pull App On Icon To Boot." << endl;
    cout << "Or,Using File that be named \"BootInfo.txt\" To boot them." <<endl;
    cout << "In that file you only fill up the route of a app." << endl;
    cout << "You can on a line first one add \"#\" to eliminate it." << endl;
    cout << "Every line cannot first one is vacant." << endl << endl;
    cout << "Legal line:" << endl;
    cout << "C:\\abc\\a.txt" <<endl;
    cout << "\"C:\\a b\\a.exe\"" << endl;
    cout << "ab\\c.mp3" << endl << endl;
    cout << "Useless line:" << endl;
    cout << "#C:\\bb\\c.c" << endl;
    cout << " \"D:\\pc.log\"" << endl;
    cout << "Also vacant line is useless." << endl << endl;
}
