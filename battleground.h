#pragma once
#ifndef _BATTLEGROUND_H_
#define _BATTLEGROUND_H_

#include "cocos2d.h"
#include "firstKnight.h"
#include "basicEnemy.h"
#include "Bullet.h"
#include "weapon.h"
#include "box.h"
#include "smallMap.h"

class BattleGround :public cocos2d::Layer
{
private:
	//friend class Enemy;
	//friend Enemy* NearestEnemy(int BulleteType, Vec2 knightPos, Vector<Enemy*> enemyArray);

	cocos2d::TMXTiledMap* tileMap;
	Knight* playerKnight;
	Box* box;
	//SmallMap* smallMap;
	cocos2d::Sprite miniMap;
	//Enemy* enemy;
	Enemy* enemyBoss;
	Vector<Enemy*> enemyArray;
	Vector<Enemy*> enemyBasicArray;


	Bullet* bullet;
	//Bullet* bullet;
	Vector<Bullet*>bulletArray;

	Weapon* weapon;
	Vector<Weapon*>weaponArray;

	ProgressTimer* pBloodProGress;
	ProgressTimer* pManaProGress;
	ProgressTimer* pArmorProGress;


	CC_SYNTHESIZE(int, bulletType, BulletType);
	cocos2d::TMXLayer* Collidable;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);//ʵ�ּ���wasd�����ƶ�
	cocos2d::EventListenerKeyboard* keyListene;

	void setKnightPosition(cocos2d::Vec2 position);//������ʿλ��
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);


	void setViewpointCenter(cocos2d::Vec2 position);//������ͼ��ʹ��ʿ������Ļ����
	void setViewpointCenter(cocos2d::Vec2 position, int first);

	void shootBullet(Vec2 position);

	void moveRandom();//���õ��˵�����ƶ�
	void update(float dt);//���õ��˵Ĳ�������ƶ�

	void enemyCreate();
	Enemy* nearestEnemy();//��������ʿ����ĵ��ˣ������ظ�enemy
	void bloodprogressInit();
	void manaprogressInit();
	void armorprogressInit();
	void bossCreate();
	void updateEnemyAttackToKnight(float dt);
	void updateBossAttackToKnight(float dt);
	CREATE_FUNC(BattleGround);
};

#endif //_BATTLEGROUND_H_