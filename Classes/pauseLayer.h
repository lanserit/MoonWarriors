
#ifndef PAUSE_LAYER_H
#define PAUSE_LAYER_H

#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer : public CCLayerColor
{
public:
	virtual bool init();
	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	void doResume(CCObject* psender);
	
	CREATE_FUNC(PauseLayer);
}; 

#endif // 
