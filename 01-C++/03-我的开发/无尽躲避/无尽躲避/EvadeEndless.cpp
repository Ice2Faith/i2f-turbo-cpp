#include "stdafx.h"
#include "EvadeEndless.h"
void ModelEntity::InitEntity()
{
	m_x = 0;
	m_y = 0;
	m_direction = 3.1415926 * 1 / 2;
	m_step = 2;
	m_isdead = false;
	m_radius = 3;
	m_blood = 100;
}
ModelEntity::ModelEntity()
{
	InitEntity();
}
ModelEntity::ModelEntity(double x, double y, double direction, double step, bool isDead, double radius, double blood)
{
	InitEntity();
	m_x = x;
	m_y = y;
	m_direction = direction;
	m_step = step;
	m_isdead = isDead;
	m_radius = radius;
	m_blood = blood;
}
ModelEntity & ModelEntity::setDirection(double direction)
{
	m_direction = direction;
	return *this;
}
ModelEntity & ModelEntity::parseAngleDirection(double angle)
{
	m_direction = angle / 180.0*3.141592653569;
	return *this;
}
double ModelEntity::parseDirection(double dy, double dx)
{
	return atan2(dy, dx);
}
ModelEntity & ModelEntity::setPosX(double posx)
{
	m_x = posx;
	return *this;
}
ModelEntity & ModelEntity::setPosY(double posy)
{
	m_y = posy;
	return *this;
}
ModelEntity & ModelEntity::setStep(double step)
{
	m_step = step;
	return *this;
}
ModelEntity & ModelEntity::setDeadState(bool isdead)
{
	m_isdead = isdead;
	return *this;
}
ModelEntity & ModelEntity::setRadius(double radius)
{
	m_radius = radius;
	return *this;
}
ModelEntity & ModelEntity::setBlood(double blood)
{
	m_blood = blood;
	return *this;
}
double ModelEntity::getDirection()
{
	return m_direction;
}
double ModelEntity::getPosX()
{
	return m_x;
}
double ModelEntity::getPosY()
{
	return m_y;
}
double ModelEntity::getStep()
{
	return m_step;
}
bool ModelEntity::getDeadState()
{
	return m_isdead;
}
double ModelEntity::getRadius()
{
	return m_radius;
}
double ModelEntity::getBlood()
{
	return m_blood;
}
void ModelEntity::move()
{
	m_x = m_x + m_step*cos(m_direction);
	m_y = m_y + m_step*sin(m_direction);
}

void EvadeEndless::InitEnv()
{
	m_player = NULL;
	DeleteEnv();
	m_isGameOver = false;
	m_score = 0;
	m_player = new ModelEntity(m_maxWidth/2,m_maxHeight,0,6,false,8,100);
}
void EvadeEndless::DeleteEnv()
{
	if (m_player!=NULL)
	{
		delete m_player;
		m_player = NULL;
	}
	m_enemy.clear();
}
EvadeEndless::EvadeEndless(int width, int height)
: m_maxWidth(width)
, m_maxHeight(height)
{
	srand((unsigned int)time(NULL));
	InitEnv();
}
void EvadeEndless::setSize(int width, int height)
{
	m_maxHeight = height;
	m_maxWidth = width;
}

EvadeEndless::~EvadeEndless()
{
	DeleteEnv();
}


void EvadeEndless::beginGame()
{
	m_isGameOver = false;
	createEnemy();
}


void EvadeEndless::continueGame()
{
	m_isGameOver = false;
	m_enemy.clear();
}


