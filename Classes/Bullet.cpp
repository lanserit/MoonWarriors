
#include "Bullet.h"
#include "Resources.h"

extern CCArray* play_bullet;
extern CCArray* enemy_bullet;

Bullet::Bullet() : m_active(true), m_vx(0), m_vy(200), m_power(1), m_hp(1), m_zorder(3000)
{

}

Bullet::Bullet(int speed, const char* weapon, int attackmode)
{
	m_vx = 0;
	m_vy = -speed;
	m_active = true;
	m_power = 1;
	m_hp = 1;
	m_zorder = 3000;
	m_attackmode = attackmode;
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(rbulletplist);
	this->initWithSpriteFrameName(weapon);
	ccBlendFunc bl = {GL_SRC_ALPHA, GL_ONE};
	this->setBlendFunc(bl);	 
}

Bullet::~Bullet()
{

}

void Bullet::update(float dt)
{
	CCPoint pos = this->getPosition();
	pos.x -= m_vx*dt;
	pos.y -= m_vy*dt;
	this->setPosition(pos);
	if (m_hp<=0)
	{
		m_active = false;
	}
}

bool Bullet::init()
{
	return true;
}

void Bullet::hurt()
{
	m_hp--;
}

void Bullet::destroy()
{
	CCSprite* explode = CCSprite::create(rhit);
	ccBlendFunc cb = {GL_SRC_ALPHA, GL_ONE};
	explode->setBlendFunc(cb);
	explode->setPosition(this->getPosition());
	explode->setRotation(CCRANDOM_0_1()*360);
	explode->setScale(0.75);
	this->getParent()->addChild(explode,9999);
	play_bullet->removeObject(this);
	enemy_bullet->removeObject(this);
	this->removeFromParent();

	CCCallFuncN* removeExplode = CCCallFuncN::create(explode,callfuncN_selector(Bullet::removeexplode));
	explode->runAction(CCScaleBy::create(0.3,2,2));
	explode->runAction(CCSequence::create(CCFadeOut::create(0.3),removeExplode,NULL));
}

CCRect Bullet::colliderect()
{
	CCPoint pos = this->getPosition();
	return CCRectMake(pos.x-3,pos.y-3,6,6);
}

bool Bullet::isactive()
{
	return m_active;
}

void Bullet::removeexplode(CCNode* psender)
{
	psender->removeFromParent();
}