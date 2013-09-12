
#include "Options.h"
#include "Resources.h"
#include "Config.h"
#include "SimpleAudioEngine.h"
#include "StartMenu.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* Options::scene()
{
	CCScene* scene = CCScene::create();
	Options* optionslayer = Options::create();
	scene->addChild(optionslayer);
	
	return scene;
}

bool Options::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::create();
	bg->initWithFile(rloading);
	bg->setScaleX(winsize.width/bg->getContentSize().width);
	bg->setScaleY(winsize.height/bg->getContentSize().height);
	bg->setAnchorPoint(ccp(0,0));
	this->addChild(bg, 0, 1);
	bg->setPosition(CCPointZero);

	CCTexture2D* imagecache = CCTextureCache::sharedTextureCache()->addImage(rmenutitle);
	CCSprite* title = CCSprite::createWithTexture(imagecache, CCRect(0,0,134,34));
	title->setPosition(ccp(winsize.width/2,winsize.height-60));
	this->addChild(title);

	CCMenuItemFont* menutitle = CCMenuItemFont::create("Sound");
	menutitle->setFontName("Arial");
	menutitle->setFontSize(16);
	menutitle->setEnabled(false);

	CCMenuItemFont::setFontName("Arial");
	CCMenuItemFont::setFontSize(26);
	CCMenuItemToggle* toggle = CCMenuItemToggle::createWithTarget(this,menu_selector(Options::setOptions),CCMenuItemFont::create("On"),CCMenuItemFont::create("Off"),NULL);
	int selectedID = Config::sharedConfig()->getAudioStatus() ? 0 : 1;
	toggle->setSelectedIndex(selectedID);

	CCLabelBMFont* backlb = CCLabelBMFont::create("Go Back", rfont);
	CCMenuItemLabel* goBack = CCMenuItemLabel::create(backlb,this,menu_selector(Options::goBack));
	goBack->setScale(0.6);
	//
	CCActionInterval* fadeIn = CCFadeTo::create(1,80);
	CCActionInterval* fadeOut = CCFadeTo::create(1,255);
	CCEaseSineInOut* ease1 = CCEaseSineInOut::create(fadeIn);
	CCEaseSineInOut* ease2 = CCEaseSineInOut::create(fadeOut);
	CCFiniteTimeAction* seq = CCSequence::create(ease1, ease2, NULL);
	//
	goBack->runAction(CCRepeatForever::create((CCActionInterval*)seq));

	CCMenu* menu = CCMenu::create(menutitle,toggle,goBack,NULL);
	menu->alignItemsInColumns(2,1);
	this->addChild(menu);

	CCPoint pos = goBack->getPosition();
	pos.y -= 50;
	goBack->setPosition(pos);

	return true;
}

void Options::setOptions(CCObject* psender)
{
	bool tmpsound = Config::sharedConfig()->getAudioStatus();
	Config::sharedConfig()->updateAudioStatus(!tmpsound);
	if (Config::sharedConfig()->getAudioStatus())
	{
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}else
	{
		SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

void Options::goBack(CCObject* psender)
{
	CCScene* scene = StartMenu::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2,scene));
}

 