#include "stdafx.h"
#include "AutoRouterCore.h"

AutoRouterCore::AutoRouterCore(int width, int height)
{
	srand((unsigned int)time(NULL));
	m_map = NULL;
	m_root = NULL;
	m_width = width;
	m_heigth = height;
	is4Direct = true;
	isStepAround = true;
	InitMap();
	InitRouter();
}

AutoRouterCore::~AutoRouterCore()
{
	if (m_map != NULL)
	{
		delete[] m_map;
		m_map = NULL;
	}
}
void AutoRouterCore::clean()
{
	for (int i = 0; i < m_heigth; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			At(i,j)=ELEM_VECANT;
		}
	}
	InitRouter();
}
void AutoRouterCore::InitMap()
{
	if (m_map != NULL)
	{
		delete[] m_map;
		m_map = NULL;
	}
	m_map = new char[(m_width)*(m_heigth)];
	clean();
	m_start = {0,0};
	m_end = {m_width-1,m_heigth-1};
}
AutoRouterCore& AutoRouterCore::setSize(int width, int height)
{
	m_width = width;
	m_heigth = height;
	InitMap();
	return *this;
}
void AutoRouterCore::setRandomWall()
{
	int rate = rand() % 25+15;
	for (int i = 0; i < m_heigth; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			At(i, j) = ELEM_VECANT;
			if (rand()%100<rate)
				At(i, j) = ELEM_WALL;
		}
	}
	m_start = {rand()%m_width,rand()%m_heigth};
	m_end = {rand()%m_width,rand()%m_heigth};
	At(m_start.x, m_start.y) = ELEM_VECANT;
	At(m_end.x,m_end.y)=ELEM_VECANT;
}
char& AutoRouterCore::At(int row, int col)
{
	return m_map[(row)*(m_width)+(col)];
}

int AutoRouterCore::getWidth()
{
	return m_width;
}
int AutoRouterCore::getHeight()
{
	return m_heigth;
}

void AutoRouterCore::setStartPoint(int row, int col)
{
	this->At(row, col) = ELEM_VECANT;
	m_start.x = row;
	m_start.y = col;
}
void AutoRouterCore::setEndPoint(int row, int col)
{
	this->At(row, col) = ELEM_VECANT;
	m_end.x = row;
	m_end.y = col;
}
int AutoRouterCore::getStartX()
{
	return m_start.x;
}
int AutoRouterCore::getStartY()
{
	return m_start.y;
}
int AutoRouterCore::getEndX()
{
	return m_end.x;
}
int AutoRouterCore::getEndY()
{
	return m_end.y;
}
void AutoRouterCore::InitRouter()
{
	m_tial = NULL;
	if (m_root != NULL)
	{
		CleanRouter();
		m_root = NULL;
	}
	m_root = CreateNode();
	m_tial = m_root;
	isFindRoute = false;

}
void AutoRouterCore::CleanRouter()
{
	TNode * p = m_root;
	while (p)
	{
		TNode * dp = p;
		p = p->next;
		if (At(dp->p.x, dp->p.y)==ELEM_TEMP)
			At(dp->p.x, dp->p.y) = ELEM_VECANT;
		delete dp;
	}
	m_root = NULL;
}
AutoRouterCore::TNode * AutoRouterCore::CreateNode()
{
	TNode * node = new TNode;
	node->next = NULL;
	node->parent = NULL;
	node->p = { 0, 0 };
	return node;
}
void AutoRouterCore::pushNode(TPoint p, TNode * parent)
{
	TNode * node = CreateNode();
	node->p = p;
	node->parent = parent;

	m_tial->next = node;
	m_tial = node;
}
void AutoRouterCore::routeFirst()
{
	InitRouter();
	pushNode(m_start, NULL);
	m_curRoute = m_root->next;
	isFindRoute = false;
}
void AutoRouterCore::setRouteMode4Direct(bool is4d)
{
	is4Direct = is4d;
}
void AutoRouterCore::setRouteStepModeIsRoundCircle(bool isRound)
{
	isStepAround = isRound;
}
bool AutoRouterCore::routeStep()
{
	if (m_curRoute == NULL)
		return false;
	static int steps[][2] = {
		{-1,0},
		{0,-1},
		{0,1},
		{1,0},
		{-1,-1},
		{1,-1},
		{-1,1},
		{1,1}
	};
	int DirectCount = 4;

	TNode * roundOnceLast = m_tial;
	do
	{

		if (is4Direct)
			DirectCount = 4;
		else
			DirectCount = 8;
		for (int i = 0; i < DirectCount; i++)
		{
			TPoint pt = { m_curRoute->p.x + steps[i][0], m_curRoute->p.y + steps[i][1] };
			if (pt.x < 0 || pt.y < 0 || pt.x >= m_width || pt.y >= m_heigth)
				continue;
			short elem = At(pt.x, pt.y);
			if (elem == ELEM_VECANT)
			{
				At(pt.x, pt.y) = ELEM_TEMP;
				pushNode(pt, m_curRoute);
				if (pt.x == m_end.x && pt.y == m_end.y){
					isFindRoute = true;
					return false;
				}
			}
		}

		//保证一步拓展一圈，这样能够减少显示端的连续刷新压力
		if (isStepAround && m_curRoute == roundOnceLast)
		{
			if (m_curRoute->next == NULL)
				return false;
			break;
		}
			

		m_curRoute = m_curRoute->next;
		if (m_curRoute == NULL)
			return false;
		
	} while (isStepAround);
	return true;
}
AutoRouterCore::TNode * AutoRouterCore::getRouteList()
{
	return m_root->next;
}
AutoRouterCore::TNode * AutoRouterCore::getCurrentRestList()
{
	return m_curRoute;
}
bool AutoRouterCore::isRouteSuccess()
{
	return isFindRoute;
}
AutoRouterCore::TNode * AutoRouterCore::getSuccessRouteNode()
{
	return m_tial;
}