#ifndef START_MENU_H
#define START_MENU_H

#include "cocos2d.h"
using namespace cocos2d;

class StartMenu : public CCLayer
{
private:
	CCSprite* m_ship;
	CCSize winsize;

public:
	virtual bool init();
	static CCScene* scene();

	void flareEffect(CCObject* node);
	void newGame();
	void menu_callback(CCObject* psender);
	virtual void update(float dt);
	void onButtonEffect();
	 
	CREATE_FUNC(StartMenu);
};

#endif