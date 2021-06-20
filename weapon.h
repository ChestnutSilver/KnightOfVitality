#pragma once
#include "cocos2d.h"
#include "firstKnight.h"
#include "basicEnemy.h"

class Weapon :public cocos2d::Sprite
{

	CC_SYNTHESIZE(int, weaponType, WeaponType);
	CC_SYNTHESIZE(int, attackRange, AttackRange);
	//CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);//速度


public:
	//void shootBulletFromKnight(Knight* knight, Enemy* enemy);

	static Weapon* createWithSpriteName(const char* spriteName);

	void weaponRotate(Weapon* weapon, Knight* knight, Enemy* enemy);//子弹围绕敌人旋转

	//void bulletfalse(float dt);//设置子弹（一定时间后）消失
};
