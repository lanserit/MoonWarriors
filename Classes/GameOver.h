#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "cocos2d.h"

using namespace cocos2d;

class GameOver : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();
	void playAgain(CCObject* psender);
	void scoreRank(CCObject* psender);

	CREATE_FUNC(GameOver);
};

#endif