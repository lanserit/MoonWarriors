#ifndef COMMON_WIGAME_H
#define COMMON_WIGAME_H

#include "cocos2d.h"

using namespace cocos2d;

#ifdef __cplusplus	
extern "C" {
#endif

void startWiGameUI();

void startScoreRankUI(int score);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif