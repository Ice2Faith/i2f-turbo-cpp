#ifndef _Snack_h_
#define _Snack_h_
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define X 20
#define Y 20
#define MAXLENTH 1024
/*
地图边界	1
空白地图	0
蛇身体		2
奖励点		9
*/

typedef struct
{
    int x;
    int y;
} space;
typedef struct
{
    int x[MAXLENTH];
    int y[MAXLENTH];
    int len;
} Snack;
space * gift;
int GiftVanul=1;
int CountBigGift=0;
int BigGiftTimes=5;
int LastGet=0;
space * head;
Snack * SnackBody;
char control;
int existgift;
int core;
void SnackEattingGmme();
void DefultMap();
void DrewMap();
void CreatGift();
void DisplayMap();
void MoveSnack();
int SnackCheak();
void ReadyAll();


#endif
