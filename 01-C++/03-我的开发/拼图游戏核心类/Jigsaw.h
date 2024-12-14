#ifndef _JIGSAW_H_
#define _JIGSAW_H_
#include<stdlib.h>
#include<time.h>
typedef int MoveDirect;
#define MOV_NULL 0
#define MOV_UP 8
#define MOV_DOWN 5
#define MOV_LEFT 4
#define MOV_RIGHT 6
class Jigsaw
{
public:
	Jigsaw(int line=5, int col=5);
	~Jigsaw();
	bool Run(MoveDirect direc);
	int GetCols();
	int GetLines();
	int MapAt(int rindex, int cindex);
	void clear();
	int GetMaxBlock();
	int GetStep();

	bool AutoRun();
	int GetWalkLen();
	int* GetWalkRoute();
private:
	bool MovePic(MoveDirect direc);
	bool IsWin();
	void SetState();
	int step;
	int Lines;
	int Cols;
	int maxblock;
	int maxx, maxy;
	int* Map;

	int direc[4];
	int antidirec[4];

	int *queueinit;
	int queuelen;
	int autoindex;
};


#endif // !_JIGSAW_H_
