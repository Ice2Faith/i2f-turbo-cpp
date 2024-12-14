#pragma once
#include<time.h>
#include<stdlib.h>
//getElement返回值
#define DTIGE_TOUCH_BLOCK 1		//可以点击方块码
#define DTIGE_DANGER_BLOCK 0	//不可点击的方块码
#define DTIGE_ERROR_INDEX -1	//获取元素下标越界码
class DontTouchIt
{
public:
	DontTouchIt(int col = 4, int row = 4);//生成这样大小规格的游戏图
	virtual ~DontTouchIt();
private:
	int m_colCount;
	int m_rowCount;
	int m_lineCount;
	int m_scoreCount;
	int m_deadCount;
	bool m_isGameOver;
	short **m_map;
	void createMap();
	void clearMap();
	void fillMap();
	void fillLine(int line);
public:
	int getColCount();//获取列数
	int getRowCount();//获取行数
	short getElement(int row, int col);//获取此行列的元素
	void beginGame();//开始新的一局
	void flushMap();//刷新数据，下移一行
	bool touchIt(int row, int col);//点击此行此列，返回false游戏结束
	bool isGameOvered();//检查游戏是否结束
	int getScore();//获取本局游戏的点击次数
	void continueGame();//如果游戏结束了，可以继续游戏
	void setLineMaxTouchCount(int maxCount);//设置一行最多的点击块数
	void setSize(int col, int row);//设置游戏大小
	int getDeadCount();//获取死亡次数
};

