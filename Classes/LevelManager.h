
#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <vector>
#include "cocos2d.h"
#include "Config.h"

using namespace cocos2d;

class LevelManager 
{
private:
	vector<EnemyInfo> m_enemies;
	vector<EnemyType> m_enemytype;
	CCLayer* m_gamelayer;

public:
	LevelManager (CCLayer* gamelayer);
	~LevelManager ();

	
	void repeatAction(CCNode* psender);
	void addEnemyToGamelayer(int type);
	void loadLevelResource(int dt);
};

#endif
