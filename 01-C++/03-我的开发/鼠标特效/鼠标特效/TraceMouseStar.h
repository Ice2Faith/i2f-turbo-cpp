#pragma once
#include<windows.h>

#include<math.h>
#include<stdlib.h>
#include<time.h>
class TraceMouseStar
{
public:
	typedef struct
	{
		int x;
		int y;
		int size;
		int maxTimes;
		int curTime;
		int speed;
		double direct;
		short r;
		short g;
		short b;
		bool live;
	}StarNode;
	TraceMouseStar();
	TraceMouseStar(int width, int height, int count);
	~TraceMouseStar();
	void InitNode();
	void DrawBackground(HDC hdc);
	void SetMaxCount(int count);
	void SetWindowSize(int width, int height);
private:
	void SetDefaultArgument();
	void ResetNodeArgs(int pos);
	void CreateNode();

	inline double AngleToRadian(double angle);
	inline short getR(COLORREF color);
	inline short getG(COLORREF color);
	inline short getB(COLORREF color);
	int mMaxCount;
	StarNode * mNode;

	int mWinWidth;
	int mWinHeight;
};

