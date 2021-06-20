#pragma once

#ifndef __BASIC_ENEMY_H__
#define __BASIC_ENEMY_H__

#include "cocos2d.h"
USING_NS_CC;


typedef enum {
	enemyice1,
	enemyice2,
	enemyice3,
	enemyice4
}EnemyTypes;


class Enemy :public cocos2d::Sprite 
{
private:
	CC_SYNTHESIZE(int, hitPoints, HitPoints); 
	CC_SYNTHESIZE(bool, alive, Alive);
	CC_SYNTHESIZE(int, enemyType, EnemyType);

public:
	Enemy* enemy;
	
	static Enemy* createWithSpriteName(const char* spriteName);
	//Enemy* Enemy::createName(cocos2d::Vec2& pos, const char* spriteName);
	//virtual bool init(cocos2d::Vec2& pos); //设置敌人的初始位置和类型

	static Enemy* NearestEnemy(int BulleteType, Vec2 knightPos, Vector<Enemy*> enemyArray);
	//void moveRandom();

	//virtual void update(float dt);

	//static Enemy* createWithSpriteName(const char* spriteName);
	
	//CREATE_FUNC(Enemy);
	//Enemy();
	//~Enemy();

};

#endif 