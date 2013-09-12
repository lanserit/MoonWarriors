
#ifndef SHIP_H
#define SHIP_H

#include "cocos2d.h"
#include "UnitSprite.h"

using namespace cocos2d;

class Ship : public UnitSprite  
{
private:
	int m_speed;
	int m_bulletspeed;
	int m_HP;
	int m_bullettypevalue;
	int m_bulletpowervalue;
	bool m_isthrowbooming;
	bool m_isthrowboom;
	bool m_canbeattack;
	int m_zorder;
	int m_maxpowervalue;
	CCPoint m_appearpos;
	int m_hurtcolorlife;
	bool m_active;
	
public:
	Ship();
	~Ship();
	void makeattack(CCNode* psender);
	virtual bool init();
	virtual void update(float dt);
	void shoot(float dt);
	virtual void hurt();
	virtual void destroy();
	virtual bool isactive();
	virtual CCRect colliderect();
	int getzorder();
	
	CREATE_FUNC(Ship);
};


#endif