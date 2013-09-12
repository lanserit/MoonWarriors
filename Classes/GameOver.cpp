
#include "GameOver.h"
#include "Resources.h"
#include "Config.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "CommonWiGame.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameOver::scene()
{
	CCScene* scene = CCScene::create();
	GameOver* layer = GameOver::create();
	scene->addChild(layer);

	return scene;
}

bool GameOver::init()
{
	if (!CCLayer::init())
	{
		false;
	}

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	float scalex = winsize.width/320;
	float scaley = winsize.height/480;
	
	CCSprite* sp = CCSprite::create(rloading);
	sp->setScaleX(winsize.width/sp->getContentSize().width);
	sp->setScaleY(winsize.height/sp->getContentSize().height);
	sp->setAnchorPoint(ccp(0,0));
	this->addChild(sp,0,1);
	sp->setPosition(CCPointZero);

	CCSprite* logo = CCSprite::create(rgameover);
	logo->setScaleX(scalex);
	logo->setScaleY(scaley);
	logo->setAnchorPoint(ccp(0.5,0.5));
	logo->setPosition(ccp(winsize.width/2,winsize.height-100*scaley));
	this->addChild(logo,10,1);

	CCSprite* scoreranknormal = CCSprite::create(rscorerank,CCRectMake(0,0,126,33));
	scoreranknormal->setScaleX(scalex);
	scoreranknormal->setScaleY(scaley);
	CCSprite* scorerankselected = CCSprite::create(rscorerank,CCRectMake(0,33,126,33));
	scorerankselected->setScaleX(scalex);
	scorerankselected->setScaleY(scaley);
	CCSprite* scorerankdisabled = CCSprite::create(rscorerank,CCRectMake(0,66,126,33));
	scorerankdisabled->setScaleX(scalex);
	scorerankdisabled->setScaleY(scaley);
	CCMenuItemSprite* scorerank = CCMenuItemSprite::create(scoreranknormal,scorerankselected,scorerankdisabled,this,menu_selector(GameOver::scoreRank));
	CCSprite* playagainnormal = CCSprite::create(rmenu,CCRectMake(378,0,126,33));
	playagainnormal->setScaleX(scalex);
	playagainnormal->setScaleY(scaley);
	CCSprite* playagainselected = CCSprite::create(rmenu,CCRectMake(378,33,126,33));
	playagainselected->setScaleX(scalex);
	playagainselected->setScaleY(scaley);
	CCSprite* playagaindisabled = CCSprite::create(rmenu,CCRectMake(378,66,126,33)); 
	playagaindisabled->setScaleX(scalex);
	playagaindisabled->setScaleY(scaley);
	CCMenuItemSprite* playagain = CCMenuItemSprite::create(playagainnormal,playagainselected,playagaindisabled,this,menu_selector(GameOver::playAgain));
	CCMenu* menu = CCMenu::create(scorerank,playagain,NULL);
	menu->alignItemsVerticallyWithPadding(30*scaley);
	this->addChild(menu,1,2);
	menu->setPosition(winsize.width/2,winsize.height-300*scaley);

	int tmpsocre = Config::sharedConfig()->getScoreValue();
	char score[20];
	char s[20] = "Your Score:";
	sprintf(score,"%d",tmpsocre);
	CCLabelTTF* lb = CCLabelTTF::create(strcat(s,score),"Arial Bold",16);
	lb->setScaleX(scalex);
	lb->setScaleY(scaley);
	lb->setPosition(ccp(winsize.width/2,winsize.height-200*scaley));
	lb->setColor(ccc3(250,179,0));
	this->addChild(lb,10);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(rmainmusic,true);

	return true;
}

void GameOver::playAgain(CCObject* psender)
{
	CCScene* scene = CCScene::create();
	GameLayer* layer = GameLayer::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2,scene));
}

void GameOver::scoreRank(CCObject* psender)
{
	int score = Config::sharedConfig()->getScoreValue();
	startScoreRankUI(score);
}