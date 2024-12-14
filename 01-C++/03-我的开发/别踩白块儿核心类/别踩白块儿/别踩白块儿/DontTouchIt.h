#pragma once
#include<time.h>
#include<stdlib.h>
//getElement����ֵ
#define DTIGE_TOUCH_BLOCK 1		//���Ե��������
#define DTIGE_DANGER_BLOCK 0	//���ɵ���ķ�����
#define DTIGE_ERROR_INDEX -1	//��ȡԪ���±�Խ����
class DontTouchIt
{
public:
	DontTouchIt(int col = 4, int row = 4);//����������С������Ϸͼ
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
	int getColCount();//��ȡ����
	int getRowCount();//��ȡ����
	short getElement(int row, int col);//��ȡ�����е�Ԫ��
	void beginGame();//��ʼ�µ�һ��
	void flushMap();//ˢ�����ݣ�����һ��
	bool touchIt(int row, int col);//������д��У�����false��Ϸ����
	bool isGameOvered();//�����Ϸ�Ƿ����
	int getScore();//��ȡ������Ϸ�ĵ������
	void continueGame();//�����Ϸ�����ˣ����Լ�����Ϸ
	void setLineMaxTouchCount(int maxCount);//����һ�����ĵ������
	void setSize(int col, int row);//������Ϸ��С
	int getDeadCount();//��ȡ��������
};

