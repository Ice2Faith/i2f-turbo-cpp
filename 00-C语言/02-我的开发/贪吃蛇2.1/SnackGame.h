#ifndef _SnackGame_h_
#define _SnackGame_h_
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define X 20
#define Y 20
#define MAXLENTH 1024
    /*
    ��ͼ�߽�	1
    �հ׵�ͼ	0
    ������		2
    ������		9
    */
using namespace::std;

class SnackGame
{
public:
    SnackGame();
    ~SnackGame(){};
    int MainActive();
    void SnackEattingGmme();
    void DefultMap();
    void DrewMap();
    void CreatGift();
    void DisplayMap();
    void MoveSnack();
    int SnackCheak();
    void ReadyAll();
    void Screentips(int type,char * before);
private:
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
    int GiftVanul;
    int CountBigGift;
    int BigGiftTimes;
    int LastGet;
    space * head;
    Snack * SnackBody;
    char control;
    int existgift;
    int core;
    int Map[X+2][Y+2];
    char contitle[100];
    char concolor[5];
    int conlines;
    int concols;
};
#include"SnackGame.cpp"
#endif // _SnackGame_h_
