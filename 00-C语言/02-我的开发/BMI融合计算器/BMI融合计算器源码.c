#include <stdio.h>
#include <math.h>
#include<stdlib.h>
void main()
{
	system("title Classic BMI caculater ByIce2Feathers");
	system("color f0");
	float a, b, c, d, k, l, s, n;
	int g;
	printf("\tClassic BMI caculater\n\n\tDeveloper by: Ice2Feathers\n----------------------------------\n");
start:
	printf("plese input your height(m) and weight(kg): as x,y\n");
	fflush(stdin);
	scanf("%f,%f", &a, &b);
	c = b / (a*a);
	d = (1.3*b) / (pow((double)a, 2.5));
	k = (a * 100 - 100)*0.9;
	l = a * 100 - 105;
	printf("please select your gender: \n\t1.man\n\t2.woman\n");
	fflush(stdin);
	scanf("%d", &g);
	n = (a * 100 - 150)*0.6 + 50;
	s = (a * 100 - 150)*0.6 + 48;
	printf("your BMI is: \n\t%.2f\nnew BMI is \n\t%.2f\n", c, d);
	if (g == 1)
	{
		if (c<20)
		{
			printf("you are so light weight.\nmabe you can eat better!\n\n");
		}
		else
		if (c >= 20 && c<25)
		{
			printf("you are normal.\nyou are health,keep it up!\n\n");
		}
		else
		if (c >= 25 && c<30)
		{
			printf("you are overweight.\nyou can eat some fruits and vegetables!\n\n");
		}
		else
		if (c >= 30 && c<35)
		{
			printf("you are fat.\nmabe you can consider about amaigrissement!\n\n");
		}
		else
		if (c >= 35 && c<40)	{
			printf("you are very fat.\nyou should amaigrissement.\n\n");
		}
		else
		if (c >= 40)	{
			printf("you are very very fat.\nyou must amaigrissement now.\n\n");
		}
		printf("your standard medicine weight is: %.2fkg\n\n", k);
		printf("best BMI is 22!\n\n");


	}
	else
	if (g == 2)
	{
		if (c<19)
		{
			printf("you are so light weight.\nmabe you can eat better!\n\n");
		}
		else
		if (c >= 19 && c<24)
		{
			printf("you are normal.\nyou are health,keep it up!\n\n");
		}
		else
		if (c >= 24 && c<29)
		{
			printf("you are overweight.\nyou can eat some fruits and vegetables!\n\n");
		}
		else
		if (c >= 29 && c<34)
		{
			printf("you are fat.\nmabe you can consider about amaigrissement!\n\n");
		}
		else
		if (c >= 34 && c<39)	{
			printf("you are very fat.\nyou should amaigrissement.\n\n");
		}
		else
		if (c >= 39)	{
			printf("you are very very fat.\nyou must amaigrissement now.\n\n");
		}
		printf("your standard medicine weight is: %.2fkg\n\n", l);
		printf("best BMI is 21!\n");



	}
	printf("north standard military weight is: %.2fkg\nsouth standard military weight is: %.2fkg\n", n, s);
	printf("----------------------------------\n\nthis result only be used reference!\n");
	goto start;
}
