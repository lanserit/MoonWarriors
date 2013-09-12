
#ifndef ABOUT_H
#define ABOUT_H

#include "cocos2d.h"
using namespace cocos2d;

class About : public CCLayer
{
public:
	static CCScene* scene();
	virtual bool init();
	void goBack(CCObject* psender); 
	void wiGame(CCObject* psender);
	
	CREATE_FUNC(About);
};

#endif