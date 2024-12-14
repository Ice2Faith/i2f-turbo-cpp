#ifndef _SUDUKU_H_
#define _SUDUKU_H_
/** _SUDOKU_H_ :
*/
#include<stdlib.h>
#include<time.h>
class Sudoku
{
public:
	Sudoku();
	~Sudoku();
	int MapAt(int rindex, int cindex);
	bool MaskAt(int rindex, int cindex);
	bool SetMapAtValue(int rindex,int cindex,int number);
	int GetLine();
	int GetCol();
	int GetBlockLine();
	int GetBlockCol();
	void clear();
	int GetTipsCount();
	int GetSuccessCount();
	int GetSumCount();
	int GetEmptyCount();
private:
	void CreateTipsNum();
	void CleanMap();
	bool LineColsOnly(int rindex,int cindex);
	void CreateMask();
	int *Map;
	bool *Mask;
	int Lines;
	int Cols;
	int BlockLines;
	int BlockCols;
	int TipsCount;
};

#endif // _SUDOKU_H_