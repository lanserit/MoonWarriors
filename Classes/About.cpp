
#include "About.h"
#include "Resources.h"
#include "StartMenu.h"
#include "SimpleAudioEngine.h"
#include "CommonWiGame.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* About::scene()
{
	CCScene* scene = CCScene::create();
	About* aboutlayer = About::create();
	scene->addChild(aboutlayer);

	return scene;
}

bool About::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::create(rloading);
	bg->setScaleX(winsize.width/bg->getContentSize().width);
	bg->setScaleY(winsize.height/bg->getContentSize().height);
	bg->setAnchorPoint(CCPointZero);
	this->addChild(bg,0,1);
	bg->setPosition(CCPointZero);

	CCTexture2D* imagechace = CCTextureCache::sharedTextureCache()->addImage(rmenutitle);
	CCSprite* title = CCSprite::createWithTexture(imagechace, CCRect(0,36,100,34));
	title->setPosition(ccp(winsize.width/2,winsize.height-60));
	this->addChild(title);

	CCLabelTTF* about = CCLabelTTF::create("	Most of the game resources are derived from MoonWarriors-html5.\n	This toy utilizes many features from Cocos2d-x engine, including: parallax background, tiledmap, action, ease, frame animation, schedule, label, keyboard dispatcher, scene transtion, etc.\n	Also, we introduced 3 wiyun utilities: WiGame, WiAd, WiOffer.\n Hope You Will Enjoy the Game!", "Arial", 18, CCSizeMake(winsize.width*0.85,320), kCCTextAlignmentLeft);
	about->setPosition(ccp(winsize.width/2,winsize.height/2-20));
	about->setAnchorPoint(ccp(0.5,0.5));
	this->addChild(about);
	
	CCLabelBMFont *wigameLb = CCLabelBMFont::create("WiGame", rfont);
    CCMenuItemLabel *wigame = CCMenuItemLabel::create(wigameLb, this, menu_selector(About::wiGame));
    wigame->setScale(0.6);
    CCActionInterval *fadeIn0 = CCFadeTo::create(0.5, 80);
    CCActionInterval *fadeOut0 = CCFadeTo::create(1, 255);
    CCEaseSineInOut *ease10 = CCEaseSineInOut::create(fadeIn0);
    CCEaseSineInOut *ease20 = CCEaseSineInOut::create(fadeOut0);
    CCFiniteTimeAction *seq0 = CCSequence::create(ease20, ease10, NULL); 
    wigame->runAction(CCRepeatForever::create((CCActionInterval*)seq0));
	
	CCLabelBMFont *backLb = CCLabelBMFont::create("Go Back", rfont);
    CCMenuItemLabel *goBack = CCMenuItemLabel::create(backLb, this, menu_selector(About::goBack));
    goBack->setScale(0.6);
    CCActionInterval *fadeIn = CCFadeTo::create(1, 80);
    CCActionInterval *fadeOut = CCFadeTo::create(1, 255);
    CCEaseSineInOut *ease1 = CCEaseSineInOut::create(fadeIn);
    CCEaseSineInOut *ease2 = CCEaseSineInOut::create(fadeOut);
    CCFiniteTimeAction *seq = CCSequence::create(ease1, ease2, NULL); 
    goBack->runAction(CCRepeatForever::create((CCActionInterval*)seq));
	//
	CCMenu* menu = CCMenu::create(wigame,goBack,NULL);
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(ccp(winsize.width/2,40));
	this->addChild(menu);
    
	return true;
}

void About::goBack(CCObject* psender)
{
	CCScene* scene = StartMenu::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

void About::wiGame(CCObject* psender)
{
	startWiGameUI();
}
 