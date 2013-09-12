
#ifndef ENEMY_H
#define ENEMY_H

#include "cocos2d.h"
#include "UnitSprite.h"
#include "Config.h"

using namespace cocos2d;

class Enemy : public UnitSprite
{
private:
	bool m_active;
	int m_speed;
	int m_bulletspeed;
	int m_hp;
	int m_bulletpowervalue;
	int m_movetype;
	int m_scorevalue;
	int m_zorder;
	float m_delaytime;
	int m_attackmode;

public:
	Enemy();
	~Enemy();
	bool enemyInit(EnemyType type);
	virtual void update(float dt);
	void shoot(float dt);
	virtual void hurt();
	virtual void destroy();
	virtual CCRect colliderect();
	virtual bool isactive();

	static void sharedEnemy();
	static Enemy* create(EnemyType type);
	int getmovetype();

};
 
#endif