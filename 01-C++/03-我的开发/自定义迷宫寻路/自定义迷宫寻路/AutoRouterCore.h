#pragma once
#define ELEM_VECANT 0
#define ELEM_WALL 1
#define ELEM_TEMP 2
#include<stdlib.h>
#include<time.h>

class AutoRouterCore
{
public:
	typedef struct __point
	{
		int x;
		int y;
	}TPoint;
	typedef struct __node
	{
		TPoint p;
		struct __node * next;
		struct __node * parent;
	}TNode;
	AutoRouterCore(int width=50,int height=50);
	~AutoRouterCore();
	AutoRouterCore& setSize(int width, int height);
	char& At(int row, int col);
	int getWidth();
	int getHeight();
	void clean();
	void setStartPoint(int row, int col);
	void setEndPoint(int row, int col);
	int getStartX();
	int getStartY();
	int getEndX();
	int getEndY();
	void routeFirst();
	bool routeStep();
	TNode * getRouteList();
	TNode * getCurrentRestList();
	bool isRouteSuccess();
	TNode * getSuccessRouteNode();
	void setRouteMode4Direct(bool is4d);
	void setRandomWall();
	void setRouteStepModeIsRoundCircle(bool isRound);
private:
	void InitMap();
	char * m_map;
	int m_width;
	int m_heigth;
	TPoint m_start;
	TPoint m_end;
	bool is4Direct;
	bool isStepAround;

	bool isFindRoute;
	TNode * m_curRoute;
	TNode * m_root;
	TNode * m_tial;
	void InitRouter();
	void CleanRouter();
	TNode * CreateNode();
	void pushNode(TPoint p, TNode * parent);
};

