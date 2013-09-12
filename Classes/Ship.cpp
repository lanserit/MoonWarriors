
#include "Ship.h"
#include "Resources.h"
#include "Bullet.h"  
#include "Config.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"

extern CCArray* play_bullet;

using namespace cocos2d;
using namespace CocosDenshion;


Ship::Ship():m_speed(200),m_bulletspeed(900),m_HP(5),m_bullettypevalue(1),m_bulletpowervalue(1),
	m_isthrowbooming(false),m_canbeattack(true),m_isthrowboom(false),m_zorder(3000),m_maxpowervalue(4),
	m_appearpos(ccp(160,60)),m_hurtcolorlife(0),m_active(true)
{

}

Ship::~Ship()
{

}

bool Ship::init()
{
	if (!CCSprite::init())
	{
		return false;
	}

	CCTexture2D* shiptexturecache = CCTextureCache::sharedTextureCache()->addImage(rship);
	this->initWithTexture(shiptexturecache, CCRectMake(0,0,60,38));
	this->setPosition(m_appearpos);

	CCSpriteFrame* frame0 = CCSpriteFrame::createWithTexture(shiptexturecache,CCRectMake(0,0,60,38));
	CCSpriteFrame* frame1 = CCSpriteFrame::createWithTexture(shiptexturecache,CCRectMake(60,0,60,38));
	CCArray* animframes = CCArray::create();
	animframes->addObject(frame0);
	animframes->addObject(frame0);

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animframes,0.1f);
	CCAnimate* animate = CCAnimate::create(animation);
	this->runAction(CCRepeatForever::create(animate));

	this->schedule(schedule_selector(Ship::shoot),0.16f);

	this->m_canbeattack = false;
	CCSprite* goastsprite = CCSprite::createWithTexture(shiptexturecache,CCRectMake(0,45,60,38));
	ccBlendFunc cb1 = {GL_SRC_ALPHA, GL_ONE};
	goastsprite->setBlendFunc(cb1);
	goastsprite->setScale(8);
	goastsprite->setPosition(ccp(this->getContentSize().width/2,12));
	this->addChild(goastsprite,3000,99999);
	goastsprite->runAction(CCScaleTo::create(0.5,1,1));
	
	CCBlink* bl = CCBlink::create(3,9);
	CCCallFuncN* makebeattack = CCCallFuncN::create(this,callfuncN_selector(Ship::makeattack));
	this->runAction(CCSequence::create(CCDelayTime::create(0.5),bl,makebeattack,NULL));

	return true;
}

void Ship::update(float dt)
{
	if (m_HP<0)
	{
		m_active = false;
	}
}

void Ship::shoot(float dt)
{
	int offset = 13;
	CCPoint pos = this->getPosition();
	CCSize size = this->getContentSize();
	Bullet* bulleta = new Bullet(m_bulletspeed, "W1.png", 1);
	if (bulleta)
	{
		bulleta->autorelease();
		play_bullet->addObject(bulleta); 
		this->getParent()->addChild(bulleta,bulleta->m_zorder,901);
		bulleta->setPosition(ccp(pos.x+offset,pos.y+3+size.height*0.3));
	}else
	{
		delete bulleta;
		bulleta=NULL;
	}

	Bullet* bulletb = new Bullet(m_bulletspeed, "W1.png", 1);
	if (bulletb)
	{
		bulletb->autorelease();
		play_bullet->addObject(bulletb);
		this->getParent()->addChild(bulletb,bulletb->m_zorder,901);
		bulletb->setPosition(ccp(pos.x-offset,pos.y+3+size.height*0.3));
	}else
	{
		delete bulletb;
		bulleta=NULL;
	}
}

void Ship::makeattack(CCNode* psender)
{
	this->m_canbeattack = true;
	this->setVisible(true);
	psender->removeChildByTag(99999);
}

void Ship::hurt()
{
	if (m_canbeattack)
	{
		m_HP--;
		this->setColor(ccc3(255,0,0));
	}
}

void Ship::destroy()
{
	Config::sharedConfig()->updateLifeCount();
	Effect* effect = Effect::create();
	effect->explode(this->getParent(),this->getPosition());
	this->removeFromParent();
	if (Config::sharedConfig()->getAudioStatus())
	{
		SimpleAudioEngine::sharedEngine()->playEffect(rshipdestroy);
	}
}

bool Ship::isactive()
{
	return m_active;
}

CCRect Ship::colliderect()
{
	CCPoint pos = getPosition();
	CCSize size = getContentSize();
	CCRect rect = CCRectMake(pos.x -size.width/2,pos.y-size.height/2,size.width,size.height);
	return rect;
}

int Ship::getzorder()
{
	return m_zorder;
}