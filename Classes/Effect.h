
#ifndef EFFECT_H
#define EFFECT_H

#include "cocos2d.h"

using namespace cocos2d;

class Effect : public CCNode
{
private:
	CCSprite* m_sprite;

public:
	Effect();
	~Effect();
	static Effect* create();
	void flareEffect(CCNode* parent, CCCallFunc* callback);
	void killSprite(CCNode* psender);
	static void sharedExplosion();
	void explode(CCNode* parent, CCPoint pos);
	void spark(CCPoint pos, CCNode* parent, float scale, float duration);
};

#endif