void EvadeEndless::flushGame()
{
	if (m_isGameOver)
		return;
	if (rand() % 100 < 20)
	{
		createEnemy();
	}
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i].move();
		if (m_enemy[i].getPosX()+m_enemy[i].getRadius()<0 || m_enemy[i].getPosX()-m_enemy[i].getRadius()>m_maxWidth
			|| m_enemy[i].getPosY() + m_enemy[i].getRadius()<0 || m_enemy[i].getPosY() - m_enemy[i].getRadius()>m_maxHeight)
		{
			m_enemy[i].setDeadState(true);
		}
		if (sqrt(pow(m_enemy[i].getPosX() - m_player->getPosX(), 2) + pow(m_enemy[i].getPosY() - m_player->getPosY(), 2))<m_player->getRadius()+m_enemy[i].getRadius())
		{
			m_player->setBlood(m_player->getBlood() - m_enemy[i].getBlood());
			if (m_player->getBlood()<=0)
				m_isGameOver = true;
		}
	}
	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i].move();
		if (m_bullet[i].getPosX() + m_bullet[i].getRadius()<0 || m_bullet[i].getPosX() - m_bullet[i].getRadius()>m_maxWidth
			|| m_bullet[i].getPosY() + m_bullet[i].getRadius()<0 || m_bullet[i].getPosY() - m_bullet[i].getRadius()>m_maxHeight)
		{
			m_bullet[i].setDeadState(true);
		}
		for (int j = 0; j < m_enemy.size(); j++)
		{
			if (sqrt(pow(m_bullet[i].getPosX() - m_enemy[j].getPosX(), 2) + pow(m_bullet[i].getPosY() - m_enemy[j].getPosY(), 2))<m_enemy[j].getRadius() + m_bullet[i].getRadius())
			{
				m_enemy[j].setBlood(m_enemy[j].getBlood()-m_bullet[i].getBlood());
				m_bullet[i].setDeadState(true);
				m_score += m_bullet[i].getBlood();
				if (m_enemy[j].getBlood()<=0)
					m_enemy[j].setDeadState(true);
			}
		}
		
	}
	int index = 0;
	while (true)
	{
		if (m_enemy.size()==0 || index>=m_enemy.size())
		{
			break;
		}
		if (m_enemy[index].getDeadState())
		{
			std::vector<ModelEntity>::iterator ei = m_enemy.begin() + index;
			m_enemy.erase(ei);
		}
		else
		{
			index++;
		}
	}
	index = 0;
	while (true)
	{
		if (m_bullet.size() == 0 || index >= m_bullet.size())
		{
			break;
		}
		if (m_bullet[index].getDeadState())
		{
			std::vector<ModelEntity>::iterator ei = m_bullet.begin() + index;
			m_bullet.erase(ei);
		}
		else
		{
			index++;
		}
	}
}


void EvadeEndless::createEnemy()
{
	double rx = rand() % m_maxWidth;
	double rr = rand() % 15 + 5;
	if (rand() % 100 < 30)
	{
		ModelEntity me(rx, 0, ModelEntity::parseDirection(m_player->getPosY(), m_player->getPosX() - rx), rand() % 10 + 1, false,rr,rr/20.0*100 );
		m_enemy.push_back(me);
	}
	else
	{
		ModelEntity me(rx, 0, 3.1415926535 * 1 / 2, rand() % 10 + 1, false, rr, rr / 20.0 * 100);
		m_enemy.push_back(me);
	}
	
}


void EvadeEndless::movePlayer(double direction)
{
	if (m_isGameOver)
		return;
	m_player->setDirection(direction);
	m_player->move();
	if (m_player->getPosX() + m_player->getRadius()<0)
	{
		m_player->setPosX(m_player->getPosX() + m_player->getRadius());
	}
	if (m_player->getPosX() - m_player->getRadius()>m_maxWidth)
	{
		m_player->setPosX(m_player->getPosX() - m_player->getRadius());
	}
	if (m_player->getPosY() + m_player->getRadius()<0)
	{
		m_player->setPosY(m_player->getPosY() + m_player->getRadius());
	}
	if(m_player->getPosY() - m_player->getRadius()>m_maxHeight)
	{
		m_player->setPosY(m_player->getPosY() - m_player->getRadius());
	}
}


int EvadeEndless::getEnemyCount()
{
	return m_enemy.size();
}


ModelEntity EvadeEndless::getEnemy(int index)
{
	if (index >= 0 && index < m_enemy.size())
		return m_enemy[index];
	else
		return ModelEntity(0,0,0,0,true,0,0);
}


ModelEntity EvadeEndless::getPlayer()
{
	return *m_player;
}


void EvadeEndless::createBullet()
{
	ModelEntity me(m_player->getPosX(), m_player->getPosY(), 
		3.14159265354 * 3 / 2, rand() % 100<5 ? 8 : 6, false, rand() % 100<5 ? 10:6, rand()%100<5?rand()%20+10:10);
	m_bullet.push_back(me);
}


int EvadeEndless::getBulletCount()
{
	return m_bullet.size();
}


ModelEntity EvadeEndless::getBullet(int index)
{
	if (index >= 0 && index < m_bullet.size())
		return m_bullet[index];
	else
		return ModelEntity(0, 0, 0, 0, true, 0,0);
}


void EvadeEndless::shootBullet()
{
	createBullet();
}


double EvadeEndless::getScore()
{
	return m_score;
}
