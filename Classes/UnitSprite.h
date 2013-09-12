
#ifndef UNIT_SPRITE_H
#define UNIT_SPRITE_H

#include "cocos2d.h"

using namespace cocos2d;

 
class CostomeKeypadDelegate : public CCKeypadDelegate , public CCNode
{
public:
	virtual void keyBackClicked();
};

class UnitSprite : public CCSprite
{
private:
	
public:
	UnitSprite();
	~UnitSprite();
	virtual void destroy() =0;
	virtual void hurt() =0;
	virtual CCRect colliderect() =0;
	virtual bool isactive() =0;

};

#endif