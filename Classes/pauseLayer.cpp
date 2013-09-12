
#include "pauseLayer.h"
#include <limits> 
#include "SimpleAudioEngine.h"

using namespace cocos2d; 
using namespace CocosDenshion;

#ifdef min
#undef min
#endif

CCMenu* menu;

bool PauseLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0,0,0,100)))
	{
		return false;
	}

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();

	setTouchEnabled(true);
	CCMenuItemImage* play = CCMenuItemImage::create("play.png","play.png");
	play->setAnchorPoint(ccp(1,0));
	play->setTag(10);
	play->setPosition(ccp(winsize.width,0));
	
	menu = CCMenu::create(play,NULL);
	menu->setAnchorPoint(ccp(0,0));
	this->addChild(menu,1,10);
	menu->setPosition(CCPointZero);

	return true;
}

void PauseLayer::doResume(CCObject* psender)
{

}

void PauseLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()),true);
	CCLayer::registerWithTouchDispatcher();
}

bool PauseLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCRect rect = menu->getChildByTag(10)->boundingBox();
	if (rect.containsPoint(touch->getLocation()))
	{
		CCDirector::sharedDirector()->resume();
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		this->removeFromParent();
	}
	return true;
}

void PauseLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
}

void PauseLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{ 
}