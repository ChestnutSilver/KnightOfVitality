#pragma once
#include "cocos2d.h"
#include "firstKnight.h"
#include "basicEnemy.h"
class Bullet :public cocos2d::Sprite 
{
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);//速度
	Bullet* bullet;

public:
	void shootBulletFromKnight(Knight* knight, Enemy* enemy);

	static Bullet* createWithSpriteName(const char* spriteName);

	virtual void update(float dt);

	void bulletRotate(Bullet* bullet, Knight* knight, Enemy* enemy);//子弹围绕敌人旋转

	void bulletfalse(float dt);//设置子弹（一定时间后）消失

	//void Bullet::ShootManyTimes(Bullet* bullet, Vec2 knightPos, Vec2 enemyPos, Knight* playerKnight, Enemy* enemy);
};