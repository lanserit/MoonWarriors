
#ifndef OPTIONS_H
#define OPTIONS_H

#include "cocos2d.h"
using namespace cocos2d;


class Options : public CCLayer
{
public:
	static CCScene* scene(); 
	virtual bool init();
	void setOptions(CCObject* psender); 
	void goBack(CCObject* psender); 

	CREATE_FUNC(Options);
};

#endif // !OPTIONS_H
