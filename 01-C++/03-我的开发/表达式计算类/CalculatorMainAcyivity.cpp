#include "CalculatorClass.h"
int main()
{
    //end test also some trouble
    char ch;
    char InString[1024];
    char help[2024];
    do
    {
        Calculator Calcu;
        //Calcu.HelpText(help);
        //cout << help;
        cout << "Please input String" << endl;
        cout << ">/ ";
        cin >> InString;
        double result;
        bool legal=Calcu.CalculateMain(InString,&result);
        if(!legal)
        {
            cout << "illegal string" << endl;
        }
        else
            cout << "==>" << result << endl;
        cout << "press any key continue" << endl;
        ch=getch();
        system("cls");
    }
    while(ch!='*');

    return 0;
}
