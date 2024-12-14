#pragma once
#include<vector>
#include<iterator>
#include<time.h>
#include<stdlib.h>
#include<math.h>
class ModelEntity{
public:
	ModelEntity();
	ModelEntity(double x,double y,double direction,double step,bool isDead,double radius,double blood);
	ModelEntity & setDirection(double direction);
	ModelEntity & parseAngleDirection(double angle);
	ModelEntity & setPosX(double posx);
	ModelEntity & setPosY(double posy);
	ModelEntity & setStep(double step);
	ModelEntity & setDeadState(bool isdead);
	ModelEntity & setRadius(double radius);
	ModelEntity & setBlood(double blood);
	static double parseDirection(double dy, double dx);
	double getDirection();
	double getPosX();
	double getPosY();
	double getStep();
	bool getDeadState();
	double getRadius();
	double getBlood();
	void move();
protected:
	void InitEntity();
private:
	bool m_isdead;
	double m_x;
	double m_y;
	double m_direction;
	double m_step;
	double m_radius;
	double m_blood;
};
class EvadeEndless
{
public:
	EvadeEndless(int width=720,int height=480);
	virtual ~EvadeEndless();
	void beginGame();
	void continueGame();
	void flushGame();
	void movePlayer(double direction);
	int getEnemyCount();
	void setSize(int width,int height);
	ModelEntity getEnemy(int index);
	ModelEntity getPlayer();
	int getBulletCount();
	ModelEntity getBullet(int index);
	void shootBullet();
	double getScore();
protected:
	void InitEnv();
	void DeleteEnv();
	void createEnemy();
	void createBullet();
private:
	std::vector<ModelEntity> m_enemy;
	std::vector<ModelEntity> m_bullet;
	ModelEntity * m_player;
	int m_maxWidth;
	int m_maxHeight;
	bool m_isGameOver;
	double m_score;
};

