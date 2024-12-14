#include"Base64.h"
#include<iostream>
#include<stdio.h>
using namespace std;
class Animal
{
public:
	int a;
	float b;
	double c;
	char d;
	char arr[3];
};
int main()
{
	Animal ani;
	ani.a = 12;
	ani.b = 12.125;
	ani.c = 21.587;
	ani.d = 'A';
	ani.arr[0] = 'R';
	ani.arr[1] = 'G';
	ani.arr[2] = 0;
	char str[100];
	Base64 bs;
	bs.DataToBase64((void*)&ani,sizeof(ani),str,100);
	cout << str << endl;
	Animal rani;
	bs.Base64ToData(str,strlen(str),(void *)&rani,sizeof(rani));
	cout << rani.a << " " << rani.b << " " << rani.c << " " << rani.d << " " << rani.arr << endl;
	printf("%0x %0x %0x\n", 'h', 'e', 'l');
	system("pause");
	return 0;
}