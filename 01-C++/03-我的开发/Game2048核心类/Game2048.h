#ifndef _GAME2048_H_
#define _GAME2048_H_
/*For example:
Game2048 mygame(10,10);
int main(int argc, char * argv[])
{
	while (1)
	{
		DisplayMap();
		int mov = GetMove();
		cout << mov << endl;
		if (!mygame.Run(mov))
			break;
}
system("pause");
return 0;
}
*/
#include<stdlib.h>
#include<time.h>
typedef int MoveDirect;
#define MOV_NULL 0
#define MOV_UP 8
#define MOV_DOWN 5
#define MOV_LEFT 4
#define MOV_RIGHT 6
class Game2048
{
public:
    Game2048(int line=5,int col=5);
    ~Game2048();
	bool Run(MoveDirect mov);
	int GetCols();
	int GetLines();
	int MapAt(int rindex, int cindex);//return >=0 is true,-1 is bad index,0 mean space,other mean number.
	int GetStep();
	int GetScore();
	int GetUsedTime();
	int GetMaxNum();
	void clear();
private:
	void CreateNew();
	void MoveAndResult(MoveDirect mov);
	bool IsDead();
    //运行图和运行时环境
	int * Map;
	int lines;
	int cols;
    int step;
    int core;
    long runtime;
    int usetime;
    int maxnum;

};

#endif // _GAME2048_H_
