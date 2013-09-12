
#include "Config.h"

static Config* g_config = NULL;
extern CCArray* play_bullet;
extern CCArray* enemy_bullet;
extern CCArray* enemy_items;

Config::Config():m_scoreValue(0), m_life(3), m_isAudioOn(true)
{
	CCAssert(g_config==NULL, "g_config is already allocated");

	EnemyInfo tmp;
	tmp.showtype = "Repeate";
	tmp.showtime = 2;
	tmp.types[1] = 1;
	tmp.types[2] = 2;
	m_enemies.push_back(tmp);

	tmp.showtime = 5;
	tmp.types[0] = 3;
	tmp.types[1] = 4;
	tmp.types[2] = 5;
	m_enemies.push_back(tmp);

	EnemyType enemytype;
	enemytype.bullettype = "W2.png";
	enemytype.texturename = "E0.png";
	enemytype.type = 0;
	enemytype.hp  = 1;
	enemytype.movetype = 0;
	enemytype.scorevalue = 15;
	m_enemytypes.push_back(enemytype);

	enemytype.type = 1;
	enemytype.bullettype = "W2.png";
	enemytype.texturename = "E1.png";
	enemytype.hp = 2;
	enemytype.movetype = 0;
	enemytype.scorevalue = 40;
	m_enemytypes.push_back(enemytype);

	enemytype.type = 2;
	enemytype.texturename = "E2.png";
	enemytype.bullettype = "W2.png";
	enemytype.hp = 4;
	enemytype.movetype = 2;
	enemytype.scorevalue = 60;
	m_enemytypes.push_back(enemytype);

	enemytype.type = 3;
	enemytype.texturename = "E3.png";
	enemytype.bullettype = "W2.png";
	enemytype.hp = 6;
	enemytype.movetype = 3;
	enemytype.scorevalue = 80;
	m_enemytypes.push_back(enemytype);

	enemytype.type = 4;
	enemytype.texturename = "E4.png";
	enemytype.bullettype = "W2.png";
	enemytype.hp = 10;
	enemytype.movetype = 2;
	enemytype.scorevalue = 150;
	m_enemytypes.push_back(enemytype);

	enemytype.type = 5;
	enemytype.texturename = "E5.png";
	enemytype.bullettype = "W2.png";
	enemytype.hp = 15;
	enemytype.movetype = 2;
	enemytype.scorevalue = 200;
	m_enemytypes.push_back(enemytype);
}

Config::~Config()
{
	play_bullet->release();
	enemy_bullet->release();
	enemy_items->release();
}

Config* Config::sharedConfig()
{
	if (!g_config)
	{
		g_config = new Config();
	}
	return g_config;
}

bool Config::getAudioStatus()
{
	return m_isAudioOn;
}

void Config::updateAudioStatus(bool var)
{
	m_isAudioOn = var;
}

vector<EnemyInfo> Config::getEnemies()
{
	return m_enemies;
}

vector<EnemyType> Config::getEnemyType()
{
	return m_enemytypes;
}

int Config::getScoreValue()
{
	return m_scoreValue;
}

void Config::setScoreValue(int score)
{
	m_scoreValue += score;
}

int Config::getLifeCount()
{
	return m_life;
}

void Config::updateLifeCount()
{
	m_life--;
}

void Config::resetConfig()
{
	m_scoreValue = 0;
	m_life = 3;
}

