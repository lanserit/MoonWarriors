
#include "GameLayer.h"
#include "Resources.h" 
#include "Global.h"
#include "Enemy.h"
#include "Effect.h"
#include "LevelManager.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"
#include "pauseLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

extern CCArray* enemy_items;

GameLayer::GameLayer():m_state(stateplaying), m_time(0), m_isbackskyreload(false), m_isbacktilemapreload(false), 
	m_ship(NULL), m_backsky(NULL), m_backskyheight(0), m_backskyre(NULL), m_backtilemap(NULL), m_backtilemapheight(0), 
	m_backtilemapre(NULL), m_scorelb(NULL), m_lifecountlb(NULL), m_tmpscore(0) 
{

}

GameLayer::~GameLayer()
{
	if (m_levelmanager)
	{
		delete m_levelmanager;
	}
	play_bullet->release();
	enemy_bullet->release();
	enemy_items->release();
}

bool GameLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	winsize = CCDirector::sharedDirector()->getWinSize();

	this->setTouchEnabled(true);
	this->setAccelerometerEnabled(true);

	//
	play_bullet = CCArray::create();
	play_bullet->retain(); 

	//
	enemy_bullet = CCArray::create();
	enemy_bullet->retain();
	enemy_items = CCArray::create();
	enemy_items->retain();

	m_state = stateplaying; 

	Enemy::sharedEnemy();
	Effect::sharedExplosion();
	
	Config::sharedConfig()->resetConfig();
	m_levelmanager = new LevelManager(this);

	initBackGround();
	
	m_screenrect = CCRectMake(0,0,winsize.width,winsize.height+10);

	m_scorelb = CCLabelBMFont::create("Score:0",rarial14_fnt);
	m_scorelb->setAnchorPoint(ccp(1,0));
	m_scorelb->setAlignment(kCCTextAlignmentRight);
	this->addChild(m_scorelb,1000);
	m_scorelb->setPosition(winsize.width-5,winsize.height-30);

	//ship life
	CCTexture2D* shiptexture = CCTextureCache::sharedTextureCache()->addImage(rship);
	CCSprite* life = CCSprite::createWithTexture(shiptexture,CCRectMake(0,0,60,38));
	life->setScale(0.6);
	life->setPosition(ccp(30,winsize.height-23));
	this->addChild(life,1,5);

	//
	char lifecount[2];
	sprintf(lifecount,"%d",Config::sharedConfig()->getLifeCount());
	m_lifecountlb = CCLabelTTF::create(lifecount,"Arial",20);
	m_lifecountlb->setPosition(ccp(60,winsize.height-20));
	m_lifecountlb->setColor(ccc3(255,0,0));
	this->addChild(m_lifecountlb,1000);

	//
	m_ship = Ship::create();
	this->addChild(m_ship,m_ship->getzorder(),1001);

	CCMenuItemImage* pause = CCMenuItemImage::create("pause.png","pause.png",this,menu_selector(GameLayer::dopause));
	pause->setAnchorPoint(ccp(1,0));
	pause->setPosition(ccp(winsize.width,0));
	CCMenu* menu = CCMenu::create(pause,NULL);
	menu->setAnchorPoint(ccp(0,0));
	this->addChild(menu,1,10);
	menu->setPosition(CCPointZero);

	this->scheduleUpdate(); 
	schedule(schedule_selector(GameLayer::scorecounter),1);

	if (Config::sharedConfig()->getAudioStatus())
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(rbgmusic,true);
	}
	
	return true;
}

void GameLayer::update(float dt)
{
	if (m_state==stateplaying)
	{
		checkcollide();
		removeinactiveunit(dt);
		checkisreborn();
		updateUI();
	}
}

