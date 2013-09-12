
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "StartMenu.h"
#include "UnitSprite.h"
#include "Resources.h"
#include "Config.h"
#include "Options.h"
#include "About.h"
#include "Effect.h"
#include "GameLayer.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* StartMenu::scene()
{
	CCScene* scene = CCScene::create();
	StartMenu* layer = StartMenu::create();
	scene->addChild(layer);

	return scene;
}

bool StartMenu::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//添加键盘处理代理
	this->setKeypadEnabled(true);
	CostomeKeypadDelegate* keyDelegate = new CostomeKeypadDelegate();
	keyDelegate->autorelease();
	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(keyDelegate);

	//添加loading logo menu ship
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	float scalex = winsize.width/320;
	float scaley = winsize.height/480;
	
	CCSprite* loading = CCSprite::create();
	loading->initWithFile(rloading);
	loading->setScaleX(winsize.width/loading->getContentSize().width);
	loading->setScaleY(winsize.height/loading->getContentSize().height);
	loading->setAnchorPoint(ccp(0,0));
	this->addChild(loading, 0, 0);
	loading->setPosition(CCPointZero);

	CCSprite* logo = CCSprite::create();
	logo->initWithFile(rlogo);
	logo->setScaleX(scalex);
	logo->setScaleY(scaley);
	logo->setAnchorPoint(ccp(0.5,1));
	logo->setPosition(ccp(winsize.width/2,winsize.height-50));
	this->addChild(logo,10,1);

	CCSprite* newgamenormal = CCSprite::create(rmenu, CCRect(0,0, 126,33));
	newgamenormal->setScaleX(scalex);
	newgamenormal->setScaleY(scaley);
	CCSprite* newgameselected = CCSprite::create(rmenu, CCRect(0,33, 126,33));
	newgameselected->setScaleX(scalex);
	newgameselected->setScaleY(scaley);
	CCSprite* newgamedisabled = CCSprite::create(rmenu, CCRect(0,66, 126,33));
	newgamedisabled->setScaleX(scalex);
	newgamedisabled->setScaleY(scaley);
	
	CCSprite* newsettingnormal = CCSprite::create(rmenu, CCRect(126,0, 126, 33));
	newsettingnormal->setScaleX(scalex);
	newsettingnormal->setScaleY(scaley); 
	CCSprite* newsettingselected = CCSprite::create(rmenu, CCRect(126,33, 126,33));
	newsettingselected->setScaleX(scalex);
	newsettingselected->setScaleY(scaley); 
	CCSprite* newsettingdisabled = CCSprite::create(rmenu, CCRect(126,66, 126,33));
	newsettingdisabled->setScaleX(scalex);
	newsettingdisabled->setScaleY(scaley);

	CCSprite* aboutnormal = CCSprite::create(rmenu, CCRect(126*2,0, 126,33));
	aboutnormal->setScaleX(scalex);
	aboutnormal->setScaleY(scaley);
	CCSprite* aboutselected = CCSprite::create(rmenu, CCRect(126*2,33, 126,33));
	aboutselected->setScaleX(scalex);
	aboutselected->setScaleY(scaley);
	CCSprite* aboutdisabled = CCSprite::create(rmenu, CCRect(126*2,33*2, 126,33));
	aboutdisabled->setScaleX(scalex);
	aboutdisabled->setScaleY(scaley);

	CCMenuItemSprite* newgame = CCMenuItemSprite::create(newgamenormal,newgameselected,newgamedisabled,this,menu_selector(StartMenu::flareEffect));
	CCMenuItemSprite* newsetting = CCMenuItemSprite::create(newsettingnormal, newsettingselected, newsettingdisabled, this, menu_selector(StartMenu::menu_callback));
	newsetting->setTag(20);
	CCMenuItemSprite* about = CCMenuItemSprite::create(aboutnormal, aboutselected, aboutdisabled, this, menu_selector(StartMenu::menu_callback));
	about->setTag(21);
	CCMenu* menu = CCMenu::create(newgame,newsetting,about,NULL);
	menu->alignItemsVerticallyWithPadding(30*scaley);
	this->addChild(menu, 1, 2);
	menu->setPosition(ccp(winsize.width/2,winsize.height/2-80*scaley));
	
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(rship);
	m_ship = CCSprite::createWithTexture(texture, CCRect(0,45,60,38));
	this->addChild(m_ship, 0, 4);
	CCPoint pos = ccp(CCRANDOM_0_1()*winsize.width,0);
	m_ship->setPosition(pos);
	m_ship->runAction(CCMoveBy::create(2, ccp(CCRANDOM_0_1()*winsize.width, pos.y+winsize.height+100)));

	if (Config::sharedConfig()->getAudioStatus())
	{
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7);
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(rmainmusic, false);
	}
	
	this->schedule(schedule_selector(StartMenu::update), 0.1f);

	return true;
}

void StartMenu::flareEffect(CCObject* node)
{
	onButtonEffect();
	Effect* flareeffect = Effect::create();
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(StartMenu::newGame));
	flareeffect->flareEffect(this,callback);
}

void StartMenu::menu_callback(CCObject* psender)
{
	onButtonEffect();
	int tag = ((CCNode*)psender)->getTag();
	if (tag==20)
	{
		CCScene* scene = Options::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2,scene));
	}else if (tag==21)
	{
		CCScene* scene = About::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2,scene));
	}
}

void StartMenu::update(float dt)
{
	if (m_ship->getPositionY() > winsize.height)
	{
		CCPoint pos = ccp(CCRANDOM_0_1()*winsize.width, 10);
		m_ship->setPosition(pos);
		m_ship->runAction(CCMoveBy::create(floor(CCRANDOM_0_1()*5), ccp(CCRANDOM_0_1()*winsize.width,pos.y+winsize.height)));
	} 
}

void StartMenu::onButtonEffect()
{
	if (Config::sharedConfig()->getAudioStatus())
	{
		SimpleAudioEngine::sharedEngine()->playEffect(rbuttoneffect, false);
	}
}

void StartMenu::newGame()
{
	CCScene* scene = CCScene::create();
	GameLayer* gamelayer = GameLayer::create();
	scene->addChild(gamelayer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2,scene));
}