
#include "Enemy.h"
#include "Resources.h"
#include "Bullet.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"
#include "Config.h"

using namespace CocosDenshion;

extern CCArray* enemy_items;
extern CCArray* enemy_bullet;

Enemy::Enemy():m_active(true),m_speed(200),m_bulletspeed(-200),m_hp(15),m_bulletpowervalue(1),
	m_movetype(0),m_scorevalue(200),m_zorder(200),m_delaytime(1+1.2*CCRANDOM_0_1()),m_attackmode(1)
{

}

Enemy::~Enemy()
{
} 

bool Enemy::enemyInit(EnemyType type)
{
	if (!CCSprite::init())
	{
		return false;
	}

	m_hp = type.hp;
	m_movetype = type.movetype;
	m_scorevalue = type.scorevalue;
	
	this->initWithSpriteFrameName(type.texturename.c_str());
	this->schedule(schedule_selector(Enemy::shoot),m_delaytime);

	return true;
}

Enemy* Enemy::create(EnemyType type)
{
	Enemy* enemy = new Enemy();
	if (enemy && enemy->enemyInit(type))
	{
		enemy->autorelease();
		return enemy;
	}else
	{
		delete enemy;
		enemy = NULL;
		return NULL;
	}
}

void Enemy::update(float dt)
{
	if ( m_hp<0 )
	{
		m_active = false;
	}
}

bool Enemy::isactive()
{
	return m_active;
}

void Enemy::hurt()
{
	m_hp--;
}

CCRect Enemy::colliderect()
{
	CCSize size = this->getContentSize();
	CCPoint pos = this->getPosition();
	return CCRectMake(pos.x-size.height/2, pos.y-size.height/4,size.width,size.height);
}

int Enemy::getmovetype()
{
	return m_movetype;
}

void Enemy::sharedEnemy()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(renemyplist,renemy);
}

void Enemy::destroy()
{
	Config::sharedConfig()->setScoreValue(m_scorevalue);
	Effect* effect = Effect::create();
	effect->explode(this->getParent(), this->getPosition());
	effect->spark(this->getPosition(),this->getParent(),1.2,0.7);
	enemy_items->removeObject(this);
	this->removeFromParent();
	if (Config::sharedConfig()->getAudioStatus())
	{
		SimpleAudioEngine::sharedEngine()->playEffect(rexplodeeffect);
	}
}

void Enemy::shoot(float dt)
{
	CCPoint pos = this->getPosition();
	Bullet* bullet = new Bullet(m_bulletspeed, "W2.png", m_attackmode);
	bullet->autorelease();
	enemy_bullet->addObject(bullet);
	this->getParent()->addChild(bullet,m_zorder,900);
	bullet->setPosition(ccp(pos.x, pos.y-this->getContentSize().height*0.2));
}