void GameLayer::initBackGround()
{
	m_backsky = CCSprite::create();
	m_backsky->initWithFile(rbg01);
	m_backsky->setScaleX(winsize.width/m_backsky->getContentSize().width);
	m_backsky->setScaleY(winsize.height/m_backsky->getContentSize().height);
	m_backsky->setAnchorPoint(CCPointZero);
	m_backskyheight = m_backsky->getContentSize().height;
	this->addChild(m_backsky,-10);
	m_backsky->setPosition(CCPointZero);

	m_backtilemap = CCTMXTiledMap::create(rlevel01);
	this->addChild(m_backtilemap,-9);
	m_backtilemapheight = m_backtilemap->getMapSize().height*m_backtilemap->getTileSize().height;

	m_backskyheight -= 48;
	m_backtilemapheight -= 200;
	m_backsky->runAction(CCMoveBy::create(3, ccp(0,-48)));
	m_backtilemap->runAction(CCMoveBy::create(3, ccp(0,-200)));

	schedule(schedule_selector(GameLayer::movingBackGround), 3.0f);
}

void GameLayer::movingBackGround(float dt)
{
	m_backsky->runAction(CCMoveBy::create(3, ccp(0,-48)));
	m_backtilemap->runAction(CCMoveBy::create(3, ccp(0,-200)));
	m_backskyheight -= 48;
	m_backtilemapheight -= 200;

	if (m_backskyheight<=winsize.height)
	{
		if (!m_isbackskyreload)
		{
			m_backskyre = CCSprite::create();
			m_backskyre->initWithFile(rbg01);
			m_backskyre->setScaleX(winsize.width/m_backskyre->getContentSize().width);
			m_backskyre->setScaleY(winsize.height/m_backskyre->getContentSize().height);
			m_backskyre->setAnchorPoint(CCPointZero);
			this->addChild(m_backskyre, -10);
			m_backskyre->setPosition(ccp(0,winsize.height));
			m_isbackskyreload = true;
		}
		m_backskyre->runAction(CCMoveBy::create(3,ccp(0,-48)));
	}

	if (m_backskyheight<=0)
	{
		m_backskyheight = m_backskyheight+m_backsky->getContentSize().height;
		this->removeChild(m_backsky,true);
		m_backsky = m_backskyre;
		m_backskyre = NULL;
		m_isbackskyreload = false;
	}

	if (m_backtilemapheight<=winsize.height)
	{
		if (!m_isbacktilemapreload)
		{
			m_backtilemapre = CCTMXTiledMap::create(rlevel01);
			m_backtilemapre->setAnchorPoint(CCPointZero);
			this->addChild(m_backtilemapre, -9);
			m_backtilemapre->setPosition(0,winsize.height);
			m_isbacktilemapreload = true;
		}
		m_backtilemapre->runAction(CCMoveBy::create(3,ccp(0,-200)));
	}

	if (m_backtilemapheight<=0)
	{
		m_backtilemapheight = m_backtilemapheight+m_backtilemap->getContentSize().height;
		this->removeChild(m_backtilemap,true);
		m_backtilemap = m_backtilemapre;
		m_backtilemapre = NULL;
		m_isbacktilemapreload = false;
	}
}
 
void GameLayer::onEnter()
{
	CCDirector* pdirector = CCDirector::sharedDirector();
	pdirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayer::onEnter();
}

