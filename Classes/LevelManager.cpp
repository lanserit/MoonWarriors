
#include "LevelManager.h"
#include "GameLayer.h"
#include "Enemy.h"
 
using namespace cocos2d;

extern CCArray* enemy_items;

LevelManager::LevelManager(CCLayer* gamelayer)
{
	m_gamelayer = gamelayer;
	m_enemies = Config::sharedConfig()->getEnemies();
	m_enemytype = Config::sharedConfig()->getEnemyType();
}

LevelManager::~LevelManager()
{
	
}

void LevelManager::loadLevelResource(int dt)
{
	for (vector<EnemyInfo>::iterator itr = m_enemies.begin(); itr!=m_enemies.end(); itr++)
	{
		if (itr->showtype=="Repeate")
		{
			if (dt%itr->showtime==0)
			{
				for (int i = 0; i != 3; i ++)
				{
					this->addEnemyToGamelayer(itr->types[i]);
				}
			}
		}
	}
}

void LevelManager::addEnemyToGamelayer(int type)
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	EnemyType enemytype = m_enemytype[type];
	Enemy* enemy = Enemy::create(enemytype);

	CCPoint enemyPos = ccp(80+(winsize.width-160)*CCRANDOM_0_1(),winsize.height);
	CCSize esize = enemy->getContentSize();
	enemy->setPosition(enemyPos);

	CCPoint offset;
	CCAction* tmpaction;
	CCMoveBy* a0;
	CCMoveBy* a1;
	CCCallFuncN* oncomplete;

	switch (enemy->getmovetype())
	{
	case 0:
		if (((GameLayer*)m_gamelayer)->getship())
		{
			offset = ((GameLayer*)m_gamelayer)->getship()->getPosition();
		}else
		{
			offset = ccp(winsize.width/2,0);
		}
		tmpaction = CCMoveTo::create(1,offset);
		break;
	case 1:
		offset = ccp(0, -winsize.height-esize.height);
		tmpaction = CCMoveBy::create(4,offset);
		break;
	case 2:
		offset = ccp(0, -100-200*CCRANDOM_0_1());
		a0 = CCMoveBy::create(0.5,offset);
		a1 = CCMoveBy::create(1,ccp(-50-100*CCRANDOM_0_1(),0));
		oncomplete = CCCallFuncN::create(enemy,callfuncN_selector(LevelManager::repeatAction));
		tmpaction = CCSequence::create(a0,a1,oncomplete,NULL);
		break;
	case 3:
		int newx = (enemyPos.x<=winsize.width/2) ? 320 : -320;
		a0 = CCMoveBy::create(4,ccp(newx,-240));
		a1 = CCMoveBy::create(4,ccp(-newx,-320));
		tmpaction = CCSequence::create(a0,a1,NULL);
		break; 
	}

	m_gamelayer->addChild(enemy,enemy->getZOrder(),1000);
	enemy_items->addObject(enemy);
	enemy->runAction(tmpaction);
}

void LevelManager::repeatAction(CCNode* psender)
{
	CCDelayTime* delay = CCDelayTime::create(1);
	CCMoveBy* mv = CCMoveBy::create(1,ccp(100+100*CCRANDOM_0_1(),0));
	CCFiniteTimeAction* seq = CCSequence::create(delay,mv,delay->copy(), mv->reverse(), NULL);
	psender->runAction(CCRepeatForever::create((CCActionInterval*)seq));
}
