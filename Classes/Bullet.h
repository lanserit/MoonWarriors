

#ifndef BULLET_H
#define BULLET_H

#include "cocos2d.h"
#include "UnitSprite.h"

using namespace cocos2d;

class Bullet : public UnitSprite
{
private:
	float m_vx;
	float m_vy;
	float m_power;
	int m_hp;
	int m_attackmode;
	int m_parenttype;

public:
	bool m_active;
	int m_zorder;
	Bullet();
	Bullet(int speed, const char* weapon, int attackmode);
	~Bullet();
	virtual bool init();
	virtual void update(float dt);
	virtual void hurt();
	virtual void destroy();
	virtual CCRect colliderect();
	virtual bool isactive();
	void removeexplode(CCNode* psender);

	CREATE_FUNC(Bullet);
};
  
#endif