void GameLayer::onExit()
{
	CCDirector* pdirector = CCDirector::sharedDirector();
	pdirector->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return true;
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if ( (m_state==stateplaying) && m_ship )
	{
		CCPoint pos = touch->getDelta();
		CCPoint currentpos = m_ship->getPosition();
		currentpos = ccpAdd(currentpos,pos); 
		m_ship->setPosition(currentpos);
	}
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{ 
}

void GameLayer::didAccelerate(CCAcceleration* pAccelerationValue)
{
	if( (m_state==stateplaying) && m_ship)
	{ 
		CCSize winsize = CCDirector::sharedDirector()->getWinSize();
		CCPoint ptNow = m_ship->getPosition();
		CCPoint tmp = CCDirector::sharedDirector()->convertToUI(ptNow);
		tmp.x += (int)(pAccelerationValue->x*G);
		tmp.y -= (int)(pAccelerationValue->y*G);
		CCPoint next = CCDirector::sharedDirector()->convertToGL(tmp);
		if(next.x>=0 && next.x<=winsize.width && next.y>=0 && next.y<=winsize.height)
		{
			m_ship->setPosition(next);  
		} 
	}
}

void GameLayer::scorecounter(float dt)
{
	if (m_state==stateplaying)
	{
		m_time++;
		m_levelmanager->loadLevelResource(m_time);
	}
}

Ship* GameLayer::getship()
{
	return m_ship;
}

void GameLayer::checkcollide()
{
	CCObject* units;
	CCObject* bullets;
	CCObject* enemybls;
	
	CCARRAY_FOREACH(enemy_items, units)
	{
		UnitSprite* enemy = dynamic_cast<UnitSprite*>(units);
		CCARRAY_FOREACH(play_bullet, bullets)
		{
			UnitSprite* bullet = dynamic_cast<UnitSprite*>(bullets);
			if (this->collide(enemy, bullet))
			{
				//进不来
				enemy->hurt();
				bullet->hurt(); 
			}
			if (!m_screenrect.intersectsRect(bullet->boundingBox()))
			{
				bullet->destroy();
			}
		}
		if (this->collide(enemy,m_ship))
		{
			if (m_ship->isactive())
			{
				enemy->hurt();
				m_ship->hurt();
			}
		}
		if (!m_screenrect.intersectsRect(enemy->boundingBox()))
		{
			enemy->destroy();
		} 
	}

	CCARRAY_FOREACH(enemy_bullet, enemybls)
	{
		UnitSprite* enemyb = dynamic_cast<UnitSprite*>(enemybls);
		if (enemyb)
		{
			if (collide(enemyb,m_ship))
			{
				if (m_ship->isactive())
				{
					//进不来
					enemyb->hurt();
					m_ship->hurt();
				}
			}
			if (!m_screenrect.intersectsRect(enemyb->boundingBox()))
			{
				enemyb->destroy();
			}
		}	
	}
}

bool GameLayer::collide(UnitSprite* a, UnitSprite* b)
{
	if (!a || !b)
	{
		return false;
	}
	CCRect arect = a->colliderect();
	CCRect brect = b->colliderect();
	if (arect.intersectsRect(brect))
	{
		return true;
	}
	return false;
}

void GameLayer::removeinactiveunit(float dt)
{
	CCArray* childrean = this->getChildren();
	for (int i = 0; i < childrean->count(); i++)
	{
		CCSprite* selchild = dynamic_cast<CCSprite*>(childrean->objectAtIndex(i));
		if (selchild)
		{
			selchild->update(dt);
			int tag = selchild->getTag();
			if (tag==900 || tag==901 || tag==1000)
			{
				if (!((UnitSprite*)selchild)->isactive())
				{
					((UnitSprite*)selchild)->destroy();
				}
			}
		}
	}

	if (m_ship)
	{
		if (!m_ship->isactive())
		{
			m_ship->destroy();
			m_ship=NULL;
		}
	} 
}

void GameLayer::checkisreborn()
{
	if (Config::sharedConfig()->getLifeCount()>0)
	{
		if (!m_ship)
		{
			m_ship = Ship::create();
			this->addChild(m_ship, m_ship->getzorder(),1001);
		}
	}else if (Config::sharedConfig()->getLifeCount()<=0)
	{
		m_state = stategameover;
		m_ship = NULL;
		CCCallFunc* game_over = CCCallFunc::create(this,callfunc_selector(GameLayer::gameover));
		this->runAction(CCSequence::create(CCDelayTime::create(0.2), game_over, NULL));
	}
}

void GameLayer::updateUI()
{
	if (m_tmpscore<Config::sharedConfig()->getScoreValue())
	{
		m_tmpscore += 5;
	}
	
	char score[20]; 
	char s[20] = "Score:";
	sprintf(score, "%d", m_tmpscore);
	m_scorelb->setString(strcat(s,score));
	char lifecount[2];
	sprintf(lifecount,"%d",Config::sharedConfig()->getLifeCount());
	m_lifecountlb->setString(lifecount); 
}

void GameLayer::gameover()
{
	CCScene* scene = GameOver::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2,scene));
}

void GameLayer::dopause(CCObject* psender)
{
	CCDirector::sharedDirector()->pause();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	PauseLayer* layer = PauseLayer::create();
	this->addChild(layer, 9999);
}

