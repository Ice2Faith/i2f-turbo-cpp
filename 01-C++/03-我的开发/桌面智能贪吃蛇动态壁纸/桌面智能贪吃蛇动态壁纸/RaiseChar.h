#pragma once
#include<windows.h>

#include<math.h>
#include<stdlib.h>
#include<time.h>
class RaiseChar
{
public:
	typedef struct
	{
		int x;
		int y;
		int speed;
		short r;
		short g;
		short b;
		bool live;
		TCHAR ch[100];
	}CharNode;
	RaiseChar();
	RaiseChar(int width, int height, int count);
	~RaiseChar();
	void InitCharNode();
	void DrawBackground(HDC hdc);
	void SetMaxCount(int count);
	void SetWindowSize(int width, int height);
private:
	void SetDefaultArgument();
	void ResetNodeArgs(int pos);
	void CreateCharNode();

	int mMaxCount; 
	CharNode * mCharNode;

	int mWinWidth;
	int mWinHeight;
};

