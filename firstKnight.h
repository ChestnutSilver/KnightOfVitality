/*#pragma once*/
#ifndef __SPACE_SHIP_H__
#define __SPACE_SHIP_H__

#include "cocos2d.h"

#define STEP 40

/*
CC_SYNTHESIZE(int, nTest, Test) 相当于干了下面这些事： 
protected: int nTest;  
public: virtual nTest getTest(void) const { return nTest; }  
public: virtual void setTest(int var){ nTest = var; }          */


class Knight : public cocos2d::Sprite
{
	Knight* knight;
	friend class battleground;
	CC_SYNTHESIZE(double, hitPoints, HitPoints);
	CC_SYNTHESIZE(double, manaPoints, ManaPoints);
	CC_SYNTHESIZE(double, armorPoints, ArmorPoints);
	CC_SYNTHESIZE(double, inithitPoints, InitHitPoints);
	CC_SYNTHESIZE(double, initmanaPoints, InitManaPoints);
	CC_SYNTHESIZE(double, initarmorPoints, InitArmorPoints);
	CC_SYNTHESIZE(double, myMovespeed, MyMovespeed);
	CC_SYNTHESIZE(double, myHurt, MyHurt);
	CC_SYNTHESIZE(double, myGetHurt, MyGetHurt);
	CC_SYNTHESIZE(double, myMaxHP, MyMaxHP);
	CC_SYNTHESIZE(double, upbuff, Upbuff);
	CC_SYNTHESIZE(double, downdebuff, Downdebuff);
	CC_SYNTHESIZE(double, swampSpeed, SwampSpeed);

	CC_SYNTHESIZE(int, placeType, PlaceType);
	CC_SYNTHESIZE(int, addcoin, Addcoin);

	CC_SYNTHESIZE(int, addspeed, Addspeed);//buff:移动速度增加
	CC_SYNTHESIZE(int, buffsteps, Buffsteps);//buff:移动速度增加
	CC_SYNTHESIZE(int, despeed, Despeed);//debuff:移动速度减少
	CC_SYNTHESIZE(int, debuffsteps, Debuffsteps);//buff:移动速度增加
	CC_SYNTHESIZE(bool, noenemy, Noenemy);//buff:无敌
	CC_SYNTHESIZE(int, noenemysteps, Noenemysteps);//buff:无敌

	//CC_SYNTHESIZE(int, battlesceneType, BattleSceneType);

public:

	//void initPosition(const cocos2d::Vec2& pos);已简化

	void moveStep(int dir);

	static Knight* createWithSpriteName(const char* spriteName, int knightGrade, int knightType);
	static Knight* createWithSpriteName(const char* spriteName, int knightGrade, int knightType, std::vector<bool>props);
	static void initSettings(Knight* knight, int knightGrade, int knightType);
	static void initSettings(Knight* knight, int knightGrade, int knightType, std::vector<bool>props);


	void TrapTerrain(cocos2d::Vec2 knightPos, Knight* knight);
	void getBloodbar(Knight* playerKnight, float a, int SCENE);
	void choiceProps(Knight* playerKnight, int SCENE);
	void pauseAndExit();

	static bool choiceProp1();
	static bool choiceProp2();
	static bool choiceProp3();
	static bool choicePause();
	static bool choiceExit();

	void prop1Callback(Ref* pSender);
	void prop2Callback(Ref* pSender);
	void prop3Callback(Ref* pSender);
	void setCallback(Ref* pSender);
	void exitCallback(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__

