#ifndef _CALCULATORCLASS_H_
#define _CALCULATORCLASS_H_

#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#define MAXSIZE 1024
using namespace::std;
class Calculator
{
private:
    typedef struct
    {
        double num[MAXSIZE];
        int top;
    } Number;
    typedef struct
    {
        char dona[MAXSIZE];
        int top;
    } Donate;
    Number Num;
    Donate Dona;
    char * PreStr;
    char String[MAXSIZE];
    int Rules[20][20];
    char AllDona[20];
    const double Pi;
    int IsSingel;
    char SingelDona[20];

public:
    Calculator();
    ~Calculator() {};

    bool CalculateMain(char * InString,double * result);
    bool GetString(char * InString);
    void HelpText(char * Text);
    int IsNumber(char * String);
    int istrdouble(char * stream,int counter,double * save,char ** newstrspace);
    int istrchar(char * stream,char * save,char ** newstrspace);
    int CompareDonaTop(char predona);
    void CalculPop();
    double Calcu(double a,double b,char k);
    double CalcuSingel(double a,char k);
};
#include "CalculatorClass.cpp"
#endif // _CALCULATORCLASS_H_
