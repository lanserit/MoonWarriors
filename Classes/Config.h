
#ifndef CONFIG_H
#define CONFIG_H

#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
 

typedef struct Enemies
{
	string showtype;
	int showtime;
	int types[3];
	Enemies(){
		showtype="Repeate";
		showtime=0;
		types[0]=0;
		types[1]=0;
		types[2]=0;
	}
}EnemyInfo;

typedef struct{
	int type;
	string texturename;
	string bullettype;
	int hp;
	int movetype;
	int scorevalue;
}EnemyType;


class Config : public CCObject
{
private:
	vector<EnemyInfo> m_enemies;
	vector<EnemyType> m_enemytypes;
	int m_scoreValue;
	int m_life;
	bool m_isAudioOn;
	Config();

public:
	~Config();
	static Config* sharedConfig();
	bool getAudioStatus();
	void updateAudioStatus(bool var);
	vector<EnemyInfo> getEnemies();
	vector<EnemyType> getEnemyType();
	int getLifeCount();
	void updateLifeCount();
	int getScoreValue();
	void setScoreValue(int score);
	void resetConfig();
};

#endif