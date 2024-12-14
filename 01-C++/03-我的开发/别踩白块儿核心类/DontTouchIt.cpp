#include "stdafx.h"
#include "DontTouchIt.h"


DontTouchIt::DontTouchIt(int col/* = 4*/, int row/* = 4*/)
: m_colCount(col)
, m_rowCount(row)
, m_lineCount(1)
, m_map(NULL)
, m_scoreCount(0)
, m_isGameOver(false)
{
	srand((unsigned int)time(NULL));
	setSize(col, row);
	fillMap();
}


DontTouchIt::~DontTouchIt()
{
	clearMap();
}


void DontTouchIt::createMap()
{
	if (m_map != NULL)
		clearMap();
	if (m_rowCount > 0 && m_colCount > 0)
	{
		m_map = (short **)malloc(sizeof(short*)*m_rowCount);
		for (int i = 0; i < m_rowCount; i++)
		{
			m_map[i] = (short *)malloc(sizeof(short)*m_colCount);
		}
	}
}


void DontTouchIt::fillMap()
{
	if (m_isGameOver)
		return;
	for (int i = 0; i < m_rowCount; i++)
	{
		for (int j = 0; j < m_colCount; j++)
		{
			m_map[i][j] = DTIGE_DANGER_BLOCK;
		}
		fillLine(i);
	}
}

void DontTouchIt::flushMap()
{
	if (m_isGameOver)
		return;
	short * lastLine = m_map[m_rowCount - 1];
	for (int i = m_rowCount - 1; i>0; i--)
	{
		m_map[i] = m_map[i - 1];
	}
	m_map[0] = lastLine;
	for (int i = 0; i < m_colCount; i++)
	{
		m_map[0][i] = DTIGE_DANGER_BLOCK;
	}
	fillLine(0);
	
}
void DontTouchIt::fillLine(int line)
{
	for (int i = 0; i < m_lineCount; i++)
	{
		m_map[line][rand() % m_colCount] = DTIGE_TOUCH_BLOCK;
	}
}

void DontTouchIt::clearMap()
{
	for (int i = 0; i < m_rowCount; i++)
	{
		free(m_map[i]);
	}
	free(m_map);
	m_map = NULL;
}



int DontTouchIt::getColCount()
{
	return m_colCount;
}


int DontTouchIt::getRowCount()
{
	return m_rowCount;
}


short DontTouchIt::getElement(int row, int col)
{
	if (row > m_rowCount - 1 || col > m_colCount - 1 || row < 0 || col < 0)
		return DTIGE_ERROR_INDEX;
	return m_map[row][col];
}


bool DontTouchIt::touchIt(int row, int col)
{
	if (row > m_rowCount - 1 || col > m_colCount - 1 || row < 0 || col < 0)
		return true;
	if (m_map[row][col] == DTIGE_TOUCH_BLOCK)
	{
		m_scoreCount++;
		flushMap();
		return true;
	}
	m_isGameOver = true;
	return false;
}


int DontTouchIt::getScore()
{
	return m_scoreCount;
}


void DontTouchIt::beginGame()
{
	m_scoreCount = 0;
	m_isGameOver = false;
	fillMap();
}


bool DontTouchIt::isGameOvered()
{
	return m_isGameOver;
}


void DontTouchIt::continueGame()
{
	m_isGameOver = false;
}


void DontTouchIt::setLineMaxTouchCount(int maxCount)
{
	if (maxCount > 0 && maxCount < m_colCount)
		m_lineCount = maxCount;
}


void DontTouchIt::setSize(int row, int col)
{
	if (row>0 && col > 0)
	{
		m_rowCount = row;
		m_colCount = col;
		createMap();
	}
}
