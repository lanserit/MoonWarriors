
#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include "cocos2d.h"
#include "Ship.h"
#include "LevelManager.h"

using namespace cocos2d;

enum State
{
	stateplaying = 0,
	stategameover = 1,
};

class GameLayer : public CCLayer
{
private:
	int m_state;
	int m_time;
	CCSize winsize;
	Ship* m_ship;

	CCSprite* m_backsky;
	CCSprite* m_backskyre;
	CCTMXTiledMap* m_backtilemap;
	CCTMXTiledMap* m_backtilemapre;
	float m_backskyheight;
	float m_backtilemapheight;
	bool m_isbackskyreload;
	bool m_isbacktilemapreload;

	CCLabelBMFont* m_scorelb;
	CCLabelTTF* m_lifecountlb;
	CCRect m_screenrect;
	int m_tmpscore;

	LevelManager* m_levelmanager;

public:
	GameLayer();
	~GameLayer();
	virtual bool init(); 
	virtual void update(float dt);
	void onEnter();
	void onExit();

	void initBackGround();
	void movingBackGround(float dt);

	void scorecounter(float dt);
	Ship* getship();
	void checkcollide();
	void removeinactiveunit(float dt);
	void checkisreborn();
	bool collide(UnitSprite* a, UnitSprite* b);
	void updateUI();
	void gameover();
	void dopause(CCObject* psender);


	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	
	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

	CREATE_FUNC(GameLayer);
};


#endif