
#include "Effect.h"
#include "Resources.h"

Effect::Effect()
{

}

Effect::~Effect()
{
	
}

Effect* Effect::create()
{
	Effect* effect = new Effect();
	if (effect)
	{
		effect->autorelease();
		return effect;
	}else
	{
		delete effect;
		effect = NULL;
		return NULL;
	} 
}

void Effect::flareEffect(CCNode* parent, CCCallFunc* callback)
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* flare = CCSprite::create();
	flare->initWithFile(rflare);
	ccBlendFunc cb1 = {GL_SRC_ALPHA, GL_ONE};
	flare->setBlendFunc(cb1);
	parent->addChild(flare,10);
	flare->setOpacity(0);
	flare->setPosition(ccp(-30,winsize.height-130));
	flare->setRotation(-120);
	flare->setScale(0.2);
	
	CCActionInterval* opanim = CCFadeTo::create(0.5, 255);
	CCActionInterval* opdim = CCFadeTo::create(1,0);
	
	CCActionInterval* biganim = CCScaleBy::create(0.7, 1.2, 1.2);
	CCEaseSineOut* biggerease = CCEaseSineOut::create(biganim);

	CCActionInterval* moveanim = CCMoveBy::create(0.5,ccp(328,0));
	CCEaseSineOut* moveease = CCEaseSineOut::create(moveanim);

	CCActionInterval* roteanim = CCRotateBy::create(2.5,90);
	CCEaseExponentialOut* roteease = CCEaseExponentialOut::create(roteanim);

	CCScaleTo* bigger = CCScaleTo::create(0.5,1);

	CCCallFuncN* removefunc = CCCallFuncN::create(flare, callfuncN_selector(Effect::killSprite));

	flare->runAction(CCSequence::create(opanim, biggerease, opdim, removefunc, callback, NULL));
	flare->runAction(moveease);
	flare->runAction(roteease);
	flare->runAction(bigger);
}


void Effect::killSprite(CCNode* psender)
{
	psender->removeFromParent();
}


void Effect::sharedExplosion()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(rexplosionplist);
	CCArray* animFrames = CCArray::create();
	char str[64] = {0};
	for (int i = 1; i < 35; i++)
	{
		sprintf(str, "explosion_%02d.png",i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.04f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "Explosion");
}

void Effect::explode(CCNode* parent, CCPoint pos)
{
	CCSpriteFrame* pframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("explosion_01.png");
	CCSprite* explosion = CCSprite::createWithSpriteFrame(pframe);
	parent->addChild(explosion);
	explosion->setPosition(pos);
	CCSize size = explosion->getContentSize();
	CCCallFuncN* removefunc = CCCallFuncN::create(explosion,callfuncN_selector(Effect::killSprite));
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("Explosion");
	explosion->runAction(CCSequence::create(CCAnimate::create(animation), removefunc, NULL));
}

void Effect::spark(CCPoint pos, CCNode* parent, float scale, float duration)
{
	CCSprite* one = CCSprite::create(rexplode1);
	CCSprite* two = CCSprite::create(rexplode2);
	CCSprite* three = CCSprite::create(rexplode3);

	ccBlendFunc	bl = {GL_SRC_ALPHA, GL_ONE};
	one->setBlendFunc(bl);
	two->setBlendFunc(bl);
	three->setBlendFunc(bl);

	one->setPosition(pos);
	two->setPosition(pos);
	three->setPosition(pos);

	parent->addChild(one);
	parent->addChild(two);
	parent->addChild(three);

	one->setScale(scale);
	two->setScale(scale);
	three->setScale(scale);

	three->setRotation(CCRANDOM_0_1()*360);

	CCRotateBy* left = CCRotateBy::create(duration, -45);
	CCRotateBy* right = CCRotateBy::create(duration, 45);
	CCScaleBy* scaleby = CCScaleBy::create(duration, 3);
	CCFadeOut* fadeout = CCFadeOut::create(duration);

	CCCallFuncN* remove1 = CCCallFuncN::create(this, callfuncN_selector(Effect::killSprite));
	CCCallFuncN* remove2 = CCCallFuncN::create(this, callfuncN_selector(Effect::killSprite));
	CCCallFuncN* remove3 = CCCallFuncN::create(this, callfuncN_selector(Effect::killSprite));

	CCAction* seq1 = CCSequence::create(fadeout, remove1, NULL);
	CCAction* seq2 = CCSequence::create((CCFadeOut*)fadeout->copy(), remove2, NULL);
	CCAction* seq3 = CCSequence::create((CCFadeOut*)fadeout->copy(), remove3, NULL);

	one->runAction(left);
	two->runAction(right);
	
	one->runAction(scaleby);
	two->runAction((CCScaleBy*)scaleby->copy());
	three->runAction((CCScaleBy*)scaleby->copy());

	one->runAction(seq1);
	two->runAction(seq2);
	three->runAction(seq3);
}